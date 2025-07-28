/**
 ******************************************************************************
 *
 * @file       fixedwingpathfollowerstatus.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: fixedwingpathfollowerstatus.xml. 
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
#ifndef FIXEDWINGPATHFOLLOWERSTATUS_H
#define FIXEDWINGPATHFOLLOWERSTATUS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT FixedWingPathFollowerStatus: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float Error_Course READ getError_Course WRITE setError_Course NOTIFY Error_CourseChanged);
    Q_PROPERTY(float Error_Speed READ getError_Speed WRITE setError_Speed NOTIFY Error_SpeedChanged);
    Q_PROPERTY(float Error_Power READ getError_Power WRITE setError_Power NOTIFY Error_PowerChanged);
    Q_PROPERTY(float ErrorInt_Course READ getErrorInt_Course WRITE setErrorInt_Course NOTIFY ErrorInt_CourseChanged);
    Q_PROPERTY(float ErrorInt_Speed READ getErrorInt_Speed WRITE setErrorInt_Speed NOTIFY ErrorInt_SpeedChanged);
    Q_PROPERTY(float ErrorInt_Power READ getErrorInt_Power WRITE setErrorInt_Power NOTIFY ErrorInt_PowerChanged);
    Q_PROPERTY(float Command_Course READ getCommand_Course WRITE setCommand_Course NOTIFY Command_CourseChanged);
    Q_PROPERTY(float Command_Speed READ getCommand_Speed WRITE setCommand_Speed NOTIFY Command_SpeedChanged);
    Q_PROPERTY(float Command_Power READ getCommand_Power WRITE setCommand_Power NOTIFY Command_PowerChanged);
    Q_PROPERTY(quint8 Errors_Wind READ getErrors_Wind WRITE setErrors_Wind NOTIFY Errors_WindChanged);
    Q_PROPERTY(quint8 Errors_Stallspeed READ getErrors_Stallspeed WRITE setErrors_Stallspeed NOTIFY Errors_StallspeedChanged);
    Q_PROPERTY(quint8 Errors_Lowspeed READ getErrors_Lowspeed WRITE setErrors_Lowspeed NOTIFY Errors_LowspeedChanged);
    Q_PROPERTY(quint8 Errors_Highspeed READ getErrors_Highspeed WRITE setErrors_Highspeed NOTIFY Errors_HighspeedChanged);
    Q_PROPERTY(quint8 Errors_Overspeed READ getErrors_Overspeed WRITE setErrors_Overspeed NOTIFY Errors_OverspeedChanged);
    Q_PROPERTY(quint8 Errors_Lowpower READ getErrors_Lowpower WRITE setErrors_Lowpower NOTIFY Errors_LowpowerChanged);
    Q_PROPERTY(quint8 Errors_Highpower READ getErrors_Highpower WRITE setErrors_Highpower NOTIFY Errors_HighpowerChanged);
    Q_PROPERTY(quint8 Errors_Pitchcontrol READ getErrors_Pitchcontrol WRITE setErrors_Pitchcontrol NOTIFY Errors_PitchcontrolChanged);


public:
    // Field structure
    typedef struct {
        float Error[3];
        float ErrorInt[3];
        float Command[3];
        quint8 Errors[8];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Error information
    /* Array element names for field Error */
    typedef enum { ERROR_COURSE=0, ERROR_SPEED=1, ERROR_POWER=2 } ErrorElem;
    /* Number of elements for field Error */
    static const quint32 ERROR_NUMELEM = 3;
    // Field ErrorInt information
    /* Array element names for field ErrorInt */
    typedef enum { ERRORINT_COURSE=0, ERRORINT_SPEED=1, ERRORINT_POWER=2 } ErrorIntElem;
    /* Number of elements for field ErrorInt */
    static const quint32 ERRORINT_NUMELEM = 3;
    // Field Command information
    /* Array element names for field Command */
    typedef enum { COMMAND_COURSE=0, COMMAND_SPEED=1, COMMAND_POWER=2 } CommandElem;
    /* Number of elements for field Command */
    static const quint32 COMMAND_NUMELEM = 3;
    // Field Errors information
    /* Array element names for field Errors */
    typedef enum { ERRORS_WIND=0, ERRORS_STALLSPEED=1, ERRORS_LOWSPEED=2, ERRORS_HIGHSPEED=3, ERRORS_OVERSPEED=4, ERRORS_LOWPOWER=5, ERRORS_HIGHPOWER=6, ERRORS_PITCHCONTROL=7 } ErrorsElem;
    /* Number of elements for field Errors */
    static const quint32 ERRORS_NUMELEM = 8;

  
    // Constants
    static const quint32 OBJID = 0x35ED0888;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    FixedWingPathFollowerStatus();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static FixedWingPathFollowerStatus* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getError(quint32 index) const;
    Q_INVOKABLE float getError_Course() const;
    Q_INVOKABLE float getError_Speed() const;
    Q_INVOKABLE float getError_Power() const;
    Q_INVOKABLE float getErrorInt(quint32 index) const;
    Q_INVOKABLE float getErrorInt_Course() const;
    Q_INVOKABLE float getErrorInt_Speed() const;
    Q_INVOKABLE float getErrorInt_Power() const;
    Q_INVOKABLE float getCommand(quint32 index) const;
    Q_INVOKABLE float getCommand_Course() const;
    Q_INVOKABLE float getCommand_Speed() const;
    Q_INVOKABLE float getCommand_Power() const;
    Q_INVOKABLE quint8 getErrors(quint32 index) const;
    Q_INVOKABLE quint8 getErrors_Wind() const;
    Q_INVOKABLE quint8 getErrors_Stallspeed() const;
    Q_INVOKABLE quint8 getErrors_Lowspeed() const;
    Q_INVOKABLE quint8 getErrors_Highspeed() const;
    Q_INVOKABLE quint8 getErrors_Overspeed() const;
    Q_INVOKABLE quint8 getErrors_Lowpower() const;
    Q_INVOKABLE quint8 getErrors_Highpower() const;
    Q_INVOKABLE quint8 getErrors_Pitchcontrol() const;


