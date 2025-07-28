/**
 ******************************************************************************
 *
 * @file       gpssettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: gpssettings.xml. 
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
#ifndef GPSSETTINGS_H
#define GPSSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT GPSSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float MaxPDOP READ getMaxPDOP WRITE setMaxPDOP NOTIFY MaxPDOPChanged);
    Q_PROPERTY(quint8 DataProtocol READ getDataProtocol WRITE setDataProtocol NOTIFY DataProtocolChanged);
    Q_PROPERTY(quint8 MinSatellites READ getMinSatellites WRITE setMinSatellites NOTIFY MinSatellitesChanged);
    Q_PROPERTY(quint8 UbxAutoConfig READ getUbxAutoConfig WRITE setUbxAutoConfig NOTIFY UbxAutoConfigChanged);
    Q_PROPERTY(qint8 UbxRate READ getUbxRate WRITE setUbxRate NOTIFY UbxRateChanged);
    Q_PROPERTY(quint8 UbxDynamicModel READ getUbxDynamicModel WRITE setUbxDynamicModel NOTIFY UbxDynamicModelChanged);
    Q_PROPERTY(quint8 UbxSBASMode READ getUbxSBASMode WRITE setUbxSBASMode NOTIFY UbxSBASModeChanged);
    Q_PROPERTY(quint8 UbxSBASChannelsUsed READ getUbxSBASChannelsUsed WRITE setUbxSBASChannelsUsed NOTIFY UbxSBASChannelsUsedChanged);
    Q_PROPERTY(quint8 UbxSBASSats READ getUbxSBASSats WRITE setUbxSBASSats NOTIFY UbxSBASSatsChanged);
    Q_PROPERTY(quint8 UbxGNSSMode READ getUbxGNSSMode WRITE setUbxGNSSMode NOTIFY UbxGNSSModeChanged);


public:
    // Field structure
    typedef struct {
        float MaxPDOP;
        quint8 DataProtocol;
        quint8 MinSatellites;
        quint8 UbxAutoConfig;
        qint8 UbxRate;
        quint8 UbxDynamicModel;
        quint8 UbxSBASMode;
        quint8 UbxSBASChannelsUsed;
        quint8 UbxSBASSats;
        quint8 UbxGNSSMode;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field MaxPDOP information
    // Field DataProtocol information
    /* Enumeration options for field DataProtocol */
    typedef enum { DATAPROTOCOL_NMEA=0, DATAPROTOCOL_UBX=1 } DataProtocolOptions;
    // Field MinSatellites information
    // Field UbxAutoConfig information
    /* Enumeration options for field UbxAutoConfig */
    typedef enum { UBXAUTOCONFIG_DISABLED=0, UBXAUTOCONFIG_CONFIGURE=1, UBXAUTOCONFIG_CONFIGUREANDSTORE=2 } UbxAutoConfigOptions;
    // Field UbxRate information
    // Field UbxDynamicModel information
    /* Enumeration options for field UbxDynamicModel */
    typedef enum { UBXDYNAMICMODEL_PORTABLE=0, UBXDYNAMICMODEL_STATIONARY=1, UBXDYNAMICMODEL_PEDESTRIAN=2, UBXDYNAMICMODEL_AUTOMOTIVE=3, UBXDYNAMICMODEL_SEA=4, UBXDYNAMICMODEL_AIRBORNE1G=5, UBXDYNAMICMODEL_AIRBORNE2G=6, UBXDYNAMICMODEL_AIRBORNE4G=7 } UbxDynamicModelOptions;
    // Field UbxSBASMode information
    /* Enumeration options for field UbxSBASMode */
    typedef enum { UBXSBASMODE_DISABLED=0, UBXSBASMODE_RANGING=1, UBXSBASMODE_CORRECTION=2, UBXSBASMODE_INTEGRITY=3, UBXSBASMODE_RANGINGCORRECTION=4, UBXSBASMODE_RANGINGINTEGRITY=5, UBXSBASMODE_RANGINGCORRECTIONINTEGRITY=6, UBXSBASMODE_CORRECTIONINTEGRITY=7 } UbxSBASModeOptions;
    // Field UbxSBASChannelsUsed information
    // Field UbxSBASSats information
    /* Enumeration options for field UbxSBASSats */
    typedef enum { UBXSBASSATS_AUTOSCAN=0, UBXSBASSATS_WAAS=1, UBXSBASSATS_EGNOS=2, UBXSBASSATS_MSAS=3, UBXSBASSATS_GAGAN=4, UBXSBASSATS_SDCM=5 } UbxSBASSatsOptions;
    // Field UbxGNSSMode information
    /* Enumeration options for field UbxGNSSMode */
    typedef enum { UBXGNSSMODE_DEFAULT=0, UBXGNSSMODE_GPS=1, UBXGNSSMODE_GLONASS=2, UBXGNSSMODE_GPSGLONASS=3, UBXGNSSMODE_GPSBEIDOU=4, UBXGNSSMODE_GLONASSBEIDOU=5 } UbxGNSSModeOptions;

  
    // Constants
    static const quint32 OBJID = 0x70C7BC8E;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    GPSSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static GPSSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getMaxPDOP() const;
    Q_INVOKABLE quint8 getDataProtocol() const;
    Q_INVOKABLE quint8 getMinSatellites() const;
    Q_INVOKABLE quint8 getUbxAutoConfig() const;
    Q_INVOKABLE qint8 getUbxRate() const;
    Q_INVOKABLE quint8 getUbxDynamicModel() const;
    Q_INVOKABLE quint8 getUbxSBASMode() const;
    Q_INVOKABLE quint8 getUbxSBASChannelsUsed() const;
    Q_INVOKABLE quint8 getUbxSBASSats() const;
    Q_INVOKABLE quint8 getUbxGNSSMode() const;


public slots:
    void setMaxPDOP(float value);
    void setDataProtocol(quint8 value);
    void setMinSatellites(quint8 value);
    void setUbxAutoConfig(quint8 value);
    void setUbxRate(qint8 value);
    void setUbxDynamicModel(quint8 value);
    void setUbxSBASMode(quint8 value);
    void setUbxSBASChannelsUsed(quint8 value);
    void setUbxSBASSats(quint8 value);
    void setUbxGNSSMode(quint8 value);


signals:
    void MaxPDOPChanged(float value);
    void DataProtocolChanged(quint8 value);
    void MinSatellitesChanged(quint8 value);
    void UbxAutoConfigChanged(quint8 value);
    void UbxRateChanged(qint8 value);
    void UbxDynamicModelChanged(quint8 value);
    void UbxSBASModeChanged(quint8 value);
    void UbxSBASChannelsUsedChanged(quint8 value);
    void UbxSBASSatsChanged(quint8 value);
    void UbxGNSSModeChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // GPSSETTINGS_H
