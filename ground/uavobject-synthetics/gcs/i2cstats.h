/**
 ******************************************************************************
 *
 * @file       i2cstats.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: i2cstats.xml. 
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
#ifndef I2CSTATS_H
#define I2CSTATS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT I2CStats: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 evirq_log_0 READ getevirq_log_0 WRITE setevirq_log_0 NOTIFY evirq_log_0Changed);
    Q_PROPERTY(quint32 evirq_log_1 READ getevirq_log_1 WRITE setevirq_log_1 NOTIFY evirq_log_1Changed);
    Q_PROPERTY(quint32 evirq_log_2 READ getevirq_log_2 WRITE setevirq_log_2 NOTIFY evirq_log_2Changed);
    Q_PROPERTY(quint32 evirq_log_3 READ getevirq_log_3 WRITE setevirq_log_3 NOTIFY evirq_log_3Changed);
    Q_PROPERTY(quint32 evirq_log_4 READ getevirq_log_4 WRITE setevirq_log_4 NOTIFY evirq_log_4Changed);
    Q_PROPERTY(quint32 erirq_log_0 READ geterirq_log_0 WRITE seterirq_log_0 NOTIFY erirq_log_0Changed);
    Q_PROPERTY(quint32 erirq_log_1 READ geterirq_log_1 WRITE seterirq_log_1 NOTIFY erirq_log_1Changed);
    Q_PROPERTY(quint32 erirq_log_2 READ geterirq_log_2 WRITE seterirq_log_2 NOTIFY erirq_log_2Changed);
    Q_PROPERTY(quint32 erirq_log_3 READ geterirq_log_3 WRITE seterirq_log_3 NOTIFY erirq_log_3Changed);
    Q_PROPERTY(quint32 erirq_log_4 READ geterirq_log_4 WRITE seterirq_log_4 NOTIFY erirq_log_4Changed);
    Q_PROPERTY(quint8 event_errors READ getevent_errors WRITE setevent_errors NOTIFY event_errorsChanged);
    Q_PROPERTY(quint8 fsm_errors READ getfsm_errors WRITE setfsm_errors NOTIFY fsm_errorsChanged);
    Q_PROPERTY(quint8 irq_errors READ getirq_errors WRITE setirq_errors NOTIFY irq_errorsChanged);
    Q_PROPERTY(quint8 nacks READ getnacks WRITE setnacks NOTIFY nacksChanged);
    Q_PROPERTY(quint8 timeouts READ gettimeouts WRITE settimeouts NOTIFY timeoutsChanged);
    Q_PROPERTY(quint8 last_error_type READ getlast_error_type WRITE setlast_error_type NOTIFY last_error_typeChanged);
    Q_PROPERTY(quint8 event_log_0 READ getevent_log_0 WRITE setevent_log_0 NOTIFY event_log_0Changed);
    Q_PROPERTY(quint8 event_log_1 READ getevent_log_1 WRITE setevent_log_1 NOTIFY event_log_1Changed);
    Q_PROPERTY(quint8 event_log_2 READ getevent_log_2 WRITE setevent_log_2 NOTIFY event_log_2Changed);
    Q_PROPERTY(quint8 event_log_3 READ getevent_log_3 WRITE setevent_log_3 NOTIFY event_log_3Changed);
    Q_PROPERTY(quint8 event_log_4 READ getevent_log_4 WRITE setevent_log_4 NOTIFY event_log_4Changed);
    Q_PROPERTY(quint8 state_log_0 READ getstate_log_0 WRITE setstate_log_0 NOTIFY state_log_0Changed);
    Q_PROPERTY(quint8 state_log_1 READ getstate_log_1 WRITE setstate_log_1 NOTIFY state_log_1Changed);
    Q_PROPERTY(quint8 state_log_2 READ getstate_log_2 WRITE setstate_log_2 NOTIFY state_log_2Changed);
    Q_PROPERTY(quint8 state_log_3 READ getstate_log_3 WRITE setstate_log_3 NOTIFY state_log_3Changed);
    Q_PROPERTY(quint8 state_log_4 READ getstate_log_4 WRITE setstate_log_4 NOTIFY state_log_4Changed);


public:
    // Field structure
    typedef struct {
        quint32 evirq_log[5];
        quint32 erirq_log[5];
        quint8 event_errors;
        quint8 fsm_errors;
        quint8 irq_errors;
        quint8 nacks;
        quint8 timeouts;
        quint8 last_error_type;
        quint8 event_log[5];
        quint8 state_log[5];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field evirq_log information
    /* Number of elements for field evirq_log */
    static const quint32 EVIRQ_LOG_NUMELEM = 5;
    // Field erirq_log information
    /* Number of elements for field erirq_log */
    static const quint32 ERIRQ_LOG_NUMELEM = 5;
    // Field event_errors information
    // Field fsm_errors information
    // Field irq_errors information
    // Field nacks information
    // Field timeouts information
    // Field last_error_type information
    /* Enumeration options for field last_error_type */
    typedef enum { LAST_ERROR_TYPE_EVENT=0, LAST_ERROR_TYPE_FSM=1, LAST_ERROR_TYPE_INTERRUPT=2 } last_error_typeOptions;
    // Field event_log information
    /* Enumeration options for field event_log */
    typedef enum { EVENT_LOG_I2C_EVENT_BUS_ERROR=0, EVENT_LOG_I2C_EVENT_START=1, EVENT_LOG_I2C_EVENT_STARTED_MORE_TXN_READ=2, EVENT_LOG_I2C_EVENT_STARTED_MORE_TXN_WRITE=3, EVENT_LOG_I2C_EVENT_STARTED_LAST_TXN_READ=4, EVENT_LOG_I2C_EVENT_STARTED_LAST_TXN_WRITE=5, EVENT_LOG_I2C_EVENT_ADDR_SENT_LEN_EQ_0=6, EVENT_LOG_I2C_EVENT_ADDR_SENT_LEN_EQ_1=7, EVENT_LOG_I2C_EVENT_ADDR_SENT_LEN_EQ_2=8, EVENT_LOG_I2C_EVENT_ADDR_SENT_LEN_GT_2=9, EVENT_LOG_I2C_EVENT_TRANSFER_DONE_LEN_EQ_0=10, EVENT_LOG_I2C_EVENT_TRANSFER_DONE_LEN_EQ_1=11, EVENT_LOG_I2C_EVENT_TRANSFER_DONE_LEN_EQ_2=12, EVENT_LOG_I2C_EVENT_TRANSFER_DONE_LEN_GT_2=13, EVENT_LOG_I2C_EVENT_NACK=14, EVENT_LOG_I2C_EVENT_STOPPED=15, EVENT_LOG_I2C_EVENT_AUTO=16 } event_logOptions;
    /* Number of elements for field event_log */
    static const quint32 EVENT_LOG_NUMELEM = 5;
    // Field state_log information
    /* Enumeration options for field state_log */
    typedef enum { STATE_LOG_I2C_STATE_FSM_FAULT=0, STATE_LOG_I2C_STATE_BUS_ERROR=1, STATE_LOG_I2C_STATE_STOPPED=2, STATE_LOG_I2C_STATE_STOPPING=3, STATE_LOG_I2C_STATE_STARTING=4, STATE_LOG_I2C_STATE_R_MORE_TXN_ADDR=5, STATE_LOG_I2C_STATE_R_MORE_TXN_PRE_ONE=6, STATE_LOG_I2C_STATE_R_MORE_TXN_PRE_FIRST=7, STATE_LOG_I2C_STATE_R_MORE_TXN_PRE_MIDDLE=8, STATE_LOG_I2C_STATE_R_MORE_TXN_LAST=9, STATE_LOG_I2C_STATE_R_MORE_TXN_POST_LAST=10, STATE_LOG_R_LAST_TXN_ADDR=11, STATE_LOG_I2C_STATE_R_LAST_TXN_PRE_ONE=12, STATE_LOG_I2C_STATE_R_LAST_TXN_PRE_FIRST=13, STATE_LOG_I2C_STATE_R_LAST_TXN_PRE_MIDDLE=14, STATE_LOG_I2C_STATE_R_LAST_TXN_PRE_LAST=15, STATE_LOG_I2C_STATE_R_LAST_TXN_POST_LAST=16, STATE_LOG_I2C_STATE_W_MORE_TXN_ADDR=17, STATE_LOG_I2C_STATE_W_MORE_TXN_MIDDLE=18, STATE_LOG_I2C_STATE_W_MORE_TXN_LAST=19, STATE_LOG_I2C_STATE_W_LAST_TXN_ADDR=20, STATE_LOG_I2C_STATE_W_LAST_TXN_MIDDLE=21, STATE_LOG_I2C_STATE_W_LAST_TXN_LAST=22, STATE_LOG_I2C_STATE_NACK=23 } state_logOptions;
    /* Number of elements for field state_log */
    static const quint32 STATE_LOG_NUMELEM = 5;

  
    // Constants
    static const quint32 OBJID = 0xB714823E;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    I2CStats();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static I2CStats* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint32 getevirq_log(quint32 index) const;
    Q_INVOKABLE quint32 getevirq_log_0() const;
    Q_INVOKABLE quint32 getevirq_log_1() const;
    Q_INVOKABLE quint32 getevirq_log_2() const;
    Q_INVOKABLE quint32 getevirq_log_3() const;
    Q_INVOKABLE quint32 getevirq_log_4() const;
    Q_INVOKABLE quint32 geterirq_log(quint32 index) const;
    Q_INVOKABLE quint32 geterirq_log_0() const;
    Q_INVOKABLE quint32 geterirq_log_1() const;
    Q_INVOKABLE quint32 geterirq_log_2() const;
    Q_INVOKABLE quint32 geterirq_log_3() const;
    Q_INVOKABLE quint32 geterirq_log_4() const;
    Q_INVOKABLE quint8 getevent_errors() const;
    Q_INVOKABLE quint8 getfsm_errors() const;
    Q_INVOKABLE quint8 getirq_errors() const;
    Q_INVOKABLE quint8 getnacks() const;
    Q_INVOKABLE quint8 gettimeouts() const;
    Q_INVOKABLE quint8 getlast_error_type() const;
    Q_INVOKABLE quint8 getevent_log(quint32 index) const;
    Q_INVOKABLE quint8 getevent_log_0() const;
    Q_INVOKABLE quint8 getevent_log_1() const;
    Q_INVOKABLE quint8 getevent_log_2() const;
    Q_INVOKABLE quint8 getevent_log_3() const;
    Q_INVOKABLE quint8 getevent_log_4() const;
    Q_INVOKABLE quint8 getstate_log(quint32 index) const;
    Q_INVOKABLE quint8 getstate_log_0() const;
    Q_INVOKABLE quint8 getstate_log_1() const;
    Q_INVOKABLE quint8 getstate_log_2() const;
    Q_INVOKABLE quint8 getstate_log_3() const;
    Q_INVOKABLE quint8 getstate_log_4() const;