public slots:
    void setError(quint32 index, float value);
    void setError_Course(float value);
    void setError_Speed(float value);
    void setError_Power(float value);
    void setErrorInt(quint32 index, float value);
    void setErrorInt_Course(float value);
    void setErrorInt_Speed(float value);
    void setErrorInt_Power(float value);
    void setCommand(quint32 index, float value);
    void setCommand_Course(float value);
    void setCommand_Speed(float value);
    void setCommand_Power(float value);
    void setErrors(quint32 index, quint8 value);
    void setErrors_Wind(quint8 value);
    void setErrors_Stallspeed(quint8 value);
    void setErrors_Lowspeed(quint8 value);
    void setErrors_Highspeed(quint8 value);
    void setErrors_Overspeed(quint8 value);
    void setErrors_Lowpower(quint8 value);
    void setErrors_Highpower(quint8 value);
    void setErrors_Pitchcontrol(quint8 value);


signals:
    void ErrorChanged(quint32 index, float value);
    void Error_CourseChanged(float value);
    void Error_SpeedChanged(float value);
    void Error_PowerChanged(float value);
    void ErrorIntChanged(quint32 index, float value);
    void ErrorInt_CourseChanged(float value);
    void ErrorInt_SpeedChanged(float value);
    void ErrorInt_PowerChanged(float value);
    void CommandChanged(quint32 index, float value);
    void Command_CourseChanged(float value);
    void Command_SpeedChanged(float value);
    void Command_PowerChanged(float value);
    void ErrorsChanged(quint32 index, quint8 value);
    void Errors_WindChanged(quint8 value);
    void Errors_StallspeedChanged(quint8 value);
    void Errors_LowspeedChanged(quint8 value);
    void Errors_HighspeedChanged(quint8 value);
    void Errors_OverspeedChanged(quint8 value);
    void Errors_LowpowerChanged(quint8 value);
    void Errors_HighpowerChanged(quint8 value);
    void Errors_PitchcontrolChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // FIXEDWINGPATHFOLLOWERSTATUS_H
