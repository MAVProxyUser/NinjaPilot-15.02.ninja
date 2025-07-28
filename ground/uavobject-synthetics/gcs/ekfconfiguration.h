/**
 ******************************************************************************
 *
 * @file       ekfconfiguration.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: ekfconfiguration.xml. 
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
#ifndef EKFCONFIGURATION_H
#define EKFCONFIGURATION_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT EKFConfiguration: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float P_PositionNorth READ getP_PositionNorth WRITE setP_PositionNorth NOTIFY P_PositionNorthChanged);
    Q_PROPERTY(float P_PositionEast READ getP_PositionEast WRITE setP_PositionEast NOTIFY P_PositionEastChanged);
    Q_PROPERTY(float P_PositionDown READ getP_PositionDown WRITE setP_PositionDown NOTIFY P_PositionDownChanged);
    Q_PROPERTY(float P_VelocityNorth READ getP_VelocityNorth WRITE setP_VelocityNorth NOTIFY P_VelocityNorthChanged);
    Q_PROPERTY(float P_VelocityEast READ getP_VelocityEast WRITE setP_VelocityEast NOTIFY P_VelocityEastChanged);
    Q_PROPERTY(float P_VelocityDown READ getP_VelocityDown WRITE setP_VelocityDown NOTIFY P_VelocityDownChanged);
    Q_PROPERTY(float P_AttitudeQ1 READ getP_AttitudeQ1 WRITE setP_AttitudeQ1 NOTIFY P_AttitudeQ1Changed);
    Q_PROPERTY(float P_AttitudeQ2 READ getP_AttitudeQ2 WRITE setP_AttitudeQ2 NOTIFY P_AttitudeQ2Changed);
    Q_PROPERTY(float P_AttitudeQ3 READ getP_AttitudeQ3 WRITE setP_AttitudeQ3 NOTIFY P_AttitudeQ3Changed);
    Q_PROPERTY(float P_AttitudeQ4 READ getP_AttitudeQ4 WRITE setP_AttitudeQ4 NOTIFY P_AttitudeQ4Changed);
    Q_PROPERTY(float P_GyroDriftX READ getP_GyroDriftX WRITE setP_GyroDriftX NOTIFY P_GyroDriftXChanged);
    Q_PROPERTY(float P_GyroDriftY READ getP_GyroDriftY WRITE setP_GyroDriftY NOTIFY P_GyroDriftYChanged);
    Q_PROPERTY(float P_GyroDriftZ READ getP_GyroDriftZ WRITE setP_GyroDriftZ NOTIFY P_GyroDriftZChanged);
    Q_PROPERTY(float Q_GyroX READ getQ_GyroX WRITE setQ_GyroX NOTIFY Q_GyroXChanged);
    Q_PROPERTY(float Q_GyroY READ getQ_GyroY WRITE setQ_GyroY NOTIFY Q_GyroYChanged);
    Q_PROPERTY(float Q_GyroZ READ getQ_GyroZ WRITE setQ_GyroZ NOTIFY Q_GyroZChanged);
    Q_PROPERTY(float Q_AccelX READ getQ_AccelX WRITE setQ_AccelX NOTIFY Q_AccelXChanged);
    Q_PROPERTY(float Q_AccelY READ getQ_AccelY WRITE setQ_AccelY NOTIFY Q_AccelYChanged);
    Q_PROPERTY(float Q_AccelZ READ getQ_AccelZ WRITE setQ_AccelZ NOTIFY Q_AccelZChanged);
    Q_PROPERTY(float Q_GyroDriftX READ getQ_GyroDriftX WRITE setQ_GyroDriftX NOTIFY Q_GyroDriftXChanged);
    Q_PROPERTY(float Q_GyroDriftY READ getQ_GyroDriftY WRITE setQ_GyroDriftY NOTIFY Q_GyroDriftYChanged);
    Q_PROPERTY(float Q_GyroDriftZ READ getQ_GyroDriftZ WRITE setQ_GyroDriftZ NOTIFY Q_GyroDriftZChanged);
    Q_PROPERTY(float R_GPSPosNorth READ getR_GPSPosNorth WRITE setR_GPSPosNorth NOTIFY R_GPSPosNorthChanged);
    Q_PROPERTY(float R_GPSPosEast READ getR_GPSPosEast WRITE setR_GPSPosEast NOTIFY R_GPSPosEastChanged);
    Q_PROPERTY(float R_GPSPosDown READ getR_GPSPosDown WRITE setR_GPSPosDown NOTIFY R_GPSPosDownChanged);
    Q_PROPERTY(float R_GPSVelNorth READ getR_GPSVelNorth WRITE setR_GPSVelNorth NOTIFY R_GPSVelNorthChanged);
    Q_PROPERTY(float R_GPSVelEast READ getR_GPSVelEast WRITE setR_GPSVelEast NOTIFY R_GPSVelEastChanged);
    Q_PROPERTY(float R_GPSVelDown READ getR_GPSVelDown WRITE setR_GPSVelDown NOTIFY R_GPSVelDownChanged);
    Q_PROPERTY(float R_MagX READ getR_MagX WRITE setR_MagX NOTIFY R_MagXChanged);
    Q_PROPERTY(float R_MagY READ getR_MagY WRITE setR_MagY NOTIFY R_MagYChanged);
    Q_PROPERTY(float R_MagZ READ getR_MagZ WRITE setR_MagZ NOTIFY R_MagZChanged);
    Q_PROPERTY(float R_BaroZ READ getR_BaroZ WRITE setR_BaroZ NOTIFY R_BaroZChanged);
    Q_PROPERTY(float FakeR_FakeGPSPosIndoor READ getFakeR_FakeGPSPosIndoor WRITE setFakeR_FakeGPSPosIndoor NOTIFY FakeR_FakeGPSPosIndoorChanged);
    Q_PROPERTY(float FakeR_FakeGPSVelIndoor READ getFakeR_FakeGPSVelIndoor WRITE setFakeR_FakeGPSVelIndoor NOTIFY FakeR_FakeGPSVelIndoorChanged);
    Q_PROPERTY(float FakeR_FakeGPSVelAirspeed READ getFakeR_FakeGPSVelAirspeed WRITE setFakeR_FakeGPSVelAirspeed NOTIFY FakeR_FakeGPSVelAirspeedChanged);


public:
    // Field structure
    typedef struct {
        float P[13];
        float Q[9];
        float R[10];
        float FakeR[3];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field P information
    /* Array element names for field P */
    typedef enum { P_POSITIONNORTH=0, P_POSITIONEAST=1, P_POSITIONDOWN=2, P_VELOCITYNORTH=3, P_VELOCITYEAST=4, P_VELOCITYDOWN=5, P_ATTITUDEQ1=6, P_ATTITUDEQ2=7, P_ATTITUDEQ3=8, P_ATTITUDEQ4=9, P_GYRODRIFTX=10, P_GYRODRIFTY=11, P_GYRODRIFTZ=12 } PElem;
    /* Number of elements for field P */
    static const quint32 P_NUMELEM = 13;
    // Field Q information
    /* Array element names for field Q */
    typedef enum { Q_GYROX=0, Q_GYROY=1, Q_GYROZ=2, Q_ACCELX=3, Q_ACCELY=4, Q_ACCELZ=5, Q_GYRODRIFTX=6, Q_GYRODRIFTY=7, Q_GYRODRIFTZ=8 } QElem;
    /* Number of elements for field Q */
    static const quint32 Q_NUMELEM = 9;
    // Field R information
    /* Array element names for field R */
    typedef enum { R_GPSPOSNORTH=0, R_GPSPOSEAST=1, R_GPSPOSDOWN=2, R_GPSVELNORTH=3, R_GPSVELEAST=4, R_GPSVELDOWN=5, R_MAGX=6, R_MAGY=7, R_MAGZ=8, R_BAROZ=9 } RElem;
    /* Number of elements for field R */
    static const quint32 R_NUMELEM = 10;
    // Field FakeR information
    /* Array element names for field FakeR */
    typedef enum { FAKER_FAKEGPSPOSINDOOR=0, FAKER_FAKEGPSVELINDOOR=1, FAKER_FAKEGPSVELAIRSPEED=2 } FakeRElem;
    /* Number of elements for field FakeR */
    static const quint32 FAKER_NUMELEM = 3;

  
    // Constants
    static const quint32 OBJID = 0x5E91213C;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    EKFConfiguration();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static EKFConfiguration* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getP(quint32 index) const;
    Q_INVOKABLE float getP_PositionNorth() const;
    Q_INVOKABLE float getP_PositionEast() const;
    Q_INVOKABLE float getP_PositionDown() const;
    Q_INVOKABLE float getP_VelocityNorth() const;
    Q_INVOKABLE float getP_VelocityEast() const;
    Q_INVOKABLE float getP_VelocityDown() const;
    Q_INVOKABLE float getP_AttitudeQ1() const;
    Q_INVOKABLE float getP_AttitudeQ2() const;
    Q_INVOKABLE float getP_AttitudeQ3() const;
    Q_INVOKABLE float getP_AttitudeQ4() const;
    Q_INVOKABLE float getP_GyroDriftX() const;
    Q_INVOKABLE float getP_GyroDriftY() const;
    Q_INVOKABLE float getP_GyroDriftZ() const;
    Q_INVOKABLE float getQ(quint32 index) const;
    Q_INVOKABLE float getQ_GyroX() const;
    Q_INVOKABLE float getQ_GyroY() const;
    Q_INVOKABLE float getQ_GyroZ() const;
    Q_INVOKABLE float getQ_AccelX() const;
    Q_INVOKABLE float getQ_AccelY() const;
    Q_INVOKABLE float getQ_AccelZ() const;
    Q_INVOKABLE float getQ_GyroDriftX() const;
    Q_INVOKABLE float getQ_GyroDriftY() const;
    Q_INVOKABLE float getQ_GyroDriftZ() const;
    Q_INVOKABLE float getR(quint32 index) const;
    Q_INVOKABLE float getR_GPSPosNorth() const;
    Q_INVOKABLE float getR_GPSPosEast() const;
    Q_INVOKABLE float getR_GPSPosDown() const;
    Q_INVOKABLE float getR_GPSVelNorth() const;
    Q_INVOKABLE float getR_GPSVelEast() const;
    Q_INVOKABLE float getR_GPSVelDown() const;
    Q_INVOKABLE float getR_MagX() const;
    Q_INVOKABLE float getR_MagY() const;
    Q_INVOKABLE float getR_MagZ() const;
    Q_INVOKABLE float getR_BaroZ() const;
    Q_INVOKABLE float getFakeR(quint32 index) const;
    Q_INVOKABLE float getFakeR_FakeGPSPosIndoor() const;
    Q_INVOKABLE float getFakeR_FakeGPSVelIndoor() const;
    Q_INVOKABLE float getFakeR_FakeGPSVelAirspeed() const;


