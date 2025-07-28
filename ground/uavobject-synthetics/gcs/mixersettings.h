/**
 ******************************************************************************
 *
 * @file       mixersettings.h
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
#ifndef MIXERSETTINGS_H
#define MIXERSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT MixerSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float MaxAccel READ getMaxAccel WRITE setMaxAccel NOTIFY MaxAccelChanged);
    Q_PROPERTY(float FeedForward READ getFeedForward WRITE setFeedForward NOTIFY FeedForwardChanged);
    Q_PROPERTY(float AccelTime READ getAccelTime WRITE setAccelTime NOTIFY AccelTimeChanged);
    Q_PROPERTY(float DecelTime READ getDecelTime WRITE setDecelTime NOTIFY DecelTimeChanged);
    Q_PROPERTY(float ThrottleCurve1_0 READ getThrottleCurve1_0 WRITE setThrottleCurve1_0 NOTIFY ThrottleCurve1_0Changed);
    Q_PROPERTY(float ThrottleCurve1_25 READ getThrottleCurve1_25 WRITE setThrottleCurve1_25 NOTIFY ThrottleCurve1_25Changed);
    Q_PROPERTY(float ThrottleCurve1_50 READ getThrottleCurve1_50 WRITE setThrottleCurve1_50 NOTIFY ThrottleCurve1_50Changed);
    Q_PROPERTY(float ThrottleCurve1_75 READ getThrottleCurve1_75 WRITE setThrottleCurve1_75 NOTIFY ThrottleCurve1_75Changed);
    Q_PROPERTY(float ThrottleCurve1_100 READ getThrottleCurve1_100 WRITE setThrottleCurve1_100 NOTIFY ThrottleCurve1_100Changed);
    Q_PROPERTY(float ThrottleCurve2_0 READ getThrottleCurve2_0 WRITE setThrottleCurve2_0 NOTIFY ThrottleCurve2_0Changed);
    Q_PROPERTY(float ThrottleCurve2_25 READ getThrottleCurve2_25 WRITE setThrottleCurve2_25 NOTIFY ThrottleCurve2_25Changed);
    Q_PROPERTY(float ThrottleCurve2_50 READ getThrottleCurve2_50 WRITE setThrottleCurve2_50 NOTIFY ThrottleCurve2_50Changed);
    Q_PROPERTY(float ThrottleCurve2_75 READ getThrottleCurve2_75 WRITE setThrottleCurve2_75 NOTIFY ThrottleCurve2_75Changed);
    Q_PROPERTY(float ThrottleCurve2_100 READ getThrottleCurve2_100 WRITE setThrottleCurve2_100 NOTIFY ThrottleCurve2_100Changed);
    Q_PROPERTY(qint8 MixerValueRoll READ getMixerValueRoll WRITE setMixerValueRoll NOTIFY MixerValueRollChanged);
    Q_PROPERTY(qint8 MixerValuePitch READ getMixerValuePitch WRITE setMixerValuePitch NOTIFY MixerValuePitchChanged);
    Q_PROPERTY(qint8 MixerValueYaw READ getMixerValueYaw WRITE setMixerValueYaw NOTIFY MixerValueYawChanged);
    Q_PROPERTY(quint8 Curve2Source READ getCurve2Source WRITE setCurve2Source NOTIFY Curve2SourceChanged);
    Q_PROPERTY(quint8 Mixer1Type READ getMixer1Type WRITE setMixer1Type NOTIFY Mixer1TypeChanged);
    Q_PROPERTY(qint8 Mixer1Vector_ThrottleCurve1 READ getMixer1Vector_ThrottleCurve1 WRITE setMixer1Vector_ThrottleCurve1 NOTIFY Mixer1Vector_ThrottleCurve1Changed);
    Q_PROPERTY(qint8 Mixer1Vector_ThrottleCurve2 READ getMixer1Vector_ThrottleCurve2 WRITE setMixer1Vector_ThrottleCurve2 NOTIFY Mixer1Vector_ThrottleCurve2Changed);
    Q_PROPERTY(qint8 Mixer1Vector_Roll READ getMixer1Vector_Roll WRITE setMixer1Vector_Roll NOTIFY Mixer1Vector_RollChanged);
    Q_PROPERTY(qint8 Mixer1Vector_Pitch READ getMixer1Vector_Pitch WRITE setMixer1Vector_Pitch NOTIFY Mixer1Vector_PitchChanged);
    Q_PROPERTY(qint8 Mixer1Vector_Yaw READ getMixer1Vector_Yaw WRITE setMixer1Vector_Yaw NOTIFY Mixer1Vector_YawChanged);
    Q_PROPERTY(quint8 Mixer2Type READ getMixer2Type WRITE setMixer2Type NOTIFY Mixer2TypeChanged);
    Q_PROPERTY(qint8 Mixer2Vector_ThrottleCurve1 READ getMixer2Vector_ThrottleCurve1 WRITE setMixer2Vector_ThrottleCurve1 NOTIFY Mixer2Vector_ThrottleCurve1Changed);
    Q_PROPERTY(qint8 Mixer2Vector_ThrottleCurve2 READ getMixer2Vector_ThrottleCurve2 WRITE setMixer2Vector_ThrottleCurve2 NOTIFY Mixer2Vector_ThrottleCurve2Changed);
    Q_PROPERTY(qint8 Mixer2Vector_Roll READ getMixer2Vector_Roll WRITE setMixer2Vector_Roll NOTIFY Mixer2Vector_RollChanged);
    Q_PROPERTY(qint8 Mixer2Vector_Pitch READ getMixer2Vector_Pitch WRITE setMixer2Vector_Pitch NOTIFY Mixer2Vector_PitchChanged);
    Q_PROPERTY(qint8 Mixer2Vector_Yaw READ getMixer2Vector_Yaw WRITE setMixer2Vector_Yaw NOTIFY Mixer2Vector_YawChanged);
    Q_PROPERTY(quint8 Mixer3Type READ getMixer3Type WRITE setMixer3Type NOTIFY Mixer3TypeChanged);
    Q_PROPERTY(qint8 Mixer3Vector_ThrottleCurve1 READ getMixer3Vector_ThrottleCurve1 WRITE setMixer3Vector_ThrottleCurve1 NOTIFY Mixer3Vector_ThrottleCurve1Changed);
    Q_PROPERTY(qint8 Mixer3Vector_ThrottleCurve2 READ getMixer3Vector_ThrottleCurve2 WRITE setMixer3Vector_ThrottleCurve2 NOTIFY Mixer3Vector_ThrottleCurve2Changed);
    Q_PROPERTY(qint8 Mixer3Vector_Roll READ getMixer3Vector_Roll WRITE setMixer3Vector_Roll NOTIFY Mixer3Vector_RollChanged);
    Q_PROPERTY(qint8 Mixer3Vector_Pitch READ getMixer3Vector_Pitch WRITE setMixer3Vector_Pitch NOTIFY Mixer3Vector_PitchChanged);
    Q_PROPERTY(qint8 Mixer3Vector_Yaw READ getMixer3Vector_Yaw WRITE setMixer3Vector_Yaw NOTIFY Mixer3Vector_YawChanged);
    Q_PROPERTY(quint8 Mixer4Type READ getMixer4Type WRITE setMixer4Type NOTIFY Mixer4TypeChanged);
    Q_PROPERTY(qint8 Mixer4Vector_ThrottleCurve1 READ getMixer4Vector_ThrottleCurve1 WRITE setMixer4Vector_ThrottleCurve1 NOTIFY Mixer4Vector_ThrottleCurve1Changed);
    Q_PROPERTY(qint8 Mixer4Vector_ThrottleCurve2 READ getMixer4Vector_ThrottleCurve2 WRITE setMixer4Vector_ThrottleCurve2 NOTIFY Mixer4Vector_ThrottleCurve2Changed);
    Q_PROPERTY(qint8 Mixer4Vector_Roll READ getMixer4Vector_Roll WRITE setMixer4Vector_Roll NOTIFY Mixer4Vector_RollChanged);
    Q_PROPERTY(qint8 Mixer4Vector_Pitch READ getMixer4Vector_Pitch WRITE setMixer4Vector_Pitch NOTIFY Mixer4Vector_PitchChanged);
    Q_PROPERTY(qint8 Mixer4Vector_Yaw READ getMixer4Vector_Yaw WRITE setMixer4Vector_Yaw NOTIFY Mixer4Vector_YawChanged);
    Q_PROPERTY(quint8 Mixer5Type READ getMixer5Type WRITE setMixer5Type NOTIFY Mixer5TypeChanged);
    Q_PROPERTY(qint8 Mixer5Vector_ThrottleCurve1 READ getMixer5Vector_ThrottleCurve1 WRITE setMixer5Vector_ThrottleCurve1 NOTIFY Mixer5Vector_ThrottleCurve1Changed);
    Q_PROPERTY(qint8 Mixer5Vector_ThrottleCurve2 READ getMixer5Vector_ThrottleCurve2 WRITE setMixer5Vector_ThrottleCurve2 NOTIFY Mixer5Vector_ThrottleCurve2Changed);
    Q_PROPERTY(qint8 Mixer5Vector_Roll READ getMixer5Vector_Roll WRITE setMixer5Vector_Roll NOTIFY Mixer5Vector_RollChanged);
    Q_PROPERTY(qint8 Mixer5Vector_Pitch READ getMixer5Vector_Pitch WRITE setMixer5Vector_Pitch NOTIFY Mixer5Vector_PitchChanged);
    Q_PROPERTY(qint8 Mixer5Vector_Yaw READ getMixer5Vector_Yaw WRITE setMixer5Vector_Yaw NOTIFY Mixer5Vector_YawChanged);
    Q_PROPERTY(quint8 Mixer6Type READ getMixer6Type WRITE setMixer6Type NOTIFY Mixer6TypeChanged);
    Q_PROPERTY(qint8 Mixer6Vector_ThrottleCurve1 READ getMixer6Vector_ThrottleCurve1 WRITE setMixer6Vector_ThrottleCurve1 NOTIFY Mixer6Vector_ThrottleCurve1Changed);
    Q_PROPERTY(qint8 Mixer6Vector_ThrottleCurve2 READ getMixer6Vector_ThrottleCurve2 WRITE setMixer6Vector_ThrottleCurve2 NOTIFY Mixer6Vector_ThrottleCurve2Changed);
    Q_PROPERTY(qint8 Mixer6Vector_Roll READ getMixer6Vector_Roll WRITE setMixer6Vector_Roll NOTIFY Mixer6Vector_RollChanged);
    Q_PROPERTY(qint8 Mixer6Vector_Pitch READ getMixer6Vector_Pitch WRITE setMixer6Vector_Pitch NOTIFY Mixer6Vector_PitchChanged);
    Q_PROPERTY(qint8 Mixer6Vector_Yaw READ getMixer6Vector_Yaw WRITE setMixer6Vector_Yaw NOTIFY Mixer6Vector_YawChanged);
    Q_PROPERTY(quint8 Mixer7Type READ getMixer7Type WRITE setMixer7Type NOTIFY Mixer7TypeChanged);
    Q_PROPERTY(qint8 Mixer7Vector_ThrottleCurve1 READ getMixer7Vector_ThrottleCurve1 WRITE setMixer7Vector_ThrottleCurve1 NOTIFY Mixer7Vector_ThrottleCurve1Changed);
    Q_PROPERTY(qint8 Mixer7Vector_ThrottleCurve2 READ getMixer7Vector_ThrottleCurve2 WRITE setMixer7Vector_ThrottleCurve2 NOTIFY Mixer7Vector_ThrottleCurve2Changed);
    Q_PROPERTY(qint8 Mixer7Vector_Roll READ getMixer7Vector_Roll WRITE setMixer7Vector_Roll NOTIFY Mixer7Vector_RollChanged);
    Q_PROPERTY(qint8 Mixer7Vector_Pitch READ getMixer7Vector_Pitch WRITE setMixer7Vector_Pitch NOTIFY Mixer7Vector_PitchChanged);
    Q_PROPERTY(qint8 Mixer7Vector_Yaw READ getMixer7Vector_Yaw WRITE setMixer7Vector_Yaw NOTIFY Mixer7Vector_YawChanged);
    Q_PROPERTY(quint8 Mixer8Type READ getMixer8Type WRITE setMixer8Type NOTIFY Mixer8TypeChanged);
    Q_PROPERTY(qint8 Mixer8Vector_ThrottleCurve1 READ getMixer8Vector_ThrottleCurve1 WRITE setMixer8Vector_ThrottleCurve1 NOTIFY Mixer8Vector_ThrottleCurve1Changed);
    Q_PROPERTY(qint8 Mixer8Vector_ThrottleCurve2 READ getMixer8Vector_ThrottleCurve2 WRITE setMixer8Vector_ThrottleCurve2 NOTIFY Mixer8Vector_ThrottleCurve2Changed);
    Q_PROPERTY(qint8 Mixer8Vector_Roll READ getMixer8Vector_Roll WRITE setMixer8Vector_Roll NOTIFY Mixer8Vector_RollChanged);
    Q_PROPERTY(qint8 Mixer8Vector_Pitch READ getMixer8Vector_Pitch WRITE setMixer8Vector_Pitch NOTIFY Mixer8Vector_PitchChanged);
    Q_PROPERTY(qint8 Mixer8Vector_Yaw READ getMixer8Vector_Yaw WRITE setMixer8Vector_Yaw NOTIFY Mixer8Vector_YawChanged);
    Q_PROPERTY(quint8 Mixer9Type READ getMixer9Type WRITE setMixer9Type NOTIFY Mixer9TypeChanged);
    Q_PROPERTY(qint8 Mixer9Vector_ThrottleCurve1 READ getMixer9Vector_ThrottleCurve1 WRITE setMixer9Vector_ThrottleCurve1 NOTIFY Mixer9Vector_ThrottleCurve1Changed);
    Q_PROPERTY(qint8 Mixer9Vector_ThrottleCurve2 READ getMixer9Vector_ThrottleCurve2 WRITE setMixer9Vector_ThrottleCurve2 NOTIFY Mixer9Vector_ThrottleCurve2Changed);
    Q_PROPERTY(qint8 Mixer9Vector_Roll READ getMixer9Vector_Roll WRITE setMixer9Vector_Roll NOTIFY Mixer9Vector_RollChanged);
    Q_PROPERTY(qint8 Mixer9Vector_Pitch READ getMixer9Vector_Pitch WRITE setMixer9Vector_Pitch NOTIFY Mixer9Vector_PitchChanged);
    Q_PROPERTY(qint8 Mixer9Vector_Yaw READ getMixer9Vector_Yaw WRITE setMixer9Vector_Yaw NOTIFY Mixer9Vector_YawChanged);
    Q_PROPERTY(quint8 Mixer10Type READ getMixer10Type WRITE setMixer10Type NOTIFY Mixer10TypeChanged);
    Q_PROPERTY(qint8 Mixer10Vector_ThrottleCurve1 READ getMixer10Vector_ThrottleCurve1 WRITE setMixer10Vector_ThrottleCurve1 NOTIFY Mixer10Vector_ThrottleCurve1Changed);
    Q_PROPERTY(qint8 Mixer10Vector_ThrottleCurve2 READ getMixer10Vector_ThrottleCurve2 WRITE setMixer10Vector_ThrottleCurve2 NOTIFY Mixer10Vector_ThrottleCurve2Changed);
    Q_PROPERTY(qint8 Mixer10Vector_Roll READ getMixer10Vector_Roll WRITE setMixer10Vector_Roll NOTIFY Mixer10Vector_RollChanged);
    Q_PROPERTY(qint8 Mixer10Vector_Pitch READ getMixer10Vector_Pitch WRITE setMixer10Vector_Pitch NOTIFY Mixer10Vector_PitchChanged);
    Q_PROPERTY(qint8 Mixer10Vector_Yaw READ getMixer10Vector_Yaw WRITE setMixer10Vector_Yaw NOTIFY Mixer10Vector_YawChanged);
    Q_PROPERTY(quint8 Mixer11Type READ getMixer11Type WRITE setMixer11Type NOTIFY Mixer11TypeChanged);
    Q_PROPERTY(qint8 Mixer11Vector_ThrottleCurve1 READ getMixer11Vector_ThrottleCurve1 WRITE setMixer11Vector_ThrottleCurve1 NOTIFY Mixer11Vector_ThrottleCurve1Changed);
    Q_PROPERTY(qint8 Mixer11Vector_ThrottleCurve2 READ getMixer11Vector_ThrottleCurve2 WRITE setMixer11Vector_ThrottleCurve2 NOTIFY Mixer11Vector_ThrottleCurve2Changed);
    Q_PROPERTY(qint8 Mixer11Vector_Roll READ getMixer11Vector_Roll WRITE setMixer11Vector_Roll NOTIFY Mixer11Vector_RollChanged);
    Q_PROPERTY(qint8 Mixer11Vector_Pitch READ getMixer11Vector_Pitch WRITE setMixer11Vector_Pitch NOTIFY Mixer11Vector_PitchChanged);
    Q_PROPERTY(qint8 Mixer11Vector_Yaw READ getMixer11Vector_Yaw WRITE setMixer11Vector_Yaw NOTIFY Mixer11Vector_YawChanged);
    Q_PROPERTY(quint8 Mixer12Type READ getMixer12Type WRITE setMixer12Type NOTIFY Mixer12TypeChanged);
    Q_PROPERTY(qint8 Mixer12Vector_ThrottleCurve1 READ getMixer12Vector_ThrottleCurve1 WRITE setMixer12Vector_ThrottleCurve1 NOTIFY Mixer12Vector_ThrottleCurve1Changed);
    Q_PROPERTY(qint8 Mixer12Vector_ThrottleCurve2 READ getMixer12Vector_ThrottleCurve2 WRITE setMixer12Vector_ThrottleCurve2 NOTIFY Mixer12Vector_ThrottleCurve2Changed);
    Q_PROPERTY(qint8 Mixer12Vector_Roll READ getMixer12Vector_Roll WRITE setMixer12Vector_Roll NOTIFY Mixer12Vector_RollChanged);
    Q_PROPERTY(qint8 Mixer12Vector_Pitch READ getMixer12Vector_Pitch WRITE setMixer12Vector_Pitch NOTIFY Mixer12Vector_PitchChanged);
    Q_PROPERTY(qint8 Mixer12Vector_Yaw READ getMixer12Vector_Yaw WRITE setMixer12Vector_Yaw NOTIFY Mixer12Vector_YawChanged);


public:
    // Field structure
    typedef struct {
        float MaxAccel;
        float FeedForward;
        float AccelTime;
        float DecelTime;
        float ThrottleCurve1[5];
        float ThrottleCurve2[5];
        qint8 MixerValueRoll;
        qint8 MixerValuePitch;
        qint8 MixerValueYaw;
        quint8 Curve2Source;
        quint8 Mixer1Type;
        qint8 Mixer1Vector[5];
        quint8 Mixer2Type;
        qint8 Mixer2Vector[5];
        quint8 Mixer3Type;
        qint8 Mixer3Vector[5];
        quint8 Mixer4Type;
        qint8 Mixer4Vector[5];
        quint8 Mixer5Type;
        qint8 Mixer5Vector[5];
        quint8 Mixer6Type;
        qint8 Mixer6Vector[5];
        quint8 Mixer7Type;
        qint8 Mixer7Vector[5];
        quint8 Mixer8Type;
        qint8 Mixer8Vector[5];
        quint8 Mixer9Type;
        qint8 Mixer9Vector[5];
        quint8 Mixer10Type;
        qint8 Mixer10Vector[5];
        quint8 Mixer11Type;
        qint8 Mixer11Vector[5];
        quint8 Mixer12Type;
        qint8 Mixer12Vector[5];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field MaxAccel information
    // Field FeedForward information
    // Field AccelTime information
    // Field DecelTime information
    // Field ThrottleCurve1 information
    /* Array element names for field ThrottleCurve1 */
    typedef enum { THROTTLECURVE1_0=0, THROTTLECURVE1_25=1, THROTTLECURVE1_50=2, THROTTLECURVE1_75=3, THROTTLECURVE1_100=4 } ThrottleCurve1Elem;
    /* Number of elements for field ThrottleCurve1 */
    static const quint32 THROTTLECURVE1_NUMELEM = 5;
    // Field ThrottleCurve2 information
    /* Array element names for field ThrottleCurve2 */
    typedef enum { THROTTLECURVE2_0=0, THROTTLECURVE2_25=1, THROTTLECURVE2_50=2, THROTTLECURVE2_75=3, THROTTLECURVE2_100=4 } ThrottleCurve2Elem;
    /* Number of elements for field ThrottleCurve2 */
    static const quint32 THROTTLECURVE2_NUMELEM = 5;
    // Field MixerValueRoll information
    // Field MixerValuePitch information
    // Field MixerValueYaw information
    // Field Curve2Source information
    /* Enumeration options for field Curve2Source */
    typedef enum { CURVE2SOURCE_THROTTLE=0, CURVE2SOURCE_ROLL=1, CURVE2SOURCE_PITCH=2, CURVE2SOURCE_YAW=3, CURVE2SOURCE_COLLECTIVE=4, CURVE2SOURCE_ACCESSORY0=5, CURVE2SOURCE_ACCESSORY1=6, CURVE2SOURCE_ACCESSORY2=7, CURVE2SOURCE_ACCESSORY3=8, CURVE2SOURCE_ACCESSORY4=9, CURVE2SOURCE_ACCESSORY5=10 } Curve2SourceOptions;
    // Field Mixer1Type information
    /* Enumeration options for field Mixer1Type */
    typedef enum { MIXER1TYPE_DISABLED=0, MIXER1TYPE_MOTOR=1, MIXER1TYPE_REVERSABLEMOTOR=2, MIXER1TYPE_SERVO=3, MIXER1TYPE_CAMERAROLLORSERVO1=4, MIXER1TYPE_CAMERAPITCHORSERVO2=5, MIXER1TYPE_CAMERAYAW=6, MIXER1TYPE_ACCESSORY0=7, MIXER1TYPE_ACCESSORY1=8, MIXER1TYPE_ACCESSORY2=9, MIXER1TYPE_ACCESSORY3=10, MIXER1TYPE_ACCESSORY4=11, MIXER1TYPE_ACCESSORY5=12 } Mixer1TypeOptions;
    // Field Mixer1Vector information
    /* Array element names for field Mixer1Vector */
    typedef enum { MIXER1VECTOR_THROTTLECURVE1=0, MIXER1VECTOR_THROTTLECURVE2=1, MIXER1VECTOR_ROLL=2, MIXER1VECTOR_PITCH=3, MIXER1VECTOR_YAW=4 } Mixer1VectorElem;
    /* Number of elements for field Mixer1Vector */
    static const quint32 MIXER1VECTOR_NUMELEM = 5;
    // Field Mixer2Type information
    /* Enumeration options for field Mixer2Type */
    typedef enum { MIXER2TYPE_DISABLED=0, MIXER2TYPE_MOTOR=1, MIXER2TYPE_REVERSABLEMOTOR=2, MIXER2TYPE_SERVO=3, MIXER2TYPE_CAMERAROLLORSERVO1=4, MIXER2TYPE_CAMERAPITCHORSERVO2=5, MIXER2TYPE_CAMERAYAW=6, MIXER2TYPE_ACCESSORY0=7, MIXER2TYPE_ACCESSORY1=8, MIXER2TYPE_ACCESSORY2=9, MIXER2TYPE_ACCESSORY3=10, MIXER2TYPE_ACCESSORY4=11, MIXER2TYPE_ACCESSORY5=12 } Mixer2TypeOptions;
    // Field Mixer2Vector information
    /* Array element names for field Mixer2Vector */
    typedef enum { MIXER2VECTOR_THROTTLECURVE1=0, MIXER2VECTOR_THROTTLECURVE2=1, MIXER2VECTOR_ROLL=2, MIXER2VECTOR_PITCH=3, MIXER2VECTOR_YAW=4 } Mixer2VectorElem;
    /* Number of elements for field Mixer2Vector */
    static const quint32 MIXER2VECTOR_NUMELEM = 5;
    // Field Mixer3Type information
    /* Enumeration options for field Mixer3Type */
    typedef enum { MIXER3TYPE_DISABLED=0, MIXER3TYPE_MOTOR=1, MIXER3TYPE_REVERSABLEMOTOR=2, MIXER3TYPE_SERVO=3, MIXER3TYPE_CAMERAROLLORSERVO1=4, MIXER3TYPE_CAMERAPITCHORSERVO2=5, MIXER3TYPE_CAMERAYAW=6, MIXER3TYPE_ACCESSORY0=7, MIXER3TYPE_ACCESSORY1=8, MIXER3TYPE_ACCESSORY2=9, MIXER3TYPE_ACCESSORY3=10, MIXER3TYPE_ACCESSORY4=11, MIXER3TYPE_ACCESSORY5=12 } Mixer3TypeOptions;
    // Field Mixer3Vector information
    /* Array element names for field Mixer3Vector */
    typedef enum { MIXER3VECTOR_THROTTLECURVE1=0, MIXER3VECTOR_THROTTLECURVE2=1, MIXER3VECTOR_ROLL=2, MIXER3VECTOR_PITCH=3, MIXER3VECTOR_YAW=4 } Mixer3VectorElem;
    /* Number of elements for field Mixer3Vector */
    static const quint32 MIXER3VECTOR_NUMELEM = 5;
    // Field Mixer4Type information
    /* Enumeration options for field Mixer4Type */
    typedef enum { MIXER4TYPE_DISABLED=0, MIXER4TYPE_MOTOR=1, MIXER4TYPE_REVERSABLEMOTOR=2, MIXER4TYPE_SERVO=3, MIXER4TYPE_CAMERAROLLORSERVO1=4, MIXER4TYPE_CAMERAPITCHORSERVO2=5, MIXER4TYPE_CAMERAYAW=6, MIXER4TYPE_ACCESSORY0=7, MIXER4TYPE_ACCESSORY1=8, MIXER4TYPE_ACCESSORY2=9, MIXER4TYPE_ACCESSORY3=10, MIXER4TYPE_ACCESSORY4=11, MIXER4TYPE_ACCESSORY5=12 } Mixer4TypeOptions;
    // Field Mixer4Vector information
    /* Array element names for field Mixer4Vector */
    typedef enum { MIXER4VECTOR_THROTTLECURVE1=0, MIXER4VECTOR_THROTTLECURVE2=1, MIXER4VECTOR_ROLL=2, MIXER4VECTOR_PITCH=3, MIXER4VECTOR_YAW=4 } Mixer4VectorElem;
    /* Number of elements for field Mixer4Vector */
    static const quint32 MIXER4VECTOR_NUMELEM = 5;
    // Field Mixer5Type information
    /* Enumeration options for field Mixer5Type */
    typedef enum { MIXER5TYPE_DISABLED=0, MIXER5TYPE_MOTOR=1, MIXER5TYPE_REVERSABLEMOTOR=2, MIXER5TYPE_SERVO=3, MIXER5TYPE_CAMERAROLLORSERVO1=4, MIXER5TYPE_CAMERAPITCHORSERVO2=5, MIXER5TYPE_CAMERAYAW=6, MIXER5TYPE_ACCESSORY0=7, MIXER5TYPE_ACCESSORY1=8, MIXER5TYPE_ACCESSORY2=9, MIXER5TYPE_ACCESSORY3=10, MIXER5TYPE_ACCESSORY4=11, MIXER5TYPE_ACCESSORY5=12 } Mixer5TypeOptions;
    // Field Mixer5Vector information
    /* Array element names for field Mixer5Vector */
    typedef enum { MIXER5VECTOR_THROTTLECURVE1=0, MIXER5VECTOR_THROTTLECURVE2=1, MIXER5VECTOR_ROLL=2, MIXER5VECTOR_PITCH=3, MIXER5VECTOR_YAW=4 } Mixer5VectorElem;
    /* Number of elements for field Mixer5Vector */
    static const quint32 MIXER5VECTOR_NUMELEM = 5;
    // Field Mixer6Type information
    /* Enumeration options for field Mixer6Type */
    typedef enum { MIXER6TYPE_DISABLED=0, MIXER6TYPE_MOTOR=1, MIXER6TYPE_REVERSABLEMOTOR=2, MIXER6TYPE_SERVO=3, MIXER6TYPE_CAMERAROLLORSERVO1=4, MIXER6TYPE_CAMERAPITCHORSERVO2=5, MIXER6TYPE_CAMERAYAW=6, MIXER6TYPE_ACCESSORY0=7, MIXER6TYPE_ACCESSORY1=8, MIXER6TYPE_ACCESSORY2=9, MIXER6TYPE_ACCESSORY3=10, MIXER6TYPE_ACCESSORY4=11, MIXER6TYPE_ACCESSORY5=12 } Mixer6TypeOptions;
    // Field Mixer6Vector information
    /* Array element names for field Mixer6Vector */
    typedef enum { MIXER6VECTOR_THROTTLECURVE1=0, MIXER6VECTOR_THROTTLECURVE2=1, MIXER6VECTOR_ROLL=2, MIXER6VECTOR_PITCH=3, MIXER6VECTOR_YAW=4 } Mixer6VectorElem;
    /* Number of elements for field Mixer6Vector */
    static const quint32 MIXER6VECTOR_NUMELEM = 5;
    // Field Mixer7Type information
    /* Enumeration options for field Mixer7Type */
    typedef enum { MIXER7TYPE_DISABLED=0, MIXER7TYPE_MOTOR=1, MIXER7TYPE_REVERSABLEMOTOR=2, MIXER7TYPE_SERVO=3, MIXER7TYPE_CAMERAROLLORSERVO1=4, MIXER7TYPE_CAMERAPITCHORSERVO2=5, MIXER7TYPE_CAMERAYAW=6, MIXER7TYPE_ACCESSORY0=7, MIXER7TYPE_ACCESSORY1=8, MIXER7TYPE_ACCESSORY2=9, MIXER7TYPE_ACCESSORY3=10, MIXER7TYPE_ACCESSORY4=11, MIXER7TYPE_ACCESSORY5=12 } Mixer7TypeOptions;
    // Field Mixer7Vector information
    /* Array element names for field Mixer7Vector */
    typedef enum { MIXER7VECTOR_THROTTLECURVE1=0, MIXER7VECTOR_THROTTLECURVE2=1, MIXER7VECTOR_ROLL=2, MIXER7VECTOR_PITCH=3, MIXER7VECTOR_YAW=4 } Mixer7VectorElem;
    /* Number of elements for field Mixer7Vector */
    static const quint32 MIXER7VECTOR_NUMELEM = 5;
    // Field Mixer8Type information
    /* Enumeration options for field Mixer8Type */
    typedef enum { MIXER8TYPE_DISABLED=0, MIXER8TYPE_MOTOR=1, MIXER8TYPE_REVERSABLEMOTOR=2, MIXER8TYPE_SERVO=3, MIXER8TYPE_CAMERAROLLORSERVO1=4, MIXER8TYPE_CAMERAPITCHORSERVO2=5, MIXER8TYPE_CAMERAYAW=6, MIXER8TYPE_ACCESSORY0=7, MIXER8TYPE_ACCESSORY1=8, MIXER8TYPE_ACCESSORY2=9, MIXER8TYPE_ACCESSORY3=10, MIXER8TYPE_ACCESSORY4=11, MIXER8TYPE_ACCESSORY5=12 } Mixer8TypeOptions;
    // Field Mixer8Vector information
    /* Array element names for field Mixer8Vector */
    typedef enum { MIXER8VECTOR_THROTTLECURVE1=0, MIXER8VECTOR_THROTTLECURVE2=1, MIXER8VECTOR_ROLL=2, MIXER8VECTOR_PITCH=3, MIXER8VECTOR_YAW=4 } Mixer8VectorElem;
    /* Number of elements for field Mixer8Vector */
    static const quint32 MIXER8VECTOR_NUMELEM = 5;
    // Field Mixer9Type information
    /* Enumeration options for field Mixer9Type */
    typedef enum { MIXER9TYPE_DISABLED=0, MIXER9TYPE_MOTOR=1, MIXER9TYPE_REVERSABLEMOTOR=2, MIXER9TYPE_SERVO=3, MIXER9TYPE_CAMERAROLLORSERVO1=4, MIXER9TYPE_CAMERAPITCHORSERVO2=5, MIXER9TYPE_CAMERAYAW=6, MIXER9TYPE_ACCESSORY0=7, MIXER9TYPE_ACCESSORY1=8, MIXER9TYPE_ACCESSORY2=9, MIXER9TYPE_ACCESSORY3=10, MIXER9TYPE_ACCESSORY4=11, MIXER9TYPE_ACCESSORY5=12 } Mixer9TypeOptions;
    // Field Mixer9Vector information
    /* Array element names for field Mixer9Vector */
    typedef enum { MIXER9VECTOR_THROTTLECURVE1=0, MIXER9VECTOR_THROTTLECURVE2=1, MIXER9VECTOR_ROLL=2, MIXER9VECTOR_PITCH=3, MIXER9VECTOR_YAW=4 } Mixer9VectorElem;
    /* Number of elements for field Mixer9Vector */
    static const quint32 MIXER9VECTOR_NUMELEM = 5;
    // Field Mixer10Type information
    /* Enumeration options for field Mixer10Type */
    typedef enum { MIXER10TYPE_DISABLED=0, MIXER10TYPE_MOTOR=1, MIXER10TYPE_REVERSABLEMOTOR=2, MIXER10TYPE_SERVO=3, MIXER10TYPE_CAMERAROLLORSERVO1=4, MIXER10TYPE_CAMERAPITCHORSERVO2=5, MIXER10TYPE_CAMERAYAW=6, MIXER10TYPE_ACCESSORY0=7, MIXER10TYPE_ACCESSORY1=8, MIXER10TYPE_ACCESSORY2=9, MIXER10TYPE_ACCESSORY3=10, MIXER10TYPE_ACCESSORY4=11, MIXER10TYPE_ACCESSORY5=12 } Mixer10TypeOptions;
    // Field Mixer10Vector information
    /* Array element names for field Mixer10Vector */
    typedef enum { MIXER10VECTOR_THROTTLECURVE1=0, MIXER10VECTOR_THROTTLECURVE2=1, MIXER10VECTOR_ROLL=2, MIXER10VECTOR_PITCH=3, MIXER10VECTOR_YAW=4 } Mixer10VectorElem;
    /* Number of elements for field Mixer10Vector */
    static const quint32 MIXER10VECTOR_NUMELEM = 5;
    // Field Mixer11Type information
    /* Enumeration options for field Mixer11Type */
    typedef enum { MIXER11TYPE_DISABLED=0, MIXER11TYPE_MOTOR=1, MIXER11TYPE_REVERSABLEMOTOR=2, MIXER11TYPE_SERVO=3, MIXER11TYPE_CAMERAROLLORSERVO1=4, MIXER11TYPE_CAMERAPITCHORSERVO2=5, MIXER11TYPE_CAMERAYAW=6, MIXER11TYPE_ACCESSORY0=7, MIXER11TYPE_ACCESSORY1=8, MIXER11TYPE_ACCESSORY2=9, MIXER11TYPE_ACCESSORY3=10, MIXER11TYPE_ACCESSORY4=11, MIXER11TYPE_ACCESSORY5=12 } Mixer11TypeOptions;
    // Field Mixer11Vector information
    /* Array element names for field Mixer11Vector */
    typedef enum { MIXER11VECTOR_THROTTLECURVE1=0, MIXER11VECTOR_THROTTLECURVE2=1, MIXER11VECTOR_ROLL=2, MIXER11VECTOR_PITCH=3, MIXER11VECTOR_YAW=4 } Mixer11VectorElem;
    /* Number of elements for field Mixer11Vector */
    static const quint32 MIXER11VECTOR_NUMELEM = 5;
    // Field Mixer12Type information
    /* Enumeration options for field Mixer12Type */
    typedef enum { MIXER12TYPE_DISABLED=0, MIXER12TYPE_MOTOR=1, MIXER12TYPE_REVERSABLEMOTOR=2, MIXER12TYPE_SERVO=3, MIXER12TYPE_CAMERAROLLORSERVO1=4, MIXER12TYPE_CAMERAPITCHORSERVO2=5, MIXER12TYPE_CAMERAYAW=6, MIXER12TYPE_ACCESSORY0=7, MIXER12TYPE_ACCESSORY1=8, MIXER12TYPE_ACCESSORY2=9, MIXER12TYPE_ACCESSORY3=10, MIXER12TYPE_ACCESSORY4=11, MIXER12TYPE_ACCESSORY5=12 } Mixer12TypeOptions;
    // Field Mixer12Vector information
    /* Array element names for field Mixer12Vector */
    typedef enum { MIXER12VECTOR_THROTTLECURVE1=0, MIXER12VECTOR_THROTTLECURVE2=1, MIXER12VECTOR_ROLL=2, MIXER12VECTOR_PITCH=3, MIXER12VECTOR_YAW=4 } Mixer12VectorElem;
    /* Number of elements for field Mixer12Vector */
    static const quint32 MIXER12VECTOR_NUMELEM = 5;

  
    // Constants
    static const quint32 OBJID = 0x7BF2CFA8;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    MixerSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static MixerSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getMaxAccel() const;
    Q_INVOKABLE float getFeedForward() const;
    Q_INVOKABLE float getAccelTime() const;
    Q_INVOKABLE float getDecelTime() const;
    Q_INVOKABLE float getThrottleCurve1(quint32 index) const;
    Q_INVOKABLE float getThrottleCurve1_0() const;
    Q_INVOKABLE float getThrottleCurve1_25() const;
    Q_INVOKABLE float getThrottleCurve1_50() const;
    Q_INVOKABLE float getThrottleCurve1_75() const;
    Q_INVOKABLE float getThrottleCurve1_100() const;
    Q_INVOKABLE float getThrottleCurve2(quint32 index) const;
    Q_INVOKABLE float getThrottleCurve2_0() const;
    Q_INVOKABLE float getThrottleCurve2_25() const;
    Q_INVOKABLE float getThrottleCurve2_50() const;
    Q_INVOKABLE float getThrottleCurve2_75() const;
    Q_INVOKABLE float getThrottleCurve2_100() const;
    Q_INVOKABLE qint8 getMixerValueRoll() const;
    Q_INVOKABLE qint8 getMixerValuePitch() const;
    Q_INVOKABLE qint8 getMixerValueYaw() const;
    Q_INVOKABLE quint8 getCurve2Source() const;
    Q_INVOKABLE quint8 getMixer1Type() const;
    Q_INVOKABLE qint8 getMixer1Vector(quint32 index) const;
    Q_INVOKABLE qint8 getMixer1Vector_ThrottleCurve1() const;
    Q_INVOKABLE qint8 getMixer1Vector_ThrottleCurve2() const;
    Q_INVOKABLE qint8 getMixer1Vector_Roll() const;
    Q_INVOKABLE qint8 getMixer1Vector_Pitch() const;
    Q_INVOKABLE qint8 getMixer1Vector_Yaw() const;
    Q_INVOKABLE quint8 getMixer2Type() const;
    Q_INVOKABLE qint8 getMixer2Vector(quint32 index) const;
    Q_INVOKABLE qint8 getMixer2Vector_ThrottleCurve1() const;
    Q_INVOKABLE qint8 getMixer2Vector_ThrottleCurve2() const;
    Q_INVOKABLE qint8 getMixer2Vector_Roll() const;
    Q_INVOKABLE qint8 getMixer2Vector_Pitch() const;
    Q_INVOKABLE qint8 getMixer2Vector_Yaw() const;
    Q_INVOKABLE quint8 getMixer3Type() const;
    Q_INVOKABLE qint8 getMixer3Vector(quint32 index) const;
    Q_INVOKABLE qint8 getMixer3Vector_ThrottleCurve1() const;
    Q_INVOKABLE qint8 getMixer3Vector_ThrottleCurve2() const;
    Q_INVOKABLE qint8 getMixer3Vector_Roll() const;
    Q_INVOKABLE qint8 getMixer3Vector_Pitch() const;
    Q_INVOKABLE qint8 getMixer3Vector_Yaw() const;
    Q_INVOKABLE quint8 getMixer4Type() const;
    Q_INVOKABLE qint8 getMixer4Vector(quint32 index) const;
    Q_INVOKABLE qint8 getMixer4Vector_ThrottleCurve1() const;
    Q_INVOKABLE qint8 getMixer4Vector_ThrottleCurve2() const;
    Q_INVOKABLE qint8 getMixer4Vector_Roll() const;
    Q_INVOKABLE qint8 getMixer4Vector_Pitch() const;
    Q_INVOKABLE qint8 getMixer4Vector_Yaw() const;
    Q_INVOKABLE quint8 getMixer5Type() const;
    Q_INVOKABLE qint8 getMixer5Vector(quint32 index) const;
    Q_INVOKABLE qint8 getMixer5Vector_ThrottleCurve1() const;
    Q_INVOKABLE qint8 getMixer5Vector_ThrottleCurve2() const;
    Q_INVOKABLE qint8 getMixer5Vector_Roll() const;
    Q_INVOKABLE qint8 getMixer5Vector_Pitch() const;
    Q_INVOKABLE qint8 getMixer5Vector_Yaw() const;
    Q_INVOKABLE quint8 getMixer6Type() const;
    Q_INVOKABLE qint8 getMixer6Vector(quint32 index) const;
    Q_INVOKABLE qint8 getMixer6Vector_ThrottleCurve1() const;
    Q_INVOKABLE qint8 getMixer6Vector_ThrottleCurve2() const;
    Q_INVOKABLE qint8 getMixer6Vector_Roll() const;
    Q_INVOKABLE qint8 getMixer6Vector_Pitch() const;
    Q_INVOKABLE qint8 getMixer6Vector_Yaw() const;
    Q_INVOKABLE quint8 getMixer7Type() const;
    Q_INVOKABLE qint8 getMixer7Vector(quint32 index) const;
    Q_INVOKABLE qint8 getMixer7Vector_ThrottleCurve1() const;
    Q_INVOKABLE qint8 getMixer7Vector_ThrottleCurve2() const;
    Q_INVOKABLE qint8 getMixer7Vector_Roll() const;
    Q_INVOKABLE qint8 getMixer7Vector_Pitch() const;
    Q_INVOKABLE qint8 getMixer7Vector_Yaw() const;
    Q_INVOKABLE quint8 getMixer8Type() const;
    Q_INVOKABLE qint8 getMixer8Vector(quint32 index) const;
    Q_INVOKABLE qint8 getMixer8Vector_ThrottleCurve1() const;
    Q_INVOKABLE qint8 getMixer8Vector_ThrottleCurve2() const;
    Q_INVOKABLE qint8 getMixer8Vector_Roll() const;
    Q_INVOKABLE qint8 getMixer8Vector_Pitch() const;
    Q_INVOKABLE qint8 getMixer8Vector_Yaw() const;
    Q_INVOKABLE quint8 getMixer9Type() const;
    Q_INVOKABLE qint8 getMixer9Vector(quint32 index) const;
    Q_INVOKABLE qint8 getMixer9Vector_ThrottleCurve1() const;
    Q_INVOKABLE qint8 getMixer9Vector_ThrottleCurve2() const;
    Q_INVOKABLE qint8 getMixer9Vector_Roll() const;
    Q_INVOKABLE qint8 getMixer9Vector_Pitch() const;
    Q_INVOKABLE qint8 getMixer9Vector_Yaw() const;
    Q_INVOKABLE quint8 getMixer10Type() const;
    Q_INVOKABLE qint8 getMixer10Vector(quint32 index) const;
    Q_INVOKABLE qint8 getMixer10Vector_ThrottleCurve1() const;
    Q_INVOKABLE qint8 getMixer10Vector_ThrottleCurve2() const;
    Q_INVOKABLE qint8 getMixer10Vector_Roll() const;
    Q_INVOKABLE qint8 getMixer10Vector_Pitch() const;
    Q_INVOKABLE qint8 getMixer10Vector_Yaw() const;
    Q_INVOKABLE quint8 getMixer11Type() const;
    Q_INVOKABLE qint8 getMixer11Vector(quint32 index) const;
    Q_INVOKABLE qint8 getMixer11Vector_ThrottleCurve1() const;
    Q_INVOKABLE qint8 getMixer11Vector_ThrottleCurve2() const;
    Q_INVOKABLE qint8 getMixer11Vector_Roll() const;
    Q_INVOKABLE qint8 getMixer11Vector_Pitch() const;
    Q_INVOKABLE qint8 getMixer11Vector_Yaw() const;
    Q_INVOKABLE quint8 getMixer12Type() const;
    Q_INVOKABLE qint8 getMixer12Vector(quint32 index) const;
    Q_INVOKABLE qint8 getMixer12Vector_ThrottleCurve1() const;
    Q_INVOKABLE qint8 getMixer12Vector_ThrottleCurve2() const;
    Q_INVOKABLE qint8 getMixer12Vector_Roll() const;
    Q_INVOKABLE qint8 getMixer12Vector_Pitch() const;
    Q_INVOKABLE qint8 getMixer12Vector_Yaw() const;


