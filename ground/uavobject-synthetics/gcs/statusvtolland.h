/**
 ******************************************************************************
 *
 * @file       statusvtolland.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: statusvtolland.xml. 
 *             This is an automatically generated file.
 *             DO NOT modify manually.
 *
 * @brief      The UAVUObjects GCS plugin 
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
#ifndef STATUSVTOLLAND_H
#define STATUSVTOLLAND_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT StatusVtolLand: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float AltitudeAtState_0 READ getAltitudeAtState_0 WRITE setAltitudeAtState_0 NOTIFY AltitudeAtState_0Changed);
    Q_PROPERTY(float AltitudeAtState_1 READ getAltitudeAtState_1 WRITE setAltitudeAtState_1 NOTIFY AltitudeAtState_1Changed);
    Q_PROPERTY(float AltitudeAtState_2 READ getAltitudeAtState_2 WRITE setAltitudeAtState_2 NOTIFY AltitudeAtState_2Changed);
    Q_PROPERTY(float AltitudeAtState_3 READ getAltitudeAtState_3 WRITE setAltitudeAtState_3 NOTIFY AltitudeAtState_3Changed);
    Q_PROPERTY(float AltitudeAtState_4 READ getAltitudeAtState_4 WRITE setAltitudeAtState_4 NOTIFY AltitudeAtState_4Changed);
    Q_PROPERTY(float AltitudeAtState_5 READ getAltitudeAtState_5 WRITE setAltitudeAtState_5 NOTIFY AltitudeAtState_5Changed);
    Q_PROPERTY(float AltitudeAtState_6 READ getAltitudeAtState_6 WRITE setAltitudeAtState_6 NOTIFY AltitudeAtState_6Changed);
    Q_PROPERTY(float AltitudeAtState_7 READ getAltitudeAtState_7 WRITE setAltitudeAtState_7 NOTIFY AltitudeAtState_7Changed);
    Q_PROPERTY(float AltitudeAtState_8 READ getAltitudeAtState_8 WRITE setAltitudeAtState_8 NOTIFY AltitudeAtState_8Changed);
    Q_PROPERTY(float AltitudeAtState_9 READ getAltitudeAtState_9 WRITE setAltitudeAtState_9 NOTIFY AltitudeAtState_9Changed);
    Q_PROPERTY(float targetDescentRate READ gettargetDescentRate WRITE settargetDescentRate NOTIFY targetDescentRateChanged);
    Q_PROPERTY(float averageDescentRate READ getaverageDescentRate WRITE setaverageDescentRate NOTIFY averageDescentRateChanged);
    Q_PROPERTY(float averageDescentThrust READ getaverageDescentThrust WRITE setaverageDescentThrust NOTIFY averageDescentThrustChanged);
    Q_PROPERTY(float calculatedNeutralThrust READ getcalculatedNeutralThrust WRITE setcalculatedNeutralThrust NOTIFY calculatedNeutralThrustChanged);
    Q_PROPERTY(float WtgForGroundEffect_BounceVelocity READ getWtgForGroundEffect_BounceVelocity WRITE setWtgForGroundEffect_BounceVelocity NOTIFY WtgForGroundEffect_BounceVelocityChanged);
    Q_PROPERTY(float WtgForGroundEffect_BounceAccel READ getWtgForGroundEffect_BounceAccel WRITE setWtgForGroundEffect_BounceAccel NOTIFY WtgForGroundEffect_BounceAccelChanged);
    Q_PROPERTY(quint8 State READ getState WRITE setState NOTIFY StateChanged);
    Q_PROPERTY(quint8 StateExitReason_0 READ getStateExitReason_0 WRITE setStateExitReason_0 NOTIFY StateExitReason_0Changed);
    Q_PROPERTY(quint8 StateExitReason_1 READ getStateExitReason_1 WRITE setStateExitReason_1 NOTIFY StateExitReason_1Changed);
    Q_PROPERTY(quint8 StateExitReason_2 READ getStateExitReason_2 WRITE setStateExitReason_2 NOTIFY StateExitReason_2Changed);
    Q_PROPERTY(quint8 StateExitReason_3 READ getStateExitReason_3 WRITE setStateExitReason_3 NOTIFY StateExitReason_3Changed);
    Q_PROPERTY(quint8 StateExitReason_4 READ getStateExitReason_4 WRITE setStateExitReason_4 NOTIFY StateExitReason_4Changed);
    Q_PROPERTY(quint8 StateExitReason_5 READ getStateExitReason_5 WRITE setStateExitReason_5 NOTIFY StateExitReason_5Changed);
    Q_PROPERTY(quint8 StateExitReason_6 READ getStateExitReason_6 WRITE setStateExitReason_6 NOTIFY StateExitReason_6Changed);
    Q_PROPERTY(quint8 StateExitReason_7 READ getStateExitReason_7 WRITE setStateExitReason_7 NOTIFY StateExitReason_7Changed);
    Q_PROPERTY(quint8 StateExitReason_8 READ getStateExitReason_8 WRITE setStateExitReason_8 NOTIFY StateExitReason_8Changed);
    Q_PROPERTY(quint8 StateExitReason_9 READ getStateExitReason_9 WRITE setStateExitReason_9 NOTIFY StateExitReason_9Changed);
    Q_PROPERTY(quint8 AltitudeState READ getAltitudeState WRITE setAltitudeState NOTIFY AltitudeStateChanged);


public:
    // Field structure
    typedef struct {
        float AltitudeAtState[10];
        float targetDescentRate;
        float averageDescentRate;
        float averageDescentThrust;
        float calculatedNeutralThrust;
        float WtgForGroundEffect[2];
        quint8 State;
        quint8 StateExitReason[10];
        quint8 AltitudeState;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field AltitudeAtState information
    /* Number of elements for field AltitudeAtState */
    static const quint32 ALTITUDEATSTATE_NUMELEM = 10;
    // Field targetDescentRate information
    // Field averageDescentRate information
    // Field averageDescentThrust information
    // Field calculatedNeutralThrust information
    // Field WtgForGroundEffect information
    /* Array element names for field WtgForGroundEffect */
    typedef enum { WTGFORGROUNDEFFECT_BOUNCEVELOCITY=0, WTGFORGROUNDEFFECT_BOUNCEACCEL=1 } WtgForGroundEffectElem;
    /* Number of elements for field WtgForGroundEffect */
    static const quint32 WTGFORGROUNDEFFECT_NUMELEM = 2;
    // Field State information
    /* Enumeration options for field State */
    typedef enum { STATE_INACTIVE=0, STATE_INITALTHOLD=1, STATE_WTGFORDESCENTRATE=2, STATE_ATDESCENTRATE=3, STATE_WTGFORGROUNDEFFECT=4, STATE_GROUNDEFFECT=5, STATE_THRUSTDOWN=6, STATE_THRUSTOFF=7, STATE_DISARMED=8, STATE_ABORT=9 } StateOptions;
    // Field StateExitReason information
    /* Enumeration options for field StateExitReason */
    typedef enum { STATEEXITREASON_NONE=0, STATEEXITREASON_DESCENTRATEOK=1, STATEEXITREASON_ONGROUND=2, STATEEXITREASON_BOUNCEVELOCITY=3, STATEEXITREASON_BOUNCEACCEL=4, STATEEXITREASON_LOWDESCENTRATE=5, STATEEXITREASON_ZEROTHRUST=6, STATEEXITREASON_POSITIONERROR=7, STATEEXITREASON_TIMEOUT=8 } StateExitReasonOptions;
    /* Number of elements for field StateExitReason */
    static const quint32 STATEEXITREASON_NUMELEM = 10;
    // Field AltitudeState information
    /* Enumeration options for field AltitudeState */
    typedef enum { ALTITUDESTATE_HIGH=0, ALTITUDESTATE_LOW=1 } AltitudeStateOptions;

  
    // Constants
    static const quint32 OBJID = 0x9F8D4E1E;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    StatusVtolLand();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static StatusVtolLand* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getAltitudeAtState(quint32 index) const;
    Q_INVOKABLE float getAltitudeAtState_0() const;
    Q_INVOKABLE float getAltitudeAtState_1() const;
    Q_INVOKABLE float getAltitudeAtState_2() const;
    Q_INVOKABLE float getAltitudeAtState_3() const;
    Q_INVOKABLE float getAltitudeAtState_4() const;
    Q_INVOKABLE float getAltitudeAtState_5() const;
    Q_INVOKABLE float getAltitudeAtState_6() const;
    Q_INVOKABLE float getAltitudeAtState_7() const;
    Q_INVOKABLE float getAltitudeAtState_8() const;
    Q_INVOKABLE float getAltitudeAtState_9() const;
    Q_INVOKABLE float gettargetDescentRate() const;
    Q_INVOKABLE float getaverageDescentRate() const;
    Q_INVOKABLE float getaverageDescentThrust() const;
    Q_INVOKABLE float getcalculatedNeutralThrust() const;
    Q_INVOKABLE float getWtgForGroundEffect(quint32 index) const;
    Q_INVOKABLE float getWtgForGroundEffect_BounceVelocity() const;
    Q_INVOKABLE float getWtgForGroundEffect_BounceAccel() const;
    Q_INVOKABLE quint8 getState() const;
    Q_INVOKABLE quint8 getStateExitReason(quint32 index) const;
    Q_INVOKABLE quint8 getStateExitReason_0() const;
    Q_INVOKABLE quint8 getStateExitReason_1() const;
    Q_INVOKABLE quint8 getStateExitReason_2() const;
    Q_INVOKABLE quint8 getStateExitReason_3() const;
    Q_INVOKABLE quint8 getStateExitReason_4() const;
    Q_INVOKABLE quint8 getStateExitReason_5() const;
    Q_INVOKABLE quint8 getStateExitReason_6() const;
    Q_INVOKABLE quint8 getStateExitReason_7() const;
    Q_INVOKABLE quint8 getStateExitReason_8() const;
    Q_INVOKABLE quint8 getStateExitReason_9() const;
    Q_INVOKABLE quint8 getAltitudeState() const;