public slots:
    void setP(quint32 index, float value);
    void setP_PositionNorth(float value);
    void setP_PositionEast(float value);
    void setP_PositionDown(float value);
    void setP_VelocityNorth(float value);
    void setP_VelocityEast(float value);
    void setP_VelocityDown(float value);
    void setP_AttitudeQ1(float value);
    void setP_AttitudeQ2(float value);
    void setP_AttitudeQ3(float value);
    void setP_AttitudeQ4(float value);
    void setP_GyroDriftX(float value);
    void setP_GyroDriftY(float value);
    void setP_GyroDriftZ(float value);
    void setQ(quint32 index, float value);
    void setQ_GyroX(float value);
    void setQ_GyroY(float value);
    void setQ_GyroZ(float value);
    void setQ_AccelX(float value);
    void setQ_AccelY(float value);
    void setQ_AccelZ(float value);
    void setQ_GyroDriftX(float value);
    void setQ_GyroDriftY(float value);
    void setQ_GyroDriftZ(float value);
    void setR(quint32 index, float value);
    void setR_GPSPosNorth(float value);
    void setR_GPSPosEast(float value);
    void setR_GPSPosDown(float value);
    void setR_GPSVelNorth(float value);
    void setR_GPSVelEast(float value);
    void setR_GPSVelDown(float value);
    void setR_MagX(float value);
    void setR_MagY(float value);
    void setR_MagZ(float value);
    void setR_BaroZ(float value);
    void setFakeR(quint32 index, float value);
    void setFakeR_FakeGPSPosIndoor(float value);
    void setFakeR_FakeGPSVelIndoor(float value);
    void setFakeR_FakeGPSVelAirspeed(float value);