public slots:
    void setMaxAccel(float value);
    void setFeedForward(float value);
    void setAccelTime(float value);
    void setDecelTime(float value);
    void setThrottleCurve1(quint32 index, float value);
    void setThrottleCurve1_0(float value);
    void setThrottleCurve1_25(float value);
    void setThrottleCurve1_50(float value);
    void setThrottleCurve1_75(float value);
    void setThrottleCurve1_100(float value);
    void setThrottleCurve2(quint32 index, float value);
    void setThrottleCurve2_0(float value);
    void setThrottleCurve2_25(float value);
    void setThrottleCurve2_50(float value);
    void setThrottleCurve2_75(float value);
    void setThrottleCurve2_100(float value);
    void setMixerValueRoll(qint8 value);
    void setMixerValuePitch(qint8 value);
    void setMixerValueYaw(qint8 value);
    void setCurve2Source(quint8 value);
    void setMixer1Type(quint8 value);
    void setMixer1Vector(quint32 index, qint8 value);
    void setMixer1Vector_ThrottleCurve1(qint8 value);
    void setMixer1Vector_ThrottleCurve2(qint8 value);
    void setMixer1Vector_Roll(qint8 value);
    void setMixer1Vector_Pitch(qint8 value);
    void setMixer1Vector_Yaw(qint8 value);
    void setMixer2Type(quint8 value);
    void setMixer2Vector(quint32 index, qint8 value);
    void setMixer2Vector_ThrottleCurve1(qint8 value);
    void setMixer2Vector_ThrottleCurve2(qint8 value);
    void setMixer2Vector_Roll(qint8 value);
    void setMixer2Vector_Pitch(qint8 value);
    void setMixer2Vector_Yaw(qint8 value);
    void setMixer3Type(quint8 value);
    void setMixer3Vector(quint32 index, qint8 value);
    void setMixer3Vector_ThrottleCurve1(qint8 value);
    void setMixer3Vector_ThrottleCurve2(qint8 value);
    void setMixer3Vector_Roll(qint8 value);
    void setMixer3Vector_Pitch(qint8 value);
    void setMixer3Vector_Yaw(qint8 value);
    void setMixer4Type(quint8 value);
    void setMixer4Vector(quint32 index, qint8 value);
    void setMixer4Vector_ThrottleCurve1(qint8 value);
    void setMixer4Vector_ThrottleCurve2(qint8 value);
    void setMixer4Vector_Roll(qint8 value);
    void setMixer4Vector_Pitch(qint8 value);
    void setMixer4Vector_Yaw(qint8 value);
    void setMixer5Type(quint8 value);
    void setMixer5Vector(quint32 index, qint8 value);
    void setMixer5Vector_ThrottleCurve1(qint8 value);
    void setMixer5Vector_ThrottleCurve2(qint8 value);
    void setMixer5Vector_Roll(qint8 value);
    void setMixer5Vector_Pitch(qint8 value);
    void setMixer5Vector_Yaw(qint8 value);
    void setMixer6Type(quint8 value);
    void setMixer6Vector(quint32 index, qint8 value);
    void setMixer6Vector_ThrottleCurve1(qint8 value);
    void setMixer6Vector_ThrottleCurve2(qint8 value);
    void setMixer6Vector_Roll(qint8 value);
    void setMixer6Vector_Pitch(qint8 value);
    void setMixer6Vector_Yaw(qint8 value);
    void setMixer7Type(quint8 value);
    void setMixer7Vector(quint32 index, qint8 value);
    void setMixer7Vector_ThrottleCurve1(qint8 value);
    void setMixer7Vector_ThrottleCurve2(qint8 value);
    void setMixer7Vector_Roll(qint8 value);
    void setMixer7Vector_Pitch(qint8 value);
    void setMixer7Vector_Yaw(qint8 value);
    void setMixer8Type(quint8 value);
    void setMixer8Vector(quint32 index, qint8 value);
    void setMixer8Vector_ThrottleCurve1(qint8 value);
    void setMixer8Vector_ThrottleCurve2(qint8 value);
    void setMixer8Vector_Roll(qint8 value);
    void setMixer8Vector_Pitch(qint8 value);
    void setMixer8Vector_Yaw(qint8 value);
    void setMixer9Type(quint8 value);
    void setMixer9Vector(quint32 index, qint8 value);
    void setMixer9Vector_ThrottleCurve1(qint8 value);
    void setMixer9Vector_ThrottleCurve2(qint8 value);
    void setMixer9Vector_Roll(qint8 value);
    void setMixer9Vector_Pitch(qint8 value);
    void setMixer9Vector_Yaw(qint8 value);
    void setMixer10Type(quint8 value);
    void setMixer10Vector(quint32 index, qint8 value);
    void setMixer10Vector_ThrottleCurve1(qint8 value);
    void setMixer10Vector_ThrottleCurve2(qint8 value);
    void setMixer10Vector_Roll(qint8 value);
    void setMixer10Vector_Pitch(qint8 value);
    void setMixer10Vector_Yaw(qint8 value);
    void setMixer11Type(quint8 value);
    void setMixer11Vector(quint32 index, qint8 value);
    void setMixer11Vector_ThrottleCurve1(qint8 value);
    void setMixer11Vector_ThrottleCurve2(qint8 value);
    void setMixer11Vector_Roll(qint8 value);
    void setMixer11Vector_Pitch(qint8 value);
    void setMixer11Vector_Yaw(qint8 value);
    void setMixer12Type(quint8 value);
    void setMixer12Vector(quint32 index, qint8 value);
    void setMixer12Vector_ThrottleCurve1(qint8 value);
    void setMixer12Vector_ThrottleCurve2(qint8 value);
    void setMixer12Vector_Roll(qint8 value);
    void setMixer12Vector_Pitch(qint8 value);
    void setMixer12Vector_Yaw(qint8 value);