public slots:
    void setAltitudeAtState(quint32 index, float value);
    void setAltitudeAtState_0(float value);
    void setAltitudeAtState_1(float value);
    void setAltitudeAtState_2(float value);
    void setAltitudeAtState_3(float value);
    void setAltitudeAtState_4(float value);
    void setAltitudeAtState_5(float value);
    void setAltitudeAtState_6(float value);
    void setAltitudeAtState_7(float value);
    void setAltitudeAtState_8(float value);
    void setAltitudeAtState_9(float value);
    void settargetDescentRate(float value);
    void setaverageDescentRate(float value);
    void setaverageDescentThrust(float value);
    void setcalculatedNeutralThrust(float value);
    void setWtgForGroundEffect(quint32 index, float value);
    void setWtgForGroundEffect_BounceVelocity(float value);
    void setWtgForGroundEffect_BounceAccel(float value);
    void setState(quint8 value);
    void setStateExitReason(quint32 index, quint8 value);
    void setStateExitReason_0(quint8 value);
    void setStateExitReason_1(quint8 value);
    void setStateExitReason_2(quint8 value);
    void setStateExitReason_3(quint8 value);
    void setStateExitReason_4(quint8 value);
    void setStateExitReason_5(quint8 value);
    void setStateExitReason_6(quint8 value);
    void setStateExitReason_7(quint8 value);
    void setStateExitReason_8(quint8 value);
    void setStateExitReason_9(quint8 value);
    void setAltitudeState(quint8 value);


