/**
 ******************************************************************************
 *
 * @file       oplinkstatus.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: oplinkstatus.xml. 
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
#ifndef OPLINKSTATUS_H
#define OPLINKSTATUS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT OPLinkStatus: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 DeviceID READ getDeviceID WRITE setDeviceID NOTIFY DeviceIDChanged);
    Q_PROPERTY(quint32 PairIDs_0 READ getPairIDs_0 WRITE setPairIDs_0 NOTIFY PairIDs_0Changed);
    Q_PROPERTY(quint32 PairIDs_1 READ getPairIDs_1 WRITE setPairIDs_1 NOTIFY PairIDs_1Changed);
    Q_PROPERTY(quint32 PairIDs_2 READ getPairIDs_2 WRITE setPairIDs_2 NOTIFY PairIDs_2Changed);
    Q_PROPERTY(quint32 PairIDs_3 READ getPairIDs_3 WRITE setPairIDs_3 NOTIFY PairIDs_3Changed);
    Q_PROPERTY(quint16 BoardRevision READ getBoardRevision WRITE setBoardRevision NOTIFY BoardRevisionChanged);
    Q_PROPERTY(quint16 HeapRemaining READ getHeapRemaining WRITE setHeapRemaining NOTIFY HeapRemainingChanged);
    Q_PROPERTY(quint16 UAVTalkErrors READ getUAVTalkErrors WRITE setUAVTalkErrors NOTIFY UAVTalkErrorsChanged);
    Q_PROPERTY(quint16 TXRate READ getTXRate WRITE setTXRate NOTIFY TXRateChanged);
    Q_PROPERTY(quint16 RXRate READ getRXRate WRITE setRXRate NOTIFY RXRateChanged);
    Q_PROPERTY(quint16 TXSeq READ getTXSeq WRITE setTXSeq NOTIFY TXSeqChanged);
    Q_PROPERTY(quint16 RXSeq READ getRXSeq WRITE setRXSeq NOTIFY RXSeqChanged);
    Q_PROPERTY(quint8 CPUSerial_0 READ getCPUSerial_0 WRITE setCPUSerial_0 NOTIFY CPUSerial_0Changed);
    Q_PROPERTY(quint8 CPUSerial_1 READ getCPUSerial_1 WRITE setCPUSerial_1 NOTIFY CPUSerial_1Changed);
    Q_PROPERTY(quint8 CPUSerial_2 READ getCPUSerial_2 WRITE setCPUSerial_2 NOTIFY CPUSerial_2Changed);
    Q_PROPERTY(quint8 CPUSerial_3 READ getCPUSerial_3 WRITE setCPUSerial_3 NOTIFY CPUSerial_3Changed);
    Q_PROPERTY(quint8 CPUSerial_4 READ getCPUSerial_4 WRITE setCPUSerial_4 NOTIFY CPUSerial_4Changed);
    Q_PROPERTY(quint8 CPUSerial_5 READ getCPUSerial_5 WRITE setCPUSerial_5 NOTIFY CPUSerial_5Changed);
    Q_PROPERTY(quint8 CPUSerial_6 READ getCPUSerial_6 WRITE setCPUSerial_6 NOTIFY CPUSerial_6Changed);
    Q_PROPERTY(quint8 CPUSerial_7 READ getCPUSerial_7 WRITE setCPUSerial_7 NOTIFY CPUSerial_7Changed);
    Q_PROPERTY(quint8 CPUSerial_8 READ getCPUSerial_8 WRITE setCPUSerial_8 NOTIFY CPUSerial_8Changed);
    Q_PROPERTY(quint8 CPUSerial_9 READ getCPUSerial_9 WRITE setCPUSerial_9 NOTIFY CPUSerial_9Changed);
    Q_PROPERTY(quint8 CPUSerial_10 READ getCPUSerial_10 WRITE setCPUSerial_10 NOTIFY CPUSerial_10Changed);
    Q_PROPERTY(quint8 CPUSerial_11 READ getCPUSerial_11 WRITE setCPUSerial_11 NOTIFY CPUSerial_11Changed);
    Q_PROPERTY(quint8 BoardType READ getBoardType WRITE setBoardType NOTIFY BoardTypeChanged);
    Q_PROPERTY(quint8 RxGood READ getRxGood WRITE setRxGood NOTIFY RxGoodChanged);
    Q_PROPERTY(quint8 RxCorrected READ getRxCorrected WRITE setRxCorrected NOTIFY RxCorrectedChanged);
    Q_PROPERTY(quint8 RxErrors READ getRxErrors WRITE setRxErrors NOTIFY RxErrorsChanged);
    Q_PROPERTY(quint8 RxMissed READ getRxMissed WRITE setRxMissed NOTIFY RxMissedChanged);
    Q_PROPERTY(quint8 RxFailure READ getRxFailure WRITE setRxFailure NOTIFY RxFailureChanged);
    Q_PROPERTY(quint8 TxDropped READ getTxDropped WRITE setTxDropped NOTIFY TxDroppedChanged);
    Q_PROPERTY(quint8 TxFailure READ getTxFailure WRITE setTxFailure NOTIFY TxFailureChanged);
    Q_PROPERTY(quint8 Resets READ getResets WRITE setResets NOTIFY ResetsChanged);
    Q_PROPERTY(quint8 Timeouts READ getTimeouts WRITE setTimeouts NOTIFY TimeoutsChanged);
    Q_PROPERTY(qint8 RSSI READ getRSSI WRITE setRSSI NOTIFY RSSIChanged);
    Q_PROPERTY(quint8 LinkQuality READ getLinkQuality WRITE setLinkQuality NOTIFY LinkQualityChanged);
    Q_PROPERTY(quint8 LinkState READ getLinkState WRITE setLinkState NOTIFY LinkStateChanged);
    Q_PROPERTY(qint8 PairSignalStrengths_0 READ getPairSignalStrengths_0 WRITE setPairSignalStrengths_0 NOTIFY PairSignalStrengths_0Changed);
    Q_PROPERTY(qint8 PairSignalStrengths_1 READ getPairSignalStrengths_1 WRITE setPairSignalStrengths_1 NOTIFY PairSignalStrengths_1Changed);
    Q_PROPERTY(qint8 PairSignalStrengths_2 READ getPairSignalStrengths_2 WRITE setPairSignalStrengths_2 NOTIFY PairSignalStrengths_2Changed);
    Q_PROPERTY(qint8 PairSignalStrengths_3 READ getPairSignalStrengths_3 WRITE setPairSignalStrengths_3 NOTIFY PairSignalStrengths_3Changed);


public:
    // Field structure
    typedef struct {
        quint32 DeviceID;
        quint32 PairIDs[4];
        quint16 BoardRevision;
        quint16 HeapRemaining;
        quint16 UAVTalkErrors;
        quint16 TXRate;
        quint16 RXRate;
        quint16 TXSeq;
        quint16 RXSeq;
        quint8 Description[40];
        quint8 CPUSerial[12];
        quint8 BoardType;
        quint8 RxGood;
        quint8 RxCorrected;
        quint8 RxErrors;
        quint8 RxMissed;
        quint8 RxFailure;
        quint8 TxDropped;
        quint8 TxFailure;
        quint8 Resets;
        quint8 Timeouts;
        qint8 RSSI;
        quint8 LinkQuality;
        quint8 LinkState;
        qint8 PairSignalStrengths[4];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field DeviceID information
    // Field PairIDs information
    /* Number of elements for field PairIDs */
    static const quint32 PAIRIDS_NUMELEM = 4;
    // Field BoardRevision information
    // Field HeapRemaining information
    // Field UAVTalkErrors information
    // Field TXRate information
    // Field RXRate information
    // Field TXSeq information
    // Field RXSeq information
    // Field Description information
    /* Number of elements for field Description */
    static const quint32 DESCRIPTION_NUMELEM = 40;
    // Field CPUSerial information
    /* Number of elements for field CPUSerial */
    static const quint32 CPUSERIAL_NUMELEM = 12;
    // Field BoardType information
    // Field RxGood information
    // Field RxCorrected information
    // Field RxErrors information
    // Field RxMissed information
    // Field RxFailure information
    // Field TxDropped information
    // Field TxFailure information
    // Field Resets information
    // Field Timeouts information
    // Field RSSI information
    // Field LinkQuality information
    // Field LinkState information
    /* Enumeration options for field LinkState */
    typedef enum { LINKSTATE_DISABLED=0, LINKSTATE_ENABLED=1, LINKSTATE_DISCONNECTED=2, LINKSTATE_CONNECTING=3, LINKSTATE_CONNECTED=4 } LinkStateOptions;
    // Field PairSignalStrengths information
    /* Number of elements for field PairSignalStrengths */
    static const quint32 PAIRSIGNALSTRENGTHS_NUMELEM = 4;

  
    // Constants
    static const quint32 OBJID = 0xB1A94E20;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    OPLinkStatus();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static OPLinkStatus* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint32 getDeviceID() const;
    Q_INVOKABLE quint32 getPairIDs(quint32 index) const;
    Q_INVOKABLE quint32 getPairIDs_0() const;
    Q_INVOKABLE quint32 getPairIDs_1() const;
    Q_INVOKABLE quint32 getPairIDs_2() const;
    Q_INVOKABLE quint32 getPairIDs_3() const;
    Q_INVOKABLE quint16 getBoardRevision() const;
    Q_INVOKABLE quint16 getHeapRemaining() const;
    Q_INVOKABLE quint16 getUAVTalkErrors() const;
    Q_INVOKABLE quint16 getTXRate() const;
    Q_INVOKABLE quint16 getRXRate() const;
    Q_INVOKABLE quint16 getTXSeq() const;
    Q_INVOKABLE quint16 getRXSeq() const;
    Q_INVOKABLE quint8 getCPUSerial(quint32 index) const;
    Q_INVOKABLE quint8 getCPUSerial_0() const;
    Q_INVOKABLE quint8 getCPUSerial_1() const;
    Q_INVOKABLE quint8 getCPUSerial_2() const;
    Q_INVOKABLE quint8 getCPUSerial_3() const;
    Q_INVOKABLE quint8 getCPUSerial_4() const;
    Q_INVOKABLE quint8 getCPUSerial_5() const;
    Q_INVOKABLE quint8 getCPUSerial_6() const;
    Q_INVOKABLE quint8 getCPUSerial_7() const;
    Q_INVOKABLE quint8 getCPUSerial_8() const;
    Q_INVOKABLE quint8 getCPUSerial_9() const;
    Q_INVOKABLE quint8 getCPUSerial_10() const;
    Q_INVOKABLE quint8 getCPUSerial_11() const;
    Q_INVOKABLE quint8 getBoardType() const;
    Q_INVOKABLE quint8 getRxGood() const;
    Q_INVOKABLE quint8 getRxCorrected() const;
    Q_INVOKABLE quint8 getRxErrors() const;
    Q_INVOKABLE quint8 getRxMissed() const;
    Q_INVOKABLE quint8 getRxFailure() const;
    Q_INVOKABLE quint8 getTxDropped() const;
    Q_INVOKABLE quint8 getTxFailure() const;
    Q_INVOKABLE quint8 getResets() const;
    Q_INVOKABLE quint8 getTimeouts() const;
    Q_INVOKABLE qint8 getRSSI() const;
    Q_INVOKABLE quint8 getLinkQuality() const;
    Q_INVOKABLE quint8 getLinkState() const;
    Q_INVOKABLE qint8 getPairSignalStrengths(quint32 index) const;
    Q_INVOKABLE qint8 getPairSignalStrengths_0() const;
    Q_INVOKABLE qint8 getPairSignalStrengths_1() const;
    Q_INVOKABLE qint8 getPairSignalStrengths_2() const;
    Q_INVOKABLE qint8 getPairSignalStrengths_3() const;