public slots:
    void setevirq_log(quint32 index, quint32 value);
    void setevirq_log_0(quint32 value);
    void setevirq_log_1(quint32 value);
    void setevirq_log_2(quint32 value);
    void setevirq_log_3(quint32 value);
    void setevirq_log_4(quint32 value);
    void seterirq_log(quint32 index, quint32 value);
    void seterirq_log_0(quint32 value);
    void seterirq_log_1(quint32 value);
    void seterirq_log_2(quint32 value);
    void seterirq_log_3(quint32 value);
    void seterirq_log_4(quint32 value);
    void setevent_errors(quint8 value);
    void setfsm_errors(quint8 value);
    void setirq_errors(quint8 value);
    void setnacks(quint8 value);
    void settimeouts(quint8 value);
    void setlast_error_type(quint8 value);
    void setevent_log(quint32 index, quint8 value);
    void setevent_log_0(quint8 value);
    void setevent_log_1(quint8 value);
    void setevent_log_2(quint8 value);
    void setevent_log_3(quint8 value);
    void setevent_log_4(quint8 value);
    void setstate_log(quint32 index, quint8 value);
    void setstate_log_0(quint8 value);
    void setstate_log_1(quint8 value);
    void setstate_log_2(quint8 value);
    void setstate_log_3(quint8 value);
    void setstate_log_4(quint8 value);


