/**
 ******************************************************************************
 *
 * @file       altitudefiltersettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: altitudefiltersettings.xml. 
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
#ifndef ALTITUDEFILTERSETTINGS_H
#define ALTITUDEFILTERSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT AltitudeFilterSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float AccelLowPassKp READ getAccelLowPassKp WRITE setAccelLowPassKp NOTIFY AccelLowPassKpChanged);
    Q_PROPERTY(float AccelDriftKi READ getAccelDriftKi WRITE setAccelDriftKi NOTIFY AccelDriftKiChanged);
    Q_PROPERTY(float InitializationAccelDriftKi READ getInitializationAccelDriftKi WRITE setInitializationAccelDriftKi NOTIFY InitializationAccelDriftKiChanged);
    Q_PROPERTY(float BaroKp READ getBaroKp WRITE setBaroKp NOTIFY BaroKpChanged);


public:
    // Field structure
    typedef struct {
        float AccelLowPassKp;
        float AccelDriftKi;
        float InitializationAccelDriftKi;
        float BaroKp;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field AccelLowPassKp information
    // Field AccelDriftKi information
    // Field InitializationAccelDriftKi information
    // Field BaroKp information

  
    // Constants
    static const quint32 OBJID = 0xE611042C;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    AltitudeFilterSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static AltitudeFilterSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getAccelLowPassKp() const;
    Q_INVOKABLE float getAccelDriftKi() const;
    Q_INVOKABLE float getInitializationAccelDriftKi() const;
    Q_INVOKABLE float getBaroKp() const;


public slots:
    void setAccelLowPassKp(float value);
    void setAccelDriftKi(float value);
    void setInitializationAccelDriftKi(float value);
    void setBaroKp(float value);


signals:
    void AccelLowPassKpChanged(float value);
    void AccelDriftKiChanged(float value);
    void InitializationAccelDriftKiChanged(float value);
    void BaroKpChanged(float value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // ALTITUDEFILTERSETTINGS_H