public slots:
    void setDeviceID(quint32 value);
    void setPairIDs(quint32 index, quint32 value);
    void setPairIDs_0(quint32 value);
    void setPairIDs_1(quint32 value);
    void setPairIDs_2(quint32 value);
    void setPairIDs_3(quint32 value);
    void setBoardRevision(quint16 value);
    void setHeapRemaining(quint16 value);
    void setUAVTalkErrors(quint16 value);
    void setTXRate(quint16 value);
    void setRXRate(quint16 value);
    void setTXSeq(quint16 value);
    void setRXSeq(quint16 value);
    void setCPUSerial(quint32 index, quint8 value);
    void setCPUSerial_0(quint8 value);
    void setCPUSerial_1(quint8 value);
    void setCPUSerial_2(quint8 value);
    void setCPUSerial_3(quint8 value);
    void setCPUSerial_4(quint8 value);
    void setCPUSerial_5(quint8 value);
    void setCPUSerial_6(quint8 value);
    void setCPUSerial_7(quint8 value);
    void setCPUSerial_8(quint8 value);
    void setCPUSerial_9(quint8 value);
    void setCPUSerial_10(quint8 value);
    void setCPUSerial_11(quint8 value);
    void setBoardType(quint8 value);
    void setRxGood(quint8 value);
    void setRxCorrected(quint8 value);
    void setRxErrors(quint8 value);
    void setRxMissed(quint8 value);
    void setRxFailure(quint8 value);
    void setTxDropped(quint8 value);
    void setTxFailure(quint8 value);
    void setResets(quint8 value);
    void setTimeouts(quint8 value);
    void setRSSI(qint8 value);
    void setLinkQuality(quint8 value);
    void setLinkState(quint8 value);
    void setPairSignalStrengths(quint32 index, qint8 value);
    void setPairSignalStrengths_0(qint8 value);
    void setPairSignalStrengths_1(qint8 value);
    void setPairSignalStrengths_2(qint8 value);
    void setPairSignalStrengths_3(qint8 value);


