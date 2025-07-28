/**
 ******************************************************************************
 *
 * @file       mixerstatus.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: mixerstatus.xml. 
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
#ifndef MIXERSTATUS_H
#define MIXERSTATUS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT MixerStatus: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float Mixer1 READ getMixer1 WRITE setMixer1 NOTIFY Mixer1Changed);
    Q_PROPERTY(float Mixer2 READ getMixer2 WRITE setMixer2 NOTIFY Mixer2Changed);
    Q_PROPERTY(float Mixer3 READ getMixer3 WRITE setMixer3 NOTIFY Mixer3Changed);
    Q_PROPERTY(float Mixer4 READ getMixer4 WRITE setMixer4 NOTIFY Mixer4Changed);
    Q_PROPERTY(float Mixer5 READ getMixer5 WRITE setMixer5 NOTIFY Mixer5Changed);
    Q_PROPERTY(float Mixer6 READ getMixer6 WRITE setMixer6 NOTIFY Mixer6Changed);
    Q_PROPERTY(float Mixer7 READ getMixer7 WRITE setMixer7 NOTIFY Mixer7Changed);
    Q_PROPERTY(float Mixer8 READ getMixer8 WRITE setMixer8 NOTIFY Mixer8Changed);
    Q_PROPERTY(float Mixer9 READ getMixer9 WRITE setMixer9 NOTIFY Mixer9Changed);
    Q_PROPERTY(float Mixer10 READ getMixer10 WRITE setMixer10 NOTIFY Mixer10Changed);
    Q_PROPERTY(float Mixer11 READ getMixer11 WRITE setMixer11 NOTIFY Mixer11Changed);
    Q_PROPERTY(float Mixer12 READ getMixer12 WRITE setMixer12 NOTIFY Mixer12Changed);


public:
    // Field structure
    typedef struct {
        float Mixer1;
        float Mixer2;
        float Mixer3;
        float Mixer4;
        float Mixer5;
        float Mixer6;
        float Mixer7;
        float Mixer8;
        float Mixer9;
        float Mixer10;
        float Mixer11;
        float Mixer12;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Mixer1 information
    // Field Mixer2 information
    // Field Mixer3 information
    // Field Mixer4 information
    // Field Mixer5 information
    // Field Mixer6 information
    // Field Mixer7 information
    // Field Mixer8 information
    // Field Mixer9 information
    // Field Mixer10 information
    // Field Mixer11 information
    // Field Mixer12 information

  
    // Constants
    static const quint32 OBJID = 0x354C0F40;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    MixerStatus();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static MixerStatus* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getMixer1() const;
    Q_INVOKABLE float getMixer2() const;
    Q_INVOKABLE float getMixer3() const;
    Q_INVOKABLE float getMixer4() const;
    Q_INVOKABLE float getMixer5() const;
    Q_INVOKABLE float getMixer6() const;
    Q_INVOKABLE float getMixer7() const;
    Q_INVOKABLE float getMixer8() const;
    Q_INVOKABLE float getMixer9() const;
    Q_INVOKABLE float getMixer10() const;
    Q_INVOKABLE float getMixer11() const;
    Q_INVOKABLE float getMixer12() const;


public slots:
    void setMixer1(float value);
    void setMixer2(float value);
    void setMixer3(float value);
    void setMixer4(float value);
    void setMixer5(float value);
    void setMixer6(float value);
    void setMixer7(float value);
    void setMixer8(float value);
    void setMixer9(float value);
    void setMixer10(float value);
    void setMixer11(float value);
    void setMixer12(float value);


signals:
    void Mixer1Changed(float value);
    void Mixer2Changed(float value);
    void Mixer3Changed(float value);
    void Mixer4Changed(float value);
    void Mixer5Changed(float value);
    void Mixer6Changed(float value);
    void Mixer7Changed(float value);
    void Mixer8Changed(float value);
    void Mixer9Changed(float value);
    void Mixer10Changed(float value);
    void Mixer11Changed(float value);
    void Mixer12Changed(float value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // MIXERSTATUS_H
