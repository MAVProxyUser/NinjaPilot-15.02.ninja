/**
 ******************************************************************************
 *
 * @file       mpu6000settings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: mpu6000settings.xml. 
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
#ifndef MPU6000SETTINGS_H
#define MPU6000SETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT Mpu6000Settings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 GyroScale READ getGyroScale WRITE setGyroScale NOTIFY GyroScaleChanged);
    Q_PROPERTY(quint8 AccelScale READ getAccelScale WRITE setAccelScale NOTIFY AccelScaleChanged);
    Q_PROPERTY(quint8 FilterSetting READ getFilterSetting WRITE setFilterSetting NOTIFY FilterSettingChanged);


public:
    // Field structure
    typedef struct {
        quint8 GyroScale;
        quint8 AccelScale;
        quint8 FilterSetting;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field GyroScale information
    /* Enumeration options for field GyroScale */
    typedef enum { GYROSCALE_SCALE_250=0, GYROSCALE_SCALE_500=1, GYROSCALE_SCALE_1000=2, GYROSCALE_SCALE_2000=3 } GyroScaleOptions;
    // Field AccelScale information
    /* Enumeration options for field AccelScale */
    typedef enum { ACCELSCALE_SCALE_2G=0, ACCELSCALE_SCALE_4G=1, ACCELSCALE_SCALE_8G=2, ACCELSCALE_SCALE_16G=3 } AccelScaleOptions;
    // Field FilterSetting information
    /* Enumeration options for field FilterSetting */
    typedef enum { FILTERSETTING_LOWPASS_256_HZ=0, FILTERSETTING_LOWPASS_188_HZ=1, FILTERSETTING_LOWPASS_98_HZ=2, FILTERSETTING_LOWPASS_42_HZ=3, FILTERSETTING_LOWPASS_20_HZ=4, FILTERSETTING_LOWPASS_10_HZ=5, FILTERSETTING_LOWPASS_5_HZ=6 } FilterSettingOptions;

  
    // Constants
    static const quint32 OBJID = 0xA909AE7C;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    Mpu6000Settings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static Mpu6000Settings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint8 getGyroScale() const;
    Q_INVOKABLE quint8 getAccelScale() const;
    Q_INVOKABLE quint8 getFilterSetting() const;


public slots:
    void setGyroScale(quint8 value);
    void setAccelScale(quint8 value);
    void setFilterSetting(quint8 value);


signals:
    void GyroScaleChanged(quint8 value);
    void AccelScaleChanged(quint8 value);
    void FilterSettingChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // MPU6000SETTINGS_H