signals:
    void DeviceIDChanged(quint32 value);
    void PairIDsChanged(quint32 index, quint32 value);
    void PairIDs_0Changed(quint32 value);
    void PairIDs_1Changed(quint32 value);
    void PairIDs_2Changed(quint32 value);
    void PairIDs_3Changed(quint32 value);
    void BoardRevisionChanged(quint16 value);
    void HeapRemainingChanged(quint16 value);
    void UAVTalkErrorsChanged(quint16 value);
    void TXRateChanged(quint16 value);
    void RXRateChanged(quint16 value);
    void TXSeqChanged(quint16 value);
    void RXSeqChanged(quint16 value);
    void CPUSerialChanged(quint32 index, quint8 value);
    void CPUSerial_0Changed(quint8 value);
    void CPUSerial_1Changed(quint8 value);
    void CPUSerial_2Changed(quint8 value);
    void CPUSerial_3Changed(quint8 value);
    void CPUSerial_4Changed(quint8 value);
    void CPUSerial_5Changed(quint8 value);
    void CPUSerial_6Changed(quint8 value);
    void CPUSerial_7Changed(quint8 value);
    void CPUSerial_8Changed(quint8 value);
    void CPUSerial_9Changed(quint8 value);
    void CPUSerial_10Changed(quint8 value);
    void CPUSerial_11Changed(quint8 value);
    void BoardTypeChanged(quint8 value);
    void RxGoodChanged(quint8 value);
    void RxCorrectedChanged(quint8 value);
    void RxErrorsChanged(quint8 value);
    void RxMissedChanged(quint8 value);
    void RxFailureChanged(quint8 value);
    void TxDroppedChanged(quint8 value);
    void TxFailureChanged(quint8 value);
    void ResetsChanged(quint8 value);
    void TimeoutsChanged(quint8 value);
    void RSSIChanged(qint8 value);
    void LinkQualityChanged(quint8 value);
    void LinkStateChanged(quint8 value);
    void PairSignalStrengthsChanged(quint32 index, qint8 value);
    void PairSignalStrengths_0Changed(qint8 value);
    void PairSignalStrengths_1Changed(qint8 value);
    void PairSignalStrengths_2Changed(qint8 value);
    void PairSignalStrengths_3Changed(qint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // OPLINKSTATUS_H