signals:
    void evirq_logChanged(quint32 index, quint32 value);
    void evirq_log_0Changed(quint32 value);
    void evirq_log_1Changed(quint32 value);
    void evirq_log_2Changed(quint32 value);
    void evirq_log_3Changed(quint32 value);
    void evirq_log_4Changed(quint32 value);
    void erirq_logChanged(quint32 index, quint32 value);
    void erirq_log_0Changed(quint32 value);
    void erirq_log_1Changed(quint32 value);
    void erirq_log_2Changed(quint32 value);
    void erirq_log_3Changed(quint32 value);
    void erirq_log_4Changed(quint32 value);
    void event_errorsChanged(quint8 value);
    void fsm_errorsChanged(quint8 value);
    void irq_errorsChanged(quint8 value);
    void nacksChanged(quint8 value);
    void timeoutsChanged(quint8 value);
    void last_error_typeChanged(quint8 value);
    void event_logChanged(quint32 index, quint8 value);
    void event_log_0Changed(quint8 value);
    void event_log_1Changed(quint8 value);
    void event_log_2Changed(quint8 value);
    void event_log_3Changed(quint8 value);
    void event_log_4Changed(quint8 value);
    void state_logChanged(quint32 index, quint8 value);
    void state_log_0Changed(quint8 value);
    void state_log_1Changed(quint8 value);
    void state_log_2Changed(quint8 value);
    void state_log_3Changed(quint8 value);
    void state_log_4Changed(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // I2CSTATS_H
