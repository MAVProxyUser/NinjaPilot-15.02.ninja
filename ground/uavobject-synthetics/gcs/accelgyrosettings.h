/**
 ******************************************************************************
 *
 * @file       accelgyrosettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: accelgyrosettings.xml. 
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
#ifndef ACCELGYROSETTINGS_H
#define ACCELGYROSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT AccelGyroSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float accel_bias_X READ getaccel_bias_X WRITE setaccel_bias_X NOTIFY accel_bias_XChanged);
    Q_PROPERTY(float accel_bias_Y READ getaccel_bias_Y WRITE setaccel_bias_Y NOTIFY accel_bias_YChanged);
    Q_PROPERTY(float accel_bias_Z READ getaccel_bias_Z WRITE setaccel_bias_Z NOTIFY accel_bias_ZChanged);
    Q_PROPERTY(float accel_scale_X READ getaccel_scale_X WRITE setaccel_scale_X NOTIFY accel_scale_XChanged);
    Q_PROPERTY(float accel_scale_Y READ getaccel_scale_Y WRITE setaccel_scale_Y NOTIFY accel_scale_YChanged);
    Q_PROPERTY(float accel_scale_Z READ getaccel_scale_Z WRITE setaccel_scale_Z NOTIFY accel_scale_ZChanged);
    Q_PROPERTY(float accel_temp_coeff_X READ getaccel_temp_coeff_X WRITE setaccel_temp_coeff_X NOTIFY accel_temp_coeff_XChanged);
    Q_PROPERTY(float accel_temp_coeff_Y READ getaccel_temp_coeff_Y WRITE setaccel_temp_coeff_Y NOTIFY accel_temp_coeff_YChanged);
    Q_PROPERTY(float accel_temp_coeff_Z READ getaccel_temp_coeff_Z WRITE setaccel_temp_coeff_Z NOTIFY accel_temp_coeff_ZChanged);
    Q_PROPERTY(float gyro_bias_X READ getgyro_bias_X WRITE setgyro_bias_X NOTIFY gyro_bias_XChanged);
    Q_PROPERTY(float gyro_bias_Y READ getgyro_bias_Y WRITE setgyro_bias_Y NOTIFY gyro_bias_YChanged);
    Q_PROPERTY(float gyro_bias_Z READ getgyro_bias_Z WRITE setgyro_bias_Z NOTIFY gyro_bias_ZChanged);
    Q_PROPERTY(float gyro_scale_X READ getgyro_scale_X WRITE setgyro_scale_X NOTIFY gyro_scale_XChanged);
    Q_PROPERTY(float gyro_scale_Y READ getgyro_scale_Y WRITE setgyro_scale_Y NOTIFY gyro_scale_YChanged);
    Q_PROPERTY(float gyro_scale_Z READ getgyro_scale_Z WRITE setgyro_scale_Z NOTIFY gyro_scale_ZChanged);
    Q_PROPERTY(float gyro_temp_coeff_X READ getgyro_temp_coeff_X WRITE setgyro_temp_coeff_X NOTIFY gyro_temp_coeff_XChanged);
    Q_PROPERTY(float gyro_temp_coeff_X2 READ getgyro_temp_coeff_X2 WRITE setgyro_temp_coeff_X2 NOTIFY gyro_temp_coeff_X2Changed);
    Q_PROPERTY(float gyro_temp_coeff_Y READ getgyro_temp_coeff_Y WRITE setgyro_temp_coeff_Y NOTIFY gyro_temp_coeff_YChanged);
    Q_PROPERTY(float gyro_temp_coeff_Y2 READ getgyro_temp_coeff_Y2 WRITE setgyro_temp_coeff_Y2 NOTIFY gyro_temp_coeff_Y2Changed);
    Q_PROPERTY(float gyro_temp_coeff_Z READ getgyro_temp_coeff_Z WRITE setgyro_temp_coeff_Z NOTIFY gyro_temp_coeff_ZChanged);
    Q_PROPERTY(float gyro_temp_coeff_Z2 READ getgyro_temp_coeff_Z2 WRITE setgyro_temp_coeff_Z2 NOTIFY gyro_temp_coeff_Z2Changed);
    Q_PROPERTY(float temp_calibrated_extent_min READ gettemp_calibrated_extent_min WRITE settemp_calibrated_extent_min NOTIFY temp_calibrated_extent_minChanged);
    Q_PROPERTY(float temp_calibrated_extent_max READ gettemp_calibrated_extent_max WRITE settemp_calibrated_extent_max NOTIFY temp_calibrated_extent_maxChanged);


public:
    // Field structure
    typedef struct {
        float accel_bias[3];
        float accel_scale[3];
        float accel_temp_coeff[3];
        float gyro_bias[3];
        float gyro_scale[3];
        float gyro_temp_coeff[6];
        float temp_calibrated_extent[2];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field accel_bias information
    /* Array element names for field accel_bias */
    typedef enum { ACCEL_BIAS_X=0, ACCEL_BIAS_Y=1, ACCEL_BIAS_Z=2 } accel_biasElem;
    /* Number of elements for field accel_bias */
    static const quint32 ACCEL_BIAS_NUMELEM = 3;
    // Field accel_scale information
    /* Array element names for field accel_scale */
    typedef enum { ACCEL_SCALE_X=0, ACCEL_SCALE_Y=1, ACCEL_SCALE_Z=2 } accel_scaleElem;
    /* Number of elements for field accel_scale */
    static const quint32 ACCEL_SCALE_NUMELEM = 3;
    // Field accel_temp_coeff information
    /* Array element names for field accel_temp_coeff */
    typedef enum { ACCEL_TEMP_COEFF_X=0, ACCEL_TEMP_COEFF_Y=1, ACCEL_TEMP_COEFF_Z=2 } accel_temp_coeffElem;
    /* Number of elements for field accel_temp_coeff */
    static const quint32 ACCEL_TEMP_COEFF_NUMELEM = 3;
    // Field gyro_bias information
    /* Array element names for field gyro_bias */
    typedef enum { GYRO_BIAS_X=0, GYRO_BIAS_Y=1, GYRO_BIAS_Z=2 } gyro_biasElem;
    /* Number of elements for field gyro_bias */
    static const quint32 GYRO_BIAS_NUMELEM = 3;
    // Field gyro_scale information
    /* Array element names for field gyro_scale */
    typedef enum { GYRO_SCALE_X=0, GYRO_SCALE_Y=1, GYRO_SCALE_Z=2 } gyro_scaleElem;
    /* Number of elements for field gyro_scale */
    static const quint32 GYRO_SCALE_NUMELEM = 3;
    // Field gyro_temp_coeff information
    /* Array element names for field gyro_temp_coeff */
    typedef enum { GYRO_TEMP_COEFF_X=0, GYRO_TEMP_COEFF_X2=1, GYRO_TEMP_COEFF_Y=2, GYRO_TEMP_COEFF_Y2=3, GYRO_TEMP_COEFF_Z=4, GYRO_TEMP_COEFF_Z2=5 } gyro_temp_coeffElem;
    /* Number of elements for field gyro_temp_coeff */
    static const quint32 GYRO_TEMP_COEFF_NUMELEM = 6;
    // Field temp_calibrated_extent information
    /* Array element names for field temp_calibrated_extent */
    typedef enum { TEMP_CALIBRATED_EXTENT_MIN=0, TEMP_CALIBRATED_EXTENT_MAX=1 } temp_calibrated_extentElem;
    /* Number of elements for field temp_calibrated_extent */
    static const quint32 TEMP_CALIBRATED_EXTENT_NUMELEM = 2;

  
    // Constants
    static const quint32 OBJID = 0x1262B2D0;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    AccelGyroSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static AccelGyroSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getaccel_bias(quint32 index) const;
    Q_INVOKABLE float getaccel_bias_X() const;
    Q_INVOKABLE float getaccel_bias_Y() const;
    Q_INVOKABLE float getaccel_bias_Z() const;
    Q_INVOKABLE float getaccel_scale(quint32 index) const;
    Q_INVOKABLE float getaccel_scale_X() const;
    Q_INVOKABLE float getaccel_scale_Y() const;
    Q_INVOKABLE float getaccel_scale_Z() const;
    Q_INVOKABLE float getaccel_temp_coeff(quint32 index) const;
    Q_INVOKABLE float getaccel_temp_coeff_X() const;
    Q_INVOKABLE float getaccel_temp_coeff_Y() const;
    Q_INVOKABLE float getaccel_temp_coeff_Z() const;
    Q_INVOKABLE float getgyro_bias(quint32 index) const;
    Q_INVOKABLE float getgyro_bias_X() const;
    Q_INVOKABLE float getgyro_bias_Y() const;
    Q_INVOKABLE float getgyro_bias_Z() const;
    Q_INVOKABLE float getgyro_scale(quint32 index) const;
    Q_INVOKABLE float getgyro_scale_X() const;
    Q_INVOKABLE float getgyro_scale_Y() const;
    Q_INVOKABLE float getgyro_scale_Z() const;
    Q_INVOKABLE float getgyro_temp_coeff(quint32 index) const;
    Q_INVOKABLE float getgyro_temp_coeff_X() const;
    Q_INVOKABLE float getgyro_temp_coeff_X2() const;
    Q_INVOKABLE float getgyro_temp_coeff_Y() const;
    Q_INVOKABLE float getgyro_temp_coeff_Y2() const;
    Q_INVOKABLE float getgyro_temp_coeff_Z() const;
    Q_INVOKABLE float getgyro_temp_coeff_Z2() const;
    Q_INVOKABLE float gettemp_calibrated_extent(quint32 index) const;
    Q_INVOKABLE float gettemp_calibrated_extent_min() const;
    Q_INVOKABLE float gettemp_calibrated_extent_max() const;


