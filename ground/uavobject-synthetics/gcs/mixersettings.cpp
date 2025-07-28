/**
 ******************************************************************************
 *
 * @file       mixersettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: mixersettings.xml.
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

#include "mixersettings.h"
#include "uavobjectfield.h"

const QString MixerSettings::NAME = QString("MixerSettings");
const QString MixerSettings::DESCRIPTION = QString("Settings for the @ref ActuatorModule that controls the channel assignments for the mixer based on AircraftType");
const QString MixerSettings::CATEGORY = QString("Control");

/**
 * Constructor
 */
MixerSettings::MixerSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList MaxAccelElemNames;
    MaxAccelElemNames.append("0");
    fields.append( new UAVObjectField(QString("MaxAccel"), tr(""), QString("units/sec"), UAVObjectField::FLOAT32, MaxAccelElemNames, QStringList(), QString("")));
    QStringList FeedForwardElemNames;
    FeedForwardElemNames.append("0");
    fields.append( new UAVObjectField(QString("FeedForward"), tr(""), QString(""), UAVObjectField::FLOAT32, FeedForwardElemNames, QStringList(), QString("")));
    QStringList AccelTimeElemNames;
    AccelTimeElemNames.append("0");
    fields.append( new UAVObjectField(QString("AccelTime"), tr(""), QString("ms"), UAVObjectField::FLOAT32, AccelTimeElemNames, QStringList(), QString("")));
    QStringList DecelTimeElemNames;
    DecelTimeElemNames.append("0");
    fields.append( new UAVObjectField(QString("DecelTime"), tr(""), QString("ms"), UAVObjectField::FLOAT32, DecelTimeElemNames, QStringList(), QString("")));
    QStringList ThrottleCurve1ElemNames;
    ThrottleCurve1ElemNames.append("0");
    ThrottleCurve1ElemNames.append("25");
    ThrottleCurve1ElemNames.append("50");
    ThrottleCurve1ElemNames.append("75");
    ThrottleCurve1ElemNames.append("100");
    fields.append( new UAVObjectField(QString("ThrottleCurve1"), tr(""), QString("percent"), UAVObjectField::FLOAT32, ThrottleCurve1ElemNames, QStringList(), QString("")));
    QStringList ThrottleCurve2ElemNames;
    ThrottleCurve2ElemNames.append("0");
    ThrottleCurve2ElemNames.append("25");
    ThrottleCurve2ElemNames.append("50");
    ThrottleCurve2ElemNames.append("75");
    ThrottleCurve2ElemNames.append("100");
    fields.append( new UAVObjectField(QString("ThrottleCurve2"), tr(""), QString("percent"), UAVObjectField::FLOAT32, ThrottleCurve2ElemNames, QStringList(), QString("")));
    QStringList MixerValueRollElemNames;
    MixerValueRollElemNames.append("0");
    fields.append( new UAVObjectField(QString("MixerValueRoll"), tr(""), QString("percent"), UAVObjectField::INT8, MixerValueRollElemNames, QStringList(), QString("")));
    QStringList MixerValuePitchElemNames;
    MixerValuePitchElemNames.append("0");
    fields.append( new UAVObjectField(QString("MixerValuePitch"), tr(""), QString("percent"), UAVObjectField::INT8, MixerValuePitchElemNames, QStringList(), QString("")));
    QStringList MixerValueYawElemNames;
    MixerValueYawElemNames.append("0");
    fields.append( new UAVObjectField(QString("MixerValueYaw"), tr(""), QString("percent"), UAVObjectField::INT8, MixerValueYawElemNames, QStringList(), QString("")));
    QStringList Curve2SourceElemNames;
    Curve2SourceElemNames.append("0");
    QStringList Curve2SourceEnumOptions;
    Curve2SourceEnumOptions.append("Throttle");
    Curve2SourceEnumOptions.append("Roll");
    Curve2SourceEnumOptions.append("Pitch");
    Curve2SourceEnumOptions.append("Yaw");
    Curve2SourceEnumOptions.append("Collective");
    Curve2SourceEnumOptions.append("Accessory0");
    Curve2SourceEnumOptions.append("Accessory1");
    Curve2SourceEnumOptions.append("Accessory2");
    Curve2SourceEnumOptions.append("Accessory3");
    Curve2SourceEnumOptions.append("Accessory4");
    Curve2SourceEnumOptions.append("Accessory5");
    fields.append( new UAVObjectField(QString("Curve2Source"), tr(""), QString(""), UAVObjectField::ENUM, Curve2SourceElemNames, Curve2SourceEnumOptions, QString("")));
    QStringList Mixer1TypeElemNames;
    Mixer1TypeElemNames.append("0");
    QStringList Mixer1TypeEnumOptions;
    Mixer1TypeEnumOptions.append("Disabled");
    Mixer1TypeEnumOptions.append("Motor");
    Mixer1TypeEnumOptions.append("ReversableMotor");
    Mixer1TypeEnumOptions.append("Servo");
    Mixer1TypeEnumOptions.append("CameraRollOrServo1");
    Mixer1TypeEnumOptions.append("CameraPitchOrServo2");
    Mixer1TypeEnumOptions.append("CameraYaw");
    Mixer1TypeEnumOptions.append("Accessory0");
    Mixer1TypeEnumOptions.append("Accessory1");
    Mixer1TypeEnumOptions.append("Accessory2");
    Mixer1TypeEnumOptions.append("Accessory3");
    Mixer1TypeEnumOptions.append("Accessory4");
    Mixer1TypeEnumOptions.append("Accessory5");
    fields.append( new UAVObjectField(QString("Mixer1Type"), tr(""), QString(""), UAVObjectField::ENUM, Mixer1TypeElemNames, Mixer1TypeEnumOptions, QString("")));
    QStringList Mixer1VectorElemNames;
    Mixer1VectorElemNames.append("ThrottleCurve1");
    Mixer1VectorElemNames.append("ThrottleCurve2");
    Mixer1VectorElemNames.append("Roll");
    Mixer1VectorElemNames.append("Pitch");
    Mixer1VectorElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("Mixer1Vector"), tr(""), QString(""), UAVObjectField::INT8, Mixer1VectorElemNames, QStringList(), QString("")));
    QStringList Mixer2TypeElemNames;
    Mixer2TypeElemNames.append("0");
    QStringList Mixer2TypeEnumOptions;
    Mixer2TypeEnumOptions.append("Disabled");
    Mixer2TypeEnumOptions.append("Motor");
    Mixer2TypeEnumOptions.append("ReversableMotor");
    Mixer2TypeEnumOptions.append("Servo");
    Mixer2TypeEnumOptions.append("CameraRollOrServo1");
    Mixer2TypeEnumOptions.append("CameraPitchOrServo2");
    Mixer2TypeEnumOptions.append("CameraYaw");
    Mixer2TypeEnumOptions.append("Accessory0");
    Mixer2TypeEnumOptions.append("Accessory1");
    Mixer2TypeEnumOptions.append("Accessory2");
    Mixer2TypeEnumOptions.append("Accessory3");
    Mixer2TypeEnumOptions.append("Accessory4");
    Mixer2TypeEnumOptions.append("Accessory5");
    fields.append( new UAVObjectField(QString("Mixer2Type"), tr(""), QString(""), UAVObjectField::ENUM, Mixer2TypeElemNames, Mixer2TypeEnumOptions, QString("")));
    QStringList Mixer2VectorElemNames;
    Mixer2VectorElemNames.append("ThrottleCurve1");
    Mixer2VectorElemNames.append("ThrottleCurve2");
    Mixer2VectorElemNames.append("Roll");
    Mixer2VectorElemNames.append("Pitch");
    Mixer2VectorElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("Mixer2Vector"), tr(""), QString(""), UAVObjectField::INT8, Mixer2VectorElemNames, QStringList(), QString("")));
    QStringList Mixer3TypeElemNames;
    Mixer3TypeElemNames.append("0");
    QStringList Mixer3TypeEnumOptions;
    Mixer3TypeEnumOptions.append("Disabled");
    Mixer3TypeEnumOptions.append("Motor");
    Mixer3TypeEnumOptions.append("ReversableMotor");
    Mixer3TypeEnumOptions.append("Servo");
    Mixer3TypeEnumOptions.append("CameraRollOrServo1");
    Mixer3TypeEnumOptions.append("CameraPitchOrServo2");
    Mixer3TypeEnumOptions.append("CameraYaw");
    Mixer3TypeEnumOptions.append("Accessory0");
    Mixer3TypeEnumOptions.append("Accessory1");
    Mixer3TypeEnumOptions.append("Accessory2");
    Mixer3TypeEnumOptions.append("Accessory3");
    Mixer3TypeEnumOptions.append("Accessory4");
    Mixer3TypeEnumOptions.append("Accessory5");
    fields.append( new UAVObjectField(QString("Mixer3Type"), tr(""), QString(""), UAVObjectField::ENUM, Mixer3TypeElemNames, Mixer3TypeEnumOptions, QString("")));
    QStringList Mixer3VectorElemNames;
    Mixer3VectorElemNames.append("ThrottleCurve1");
    Mixer3VectorElemNames.append("ThrottleCurve2");
    Mixer3VectorElemNames.append("Roll");
    Mixer3VectorElemNames.append("Pitch");
    Mixer3VectorElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("Mixer3Vector"), tr(""), QString(""), UAVObjectField::INT8, Mixer3VectorElemNames, QStringList(), QString("")));
    QStringList Mixer4TypeElemNames;
    Mixer4TypeElemNames.append("0");
    QStringList Mixer4TypeEnumOptions;
    Mixer4TypeEnumOptions.append("Disabled");
    Mixer4TypeEnumOptions.append("Motor");
    Mixer4TypeEnumOptions.append("ReversableMotor");
    Mixer4TypeEnumOptions.append("Servo");
    Mixer4TypeEnumOptions.append("CameraRollOrServo1");
    Mixer4TypeEnumOptions.append("CameraPitchOrServo2");
    Mixer4TypeEnumOptions.append("CameraYaw");
    Mixer4TypeEnumOptions.append("Accessory0");
    Mixer4TypeEnumOptions.append("Accessory1");
    Mixer4TypeEnumOptions.append("Accessory2");
    Mixer4TypeEnumOptions.append("Accessory3");
    Mixer4TypeEnumOptions.append("Accessory4");
    Mixer4TypeEnumOptions.append("Accessory5");
    fields.append( new UAVObjectField(QString("Mixer4Type"), tr(""), QString(""), UAVObjectField::ENUM, Mixer4TypeElemNames, Mixer4TypeEnumOptions, QString("")));
    QStringList Mixer4VectorElemNames;
    Mixer4VectorElemNames.append("ThrottleCurve1");
    Mixer4VectorElemNames.append("ThrottleCurve2");
    Mixer4VectorElemNames.append("Roll");
    Mixer4VectorElemNames.append("Pitch");
    Mixer4VectorElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("Mixer4Vector"), tr(""), QString(""), UAVObjectField::INT8, Mixer4VectorElemNames, QStringList(), QString("")));
    QStringList Mixer5TypeElemNames;
    Mixer5TypeElemNames.append("0");
    QStringList Mixer5TypeEnumOptions;
    Mixer5TypeEnumOptions.append("Disabled");
    Mixer5TypeEnumOptions.append("Motor");
    Mixer5TypeEnumOptions.append("ReversableMotor");
    Mixer5TypeEnumOptions.append("Servo");
    Mixer5TypeEnumOptions.append("CameraRollOrServo1");
    Mixer5TypeEnumOptions.append("CameraPitchOrServo2");
    Mixer5TypeEnumOptions.append("CameraYaw");
    Mixer5TypeEnumOptions.append("Accessory0");
    Mixer5TypeEnumOptions.append("Accessory1");
    Mixer5TypeEnumOptions.append("Accessory2");
    Mixer5TypeEnumOptions.append("Accessory3");
    Mixer5TypeEnumOptions.append("Accessory4");
    Mixer5TypeEnumOptions.append("Accessory5");
    fields.append( new UAVObjectField(QString("Mixer5Type"), tr(""), QString(""), UAVObjectField::ENUM, Mixer5TypeElemNames, Mixer5TypeEnumOptions, QString("")));
    QStringList Mixer5VectorElemNames;
    Mixer5VectorElemNames.append("ThrottleCurve1");
    Mixer5VectorElemNames.append("ThrottleCurve2");
    Mixer5VectorElemNames.append("Roll");
    Mixer5VectorElemNames.append("Pitch");
    Mixer5VectorElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("Mixer5Vector"), tr(""), QString(""), UAVObjectField::INT8, Mixer5VectorElemNames, QStringList(), QString("")));
    QStringList Mixer6TypeElemNames;
    Mixer6TypeElemNames.append("0");
    QStringList Mixer6TypeEnumOptions;
    Mixer6TypeEnumOptions.append("Disabled");
    Mixer6TypeEnumOptions.append("Motor");
    Mixer6TypeEnumOptions.append("ReversableMotor");
    Mixer6TypeEnumOptions.append("Servo");
    Mixer6TypeEnumOptions.append("CameraRollOrServo1");
    Mixer6TypeEnumOptions.append("CameraPitchOrServo2");
    Mixer6TypeEnumOptions.append("CameraYaw");
    Mixer6TypeEnumOptions.append("Accessory0");
    Mixer6TypeEnumOptions.append("Accessory1");
    Mixer6TypeEnumOptions.append("Accessory2");
    Mixer6TypeEnumOptions.append("Accessory3");
    Mixer6TypeEnumOptions.append("Accessory4");
    Mixer6TypeEnumOptions.append("Accessory5");
    fields.append( new UAVObjectField(QString("Mixer6Type"), tr(""), QString(""), UAVObjectField::ENUM, Mixer6TypeElemNames, Mixer6TypeEnumOptions, QString("")));
    QStringList Mixer6VectorElemNames;
    Mixer6VectorElemNames.append("ThrottleCurve1");
    Mixer6VectorElemNames.append("ThrottleCurve2");
    Mixer6VectorElemNames.append("Roll");
    Mixer6VectorElemNames.append("Pitch");
    Mixer6VectorElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("Mixer6Vector"), tr(""), QString(""), UAVObjectField::INT8, Mixer6VectorElemNames, QStringList(), QString("")));
    QStringList Mixer7TypeElemNames;
    Mixer7TypeElemNames.append("0");
    QStringList Mixer7TypeEnumOptions;
    Mixer7TypeEnumOptions.append("Disabled");
    Mixer7TypeEnumOptions.append("Motor");
    Mixer7TypeEnumOptions.append("ReversableMotor");
    Mixer7TypeEnumOptions.append("Servo");
    Mixer7TypeEnumOptions.append("CameraRollOrServo1");
    Mixer7TypeEnumOptions.append("CameraPitchOrServo2");
    Mixer7TypeEnumOptions.append("CameraYaw");
    Mixer7TypeEnumOptions.append("Accessory0");
    Mixer7TypeEnumOptions.append("Accessory1");
    Mixer7TypeEnumOptions.append("Accessory2");
    Mixer7TypeEnumOptions.append("Accessory3");
    Mixer7TypeEnumOptions.append("Accessory4");
    Mixer7TypeEnumOptions.append("Accessory5");
    fields.append( new UAVObjectField(QString("Mixer7Type"), tr(""), QString(""), UAVObjectField::ENUM, Mixer7TypeElemNames, Mixer7TypeEnumOptions, QString("")));
    QStringList Mixer7VectorElemNames;
    Mixer7VectorElemNames.append("ThrottleCurve1");
    Mixer7VectorElemNames.append("ThrottleCurve2");
    Mixer7VectorElemNames.append("Roll");
    Mixer7VectorElemNames.append("Pitch");
    Mixer7VectorElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("Mixer7Vector"), tr(""), QString(""), UAVObjectField::INT8, Mixer7VectorElemNames, QStringList(), QString("")));
    QStringList Mixer8TypeElemNames;
    Mixer8TypeElemNames.append("0");
    QStringList Mixer8TypeEnumOptions;
    Mixer8TypeEnumOptions.append("Disabled");
    Mixer8TypeEnumOptions.append("Motor");
    Mixer8TypeEnumOptions.append("ReversableMotor");
    Mixer8TypeEnumOptions.append("Servo");
    Mixer8TypeEnumOptions.append("CameraRollOrServo1");
    Mixer8TypeEnumOptions.append("CameraPitchOrServo2");
    Mixer8TypeEnumOptions.append("CameraYaw");
    Mixer8TypeEnumOptions.append("Accessory0");
    Mixer8TypeEnumOptions.append("Accessory1");
    Mixer8TypeEnumOptions.append("Accessory2");
    Mixer8TypeEnumOptions.append("Accessory3");
    Mixer8TypeEnumOptions.append("Accessory4");
    Mixer8TypeEnumOptions.append("Accessory5");
    fields.append( new UAVObjectField(QString("Mixer8Type"), tr(""), QString(""), UAVObjectField::ENUM, Mixer8TypeElemNames, Mixer8TypeEnumOptions, QString("")));
    QStringList Mixer8VectorElemNames;
    Mixer8VectorElemNames.append("ThrottleCurve1");
    Mixer8VectorElemNames.append("ThrottleCurve2");
    Mixer8VectorElemNames.append("Roll");
    Mixer8VectorElemNames.append("Pitch");
    Mixer8VectorElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("Mixer8Vector"), tr(""), QString(""), UAVObjectField::INT8, Mixer8VectorElemNames, QStringList(), QString("")));
    QStringList Mixer9TypeElemNames;
    Mixer9TypeElemNames.append("0");
    QStringList Mixer9TypeEnumOptions;
    Mixer9TypeEnumOptions.append("Disabled");
    Mixer9TypeEnumOptions.append("Motor");
    Mixer9TypeEnumOptions.append("ReversableMotor");
    Mixer9TypeEnumOptions.append("Servo");
    Mixer9TypeEnumOptions.append("CameraRollOrServo1");
    Mixer9TypeEnumOptions.append("CameraPitchOrServo2");
    Mixer9TypeEnumOptions.append("CameraYaw");
    Mixer9TypeEnumOptions.append("Accessory0");
    Mixer9TypeEnumOptions.append("Accessory1");
    Mixer9TypeEnumOptions.append("Accessory2");
    Mixer9TypeEnumOptions.append("Accessory3");
    Mixer9TypeEnumOptions.append("Accessory4");
    Mixer9TypeEnumOptions.append("Accessory5");
    fields.append( new UAVObjectField(QString("Mixer9Type"), tr(""), QString(""), UAVObjectField::ENUM, Mixer9TypeElemNames, Mixer9TypeEnumOptions, QString("")));
    QStringList Mixer9VectorElemNames;
    Mixer9VectorElemNames.append("ThrottleCurve1");
    Mixer9VectorElemNames.append("ThrottleCurve2");
    Mixer9VectorElemNames.append("Roll");
    Mixer9VectorElemNames.append("Pitch");
    Mixer9VectorElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("Mixer9Vector"), tr(""), QString(""), UAVObjectField::INT8, Mixer9VectorElemNames, QStringList(), QString("")));
    QStringList Mixer10TypeElemNames;
    Mixer10TypeElemNames.append("0");
    QStringList Mixer10TypeEnumOptions;
    Mixer10TypeEnumOptions.append("Disabled");
    Mixer10TypeEnumOptions.append("Motor");
    Mixer10TypeEnumOptions.append("ReversableMotor");
    Mixer10TypeEnumOptions.append("Servo");
    Mixer10TypeEnumOptions.append("CameraRollOrServo1");
    Mixer10TypeEnumOptions.append("CameraPitchOrServo2");
    Mixer10TypeEnumOptions.append("CameraYaw");
    Mixer10TypeEnumOptions.append("Accessory0");
    Mixer10TypeEnumOptions.append("Accessory1");
    Mixer10TypeEnumOptions.append("Accessory2");
    Mixer10TypeEnumOptions.append("Accessory3");
    Mixer10TypeEnumOptions.append("Accessory4");
    Mixer10TypeEnumOptions.append("Accessory5");
    fields.append( new UAVObjectField(QString("Mixer10Type"), tr(""), QString(""), UAVObjectField::ENUM, Mixer10TypeElemNames, Mixer10TypeEnumOptions, QString("")));
    QStringList Mixer10VectorElemNames;
    Mixer10VectorElemNames.append("ThrottleCurve1");
    Mixer10VectorElemNames.append("ThrottleCurve2");
    Mixer10VectorElemNames.append("Roll");
    Mixer10VectorElemNames.append("Pitch");
    Mixer10VectorElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("Mixer10Vector"), tr(""), QString(""), UAVObjectField::INT8, Mixer10VectorElemNames, QStringList(), QString("")));
    QStringList Mixer11TypeElemNames;
    Mixer11TypeElemNames.append("0");
    QStringList Mixer11TypeEnumOptions;
    Mixer11TypeEnumOptions.append("Disabled");
    Mixer11TypeEnumOptions.append("Motor");
    Mixer11TypeEnumOptions.append("ReversableMotor");
    Mixer11TypeEnumOptions.append("Servo");
    Mixer11TypeEnumOptions.append("CameraRollOrServo1");
    Mixer11TypeEnumOptions.append("CameraPitchOrServo2");
    Mixer11TypeEnumOptions.append("CameraYaw");
    Mixer11TypeEnumOptions.append("Accessory0");
    Mixer11TypeEnumOptions.append("Accessory1");
    Mixer11TypeEnumOptions.append("Accessory2");
    Mixer11TypeEnumOptions.append("Accessory3");
    Mixer11TypeEnumOptions.append("Accessory4");
    Mixer11TypeEnumOptions.append("Accessory5");
    fields.append( new UAVObjectField(QString("Mixer11Type"), tr(""), QString(""), UAVObjectField::ENUM, Mixer11TypeElemNames, Mixer11TypeEnumOptions, QString("")));
    QStringList Mixer11VectorElemNames;
    Mixer11VectorElemNames.append("ThrottleCurve1");
    Mixer11VectorElemNames.append("ThrottleCurve2");
    Mixer11VectorElemNames.append("Roll");
    Mixer11VectorElemNames.append("Pitch");
    Mixer11VectorElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("Mixer11Vector"), tr(""), QString(""), UAVObjectField::INT8, Mixer11VectorElemNames, QStringList(), QString("")));
    QStringList Mixer12TypeElemNames;
    Mixer12TypeElemNames.append("0");
    QStringList Mixer12TypeEnumOptions;
    Mixer12TypeEnumOptions.append("Disabled");
    Mixer12TypeEnumOptions.append("Motor");
    Mixer12TypeEnumOptions.append("ReversableMotor");
    Mixer12TypeEnumOptions.append("Servo");
    Mixer12TypeEnumOptions.append("CameraRollOrServo1");
    Mixer12TypeEnumOptions.append("CameraPitchOrServo2");
    Mixer12TypeEnumOptions.append("CameraYaw");
    Mixer12TypeEnumOptions.append("Accessory0");
    Mixer12TypeEnumOptions.append("Accessory1");
    Mixer12TypeEnumOptions.append("Accessory2");
    Mixer12TypeEnumOptions.append("Accessory3");
    Mixer12TypeEnumOptions.append("Accessory4");
    Mixer12TypeEnumOptions.append("Accessory5");
    fields.append( new UAVObjectField(QString("Mixer12Type"), tr(""), QString(""), UAVObjectField::ENUM, Mixer12TypeElemNames, Mixer12TypeEnumOptions, QString("")));
    QStringList Mixer12VectorElemNames;
    Mixer12VectorElemNames.append("ThrottleCurve1");
    Mixer12VectorElemNames.append("ThrottleCurve2");
    Mixer12VectorElemNames.append("Roll");
    Mixer12VectorElemNames.append("Pitch");
    Mixer12VectorElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("Mixer12Vector"), tr(""), QString(""), UAVObjectField::INT8, Mixer12VectorElemNames, QStringList(), QString("")));

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
UAVObject::Metadata MixerSettings::getDefaultMetadata()
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
void MixerSettings::setDefaultFieldValues()
{
    data.MaxAccel = 1000;
    data.FeedForward = 0;
    data.AccelTime = 0;
    data.DecelTime = 0;
    data.ThrottleCurve1[0] = 0;
    data.ThrottleCurve1[1] = 0;
    data.ThrottleCurve1[2] = 0;
    data.ThrottleCurve1[3] = 0;
    data.ThrottleCurve1[4] = 0;
    data.ThrottleCurve2[0] = 0;
    data.ThrottleCurve2[1] = 0.25;
    data.ThrottleCurve2[2] = 0.5;
    data.ThrottleCurve2[3] = 0.75;
    data.ThrottleCurve2[4] = 1;
    data.MixerValueRoll = 50;
    data.MixerValuePitch = 50;
    data.MixerValueYaw = 50;
    data.Curve2Source = 0;
    data.Mixer1Type = 0;
    data.Mixer1Vector[0] = 0;
    data.Mixer1Vector[1] = 0;
    data.Mixer1Vector[2] = 0;
    data.Mixer1Vector[3] = 0;
    data.Mixer1Vector[4] = 0;
    data.Mixer2Type = 0;
    data.Mixer2Vector[0] = 0;
    data.Mixer2Vector[1] = 0;
    data.Mixer2Vector[2] = 0;
    data.Mixer2Vector[3] = 0;
    data.Mixer2Vector[4] = 0;
    data.Mixer3Type = 0;
    data.Mixer3Vector[0] = 0;
    data.Mixer3Vector[1] = 0;
    data.Mixer3Vector[2] = 0;
    data.Mixer3Vector[3] = 0;
    data.Mixer3Vector[4] = 0;
    data.Mixer4Type = 0;
    data.Mixer4Vector[0] = 0;
    data.Mixer4Vector[1] = 0;
    data.Mixer4Vector[2] = 0;
    data.Mixer4Vector[3] = 0;
    data.Mixer4Vector[4] = 0;
    data.Mixer5Type = 0;
    data.Mixer5Vector[0] = 0;
    data.Mixer5Vector[1] = 0;
    data.Mixer5Vector[2] = 0;
    data.Mixer5Vector[3] = 0;
    data.Mixer5Vector[4] = 0;
    data.Mixer6Type = 0;
    data.Mixer6Vector[0] = 0;
    data.Mixer6Vector[1] = 0;
    data.Mixer6Vector[2] = 0;
    data.Mixer6Vector[3] = 0;
    data.Mixer6Vector[4] = 0;
    data.Mixer7Type = 0;
    data.Mixer7Vector[0] = 0;
    data.Mixer7Vector[1] = 0;
    data.Mixer7Vector[2] = 0;
    data.Mixer7Vector[3] = 0;
    data.Mixer7Vector[4] = 0;
    data.Mixer8Type = 0;
    data.Mixer8Vector[0] = 0;
    data.Mixer8Vector[1] = 0;
    data.Mixer8Vector[2] = 0;
    data.Mixer8Vector[3] = 0;
    data.Mixer8Vector[4] = 0;
    data.Mixer9Type = 0;
    data.Mixer9Vector[0] = 0;
    data.Mixer9Vector[1] = 0;
    data.Mixer9Vector[2] = 0;
    data.Mixer9Vector[3] = 0;
    data.Mixer9Vector[4] = 0;
    data.Mixer10Type = 0;
    data.Mixer10Vector[0] = 0;
    data.Mixer10Vector[1] = 0;
    data.Mixer10Vector[2] = 0;
    data.Mixer10Vector[3] = 0;
    data.Mixer10Vector[4] = 0;
    data.Mixer11Type = 0;
    data.Mixer11Vector[0] = 0;
    data.Mixer11Vector[1] = 0;
    data.Mixer11Vector[2] = 0;
    data.Mixer11Vector[3] = 0;
    data.Mixer11Vector[4] = 0;
    data.Mixer12Type = 0;
    data.Mixer12Vector[0] = 0;
    data.Mixer12Vector[1] = 0;
    data.Mixer12Vector[2] = 0;
    data.Mixer12Vector[3] = 0;
    data.Mixer12Vector[4] = 0;

}

