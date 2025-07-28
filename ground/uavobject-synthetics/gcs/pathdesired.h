/**
 ******************************************************************************
 *
 * @file       pathdesired.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: pathdesired.xml. 
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
#ifndef PATHDESIRED_H
#define PATHDESIRED_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT PathDesired: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float Start_North READ getStart_North WRITE setStart_North NOTIFY Start_NorthChanged);
    Q_PROPERTY(float Start_East READ getStart_East WRITE setStart_East NOTIFY Start_EastChanged);
    Q_PROPERTY(float Start_Down READ getStart_Down WRITE setStart_Down NOTIFY Start_DownChanged);
    Q_PROPERTY(float End_North READ getEnd_North WRITE setEnd_North NOTIFY End_NorthChanged);
    Q_PROPERTY(float End_East READ getEnd_East WRITE setEnd_East NOTIFY End_EastChanged);
    Q_PROPERTY(float End_Down READ getEnd_Down WRITE setEnd_Down NOTIFY End_DownChanged);
    Q_PROPERTY(float StartingVelocity READ getStartingVelocity WRITE setStartingVelocity NOTIFY StartingVelocityChanged);
    Q_PROPERTY(float EndingVelocity READ getEndingVelocity WRITE setEndingVelocity NOTIFY EndingVelocityChanged);
    Q_PROPERTY(float ModeParameters_0 READ getModeParameters_0 WRITE setModeParameters_0 NOTIFY ModeParameters_0Changed);
    Q_PROPERTY(float ModeParameters_1 READ getModeParameters_1 WRITE setModeParameters_1 NOTIFY ModeParameters_1Changed);
    Q_PROPERTY(float ModeParameters_2 READ getModeParameters_2 WRITE setModeParameters_2 NOTIFY ModeParameters_2Changed);
    Q_PROPERTY(float ModeParameters_3 READ getModeParameters_3 WRITE setModeParameters_3 NOTIFY ModeParameters_3Changed);
    Q_PROPERTY(qint16 UID READ getUID WRITE setUID NOTIFY UIDChanged);
    Q_PROPERTY(quint8 Mode READ getMode WRITE setMode NOTIFY ModeChanged);


public:
    // Field structure
    typedef struct {
        float Start[3];
        float End[3];
        float StartingVelocity;
        float EndingVelocity;
        float ModeParameters[4];
        qint16 UID;
        quint8 Mode;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Start information
    /* Array element names for field Start */
    typedef enum { START_NORTH=0, START_EAST=1, START_DOWN=2 } StartElem;
    /* Number of elements for field Start */
    static const quint32 START_NUMELEM = 3;
    // Field End information
    /* Array element names for field End */
    typedef enum { END_NORTH=0, END_EAST=1, END_DOWN=2 } EndElem;
    /* Number of elements for field End */
    static const quint32 END_NUMELEM = 3;
    // Field StartingVelocity information
    // Field EndingVelocity information
    // Field ModeParameters information
    /* Number of elements for field ModeParameters */
    static const quint32 MODEPARAMETERS_NUMELEM = 4;
    // Field UID information
    // Field Mode information
    /* Enumeration options for field Mode */
    typedef enum { MODE_GOTOENDPOINT=0, MODE_FOLLOWVECTOR=1, MODE_CIRCLERIGHT=2, MODE_CIRCLELEFT=3, MODE_FIXEDATTITUDE=4, MODE_SETACCESSORY=5, MODE_DISARMALARM=6, MODE_LAND=7, MODE_BRAKE=8, MODE_VELOCITY=9 } ModeOptions;

  
    // Constants
    static const quint32 OBJID = 0x4CB8CD10;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    PathDesired();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static PathDesired* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getStart(quint32 index) const;
    Q_INVOKABLE float getStart_North() const;
    Q_INVOKABLE float getStart_East() const;
    Q_INVOKABLE float getStart_Down() const;
    Q_INVOKABLE float getEnd(quint32 index) const;
    Q_INVOKABLE float getEnd_North() const;
    Q_INVOKABLE float getEnd_East() const;
    Q_INVOKABLE float getEnd_Down() const;
    Q_INVOKABLE float getStartingVelocity() const;
    Q_INVOKABLE float getEndingVelocity() const;
    Q_INVOKABLE float getModeParameters(quint32 index) const;
    Q_INVOKABLE float getModeParameters_0() const;
    Q_INVOKABLE float getModeParameters_1() const;
    Q_INVOKABLE float getModeParameters_2() const;
    Q_INVOKABLE float getModeParameters_3() const;
    Q_INVOKABLE qint16 getUID() const;
    Q_INVOKABLE quint8 getMode() const;


public slots:
    void setStart(quint32 index, float value);
    void setStart_North(float value);
    void setStart_East(float value);
    void setStart_Down(float value);
    void setEnd(quint32 index, float value);
    void setEnd_North(float value);
    void setEnd_East(float value);
    void setEnd_Down(float value);
    void setStartingVelocity(float value);
    void setEndingVelocity(float value);
    void setModeParameters(quint32 index, float value);
    void setModeParameters_0(float value);
    void setModeParameters_1(float value);
    void setModeParameters_2(float value);
    void setModeParameters_3(float value);
    void setUID(qint16 value);
    void setMode(quint8 value);


signals:
    void StartChanged(quint32 index, float value);
    void Start_NorthChanged(float value);
    void Start_EastChanged(float value);
    void Start_DownChanged(float value);
    void EndChanged(quint32 index, float value);
    void End_NorthChanged(float value);
    void End_EastChanged(float value);
    void End_DownChanged(float value);
    void StartingVelocityChanged(float value);
    void EndingVelocityChanged(float value);
    void ModeParametersChanged(quint32 index, float value);
    void ModeParameters_0Changed(float value);
    void ModeParameters_1Changed(float value);
    void ModeParameters_2Changed(float value);
    void ModeParameters_3Changed(float value);
    void UIDChanged(qint16 value);
    void ModeChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // PATHDESIRED_H