public slots:
    void setaccel_bias(quint32 index, float value);
    void setaccel_bias_X(float value);
    void setaccel_bias_Y(float value);
    void setaccel_bias_Z(float value);
    void setaccel_scale(quint32 index, float value);
    void setaccel_scale_X(float value);
    void setaccel_scale_Y(float value);
    void setaccel_scale_Z(float value);
    void setaccel_temp_coeff(quint32 index, float value);
    void setaccel_temp_coeff_X(float value);
    void setaccel_temp_coeff_Y(float value);
    void setaccel_temp_coeff_Z(float value);
    void setgyro_bias(quint32 index, float value);
    void setgyro_bias_X(float value);
    void setgyro_bias_Y(float value);
    void setgyro_bias_Z(float value);
    void setgyro_scale(quint32 index, float value);
    void setgyro_scale_X(float value);
    void setgyro_scale_Y(float value);
    void setgyro_scale_Z(float value);
    void setgyro_temp_coeff(quint32 index, float value);
    void setgyro_temp_coeff_X(float value);
    void setgyro_temp_coeff_X2(float value);
    void setgyro_temp_coeff_Y(float value);
    void setgyro_temp_coeff_Y2(float value);
    void setgyro_temp_coeff_Z(float value);
    void setgyro_temp_coeff_Z2(float value);
    void settemp_calibrated_extent(quint32 index, float value);
    void settemp_calibrated_extent_min(float value);
    void settemp_calibrated_extent_max(float value);


