/**
 ******************************************************************************
 *
 * @file       attitudesettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: attitudesettings.xml. 
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
#ifndef ATTITUDESETTINGS_H
#define ATTITUDESETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT AttitudeSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float BoardRotation_Roll READ getBoardRotation_Roll WRITE setBoardRotation_Roll NOTIFY BoardRotation_RollChanged);
    Q_PROPERTY(float BoardRotation_Pitch READ getBoardRotation_Pitch WRITE setBoardRotation_Pitch NOTIFY BoardRotation_PitchChanged);
    Q_PROPERTY(float BoardRotation_Yaw READ getBoardRotation_Yaw WRITE setBoardRotation_Yaw NOTIFY BoardRotation_YawChanged);
    Q_PROPERTY(float BoardLevelTrim_Roll READ getBoardLevelTrim_Roll WRITE setBoardLevelTrim_Roll NOTIFY BoardLevelTrim_RollChanged);
    Q_PROPERTY(float BoardLevelTrim_Pitch READ getBoardLevelTrim_Pitch WRITE setBoardLevelTrim_Pitch NOTIFY BoardLevelTrim_PitchChanged);
    Q_PROPERTY(float AccelKp READ getAccelKp WRITE setAccelKp NOTIFY AccelKpChanged);
    Q_PROPERTY(float AccelKi READ getAccelKi WRITE setAccelKi NOTIFY AccelKiChanged);
    Q_PROPERTY(float MagKi READ getMagKi WRITE setMagKi NOTIFY MagKiChanged);
    Q_PROPERTY(float MagKp READ getMagKp WRITE setMagKp NOTIFY MagKpChanged);
    Q_PROPERTY(float AccelTau READ getAccelTau WRITE setAccelTau NOTIFY AccelTauChanged);
    Q_PROPERTY(float YawBiasRate READ getYawBiasRate WRITE setYawBiasRate NOTIFY YawBiasRateChanged);
    Q_PROPERTY(quint8 ZeroDuringArming READ getZeroDuringArming WRITE setZeroDuringArming NOTIFY ZeroDuringArmingChanged);
    Q_PROPERTY(quint8 BiasCorrectGyro READ getBiasCorrectGyro WRITE setBiasCorrectGyro NOTIFY BiasCorrectGyroChanged);
    Q_PROPERTY(quint8 TrimFlight READ getTrimFlight WRITE setTrimFlight NOTIFY TrimFlightChanged);


public:
    // Field structure
    typedef struct {
        float BoardRotation[3];
        float BoardLevelTrim[2];
        float AccelKp;
        float AccelKi;
        float MagKi;
        float MagKp;
        float AccelTau;
        float YawBiasRate;
        quint8 ZeroDuringArming;
        quint8 BiasCorrectGyro;
        quint8 TrimFlight;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field BoardRotation information
    /* Array element names for field BoardRotation */
    typedef enum { BOARDROTATION_ROLL=0, BOARDROTATION_PITCH=1, BOARDROTATION_YAW=2 } BoardRotationElem;
    /* Number of elements for field BoardRotation */
    static const quint32 BOARDROTATION_NUMELEM = 3;
    // Field BoardLevelTrim information
    /* Array element names for field BoardLevelTrim */
    typedef enum { BOARDLEVELTRIM_ROLL=0, BOARDLEVELTRIM_PITCH=1 } BoardLevelTrimElem;
    /* Number of elements for field BoardLevelTrim */
    static const quint32 BOARDLEVELTRIM_NUMELEM = 2;
    // Field AccelKp information
    // Field AccelKi information
    // Field MagKi information
    // Field MagKp information
    // Field AccelTau information
    // Field YawBiasRate information
    // Field ZeroDuringArming information
    /* Enumeration options for field ZeroDuringArming */
    typedef enum { ZERODURINGARMING_FALSE=0, ZERODURINGARMING_TRUE=1 } ZeroDuringArmingOptions;
    // Field BiasCorrectGyro information
    /* Enumeration options for field BiasCorrectGyro */
    typedef enum { BIASCORRECTGYRO_FALSE=0, BIASCORRECTGYRO_TRUE=1 } BiasCorrectGyroOptions;
    // Field TrimFlight information
    /* Enumeration options for field TrimFlight */
    typedef enum { TRIMFLIGHT_NORMAL=0, TRIMFLIGHT_START=1, TRIMFLIGHT_LOAD=2 } TrimFlightOptions;

  
    // Constants
    static const quint32 OBJID = 0x448954B8;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    AttitudeSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static AttitudeSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getBoardRotation(quint32 index) const;
    Q_INVOKABLE float getBoardRotation_Roll() const;
    Q_INVOKABLE float getBoardRotation_Pitch() const;
    Q_INVOKABLE float getBoardRotation_Yaw() const;
    Q_INVOKABLE float getBoardLevelTrim(quint32 index) const;
    Q_INVOKABLE float getBoardLevelTrim_Roll() const;
    Q_INVOKABLE float getBoardLevelTrim_Pitch() const;
    Q_INVOKABLE float getAccelKp() const;
    Q_INVOKABLE float getAccelKi() const;
    Q_INVOKABLE float getMagKi() const;
    Q_INVOKABLE float getMagKp() const;
    Q_INVOKABLE float getAccelTau() const;
    Q_INVOKABLE float getYawBiasRate() const;
    Q_INVOKABLE quint8 getZeroDuringArming() const;
    Q_INVOKABLE quint8 getBiasCorrectGyro() const;
    Q_INVOKABLE quint8 getTrimFlight() const;


public slots:
    void setBoardRotation(quint32 index, float value);
    void setBoardRotation_Roll(float value);
    void setBoardRotation_Pitch(float value);
    void setBoardRotation_Yaw(float value);
    void setBoardLevelTrim(quint32 index, float value);
    void setBoardLevelTrim_Roll(float value);
    void setBoardLevelTrim_Pitch(float value);
    void setAccelKp(float value);
    void setAccelKi(float value);
    void setMagKi(float value);
    void setMagKp(float value);
    void setAccelTau(float value);
    void setYawBiasRate(float value);
    void setZeroDuringArming(quint8 value);
    void setBiasCorrectGyro(quint8 value);
    void setTrimFlight(quint8 value);


signals:
    void BoardRotationChanged(quint32 index, float value);
    void BoardRotation_RollChanged(float value);
    void BoardRotation_PitchChanged(float value);
    void BoardRotation_YawChanged(float value);
    void BoardLevelTrimChanged(quint32 index, float value);
    void BoardLevelTrim_RollChanged(float value);
    void BoardLevelTrim_PitchChanged(float value);
    void AccelKpChanged(float value);
    void AccelKiChanged(float value);
    void MagKiChanged(float value);
    void MagKpChanged(float value);
    void AccelTauChanged(float value);
    void YawBiasRateChanged(float value);
    void ZeroDuringArmingChanged(quint8 value);
    void BiasCorrectGyroChanged(quint8 value);
    void TrimFlightChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // ATTITUDESETTINGS_H