/**
 * Get the object data fields
 */
MixerSettings::DataFields MixerSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void MixerSettings::setData(const DataFields& data)
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

void MixerSettings::emitNotifications()
{
            //if (data.MaxAccel != oldData.MaxAccel)
            emit MaxAccelChanged(data.MaxAccel);
        //if (data.FeedForward != oldData.FeedForward)
            emit FeedForwardChanged(data.FeedForward);
        //if (data.AccelTime != oldData.AccelTime)
            emit AccelTimeChanged(data.AccelTime);
        //if (data.DecelTime != oldData.DecelTime)
            emit DecelTimeChanged(data.DecelTime);
        //if (data.ThrottleCurve1[0] != oldData.ThrottleCurve1[0])
            emit ThrottleCurve1_0Changed(data.ThrottleCurve1[0]);
        //if (data.ThrottleCurve1[1] != oldData.ThrottleCurve1[1])
            emit ThrottleCurve1_25Changed(data.ThrottleCurve1[1]);
        //if (data.ThrottleCurve1[2] != oldData.ThrottleCurve1[2])
            emit ThrottleCurve1_50Changed(data.ThrottleCurve1[2]);
        //if (data.ThrottleCurve1[3] != oldData.ThrottleCurve1[3])
            emit ThrottleCurve1_75Changed(data.ThrottleCurve1[3]);
        //if (data.ThrottleCurve1[4] != oldData.ThrottleCurve1[4])
            emit ThrottleCurve1_100Changed(data.ThrottleCurve1[4]);
        //if (data.ThrottleCurve2[0] != oldData.ThrottleCurve2[0])
            emit ThrottleCurve2_0Changed(data.ThrottleCurve2[0]);
        //if (data.ThrottleCurve2[1] != oldData.ThrottleCurve2[1])
            emit ThrottleCurve2_25Changed(data.ThrottleCurve2[1]);
        //if (data.ThrottleCurve2[2] != oldData.ThrottleCurve2[2])
            emit ThrottleCurve2_50Changed(data.ThrottleCurve2[2]);
        //if (data.ThrottleCurve2[3] != oldData.ThrottleCurve2[3])
            emit ThrottleCurve2_75Changed(data.ThrottleCurve2[3]);
        //if (data.ThrottleCurve2[4] != oldData.ThrottleCurve2[4])
            emit ThrottleCurve2_100Changed(data.ThrottleCurve2[4]);
        //if (data.MixerValueRoll != oldData.MixerValueRoll)
            emit MixerValueRollChanged(data.MixerValueRoll);
        //if (data.MixerValuePitch != oldData.MixerValuePitch)
            emit MixerValuePitchChanged(data.MixerValuePitch);
        //if (data.MixerValueYaw != oldData.MixerValueYaw)
            emit MixerValueYawChanged(data.MixerValueYaw);
        //if (data.Curve2Source != oldData.Curve2Source)
            emit Curve2SourceChanged(data.Curve2Source);
        //if (data.Mixer1Type != oldData.Mixer1Type)
            emit Mixer1TypeChanged(data.Mixer1Type);
        //if (data.Mixer1Vector[0] != oldData.Mixer1Vector[0])
            emit Mixer1Vector_ThrottleCurve1Changed(data.Mixer1Vector[0]);
        //if (data.Mixer1Vector[1] != oldData.Mixer1Vector[1])
            emit Mixer1Vector_ThrottleCurve2Changed(data.Mixer1Vector[1]);
        //if (data.Mixer1Vector[2] != oldData.Mixer1Vector[2])
            emit Mixer1Vector_RollChanged(data.Mixer1Vector[2]);
        //if (data.Mixer1Vector[3] != oldData.Mixer1Vector[3])
            emit Mixer1Vector_PitchChanged(data.Mixer1Vector[3]);
        //if (data.Mixer1Vector[4] != oldData.Mixer1Vector[4])
            emit Mixer1Vector_YawChanged(data.Mixer1Vector[4]);
        //if (data.Mixer2Type != oldData.Mixer2Type)
            emit Mixer2TypeChanged(data.Mixer2Type);
        //if (data.Mixer2Vector[0] != oldData.Mixer2Vector[0])
            emit Mixer2Vector_ThrottleCurve1Changed(data.Mixer2Vector[0]);
        //if (data.Mixer2Vector[1] != oldData.Mixer2Vector[1])
            emit Mixer2Vector_ThrottleCurve2Changed(data.Mixer2Vector[1]);
        //if (data.Mixer2Vector[2] != oldData.Mixer2Vector[2])
            emit Mixer2Vector_RollChanged(data.Mixer2Vector[2]);
        //if (data.Mixer2Vector[3] != oldData.Mixer2Vector[3])
            emit Mixer2Vector_PitchChanged(data.Mixer2Vector[3]);
        //if (data.Mixer2Vector[4] != oldData.Mixer2Vector[4])
            emit Mixer2Vector_YawChanged(data.Mixer2Vector[4]);
        //if (data.Mixer3Type != oldData.Mixer3Type)
            emit Mixer3TypeChanged(data.Mixer3Type);
        //if (data.Mixer3Vector[0] != oldData.Mixer3Vector[0])
            emit Mixer3Vector_ThrottleCurve1Changed(data.Mixer3Vector[0]);
        //if (data.Mixer3Vector[1] != oldData.Mixer3Vector[1])
            emit Mixer3Vector_ThrottleCurve2Changed(data.Mixer3Vector[1]);
        //if (data.Mixer3Vector[2] != oldData.Mixer3Vector[2])
            emit Mixer3Vector_RollChanged(data.Mixer3Vector[2]);
        //if (data.Mixer3Vector[3] != oldData.Mixer3Vector[3])
            emit Mixer3Vector_PitchChanged(data.Mixer3Vector[3]);
        //if (data.Mixer3Vector[4] != oldData.Mixer3Vector[4])
            emit Mixer3Vector_YawChanged(data.Mixer3Vector[4]);
        //if (data.Mixer4Type != oldData.Mixer4Type)
            emit Mixer4TypeChanged(data.Mixer4Type);
        //if (data.Mixer4Vector[0] != oldData.Mixer4Vector[0])
            emit Mixer4Vector_ThrottleCurve1Changed(data.Mixer4Vector[0]);
        //if (data.Mixer4Vector[1] != oldData.Mixer4Vector[1])
            emit Mixer4Vector_ThrottleCurve2Changed(data.Mixer4Vector[1]);
        //if (data.Mixer4Vector[2] != oldData.Mixer4Vector[2])
            emit Mixer4Vector_RollChanged(data.Mixer4Vector[2]);
        //if (data.Mixer4Vector[3] != oldData.Mixer4Vector[3])
            emit Mixer4Vector_PitchChanged(data.Mixer4Vector[3]);
        //if (data.Mixer4Vector[4] != oldData.Mixer4Vector[4])
            emit Mixer4Vector_YawChanged(data.Mixer4Vector[4]);
        //if (data.Mixer5Type != oldData.Mixer5Type)
            emit Mixer5TypeChanged(data.Mixer5Type);
        //if (data.Mixer5Vector[0] != oldData.Mixer5Vector[0])
            emit Mixer5Vector_ThrottleCurve1Changed(data.Mixer5Vector[0]);
        //if (data.Mixer5Vector[1] != oldData.Mixer5Vector[1])
            emit Mixer5Vector_ThrottleCurve2Changed(data.Mixer5Vector[1]);
        //if (data.Mixer5Vector[2] != oldData.Mixer5Vector[2])
            emit Mixer5Vector_RollChanged(data.Mixer5Vector[2]);
        //if (data.Mixer5Vector[3] != oldData.Mixer5Vector[3])
            emit Mixer5Vector_PitchChanged(data.Mixer5Vector[3]);
        //if (data.Mixer5Vector[4] != oldData.Mixer5Vector[4])
            emit Mixer5Vector_YawChanged(data.Mixer5Vector[4]);
        //if (data.Mixer6Type != oldData.Mixer6Type)
            emit Mixer6TypeChanged(data.Mixer6Type);
        //if (data.Mixer6Vector[0] != oldData.Mixer6Vector[0])
            emit Mixer6Vector_ThrottleCurve1Changed(data.Mixer6Vector[0]);
        //if (data.Mixer6Vector[1] != oldData.Mixer6Vector[1])
            emit Mixer6Vector_ThrottleCurve2Changed(data.Mixer6Vector[1]);
        //if (data.Mixer6Vector[2] != oldData.Mixer6Vector[2])
            emit Mixer6Vector_RollChanged(data.Mixer6Vector[2]);
        //if (data.Mixer6Vector[3] != oldData.Mixer6Vector[3])
            emit Mixer6Vector_PitchChanged(data.Mixer6Vector[3]);
        //if (data.Mixer6Vector[4] != oldData.Mixer6Vector[4])
            emit Mixer6Vector_YawChanged(data.Mixer6Vector[4]);
        //if (data.Mixer7Type != oldData.Mixer7Type)
            emit Mixer7TypeChanged(data.Mixer7Type);
        //if (data.Mixer7Vector[0] != oldData.Mixer7Vector[0])
            emit Mixer7Vector_ThrottleCurve1Changed(data.Mixer7Vector[0]);
        //if (data.Mixer7Vector[1] != oldData.Mixer7Vector[1])
            emit Mixer7Vector_ThrottleCurve2Changed(data.Mixer7Vector[1]);
        //if (data.Mixer7Vector[2] != oldData.Mixer7Vector[2])
            emit Mixer7Vector_RollChanged(data.Mixer7Vector[2]);
        //if (data.Mixer7Vector[3] != oldData.Mixer7Vector[3])
            emit Mixer7Vector_PitchChanged(data.Mixer7Vector[3]);
        //if (data.Mixer7Vector[4] != oldData.Mixer7Vector[4])
            emit Mixer7Vector_YawChanged(data.Mixer7Vector[4]);
        //if (data.Mixer8Type != oldData.Mixer8Type)
            emit Mixer8TypeChanged(data.Mixer8Type);
        //if (data.Mixer8Vector[0] != oldData.Mixer8Vector[0])
            emit Mixer8Vector_ThrottleCurve1Changed(data.Mixer8Vector[0]);
        //if (data.Mixer8Vector[1] != oldData.Mixer8Vector[1])
            emit Mixer8Vector_ThrottleCurve2Changed(data.Mixer8Vector[1]);
        //if (data.Mixer8Vector[2] != oldData.Mixer8Vector[2])
            emit Mixer8Vector_RollChanged(data.Mixer8Vector[2]);
        //if (data.Mixer8Vector[3] != oldData.Mixer8Vector[3])
            emit Mixer8Vector_PitchChanged(data.Mixer8Vector[3]);
        //if (data.Mixer8Vector[4] != oldData.Mixer8Vector[4])
            emit Mixer8Vector_YawChanged(data.Mixer8Vector[4]);
        //if (data.Mixer9Type != oldData.Mixer9Type)
            emit Mixer9TypeChanged(data.Mixer9Type);
        //if (data.Mixer9Vector[0] != oldData.Mixer9Vector[0])
            emit Mixer9Vector_ThrottleCurve1Changed(data.Mixer9Vector[0]);
        //if (data.Mixer9Vector[1] != oldData.Mixer9Vector[1])
            emit Mixer9Vector_ThrottleCurve2Changed(data.Mixer9Vector[1]);
        //if (data.Mixer9Vector[2] != oldData.Mixer9Vector[2])
            emit Mixer9Vector_RollChanged(data.Mixer9Vector[2]);
        //if (data.Mixer9Vector[3] != oldData.Mixer9Vector[3])
            emit Mixer9Vector_PitchChanged(data.Mixer9Vector[3]);
        //if (data.Mixer9Vector[4] != oldData.Mixer9Vector[4])
            emit Mixer9Vector_YawChanged(data.Mixer9Vector[4]);
        //if (data.Mixer10Type != oldData.Mixer10Type)
            emit Mixer10TypeChanged(data.Mixer10Type);
        //if (data.Mixer10Vector[0] != oldData.Mixer10Vector[0])
            emit Mixer10Vector_ThrottleCurve1Changed(data.Mixer10Vector[0]);
        //if (data.Mixer10Vector[1] != oldData.Mixer10Vector[1])
            emit Mixer10Vector_ThrottleCurve2Changed(data.Mixer10Vector[1]);
        //if (data.Mixer10Vector[2] != oldData.Mixer10Vector[2])
            emit Mixer10Vector_RollChanged(data.Mixer10Vector[2]);
        //if (data.Mixer10Vector[3] != oldData.Mixer10Vector[3])
            emit Mixer10Vector_PitchChanged(data.Mixer10Vector[3]);
        //if (data.Mixer10Vector[4] != oldData.Mixer10Vector[4])
            emit Mixer10Vector_YawChanged(data.Mixer10Vector[4]);
        //if (data.Mixer11Type != oldData.Mixer11Type)
            emit Mixer11TypeChanged(data.Mixer11Type);
        //if (data.Mixer11Vector[0] != oldData.Mixer11Vector[0])
            emit Mixer11Vector_ThrottleCurve1Changed(data.Mixer11Vector[0]);
        //if (data.Mixer11Vector[1] != oldData.Mixer11Vector[1])
            emit Mixer11Vector_ThrottleCurve2Changed(data.Mixer11Vector[1]);
        //if (data.Mixer11Vector[2] != oldData.Mixer11Vector[2])
            emit Mixer11Vector_RollChanged(data.Mixer11Vector[2]);
        //if (data.Mixer11Vector[3] != oldData.Mixer11Vector[3])
            emit Mixer11Vector_PitchChanged(data.Mixer11Vector[3]);
        //if (data.Mixer11Vector[4] != oldData.Mixer11Vector[4])
            emit Mixer11Vector_YawChanged(data.Mixer11Vector[4]);
        //if (data.Mixer12Type != oldData.Mixer12Type)
            emit Mixer12TypeChanged(data.Mixer12Type);
        //if (data.Mixer12Vector[0] != oldData.Mixer12Vector[0])
            emit Mixer12Vector_ThrottleCurve1Changed(data.Mixer12Vector[0]);
        //if (data.Mixer12Vector[1] != oldData.Mixer12Vector[1])
            emit Mixer12Vector_ThrottleCurve2Changed(data.Mixer12Vector[1]);
        //if (data.Mixer12Vector[2] != oldData.Mixer12Vector[2])
            emit Mixer12Vector_RollChanged(data.Mixer12Vector[2]);
        //if (data.Mixer12Vector[3] != oldData.Mixer12Vector[3])
            emit Mixer12Vector_PitchChanged(data.Mixer12Vector[3]);
        //if (data.Mixer12Vector[4] != oldData.Mixer12Vector[4])
            emit Mixer12Vector_YawChanged(data.Mixer12Vector[4]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *MixerSettings::clone(quint32 instID)
{
    MixerSettings *obj = new MixerSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *MixerSettings::dirtyClone()
{
    MixerSettings *obj = new MixerSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
MixerSettings *MixerSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<MixerSettings *>(objMngr->getObject(MixerSettings::OBJID, instID));
}

float MixerSettings::getMaxAccel() const
{
   QMutexLocker locker(mutex);
   return data.MaxAccel;
}
void MixerSettings::setMaxAccel(float value)
{
   mutex->lock();
   bool changed = data.MaxAccel != value;
   data.MaxAccel = value;
   mutex->unlock();
   if (changed) emit MaxAccelChanged(value);
}

float MixerSettings::getFeedForward() const
{
   QMutexLocker locker(mutex);
   return data.FeedForward;
}
void MixerSettings::setFeedForward(float value)
{
   mutex->lock();
   bool changed = data.FeedForward != value;
   data.FeedForward = value;
   mutex->unlock();
   if (changed) emit FeedForwardChanged(value);
}

float MixerSettings::getAccelTime() const
{
   QMutexLocker locker(mutex);
   return data.AccelTime;
}
void MixerSettings::setAccelTime(float value)
{
   mutex->lock();
   bool changed = data.AccelTime != value;
   data.AccelTime = value;
   mutex->unlock();
   if (changed) emit AccelTimeChanged(value);
}

float MixerSettings::getDecelTime() const
{
   QMutexLocker locker(mutex);
   return data.DecelTime;
}
void MixerSettings::setDecelTime(float value)
{
   mutex->lock();
   bool changed = data.DecelTime != value;
   data.DecelTime = value;
   mutex->unlock();
   if (changed) emit DecelTimeChanged(value);
}

float MixerSettings::getThrottleCurve1(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ThrottleCurve1[index];
}
void MixerSettings::setThrottleCurve1(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.ThrottleCurve1[index] != value;
   data.ThrottleCurve1[index] = value;
   mutex->unlock();
   if (changed) emit ThrottleCurve1Changed(index,value);
}

float MixerSettings::getThrottleCurve1_0() const
{
   QMutexLocker locker(mutex);
   return data.ThrottleCurve1[0];
}
void MixerSettings::setThrottleCurve1_0(float value)
{
   mutex->lock();
   bool changed = data.ThrottleCurve1[0] != value;
   data.ThrottleCurve1[0] = value;
   mutex->unlock();
   if (changed) emit ThrottleCurve1_0Changed(value);
}

float MixerSettings::getThrottleCurve1_25() const
{
   QMutexLocker locker(mutex);
   return data.ThrottleCurve1[1];
}
void MixerSettings::setThrottleCurve1_25(float value)
{
   mutex->lock();
   bool changed = data.ThrottleCurve1[1] != value;
   data.ThrottleCurve1[1] = value;
   mutex->unlock();
   if (changed) emit ThrottleCurve1_25Changed(value);
}

float MixerSettings::getThrottleCurve1_50() const
{
   QMutexLocker locker(mutex);
   return data.ThrottleCurve1[2];
}
void MixerSettings::setThrottleCurve1_50(float value)
{
   mutex->lock();
   bool changed = data.ThrottleCurve1[2] != value;
   data.ThrottleCurve1[2] = value;
   mutex->unlock();
   if (changed) emit ThrottleCurve1_50Changed(value);
}

float MixerSettings::getThrottleCurve1_75() const
{
   QMutexLocker locker(mutex);
   return data.ThrottleCurve1[3];
}
void MixerSettings::setThrottleCurve1_75(float value)
{
   mutex->lock();
   bool changed = data.ThrottleCurve1[3] != value;
   data.ThrottleCurve1[3] = value;
   mutex->unlock();
   if (changed) emit ThrottleCurve1_75Changed(value);
}

float MixerSettings::getThrottleCurve1_100() const
{
   QMutexLocker locker(mutex);
   return data.ThrottleCurve1[4];
}
void MixerSettings::setThrottleCurve1_100(float value)
{
   mutex->lock();
   bool changed = data.ThrottleCurve1[4] != value;
   data.ThrottleCurve1[4] = value;
   mutex->unlock();
   if (changed) emit ThrottleCurve1_100Changed(value);
}

float MixerSettings::getThrottleCurve2(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ThrottleCurve2[index];
}
void MixerSettings::setThrottleCurve2(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.ThrottleCurve2[index] != value;
   data.ThrottleCurve2[index] = value;
   mutex->unlock();
   if (changed) emit ThrottleCurve2Changed(index,value);
}

float MixerSettings::getThrottleCurve2_0() const
{
   QMutexLocker locker(mutex);
   return data.ThrottleCurve2[0];
}
void MixerSettings::setThrottleCurve2_0(float value)
{
   mutex->lock();
   bool changed = data.ThrottleCurve2[0] != value;
   data.ThrottleCurve2[0] = value;
   mutex->unlock();
   if (changed) emit ThrottleCurve2_0Changed(value);
}

float MixerSettings::getThrottleCurve2_25() const
{
   QMutexLocker locker(mutex);
   return data.ThrottleCurve2[1];
}
void MixerSettings::setThrottleCurve2_25(float value)
{
   mutex->lock();
   bool changed = data.ThrottleCurve2[1] != value;
   data.ThrottleCurve2[1] = value;
   mutex->unlock();
   if (changed) emit ThrottleCurve2_25Changed(value);
}

float MixerSettings::getThrottleCurve2_50() const
{
   QMutexLocker locker(mutex);
   return data.ThrottleCurve2[2];
}
void MixerSettings::setThrottleCurve2_50(float value)
{
   mutex->lock();
   bool changed = data.ThrottleCurve2[2] != value;
   data.ThrottleCurve2[2] = value;
   mutex->unlock();
   if (changed) emit ThrottleCurve2_50Changed(value);
}

float MixerSettings::getThrottleCurve2_75() const
{
   QMutexLocker locker(mutex);
   return data.ThrottleCurve2[3];
}
void MixerSettings::setThrottleCurve2_75(float value)
{
   mutex->lock();
   bool changed = data.ThrottleCurve2[3] != value;
   data.ThrottleCurve2[3] = value;
   mutex->unlock();
   if (changed) emit ThrottleCurve2_75Changed(value);
}

float MixerSettings::getThrottleCurve2_100() const
{
   QMutexLocker locker(mutex);
   return data.ThrottleCurve2[4];
}
void MixerSettings::setThrottleCurve2_100(float value)
{
   mutex->lock();
   bool changed = data.ThrottleCurve2[4] != value;
   data.ThrottleCurve2[4] = value;
   mutex->unlock();
   if (changed) emit ThrottleCurve2_100Changed(value);
}

qint8 MixerSettings::getMixerValueRoll() const
{
   QMutexLocker locker(mutex);
   return data.MixerValueRoll;
}
void MixerSettings::setMixerValueRoll(qint8 value)
{
   mutex->lock();
   bool changed = data.MixerValueRoll != value;
   data.MixerValueRoll = value;
   mutex->unlock();
   if (changed) emit MixerValueRollChanged(value);
}

qint8 MixerSettings::getMixerValuePitch() const
{
   QMutexLocker locker(mutex);
   return data.MixerValuePitch;
}
void MixerSettings::setMixerValuePitch(qint8 value)
{
   mutex->lock();
   bool changed = data.MixerValuePitch != value;
   data.MixerValuePitch = value;
   mutex->unlock();
   if (changed) emit MixerValuePitchChanged(value);
}

qint8 MixerSettings::getMixerValueYaw() const
{
   QMutexLocker locker(mutex);
   return data.MixerValueYaw;
}
void MixerSettings::setMixerValueYaw(qint8 value)
{
   mutex->lock();
   bool changed = data.MixerValueYaw != value;
   data.MixerValueYaw = value;
   mutex->unlock();
   if (changed) emit MixerValueYawChanged(value);
}

quint8 MixerSettings::getCurve2Source() const
{
   QMutexLocker locker(mutex);
   return data.Curve2Source;
}
void MixerSettings::setCurve2Source(quint8 value)
{
   mutex->lock();
   bool changed = data.Curve2Source != value;
   data.Curve2Source = value;
   mutex->unlock();
   if (changed) emit Curve2SourceChanged(value);
}

quint8 MixerSettings::getMixer1Type() const
{
   QMutexLocker locker(mutex);
   return data.Mixer1Type;
}
void MixerSettings::setMixer1Type(quint8 value)
{
   mutex->lock();
   bool changed = data.Mixer1Type != value;
   data.Mixer1Type = value;
   mutex->unlock();
   if (changed) emit Mixer1TypeChanged(value);
}

qint8 MixerSettings::getMixer1Vector(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Mixer1Vector[index];
}
void MixerSettings::setMixer1Vector(quint32 index, qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer1Vector[index] != value;
   data.Mixer1Vector[index] = value;
   mutex->unlock();
   if (changed) emit Mixer1VectorChanged(index,value);
}

qint8 MixerSettings::getMixer1Vector_ThrottleCurve1() const
{
   QMutexLocker locker(mutex);
   return data.Mixer1Vector[0];
}
void MixerSettings::setMixer1Vector_ThrottleCurve1(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer1Vector[0] != value;
   data.Mixer1Vector[0] = value;
   mutex->unlock();
   if (changed) emit Mixer1Vector_ThrottleCurve1Changed(value);
}

qint8 MixerSettings::getMixer1Vector_ThrottleCurve2() const
{
   QMutexLocker locker(mutex);
   return data.Mixer1Vector[1];
}
void MixerSettings::setMixer1Vector_ThrottleCurve2(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer1Vector[1] != value;
   data.Mixer1Vector[1] = value;
   mutex->unlock();
   if (changed) emit Mixer1Vector_ThrottleCurve2Changed(value);
}

qint8 MixerSettings::getMixer1Vector_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Mixer1Vector[2];
}
void MixerSettings::setMixer1Vector_Roll(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer1Vector[2] != value;
   data.Mixer1Vector[2] = value;
   mutex->unlock();
   if (changed) emit Mixer1Vector_RollChanged(value);
}

qint8 MixerSettings::getMixer1Vector_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Mixer1Vector[3];
}
void MixerSettings::setMixer1Vector_Pitch(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer1Vector[3] != value;
   data.Mixer1Vector[3] = value;
   mutex->unlock();
   if (changed) emit Mixer1Vector_PitchChanged(value);
}

qint8 MixerSettings::getMixer1Vector_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Mixer1Vector[4];
}
void MixerSettings::setMixer1Vector_Yaw(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer1Vector[4] != value;
   data.Mixer1Vector[4] = value;
   mutex->unlock();
   if (changed) emit Mixer1Vector_YawChanged(value);
}

