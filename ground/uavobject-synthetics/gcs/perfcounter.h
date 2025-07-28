/**
 ******************************************************************************
 *
 * @file       perfcounter.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: perfcounter.xml. 
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
#ifndef PERFCOUNTER_H
#define PERFCOUNTER_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT PerfCounter: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 Id READ getId WRITE setId NOTIFY IdChanged);
    Q_PROPERTY(qint32 Counter_Value READ getCounter_Value WRITE setCounter_Value NOTIFY Counter_ValueChanged);
    Q_PROPERTY(qint32 Counter_Min READ getCounter_Min WRITE setCounter_Min NOTIFY Counter_MinChanged);
    Q_PROPERTY(qint32 Counter_Max READ getCounter_Max WRITE setCounter_Max NOTIFY Counter_MaxChanged);


public:
    // Field structure
    typedef struct {
        quint32 Id;
        qint32 Counter[3];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Id information
    // Field Counter information
    /* Array element names for field Counter */
    typedef enum { COUNTER_VALUE=0, COUNTER_MIN=1, COUNTER_MAX=2 } CounterElem;
    /* Number of elements for field Counter */
    static const quint32 COUNTER_NUMELEM = 3;

  
    // Constants
    static const quint32 OBJID = 0x692FBF7A;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 0;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    PerfCounter();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static PerfCounter* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint32 getId() const;
    Q_INVOKABLE qint32 getCounter(quint32 index) const;
    Q_INVOKABLE qint32 getCounter_Value() const;
    Q_INVOKABLE qint32 getCounter_Min() const;
    Q_INVOKABLE qint32 getCounter_Max() const;


public slots:
    void setId(quint32 value);
    void setCounter(quint32 index, qint32 value);
    void setCounter_Value(qint32 value);
    void setCounter_Min(qint32 value);
    void setCounter_Max(qint32 value);


signals:
    void IdChanged(quint32 value);
    void CounterChanged(quint32 index, qint32 value);
    void Counter_ValueChanged(qint32 value);
    void Counter_MinChanged(qint32 value);
    void Counter_MaxChanged(qint32 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // PERFCOUNTER_H
