/**
 ******************************************************************************
 *
 * @file       i2cstats.cpp
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

#include "i2cstats.h"
#include "uavobjectfield.h"

const QString I2CStats::NAME = QString("I2CStats");
const QString I2CStats::DESCRIPTION = QString("Tracks statistics on the I2C bus.");
const QString I2CStats::CATEGORY = QString("System");

/**
 * Constructor
 */
I2CStats::I2CStats(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList evirq_logElemNames;
    evirq_logElemNames.append("0");
    evirq_logElemNames.append("1");
    evirq_logElemNames.append("2");
    evirq_logElemNames.append("3");
    evirq_logElemNames.append("4");
    fields.append( new UAVObjectField(QString("evirq_log"), tr(""), QString(""), UAVObjectField::UINT32, evirq_logElemNames, QStringList(), QString("")));
    QStringList erirq_logElemNames;
    erirq_logElemNames.append("0");
    erirq_logElemNames.append("1");
    erirq_logElemNames.append("2");
    erirq_logElemNames.append("3");
    erirq_logElemNames.append("4");
    fields.append( new UAVObjectField(QString("erirq_log"), tr(""), QString(""), UAVObjectField::UINT32, erirq_logElemNames, QStringList(), QString("")));
    QStringList event_errorsElemNames;
    event_errorsElemNames.append("0");
    fields.append( new UAVObjectField(QString("event_errors"), tr(""), QString(""), UAVObjectField::UINT8, event_errorsElemNames, QStringList(), QString("")));
    QStringList fsm_errorsElemNames;
    fsm_errorsElemNames.append("0");
    fields.append( new UAVObjectField(QString("fsm_errors"), tr(""), QString(""), UAVObjectField::UINT8, fsm_errorsElemNames, QStringList(), QString("")));
    QStringList irq_errorsElemNames;
    irq_errorsElemNames.append("0");
    fields.append( new UAVObjectField(QString("irq_errors"), tr(""), QString(""), UAVObjectField::UINT8, irq_errorsElemNames, QStringList(), QString("")));
    QStringList nacksElemNames;
    nacksElemNames.append("0");
    fields.append( new UAVObjectField(QString("nacks"), tr(""), QString(""), UAVObjectField::UINT8, nacksElemNames, QStringList(), QString("")));
    QStringList timeoutsElemNames;
    timeoutsElemNames.append("0");
    fields.append( new UAVObjectField(QString("timeouts"), tr(""), QString(""), UAVObjectField::UINT8, timeoutsElemNames, QStringList(), QString("")));
    QStringList last_error_typeElemNames;
    last_error_typeElemNames.append("0");
    QStringList last_error_typeEnumOptions;
    last_error_typeEnumOptions.append("EVENT");
    last_error_typeEnumOptions.append("FSM");
    last_error_typeEnumOptions.append("INTERRUPT");
    fields.append( new UAVObjectField(QString("last_error_type"), tr(""), QString(""), UAVObjectField::ENUM, last_error_typeElemNames, last_error_typeEnumOptions, QString("")));
    QStringList event_logElemNames;
    event_logElemNames.append("0");
    event_logElemNames.append("1");
    event_logElemNames.append("2");
    event_logElemNames.append("3");
    event_logElemNames.append("4");
    QStringList event_logEnumOptions;
    event_logEnumOptions.append("I2C_EVENT_BUS_ERROR");
    event_logEnumOptions.append("I2C_EVENT_START");
    event_logEnumOptions.append("I2C_EVENT_STARTED_MORE_TXN_READ");
    event_logEnumOptions.append("I2C_EVENT_STARTED_MORE_TXN_WRITE");
    event_logEnumOptions.append("I2C_EVENT_STARTED_LAST_TXN_READ");
    event_logEnumOptions.append("I2C_EVENT_STARTED_LAST_TXN_WRITE");
    event_logEnumOptions.append("I2C_EVENT_ADDR_SENT_LEN_EQ_0");
    event_logEnumOptions.append("I2C_EVENT_ADDR_SENT_LEN_EQ_1");
    event_logEnumOptions.append("I2C_EVENT_ADDR_SENT_LEN_EQ_2");
    event_logEnumOptions.append("I2C_EVENT_ADDR_SENT_LEN_GT_2");
    event_logEnumOptions.append("I2C_EVENT_TRANSFER_DONE_LEN_EQ_0");
    event_logEnumOptions.append("I2C_EVENT_TRANSFER_DONE_LEN_EQ_1");
    event_logEnumOptions.append("I2C_EVENT_TRANSFER_DONE_LEN_EQ_2");
    event_logEnumOptions.append("I2C_EVENT_TRANSFER_DONE_LEN_GT_2");
    event_logEnumOptions.append("I2C_EVENT_NACK");
    event_logEnumOptions.append("I2C_EVENT_STOPPED");
    event_logEnumOptions.append("I2C_EVENT_AUTO");
    fields.append( new UAVObjectField(QString("event_log"), tr(""), QString(""), UAVObjectField::ENUM, event_logElemNames, event_logEnumOptions, QString("")));
    QStringList state_logElemNames;
    state_logElemNames.append("0");
    state_logElemNames.append("1");
    state_logElemNames.append("2");
    state_logElemNames.append("3");
    state_logElemNames.append("4");
    QStringList state_logEnumOptions;
    state_logEnumOptions.append("I2C_STATE_FSM_FAULT");
    state_logEnumOptions.append("I2C_STATE_BUS_ERROR");
    state_logEnumOptions.append("I2C_STATE_STOPPED");
    state_logEnumOptions.append("I2C_STATE_STOPPING");
    state_logEnumOptions.append("I2C_STATE_STARTING");
    state_logEnumOptions.append("I2C_STATE_R_MORE_TXN_ADDR");
    state_logEnumOptions.append("I2C_STATE_R_MORE_TXN_PRE_ONE");
    state_logEnumOptions.append("I2C_STATE_R_MORE_TXN_PRE_FIRST");
    state_logEnumOptions.append("I2C_STATE_R_MORE_TXN_PRE_MIDDLE");
    state_logEnumOptions.append("I2C_STATE_R_MORE_TXN_LAST");
    state_logEnumOptions.append("I2C_STATE_R_MORE_TXN_POST_LAST");
    state_logEnumOptions.append("R_LAST_TXN_ADDR");
    state_logEnumOptions.append("I2C_STATE_R_LAST_TXN_PRE_ONE");
    state_logEnumOptions.append("I2C_STATE_R_LAST_TXN_PRE_FIRST");
    state_logEnumOptions.append("I2C_STATE_R_LAST_TXN_PRE_MIDDLE");
    state_logEnumOptions.append("I2C_STATE_R_LAST_TXN_PRE_LAST");
    state_logEnumOptions.append("I2C_STATE_R_LAST_TXN_POST_LAST");
    state_logEnumOptions.append("I2C_STATE_W_MORE_TXN_ADDR");
    state_logEnumOptions.append("I2C_STATE_W_MORE_TXN_MIDDLE");
    state_logEnumOptions.append("I2C_STATE_W_MORE_TXN_LAST");
    state_logEnumOptions.append("I2C_STATE_W_LAST_TXN_ADDR");
    state_logEnumOptions.append("I2C_STATE_W_LAST_TXN_MIDDLE");
    state_logEnumOptions.append("I2C_STATE_W_LAST_TXN_LAST");
    state_logEnumOptions.append("I2C_STATE_NACK");
    fields.append( new UAVObjectField(QString("state_log"), tr(""), QString(""), UAVObjectField::ENUM, state_logElemNames, state_logEnumOptions, QString("")));

    // Initialize object
    initializeFields(fields, (quint8 *)&data, NUMBYTES);
    // Set the default field values
    setDefaultFieldValues();
    // Set the object description
    setDescription(DESCRIPTION);

    // Set the Category of this object type
    setCategory(CATEGORY);

    connect(this, SIGNAL(objectUpdated(UAVObject *)), SLOT(emitNotifications()));
}