signals:
    void AltitudeAtStateChanged(quint32 index, float value);
    void AltitudeAtState_0Changed(float value);
    void AltitudeAtState_1Changed(float value);
    void AltitudeAtState_2Changed(float value);
    void AltitudeAtState_3Changed(float value);
    void AltitudeAtState_4Changed(float value);
    void AltitudeAtState_5Changed(float value);
    void AltitudeAtState_6Changed(float value);
    void AltitudeAtState_7Changed(float value);
    void AltitudeAtState_8Changed(float value);
    void AltitudeAtState_9Changed(float value);
    void targetDescentRateChanged(float value);
    void averageDescentRateChanged(float value);
    void averageDescentThrustChanged(float value);
    void calculatedNeutralThrustChanged(float value);
    void WtgForGroundEffectChanged(quint32 index, float value);
    void WtgForGroundEffect_BounceVelocityChanged(float value);
    void WtgForGroundEffect_BounceAccelChanged(float value);
    void StateChanged(quint8 value);
    void StateExitReasonChanged(quint32 index, quint8 value);
    void StateExitReason_0Changed(quint8 value);
    void StateExitReason_1Changed(quint8 value);
    void StateExitReason_2Changed(quint8 value);
    void StateExitReason_3Changed(quint8 value);
    void StateExitReason_4Changed(quint8 value);
    void StateExitReason_5Changed(quint8 value);
    void StateExitReason_6Changed(quint8 value);
    void StateExitReason_7Changed(quint8 value);
    void StateExitReason_8Changed(quint8 value);
    void StateExitReason_9Changed(quint8 value);
    void AltitudeStateChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // STATUSVTOLLAND_H
