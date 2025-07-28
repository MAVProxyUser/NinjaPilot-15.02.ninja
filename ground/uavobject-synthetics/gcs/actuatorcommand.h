/**
 ******************************************************************************
 *
 * @file       actuatorcommand.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: actuatorcommand.xml. 
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
#ifndef ACTUATORCOMMAND_H
#define ACTUATORCOMMAND_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT ActuatorCommand: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(qint16 Channel_0 READ getChannel_0 WRITE setChannel_0 NOTIFY Channel_0Changed);
    Q_PROPERTY(qint16 Channel_1 READ getChannel_1 WRITE setChannel_1 NOTIFY Channel_1Changed);
    Q_PROPERTY(qint16 Channel_2 READ getChannel_2 WRITE setChannel_2 NOTIFY Channel_2Changed);
    Q_PROPERTY(qint16 Channel_3 READ getChannel_3 WRITE setChannel_3 NOTIFY Channel_3Changed);
    Q_PROPERTY(qint16 Channel_4 READ getChannel_4 WRITE setChannel_4 NOTIFY Channel_4Changed);
    Q_PROPERTY(qint16 Channel_5 READ getChannel_5 WRITE setChannel_5 NOTIFY Channel_5Changed);
    Q_PROPERTY(qint16 Channel_6 READ getChannel_6 WRITE setChannel_6 NOTIFY Channel_6Changed);
    Q_PROPERTY(qint16 Channel_7 READ getChannel_7 WRITE setChannel_7 NOTIFY Channel_7Changed);
    Q_PROPERTY(qint16 Channel_8 READ getChannel_8 WRITE setChannel_8 NOTIFY Channel_8Changed);
    Q_PROPERTY(qint16 Channel_9 READ getChannel_9 WRITE setChannel_9 NOTIFY Channel_9Changed);
    Q_PROPERTY(qint16 Channel_10 READ getChannel_10 WRITE setChannel_10 NOTIFY Channel_10Changed);
    Q_PROPERTY(qint16 Channel_11 READ getChannel_11 WRITE setChannel_11 NOTIFY Channel_11Changed);
    Q_PROPERTY(quint16 UpdateTime READ getUpdateTime WRITE setUpdateTime NOTIFY UpdateTimeChanged);
    Q_PROPERTY(quint16 MaxUpdateTime READ getMaxUpdateTime WRITE setMaxUpdateTime NOTIFY MaxUpdateTimeChanged);
    Q_PROPERTY(quint8 NumFailedUpdates READ getNumFailedUpdates WRITE setNumFailedUpdates NOTIFY NumFailedUpdatesChanged);


public:
    // Field structure
    typedef struct {
        qint16 Channel[12];
        quint16 UpdateTime;
        quint16 MaxUpdateTime;
        quint8 NumFailedUpdates;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Channel information
    /* Number of elements for field Channel */
    static const quint32 CHANNEL_NUMELEM = 12;
    // Field UpdateTime information
    // Field MaxUpdateTime information
    // Field NumFailedUpdates information

  
    // Constants
    static const quint32 OBJID = 0xB8229FE4;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    ActuatorCommand();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static ActuatorCommand* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE qint16 getChannel(quint32 index) const;
    Q_INVOKABLE qint16 getChannel_0() const;
    Q_INVOKABLE qint16 getChannel_1() const;
    Q_INVOKABLE qint16 getChannel_2() const;
    Q_INVOKABLE qint16 getChannel_3() const;
    Q_INVOKABLE qint16 getChannel_4() const;
    Q_INVOKABLE qint16 getChannel_5() const;
    Q_INVOKABLE qint16 getChannel_6() const;
    Q_INVOKABLE qint16 getChannel_7() const;
    Q_INVOKABLE qint16 getChannel_8() const;
    Q_INVOKABLE qint16 getChannel_9() const;
    Q_INVOKABLE qint16 getChannel_10() const;
    Q_INVOKABLE qint16 getChannel_11() const;
    Q_INVOKABLE quint16 getUpdateTime() const;
    Q_INVOKABLE quint16 getMaxUpdateTime() const;
    Q_INVOKABLE quint8 getNumFailedUpdates() const;


public slots:
    void setChannel(quint32 index, qint16 value);
    void setChannel_0(qint16 value);
    void setChannel_1(qint16 value);
    void setChannel_2(qint16 value);
    void setChannel_3(qint16 value);
    void setChannel_4(qint16 value);
    void setChannel_5(qint16 value);
    void setChannel_6(qint16 value);
    void setChannel_7(qint16 value);
    void setChannel_8(qint16 value);
    void setChannel_9(qint16 value);
    void setChannel_10(qint16 value);
    void setChannel_11(qint16 value);
    void setUpdateTime(quint16 value);
    void setMaxUpdateTime(quint16 value);
    void setNumFailedUpdates(quint8 value);


signals:
    void ChannelChanged(quint32 index, qint16 value);
    void Channel_0Changed(qint16 value);
    void Channel_1Changed(qint16 value);
    void Channel_2Changed(qint16 value);
    void Channel_3Changed(qint16 value);
    void Channel_4Changed(qint16 value);
    void Channel_5Changed(qint16 value);
    void Channel_6Changed(qint16 value);
    void Channel_7Changed(qint16 value);
    void Channel_8Changed(qint16 value);
    void Channel_9Changed(qint16 value);
    void Channel_10Changed(qint16 value);
    void Channel_11Changed(qint16 value);
    void UpdateTimeChanged(quint16 value);
    void MaxUpdateTimeChanged(quint16 value);
    void NumFailedUpdatesChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // ACTUATORCOMMAND_H
