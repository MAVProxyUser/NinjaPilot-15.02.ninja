/**
 ******************************************************************************
 *
 * @file       altitudeholdsettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: altitudeholdsettings.xml. 
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
#ifndef ALTITUDEHOLDSETTINGS_H
#define ALTITUDEHOLDSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT AltitudeHoldSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float AltitudePI_Kp READ getAltitudePI_Kp WRITE setAltitudePI_Kp NOTIFY AltitudePI_KpChanged);
    Q_PROPERTY(float AltitudePI_Ki READ getAltitudePI_Ki WRITE setAltitudePI_Ki NOTIFY AltitudePI_KiChanged);
    Q_PROPERTY(float AltitudePI_Ilimit READ getAltitudePI_Ilimit WRITE setAltitudePI_Ilimit NOTIFY AltitudePI_IlimitChanged);
    Q_PROPERTY(float VelocityPI_Kp READ getVelocityPI_Kp WRITE setVelocityPI_Kp NOTIFY VelocityPI_KpChanged);
    Q_PROPERTY(float VelocityPI_Ki READ getVelocityPI_Ki WRITE setVelocityPI_Ki NOTIFY VelocityPI_KiChanged);
    Q_PROPERTY(float VelocityPI_Ilimit READ getVelocityPI_Ilimit WRITE setVelocityPI_Ilimit NOTIFY VelocityPI_IlimitChanged);
    Q_PROPERTY(float ThrustRate READ getThrustRate WRITE setThrustRate NOTIFY ThrustRateChanged);
    Q_PROPERTY(quint8 CutThrustWhenZero READ getCutThrustWhenZero WRITE setCutThrustWhenZero NOTIFY CutThrustWhenZeroChanged);
    Q_PROPERTY(quint8 ThrustExp READ getThrustExp WRITE setThrustExp NOTIFY ThrustExpChanged);


public:
    // Field structure
    typedef struct {
        float AltitudePI[3];
        float VelocityPI[3];
        float ThrustRate;
        quint8 CutThrustWhenZero;
        quint8 ThrustExp;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field AltitudePI information
    /* Array element names for field AltitudePI */
    typedef enum { ALTITUDEPI_KP=0, ALTITUDEPI_KI=1, ALTITUDEPI_ILIMIT=2 } AltitudePIElem;
    /* Number of elements for field AltitudePI */
    static const quint32 ALTITUDEPI_NUMELEM = 3;
    // Field VelocityPI information
    /* Array element names for field VelocityPI */
    typedef enum { VELOCITYPI_KP=0, VELOCITYPI_KI=1, VELOCITYPI_ILIMIT=2 } VelocityPIElem;
    /* Number of elements for field VelocityPI */
    static const quint32 VELOCITYPI_NUMELEM = 3;
    // Field ThrustRate information
    // Field CutThrustWhenZero information
    /* Enumeration options for field CutThrustWhenZero */
    typedef enum { CUTTHRUSTWHENZERO_FALSE=0, CUTTHRUSTWHENZERO_TRUE=1 } CutThrustWhenZeroOptions;
    // Field ThrustExp information

  
    // Constants
    static const quint32 OBJID = 0xF19EFC2C;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    AltitudeHoldSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static AltitudeHoldSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getAltitudePI(quint32 index) const;
    Q_INVOKABLE float getAltitudePI_Kp() const;
    Q_INVOKABLE float getAltitudePI_Ki() const;
    Q_INVOKABLE float getAltitudePI_Ilimit() const;
    Q_INVOKABLE float getVelocityPI(quint32 index) const;
    Q_INVOKABLE float getVelocityPI_Kp() const;
    Q_INVOKABLE float getVelocityPI_Ki() const;
    Q_INVOKABLE float getVelocityPI_Ilimit() const;
    Q_INVOKABLE float getThrustRate() const;
    Q_INVOKABLE quint8 getCutThrustWhenZero() const;
    Q_INVOKABLE quint8 getThrustExp() const;


public slots:
    void setAltitudePI(quint32 index, float value);
    void setAltitudePI_Kp(float value);
    void setAltitudePI_Ki(float value);
    void setAltitudePI_Ilimit(float value);
    void setVelocityPI(quint32 index, float value);
    void setVelocityPI_Kp(float value);
    void setVelocityPI_Ki(float value);
    void setVelocityPI_Ilimit(float value);
    void setThrustRate(float value);
    void setCutThrustWhenZero(quint8 value);
    void setThrustExp(quint8 value);


signals:
    void AltitudePIChanged(quint32 index, float value);
    void AltitudePI_KpChanged(float value);
    void AltitudePI_KiChanged(float value);
    void AltitudePI_IlimitChanged(float value);
    void VelocityPIChanged(quint32 index, float value);
    void VelocityPI_KpChanged(float value);
    void VelocityPI_KiChanged(float value);
    void VelocityPI_IlimitChanged(float value);
    void ThrustRateChanged(float value);
    void CutThrustWhenZeroChanged(quint8 value);
    void ThrustExpChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // ALTITUDEHOLDSETTINGS_H
