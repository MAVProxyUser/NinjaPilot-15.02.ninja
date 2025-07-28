/**
 ******************************************************************************
 *
 * @file       groundtruth.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: groundtruth.xml. 
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
#ifndef GROUNDTRUTH_H
#define GROUNDTRUTH_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT GroundTruth: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float AccelerationXYZ_0 READ getAccelerationXYZ_0 WRITE setAccelerationXYZ_0 NOTIFY AccelerationXYZ_0Changed);
    Q_PROPERTY(float AccelerationXYZ_1 READ getAccelerationXYZ_1 WRITE setAccelerationXYZ_1 NOTIFY AccelerationXYZ_1Changed);
    Q_PROPERTY(float AccelerationXYZ_2 READ getAccelerationXYZ_2 WRITE setAccelerationXYZ_2 NOTIFY AccelerationXYZ_2Changed);
    Q_PROPERTY(float PositionNED_0 READ getPositionNED_0 WRITE setPositionNED_0 NOTIFY PositionNED_0Changed);
    Q_PROPERTY(float PositionNED_1 READ getPositionNED_1 WRITE setPositionNED_1 NOTIFY PositionNED_1Changed);
    Q_PROPERTY(float PositionNED_2 READ getPositionNED_2 WRITE setPositionNED_2 NOTIFY PositionNED_2Changed);
    Q_PROPERTY(float VelocityNED_0 READ getVelocityNED_0 WRITE setVelocityNED_0 NOTIFY VelocityNED_0Changed);
    Q_PROPERTY(float VelocityNED_1 READ getVelocityNED_1 WRITE setVelocityNED_1 NOTIFY VelocityNED_1Changed);
    Q_PROPERTY(float VelocityNED_2 READ getVelocityNED_2 WRITE setVelocityNED_2 NOTIFY VelocityNED_2Changed);
    Q_PROPERTY(float RPY_0 READ getRPY_0 WRITE setRPY_0 NOTIFY RPY_0Changed);
    Q_PROPERTY(float RPY_1 READ getRPY_1 WRITE setRPY_1 NOTIFY RPY_1Changed);
    Q_PROPERTY(float RPY_2 READ getRPY_2 WRITE setRPY_2 NOTIFY RPY_2Changed);
    Q_PROPERTY(float AngularRates_0 READ getAngularRates_0 WRITE setAngularRates_0 NOTIFY AngularRates_0Changed);
    Q_PROPERTY(float AngularRates_1 READ getAngularRates_1 WRITE setAngularRates_1 NOTIFY AngularRates_1Changed);
    Q_PROPERTY(float AngularRates_2 READ getAngularRates_2 WRITE setAngularRates_2 NOTIFY AngularRates_2Changed);
    Q_PROPERTY(float TrueAirspeed READ getTrueAirspeed WRITE setTrueAirspeed NOTIFY TrueAirspeedChanged);
    Q_PROPERTY(float CalibratedAirspeed READ getCalibratedAirspeed WRITE setCalibratedAirspeed NOTIFY CalibratedAirspeedChanged);
    Q_PROPERTY(float AngleOfAttack READ getAngleOfAttack WRITE setAngleOfAttack NOTIFY AngleOfAttackChanged);
    Q_PROPERTY(float AngleOfSlip READ getAngleOfSlip WRITE setAngleOfSlip NOTIFY AngleOfSlipChanged);


public:
    // Field structure
    typedef struct {
        float AccelerationXYZ[3];
        float PositionNED[3];
        float VelocityNED[3];
        float RPY[3];
        float AngularRates[3];
        float TrueAirspeed;
        float CalibratedAirspeed;
        float AngleOfAttack;
        float AngleOfSlip;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field AccelerationXYZ information
    /* Number of elements for field AccelerationXYZ */
    static const quint32 ACCELERATIONXYZ_NUMELEM = 3;
    // Field PositionNED information
    /* Number of elements for field PositionNED */
    static const quint32 POSITIONNED_NUMELEM = 3;
    // Field VelocityNED information
    /* Number of elements for field VelocityNED */
    static const quint32 VELOCITYNED_NUMELEM = 3;
    // Field RPY information
    /* Number of elements for field RPY */
    static const quint32 RPY_NUMELEM = 3;
    // Field AngularRates information
    /* Number of elements for field AngularRates */
    static const quint32 ANGULARRATES_NUMELEM = 3;
    // Field TrueAirspeed information
    // Field CalibratedAirspeed information
    // Field AngleOfAttack information
    // Field AngleOfSlip information

  
    // Constants
    static const quint32 OBJID = 0xF178DCA8;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    GroundTruth();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static GroundTruth* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getAccelerationXYZ(quint32 index) const;
    Q_INVOKABLE float getAccelerationXYZ_0() const;
    Q_INVOKABLE float getAccelerationXYZ_1() const;
    Q_INVOKABLE float getAccelerationXYZ_2() const;
    Q_INVOKABLE float getPositionNED(quint32 index) const;
    Q_INVOKABLE float getPositionNED_0() const;
    Q_INVOKABLE float getPositionNED_1() const;
    Q_INVOKABLE float getPositionNED_2() const;
    Q_INVOKABLE float getVelocityNED(quint32 index) const;
    Q_INVOKABLE float getVelocityNED_0() const;
    Q_INVOKABLE float getVelocityNED_1() const;
    Q_INVOKABLE float getVelocityNED_2() const;
    Q_INVOKABLE float getRPY(quint32 index) const;
    Q_INVOKABLE float getRPY_0() const;
    Q_INVOKABLE float getRPY_1() const;
    Q_INVOKABLE float getRPY_2() const;
    Q_INVOKABLE float getAngularRates(quint32 index) const;
    Q_INVOKABLE float getAngularRates_0() const;
    Q_INVOKABLE float getAngularRates_1() const;
    Q_INVOKABLE float getAngularRates_2() const;
    Q_INVOKABLE float getTrueAirspeed() const;
    Q_INVOKABLE float getCalibratedAirspeed() const;
    Q_INVOKABLE float getAngleOfAttack() const;
    Q_INVOKABLE float getAngleOfSlip() const;


