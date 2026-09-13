/**
 ******************************************************************************
 *
 * @file       inputpage.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @addtogroup
 * @{
 * @addtogroup InputPage
 * @{
 * @brief
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "inputpage.h"
#include "ui_inputpage.h"
#include "setupwizard.h"
#include "extensionsystem/pluginmanager.h"
#include "uavobjectmanager.h"
#include "hwsettings.h"

InputPage::InputPage(SetupWizard *wizard, QWidget *parent) :
    AbstractWizardPage(wizard, parent),

    ui(new Ui::InputPage)
{
    ui->setupUi(this);
}

InputPage::~InputPage()
{
    delete ui;
}

void InputPage::initializePage()
{
    /* The ESP32 Thing Plus target has exactly one receiver input: a
     * Spektrum satellite on the pin silkscreened RX1. Offering PWM, PPM or
     * S.Bus here would write a configuration the firmware cannot serve. */
    bool dsmOnly = getWizard()->getControllerType() == SetupWizard::CONTROLLER_ESP32;

    ui->pwmButton->setEnabled(!dsmOnly);
    ui->ppmButton->setEnabled(!dsmOnly);
    ui->sbusButton->setEnabled(!dsmOnly);
    if (dsmOnly) {
        ui->spectrumButton->setChecked(true);
        QString why = tr("This board takes a Spektrum satellite on RX1 only.");
        ui->pwmButton->setToolTip(why);
        ui->ppmButton->setToolTip(why);
        ui->sbusButton->setToolTip(why);
    }

    /* LiteWing has exactly two ways for sticks to arrive, and neither of them
     * is a wire into a receiver pin: there is no PWM header, no S.Bus input
     * and no hardware PPM (the RMT receiver picks up coupled noise on an
     * unconnected pin and starves the gyro interrupt, so it is not built).
     *
     * What it does have is the GCS receiver riding the telemetry link -- WiFi
     * UDP in flight, USB serial on the bench -- and a Spektrum satellite on
     * IO15. The PPM button is reused for the former because the wizard has no
     * separate notion of a link-borne receiver, so it is relabelled to say
     * what it actually selects rather than implying a cable. */
    if (getWizard()->getControllerType() == SetupWizard::CONTROLLER_LITEWING) {
        const QString why = tr("Not present on LiteWing: no PWM header, no "
                               "S.Bus input, and hardware PPM is not built.");
        ui->pwmButton->setEnabled(false);
        ui->sbusButton->setEnabled(false);
        ui->pwmButton->setToolTip(why);
        ui->sbusButton->setToolTip(why);

        ui->ppmButton->setEnabled(true);
        ui->ppmButton->setText(tr("Sticks over WiFi (GCS receiver)"));
        ui->ppmButton->setToolTip(tr("Control from the GCS over the telemetry "
                                     "link -- WiFi UDP in flight, USB serial on "
                                     "the bench. No receiver hardware."));
        ui->spectrumButton->setEnabled(true);
        ui->spectrumButton->setToolTip(tr("Spektrum DSMX satellite on IO15."));
    }
}

bool InputPage::validatePage()
{
    if (ui->pwmButton->isChecked()) {
        getWizard()->setInputType(SetupWizard::INPUT_PWM);
    } else if (ui->ppmButton->isChecked()) {
        getWizard()->setInputType(SetupWizard::INPUT_PPM);
    } else if (ui->sbusButton->isChecked()) {
        getWizard()->setInputType(SetupWizard::INPUT_SBUS);
    } else if (ui->spectrumButton->isChecked()) {
        getWizard()->setInputType(SetupWizard::INPUT_DSM);
    } else {
        getWizard()->setInputType(SetupWizard::INPUT_PWM);
    }
    getWizard()->setRestartNeeded(getWizard()->isRestartNeeded() || restartNeeded(getWizard()->getInputType()));

    return true;
}

bool InputPage::restartNeeded(VehicleConfigurationSource::INPUT_TYPE selectedType)
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    UAVObjectManager *uavoManager = pm->getObject<UAVObjectManager>();

    Q_ASSERT(uavoManager);
    HwSettings *hwSettings = HwSettings::GetInstance(uavoManager);
    HwSettings::DataFields data = hwSettings->getData();
    switch (getWizard()->getControllerType()) {
    case SetupWizard::CONTROLLER_CC:
    case SetupWizard::CONTROLLER_CC3D:
    {
        switch (selectedType) {
        case VehicleConfigurationSource::INPUT_PWM:
            return data.CC_RcvrPort != HwSettings::CC_RCVRPORT_PWMNOONESHOT;

        case VehicleConfigurationSource::INPUT_PPM:
            return data.CC_RcvrPort != HwSettings::CC_RCVRPORT_PPMNOONESHOT;

        case VehicleConfigurationSource::INPUT_SBUS:
            return data.CC_MainPort != HwSettings::CC_MAINPORT_SBUS;

        case VehicleConfigurationSource::INPUT_DSM:
            // TODO: Handle all of the DSM types ?? Which is most common?
            return data.CC_MainPort != HwSettings::CC_MAINPORT_DSM;

        default: return true;
        }
        break;
    }
    case SetupWizard::CONTROLLER_ESP32:
        /* The Spektrum satellite is the only receiver this board has, and
         * it lives on a fixed UART -- there is no port mode to flip and
         * nothing a reboot would re-init. */
        return false;

    case SetupWizard::CONTROLLER_REVO:
    case SetupWizard::CONTROLLER_REALPOSIX:
    case SetupWizard::CONTROLLER_DISCOVERYF4:
    {
        switch (selectedType) {
        case VehicleConfigurationSource::INPUT_PWM:
            return data.RM_RcvrPort != HwSettings::RM_RCVRPORT_PWM;

        case VehicleConfigurationSource::INPUT_PPM:
            return data.RM_RcvrPort != HwSettings::RM_RCVRPORT_PPM;

        case VehicleConfigurationSource::INPUT_SBUS:
            return data.RM_MainPort != HwSettings::RM_MAINPORT_SBUS;

        case VehicleConfigurationSource::INPUT_DSM:
            // TODO: Handle all of the DSM types ?? Which is most common?
            return data.RM_MainPort != HwSettings::RM_MAINPORT_DSM;

        default: return true;
        }
        break;
    }
    default: return true;
    }
}