quint8 MixerSettings::getMixer2Type() const
{
   QMutexLocker locker(mutex);
   return data.Mixer2Type;
}
void MixerSettings::setMixer2Type(quint8 value)
{
   mutex->lock();
   bool changed = data.Mixer2Type != value;
   data.Mixer2Type = value;
   mutex->unlock();
   if (changed) emit Mixer2TypeChanged(value);
}

qint8 MixerSettings::getMixer2Vector(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Mixer2Vector[index];
}
void MixerSettings::setMixer2Vector(quint32 index, qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer2Vector[index] != value;
   data.Mixer2Vector[index] = value;
   mutex->unlock();
   if (changed) emit Mixer2VectorChanged(index,value);
}

qint8 MixerSettings::getMixer2Vector_ThrottleCurve1() const
{
   QMutexLocker locker(mutex);
   return data.Mixer2Vector[0];
}
void MixerSettings::setMixer2Vector_ThrottleCurve1(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer2Vector[0] != value;
   data.Mixer2Vector[0] = value;
   mutex->unlock();
   if (changed) emit Mixer2Vector_ThrottleCurve1Changed(value);
}

qint8 MixerSettings::getMixer2Vector_ThrottleCurve2() const
{
   QMutexLocker locker(mutex);
   return data.Mixer2Vector[1];
}
void MixerSettings::setMixer2Vector_ThrottleCurve2(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer2Vector[1] != value;
   data.Mixer2Vector[1] = value;
   mutex->unlock();
   if (changed) emit Mixer2Vector_ThrottleCurve2Changed(value);
}

