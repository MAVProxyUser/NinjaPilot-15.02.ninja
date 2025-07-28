/**
 ******************************************************************************
 *
 * @file       pidstatus.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: pidstatus.xml. 
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
#ifndef PIDSTATUS_H
#define PIDSTATUS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT PIDStatus: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float setpoint READ getsetpoint WRITE setsetpoint NOTIFY setpointChanged);
    Q_PROPERTY(float actual READ getactual WRITE setactual NOTIFY actualChanged);
    Q_PROPERTY(float error READ geterror WRITE seterror NOTIFY errorChanged);
    Q_PROPERTY(float ulow READ getulow WRITE setulow NOTIFY ulowChanged);
    Q_PROPERTY(float uhigh READ getuhigh WRITE setuhigh NOTIFY uhighChanged);
    Q_PROPERTY(float command READ getcommand WRITE setcommand NOTIFY commandChanged);
    Q_PROPERTY(float P READ getP WRITE setP NOTIFY PChanged);
    Q_PROPERTY(float I READ getI WRITE setI NOTIFY IChanged);
    Q_PROPERTY(float D READ getD WRITE setD NOTIFY DChanged);


public:
    // Field structure
    typedef struct {
        float setpoint;
        float actual;
        float error;
        float ulow;
        float uhigh;
        float command;
        float P;
        float I;
        float D;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field setpoint information
    // Field actual information
    // Field error information
    // Field ulow information
    // Field uhigh information
    // Field command information
    // Field P information
    // Field I information
    // Field D information

  
    // Constants
    static const quint32 OBJID = 0x75CF70A6;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    PIDStatus();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static PIDStatus* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getsetpoint() const;
    Q_INVOKABLE float getactual() const;
    Q_INVOKABLE float geterror() const;
    Q_INVOKABLE float getulow() const;
    Q_INVOKABLE float getuhigh() const;
    Q_INVOKABLE float getcommand() const;
    Q_INVOKABLE float getP() const;
    Q_INVOKABLE float getI() const;
    Q_INVOKABLE float getD() const;


public slots:
    void setsetpoint(float value);
    void setactual(float value);
    void seterror(float value);
    void setulow(float value);
    void setuhigh(float value);
    void setcommand(float value);
    void setP(float value);
    void setI(float value);
    void setD(float value);


signals:
    void setpointChanged(float value);
    void actualChanged(float value);
    void errorChanged(float value);
    void ulowChanged(float value);
    void uhighChanged(float value);
    void commandChanged(float value);
    void PChanged(float value);
    void IChanged(float value);
    void DChanged(float value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // PIDSTATUS_H