/**
 * Get the default metadata for this object
 */
UAVObject::Metadata I2CStats::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        0 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        0 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_PERIODIC << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_GCS_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_LOGGING_UPDATE_MODE_SHIFT;
    metadata.flightTelemetryUpdatePeriod = 10000;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void I2CStats::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
I2CStats::DataFields I2CStats::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void I2CStats::setData(const DataFields& data)
{
    QMutexLocker locker(mutex);
    // Get metadata
    Metadata mdata = getMetadata();
    // Update object if the access mode permits
    if (UAVObject::GetGcsAccess(mdata) == ACCESS_READWRITE) {
        this->data = data;
        emit objectUpdatedAuto(this); // trigger object updated event
        emit objectUpdated(this);
    }
}

void I2CStats::emitNotifications()
{
            //if (data.evirq_log[0] != oldData.evirq_log[0])
            emit evirq_log_0Changed(data.evirq_log[0]);
        //if (data.evirq_log[1] != oldData.evirq_log[1])
            emit evirq_log_1Changed(data.evirq_log[1]);
        //if (data.evirq_log[2] != oldData.evirq_log[2])
            emit evirq_log_2Changed(data.evirq_log[2]);
        //if (data.evirq_log[3] != oldData.evirq_log[3])
            emit evirq_log_3Changed(data.evirq_log[3]);
        //if (data.evirq_log[4] != oldData.evirq_log[4])
            emit evirq_log_4Changed(data.evirq_log[4]);
        //if (data.erirq_log[0] != oldData.erirq_log[0])
            emit erirq_log_0Changed(data.erirq_log[0]);
        //if (data.erirq_log[1] != oldData.erirq_log[1])
            emit erirq_log_1Changed(data.erirq_log[1]);
        //if (data.erirq_log[2] != oldData.erirq_log[2])
            emit erirq_log_2Changed(data.erirq_log[2]);
        //if (data.erirq_log[3] != oldData.erirq_log[3])
            emit erirq_log_3Changed(data.erirq_log[3]);
        //if (data.erirq_log[4] != oldData.erirq_log[4])
            emit erirq_log_4Changed(data.erirq_log[4]);
        //if (data.event_errors != oldData.event_errors)
            emit event_errorsChanged(data.event_errors);
        //if (data.fsm_errors != oldData.fsm_errors)
            emit fsm_errorsChanged(data.fsm_errors);
        //if (data.irq_errors != oldData.irq_errors)
            emit irq_errorsChanged(data.irq_errors);
        //if (data.nacks != oldData.nacks)
            emit nacksChanged(data.nacks);
        //if (data.timeouts != oldData.timeouts)
            emit timeoutsChanged(data.timeouts);
        //if (data.last_error_type != oldData.last_error_type)
            emit last_error_typeChanged(data.last_error_type);
        //if (data.event_log[0] != oldData.event_log[0])
            emit event_log_0Changed(data.event_log[0]);
        //if (data.event_log[1] != oldData.event_log[1])
            emit event_log_1Changed(data.event_log[1]);
        //if (data.event_log[2] != oldData.event_log[2])
            emit event_log_2Changed(data.event_log[2]);
        //if (data.event_log[3] != oldData.event_log[3])
            emit event_log_3Changed(data.event_log[3]);
        //if (data.event_log[4] != oldData.event_log[4])
            emit event_log_4Changed(data.event_log[4]);
        //if (data.state_log[0] != oldData.state_log[0])
            emit state_log_0Changed(data.state_log[0]);
        //if (data.state_log[1] != oldData.state_log[1])
            emit state_log_1Changed(data.state_log[1]);
        //if (data.state_log[2] != oldData.state_log[2])
            emit state_log_2Changed(data.state_log[2]);
        //if (data.state_log[3] != oldData.state_log[3])
            emit state_log_3Changed(data.state_log[3]);
        //if (data.state_log[4] != oldData.state_log[4])
            emit state_log_4Changed(data.state_log[4]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *I2CStats::clone(quint32 instID)
{
    I2CStats *obj = new I2CStats();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *I2CStats::dirtyClone()
{
    I2CStats *obj = new I2CStats();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
I2CStats *I2CStats::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<I2CStats *>(objMngr->getObject(I2CStats::OBJID, instID));
}

quint32 I2CStats::getevirq_log(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.evirq_log[index];
}
void I2CStats::setevirq_log(quint32 index, quint32 value)
{
   mutex->lock();
   bool changed = data.evirq_log[index] != value;
   data.evirq_log[index] = value;
   mutex->unlock();
   if (changed) emit evirq_logChanged(index,value);
}

quint32 I2CStats::getevirq_log_0() const
{
   QMutexLocker locker(mutex);
   return data.evirq_log[0];
}
void I2CStats::setevirq_log_0(quint32 value)
{
   mutex->lock();
   bool changed = data.evirq_log[0] != value;
   data.evirq_log[0] = value;
   mutex->unlock();
   if (changed) emit evirq_log_0Changed(value);
}

quint32 I2CStats::getevirq_log_1() const
{
   QMutexLocker locker(mutex);
   return data.evirq_log[1];
}
void I2CStats::setevirq_log_1(quint32 value)
{
   mutex->lock();
   bool changed = data.evirq_log[1] != value;
   data.evirq_log[1] = value;
   mutex->unlock();
   if (changed) emit evirq_log_1Changed(value);
}

quint32 I2CStats::getevirq_log_2() const
{
   QMutexLocker locker(mutex);
   return data.evirq_log[2];
}
void I2CStats::setevirq_log_2(quint32 value)
{
   mutex->lock();
   bool changed = data.evirq_log[2] != value;
   data.evirq_log[2] = value;
   mutex->unlock();
   if (changed) emit evirq_log_2Changed(value);
}

quint32 I2CStats::getevirq_log_3() const
{
   QMutexLocker locker(mutex);
   return data.evirq_log[3];
}
void I2CStats::setevirq_log_3(quint32 value)
{
   mutex->lock();
   bool changed = data.evirq_log[3] != value;
   data.evirq_log[3] = value;
   mutex->unlock();
   if (changed) emit evirq_log_3Changed(value);
}

quint32 I2CStats::getevirq_log_4() const
{
   QMutexLocker locker(mutex);
   return data.evirq_log[4];
}
void I2CStats::setevirq_log_4(quint32 value)
{
   mutex->lock();
   bool changed = data.evirq_log[4] != value;
   data.evirq_log[4] = value;
   mutex->unlock();
   if (changed) emit evirq_log_4Changed(value);
}

quint32 I2CStats::geterirq_log(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.erirq_log[index];
}
void I2CStats::seterirq_log(quint32 index, quint32 value)
{
   mutex->lock();
   bool changed = data.erirq_log[index] != value;
   data.erirq_log[index] = value;
   mutex->unlock();
   if (changed) emit erirq_logChanged(index,value);
}

quint32 I2CStats::geterirq_log_0() const
{
   QMutexLocker locker(mutex);
   return data.erirq_log[0];
}
void I2CStats::seterirq_log_0(quint32 value)
{
   mutex->lock();
   bool changed = data.erirq_log[0] != value;
   data.erirq_log[0] = value;
   mutex->unlock();
   if (changed) emit erirq_log_0Changed(value);
}

quint32 I2CStats::geterirq_log_1() const
{
   QMutexLocker locker(mutex);
   return data.erirq_log[1];
}
void I2CStats::seterirq_log_1(quint32 value)
{
   mutex->lock();
   bool changed = data.erirq_log[1] != value;
   data.erirq_log[1] = value;
   mutex->unlock();
   if (changed) emit erirq_log_1Changed(value);
}

quint32 I2CStats::geterirq_log_2() const
{
   QMutexLocker locker(mutex);
   return data.erirq_log[2];
}
void I2CStats::seterirq_log_2(quint32 value)
{
   mutex->lock();
   bool changed = data.erirq_log[2] != value;
   data.erirq_log[2] = value;
   mutex->unlock();
   if (changed) emit erirq_log_2Changed(value);
}

quint32 I2CStats::geterirq_log_3() const
{
   QMutexLocker locker(mutex);
   return data.erirq_log[3];
}
void I2CStats::seterirq_log_3(quint32 value)
{
   mutex->lock();
   bool changed = data.erirq_log[3] != value;
   data.erirq_log[3] = value;
   mutex->unlock();
   if (changed) emit erirq_log_3Changed(value);
}

quint32 I2CStats::geterirq_log_4() const
{
   QMutexLocker locker(mutex);
   return data.erirq_log[4];
}
void I2CStats::seterirq_log_4(quint32 value)
{
   mutex->lock();
   bool changed = data.erirq_log[4] != value;
   data.erirq_log[4] = value;
   mutex->unlock();
   if (changed) emit erirq_log_4Changed(value);
}

quint8 I2CStats::getevent_errors() const
{
   QMutexLocker locker(mutex);
   return data.event_errors;
}
void I2CStats::setevent_errors(quint8 value)
{
   mutex->lock();
   bool changed = data.event_errors != value;
   data.event_errors = value;
   mutex->unlock();
   if (changed) emit event_errorsChanged(value);
}

quint8 I2CStats::getfsm_errors() const
{
   QMutexLocker locker(mutex);
   return data.fsm_errors;
}
void I2CStats::setfsm_errors(quint8 value)
{
   mutex->lock();
   bool changed = data.fsm_errors != value;
   data.fsm_errors = value;
   mutex->unlock();
   if (changed) emit fsm_errorsChanged(value);
}

quint8 I2CStats::getirq_errors() const
{
   QMutexLocker locker(mutex);
   return data.irq_errors;
}
void I2CStats::setirq_errors(quint8 value)
{
   mutex->lock();
   bool changed = data.irq_errors != value;
   data.irq_errors = value;
   mutex->unlock();
   if (changed) emit irq_errorsChanged(value);
}

quint8 I2CStats::getnacks() const
{
   QMutexLocker locker(mutex);
   return data.nacks;
}
void I2CStats::setnacks(quint8 value)
{
   mutex->lock();
   bool changed = data.nacks != value;
   data.nacks = value;
   mutex->unlock();
   if (changed) emit nacksChanged(value);
}

quint8 I2CStats::gettimeouts() const
{
   QMutexLocker locker(mutex);
   return data.timeouts;
}
void I2CStats::settimeouts(quint8 value)
{
   mutex->lock();
   bool changed = data.timeouts != value;
   data.timeouts = value;
   mutex->unlock();
   if (changed) emit timeoutsChanged(value);
}

quint8 I2CStats::getlast_error_type() const
{
   QMutexLocker locker(mutex);
   return data.last_error_type;
}
void I2CStats::setlast_error_type(quint8 value)
{
   mutex->lock();
   bool changed = data.last_error_type != value;
   data.last_error_type = value;
   mutex->unlock();
   if (changed) emit last_error_typeChanged(value);
}

quint8 I2CStats::getevent_log(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.event_log[index];
}
void I2CStats::setevent_log(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.event_log[index] != value;
   data.event_log[index] = value;
   mutex->unlock();
   if (changed) emit event_logChanged(index,value);
}

quint8 I2CStats::getevent_log_0() const
{
   QMutexLocker locker(mutex);
   return data.event_log[0];
}
void I2CStats::setevent_log_0(quint8 value)
{
   mutex->lock();
   bool changed = data.event_log[0] != value;
   data.event_log[0] = value;
   mutex->unlock();
   if (changed) emit event_log_0Changed(value);
}

quint8 I2CStats::getevent_log_1() const
{
   QMutexLocker locker(mutex);
   return data.event_log[1];
}
void I2CStats::setevent_log_1(quint8 value)
{
   mutex->lock();
   bool changed = data.event_log[1] != value;
   data.event_log[1] = value;
   mutex->unlock();
   if (changed) emit event_log_1Changed(value);
}

quint8 I2CStats::getevent_log_2() const
{
   QMutexLocker locker(mutex);
   return data.event_log[2];
}
void I2CStats::setevent_log_2(quint8 value)
{
   mutex->lock();
   bool changed = data.event_log[2] != value;
   data.event_log[2] = value;
   mutex->unlock();
   if (changed) emit event_log_2Changed(value);
}

quint8 I2CStats::getevent_log_3() const
{
   QMutexLocker locker(mutex);
   return data.event_log[3];
}
void I2CStats::setevent_log_3(quint8 value)
{
   mutex->lock();
   bool changed = data.event_log[3] != value;
   data.event_log[3] = value;
   mutex->unlock();
   if (changed) emit event_log_3Changed(value);
}

quint8 I2CStats::getevent_log_4() const
{
   QMutexLocker locker(mutex);
   return data.event_log[4];
}
void I2CStats::setevent_log_4(quint8 value)
{
   mutex->lock();
   bool changed = data.event_log[4] != value;
   data.event_log[4] = value;
   mutex->unlock();
   if (changed) emit event_log_4Changed(value);
}

quint8 I2CStats::getstate_log(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.state_log[index];
}
void I2CStats::setstate_log(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.state_log[index] != value;
   data.state_log[index] = value;
   mutex->unlock();
   if (changed) emit state_logChanged(index,value);
}

quint8 I2CStats::getstate_log_0() const
{
   QMutexLocker locker(mutex);
   return data.state_log[0];
}
void I2CStats::setstate_log_0(quint8 value)
{
   mutex->lock();
   bool changed = data.state_log[0] != value;
   data.state_log[0] = value;
   mutex->unlock();
   if (changed) emit state_log_0Changed(value);
}

quint8 I2CStats::getstate_log_1() const
{
   QMutexLocker locker(mutex);
   return data.state_log[1];
}
void I2CStats::setstate_log_1(quint8 value)
{
   mutex->lock();
   bool changed = data.state_log[1] != value;
   data.state_log[1] = value;
   mutex->unlock();
   if (changed) emit state_log_1Changed(value);
}

quint8 I2CStats::getstate_log_2() const
{
   QMutexLocker locker(mutex);
   return data.state_log[2];
}
void I2CStats::setstate_log_2(quint8 value)
{
   mutex->lock();
   bool changed = data.state_log[2] != value;
   data.state_log[2] = value;
   mutex->unlock();
   if (changed) emit state_log_2Changed(value);
}

quint8 I2CStats::getstate_log_3() const
{
   QMutexLocker locker(mutex);
   return data.state_log[3];
}
void I2CStats::setstate_log_3(quint8 value)
{
   mutex->lock();
   bool changed = data.state_log[3] != value;
   data.state_log[3] = value;
   mutex->unlock();
   if (changed) emit state_log_3Changed(value);
}

quint8 I2CStats::getstate_log_4() const
{
   QMutexLocker locker(mutex);
   return data.state_log[4];
}
void I2CStats::setstate_log_4(quint8 value)
{
   mutex->lock();
   bool changed = data.state_log[4] != value;
   data.state_log[4] = value;
   mutex->unlock();
   if (changed) emit state_log_4Changed(value);
}


