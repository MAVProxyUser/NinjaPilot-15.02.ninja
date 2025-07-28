/**
 ******************************************************************************
 *
 * @file       pathstatus.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: pathstatus.xml. 
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
#ifndef PATHSTATUS_H
#define PATHSTATUS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT PathStatus: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float fractional_progress READ getfractional_progress WRITE setfractional_progress NOTIFY fractional_progressChanged);
    Q_PROPERTY(float error READ geterror WRITE seterror NOTIFY errorChanged);
    Q_PROPERTY(float path_direction_north READ getpath_direction_north WRITE setpath_direction_north NOTIFY path_direction_northChanged);
    Q_PROPERTY(float path_direction_east READ getpath_direction_east WRITE setpath_direction_east NOTIFY path_direction_eastChanged);
    Q_PROPERTY(float path_direction_down READ getpath_direction_down WRITE setpath_direction_down NOTIFY path_direction_downChanged);
    Q_PROPERTY(float correction_direction_north READ getcorrection_direction_north WRITE setcorrection_direction_north NOTIFY correction_direction_northChanged);
    Q_PROPERTY(float correction_direction_east READ getcorrection_direction_east WRITE setcorrection_direction_east NOTIFY correction_direction_eastChanged);
    Q_PROPERTY(float correction_direction_down READ getcorrection_direction_down WRITE setcorrection_direction_down NOTIFY correction_direction_downChanged);
    Q_PROPERTY(float path_time READ getpath_time WRITE setpath_time NOTIFY path_timeChanged);
    Q_PROPERTY(qint16 UID READ getUID WRITE setUID NOTIFY UIDChanged);
    Q_PROPERTY(quint8 Status READ getStatus WRITE setStatus NOTIFY StatusChanged);


public:
    // Field structure
    typedef struct {
        float fractional_progress;
        float error;
        float path_direction_north;
        float path_direction_east;
        float path_direction_down;
        float correction_direction_north;
        float correction_direction_east;
        float correction_direction_down;
        float path_time;
        qint16 UID;
        quint8 Status;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field fractional_progress information
    // Field error information
    // Field path_direction_north information
    // Field path_direction_east information
    // Field path_direction_down information
    // Field correction_direction_north information
    // Field correction_direction_east information
    // Field correction_direction_down information
    // Field path_time information
    // Field UID information
    // Field Status information
    /* Enumeration options for field Status */
    typedef enum { STATUS_INPROGRESS=0, STATUS_COMPLETED=1, STATUS_WARNING=2, STATUS_CRITICAL=3 } StatusOptions;

  
    // Constants
    static const quint32 OBJID = 0x65C06EB0;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    PathStatus();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static PathStatus* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getfractional_progress() const;
    Q_INVOKABLE float geterror() const;
    Q_INVOKABLE float getpath_direction_north() const;
    Q_INVOKABLE float getpath_direction_east() const;
    Q_INVOKABLE float getpath_direction_down() const;
    Q_INVOKABLE float getcorrection_direction_north() const;
    Q_INVOKABLE float getcorrection_direction_east() const;
    Q_INVOKABLE float getcorrection_direction_down() const;
    Q_INVOKABLE float getpath_time() const;
    Q_INVOKABLE qint16 getUID() const;
    Q_INVOKABLE quint8 getStatus() const;


public slots:
    void setfractional_progress(float value);
    void seterror(float value);
    void setpath_direction_north(float value);
    void setpath_direction_east(float value);
    void setpath_direction_down(float value);
    void setcorrection_direction_north(float value);
    void setcorrection_direction_east(float value);
    void setcorrection_direction_down(float value);
    void setpath_time(float value);
    void setUID(qint16 value);
    void setStatus(quint8 value);


signals:
    void fractional_progressChanged(float value);
    void errorChanged(float value);
    void path_direction_northChanged(float value);
    void path_direction_eastChanged(float value);
    void path_direction_downChanged(float value);
    void correction_direction_northChanged(float value);
    void correction_direction_eastChanged(float value);
    void correction_direction_downChanged(float value);
    void path_timeChanged(float value);
    void UIDChanged(qint16 value);
    void StatusChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // PATHSTATUS_H