signals:
    void accel_biasChanged(quint32 index, float value);
    void accel_bias_XChanged(float value);
    void accel_bias_YChanged(float value);
    void accel_bias_ZChanged(float value);
    void accel_scaleChanged(quint32 index, float value);
    void accel_scale_XChanged(float value);
    void accel_scale_YChanged(float value);
    void accel_scale_ZChanged(float value);
    void accel_temp_coeffChanged(quint32 index, float value);
    void accel_temp_coeff_XChanged(float value);
    void accel_temp_coeff_YChanged(float value);
    void accel_temp_coeff_ZChanged(float value);
    void gyro_biasChanged(quint32 index, float value);
    void gyro_bias_XChanged(float value);
    void gyro_bias_YChanged(float value);
    void gyro_bias_ZChanged(float value);
    void gyro_scaleChanged(quint32 index, float value);
    void gyro_scale_XChanged(float value);
    void gyro_scale_YChanged(float value);
    void gyro_scale_ZChanged(float value);
    void gyro_temp_coeffChanged(quint32 index, float value);
    void gyro_temp_coeff_XChanged(float value);
    void gyro_temp_coeff_X2Changed(float value);
    void gyro_temp_coeff_YChanged(float value);
    void gyro_temp_coeff_Y2Changed(float value);
    void gyro_temp_coeff_ZChanged(float value);
    void gyro_temp_coeff_Z2Changed(float value);
    void temp_calibrated_extentChanged(quint32 index, float value);
    void temp_calibrated_extent_minChanged(float value);
    void temp_calibrated_extent_maxChanged(float value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // ACCELGYROSETTINGS_H