qint8 MixerSettings::getMixer2Vector_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Mixer2Vector[2];
}
void MixerSettings::setMixer2Vector_Roll(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer2Vector[2] != value;
   data.Mixer2Vector[2] = value;
   mutex->unlock();
   if (changed) emit Mixer2Vector_RollChanged(value);
}

qint8 MixerSettings::getMixer2Vector_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Mixer2Vector[3];
}
void MixerSettings::setMixer2Vector_Pitch(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer2Vector[3] != value;
   data.Mixer2Vector[3] = value;
   mutex->unlock();
   if (changed) emit Mixer2Vector_PitchChanged(value);
}

qint8 MixerSettings::getMixer2Vector_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Mixer2Vector[4];
}
void MixerSettings::setMixer2Vector_Yaw(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer2Vector[4] != value;
   data.Mixer2Vector[4] = value;
   mutex->unlock();
   if (changed) emit Mixer2Vector_YawChanged(value);
}

quint8 MixerSettings::getMixer3Type() const
{
   QMutexLocker locker(mutex);
   return data.Mixer3Type;
}
void MixerSettings::setMixer3Type(quint8 value)
{
   mutex->lock();
   bool changed = data.Mixer3Type != value;
   data.Mixer3Type = value;
   mutex->unlock();
   if (changed) emit Mixer3TypeChanged(value);
}

