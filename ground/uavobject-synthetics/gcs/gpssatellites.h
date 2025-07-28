/**
 ******************************************************************************
 *
 * @file       gpssatellites.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: gpssatellites.xml. 
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
#ifndef GPSSATELLITES_H
#define GPSSATELLITES_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT GPSSatellites: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(qint16 Azimuth_0 READ getAzimuth_0 WRITE setAzimuth_0 NOTIFY Azimuth_0Changed);
    Q_PROPERTY(qint16 Azimuth_1 READ getAzimuth_1 WRITE setAzimuth_1 NOTIFY Azimuth_1Changed);
    Q_PROPERTY(qint16 Azimuth_2 READ getAzimuth_2 WRITE setAzimuth_2 NOTIFY Azimuth_2Changed);
    Q_PROPERTY(qint16 Azimuth_3 READ getAzimuth_3 WRITE setAzimuth_3 NOTIFY Azimuth_3Changed);
    Q_PROPERTY(qint16 Azimuth_4 READ getAzimuth_4 WRITE setAzimuth_4 NOTIFY Azimuth_4Changed);
    Q_PROPERTY(qint16 Azimuth_5 READ getAzimuth_5 WRITE setAzimuth_5 NOTIFY Azimuth_5Changed);
    Q_PROPERTY(qint16 Azimuth_6 READ getAzimuth_6 WRITE setAzimuth_6 NOTIFY Azimuth_6Changed);
    Q_PROPERTY(qint16 Azimuth_7 READ getAzimuth_7 WRITE setAzimuth_7 NOTIFY Azimuth_7Changed);
    Q_PROPERTY(qint16 Azimuth_8 READ getAzimuth_8 WRITE setAzimuth_8 NOTIFY Azimuth_8Changed);
    Q_PROPERTY(qint16 Azimuth_9 READ getAzimuth_9 WRITE setAzimuth_9 NOTIFY Azimuth_9Changed);
    Q_PROPERTY(qint16 Azimuth_10 READ getAzimuth_10 WRITE setAzimuth_10 NOTIFY Azimuth_10Changed);
    Q_PROPERTY(qint16 Azimuth_11 READ getAzimuth_11 WRITE setAzimuth_11 NOTIFY Azimuth_11Changed);
    Q_PROPERTY(qint16 Azimuth_12 READ getAzimuth_12 WRITE setAzimuth_12 NOTIFY Azimuth_12Changed);
    Q_PROPERTY(qint16 Azimuth_13 READ getAzimuth_13 WRITE setAzimuth_13 NOTIFY Azimuth_13Changed);
    Q_PROPERTY(qint16 Azimuth_14 READ getAzimuth_14 WRITE setAzimuth_14 NOTIFY Azimuth_14Changed);
    Q_PROPERTY(qint16 Azimuth_15 READ getAzimuth_15 WRITE setAzimuth_15 NOTIFY Azimuth_15Changed);
    Q_PROPERTY(qint8 SatsInView READ getSatsInView WRITE setSatsInView NOTIFY SatsInViewChanged);
    Q_PROPERTY(quint8 PRN_0 READ getPRN_0 WRITE setPRN_0 NOTIFY PRN_0Changed);
    Q_PROPERTY(quint8 PRN_1 READ getPRN_1 WRITE setPRN_1 NOTIFY PRN_1Changed);
    Q_PROPERTY(quint8 PRN_2 READ getPRN_2 WRITE setPRN_2 NOTIFY PRN_2Changed);
    Q_PROPERTY(quint8 PRN_3 READ getPRN_3 WRITE setPRN_3 NOTIFY PRN_3Changed);
    Q_PROPERTY(quint8 PRN_4 READ getPRN_4 WRITE setPRN_4 NOTIFY PRN_4Changed);
    Q_PROPERTY(quint8 PRN_5 READ getPRN_5 WRITE setPRN_5 NOTIFY PRN_5Changed);
    Q_PROPERTY(quint8 PRN_6 READ getPRN_6 WRITE setPRN_6 NOTIFY PRN_6Changed);
    Q_PROPERTY(quint8 PRN_7 READ getPRN_7 WRITE setPRN_7 NOTIFY PRN_7Changed);
    Q_PROPERTY(quint8 PRN_8 READ getPRN_8 WRITE setPRN_8 NOTIFY PRN_8Changed);
    Q_PROPERTY(quint8 PRN_9 READ getPRN_9 WRITE setPRN_9 NOTIFY PRN_9Changed);
    Q_PROPERTY(quint8 PRN_10 READ getPRN_10 WRITE setPRN_10 NOTIFY PRN_10Changed);
    Q_PROPERTY(quint8 PRN_11 READ getPRN_11 WRITE setPRN_11 NOTIFY PRN_11Changed);
    Q_PROPERTY(quint8 PRN_12 READ getPRN_12 WRITE setPRN_12 NOTIFY PRN_12Changed);
    Q_PROPERTY(quint8 PRN_13 READ getPRN_13 WRITE setPRN_13 NOTIFY PRN_13Changed);
    Q_PROPERTY(quint8 PRN_14 READ getPRN_14 WRITE setPRN_14 NOTIFY PRN_14Changed);
    Q_PROPERTY(quint8 PRN_15 READ getPRN_15 WRITE setPRN_15 NOTIFY PRN_15Changed);
    Q_PROPERTY(qint8 Elevation_0 READ getElevation_0 WRITE setElevation_0 NOTIFY Elevation_0Changed);
    Q_PROPERTY(qint8 Elevation_1 READ getElevation_1 WRITE setElevation_1 NOTIFY Elevation_1Changed);
    Q_PROPERTY(qint8 Elevation_2 READ getElevation_2 WRITE setElevation_2 NOTIFY Elevation_2Changed);
    Q_PROPERTY(qint8 Elevation_3 READ getElevation_3 WRITE setElevation_3 NOTIFY Elevation_3Changed);
    Q_PROPERTY(qint8 Elevation_4 READ getElevation_4 WRITE setElevation_4 NOTIFY Elevation_4Changed);
    Q_PROPERTY(qint8 Elevation_5 READ getElevation_5 WRITE setElevation_5 NOTIFY Elevation_5Changed);
    Q_PROPERTY(qint8 Elevation_6 READ getElevation_6 WRITE setElevation_6 NOTIFY Elevation_6Changed);
    Q_PROPERTY(qint8 Elevation_7 READ getElevation_7 WRITE setElevation_7 NOTIFY Elevation_7Changed);
    Q_PROPERTY(qint8 Elevation_8 READ getElevation_8 WRITE setElevation_8 NOTIFY Elevation_8Changed);
    Q_PROPERTY(qint8 Elevation_9 READ getElevation_9 WRITE setElevation_9 NOTIFY Elevation_9Changed);
    Q_PROPERTY(qint8 Elevation_10 READ getElevation_10 WRITE setElevation_10 NOTIFY Elevation_10Changed);
    Q_PROPERTY(qint8 Elevation_11 READ getElevation_11 WRITE setElevation_11 NOTIFY Elevation_11Changed);
    Q_PROPERTY(qint8 Elevation_12 READ getElevation_12 WRITE setElevation_12 NOTIFY Elevation_12Changed);
    Q_PROPERTY(qint8 Elevation_13 READ getElevation_13 WRITE setElevation_13 NOTIFY Elevation_13Changed);
    Q_PROPERTY(qint8 Elevation_14 READ getElevation_14 WRITE setElevation_14 NOTIFY Elevation_14Changed);
    Q_PROPERTY(qint8 Elevation_15 READ getElevation_15 WRITE setElevation_15 NOTIFY Elevation_15Changed);
    Q_PROPERTY(qint8 SNR_0 READ getSNR_0 WRITE setSNR_0 NOTIFY SNR_0Changed);
    Q_PROPERTY(qint8 SNR_1 READ getSNR_1 WRITE setSNR_1 NOTIFY SNR_1Changed);
    Q_PROPERTY(qint8 SNR_2 READ getSNR_2 WRITE setSNR_2 NOTIFY SNR_2Changed);
    Q_PROPERTY(qint8 SNR_3 READ getSNR_3 WRITE setSNR_3 NOTIFY SNR_3Changed);
    Q_PROPERTY(qint8 SNR_4 READ getSNR_4 WRITE setSNR_4 NOTIFY SNR_4Changed);
    Q_PROPERTY(qint8 SNR_5 READ getSNR_5 WRITE setSNR_5 NOTIFY SNR_5Changed);
    Q_PROPERTY(qint8 SNR_6 READ getSNR_6 WRITE setSNR_6 NOTIFY SNR_6Changed);
    Q_PROPERTY(qint8 SNR_7 READ getSNR_7 WRITE setSNR_7 NOTIFY SNR_7Changed);
    Q_PROPERTY(qint8 SNR_8 READ getSNR_8 WRITE setSNR_8 NOTIFY SNR_8Changed);
    Q_PROPERTY(qint8 SNR_9 READ getSNR_9 WRITE setSNR_9 NOTIFY SNR_9Changed);
    Q_PROPERTY(qint8 SNR_10 READ getSNR_10 WRITE setSNR_10 NOTIFY SNR_10Changed);
    Q_PROPERTY(qint8 SNR_11 READ getSNR_11 WRITE setSNR_11 NOTIFY SNR_11Changed);
    Q_PROPERTY(qint8 SNR_12 READ getSNR_12 WRITE setSNR_12 NOTIFY SNR_12Changed);
    Q_PROPERTY(qint8 SNR_13 READ getSNR_13 WRITE setSNR_13 NOTIFY SNR_13Changed);
    Q_PROPERTY(qint8 SNR_14 READ getSNR_14 WRITE setSNR_14 NOTIFY SNR_14Changed);
    Q_PROPERTY(qint8 SNR_15 READ getSNR_15 WRITE setSNR_15 NOTIFY SNR_15Changed);


public:
    // Field structure
    typedef struct {
        qint16 Azimuth[16];
        qint8 SatsInView;
        quint8 PRN[16];
        qint8 Elevation[16];
        qint8 SNR[16];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Azimuth information
    /* Number of elements for field Azimuth */
    static const quint32 AZIMUTH_NUMELEM = 16;
    // Field SatsInView information
    // Field PRN information
    /* Number of elements for field PRN */
    static const quint32 PRN_NUMELEM = 16;
    // Field Elevation information
    /* Number of elements for field Elevation */
    static const quint32 ELEVATION_NUMELEM = 16;
    // Field SNR information
    /* Number of elements for field SNR */
    static const quint32 SNR_NUMELEM = 16;

  
    // Constants
    static const quint32 OBJID = 0xC555B700;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    GPSSatellites();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static GPSSatellites* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE qint16 getAzimuth(quint32 index) const;
    Q_INVOKABLE qint16 getAzimuth_0() const;
    Q_INVOKABLE qint16 getAzimuth_1() const;
    Q_INVOKABLE qint16 getAzimuth_2() const;
    Q_INVOKABLE qint16 getAzimuth_3() const;
    Q_INVOKABLE qint16 getAzimuth_4() const;
    Q_INVOKABLE qint16 getAzimuth_5() const;
    Q_INVOKABLE qint16 getAzimuth_6() const;
    Q_INVOKABLE qint16 getAzimuth_7() const;
    Q_INVOKABLE qint16 getAzimuth_8() const;
    Q_INVOKABLE qint16 getAzimuth_9() const;
    Q_INVOKABLE qint16 getAzimuth_10() const;
    Q_INVOKABLE qint16 getAzimuth_11() const;
    Q_INVOKABLE qint16 getAzimuth_12() const;
    Q_INVOKABLE qint16 getAzimuth_13() const;
    Q_INVOKABLE qint16 getAzimuth_14() const;
    Q_INVOKABLE qint16 getAzimuth_15() const;
    Q_INVOKABLE qint8 getSatsInView() const;
    Q_INVOKABLE quint8 getPRN(quint32 index) const;
    Q_INVOKABLE quint8 getPRN_0() const;
    Q_INVOKABLE quint8 getPRN_1() const;
    Q_INVOKABLE quint8 getPRN_2() const;
    Q_INVOKABLE quint8 getPRN_3() const;
    Q_INVOKABLE quint8 getPRN_4() const;
    Q_INVOKABLE quint8 getPRN_5() const;
    Q_INVOKABLE quint8 getPRN_6() const;
    Q_INVOKABLE quint8 getPRN_7() const;
    Q_INVOKABLE quint8 getPRN_8() const;
    Q_INVOKABLE quint8 getPRN_9() const;
    Q_INVOKABLE quint8 getPRN_10() const;
    Q_INVOKABLE quint8 getPRN_11() const;
    Q_INVOKABLE quint8 getPRN_12() const;
    Q_INVOKABLE quint8 getPRN_13() const;
    Q_INVOKABLE quint8 getPRN_14() const;
    Q_INVOKABLE quint8 getPRN_15() const;
    Q_INVOKABLE qint8 getElevation(quint32 index) const;
    Q_INVOKABLE qint8 getElevation_0() const;
    Q_INVOKABLE qint8 getElevation_1() const;
    Q_INVOKABLE qint8 getElevation_2() const;
    Q_INVOKABLE qint8 getElevation_3() const;
    Q_INVOKABLE qint8 getElevation_4() const;
    Q_INVOKABLE qint8 getElevation_5() const;
    Q_INVOKABLE qint8 getElevation_6() const;
    Q_INVOKABLE qint8 getElevation_7() const;
    Q_INVOKABLE qint8 getElevation_8() const;
    Q_INVOKABLE qint8 getElevation_9() const;
    Q_INVOKABLE qint8 getElevation_10() const;
    Q_INVOKABLE qint8 getElevation_11() const;
    Q_INVOKABLE qint8 getElevation_12() const;
    Q_INVOKABLE qint8 getElevation_13() const;
    Q_INVOKABLE qint8 getElevation_14() const;
    Q_INVOKABLE qint8 getElevation_15() const;
    Q_INVOKABLE qint8 getSNR(quint32 index) const;
    Q_INVOKABLE qint8 getSNR_0() const;
    Q_INVOKABLE qint8 getSNR_1() const;
    Q_INVOKABLE qint8 getSNR_2() const;
    Q_INVOKABLE qint8 getSNR_3() const;
    Q_INVOKABLE qint8 getSNR_4() const;
    Q_INVOKABLE qint8 getSNR_5() const;
    Q_INVOKABLE qint8 getSNR_6() const;
    Q_INVOKABLE qint8 getSNR_7() const;
    Q_INVOKABLE qint8 getSNR_8() const;
    Q_INVOKABLE qint8 getSNR_9() const;
    Q_INVOKABLE qint8 getSNR_10() const;
    Q_INVOKABLE qint8 getSNR_11() const;
    Q_INVOKABLE qint8 getSNR_12() const;
    Q_INVOKABLE qint8 getSNR_13() const;
    Q_INVOKABLE qint8 getSNR_14() const;
    Q_INVOKABLE qint8 getSNR_15() const;


