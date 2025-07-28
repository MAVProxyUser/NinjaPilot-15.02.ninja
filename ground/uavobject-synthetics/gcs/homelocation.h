/**
 ******************************************************************************
 *
 * @file       homelocation.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: homelocation.xml. 
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
#ifndef HOMELOCATION_H
#define HOMELOCATION_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT HomeLocation: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 Latitude READ getLatitude WRITE setLatitude NOTIFY LatitudeChanged);
    Q_PROPERTY(qint32 Longitude READ getLongitude WRITE setLongitude NOTIFY LongitudeChanged);
    Q_PROPERTY(float Altitude READ getAltitude WRITE setAltitude NOTIFY AltitudeChanged);
    Q_PROPERTY(float Be_0 READ getBe_0 WRITE setBe_0 NOTIFY Be_0Changed);
    Q_PROPERTY(float Be_1 READ getBe_1 WRITE setBe_1 NOTIFY Be_1Changed);
    Q_PROPERTY(float Be_2 READ getBe_2 WRITE setBe_2 NOTIFY Be_2Changed);
    Q_PROPERTY(float g_e READ getg_e WRITE setg_e NOTIFY g_eChanged);
    Q_PROPERTY(quint8 Set READ getSet WRITE setSet NOTIFY SetChanged);


public:
    // Field structure
    typedef struct {
        qint32 Latitude;
        qint32 Longitude;
        float Altitude;
        float Be[3];
        float g_e;
        quint8 Set;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Latitude information
    // Field Longitude information
    // Field Altitude information
    // Field Be information
    /* Number of elements for field Be */
    static const quint32 BE_NUMELEM = 3;
    // Field g_e information
    // Field Set information
    /* Enumeration options for field Set */
    typedef enum { SET_FALSE=0, SET_TRUE=1 } SetOptions;

  
    // Constants
    static const quint32 OBJID = 0x6185DC6E;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    HomeLocation();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static HomeLocation* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE qint32 getLatitude() const;
    Q_INVOKABLE qint32 getLongitude() const;
    Q_INVOKABLE float getAltitude() const;
    Q_INVOKABLE float getBe(quint32 index) const;
    Q_INVOKABLE float getBe_0() const;
    Q_INVOKABLE float getBe_1() const;
    Q_INVOKABLE float getBe_2() const;
    Q_INVOKABLE float getg_e() const;
    Q_INVOKABLE quint8 getSet() const;


public slots:
    void setLatitude(qint32 value);
    void setLongitude(qint32 value);
    void setAltitude(float value);
    void setBe(quint32 index, float value);
    void setBe_0(float value);
    void setBe_1(float value);
    void setBe_2(float value);
    void setg_e(float value);
    void setSet(quint8 value);


signals:
    void LatitudeChanged(qint32 value);
    void LongitudeChanged(qint32 value);
    void AltitudeChanged(float value);
    void BeChanged(quint32 index, float value);
    void Be_0Changed(float value);
    void Be_1Changed(float value);
    void Be_2Changed(float value);
    void g_eChanged(float value);
    void SetChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // HOMELOCATION_H
