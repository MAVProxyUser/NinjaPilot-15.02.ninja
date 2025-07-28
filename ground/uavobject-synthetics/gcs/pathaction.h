/**
 ******************************************************************************
 *
 * @file       pathaction.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: pathaction.xml. 
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
#ifndef PATHACTION_H
#define PATHACTION_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT PathAction: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float ModeParameters_0 READ getModeParameters_0 WRITE setModeParameters_0 NOTIFY ModeParameters_0Changed);
    Q_PROPERTY(float ModeParameters_1 READ getModeParameters_1 WRITE setModeParameters_1 NOTIFY ModeParameters_1Changed);
    Q_PROPERTY(float ModeParameters_2 READ getModeParameters_2 WRITE setModeParameters_2 NOTIFY ModeParameters_2Changed);
    Q_PROPERTY(float ModeParameters_3 READ getModeParameters_3 WRITE setModeParameters_3 NOTIFY ModeParameters_3Changed);
    Q_PROPERTY(float ConditionParameters_0 READ getConditionParameters_0 WRITE setConditionParameters_0 NOTIFY ConditionParameters_0Changed);
    Q_PROPERTY(float ConditionParameters_1 READ getConditionParameters_1 WRITE setConditionParameters_1 NOTIFY ConditionParameters_1Changed);
    Q_PROPERTY(float ConditionParameters_2 READ getConditionParameters_2 WRITE setConditionParameters_2 NOTIFY ConditionParameters_2Changed);
    Q_PROPERTY(float ConditionParameters_3 READ getConditionParameters_3 WRITE setConditionParameters_3 NOTIFY ConditionParameters_3Changed);
    Q_PROPERTY(qint16 JumpDestination READ getJumpDestination WRITE setJumpDestination NOTIFY JumpDestinationChanged);
    Q_PROPERTY(qint16 ErrorDestination READ getErrorDestination WRITE setErrorDestination NOTIFY ErrorDestinationChanged);
    Q_PROPERTY(quint8 Mode READ getMode WRITE setMode NOTIFY ModeChanged);
    Q_PROPERTY(quint8 EndCondition READ getEndCondition WRITE setEndCondition NOTIFY EndConditionChanged);
    Q_PROPERTY(quint8 Command READ getCommand WRITE setCommand NOTIFY CommandChanged);


public:
    // Field structure
    typedef struct {
        float ModeParameters[4];
        float ConditionParameters[4];
        qint16 JumpDestination;
        qint16 ErrorDestination;
        quint8 Mode;
        quint8 EndCondition;
        quint8 Command;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field ModeParameters information
    /* Number of elements for field ModeParameters */
    static const quint32 MODEPARAMETERS_NUMELEM = 4;
    // Field ConditionParameters information
    /* Number of elements for field ConditionParameters */
    static const quint32 CONDITIONPARAMETERS_NUMELEM = 4;
    // Field JumpDestination information
    // Field ErrorDestination information
    // Field Mode information
    /* Enumeration options for field Mode */
    typedef enum { MODE_GOTOENDPOINT=0, MODE_FOLLOWVECTOR=1, MODE_CIRCLERIGHT=2, MODE_CIRCLELEFT=3, MODE_FIXEDATTITUDE=4, MODE_SETACCESSORY=5, MODE_DISARMALARM=6, MODE_LAND=7, MODE_BRAKE=8, MODE_VELOCITY=9 } ModeOptions;
    // Field EndCondition information
    /* Enumeration options for field EndCondition */
    typedef enum { ENDCONDITION_NONE=0, ENDCONDITION_TIMEOUT=1, ENDCONDITION_DISTANCETOTARGET=2, ENDCONDITION_LEGREMAINING=3, ENDCONDITION_BELOWERROR=4, ENDCONDITION_ABOVEALTITUDE=5, ENDCONDITION_ABOVESPEED=6, ENDCONDITION_POINTINGTOWARDSNEXT=7, ENDCONDITION_PYTHONSCRIPT=8, ENDCONDITION_IMMEDIATE=9 } EndConditionOptions;
    // Field Command information
    /* Enumeration options for field Command */
    typedef enum { COMMAND_ONCONDITIONNEXTWAYPOINT=0, COMMAND_ONNOTCONDITIONNEXTWAYPOINT=1, COMMAND_ONCONDITIONJUMPWAYPOINT=2, COMMAND_ONNOTCONDITIONJUMPWAYPOINT=3, COMMAND_IFCONDITIONJUMPWAYPOINTELSENEXTWAYPOINT=4 } CommandOptions;

  
    // Constants
    static const quint32 OBJID = 0x341360B2;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 0;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    PathAction();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static PathAction* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getModeParameters(quint32 index) const;
    Q_INVOKABLE float getModeParameters_0() const;
    Q_INVOKABLE float getModeParameters_1() const;
    Q_INVOKABLE float getModeParameters_2() const;
    Q_INVOKABLE float getModeParameters_3() const;
    Q_INVOKABLE float getConditionParameters(quint32 index) const;
    Q_INVOKABLE float getConditionParameters_0() const;
    Q_INVOKABLE float getConditionParameters_1() const;
    Q_INVOKABLE float getConditionParameters_2() const;
    Q_INVOKABLE float getConditionParameters_3() const;
    Q_INVOKABLE qint16 getJumpDestination() const;
    Q_INVOKABLE qint16 getErrorDestination() const;
    Q_INVOKABLE quint8 getMode() const;
    Q_INVOKABLE quint8 getEndCondition() const;
    Q_INVOKABLE quint8 getCommand() const;


public slots:
    void setModeParameters(quint32 index, float value);
    void setModeParameters_0(float value);
    void setModeParameters_1(float value);
    void setModeParameters_2(float value);
    void setModeParameters_3(float value);
    void setConditionParameters(quint32 index, float value);
    void setConditionParameters_0(float value);
    void setConditionParameters_1(float value);
    void setConditionParameters_2(float value);
    void setConditionParameters_3(float value);
    void setJumpDestination(qint16 value);
    void setErrorDestination(qint16 value);
    void setMode(quint8 value);
    void setEndCondition(quint8 value);
    void setCommand(quint8 value);


signals:
    void ModeParametersChanged(quint32 index, float value);
    void ModeParameters_0Changed(float value);
    void ModeParameters_1Changed(float value);
    void ModeParameters_2Changed(float value);
    void ModeParameters_3Changed(float value);
    void ConditionParametersChanged(quint32 index, float value);
    void ConditionParameters_0Changed(float value);
    void ConditionParameters_1Changed(float value);
    void ConditionParameters_2Changed(float value);
    void ConditionParameters_3Changed(float value);
    void JumpDestinationChanged(qint16 value);
    void ErrorDestinationChanged(qint16 value);
    void ModeChanged(quint8 value);
    void EndConditionChanged(quint8 value);
    void CommandChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // PATHACTION_H