public slots:
    void setAzimuth(quint32 index, qint16 value);
    void setAzimuth_0(qint16 value);
    void setAzimuth_1(qint16 value);
    void setAzimuth_2(qint16 value);
    void setAzimuth_3(qint16 value);
    void setAzimuth_4(qint16 value);
    void setAzimuth_5(qint16 value);
    void setAzimuth_6(qint16 value);
    void setAzimuth_7(qint16 value);
    void setAzimuth_8(qint16 value);
    void setAzimuth_9(qint16 value);
    void setAzimuth_10(qint16 value);
    void setAzimuth_11(qint16 value);
    void setAzimuth_12(qint16 value);
    void setAzimuth_13(qint16 value);
    void setAzimuth_14(qint16 value);
    void setAzimuth_15(qint16 value);
    void setSatsInView(qint8 value);
    void setPRN(quint32 index, quint8 value);
    void setPRN_0(quint8 value);
    void setPRN_1(quint8 value);
    void setPRN_2(quint8 value);
    void setPRN_3(quint8 value);
    void setPRN_4(quint8 value);
    void setPRN_5(quint8 value);
    void setPRN_6(quint8 value);
    void setPRN_7(quint8 value);
    void setPRN_8(quint8 value);
    void setPRN_9(quint8 value);
    void setPRN_10(quint8 value);
    void setPRN_11(quint8 value);
    void setPRN_12(quint8 value);
    void setPRN_13(quint8 value);
    void setPRN_14(quint8 value);
    void setPRN_15(quint8 value);
    void setElevation(quint32 index, qint8 value);
    void setElevation_0(qint8 value);
    void setElevation_1(qint8 value);
    void setElevation_2(qint8 value);
    void setElevation_3(qint8 value);
    void setElevation_4(qint8 value);
    void setElevation_5(qint8 value);
    void setElevation_6(qint8 value);
    void setElevation_7(qint8 value);
    void setElevation_8(qint8 value);
    void setElevation_9(qint8 value);
    void setElevation_10(qint8 value);
    void setElevation_11(qint8 value);
    void setElevation_12(qint8 value);
    void setElevation_13(qint8 value);
    void setElevation_14(qint8 value);
    void setElevation_15(qint8 value);
    void setSNR(quint32 index, qint8 value);
    void setSNR_0(qint8 value);
    void setSNR_1(qint8 value);
    void setSNR_2(qint8 value);
    void setSNR_3(qint8 value);
    void setSNR_4(qint8 value);
    void setSNR_5(qint8 value);
    void setSNR_6(qint8 value);
    void setSNR_7(qint8 value);
    void setSNR_8(qint8 value);
    void setSNR_9(qint8 value);
    void setSNR_10(qint8 value);
    void setSNR_11(qint8 value);
    void setSNR_12(qint8 value);
    void setSNR_13(qint8 value);
    void setSNR_14(qint8 value);
    void setSNR_15(qint8 value);


