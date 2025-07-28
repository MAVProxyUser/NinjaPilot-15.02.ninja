/**
 ******************************************************************************
 *
 * @file       groundtruth.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: groundtruth.xml.
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

#include "groundtruth.h"
#include "uavobjectfield.h"

const QString GroundTruth::NAME = QString("GroundTruth");
const QString GroundTruth::DESCRIPTION = QString("Ground truth data output by a simulator.");
const QString GroundTruth::CATEGORY = QString("State");

/**
 * Constructor
 */
GroundTruth::GroundTruth(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList AccelerationXYZElemNames;
    AccelerationXYZElemNames.append("0");
    AccelerationXYZElemNames.append("1");
    AccelerationXYZElemNames.append("2");
    fields.append( new UAVObjectField(QString("AccelerationXYZ"), tr(""), QString("m/s^2"), UAVObjectField::FLOAT32, AccelerationXYZElemNames, QStringList(), QString("")));
    QStringList PositionNEDElemNames;
    PositionNEDElemNames.append("0");
    PositionNEDElemNames.append("1");
    PositionNEDElemNames.append("2");
    fields.append( new UAVObjectField(QString("PositionNED"), tr(""), QString("m"), UAVObjectField::FLOAT32, PositionNEDElemNames, QStringList(), QString("")));
    QStringList VelocityNEDElemNames;
    VelocityNEDElemNames.append("0");
    VelocityNEDElemNames.append("1");
    VelocityNEDElemNames.append("2");
    fields.append( new UAVObjectField(QString("VelocityNED"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, VelocityNEDElemNames, QStringList(), QString("")));
    QStringList RPYElemNames;
    RPYElemNames.append("0");
    RPYElemNames.append("1");
    RPYElemNames.append("2");
    fields.append( new UAVObjectField(QString("RPY"), tr(""), QString("deg"), UAVObjectField::FLOAT32, RPYElemNames, QStringList(), QString("")));
    QStringList AngularRatesElemNames;
    AngularRatesElemNames.append("0");
    AngularRatesElemNames.append("1");
    AngularRatesElemNames.append("2");
    fields.append( new UAVObjectField(QString("AngularRates"), tr(""), QString("deg/s"), UAVObjectField::FLOAT32, AngularRatesElemNames, QStringList(), QString("")));
    QStringList TrueAirspeedElemNames;
    TrueAirspeedElemNames.append("0");
    fields.append( new UAVObjectField(QString("TrueAirspeed"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, TrueAirspeedElemNames, QStringList(), QString("")));
    QStringList CalibratedAirspeedElemNames;
    CalibratedAirspeedElemNames.append("0");
    fields.append( new UAVObjectField(QString("CalibratedAirspeed"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, CalibratedAirspeedElemNames, QStringList(), QString("")));
    QStringList AngleOfAttackElemNames;
    AngleOfAttackElemNames.append("0");
    fields.append( new UAVObjectField(QString("AngleOfAttack"), tr(""), QString("deg"), UAVObjectField::FLOAT32, AngleOfAttackElemNames, QStringList(), QString("")));
    QStringList AngleOfSlipElemNames;
    AngleOfSlipElemNames.append("0");
    fields.append( new UAVObjectField(QString("AngleOfSlip"), tr(""), QString("deg"), UAVObjectField::FLOAT32, AngleOfSlipElemNames, QStringList(), QString("")));

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
UAVObject::Metadata GroundTruth::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READONLY << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        0 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        0 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_GCS_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_LOGGING_UPDATE_MODE_SHIFT;
    metadata.flightTelemetryUpdatePeriod = 0;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void GroundTruth::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
GroundTruth::DataFields GroundTruth::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void GroundTruth::setData(const DataFields& data)
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

void GroundTruth::emitNotifications()
{
            //if (data.AccelerationXYZ[0] != oldData.AccelerationXYZ[0])
            emit AccelerationXYZ_0Changed(data.AccelerationXYZ[0]);
        //if (data.AccelerationXYZ[1] != oldData.AccelerationXYZ[1])
            emit AccelerationXYZ_1Changed(data.AccelerationXYZ[1]);
        //if (data.AccelerationXYZ[2] != oldData.AccelerationXYZ[2])
            emit AccelerationXYZ_2Changed(data.AccelerationXYZ[2]);
        //if (data.PositionNED[0] != oldData.PositionNED[0])
            emit PositionNED_0Changed(data.PositionNED[0]);
        //if (data.PositionNED[1] != oldData.PositionNED[1])
            emit PositionNED_1Changed(data.PositionNED[1]);
        //if (data.PositionNED[2] != oldData.PositionNED[2])
            emit PositionNED_2Changed(data.PositionNED[2]);
        //if (data.VelocityNED[0] != oldData.VelocityNED[0])
            emit VelocityNED_0Changed(data.VelocityNED[0]);
        //if (data.VelocityNED[1] != oldData.VelocityNED[1])
            emit VelocityNED_1Changed(data.VelocityNED[1]);
        //if (data.VelocityNED[2] != oldData.VelocityNED[2])
            emit VelocityNED_2Changed(data.VelocityNED[2]);
        //if (data.RPY[0] != oldData.RPY[0])
            emit RPY_0Changed(data.RPY[0]);
        //if (data.RPY[1] != oldData.RPY[1])
            emit RPY_1Changed(data.RPY[1]);
        //if (data.RPY[2] != oldData.RPY[2])
            emit RPY_2Changed(data.RPY[2]);
        //if (data.AngularRates[0] != oldData.AngularRates[0])
            emit AngularRates_0Changed(data.AngularRates[0]);
        //if (data.AngularRates[1] != oldData.AngularRates[1])
            emit AngularRates_1Changed(data.AngularRates[1]);
        //if (data.AngularRates[2] != oldData.AngularRates[2])
            emit AngularRates_2Changed(data.AngularRates[2]);
        //if (data.TrueAirspeed != oldData.TrueAirspeed)
            emit TrueAirspeedChanged(data.TrueAirspeed);
        //if (data.CalibratedAirspeed != oldData.CalibratedAirspeed)
            emit CalibratedAirspeedChanged(data.CalibratedAirspeed);
        //if (data.AngleOfAttack != oldData.AngleOfAttack)
            emit AngleOfAttackChanged(data.AngleOfAttack);
        //if (data.AngleOfSlip != oldData.AngleOfSlip)
            emit AngleOfSlipChanged(data.AngleOfSlip);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *GroundTruth::clone(quint32 instID)
{
    GroundTruth *obj = new GroundTruth();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *GroundTruth::dirtyClone()
{
    GroundTruth *obj = new GroundTruth();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
GroundTruth *GroundTruth::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<GroundTruth *>(objMngr->getObject(GroundTruth::OBJID, instID));
}

float GroundTruth::getAccelerationXYZ(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.AccelerationXYZ[index];
}
void GroundTruth::setAccelerationXYZ(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.AccelerationXYZ[index] != value;
   data.AccelerationXYZ[index] = value;
   mutex->unlock();
   if (changed) emit AccelerationXYZChanged(index,value);
}

float GroundTruth::getAccelerationXYZ_0() const
{
   QMutexLocker locker(mutex);
   return data.AccelerationXYZ[0];
}
void GroundTruth::setAccelerationXYZ_0(float value)
{
   mutex->lock();
   bool changed = data.AccelerationXYZ[0] != value;
   data.AccelerationXYZ[0] = value;
   mutex->unlock();
   if (changed) emit AccelerationXYZ_0Changed(value);
}

float GroundTruth::getAccelerationXYZ_1() const
{
   QMutexLocker locker(mutex);
   return data.AccelerationXYZ[1];
}
void GroundTruth::setAccelerationXYZ_1(float value)
{
   mutex->lock();
   bool changed = data.AccelerationXYZ[1] != value;
   data.AccelerationXYZ[1] = value;
   mutex->unlock();
   if (changed) emit AccelerationXYZ_1Changed(value);
}

float GroundTruth::getAccelerationXYZ_2() const
{
   QMutexLocker locker(mutex);
   return data.AccelerationXYZ[2];
}
void GroundTruth::setAccelerationXYZ_2(float value)
{
   mutex->lock();
   bool changed = data.AccelerationXYZ[2] != value;
   data.AccelerationXYZ[2] = value;
   mutex->unlock();
   if (changed) emit AccelerationXYZ_2Changed(value);
}

float GroundTruth::getPositionNED(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.PositionNED[index];
}
void GroundTruth::setPositionNED(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.PositionNED[index] != value;
   data.PositionNED[index] = value;
   mutex->unlock();
   if (changed) emit PositionNEDChanged(index,value);
}

float GroundTruth::getPositionNED_0() const
{
   QMutexLocker locker(mutex);
   return data.PositionNED[0];
}
void GroundTruth::setPositionNED_0(float value)
{
   mutex->lock();
   bool changed = data.PositionNED[0] != value;
   data.PositionNED[0] = value;
   mutex->unlock();
   if (changed) emit PositionNED_0Changed(value);
}

float GroundTruth::getPositionNED_1() const
{
   QMutexLocker locker(mutex);
   return data.PositionNED[1];
}
void GroundTruth::setPositionNED_1(float value)
{
   mutex->lock();
   bool changed = data.PositionNED[1] != value;
   data.PositionNED[1] = value;
   mutex->unlock();
   if (changed) emit PositionNED_1Changed(value);
}

float GroundTruth::getPositionNED_2() const
{
   QMutexLocker locker(mutex);
   return data.PositionNED[2];
}
void GroundTruth::setPositionNED_2(float value)
{
   mutex->lock();
   bool changed = data.PositionNED[2] != value;
   data.PositionNED[2] = value;
   mutex->unlock();
   if (changed) emit PositionNED_2Changed(value);
}

float GroundTruth::getVelocityNED(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.VelocityNED[index];
}
void GroundTruth::setVelocityNED(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.VelocityNED[index] != value;
   data.VelocityNED[index] = value;
   mutex->unlock();
   if (changed) emit VelocityNEDChanged(index,value);
}

float GroundTruth::getVelocityNED_0() const
{
   QMutexLocker locker(mutex);
   return data.VelocityNED[0];
}
void GroundTruth::setVelocityNED_0(float value)
{
   mutex->lock();
   bool changed = data.VelocityNED[0] != value;
   data.VelocityNED[0] = value;
   mutex->unlock();
   if (changed) emit VelocityNED_0Changed(value);
}

float GroundTruth::getVelocityNED_1() const
{
   QMutexLocker locker(mutex);
   return data.VelocityNED[1];
}
void GroundTruth::setVelocityNED_1(float value)
{
   mutex->lock();
   bool changed = data.VelocityNED[1] != value;
   data.VelocityNED[1] = value;
   mutex->unlock();
   if (changed) emit VelocityNED_1Changed(value);
}

float GroundTruth::getVelocityNED_2() const
{
   QMutexLocker locker(mutex);
   return data.VelocityNED[2];
}
void GroundTruth::setVelocityNED_2(float value)
{
   mutex->lock();
   bool changed = data.VelocityNED[2] != value;
   data.VelocityNED[2] = value;
   mutex->unlock();
   if (changed) emit VelocityNED_2Changed(value);
}

float GroundTruth::getRPY(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.RPY[index];
}
void GroundTruth::setRPY(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.RPY[index] != value;
   data.RPY[index] = value;
   mutex->unlock();
   if (changed) emit RPYChanged(index,value);
}

float GroundTruth::getRPY_0() const
{
   QMutexLocker locker(mutex);
   return data.RPY[0];
}
void GroundTruth::setRPY_0(float value)
{
   mutex->lock();
   bool changed = data.RPY[0] != value;
   data.RPY[0] = value;
   mutex->unlock();
   if (changed) emit RPY_0Changed(value);
}

float GroundTruth::getRPY_1() const
{
   QMutexLocker locker(mutex);
   return data.RPY[1];
}
void GroundTruth::setRPY_1(float value)
{
   mutex->lock();
   bool changed = data.RPY[1] != value;
   data.RPY[1] = value;
   mutex->unlock();
   if (changed) emit RPY_1Changed(value);
}

float GroundTruth::getRPY_2() const
{
   QMutexLocker locker(mutex);
   return data.RPY[2];
}
void GroundTruth::setRPY_2(float value)
{
   mutex->lock();
   bool changed = data.RPY[2] != value;
   data.RPY[2] = value;
   mutex->unlock();
   if (changed) emit RPY_2Changed(value);
}

float GroundTruth::getAngularRates(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.AngularRates[index];
}
void GroundTruth::setAngularRates(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.AngularRates[index] != value;
   data.AngularRates[index] = value;
   mutex->unlock();
   if (changed) emit AngularRatesChanged(index,value);
}

float GroundTruth::getAngularRates_0() const
{
   QMutexLocker locker(mutex);
   return data.AngularRates[0];
}
void GroundTruth::setAngularRates_0(float value)
{
   mutex->lock();
   bool changed = data.AngularRates[0] != value;
   data.AngularRates[0] = value;
   mutex->unlock();
   if (changed) emit AngularRates_0Changed(value);
}

float GroundTruth::getAngularRates_1() const
{
   QMutexLocker locker(mutex);
   return data.AngularRates[1];
}
void GroundTruth::setAngularRates_1(float value)
{
   mutex->lock();
   bool changed = data.AngularRates[1] != value;
   data.AngularRates[1] = value;
   mutex->unlock();
   if (changed) emit AngularRates_1Changed(value);
}

float GroundTruth::getAngularRates_2() const
{
   QMutexLocker locker(mutex);
   return data.AngularRates[2];
}
void GroundTruth::setAngularRates_2(float value)
{
   mutex->lock();
   bool changed = data.AngularRates[2] != value;
   data.AngularRates[2] = value;
   mutex->unlock();
   if (changed) emit AngularRates_2Changed(value);
}

float GroundTruth::getTrueAirspeed() const
{
   QMutexLocker locker(mutex);
   return data.TrueAirspeed;
}
void GroundTruth::setTrueAirspeed(float value)
{
   mutex->lock();
   bool changed = data.TrueAirspeed != value;
   data.TrueAirspeed = value;
   mutex->unlock();
   if (changed) emit TrueAirspeedChanged(value);
}

float GroundTruth::getCalibratedAirspeed() const
{
   QMutexLocker locker(mutex);
   return data.CalibratedAirspeed;
}
void GroundTruth::setCalibratedAirspeed(float value)
{
   mutex->lock();
   bool changed = data.CalibratedAirspeed != value;
   data.CalibratedAirspeed = value;
   mutex->unlock();
   if (changed) emit CalibratedAirspeedChanged(value);
}

float GroundTruth::getAngleOfAttack() const
{
   QMutexLocker locker(mutex);
   return data.AngleOfAttack;
}
void GroundTruth::setAngleOfAttack(float value)
{
   mutex->lock();
   bool changed = data.AngleOfAttack != value;
   data.AngleOfAttack = value;
   mutex->unlock();
   if (changed) emit AngleOfAttackChanged(value);
}

float GroundTruth::getAngleOfSlip() const
{
   QMutexLocker locker(mutex);
   return data.AngleOfSlip;
}
void GroundTruth::setAngleOfSlip(float value)
{
   mutex->lock();
   bool changed = data.AngleOfSlip != value;
   data.AngleOfSlip = value;
   mutex->unlock();
   if (changed) emit AngleOfSlipChanged(value);
}