qint8 MixerSettings::getMixer3Vector(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Mixer3Vector[index];
}
void MixerSettings::setMixer3Vector(quint32 index, qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer3Vector[index] != value;
   data.Mixer3Vector[index] = value;
   mutex->unlock();
   if (changed) emit Mixer3VectorChanged(index,value);
}

qint8 MixerSettings::getMixer3Vector_ThrottleCurve1() const
{
   QMutexLocker locker(mutex);
   return data.Mixer3Vector[0];
}
void MixerSettings::setMixer3Vector_ThrottleCurve1(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer3Vector[0] != value;
   data.Mixer3Vector[0] = value;
   mutex->unlock();
   if (changed) emit Mixer3Vector_ThrottleCurve1Changed(value);
}

qint8 MixerSettings::getMixer3Vector_ThrottleCurve2() const
{
   QMutexLocker locker(mutex);
   return data.Mixer3Vector[1];
}
void MixerSettings::setMixer3Vector_ThrottleCurve2(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer3Vector[1] != value;
   data.Mixer3Vector[1] = value;
   mutex->unlock();
   if (changed) emit Mixer3Vector_ThrottleCurve2Changed(value);
}

qint8 MixerSettings::getMixer3Vector_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Mixer3Vector[2];
}
void MixerSettings::setMixer3Vector_Roll(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer3Vector[2] != value;
   data.Mixer3Vector[2] = value;
   mutex->unlock();
   if (changed) emit Mixer3Vector_RollChanged(value);
}