signals:
    void MaxAccelChanged(float value);
    void FeedForwardChanged(float value);
    void AccelTimeChanged(float value);
    void DecelTimeChanged(float value);
    void ThrottleCurve1Changed(quint32 index, float value);
    void ThrottleCurve1_0Changed(float value);
    void ThrottleCurve1_25Changed(float value);
    void ThrottleCurve1_50Changed(float value);
    void ThrottleCurve1_75Changed(float value);
    void ThrottleCurve1_100Changed(float value);
    void ThrottleCurve2Changed(quint32 index, float value);
    void ThrottleCurve2_0Changed(float value);
    void ThrottleCurve2_25Changed(float value);
    void ThrottleCurve2_50Changed(float value);
    void ThrottleCurve2_75Changed(float value);
    void ThrottleCurve2_100Changed(float value);
    void MixerValueRollChanged(qint8 value);
    void MixerValuePitchChanged(qint8 value);
    void MixerValueYawChanged(qint8 value);
    void Curve2SourceChanged(quint8 value);
    void Mixer1TypeChanged(quint8 value);
    void Mixer1VectorChanged(quint32 index, qint8 value);
    void Mixer1Vector_ThrottleCurve1Changed(qint8 value);
    void Mixer1Vector_ThrottleCurve2Changed(qint8 value);
    void Mixer1Vector_RollChanged(qint8 value);
    void Mixer1Vector_PitchChanged(qint8 value);
    void Mixer1Vector_YawChanged(qint8 value);
    void Mixer2TypeChanged(quint8 value);
    void Mixer2VectorChanged(quint32 index, qint8 value);
    void Mixer2Vector_ThrottleCurve1Changed(qint8 value);
    void Mixer2Vector_ThrottleCurve2Changed(qint8 value);
    void Mixer2Vector_RollChanged(qint8 value);
    void Mixer2Vector_PitchChanged(qint8 value);
    void Mixer2Vector_YawChanged(qint8 value);
    void Mixer3TypeChanged(quint8 value);
    void Mixer3VectorChanged(quint32 index, qint8 value);
    void Mixer3Vector_ThrottleCurve1Changed(qint8 value);
    void Mixer3Vector_ThrottleCurve2Changed(qint8 value);
    void Mixer3Vector_RollChanged(qint8 value);
    void Mixer3Vector_PitchChanged(qint8 value);
    void Mixer3Vector_YawChanged(qint8 value);
    void Mixer4TypeChanged(quint8 value);
    void Mixer4VectorChanged(quint32 index, qint8 value);
    void Mixer4Vector_ThrottleCurve1Changed(qint8 value);
    void Mixer4Vector_ThrottleCurve2Changed(qint8 value);
    void Mixer4Vector_RollChanged(qint8 value);
    void Mixer4Vector_PitchChanged(qint8 value);
    void Mixer4Vector_YawChanged(qint8 value);
    void Mixer5TypeChanged(quint8 value);
    void Mixer5VectorChanged(quint32 index, qint8 value);
    void Mixer5Vector_ThrottleCurve1Changed(qint8 value);
    void Mixer5Vector_ThrottleCurve2Changed(qint8 value);
    void Mixer5Vector_RollChanged(qint8 value);
    void Mixer5Vector_PitchChanged(qint8 value);
    void Mixer5Vector_YawChanged(qint8 value);
    void Mixer6TypeChanged(quint8 value);
    void Mixer6VectorChanged(quint32 index, qint8 value);
    void Mixer6Vector_ThrottleCurve1Changed(qint8 value);
    void Mixer6Vector_ThrottleCurve2Changed(qint8 value);
    void Mixer6Vector_RollChanged(qint8 value);
    void Mixer6Vector_PitchChanged(qint8 value);
    void Mixer6Vector_YawChanged(qint8 value);
    void Mixer7TypeChanged(quint8 value);
    void Mixer7VectorChanged(quint32 index, qint8 value);
    void Mixer7Vector_ThrottleCurve1Changed(qint8 value);
    void Mixer7Vector_ThrottleCurve2Changed(qint8 value);
    void Mixer7Vector_RollChanged(qint8 value);
    void Mixer7Vector_PitchChanged(qint8 value);
    void Mixer7Vector_YawChanged(qint8 value);
    void Mixer8TypeChanged(quint8 value);
    void Mixer8VectorChanged(quint32 index, qint8 value);
    void Mixer8Vector_ThrottleCurve1Changed(qint8 value);
    void Mixer8Vector_ThrottleCurve2Changed(qint8 value);
    void Mixer8Vector_RollChanged(qint8 value);
    void Mixer8Vector_PitchChanged(qint8 value);
    void Mixer8Vector_YawChanged(qint8 value);
    void Mixer9TypeChanged(quint8 value);
    void Mixer9VectorChanged(quint32 index, qint8 value);
    void Mixer9Vector_ThrottleCurve1Changed(qint8 value);
    void Mixer9Vector_ThrottleCurve2Changed(qint8 value);
    void Mixer9Vector_RollChanged(qint8 value);
    void Mixer9Vector_PitchChanged(qint8 value);
    void Mixer9Vector_YawChanged(qint8 value);
    void Mixer10TypeChanged(quint8 value);
    void Mixer10VectorChanged(quint32 index, qint8 value);
    void Mixer10Vector_ThrottleCurve1Changed(qint8 value);
    void Mixer10Vector_ThrottleCurve2Changed(qint8 value);
    void Mixer10Vector_RollChanged(qint8 value);
    void Mixer10Vector_PitchChanged(qint8 value);
    void Mixer10Vector_YawChanged(qint8 value);
    void Mixer11TypeChanged(quint8 value);
    void Mixer11VectorChanged(quint32 index, qint8 value);
    void Mixer11Vector_ThrottleCurve1Changed(qint8 value);
    void Mixer11Vector_ThrottleCurve2Changed(qint8 value);
    void Mixer11Vector_RollChanged(qint8 value);
    void Mixer11Vector_PitchChanged(qint8 value);
    void Mixer11Vector_YawChanged(qint8 value);
    void Mixer12TypeChanged(quint8 value);
    void Mixer12VectorChanged(quint32 index, qint8 value);
    void Mixer12Vector_ThrottleCurve1Changed(qint8 value);
    void Mixer12Vector_ThrottleCurve2Changed(qint8 value);
    void Mixer12Vector_RollChanged(qint8 value);
    void Mixer12Vector_PitchChanged(qint8 value);
    void Mixer12Vector_YawChanged(qint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // MIXERSETTINGS_H
