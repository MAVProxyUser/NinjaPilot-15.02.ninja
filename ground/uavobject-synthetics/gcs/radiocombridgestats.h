/**
 ******************************************************************************
 *
 * @file       radiocombridgestats.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: radiocombridgestats.xml. 
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
#ifndef RADIOCOMBRIDGESTATS_H
#define RADIOCOMBRIDGESTATS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT RadioComBridgeStats: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 TelemetryTxBytes READ getTelemetryTxBytes WRITE setTelemetryTxBytes NOTIFY TelemetryTxBytesChanged);
    Q_PROPERTY(quint32 TelemetryTxFailures READ getTelemetryTxFailures WRITE setTelemetryTxFailures NOTIFY TelemetryTxFailuresChanged);
    Q_PROPERTY(quint32 TelemetryTxRetries READ getTelemetryTxRetries WRITE setTelemetryTxRetries NOTIFY TelemetryTxRetriesChanged);
    Q_PROPERTY(quint32 TelemetryRxBytes READ getTelemetryRxBytes WRITE setTelemetryRxBytes NOTIFY TelemetryRxBytesChanged);
    Q_PROPERTY(quint32 TelemetryRxFailures READ getTelemetryRxFailures WRITE setTelemetryRxFailures NOTIFY TelemetryRxFailuresChanged);
    Q_PROPERTY(quint32 TelemetryRxSyncErrors READ getTelemetryRxSyncErrors WRITE setTelemetryRxSyncErrors NOTIFY TelemetryRxSyncErrorsChanged);
    Q_PROPERTY(quint32 TelemetryRxCrcErrors READ getTelemetryRxCrcErrors WRITE setTelemetryRxCrcErrors NOTIFY TelemetryRxCrcErrorsChanged);
    Q_PROPERTY(quint32 RadioTxBytes READ getRadioTxBytes WRITE setRadioTxBytes NOTIFY RadioTxBytesChanged);
    Q_PROPERTY(quint32 RadioTxFailures READ getRadioTxFailures WRITE setRadioTxFailures NOTIFY RadioTxFailuresChanged);
    Q_PROPERTY(quint32 RadioTxRetries READ getRadioTxRetries WRITE setRadioTxRetries NOTIFY RadioTxRetriesChanged);
    Q_PROPERTY(quint32 RadioRxBytes READ getRadioRxBytes WRITE setRadioRxBytes NOTIFY RadioRxBytesChanged);
    Q_PROPERTY(quint32 RadioRxFailures READ getRadioRxFailures WRITE setRadioRxFailures NOTIFY RadioRxFailuresChanged);
    Q_PROPERTY(quint32 RadioRxSyncErrors READ getRadioRxSyncErrors WRITE setRadioRxSyncErrors NOTIFY RadioRxSyncErrorsChanged);
    Q_PROPERTY(quint32 RadioRxCrcErrors READ getRadioRxCrcErrors WRITE setRadioRxCrcErrors NOTIFY RadioRxCrcErrorsChanged);


public:
    // Field structure
    typedef struct {
        quint32 TelemetryTxBytes;
        quint32 TelemetryTxFailures;
        quint32 TelemetryTxRetries;
        quint32 TelemetryRxBytes;
        quint32 TelemetryRxFailures;
        quint32 TelemetryRxSyncErrors;
        quint32 TelemetryRxCrcErrors;
        quint32 RadioTxBytes;
        quint32 RadioTxFailures;
        quint32 RadioTxRetries;
        quint32 RadioRxBytes;
        quint32 RadioRxFailures;
        quint32 RadioRxSyncErrors;
        quint32 RadioRxCrcErrors;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field TelemetryTxBytes information
    // Field TelemetryTxFailures information
    // Field TelemetryTxRetries information
    // Field TelemetryRxBytes information
    // Field TelemetryRxFailures information
    // Field TelemetryRxSyncErrors information
    // Field TelemetryRxCrcErrors information
    // Field RadioTxBytes information
    // Field RadioTxFailures information
    // Field RadioTxRetries information
    // Field RadioRxBytes information
    // Field RadioRxFailures information
    // Field RadioRxSyncErrors information
    // Field RadioRxCrcErrors information

  
    // Constants
    static const quint32 OBJID = 0x2499AE58;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    RadioComBridgeStats();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static RadioComBridgeStats* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint32 getTelemetryTxBytes() const;
    Q_INVOKABLE quint32 getTelemetryTxFailures() const;
    Q_INVOKABLE quint32 getTelemetryTxRetries() const;
    Q_INVOKABLE quint32 getTelemetryRxBytes() const;
    Q_INVOKABLE quint32 getTelemetryRxFailures() const;
    Q_INVOKABLE quint32 getTelemetryRxSyncErrors() const;
    Q_INVOKABLE quint32 getTelemetryRxCrcErrors() const;
    Q_INVOKABLE quint32 getRadioTxBytes() const;
    Q_INVOKABLE quint32 getRadioTxFailures() const;
    Q_INVOKABLE quint32 getRadioTxRetries() const;
    Q_INVOKABLE quint32 getRadioRxBytes() const;
    Q_INVOKABLE quint32 getRadioRxFailures() const;
    Q_INVOKABLE quint32 getRadioRxSyncErrors() const;
    Q_INVOKABLE quint32 getRadioRxCrcErrors() const;


public slots:
    void setTelemetryTxBytes(quint32 value);
    void setTelemetryTxFailures(quint32 value);
    void setTelemetryTxRetries(quint32 value);
    void setTelemetryRxBytes(quint32 value);
    void setTelemetryRxFailures(quint32 value);
    void setTelemetryRxSyncErrors(quint32 value);
    void setTelemetryRxCrcErrors(quint32 value);
    void setRadioTxBytes(quint32 value);
    void setRadioTxFailures(quint32 value);
    void setRadioTxRetries(quint32 value);
    void setRadioRxBytes(quint32 value);
    void setRadioRxFailures(quint32 value);
    void setRadioRxSyncErrors(quint32 value);
    void setRadioRxCrcErrors(quint32 value);


signals:
    void TelemetryTxBytesChanged(quint32 value);
    void TelemetryTxFailuresChanged(quint32 value);
    void TelemetryTxRetriesChanged(quint32 value);
    void TelemetryRxBytesChanged(quint32 value);
    void TelemetryRxFailuresChanged(quint32 value);
    void TelemetryRxSyncErrorsChanged(quint32 value);
    void TelemetryRxCrcErrorsChanged(quint32 value);
    void RadioTxBytesChanged(quint32 value);
    void RadioTxFailuresChanged(quint32 value);
    void RadioTxRetriesChanged(quint32 value);
    void RadioRxBytesChanged(quint32 value);
    void RadioRxFailuresChanged(quint32 value);
    void RadioRxSyncErrorsChanged(quint32 value);
    void RadioRxCrcErrorsChanged(quint32 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // RADIOCOMBRIDGESTATS_H