qint8 MixerSettings::getMixer3Vector_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Mixer3Vector[3];
}
void MixerSettings::setMixer3Vector_Pitch(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer3Vector[3] != value;
   data.Mixer3Vector[3] = value;
   mutex->unlock();
   if (changed) emit Mixer3Vector_PitchChanged(value);
}

qint8 MixerSettings::getMixer3Vector_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Mixer3Vector[4];
}
void MixerSettings::setMixer3Vector_Yaw(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer3Vector[4] != value;
   data.Mixer3Vector[4] = value;
   mutex->unlock();
   if (changed) emit Mixer3Vector_YawChanged(value);
}

quint8 MixerSettings::getMixer4Type() const
{
   QMutexLocker locker(mutex);
   return data.Mixer4Type;
}
void MixerSettings::setMixer4Type(quint8 value)
{
   mutex->lock();
   bool changed = data.Mixer4Type != value;
   data.Mixer4Type = value;
   mutex->unlock();
   if (changed) emit Mixer4TypeChanged(value);
}

qint8 MixerSettings::getMixer4Vector(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Mixer4Vector[index];
}
void MixerSettings::setMixer4Vector(quint32 index, qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer4Vector[index] != value;
   data.Mixer4Vector[index] = value;
   mutex->unlock();
   if (changed) emit Mixer4VectorChanged(index,value);
}

qint8 MixerSettings::getMixer4Vector_ThrottleCurve1() const
{
   QMutexLocker locker(mutex);
   return data.Mixer4Vector[0];
}
void MixerSettings::setMixer4Vector_ThrottleCurve1(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer4Vector[0] != value;
   data.Mixer4Vector[0] = value;
   mutex->unlock();
   if (changed) emit Mixer4Vector_ThrottleCurve1Changed(value);
}

qint8 MixerSettings::getMixer4Vector_ThrottleCurve2() const
{
   QMutexLocker locker(mutex);
   return data.Mixer4Vector[1];
}
void MixerSettings::setMixer4Vector_ThrottleCurve2(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer4Vector[1] != value;
   data.Mixer4Vector[1] = value;
   mutex->unlock();
   if (changed) emit Mixer4Vector_ThrottleCurve2Changed(value);
}

qint8 MixerSettings::getMixer4Vector_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Mixer4Vector[2];
}
void MixerSettings::setMixer4Vector_Roll(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer4Vector[2] != value;
   data.Mixer4Vector[2] = value;
   mutex->unlock();
   if (changed) emit Mixer4Vector_RollChanged(value);
}

qint8 MixerSettings::getMixer4Vector_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Mixer4Vector[3];
}
void MixerSettings::setMixer4Vector_Pitch(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer4Vector[3] != value;
   data.Mixer4Vector[3] = value;
   mutex->unlock();
   if (changed) emit Mixer4Vector_PitchChanged(value);
}