public slots:
    void setAccelerationXYZ(quint32 index, float value);
    void setAccelerationXYZ_0(float value);
    void setAccelerationXYZ_1(float value);
    void setAccelerationXYZ_2(float value);
    void setPositionNED(quint32 index, float value);
    void setPositionNED_0(float value);
    void setPositionNED_1(float value);
    void setPositionNED_2(float value);
    void setVelocityNED(quint32 index, float value);
    void setVelocityNED_0(float value);
    void setVelocityNED_1(float value);
    void setVelocityNED_2(float value);
    void setRPY(quint32 index, float value);
    void setRPY_0(float value);
    void setRPY_1(float value);
    void setRPY_2(float value);
    void setAngularRates(quint32 index, float value);
    void setAngularRates_0(float value);
    void setAngularRates_1(float value);
    void setAngularRates_2(float value);
    void setTrueAirspeed(float value);
    void setCalibratedAirspeed(float value);
    void setAngleOfAttack(float value);
    void setAngleOfSlip(float value);


signals:
    void AccelerationXYZChanged(quint32 index, float value);
    void AccelerationXYZ_0Changed(float value);
    void AccelerationXYZ_1Changed(float value);
    void AccelerationXYZ_2Changed(float value);
    void PositionNEDChanged(quint32 index, float value);
    void PositionNED_0Changed(float value);
    void PositionNED_1Changed(float value);
    void PositionNED_2Changed(float value);
    void VelocityNEDChanged(quint32 index, float value);
    void VelocityNED_0Changed(float value);
    void VelocityNED_1Changed(float value);
    void VelocityNED_2Changed(float value);
    void RPYChanged(quint32 index, float value);
    void RPY_0Changed(float value);
    void RPY_1Changed(float value);
    void RPY_2Changed(float value);
    void AngularRatesChanged(quint32 index, float value);
    void AngularRates_0Changed(float value);
    void AngularRates_1Changed(float value);
    void AngularRates_2Changed(float value);
    void TrueAirspeedChanged(float value);
    void CalibratedAirspeedChanged(float value);
    void AngleOfAttackChanged(float value);
    void AngleOfSlipChanged(float value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // GROUNDTRUTH_H
