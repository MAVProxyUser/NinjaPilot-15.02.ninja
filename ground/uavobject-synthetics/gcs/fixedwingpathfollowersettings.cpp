/**
 ******************************************************************************
 *
 * @file       fixedwingpathfollowersettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: fixedwingpathfollowersettings.xml.
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

#include "fixedwingpathfollowersettings.h"
#include "uavobjectfield.h"

const QString FixedWingPathFollowerSettings::NAME = QString("FixedWingPathFollowerSettings");
const QString FixedWingPathFollowerSettings::DESCRIPTION = QString("Settings for the @ref FixedWingPathFollowerModule");
const QString FixedWingPathFollowerSettings::CATEGORY = QString("Control");

/**
 * Constructor
 */
FixedWingPathFollowerSettings::FixedWingPathFollowerSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList HorizontalVelMaxElemNames;
    HorizontalVelMaxElemNames.append("0");
    fields.append( new UAVObjectField(QString("HorizontalVelMax"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, HorizontalVelMaxElemNames, QStringList(), QString("")));
    QStringList HorizontalVelMinElemNames;
    HorizontalVelMinElemNames.append("0");
    fields.append( new UAVObjectField(QString("HorizontalVelMin"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, HorizontalVelMinElemNames, QStringList(), QString("")));
    QStringList VerticalVelMaxElemNames;
    VerticalVelMaxElemNames.append("0");
    fields.append( new UAVObjectField(QString("VerticalVelMax"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, VerticalVelMaxElemNames, QStringList(), QString("")));
    QStringList CourseFeedForwardElemNames;
    CourseFeedForwardElemNames.append("0");
    fields.append( new UAVObjectField(QString("CourseFeedForward"), tr(""), QString("s"), UAVObjectField::FLOAT32, CourseFeedForwardElemNames, QStringList(), QString("")));
    QStringList ReverseCourseOverlapElemNames;
    ReverseCourseOverlapElemNames.append("0");
    fields.append( new UAVObjectField(QString("ReverseCourseOverlap"), tr(""), QString("deg"), UAVObjectField::FLOAT32, ReverseCourseOverlapElemNames, QStringList(), QString("")));
    QStringList HorizontalPosPElemNames;
    HorizontalPosPElemNames.append("0");
    fields.append( new UAVObjectField(QString("HorizontalPosP"), tr(""), QString("(m/s)/m"), UAVObjectField::FLOAT32, HorizontalPosPElemNames, QStringList(), QString("")));
    QStringList VerticalPosPElemNames;
    VerticalPosPElemNames.append("0");
    fields.append( new UAVObjectField(QString("VerticalPosP"), tr(""), QString("(m/s)/m"), UAVObjectField::FLOAT32, VerticalPosPElemNames, QStringList(), QString("")));
    QStringList CoursePIElemNames;
    CoursePIElemNames.append("Kp");
    CoursePIElemNames.append("Ki");
    CoursePIElemNames.append("ILimit");
    fields.append( new UAVObjectField(QString("CoursePI"), tr(""), QString("deg/deg"), UAVObjectField::FLOAT32, CoursePIElemNames, QStringList(), QString("")));
    QStringList SpeedPIElemNames;
    SpeedPIElemNames.append("Kp");
    SpeedPIElemNames.append("Ki");
    SpeedPIElemNames.append("ILimit");
    fields.append( new UAVObjectField(QString("SpeedPI"), tr(""), QString("deg / (m/s)"), UAVObjectField::FLOAT32, SpeedPIElemNames, QStringList(), QString("")));
    QStringList VerticalToPitchCrossFeedElemNames;
    VerticalToPitchCrossFeedElemNames.append("Kp");
    VerticalToPitchCrossFeedElemNames.append("Max");
    fields.append( new UAVObjectField(QString("VerticalToPitchCrossFeed"), tr(""), QString("deg / (m/s)"), UAVObjectField::FLOAT32, VerticalToPitchCrossFeedElemNames, QStringList(), QString("")));
    QStringList AirspeedToPowerCrossFeedElemNames;
    AirspeedToPowerCrossFeedElemNames.append("Kp");
    AirspeedToPowerCrossFeedElemNames.append("Max");
    fields.append( new UAVObjectField(QString("AirspeedToPowerCrossFeed"), tr(""), QString("1 / (m/s)"), UAVObjectField::FLOAT32, AirspeedToPowerCrossFeedElemNames, QStringList(), QString("")));
    QStringList PowerPIElemNames;
    PowerPIElemNames.append("Kp");
    PowerPIElemNames.append("Ki");
    PowerPIElemNames.append("ILimit");
    fields.append( new UAVObjectField(QString("PowerPI"), tr(""), QString("1/(m/s)"), UAVObjectField::FLOAT32, PowerPIElemNames, QStringList(), QString("")));
    QStringList RollLimitElemNames;
    RollLimitElemNames.append("Min");
    RollLimitElemNames.append("Neutral");
    RollLimitElemNames.append("Max");
    fields.append( new UAVObjectField(QString("RollLimit"), tr(""), QString("deg"), UAVObjectField::FLOAT32, RollLimitElemNames, QStringList(), QString("")));
    QStringList PitchLimitElemNames;
    PitchLimitElemNames.append("Min");
    PitchLimitElemNames.append("Neutral");
    PitchLimitElemNames.append("Max");
    fields.append( new UAVObjectField(QString("PitchLimit"), tr(""), QString("deg"), UAVObjectField::FLOAT32, PitchLimitElemNames, QStringList(), QString("")));
    QStringList ThrustLimitElemNames;
    ThrustLimitElemNames.append("Min");
    ThrustLimitElemNames.append("Neutral");
    ThrustLimitElemNames.append("Max");
    fields.append( new UAVObjectField(QString("ThrustLimit"), tr(""), QString(""), UAVObjectField::FLOAT32, ThrustLimitElemNames, QStringList(), QString("")));
    QStringList SafetymarginsElemNames;
    SafetymarginsElemNames.append("Wind");
    SafetymarginsElemNames.append("Stallspeed");
    SafetymarginsElemNames.append("Lowspeed");
    SafetymarginsElemNames.append("Highspeed");
    SafetymarginsElemNames.append("Overspeed");
    SafetymarginsElemNames.append("Lowpower");
    SafetymarginsElemNames.append("Highpower");
    SafetymarginsElemNames.append("Pitchcontrol");
    fields.append( new UAVObjectField(QString("Safetymargins"), tr(""), QString(""), UAVObjectField::FLOAT32, SafetymarginsElemNames, QStringList(), QString("")));
    QStringList UpdatePeriodElemNames;
    UpdatePeriodElemNames.append("0");
    fields.append( new UAVObjectField(QString("UpdatePeriod"), tr(""), QString("ms"), UAVObjectField::INT32, UpdatePeriodElemNames, QStringList(), QString("")));

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
UAVObject::Metadata FixedWingPathFollowerSettings::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        1 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        1 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_ONCHANGE << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_ONCHANGE << UAVOBJ_GCS_TELEMETRY_UPDATE_MODE_SHIFT |
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
void FixedWingPathFollowerSettings::setDefaultFieldValues()
{
    data.HorizontalVelMax = 20;
    data.HorizontalVelMin = 10;
    data.VerticalVelMax = 10;
    data.CourseFeedForward = 3;
    data.ReverseCourseOverlap = 20;
    data.HorizontalPosP = 0.2;
    data.VerticalPosP = 0.4;
    data.CoursePI[0] = 0.2;
    data.CoursePI[1] = 0;
    data.CoursePI[2] = 0;
    data.SpeedPI[0] = 2.5;
    data.SpeedPI[1] = 0.25;
    data.SpeedPI[2] = 10;
    data.VerticalToPitchCrossFeed[0] = 5;
    data.VerticalToPitchCrossFeed[1] = 10;
    data.AirspeedToPowerCrossFeed[0] = 0.2;
    data.AirspeedToPowerCrossFeed[1] = 1;
    data.PowerPI[0] = 0.01;
    data.PowerPI[1] = 0.05;
    data.PowerPI[2] = 0.5;
    data.RollLimit[0] = -45;
    data.RollLimit[1] = 0;
    data.RollLimit[2] = 45;
    data.PitchLimit[0] = -10;
    data.PitchLimit[1] = 5;
    data.PitchLimit[2] = 20;
    data.ThrustLimit[0] = 0.1;
    data.ThrustLimit[1] = 0.5;
    data.ThrustLimit[2] = 0.9;
    data.Safetymargins[0] = 90;
    data.Safetymargins[1] = 1;
    data.Safetymargins[2] = 0.5;
    data.Safetymargins[3] = 1.5;
    data.Safetymargins[4] = 1;
    data.Safetymargins[5] = 1;
    data.Safetymargins[6] = 0;
    data.Safetymargins[7] = 1;
    data.UpdatePeriod = 100;

}

/**
 * Get the object data fields
 */
FixedWingPathFollowerSettings::DataFields FixedWingPathFollowerSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void FixedWingPathFollowerSettings::setData(const DataFields& data)
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

void FixedWingPathFollowerSettings::emitNotifications()
{
            //if (data.HorizontalVelMax != oldData.HorizontalVelMax)
            emit HorizontalVelMaxChanged(data.HorizontalVelMax);
        //if (data.HorizontalVelMin != oldData.HorizontalVelMin)
            emit HorizontalVelMinChanged(data.HorizontalVelMin);
        //if (data.VerticalVelMax != oldData.VerticalVelMax)
            emit VerticalVelMaxChanged(data.VerticalVelMax);
        //if (data.CourseFeedForward != oldData.CourseFeedForward)
            emit CourseFeedForwardChanged(data.CourseFeedForward);
        //if (data.ReverseCourseOverlap != oldData.ReverseCourseOverlap)
            emit ReverseCourseOverlapChanged(data.ReverseCourseOverlap);
        //if (data.HorizontalPosP != oldData.HorizontalPosP)
            emit HorizontalPosPChanged(data.HorizontalPosP);
        //if (data.VerticalPosP != oldData.VerticalPosP)
            emit VerticalPosPChanged(data.VerticalPosP);
        //if (data.CoursePI[0] != oldData.CoursePI[0])
            emit CoursePI_KpChanged(data.CoursePI[0]);
        //if (data.CoursePI[1] != oldData.CoursePI[1])
            emit CoursePI_KiChanged(data.CoursePI[1]);
        //if (data.CoursePI[2] != oldData.CoursePI[2])
            emit CoursePI_ILimitChanged(data.CoursePI[2]);
        //if (data.SpeedPI[0] != oldData.SpeedPI[0])
            emit SpeedPI_KpChanged(data.SpeedPI[0]);
        //if (data.SpeedPI[1] != oldData.SpeedPI[1])
            emit SpeedPI_KiChanged(data.SpeedPI[1]);
        //if (data.SpeedPI[2] != oldData.SpeedPI[2])
            emit SpeedPI_ILimitChanged(data.SpeedPI[2]);
        //if (data.VerticalToPitchCrossFeed[0] != oldData.VerticalToPitchCrossFeed[0])
            emit VerticalToPitchCrossFeed_KpChanged(data.VerticalToPitchCrossFeed[0]);
        //if (data.VerticalToPitchCrossFeed[1] != oldData.VerticalToPitchCrossFeed[1])
            emit VerticalToPitchCrossFeed_MaxChanged(data.VerticalToPitchCrossFeed[1]);
        //if (data.AirspeedToPowerCrossFeed[0] != oldData.AirspeedToPowerCrossFeed[0])
            emit AirspeedToPowerCrossFeed_KpChanged(data.AirspeedToPowerCrossFeed[0]);
        //if (data.AirspeedToPowerCrossFeed[1] != oldData.AirspeedToPowerCrossFeed[1])
            emit AirspeedToPowerCrossFeed_MaxChanged(data.AirspeedToPowerCrossFeed[1]);
        //if (data.PowerPI[0] != oldData.PowerPI[0])
            emit PowerPI_KpChanged(data.PowerPI[0]);
        //if (data.PowerPI[1] != oldData.PowerPI[1])
            emit PowerPI_KiChanged(data.PowerPI[1]);
        //if (data.PowerPI[2] != oldData.PowerPI[2])
            emit PowerPI_ILimitChanged(data.PowerPI[2]);
        //if (data.RollLimit[0] != oldData.RollLimit[0])
            emit RollLimit_MinChanged(data.RollLimit[0]);
        //if (data.RollLimit[1] != oldData.RollLimit[1])
            emit RollLimit_NeutralChanged(data.RollLimit[1]);
        //if (data.RollLimit[2] != oldData.RollLimit[2])
            emit RollLimit_MaxChanged(data.RollLimit[2]);
        //if (data.PitchLimit[0] != oldData.PitchLimit[0])
            emit PitchLimit_MinChanged(data.PitchLimit[0]);
        //if (data.PitchLimit[1] != oldData.PitchLimit[1])
            emit PitchLimit_NeutralChanged(data.PitchLimit[1]);
        //if (data.PitchLimit[2] != oldData.PitchLimit[2])
            emit PitchLimit_MaxChanged(data.PitchLimit[2]);
        //if (data.ThrustLimit[0] != oldData.ThrustLimit[0])
            emit ThrustLimit_MinChanged(data.ThrustLimit[0]);
        //if (data.ThrustLimit[1] != oldData.ThrustLimit[1])
            emit ThrustLimit_NeutralChanged(data.ThrustLimit[1]);
        //if (data.ThrustLimit[2] != oldData.ThrustLimit[2])
            emit ThrustLimit_MaxChanged(data.ThrustLimit[2]);
        //if (data.Safetymargins[0] != oldData.Safetymargins[0])
            emit Safetymargins_WindChanged(data.Safetymargins[0]);
        //if (data.Safetymargins[1] != oldData.Safetymargins[1])
            emit Safetymargins_StallspeedChanged(data.Safetymargins[1]);
        //if (data.Safetymargins[2] != oldData.Safetymargins[2])
            emit Safetymargins_LowspeedChanged(data.Safetymargins[2]);
        //if (data.Safetymargins[3] != oldData.Safetymargins[3])
            emit Safetymargins_HighspeedChanged(data.Safetymargins[3]);
        //if (data.Safetymargins[4] != oldData.Safetymargins[4])
            emit Safetymargins_OverspeedChanged(data.Safetymargins[4]);
        //if (data.Safetymargins[5] != oldData.Safetymargins[5])
            emit Safetymargins_LowpowerChanged(data.Safetymargins[5]);
        //if (data.Safetymargins[6] != oldData.Safetymargins[6])
            emit Safetymargins_HighpowerChanged(data.Safetymargins[6]);
        //if (data.Safetymargins[7] != oldData.Safetymargins[7])
            emit Safetymargins_PitchcontrolChanged(data.Safetymargins[7]);
        //if (data.UpdatePeriod != oldData.UpdatePeriod)
            emit UpdatePeriodChanged(data.UpdatePeriod);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *FixedWingPathFollowerSettings::clone(quint32 instID)
{
    FixedWingPathFollowerSettings *obj = new FixedWingPathFollowerSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *FixedWingPathFollowerSettings::dirtyClone()
{
    FixedWingPathFollowerSettings *obj = new FixedWingPathFollowerSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
FixedWingPathFollowerSettings *FixedWingPathFollowerSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<FixedWingPathFollowerSettings *>(objMngr->getObject(FixedWingPathFollowerSettings::OBJID, instID));
}

float FixedWingPathFollowerSettings::getHorizontalVelMax() const
{
   QMutexLocker locker(mutex);
   return data.HorizontalVelMax;
}
void FixedWingPathFollowerSettings::setHorizontalVelMax(float value)
{
   mutex->lock();
   bool changed = data.HorizontalVelMax != value;
   data.HorizontalVelMax = value;
   mutex->unlock();
   if (changed) emit HorizontalVelMaxChanged(value);
}

float FixedWingPathFollowerSettings::getHorizontalVelMin() const
{
   QMutexLocker locker(mutex);
   return data.HorizontalVelMin;
}
void FixedWingPathFollowerSettings::setHorizontalVelMin(float value)
{
   mutex->lock();
   bool changed = data.HorizontalVelMin != value;
   data.HorizontalVelMin = value;
   mutex->unlock();
   if (changed) emit HorizontalVelMinChanged(value);
}

float FixedWingPathFollowerSettings::getVerticalVelMax() const
{
   QMutexLocker locker(mutex);
   return data.VerticalVelMax;
}
void FixedWingPathFollowerSettings::setVerticalVelMax(float value)
{
   mutex->lock();
   bool changed = data.VerticalVelMax != value;
   data.VerticalVelMax = value;
   mutex->unlock();
   if (changed) emit VerticalVelMaxChanged(value);
}

float FixedWingPathFollowerSettings::getCourseFeedForward() const
{
   QMutexLocker locker(mutex);
   return data.CourseFeedForward;
}
void FixedWingPathFollowerSettings::setCourseFeedForward(float value)
{
   mutex->lock();
   bool changed = data.CourseFeedForward != value;
   data.CourseFeedForward = value;
   mutex->unlock();
   if (changed) emit CourseFeedForwardChanged(value);
}

float FixedWingPathFollowerSettings::getReverseCourseOverlap() const
{
   QMutexLocker locker(mutex);
   return data.ReverseCourseOverlap;
}
void FixedWingPathFollowerSettings::setReverseCourseOverlap(float value)
{
   mutex->lock();
   bool changed = data.ReverseCourseOverlap != value;
   data.ReverseCourseOverlap = value;
   mutex->unlock();
   if (changed) emit ReverseCourseOverlapChanged(value);
}

float FixedWingPathFollowerSettings::getHorizontalPosP() const
{
   QMutexLocker locker(mutex);
   return data.HorizontalPosP;
}
void FixedWingPathFollowerSettings::setHorizontalPosP(float value)
{
   mutex->lock();
   bool changed = data.HorizontalPosP != value;
   data.HorizontalPosP = value;
   mutex->unlock();
   if (changed) emit HorizontalPosPChanged(value);
}

float FixedWingPathFollowerSettings::getVerticalPosP() const
{
   QMutexLocker locker(mutex);
   return data.VerticalPosP;
}
void FixedWingPathFollowerSettings::setVerticalPosP(float value)
{
   mutex->lock();
   bool changed = data.VerticalPosP != value;
   data.VerticalPosP = value;
   mutex->unlock();
   if (changed) emit VerticalPosPChanged(value);
}

float FixedWingPathFollowerSettings::getCoursePI(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.CoursePI[index];
}
void FixedWingPathFollowerSettings::setCoursePI(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.CoursePI[index] != value;
   data.CoursePI[index] = value;
   mutex->unlock();
   if (changed) emit CoursePIChanged(index,value);
}

float FixedWingPathFollowerSettings::getCoursePI_Kp() const
{
   QMutexLocker locker(mutex);
   return data.CoursePI[0];
}
void FixedWingPathFollowerSettings::setCoursePI_Kp(float value)
{
   mutex->lock();
   bool changed = data.CoursePI[0] != value;
   data.CoursePI[0] = value;
   mutex->unlock();
   if (changed) emit CoursePI_KpChanged(value);
}

float FixedWingPathFollowerSettings::getCoursePI_Ki() const
{
   QMutexLocker locker(mutex);
   return data.CoursePI[1];
}
void FixedWingPathFollowerSettings::setCoursePI_Ki(float value)
{
   mutex->lock();
   bool changed = data.CoursePI[1] != value;
   data.CoursePI[1] = value;
   mutex->unlock();
   if (changed) emit CoursePI_KiChanged(value);
}

float FixedWingPathFollowerSettings::getCoursePI_ILimit() const
{
   QMutexLocker locker(mutex);
   return data.CoursePI[2];
}
void FixedWingPathFollowerSettings::setCoursePI_ILimit(float value)
{
   mutex->lock();
   bool changed = data.CoursePI[2] != value;
   data.CoursePI[2] = value;
   mutex->unlock();
   if (changed) emit CoursePI_ILimitChanged(value);
}

float FixedWingPathFollowerSettings::getSpeedPI(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.SpeedPI[index];
}
void FixedWingPathFollowerSettings::setSpeedPI(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.SpeedPI[index] != value;
   data.SpeedPI[index] = value;
   mutex->unlock();
   if (changed) emit SpeedPIChanged(index,value);
}

float FixedWingPathFollowerSettings::getSpeedPI_Kp() const
{
   QMutexLocker locker(mutex);
   return data.SpeedPI[0];
}
void FixedWingPathFollowerSettings::setSpeedPI_Kp(float value)
{
   mutex->lock();
   bool changed = data.SpeedPI[0] != value;
   data.SpeedPI[0] = value;
   mutex->unlock();
   if (changed) emit SpeedPI_KpChanged(value);
}

float FixedWingPathFollowerSettings::getSpeedPI_Ki() const
{
   QMutexLocker locker(mutex);
   return data.SpeedPI[1];
}
void FixedWingPathFollowerSettings::setSpeedPI_Ki(float value)
{
   mutex->lock();
   bool changed = data.SpeedPI[1] != value;
   data.SpeedPI[1] = value;
   mutex->unlock();
   if (changed) emit SpeedPI_KiChanged(value);
}

float FixedWingPathFollowerSettings::getSpeedPI_ILimit() const
{
   QMutexLocker locker(mutex);
   return data.SpeedPI[2];
}
void FixedWingPathFollowerSettings::setSpeedPI_ILimit(float value)
{
   mutex->lock();
   bool changed = data.SpeedPI[2] != value;
   data.SpeedPI[2] = value;
   mutex->unlock();
   if (changed) emit SpeedPI_ILimitChanged(value);
}

float FixedWingPathFollowerSettings::getVerticalToPitchCrossFeed(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.VerticalToPitchCrossFeed[index];
}
void FixedWingPathFollowerSettings::setVerticalToPitchCrossFeed(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.VerticalToPitchCrossFeed[index] != value;
   data.VerticalToPitchCrossFeed[index] = value;
   mutex->unlock();
   if (changed) emit VerticalToPitchCrossFeedChanged(index,value);
}

float FixedWingPathFollowerSettings::getVerticalToPitchCrossFeed_Kp() const
{
   QMutexLocker locker(mutex);
   return data.VerticalToPitchCrossFeed[0];
}
void FixedWingPathFollowerSettings::setVerticalToPitchCrossFeed_Kp(float value)
{
   mutex->lock();
   bool changed = data.VerticalToPitchCrossFeed[0] != value;
   data.VerticalToPitchCrossFeed[0] = value;
   mutex->unlock();
   if (changed) emit VerticalToPitchCrossFeed_KpChanged(value);
}

float FixedWingPathFollowerSettings::getVerticalToPitchCrossFeed_Max() const
{
   QMutexLocker locker(mutex);
   return data.VerticalToPitchCrossFeed[1];
}
void FixedWingPathFollowerSettings::setVerticalToPitchCrossFeed_Max(float value)
{
   mutex->lock();
   bool changed = data.VerticalToPitchCrossFeed[1] != value;
   data.VerticalToPitchCrossFeed[1] = value;
   mutex->unlock();
   if (changed) emit VerticalToPitchCrossFeed_MaxChanged(value);
}

float FixedWingPathFollowerSettings::getAirspeedToPowerCrossFeed(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.AirspeedToPowerCrossFeed[index];
}
void FixedWingPathFollowerSettings::setAirspeedToPowerCrossFeed(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.AirspeedToPowerCrossFeed[index] != value;
   data.AirspeedToPowerCrossFeed[index] = value;
   mutex->unlock();
   if (changed) emit AirspeedToPowerCrossFeedChanged(index,value);
}

float FixedWingPathFollowerSettings::getAirspeedToPowerCrossFeed_Kp() const
{
   QMutexLocker locker(mutex);
   return data.AirspeedToPowerCrossFeed[0];
}
void FixedWingPathFollowerSettings::setAirspeedToPowerCrossFeed_Kp(float value)
{
   mutex->lock();
   bool changed = data.AirspeedToPowerCrossFeed[0] != value;
   data.AirspeedToPowerCrossFeed[0] = value;
   mutex->unlock();
   if (changed) emit AirspeedToPowerCrossFeed_KpChanged(value);
}

float FixedWingPathFollowerSettings::getAirspeedToPowerCrossFeed_Max() const
{
   QMutexLocker locker(mutex);
   return data.AirspeedToPowerCrossFeed[1];
}
void FixedWingPathFollowerSettings::setAirspeedToPowerCrossFeed_Max(float value)
{
   mutex->lock();
   bool changed = data.AirspeedToPowerCrossFeed[1] != value;
   data.AirspeedToPowerCrossFeed[1] = value;
   mutex->unlock();
   if (changed) emit AirspeedToPowerCrossFeed_MaxChanged(value);
}

float FixedWingPathFollowerSettings::getPowerPI(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.PowerPI[index];
}
void FixedWingPathFollowerSettings::setPowerPI(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.PowerPI[index] != value;
   data.PowerPI[index] = value;
   mutex->unlock();
   if (changed) emit PowerPIChanged(index,value);
}

float FixedWingPathFollowerSettings::getPowerPI_Kp() const
{
   QMutexLocker locker(mutex);
   return data.PowerPI[0];
}
void FixedWingPathFollowerSettings::setPowerPI_Kp(float value)
{
   mutex->lock();
   bool changed = data.PowerPI[0] != value;
   data.PowerPI[0] = value;
   mutex->unlock();
   if (changed) emit PowerPI_KpChanged(value);
}

float FixedWingPathFollowerSettings::getPowerPI_Ki() const
{
   QMutexLocker locker(mutex);
   return data.PowerPI[1];
}
void FixedWingPathFollowerSettings::setPowerPI_Ki(float value)
{
   mutex->lock();
   bool changed = data.PowerPI[1] != value;
   data.PowerPI[1] = value;
   mutex->unlock();
   if (changed) emit PowerPI_KiChanged(value);
}

float FixedWingPathFollowerSettings::getPowerPI_ILimit() const
{
   QMutexLocker locker(mutex);
   return data.PowerPI[2];
}
void FixedWingPathFollowerSettings::setPowerPI_ILimit(float value)
{
   mutex->lock();
   bool changed = data.PowerPI[2] != value;
   data.PowerPI[2] = value;
   mutex->unlock();
   if (changed) emit PowerPI_ILimitChanged(value);
}

float FixedWingPathFollowerSettings::getRollLimit(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.RollLimit[index];
}
void FixedWingPathFollowerSettings::setRollLimit(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.RollLimit[index] != value;
   data.RollLimit[index] = value;
   mutex->unlock();
   if (changed) emit RollLimitChanged(index,value);
}

float FixedWingPathFollowerSettings::getRollLimit_Min() const
{
   QMutexLocker locker(mutex);
   return data.RollLimit[0];
}
void FixedWingPathFollowerSettings::setRollLimit_Min(float value)
{
   mutex->lock();
   bool changed = data.RollLimit[0] != value;
   data.RollLimit[0] = value;
   mutex->unlock();
   if (changed) emit RollLimit_MinChanged(value);
}

float FixedWingPathFollowerSettings::getRollLimit_Neutral() const
{
   QMutexLocker locker(mutex);
   return data.RollLimit[1];
}
void FixedWingPathFollowerSettings::setRollLimit_Neutral(float value)
{
   mutex->lock();
   bool changed = data.RollLimit[1] != value;
   data.RollLimit[1] = value;
   mutex->unlock();
   if (changed) emit RollLimit_NeutralChanged(value);
}

float FixedWingPathFollowerSettings::getRollLimit_Max() const
{
   QMutexLocker locker(mutex);
   return data.RollLimit[2];
}
void FixedWingPathFollowerSettings::setRollLimit_Max(float value)
{
   mutex->lock();
   bool changed = data.RollLimit[2] != value;
   data.RollLimit[2] = value;
   mutex->unlock();
   if (changed) emit RollLimit_MaxChanged(value);
}

float FixedWingPathFollowerSettings::getPitchLimit(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.PitchLimit[index];
}
void FixedWingPathFollowerSettings::setPitchLimit(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.PitchLimit[index] != value;
   data.PitchLimit[index] = value;
   mutex->unlock();
   if (changed) emit PitchLimitChanged(index,value);
}

float FixedWingPathFollowerSettings::getPitchLimit_Min() const
{
   QMutexLocker locker(mutex);
   return data.PitchLimit[0];
}
void FixedWingPathFollowerSettings::setPitchLimit_Min(float value)
{
   mutex->lock();
   bool changed = data.PitchLimit[0] != value;
   data.PitchLimit[0] = value;
   mutex->unlock();
   if (changed) emit PitchLimit_MinChanged(value);
}

float FixedWingPathFollowerSettings::getPitchLimit_Neutral() const
{
   QMutexLocker locker(mutex);
   return data.PitchLimit[1];
}
void FixedWingPathFollowerSettings::setPitchLimit_Neutral(float value)
{
   mutex->lock();
   bool changed = data.PitchLimit[1] != value;
   data.PitchLimit[1] = value;
   mutex->unlock();
   if (changed) emit PitchLimit_NeutralChanged(value);
}

float FixedWingPathFollowerSettings::getPitchLimit_Max() const
{
   QMutexLocker locker(mutex);
   return data.PitchLimit[2];
}
void FixedWingPathFollowerSettings::setPitchLimit_Max(float value)
{
   mutex->lock();
   bool changed = data.PitchLimit[2] != value;
   data.PitchLimit[2] = value;
   mutex->unlock();
   if (changed) emit PitchLimit_MaxChanged(value);
}

float FixedWingPathFollowerSettings::getThrustLimit(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ThrustLimit[index];
}
void FixedWingPathFollowerSettings::setThrustLimit(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.ThrustLimit[index] != value;
   data.ThrustLimit[index] = value;
   mutex->unlock();
   if (changed) emit ThrustLimitChanged(index,value);
}

float FixedWingPathFollowerSettings::getThrustLimit_Min() const
{
   QMutexLocker locker(mutex);
   return data.ThrustLimit[0];
}
void FixedWingPathFollowerSettings::setThrustLimit_Min(float value)
{
   mutex->lock();
   bool changed = data.ThrustLimit[0] != value;
   data.ThrustLimit[0] = value;
   mutex->unlock();
   if (changed) emit ThrustLimit_MinChanged(value);
}

float FixedWingPathFollowerSettings::getThrustLimit_Neutral() const
{
   QMutexLocker locker(mutex);
   return data.ThrustLimit[1];
}
void FixedWingPathFollowerSettings::setThrustLimit_Neutral(float value)
{
   mutex->lock();
   bool changed = data.ThrustLimit[1] != value;
   data.ThrustLimit[1] = value;
   mutex->unlock();
   if (changed) emit ThrustLimit_NeutralChanged(value);
}

float FixedWingPathFollowerSettings::getThrustLimit_Max() const
{
   QMutexLocker locker(mutex);
   return data.ThrustLimit[2];
}
void FixedWingPathFollowerSettings::setThrustLimit_Max(float value)
{
   mutex->lock();
   bool changed = data.ThrustLimit[2] != value;
   data.ThrustLimit[2] = value;
   mutex->unlock();
   if (changed) emit ThrustLimit_MaxChanged(value);
}

float FixedWingPathFollowerSettings::getSafetymargins(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Safetymargins[index];
}
void FixedWingPathFollowerSettings::setSafetymargins(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.Safetymargins[index] != value;
   data.Safetymargins[index] = value;
   mutex->unlock();
   if (changed) emit SafetymarginsChanged(index,value);
}

float FixedWingPathFollowerSettings::getSafetymargins_Wind() const
{
   QMutexLocker locker(mutex);
   return data.Safetymargins[0];
}
void FixedWingPathFollowerSettings::setSafetymargins_Wind(float value)
{
   mutex->lock();
   bool changed = data.Safetymargins[0] != value;
   data.Safetymargins[0] = value;
   mutex->unlock();
   if (changed) emit Safetymargins_WindChanged(value);
}

float FixedWingPathFollowerSettings::getSafetymargins_Stallspeed() const
{
   QMutexLocker locker(mutex);
   return data.Safetymargins[1];
}
void FixedWingPathFollowerSettings::setSafetymargins_Stallspeed(float value)
{
   mutex->lock();
   bool changed = data.Safetymargins[1] != value;
   data.Safetymargins[1] = value;
   mutex->unlock();
   if (changed) emit Safetymargins_StallspeedChanged(value);
}

float FixedWingPathFollowerSettings::getSafetymargins_Lowspeed() const
{
   QMutexLocker locker(mutex);
   return data.Safetymargins[2];
}
void FixedWingPathFollowerSettings::setSafetymargins_Lowspeed(float value)
{
   mutex->lock();
   bool changed = data.Safetymargins[2] != value;
   data.Safetymargins[2] = value;
   mutex->unlock();
   if (changed) emit Safetymargins_LowspeedChanged(value);
}

float FixedWingPathFollowerSettings::getSafetymargins_Highspeed() const
{
   QMutexLocker locker(mutex);
   return data.Safetymargins[3];
}
void FixedWingPathFollowerSettings::setSafetymargins_Highspeed(float value)
{
   mutex->lock();
   bool changed = data.Safetymargins[3] != value;
   data.Safetymargins[3] = value;
   mutex->unlock();
   if (changed) emit Safetymargins_HighspeedChanged(value);
}

float FixedWingPathFollowerSettings::getSafetymargins_Overspeed() const
{
   QMutexLocker locker(mutex);
   return data.Safetymargins[4];
}
void FixedWingPathFollowerSettings::setSafetymargins_Overspeed(float value)
{
   mutex->lock();
   bool changed = data.Safetymargins[4] != value;
   data.Safetymargins[4] = value;
   mutex->unlock();
   if (changed) emit Safetymargins_OverspeedChanged(value);
}

float FixedWingPathFollowerSettings::getSafetymargins_Lowpower() const
{
   QMutexLocker locker(mutex);
   return data.Safetymargins[5];
}
void FixedWingPathFollowerSettings::setSafetymargins_Lowpower(float value)
{
   mutex->lock();
   bool changed = data.Safetymargins[5] != value;
   data.Safetymargins[5] = value;
   mutex->unlock();
   if (changed) emit Safetymargins_LowpowerChanged(value);
}

float FixedWingPathFollowerSettings::getSafetymargins_Highpower() const
{
   QMutexLocker locker(mutex);
   return data.Safetymargins[6];
}
void FixedWingPathFollowerSettings::setSafetymargins_Highpower(float value)
{
   mutex->lock();
   bool changed = data.Safetymargins[6] != value;
   data.Safetymargins[6] = value;
   mutex->unlock();
   if (changed) emit Safetymargins_HighpowerChanged(value);
}

float FixedWingPathFollowerSettings::getSafetymargins_Pitchcontrol() const
{
   QMutexLocker locker(mutex);
   return data.Safetymargins[7];
}
void FixedWingPathFollowerSettings::setSafetymargins_Pitchcontrol(float value)
{
   mutex->lock();
   bool changed = data.Safetymargins[7] != value;
   data.Safetymargins[7] = value;
   mutex->unlock();
   if (changed) emit Safetymargins_PitchcontrolChanged(value);
}

qint32 FixedWingPathFollowerSettings::getUpdatePeriod() const
{
   QMutexLocker locker(mutex);
   return data.UpdatePeriod;
}
void FixedWingPathFollowerSettings::setUpdatePeriod(qint32 value)
{
   mutex->lock();
   bool changed = data.UpdatePeriod != value;
   data.UpdatePeriod = value;
   mutex->unlock();
   if (changed) emit UpdatePeriodChanged(value);
}