signals:
    void PChanged(quint32 index, float value);
    void P_PositionNorthChanged(float value);
    void P_PositionEastChanged(float value);
    void P_PositionDownChanged(float value);
    void P_VelocityNorthChanged(float value);
    void P_VelocityEastChanged(float value);
    void P_VelocityDownChanged(float value);
    void P_AttitudeQ1Changed(float value);
    void P_AttitudeQ2Changed(float value);
    void P_AttitudeQ3Changed(float value);
    void P_AttitudeQ4Changed(float value);
    void P_GyroDriftXChanged(float value);
    void P_GyroDriftYChanged(float value);
    void P_GyroDriftZChanged(float value);
    void QChanged(quint32 index, float value);
    void Q_GyroXChanged(float value);
    void Q_GyroYChanged(float value);
    void Q_GyroZChanged(float value);
    void Q_AccelXChanged(float value);
    void Q_AccelYChanged(float value);
    void Q_AccelZChanged(float value);
    void Q_GyroDriftXChanged(float value);
    void Q_GyroDriftYChanged(float value);
    void Q_GyroDriftZChanged(float value);
    void RChanged(quint32 index, float value);
    void R_GPSPosNorthChanged(float value);
    void R_GPSPosEastChanged(float value);
    void R_GPSPosDownChanged(float value);
    void R_GPSVelNorthChanged(float value);
    void R_GPSVelEastChanged(float value);
    void R_GPSVelDownChanged(float value);
    void R_MagXChanged(float value);
    void R_MagYChanged(float value);
    void R_MagZChanged(float value);
    void R_BaroZChanged(float value);
    void FakeRChanged(quint32 index, float value);
    void FakeR_FakeGPSPosIndoorChanged(float value);
    void FakeR_FakeGPSVelIndoorChanged(float value);
    void FakeR_FakeGPSVelAirspeedChanged(float value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // EKFCONFIGURATION_H
