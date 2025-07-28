/**
 ******************************************************************************
 *
 * @file       flightplanstatus.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: flightplanstatus.xml. 
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
#ifndef FLIGHTPLANSTATUS_H
#define FLIGHTPLANSTATUS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT FlightPlanStatus: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 ErrorFileID READ getErrorFileID WRITE setErrorFileID NOTIFY ErrorFileIDChanged);
    Q_PROPERTY(quint32 ErrorLineNum READ getErrorLineNum WRITE setErrorLineNum NOTIFY ErrorLineNumChanged);
    Q_PROPERTY(float Debug_0 READ getDebug_0 WRITE setDebug_0 NOTIFY Debug_0Changed);
    Q_PROPERTY(float Debug_1 READ getDebug_1 WRITE setDebug_1 NOTIFY Debug_1Changed);
    Q_PROPERTY(quint8 Status READ getStatus WRITE setStatus NOTIFY StatusChanged);
    Q_PROPERTY(quint8 ErrorType READ getErrorType WRITE setErrorType NOTIFY ErrorTypeChanged);


public:
    // Field structure
    typedef struct {
        quint32 ErrorFileID;
        quint32 ErrorLineNum;
        float Debug[2];
        quint8 Status;
        quint8 ErrorType;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field ErrorFileID information
    // Field ErrorLineNum information
    // Field Debug information
    /* Number of elements for field Debug */
    static const quint32 DEBUG_NUMELEM = 2;
    // Field Status information
    /* Enumeration options for field Status */
    typedef enum { STATUS_STOPPED=0, STATUS_RUNNING=1, STATUS_ERROR=2 } StatusOptions;
    // Field ErrorType information
    /* Enumeration options for field ErrorType */
    typedef enum { ERRORTYPE_NONE=0, ERRORTYPE_VMINITERROR=1, ERRORTYPE_EXCEPTION=2, ERRORTYPE_IOERROR=3, ERRORTYPE_DIVBYZERO=4, ERRORTYPE_ASSERTERROR=5, ERRORTYPE_ATTRIBUTEERROR=6, ERRORTYPE_IMPORTERROR=7, ERRORTYPE_INDEXERROR=8, ERRORTYPE_KEYERROR=9, ERRORTYPE_MEMORYERROR=10, ERRORTYPE_NAMEERROR=11, ERRORTYPE_SYNTAXERROR=12, ERRORTYPE_SYSTEMERROR=13, ERRORTYPE_TYPEERROR=14, ERRORTYPE_VALUEERROR=15, ERRORTYPE_STOPITERATION=16, ERRORTYPE_WARNING=17, ERRORTYPE_UNKNOWNERROR=18 } ErrorTypeOptions;

  
    // Constants
    static const quint32 OBJID = 0x2206EE46;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    FlightPlanStatus();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static FlightPlanStatus* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint32 getErrorFileID() const;
    Q_INVOKABLE quint32 getErrorLineNum() const;
    Q_INVOKABLE float getDebug(quint32 index) const;
    Q_INVOKABLE float getDebug_0() const;
    Q_INVOKABLE float getDebug_1() const;
    Q_INVOKABLE quint8 getStatus() const;
    Q_INVOKABLE quint8 getErrorType() const;


public slots:
    void setErrorFileID(quint32 value);
    void setErrorLineNum(quint32 value);
    void setDebug(quint32 index, float value);
    void setDebug_0(float value);
    void setDebug_1(float value);
    void setStatus(quint8 value);
    void setErrorType(quint8 value);


signals:
    void ErrorFileIDChanged(quint32 value);
    void ErrorLineNumChanged(quint32 value);
    void DebugChanged(quint32 index, float value);
    void Debug_0Changed(float value);
    void Debug_1Changed(float value);
    void StatusChanged(quint8 value);
    void ErrorTypeChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // FLIGHTPLANSTATUS_H
