/**
 ******************************************************************************
 *
 * @file       vtolselftuningstats.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: vtolselftuningstats.xml. 
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
#ifndef VTOLSELFTUNINGSTATS_H
#define VTOLSELFTUNINGSTATS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT VtolSelfTuningStats: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float NeutralThrustOffset READ getNeutralThrustOffset WRITE setNeutralThrustOffset NOTIFY NeutralThrustOffsetChanged);
    Q_PROPERTY(float NeutralThrustCorrection READ getNeutralThrustCorrection WRITE setNeutralThrustCorrection NOTIFY NeutralThrustCorrectionChanged);
    Q_PROPERTY(float NeutralThrustAccumulator READ getNeutralThrustAccumulator WRITE setNeutralThrustAccumulator NOTIFY NeutralThrustAccumulatorChanged);
    Q_PROPERTY(float NeutralThrustRange READ getNeutralThrustRange WRITE setNeutralThrustRange NOTIFY NeutralThrustRangeChanged);


public:
    // Field structure
    typedef struct {
        float NeutralThrustOffset;
        float NeutralThrustCorrection;
        float NeutralThrustAccumulator;
        float NeutralThrustRange;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field NeutralThrustOffset information
    // Field NeutralThrustCorrection information
    // Field NeutralThrustAccumulator information
    // Field NeutralThrustRange information

  
    // Constants
    static const quint32 OBJID = 0x1B0B1B34;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    VtolSelfTuningStats();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static VtolSelfTuningStats* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getNeutralThrustOffset() const;
    Q_INVOKABLE float getNeutralThrustCorrection() const;
    Q_INVOKABLE float getNeutralThrustAccumulator() const;
    Q_INVOKABLE float getNeutralThrustRange() const;


public slots:
    void setNeutralThrustOffset(float value);
    void setNeutralThrustCorrection(float value);
    void setNeutralThrustAccumulator(float value);
    void setNeutralThrustRange(float value);


signals:
    void NeutralThrustOffsetChanged(float value);
    void NeutralThrustCorrectionChanged(float value);
    void NeutralThrustAccumulatorChanged(float value);
    void NeutralThrustRangeChanged(float value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // VTOLSELFTUNINGSTATS_H
