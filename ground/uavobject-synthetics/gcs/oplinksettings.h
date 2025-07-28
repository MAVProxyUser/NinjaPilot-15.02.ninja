/**
 ******************************************************************************
 *
 * @file       oplinksettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: oplinksettings.xml. 
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
#ifndef OPLINKSETTINGS_H
#define OPLINKSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT OPLinkSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 CoordID READ getCoordID WRITE setCoordID NOTIFY CoordIDChanged);
    Q_PROPERTY(quint8 Coordinator READ getCoordinator WRITE setCoordinator NOTIFY CoordinatorChanged);
    Q_PROPERTY(quint8 OneWay READ getOneWay WRITE setOneWay NOTIFY OneWayChanged);
    Q_PROPERTY(quint8 PPM READ getPPM WRITE setPPM NOTIFY PPMChanged);
    Q_PROPERTY(quint8 PPMOnly READ getPPMOnly WRITE setPPMOnly NOTIFY PPMOnlyChanged);
    Q_PROPERTY(quint8 MainPort READ getMainPort WRITE setMainPort NOTIFY MainPortChanged);
    Q_PROPERTY(quint8 FlexiPort READ getFlexiPort WRITE setFlexiPort NOTIFY FlexiPortChanged);
    Q_PROPERTY(quint8 VCPPort READ getVCPPort WRITE setVCPPort NOTIFY VCPPortChanged);
    Q_PROPERTY(quint8 ComSpeed READ getComSpeed WRITE setComSpeed NOTIFY ComSpeedChanged);
    Q_PROPERTY(quint8 MaxRFPower READ getMaxRFPower WRITE setMaxRFPower NOTIFY MaxRFPowerChanged);
    Q_PROPERTY(quint8 MinChannel READ getMinChannel WRITE setMinChannel NOTIFY MinChannelChanged);
    Q_PROPERTY(quint8 MaxChannel READ getMaxChannel WRITE setMaxChannel NOTIFY MaxChannelChanged);


public:
    // Field structure
    typedef struct {
        quint32 CoordID;
        quint8 Coordinator;
        quint8 OneWay;
        quint8 PPM;
        quint8 PPMOnly;
        quint8 MainPort;
        quint8 FlexiPort;
        quint8 VCPPort;
        quint8 ComSpeed;
        quint8 MaxRFPower;
        quint8 MinChannel;
        quint8 MaxChannel;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field CoordID information
    // Field Coordinator information
    /* Enumeration options for field Coordinator */
    typedef enum { COORDINATOR_FALSE=0, COORDINATOR_TRUE=1 } CoordinatorOptions;
    // Field OneWay information
    /* Enumeration options for field OneWay */
    typedef enum { ONEWAY_FALSE=0, ONEWAY_TRUE=1 } OneWayOptions;
    // Field PPM information
    /* Enumeration options for field PPM */
    typedef enum { PPM_FALSE=0, PPM_TRUE=1 } PPMOptions;
    // Field PPMOnly information
    /* Enumeration options for field PPMOnly */
    typedef enum { PPMONLY_FALSE=0, PPMONLY_TRUE=1 } PPMOnlyOptions;
    // Field MainPort information
    /* Enumeration options for field MainPort */
    typedef enum { MAINPORT_DISABLED=0, MAINPORT_TELEMETRY=1, MAINPORT_SERIAL=2, MAINPORT_PPM=3, MAINPORT_PWM=4 } MainPortOptions;
    // Field FlexiPort information
    /* Enumeration options for field FlexiPort */
    typedef enum { FLEXIPORT_DISABLED=0, FLEXIPORT_TELEMETRY=1, FLEXIPORT_SERIAL=2, FLEXIPORT_PPM=3, FLEXIPORT_PWM=4 } FlexiPortOptions;
    // Field VCPPort information
    /* Enumeration options for field VCPPort */
    typedef enum { VCPPORT_DISABLED=0, VCPPORT_SERIAL=1 } VCPPortOptions;
    // Field ComSpeed information
    /* Enumeration options for field ComSpeed */
    typedef enum { COMSPEED_4800=0, COMSPEED_9600=1, COMSPEED_19200=2, COMSPEED_38400=3, COMSPEED_57600=4, COMSPEED_115200=5 } ComSpeedOptions;
    // Field MaxRFPower information
    /* Enumeration options for field MaxRFPower */
    typedef enum { MAXRFPOWER_0=0, MAXRFPOWER_125=1, MAXRFPOWER_16=2, MAXRFPOWER_316=3, MAXRFPOWER_63=4, MAXRFPOWER_126=5, MAXRFPOWER_25=6, MAXRFPOWER_50=7, MAXRFPOWER_100=8 } MaxRFPowerOptions;
    // Field MinChannel information
    // Field MaxChannel information

  
    // Constants
    static const quint32 OBJID = 0x8885F812;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    OPLinkSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static OPLinkSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint32 getCoordID() const;
    Q_INVOKABLE quint8 getCoordinator() const;
    Q_INVOKABLE quint8 getOneWay() const;
    Q_INVOKABLE quint8 getPPM() const;
    Q_INVOKABLE quint8 getPPMOnly() const;
    Q_INVOKABLE quint8 getMainPort() const;
    Q_INVOKABLE quint8 getFlexiPort() const;
    Q_INVOKABLE quint8 getVCPPort() const;
    Q_INVOKABLE quint8 getComSpeed() const;
    Q_INVOKABLE quint8 getMaxRFPower() const;
    Q_INVOKABLE quint8 getMinChannel() const;
    Q_INVOKABLE quint8 getMaxChannel() const;


public slots:
    void setCoordID(quint32 value);
    void setCoordinator(quint8 value);
    void setOneWay(quint8 value);
    void setPPM(quint8 value);
    void setPPMOnly(quint8 value);
    void setMainPort(quint8 value);
    void setFlexiPort(quint8 value);
    void setVCPPort(quint8 value);
    void setComSpeed(quint8 value);
    void setMaxRFPower(quint8 value);
    void setMinChannel(quint8 value);
    void setMaxChannel(quint8 value);


signals:
    void CoordIDChanged(quint32 value);
    void CoordinatorChanged(quint8 value);
    void OneWayChanged(quint8 value);
    void PPMChanged(quint8 value);
    void PPMOnlyChanged(quint8 value);
    void MainPortChanged(quint8 value);
    void FlexiPortChanged(quint8 value);
    void VCPPortChanged(quint8 value);
    void ComSpeedChanged(quint8 value);
    void MaxRFPowerChanged(quint8 value);
    void MinChannelChanged(quint8 value);
    void MaxChannelChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // OPLINKSETTINGS_H
