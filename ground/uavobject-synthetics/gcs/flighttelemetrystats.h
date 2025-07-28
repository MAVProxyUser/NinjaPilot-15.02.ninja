/**
 ******************************************************************************
 *
 * @file       flighttelemetrystats.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: flighttelemetrystats.xml. 
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
#ifndef FLIGHTTELEMETRYSTATS_H
#define FLIGHTTELEMETRYSTATS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT FlightTelemetryStats: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float TxDataRate READ getTxDataRate WRITE setTxDataRate NOTIFY TxDataRateChanged);
    Q_PROPERTY(quint32 TxBytes READ getTxBytes WRITE setTxBytes NOTIFY TxBytesChanged);
    Q_PROPERTY(quint32 TxFailures READ getTxFailures WRITE setTxFailures NOTIFY TxFailuresChanged);
    Q_PROPERTY(quint32 TxRetries READ getTxRetries WRITE setTxRetries NOTIFY TxRetriesChanged);
    Q_PROPERTY(float RxDataRate READ getRxDataRate WRITE setRxDataRate NOTIFY RxDataRateChanged);
    Q_PROPERTY(quint32 RxBytes READ getRxBytes WRITE setRxBytes NOTIFY RxBytesChanged);
    Q_PROPERTY(quint32 RxFailures READ getRxFailures WRITE setRxFailures NOTIFY RxFailuresChanged);
    Q_PROPERTY(quint32 RxSyncErrors READ getRxSyncErrors WRITE setRxSyncErrors NOTIFY RxSyncErrorsChanged);
    Q_PROPERTY(quint32 RxCrcErrors READ getRxCrcErrors WRITE setRxCrcErrors NOTIFY RxCrcErrorsChanged);
    Q_PROPERTY(quint8 Status READ getStatus WRITE setStatus NOTIFY StatusChanged);


public:
    // Field structure
    typedef struct {
        float TxDataRate;
        quint32 TxBytes;
        quint32 TxFailures;
        quint32 TxRetries;
        float RxDataRate;
        quint32 RxBytes;
        quint32 RxFailures;
        quint32 RxSyncErrors;
        quint32 RxCrcErrors;
        quint8 Status;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field TxDataRate information
    // Field TxBytes information
    // Field TxFailures information
    // Field TxRetries information
    // Field RxDataRate information
    // Field RxBytes information
    // Field RxFailures information
    // Field RxSyncErrors information
    // Field RxCrcErrors information
    // Field Status information
    /* Enumeration options for field Status */
    typedef enum { STATUS_DISCONNECTED=0, STATUS_HANDSHAKEREQ=1, STATUS_HANDSHAKEACK=2, STATUS_CONNECTED=3 } StatusOptions;

  
    // Constants
    static const quint32 OBJID = 0x6737BB5A;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    FlightTelemetryStats();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static FlightTelemetryStats* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getTxDataRate() const;
    Q_INVOKABLE quint32 getTxBytes() const;
    Q_INVOKABLE quint32 getTxFailures() const;
    Q_INVOKABLE quint32 getTxRetries() const;
    Q_INVOKABLE float getRxDataRate() const;
    Q_INVOKABLE quint32 getRxBytes() const;
    Q_INVOKABLE quint32 getRxFailures() const;
    Q_INVOKABLE quint32 getRxSyncErrors() const;
    Q_INVOKABLE quint32 getRxCrcErrors() const;
    Q_INVOKABLE quint8 getStatus() const;


public slots:
    void setTxDataRate(float value);
    void setTxBytes(quint32 value);
    void setTxFailures(quint32 value);
    void setTxRetries(quint32 value);
    void setRxDataRate(float value);
    void setRxBytes(quint32 value);
    void setRxFailures(quint32 value);
    void setRxSyncErrors(quint32 value);
    void setRxCrcErrors(quint32 value);
    void setStatus(quint8 value);


signals:
    void TxDataRateChanged(float value);
    void TxBytesChanged(quint32 value);
    void TxFailuresChanged(quint32 value);
    void TxRetriesChanged(quint32 value);
    void RxDataRateChanged(float value);
    void RxBytesChanged(quint32 value);
    void RxFailuresChanged(quint32 value);
    void RxSyncErrorsChanged(quint32 value);
    void RxCrcErrorsChanged(quint32 value);
    void StatusChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // FLIGHTTELEMETRYSTATS_H