qint8 MixerSettings::getMixer4Vector_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Mixer4Vector[4];
}
void MixerSettings::setMixer4Vector_Yaw(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer4Vector[4] != value;
   data.Mixer4Vector[4] = value;
   mutex->unlock();
   if (changed) emit Mixer4Vector_YawChanged(value);
}

quint8 MixerSettings::getMixer5Type() const
{
   QMutexLocker locker(mutex);
   return data.Mixer5Type;
}
void MixerSettings::setMixer5Type(quint8 value)
{
   mutex->lock();
   bool changed = data.Mixer5Type != value;
   data.Mixer5Type = value;
   mutex->unlock();
   if (changed) emit Mixer5TypeChanged(value);
}

qint8 MixerSettings::getMixer5Vector(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Mixer5Vector[index];
}
void MixerSettings::setMixer5Vector(quint32 index, qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer5Vector[index] != value;
   data.Mixer5Vector[index] = value;
   mutex->unlock();
   if (changed) emit Mixer5VectorChanged(index,value);
}

qint8 MixerSettings::getMixer5Vector_ThrottleCurve1() const
{
   QMutexLocker locker(mutex);
   return data.Mixer5Vector[0];
}
void MixerSettings::setMixer5Vector_ThrottleCurve1(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer5Vector[0] != value;
   data.Mixer5Vector[0] = value;
   mutex->unlock();
   if (changed) emit Mixer5Vector_ThrottleCurve1Changed(value);
}

qint8 MixerSettings::getMixer5Vector_ThrottleCurve2() const
{
   QMutexLocker locker(mutex);
   return data.Mixer5Vector[1];
}
void MixerSettings::setMixer5Vector_ThrottleCurve2(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer5Vector[1] != value;
   data.Mixer5Vector[1] = value;
   mutex->unlock();
   if (changed) emit Mixer5Vector_ThrottleCurve2Changed(value);
}

qint8 MixerSettings::getMixer5Vector_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Mixer5Vector[2];
}
void MixerSettings::setMixer5Vector_Roll(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer5Vector[2] != value;
   data.Mixer5Vector[2] = value;
   mutex->unlock();
   if (changed) emit Mixer5Vector_RollChanged(value);
}

qint8 MixerSettings::getMixer5Vector_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Mixer5Vector[3];
}
void MixerSettings::setMixer5Vector_Pitch(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer5Vector[3] != value;
   data.Mixer5Vector[3] = value;
   mutex->unlock();
   if (changed) emit Mixer5Vector_PitchChanged(value);
}

qint8 MixerSettings::getMixer5Vector_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Mixer5Vector[4];
}
void MixerSettings::setMixer5Vector_Yaw(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer5Vector[4] != value;
   data.Mixer5Vector[4] = value;
   mutex->unlock();
   if (changed) emit Mixer5Vector_YawChanged(value);
}

quint8 MixerSettings::getMixer6Type() const
{
   QMutexLocker locker(mutex);
   return data.Mixer6Type;
}
void MixerSettings::setMixer6Type(quint8 value)
{
   mutex->lock();
   bool changed = data.Mixer6Type != value;
   data.Mixer6Type = value;
   mutex->unlock();
   if (changed) emit Mixer6TypeChanged(value);
}

qint8 MixerSettings::getMixer6Vector(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Mixer6Vector[index];
}
void MixerSettings::setMixer6Vector(quint32 index, qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer6Vector[index] != value;
   data.Mixer6Vector[index] = value;
   mutex->unlock();
   if (changed) emit Mixer6VectorChanged(index,value);
}

qint8 MixerSettings::getMixer6Vector_ThrottleCurve1() const
{
   QMutexLocker locker(mutex);
   return data.Mixer6Vector[0];
}
void MixerSettings::setMixer6Vector_ThrottleCurve1(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer6Vector[0] != value;
   data.Mixer6Vector[0] = value;
   mutex->unlock();
   if (changed) emit Mixer6Vector_ThrottleCurve1Changed(value);
}

qint8 MixerSettings::getMixer6Vector_ThrottleCurve2() const
{
   QMutexLocker locker(mutex);
   return data.Mixer6Vector[1];
}
void MixerSettings::setMixer6Vector_ThrottleCurve2(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer6Vector[1] != value;
   data.Mixer6Vector[1] = value;
   mutex->unlock();
   if (changed) emit Mixer6Vector_ThrottleCurve2Changed(value);
}

qint8 MixerSettings::getMixer6Vector_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Mixer6Vector[2];
}
void MixerSettings::setMixer6Vector_Roll(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer6Vector[2] != value;
   data.Mixer6Vector[2] = value;
   mutex->unlock();
   if (changed) emit Mixer6Vector_RollChanged(value);
}

qint8 MixerSettings::getMixer6Vector_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Mixer6Vector[3];
}
void MixerSettings::setMixer6Vector_Pitch(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer6Vector[3] != value;
   data.Mixer6Vector[3] = value;
   mutex->unlock();
   if (changed) emit Mixer6Vector_PitchChanged(value);
}

qint8 MixerSettings::getMixer6Vector_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Mixer6Vector[4];
}
void MixerSettings::setMixer6Vector_Yaw(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer6Vector[4] != value;
   data.Mixer6Vector[4] = value;
   mutex->unlock();
   if (changed) emit Mixer6Vector_YawChanged(value);
}

quint8 MixerSettings::getMixer7Type() const
{
   QMutexLocker locker(mutex);
   return data.Mixer7Type;
}
void MixerSettings::setMixer7Type(quint8 value)
{
   mutex->lock();
   bool changed = data.Mixer7Type != value;
   data.Mixer7Type = value;
   mutex->unlock();
   if (changed) emit Mixer7TypeChanged(value);
}

qint8 MixerSettings::getMixer7Vector(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Mixer7Vector[index];
}
void MixerSettings::setMixer7Vector(quint32 index, qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer7Vector[index] != value;
   data.Mixer7Vector[index] = value;
   mutex->unlock();
   if (changed) emit Mixer7VectorChanged(index,value);
}

qint8 MixerSettings::getMixer7Vector_ThrottleCurve1() const
{
   QMutexLocker locker(mutex);
   return data.Mixer7Vector[0];
}
void MixerSettings::setMixer7Vector_ThrottleCurve1(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer7Vector[0] != value;
   data.Mixer7Vector[0] = value;
   mutex->unlock();
   if (changed) emit Mixer7Vector_ThrottleCurve1Changed(value);
}

qint8 MixerSettings::getMixer7Vector_ThrottleCurve2() const
{
   QMutexLocker locker(mutex);
   return data.Mixer7Vector[1];
}
void MixerSettings::setMixer7Vector_ThrottleCurve2(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer7Vector[1] != value;
   data.Mixer7Vector[1] = value;
   mutex->unlock();
   if (changed) emit Mixer7Vector_ThrottleCurve2Changed(value);
}

qint8 MixerSettings::getMixer7Vector_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Mixer7Vector[2];
}
void MixerSettings::setMixer7Vector_Roll(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer7Vector[2] != value;
   data.Mixer7Vector[2] = value;
   mutex->unlock();
   if (changed) emit Mixer7Vector_RollChanged(value);
}

qint8 MixerSettings::getMixer7Vector_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Mixer7Vector[3];
}
void MixerSettings::setMixer7Vector_Pitch(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer7Vector[3] != value;
   data.Mixer7Vector[3] = value;
   mutex->unlock();
   if (changed) emit Mixer7Vector_PitchChanged(value);
}

qint8 MixerSettings::getMixer7Vector_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Mixer7Vector[4];
}
void MixerSettings::setMixer7Vector_Yaw(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer7Vector[4] != value;
   data.Mixer7Vector[4] = value;
   mutex->unlock();
   if (changed) emit Mixer7Vector_YawChanged(value);
}

quint8 MixerSettings::getMixer8Type() const
{
   QMutexLocker locker(mutex);
   return data.Mixer8Type;
}
void MixerSettings::setMixer8Type(quint8 value)
{
   mutex->lock();
   bool changed = data.Mixer8Type != value;
   data.Mixer8Type = value;
   mutex->unlock();
   if (changed) emit Mixer8TypeChanged(value);
}

qint8 MixerSettings::getMixer8Vector(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Mixer8Vector[index];
}
void MixerSettings::setMixer8Vector(quint32 index, qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer8Vector[index] != value;
   data.Mixer8Vector[index] = value;
   mutex->unlock();
   if (changed) emit Mixer8VectorChanged(index,value);
}

qint8 MixerSettings::getMixer8Vector_ThrottleCurve1() const
{
   QMutexLocker locker(mutex);
   return data.Mixer8Vector[0];
}
void MixerSettings::setMixer8Vector_ThrottleCurve1(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer8Vector[0] != value;
   data.Mixer8Vector[0] = value;
   mutex->unlock();
   if (changed) emit Mixer8Vector_ThrottleCurve1Changed(value);
}

qint8 MixerSettings::getMixer8Vector_ThrottleCurve2() const
{
   QMutexLocker locker(mutex);
   return data.Mixer8Vector[1];
}
void MixerSettings::setMixer8Vector_ThrottleCurve2(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer8Vector[1] != value;
   data.Mixer8Vector[1] = value;
   mutex->unlock();
   if (changed) emit Mixer8Vector_ThrottleCurve2Changed(value);
}

qint8 MixerSettings::getMixer8Vector_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Mixer8Vector[2];
}
void MixerSettings::setMixer8Vector_Roll(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer8Vector[2] != value;
   data.Mixer8Vector[2] = value;
   mutex->unlock();
   if (changed) emit Mixer8Vector_RollChanged(value);
}

qint8 MixerSettings::getMixer8Vector_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Mixer8Vector[3];
}
void MixerSettings::setMixer8Vector_Pitch(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer8Vector[3] != value;
   data.Mixer8Vector[3] = value;
   mutex->unlock();
   if (changed) emit Mixer8Vector_PitchChanged(value);
}

