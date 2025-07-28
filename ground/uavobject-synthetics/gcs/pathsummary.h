/**
 ******************************************************************************
 *
 * @file       pathsummary.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: pathsummary.xml. 
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
#ifndef PATHSUMMARY_H
#define PATHSUMMARY_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT PathSummary: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float brake_distance_offset READ getbrake_distance_offset WRITE setbrake_distance_offset NOTIFY brake_distance_offsetChanged);
    Q_PROPERTY(float time_remaining READ gettime_remaining WRITE settime_remaining NOTIFY time_remainingChanged);
    Q_PROPERTY(float fractional_progress READ getfractional_progress WRITE setfractional_progress NOTIFY fractional_progressChanged);
    Q_PROPERTY(float decelrate READ getdecelrate WRITE setdecelrate NOTIFY decelrateChanged);
    Q_PROPERTY(float brakeRateActualDesiredRatio READ getbrakeRateActualDesiredRatio WRITE setbrakeRateActualDesiredRatio NOTIFY brakeRateActualDesiredRatioChanged);
    Q_PROPERTY(float velocityIntoHold READ getvelocityIntoHold WRITE setvelocityIntoHold NOTIFY velocityIntoHoldChanged);
    Q_PROPERTY(qint16 UID READ getUID WRITE setUID NOTIFY UIDChanged);
    Q_PROPERTY(quint8 brake_exit_reason READ getbrake_exit_reason WRITE setbrake_exit_reason NOTIFY brake_exit_reasonChanged);
    Q_PROPERTY(quint8 Mode READ getMode WRITE setMode NOTIFY ModeChanged);


public:
    // Field structure
    typedef struct {
        float brake_distance_offset;
        float time_remaining;
        float fractional_progress;
        float decelrate;
        float brakeRateActualDesiredRatio;
        float velocityIntoHold;
        qint16 UID;
        quint8 brake_exit_reason;
        quint8 Mode;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field brake_distance_offset information
    // Field time_remaining information
    // Field fractional_progress information
    // Field decelrate information
    // Field brakeRateActualDesiredRatio information
    // Field velocityIntoHold information
    // Field UID information
    // Field brake_exit_reason information
    /* Enumeration options for field brake_exit_reason */
    typedef enum { BRAKE_EXIT_REASON_TIMEOUT=0, BRAKE_EXIT_REASON_PATHCOMPLETED=1, BRAKE_EXIT_REASON_PATHERROR=2 } brake_exit_reasonOptions;
    // Field Mode information
    /* Enumeration options for field Mode */
    typedef enum { MODE_GOTOENDPOINT=0, MODE_FOLLOWVECTOR=1, MODE_CIRCLERIGHT=2, MODE_CIRCLELEFT=3, MODE_FIXEDATTITUDE=4, MODE_SETACCESSORY=5, MODE_DISARMALARM=6, MODE_LAND=7, MODE_BRAKE=8, MODE_VELOCITY=9 } ModeOptions;

  
    // Constants
    static const quint32 OBJID = 0x5FFC862C;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    PathSummary();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static PathSummary* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getbrake_distance_offset() const;
    Q_INVOKABLE float gettime_remaining() const;
    Q_INVOKABLE float getfractional_progress() const;
    Q_INVOKABLE float getdecelrate() const;
    Q_INVOKABLE float getbrakeRateActualDesiredRatio() const;
    Q_INVOKABLE float getvelocityIntoHold() const;
    Q_INVOKABLE qint16 getUID() const;
    Q_INVOKABLE quint8 getbrake_exit_reason() const;
    Q_INVOKABLE quint8 getMode() const;


public slots:
    void setbrake_distance_offset(float value);
    void settime_remaining(float value);
    void setfractional_progress(float value);
    void setdecelrate(float value);
    void setbrakeRateActualDesiredRatio(float value);
    void setvelocityIntoHold(float value);
    void setUID(qint16 value);
    void setbrake_exit_reason(quint8 value);
    void setMode(quint8 value);


signals:
    void brake_distance_offsetChanged(float value);
    void time_remainingChanged(float value);
    void fractional_progressChanged(float value);
    void decelrateChanged(float value);
    void brakeRateActualDesiredRatioChanged(float value);
    void velocityIntoHoldChanged(float value);
    void UIDChanged(qint16 value);
    void brake_exit_reasonChanged(quint8 value);
    void ModeChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // PATHSUMMARY_H
