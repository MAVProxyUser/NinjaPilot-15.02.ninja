/**
 ******************************************************************************
 *
 * @file       ekfstatevariance.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: ekfstatevariance.xml. 
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
#ifndef EKFSTATEVARIANCE_H
#define EKFSTATEVARIANCE_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT EKFStateVariance: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float P_PositionNorth READ getP_PositionNorth WRITE setP_PositionNorth NOTIFY P_PositionNorthChanged);
    Q_PROPERTY(float P_PositionEast READ getP_PositionEast WRITE setP_PositionEast NOTIFY P_PositionEastChanged);
    Q_PROPERTY(float P_PositionDown READ getP_PositionDown WRITE setP_PositionDown NOTIFY P_PositionDownChanged);
    Q_PROPERTY(float P_VelocityNorth READ getP_VelocityNorth WRITE setP_VelocityNorth NOTIFY P_VelocityNorthChanged);
    Q_PROPERTY(float P_VelocityEast READ getP_VelocityEast WRITE setP_VelocityEast NOTIFY P_VelocityEastChanged);
    Q_PROPERTY(float P_VelocityDown READ getP_VelocityDown WRITE setP_VelocityDown NOTIFY P_VelocityDownChanged);
    Q_PROPERTY(float P_AttitudeQ1 READ getP_AttitudeQ1 WRITE setP_AttitudeQ1 NOTIFY P_AttitudeQ1Changed);
    Q_PROPERTY(float P_AttitudeQ2 READ getP_AttitudeQ2 WRITE setP_AttitudeQ2 NOTIFY P_AttitudeQ2Changed);
    Q_PROPERTY(float P_AttitudeQ3 READ getP_AttitudeQ3 WRITE setP_AttitudeQ3 NOTIFY P_AttitudeQ3Changed);
    Q_PROPERTY(float P_AttitudeQ4 READ getP_AttitudeQ4 WRITE setP_AttitudeQ4 NOTIFY P_AttitudeQ4Changed);
    Q_PROPERTY(float P_GyroDriftX READ getP_GyroDriftX WRITE setP_GyroDriftX NOTIFY P_GyroDriftXChanged);
    Q_PROPERTY(float P_GyroDriftY READ getP_GyroDriftY WRITE setP_GyroDriftY NOTIFY P_GyroDriftYChanged);
    Q_PROPERTY(float P_GyroDriftZ READ getP_GyroDriftZ WRITE setP_GyroDriftZ NOTIFY P_GyroDriftZChanged);


public:
    // Field structure
    typedef struct {
        float P[13];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field P information
    /* Array element names for field P */
    typedef enum { P_POSITIONNORTH=0, P_POSITIONEAST=1, P_POSITIONDOWN=2, P_VELOCITYNORTH=3, P_VELOCITYEAST=4, P_VELOCITYDOWN=5, P_ATTITUDEQ1=6, P_ATTITUDEQ2=7, P_ATTITUDEQ3=8, P_ATTITUDEQ4=9, P_GYRODRIFTX=10, P_GYRODRIFTY=11, P_GYRODRIFTZ=12 } PElem;
    /* Number of elements for field P */
    static const quint32 P_NUMELEM = 13;

  
    // Constants
    static const quint32 OBJID = 0x1EB385E4;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    EKFStateVariance();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static EKFStateVariance* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getP(quint32 index) const;
    Q_INVOKABLE float getP_PositionNorth() const;
    Q_INVOKABLE float getP_PositionEast() const;
    Q_INVOKABLE float getP_PositionDown() const;
    Q_INVOKABLE float getP_VelocityNorth() const;
    Q_INVOKABLE float getP_VelocityEast() const;
    Q_INVOKABLE float getP_VelocityDown() const;
    Q_INVOKABLE float getP_AttitudeQ1() const;
    Q_INVOKABLE float getP_AttitudeQ2() const;
    Q_INVOKABLE float getP_AttitudeQ3() const;
    Q_INVOKABLE float getP_AttitudeQ4() const;
    Q_INVOKABLE float getP_GyroDriftX() const;
    Q_INVOKABLE float getP_GyroDriftY() const;
    Q_INVOKABLE float getP_GyroDriftZ() const;


public slots:
    void setP(quint32 index, float value);
    void setP_PositionNorth(float value);
    void setP_PositionEast(float value);
    void setP_PositionDown(float value);
    void setP_VelocityNorth(float value);
    void setP_VelocityEast(float value);
    void setP_VelocityDown(float value);
    void setP_AttitudeQ1(float value);
    void setP_AttitudeQ2(float value);
    void setP_AttitudeQ3(float value);
    void setP_AttitudeQ4(float value);
    void setP_GyroDriftX(float value);
    void setP_GyroDriftY(float value);
    void setP_GyroDriftZ(float value);


signals:
    void PChanged(quint32 index, float value);
    void P_PositionNorthChanged(float value);
    void P_PositionEastChanged(float value);
    void P_PositionDownChanged(float value);
    void P_VelocityNorthChanged(float value);
    void P_VelocityEastChanged(float value);
    void P_VelocityDownChanged(float value);
    void P_AttitudeQ1Changed(float value);
    void P_AttitudeQ2Changed(float value);
    void P_AttitudeQ3Changed(float value);
    void P_AttitudeQ4Changed(float value);
    void P_GyroDriftXChanged(float value);
    void P_GyroDriftYChanged(float value);
    void P_GyroDriftZChanged(float value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // EKFSTATEVARIANCE_H