signals:
    void AzimuthChanged(quint32 index, qint16 value);
    void Azimuth_0Changed(qint16 value);
    void Azimuth_1Changed(qint16 value);
    void Azimuth_2Changed(qint16 value);
    void Azimuth_3Changed(qint16 value);
    void Azimuth_4Changed(qint16 value);
    void Azimuth_5Changed(qint16 value);
    void Azimuth_6Changed(qint16 value);
    void Azimuth_7Changed(qint16 value);
    void Azimuth_8Changed(qint16 value);
    void Azimuth_9Changed(qint16 value);
    void Azimuth_10Changed(qint16 value);
    void Azimuth_11Changed(qint16 value);
    void Azimuth_12Changed(qint16 value);
    void Azimuth_13Changed(qint16 value);
    void Azimuth_14Changed(qint16 value);
    void Azimuth_15Changed(qint16 value);
    void SatsInViewChanged(qint8 value);
    void PRNChanged(quint32 index, quint8 value);
    void PRN_0Changed(quint8 value);
    void PRN_1Changed(quint8 value);
    void PRN_2Changed(quint8 value);
    void PRN_3Changed(quint8 value);
    void PRN_4Changed(quint8 value);
    void PRN_5Changed(quint8 value);
    void PRN_6Changed(quint8 value);
    void PRN_7Changed(quint8 value);
    void PRN_8Changed(quint8 value);
    void PRN_9Changed(quint8 value);
    void PRN_10Changed(quint8 value);
    void PRN_11Changed(quint8 value);
    void PRN_12Changed(quint8 value);
    void PRN_13Changed(quint8 value);
    void PRN_14Changed(quint8 value);
    void PRN_15Changed(quint8 value);
    void ElevationChanged(quint32 index, qint8 value);
    void Elevation_0Changed(qint8 value);
    void Elevation_1Changed(qint8 value);
    void Elevation_2Changed(qint8 value);
    void Elevation_3Changed(qint8 value);
    void Elevation_4Changed(qint8 value);
    void Elevation_5Changed(qint8 value);
    void Elevation_6Changed(qint8 value);
    void Elevation_7Changed(qint8 value);
    void Elevation_8Changed(qint8 value);
    void Elevation_9Changed(qint8 value);
    void Elevation_10Changed(qint8 value);
    void Elevation_11Changed(qint8 value);
    void Elevation_12Changed(qint8 value);
    void Elevation_13Changed(qint8 value);
    void Elevation_14Changed(qint8 value);
    void Elevation_15Changed(qint8 value);
    void SNRChanged(quint32 index, qint8 value);
    void SNR_0Changed(qint8 value);
    void SNR_1Changed(qint8 value);
    void SNR_2Changed(qint8 value);
    void SNR_3Changed(qint8 value);
    void SNR_4Changed(qint8 value);
    void SNR_5Changed(qint8 value);
    void SNR_6Changed(qint8 value);
    void SNR_7Changed(qint8 value);
    void SNR_8Changed(qint8 value);
    void SNR_9Changed(qint8 value);
    void SNR_10Changed(qint8 value);
    void SNR_11Changed(qint8 value);
    void SNR_12Changed(qint8 value);
    void SNR_13Changed(qint8 value);
    void SNR_14Changed(qint8 value);
    void SNR_15Changed(qint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // GPSSATELLITES_H
