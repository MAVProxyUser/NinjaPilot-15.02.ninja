/**
 * This file is part of SDLGamepad.
 *
 * SDLGamepad is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SDLGamepad is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Manuel Blanquett
 * mail.nalla@gmail.com
 */

/**********************************************************************/
#include "sdlgamepad.h"

#include <SDL2/SDL.h>
// #undef main

class SDLGamepadPrivate {
public:
    SDLGamepadPrivate() : gamepad(0)
    {}

    /**
     * SDL_GameController object.
     *
     * This represents the currently opened SDL_GameController object.
     */
    SDL_GameController *gamepad;
};

/**********************************************************************/
SDLGamepad::SDLGamepad()
{
    buttons = -1;
    axes    = -1;
    index   = -1;
    loop    = false;
    tick    = MIN_RATE;
    priv    = new SDLGamepadPrivate;
}

/**********************************************************************/
SDLGamepad::~SDLGamepad()
{
    loop = false;

    if (priv->gamepad) {
        SDL_GameControllerClose(priv->gamepad);
    }

    SDL_Quit();

    delete priv;
}

/**********************************************************************/
bool SDLGamepad::init()
{
    if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
        return false;
    }

    int numControllers = 0;
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            numControllers++;
        }
    }

    if (numControllers > 0) {
        emit gamepads(numControllers);

        if (!setGamepad(0)) {
            return false;
        }

        for (qint8 i = 0; i < buttons; i++) {
            buttonStates.append(0);
        }
    } else {
        return false;
    }

    loop = true;
    return true;
}

/**********************************************************************/
void SDLGamepad::run()
{
    while (loop) {
        updateAxes();
        updateButtons();
        msleep(tick);
    }
}

/**********************************************************************/
bool SDLGamepad::setGamepad(qint16 index)
{
    if (index != this->index) {
        if (priv->gamepad) {
            SDL_GameControllerClose(priv->gamepad);
        }

        // Find the index-th game controller
        int controllerIndex = -1;
        int controllerCount = 0;
        for (int i = 0; i < SDL_NumJoysticks(); i++) {
            if (SDL_IsGameController(i)) {
                if (controllerCount == index) {
                    controllerIndex = i;
                    break;
                }
                controllerCount++;
            }
        }

        if (controllerIndex >= 0) {
            priv->gamepad = SDL_GameControllerOpen(controllerIndex);

            if (priv->gamepad) {
                SDL_Joystick *joystick = SDL_GameControllerGetJoystick(priv->gamepad);
                buttons = SDL_JoystickNumButtons(joystick);
                axes    = SDL_JoystickNumAxes(joystick);

                if (axes >= 4) {
                    this->index = index;
                    return true;
                } else {
                    buttons     = -1;
                    axes        = -1;
                    this->index = -1;
                    qCritical("Gamepad has less than 4 axes");
                }
            } else {
                buttons     = -1;
                axes        = -1;
                this->index = -1;
                qCritical("Unable to open Gamepad!");
            }
        } else {
            buttons     = -1;
            axes        = -1;
            this->index = -1;
            qCritical("Invalid gamepad index!");
        }
    }

    return false;
}

/**********************************************************************/
void SDLGamepad::setTickRate(qint16 ms)
{
    tick = ms;
}

/**********************************************************************/
void SDLGamepad::updateAxes()
{
    if (priv->gamepad) {
        QListInt16 values;
        SDL_GameControllerUpdate();

        SDL_Joystick *joystick = SDL_GameControllerGetJoystick(priv->gamepad);
        for (qint8 i = 0; i < axes; i++) {
            qint16 value = SDL_JoystickGetAxis(joystick, i);

            if (value > -NULL_RANGE && value < NULL_RANGE) {
                value = 0;
            }

            values.append(value);
        }

        emit axesValues(values);
    }
}

/**********************************************************************/
void SDLGamepad::updateButtons()
{
    if (priv->gamepad) {
        SDL_GameControllerUpdate();

        SDL_Joystick *joystick = SDL_GameControllerGetJoystick(priv->gamepad);
        for (qint8 i = 0; i < buttons; i++) {
            qint16 state = SDL_JoystickGetButton(joystick, i);

            if (buttonStates.at(i) != state) {
                if (state > 0) {
                    emit buttonState((ButtonNumber)i, true);
                } else {
                    emit buttonState((ButtonNumber)i, false);
                }

                buttonStates.replace(i, state);
            }
        }
    }
}

/**********************************************************************/
void SDLGamepad::quit()
{
    loop = false;
}

/**********************************************************************/
qint16 SDLGamepad::getAxes()
{
    return axes;
}

/**********************************************************************/
qint16 SDLGamepad::getButtons()
{
    return buttons;
}