qint8 MixerSettings::getMixer8Vector_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Mixer8Vector[4];
}
void MixerSettings::setMixer8Vector_Yaw(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer8Vector[4] != value;
   data.Mixer8Vector[4] = value;
   mutex->unlock();
   if (changed) emit Mixer8Vector_YawChanged(value);
}

quint8 MixerSettings::getMixer9Type() const
{
   QMutexLocker locker(mutex);
   return data.Mixer9Type;
}
void MixerSettings::setMixer9Type(quint8 value)
{
   mutex->lock();
   bool changed = data.Mixer9Type != value;
   data.Mixer9Type = value;
   mutex->unlock();
   if (changed) emit Mixer9TypeChanged(value);
}

qint8 MixerSettings::getMixer9Vector(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Mixer9Vector[index];
}
void MixerSettings::setMixer9Vector(quint32 index, qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer9Vector[index] != value;
   data.Mixer9Vector[index] = value;
   mutex->unlock();
   if (changed) emit Mixer9VectorChanged(index,value);
}

qint8 MixerSettings::getMixer9Vector_ThrottleCurve1() const
{
   QMutexLocker locker(mutex);
   return data.Mixer9Vector[0];
}
void MixerSettings::setMixer9Vector_ThrottleCurve1(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer9Vector[0] != value;
   data.Mixer9Vector[0] = value;
   mutex->unlock();
   if (changed) emit Mixer9Vector_ThrottleCurve1Changed(value);
}

qint8 MixerSettings::getMixer9Vector_ThrottleCurve2() const
{
   QMutexLocker locker(mutex);
   return data.Mixer9Vector[1];
}
void MixerSettings::setMixer9Vector_ThrottleCurve2(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer9Vector[1] != value;
   data.Mixer9Vector[1] = value;
   mutex->unlock();
   if (changed) emit Mixer9Vector_ThrottleCurve2Changed(value);
}

qint8 MixerSettings::getMixer9Vector_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Mixer9Vector[2];
}
void MixerSettings::setMixer9Vector_Roll(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer9Vector[2] != value;
   data.Mixer9Vector[2] = value;
   mutex->unlock();
   if (changed) emit Mixer9Vector_RollChanged(value);
}

qint8 MixerSettings::getMixer9Vector_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Mixer9Vector[3];
}
void MixerSettings::setMixer9Vector_Pitch(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer9Vector[3] != value;
   data.Mixer9Vector[3] = value;
   mutex->unlock();
   if (changed) emit Mixer9Vector_PitchChanged(value);
}

qint8 MixerSettings::getMixer9Vector_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Mixer9Vector[4];
}
void MixerSettings::setMixer9Vector_Yaw(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer9Vector[4] != value;
   data.Mixer9Vector[4] = value;
   mutex->unlock();
   if (changed) emit Mixer9Vector_YawChanged(value);
}

quint8 MixerSettings::getMixer10Type() const
{
   QMutexLocker locker(mutex);
   return data.Mixer10Type;
}
void MixerSettings::setMixer10Type(quint8 value)
{
   mutex->lock();
   bool changed = data.Mixer10Type != value;
   data.Mixer10Type = value;
   mutex->unlock();
   if (changed) emit Mixer10TypeChanged(value);
}

qint8 MixerSettings::getMixer10Vector(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Mixer10Vector[index];
}
void MixerSettings::setMixer10Vector(quint32 index, qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer10Vector[index] != value;
   data.Mixer10Vector[index] = value;
   mutex->unlock();
   if (changed) emit Mixer10VectorChanged(index,value);
}

qint8 MixerSettings::getMixer10Vector_ThrottleCurve1() const
{
   QMutexLocker locker(mutex);
   return data.Mixer10Vector[0];
}
void MixerSettings::setMixer10Vector_ThrottleCurve1(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer10Vector[0] != value;
   data.Mixer10Vector[0] = value;
   mutex->unlock();
   if (changed) emit Mixer10Vector_ThrottleCurve1Changed(value);
}

qint8 MixerSettings::getMixer10Vector_ThrottleCurve2() const
{
   QMutexLocker locker(mutex);
   return data.Mixer10Vector[1];
}
void MixerSettings::setMixer10Vector_ThrottleCurve2(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer10Vector[1] != value;
   data.Mixer10Vector[1] = value;
   mutex->unlock();
   if (changed) emit Mixer10Vector_ThrottleCurve2Changed(value);
}

qint8 MixerSettings::getMixer10Vector_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Mixer10Vector[2];
}
void MixerSettings::setMixer10Vector_Roll(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer10Vector[2] != value;
   data.Mixer10Vector[2] = value;
   mutex->unlock();
   if (changed) emit Mixer10Vector_RollChanged(value);
}

qint8 MixerSettings::getMixer10Vector_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Mixer10Vector[3];
}
void MixerSettings::setMixer10Vector_Pitch(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer10Vector[3] != value;
   data.Mixer10Vector[3] = value;
   mutex->unlock();
   if (changed) emit Mixer10Vector_PitchChanged(value);
}

qint8 MixerSettings::getMixer10Vector_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Mixer10Vector[4];
}
void MixerSettings::setMixer10Vector_Yaw(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer10Vector[4] != value;
   data.Mixer10Vector[4] = value;
   mutex->unlock();
   if (changed) emit Mixer10Vector_YawChanged(value);
}

quint8 MixerSettings::getMixer11Type() const
{
   QMutexLocker locker(mutex);
   return data.Mixer11Type;
}
void MixerSettings::setMixer11Type(quint8 value)
{
   mutex->lock();
   bool changed = data.Mixer11Type != value;
   data.Mixer11Type = value;
   mutex->unlock();
   if (changed) emit Mixer11TypeChanged(value);
}

qint8 MixerSettings::getMixer11Vector(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Mixer11Vector[index];
}
void MixerSettings::setMixer11Vector(quint32 index, qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer11Vector[index] != value;
   data.Mixer11Vector[index] = value;
   mutex->unlock();
   if (changed) emit Mixer11VectorChanged(index,value);
}

qint8 MixerSettings::getMixer11Vector_ThrottleCurve1() const
{
   QMutexLocker locker(mutex);
   return data.Mixer11Vector[0];
}
void MixerSettings::setMixer11Vector_ThrottleCurve1(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer11Vector[0] != value;
   data.Mixer11Vector[0] = value;
   mutex->unlock();
   if (changed) emit Mixer11Vector_ThrottleCurve1Changed(value);
}

qint8 MixerSettings::getMixer11Vector_ThrottleCurve2() const
{
   QMutexLocker locker(mutex);
   return data.Mixer11Vector[1];
}
void MixerSettings::setMixer11Vector_ThrottleCurve2(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer11Vector[1] != value;
   data.Mixer11Vector[1] = value;
   mutex->unlock();
   if (changed) emit Mixer11Vector_ThrottleCurve2Changed(value);
}

qint8 MixerSettings::getMixer11Vector_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Mixer11Vector[2];
}
void MixerSettings::setMixer11Vector_Roll(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer11Vector[2] != value;
   data.Mixer11Vector[2] = value;
   mutex->unlock();
   if (changed) emit Mixer11Vector_RollChanged(value);
}

qint8 MixerSettings::getMixer11Vector_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Mixer11Vector[3];
}
void MixerSettings::setMixer11Vector_Pitch(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer11Vector[3] != value;
   data.Mixer11Vector[3] = value;
   mutex->unlock();
   if (changed) emit Mixer11Vector_PitchChanged(value);
}

qint8 MixerSettings::getMixer11Vector_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Mixer11Vector[4];
}
void MixerSettings::setMixer11Vector_Yaw(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer11Vector[4] != value;
   data.Mixer11Vector[4] = value;
   mutex->unlock();
   if (changed) emit Mixer11Vector_YawChanged(value);
}

quint8 MixerSettings::getMixer12Type() const
{
   QMutexLocker locker(mutex);
   return data.Mixer12Type;
}
void MixerSettings::setMixer12Type(quint8 value)
{
   mutex->lock();
   bool changed = data.Mixer12Type != value;
   data.Mixer12Type = value;
   mutex->unlock();
   if (changed) emit Mixer12TypeChanged(value);
}

qint8 MixerSettings::getMixer12Vector(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Mixer12Vector[index];
}
void MixerSettings::setMixer12Vector(quint32 index, qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer12Vector[index] != value;
   data.Mixer12Vector[index] = value;
   mutex->unlock();
   if (changed) emit Mixer12VectorChanged(index,value);
}

qint8 MixerSettings::getMixer12Vector_ThrottleCurve1() const
{
   QMutexLocker locker(mutex);
   return data.Mixer12Vector[0];
}
void MixerSettings::setMixer12Vector_ThrottleCurve1(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer12Vector[0] != value;
   data.Mixer12Vector[0] = value;
   mutex->unlock();
   if (changed) emit Mixer12Vector_ThrottleCurve1Changed(value);
}

qint8 MixerSettings::getMixer12Vector_ThrottleCurve2() const
{
   QMutexLocker locker(mutex);
   return data.Mixer12Vector[1];
}
void MixerSettings::setMixer12Vector_ThrottleCurve2(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer12Vector[1] != value;
   data.Mixer12Vector[1] = value;
   mutex->unlock();
   if (changed) emit Mixer12Vector_ThrottleCurve2Changed(value);
}

qint8 MixerSettings::getMixer12Vector_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Mixer12Vector[2];
}
void MixerSettings::setMixer12Vector_Roll(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer12Vector[2] != value;
   data.Mixer12Vector[2] = value;
   mutex->unlock();
   if (changed) emit Mixer12Vector_RollChanged(value);
}

qint8 MixerSettings::getMixer12Vector_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Mixer12Vector[3];
}
void MixerSettings::setMixer12Vector_Pitch(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer12Vector[3] != value;
   data.Mixer12Vector[3] = value;
   mutex->unlock();
   if (changed) emit Mixer12Vector_PitchChanged(value);
}

qint8 MixerSettings::getMixer12Vector_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Mixer12Vector[4];
}
void MixerSettings::setMixer12Vector_Yaw(qint8 value)
{
   mutex->lock();
   bool changed = data.Mixer12Vector[4] != value;
   data.Mixer12Vector[4] = value;
   mutex->unlock();
   if (changed) emit Mixer12Vector_YawChanged(value);
}


