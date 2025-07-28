/**
 ******************************************************************************
 *
 * @file       actuatorsettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: actuatorsettings.xml. 
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
#ifndef ACTUATORSETTINGS_H
#define ACTUATORSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT ActuatorSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 BankUpdateFreq_0 READ getBankUpdateFreq_0 WRITE setBankUpdateFreq_0 NOTIFY BankUpdateFreq_0Changed);
    Q_PROPERTY(quint16 BankUpdateFreq_1 READ getBankUpdateFreq_1 WRITE setBankUpdateFreq_1 NOTIFY BankUpdateFreq_1Changed);
    Q_PROPERTY(quint16 BankUpdateFreq_2 READ getBankUpdateFreq_2 WRITE setBankUpdateFreq_2 NOTIFY BankUpdateFreq_2Changed);
    Q_PROPERTY(quint16 BankUpdateFreq_3 READ getBankUpdateFreq_3 WRITE setBankUpdateFreq_3 NOTIFY BankUpdateFreq_3Changed);
    Q_PROPERTY(quint16 BankUpdateFreq_4 READ getBankUpdateFreq_4 WRITE setBankUpdateFreq_4 NOTIFY BankUpdateFreq_4Changed);
    Q_PROPERTY(quint16 BankUpdateFreq_5 READ getBankUpdateFreq_5 WRITE setBankUpdateFreq_5 NOTIFY BankUpdateFreq_5Changed);
    Q_PROPERTY(qint16 ChannelMax_0 READ getChannelMax_0 WRITE setChannelMax_0 NOTIFY ChannelMax_0Changed);
    Q_PROPERTY(qint16 ChannelMax_1 READ getChannelMax_1 WRITE setChannelMax_1 NOTIFY ChannelMax_1Changed);
    Q_PROPERTY(qint16 ChannelMax_2 READ getChannelMax_2 WRITE setChannelMax_2 NOTIFY ChannelMax_2Changed);
    Q_PROPERTY(qint16 ChannelMax_3 READ getChannelMax_3 WRITE setChannelMax_3 NOTIFY ChannelMax_3Changed);
    Q_PROPERTY(qint16 ChannelMax_4 READ getChannelMax_4 WRITE setChannelMax_4 NOTIFY ChannelMax_4Changed);
    Q_PROPERTY(qint16 ChannelMax_5 READ getChannelMax_5 WRITE setChannelMax_5 NOTIFY ChannelMax_5Changed);
    Q_PROPERTY(qint16 ChannelMax_6 READ getChannelMax_6 WRITE setChannelMax_6 NOTIFY ChannelMax_6Changed);
    Q_PROPERTY(qint16 ChannelMax_7 READ getChannelMax_7 WRITE setChannelMax_7 NOTIFY ChannelMax_7Changed);
    Q_PROPERTY(qint16 ChannelMax_8 READ getChannelMax_8 WRITE setChannelMax_8 NOTIFY ChannelMax_8Changed);
    Q_PROPERTY(qint16 ChannelMax_9 READ getChannelMax_9 WRITE setChannelMax_9 NOTIFY ChannelMax_9Changed);
    Q_PROPERTY(qint16 ChannelMax_10 READ getChannelMax_10 WRITE setChannelMax_10 NOTIFY ChannelMax_10Changed);
    Q_PROPERTY(qint16 ChannelMax_11 READ getChannelMax_11 WRITE setChannelMax_11 NOTIFY ChannelMax_11Changed);
    Q_PROPERTY(qint16 ChannelNeutral_0 READ getChannelNeutral_0 WRITE setChannelNeutral_0 NOTIFY ChannelNeutral_0Changed);
    Q_PROPERTY(qint16 ChannelNeutral_1 READ getChannelNeutral_1 WRITE setChannelNeutral_1 NOTIFY ChannelNeutral_1Changed);
    Q_PROPERTY(qint16 ChannelNeutral_2 READ getChannelNeutral_2 WRITE setChannelNeutral_2 NOTIFY ChannelNeutral_2Changed);
    Q_PROPERTY(qint16 ChannelNeutral_3 READ getChannelNeutral_3 WRITE setChannelNeutral_3 NOTIFY ChannelNeutral_3Changed);
    Q_PROPERTY(qint16 ChannelNeutral_4 READ getChannelNeutral_4 WRITE setChannelNeutral_4 NOTIFY ChannelNeutral_4Changed);
    Q_PROPERTY(qint16 ChannelNeutral_5 READ getChannelNeutral_5 WRITE setChannelNeutral_5 NOTIFY ChannelNeutral_5Changed);
    Q_PROPERTY(qint16 ChannelNeutral_6 READ getChannelNeutral_6 WRITE setChannelNeutral_6 NOTIFY ChannelNeutral_6Changed);
    Q_PROPERTY(qint16 ChannelNeutral_7 READ getChannelNeutral_7 WRITE setChannelNeutral_7 NOTIFY ChannelNeutral_7Changed);
    Q_PROPERTY(qint16 ChannelNeutral_8 READ getChannelNeutral_8 WRITE setChannelNeutral_8 NOTIFY ChannelNeutral_8Changed);
    Q_PROPERTY(qint16 ChannelNeutral_9 READ getChannelNeutral_9 WRITE setChannelNeutral_9 NOTIFY ChannelNeutral_9Changed);
    Q_PROPERTY(qint16 ChannelNeutral_10 READ getChannelNeutral_10 WRITE setChannelNeutral_10 NOTIFY ChannelNeutral_10Changed);
    Q_PROPERTY(qint16 ChannelNeutral_11 READ getChannelNeutral_11 WRITE setChannelNeutral_11 NOTIFY ChannelNeutral_11Changed);
    Q_PROPERTY(qint16 ChannelMin_0 READ getChannelMin_0 WRITE setChannelMin_0 NOTIFY ChannelMin_0Changed);
    Q_PROPERTY(qint16 ChannelMin_1 READ getChannelMin_1 WRITE setChannelMin_1 NOTIFY ChannelMin_1Changed);
    Q_PROPERTY(qint16 ChannelMin_2 READ getChannelMin_2 WRITE setChannelMin_2 NOTIFY ChannelMin_2Changed);
    Q_PROPERTY(qint16 ChannelMin_3 READ getChannelMin_3 WRITE setChannelMin_3 NOTIFY ChannelMin_3Changed);
    Q_PROPERTY(qint16 ChannelMin_4 READ getChannelMin_4 WRITE setChannelMin_4 NOTIFY ChannelMin_4Changed);
    Q_PROPERTY(qint16 ChannelMin_5 READ getChannelMin_5 WRITE setChannelMin_5 NOTIFY ChannelMin_5Changed);
    Q_PROPERTY(qint16 ChannelMin_6 READ getChannelMin_6 WRITE setChannelMin_6 NOTIFY ChannelMin_6Changed);
    Q_PROPERTY(qint16 ChannelMin_7 READ getChannelMin_7 WRITE setChannelMin_7 NOTIFY ChannelMin_7Changed);
    Q_PROPERTY(qint16 ChannelMin_8 READ getChannelMin_8 WRITE setChannelMin_8 NOTIFY ChannelMin_8Changed);
    Q_PROPERTY(qint16 ChannelMin_9 READ getChannelMin_9 WRITE setChannelMin_9 NOTIFY ChannelMin_9Changed);
    Q_PROPERTY(qint16 ChannelMin_10 READ getChannelMin_10 WRITE setChannelMin_10 NOTIFY ChannelMin_10Changed);
    Q_PROPERTY(qint16 ChannelMin_11 READ getChannelMin_11 WRITE setChannelMin_11 NOTIFY ChannelMin_11Changed);
    Q_PROPERTY(quint8 BankMode_0 READ getBankMode_0 WRITE setBankMode_0 NOTIFY BankMode_0Changed);
    Q_PROPERTY(quint8 BankMode_1 READ getBankMode_1 WRITE setBankMode_1 NOTIFY BankMode_1Changed);
    Q_PROPERTY(quint8 BankMode_2 READ getBankMode_2 WRITE setBankMode_2 NOTIFY BankMode_2Changed);
    Q_PROPERTY(quint8 BankMode_3 READ getBankMode_3 WRITE setBankMode_3 NOTIFY BankMode_3Changed);
    Q_PROPERTY(quint8 BankMode_4 READ getBankMode_4 WRITE setBankMode_4 NOTIFY BankMode_4Changed);
    Q_PROPERTY(quint8 BankMode_5 READ getBankMode_5 WRITE setBankMode_5 NOTIFY BankMode_5Changed);
    Q_PROPERTY(quint8 ChannelType_0 READ getChannelType_0 WRITE setChannelType_0 NOTIFY ChannelType_0Changed);
    Q_PROPERTY(quint8 ChannelType_1 READ getChannelType_1 WRITE setChannelType_1 NOTIFY ChannelType_1Changed);
    Q_PROPERTY(quint8 ChannelType_2 READ getChannelType_2 WRITE setChannelType_2 NOTIFY ChannelType_2Changed);
    Q_PROPERTY(quint8 ChannelType_3 READ getChannelType_3 WRITE setChannelType_3 NOTIFY ChannelType_3Changed);
    Q_PROPERTY(quint8 ChannelType_4 READ getChannelType_4 WRITE setChannelType_4 NOTIFY ChannelType_4Changed);
    Q_PROPERTY(quint8 ChannelType_5 READ getChannelType_5 WRITE setChannelType_5 NOTIFY ChannelType_5Changed);
    Q_PROPERTY(quint8 ChannelType_6 READ getChannelType_6 WRITE setChannelType_6 NOTIFY ChannelType_6Changed);
    Q_PROPERTY(quint8 ChannelType_7 READ getChannelType_7 WRITE setChannelType_7 NOTIFY ChannelType_7Changed);
    Q_PROPERTY(quint8 ChannelType_8 READ getChannelType_8 WRITE setChannelType_8 NOTIFY ChannelType_8Changed);
    Q_PROPERTY(quint8 ChannelType_9 READ getChannelType_9 WRITE setChannelType_9 NOTIFY ChannelType_9Changed);
    Q_PROPERTY(quint8 ChannelType_10 READ getChannelType_10 WRITE setChannelType_10 NOTIFY ChannelType_10Changed);
    Q_PROPERTY(quint8 ChannelType_11 READ getChannelType_11 WRITE setChannelType_11 NOTIFY ChannelType_11Changed);
    Q_PROPERTY(quint8 ChannelAddr_0 READ getChannelAddr_0 WRITE setChannelAddr_0 NOTIFY ChannelAddr_0Changed);
    Q_PROPERTY(quint8 ChannelAddr_1 READ getChannelAddr_1 WRITE setChannelAddr_1 NOTIFY ChannelAddr_1Changed);
    Q_PROPERTY(quint8 ChannelAddr_2 READ getChannelAddr_2 WRITE setChannelAddr_2 NOTIFY ChannelAddr_2Changed);
    Q_PROPERTY(quint8 ChannelAddr_3 READ getChannelAddr_3 WRITE setChannelAddr_3 NOTIFY ChannelAddr_3Changed);
    Q_PROPERTY(quint8 ChannelAddr_4 READ getChannelAddr_4 WRITE setChannelAddr_4 NOTIFY ChannelAddr_4Changed);
    Q_PROPERTY(quint8 ChannelAddr_5 READ getChannelAddr_5 WRITE setChannelAddr_5 NOTIFY ChannelAddr_5Changed);
    Q_PROPERTY(quint8 ChannelAddr_6 READ getChannelAddr_6 WRITE setChannelAddr_6 NOTIFY ChannelAddr_6Changed);
    Q_PROPERTY(quint8 ChannelAddr_7 READ getChannelAddr_7 WRITE setChannelAddr_7 NOTIFY ChannelAddr_7Changed);
    Q_PROPERTY(quint8 ChannelAddr_8 READ getChannelAddr_8 WRITE setChannelAddr_8 NOTIFY ChannelAddr_8Changed);
    Q_PROPERTY(quint8 ChannelAddr_9 READ getChannelAddr_9 WRITE setChannelAddr_9 NOTIFY ChannelAddr_9Changed);
    Q_PROPERTY(quint8 ChannelAddr_10 READ getChannelAddr_10 WRITE setChannelAddr_10 NOTIFY ChannelAddr_10Changed);
    Q_PROPERTY(quint8 ChannelAddr_11 READ getChannelAddr_11 WRITE setChannelAddr_11 NOTIFY ChannelAddr_11Changed);
    Q_PROPERTY(quint8 MotorsSpinWhileArmed READ getMotorsSpinWhileArmed WRITE setMotorsSpinWhileArmed NOTIFY MotorsSpinWhileArmedChanged);
    Q_PROPERTY(quint8 LowThrottleZeroAxis_Roll READ getLowThrottleZeroAxis_Roll WRITE setLowThrottleZeroAxis_Roll NOTIFY LowThrottleZeroAxis_RollChanged);
    Q_PROPERTY(quint8 LowThrottleZeroAxis_Pitch READ getLowThrottleZeroAxis_Pitch WRITE setLowThrottleZeroAxis_Pitch NOTIFY LowThrottleZeroAxis_PitchChanged);
    Q_PROPERTY(quint8 LowThrottleZeroAxis_Yaw READ getLowThrottleZeroAxis_Yaw WRITE setLowThrottleZeroAxis_Yaw NOTIFY LowThrottleZeroAxis_YawChanged);


public:
    // Field structure
    typedef struct {
        quint16 BankUpdateFreq[6];
        qint16 ChannelMax[12];
        qint16 ChannelNeutral[12];
        qint16 ChannelMin[12];
        quint8 BankMode[6];
        quint8 ChannelType[12];
        quint8 ChannelAddr[12];
        quint8 MotorsSpinWhileArmed;
        quint8 LowThrottleZeroAxis[3];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field BankUpdateFreq information
    /* Number of elements for field BankUpdateFreq */
    static const quint32 BANKUPDATEFREQ_NUMELEM = 6;
    // Field ChannelMax information
    /* Number of elements for field ChannelMax */
    static const quint32 CHANNELMAX_NUMELEM = 12;
    // Field ChannelNeutral information
    /* Number of elements for field ChannelNeutral */
    static const quint32 CHANNELNEUTRAL_NUMELEM = 12;
    // Field ChannelMin information
    /* Number of elements for field ChannelMin */
    static const quint32 CHANNELMIN_NUMELEM = 12;
    // Field BankMode information
    /* Enumeration options for field BankMode */
    typedef enum { BANKMODE_PWM=0, BANKMODE_PWMSYNC=1, BANKMODE_ONESHOT125=2 } BankModeOptions;
    /* Number of elements for field BankMode */
    static const quint32 BANKMODE_NUMELEM = 6;
    // Field ChannelType information
    /* Enumeration options for field ChannelType */
    typedef enum { CHANNELTYPE_PWM=0, CHANNELTYPE_MK=1, CHANNELTYPE_ASTEC4=2, CHANNELTYPE_PWMALARMBUZZER=3, CHANNELTYPE_ARMINGLED=4, CHANNELTYPE_INFOLED=5 } ChannelTypeOptions;
    /* Number of elements for field ChannelType */
    static const quint32 CHANNELTYPE_NUMELEM = 12;
    // Field ChannelAddr information
    /* Number of elements for field ChannelAddr */
    static const quint32 CHANNELADDR_NUMELEM = 12;
    // Field MotorsSpinWhileArmed information
    /* Enumeration options for field MotorsSpinWhileArmed */
    typedef enum { MOTORSSPINWHILEARMED_FALSE=0, MOTORSSPINWHILEARMED_TRUE=1 } MotorsSpinWhileArmedOptions;
    // Field LowThrottleZeroAxis information
    /* Enumeration options for field LowThrottleZeroAxis */
    typedef enum { LOWTHROTTLEZEROAXIS_FALSE=0, LOWTHROTTLEZEROAXIS_TRUE=1 } LowThrottleZeroAxisOptions;
    /* Array element names for field LowThrottleZeroAxis */
    typedef enum { LOWTHROTTLEZEROAXIS_ROLL=0, LOWTHROTTLEZEROAXIS_PITCH=1, LOWTHROTTLEZEROAXIS_YAW=2 } LowThrottleZeroAxisElem;
    /* Number of elements for field LowThrottleZeroAxis */
    static const quint32 LOWTHROTTLEZEROAXIS_NUMELEM = 3;

  
    // Constants
    static const quint32 OBJID = 0xD2AD60A2;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    ActuatorSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static ActuatorSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint16 getBankUpdateFreq(quint32 index) const;
    Q_INVOKABLE quint16 getBankUpdateFreq_0() const;
    Q_INVOKABLE quint16 getBankUpdateFreq_1() const;
    Q_INVOKABLE quint16 getBankUpdateFreq_2() const;
    Q_INVOKABLE quint16 getBankUpdateFreq_3() const;
    Q_INVOKABLE quint16 getBankUpdateFreq_4() const;
    Q_INVOKABLE quint16 getBankUpdateFreq_5() const;
    Q_INVOKABLE qint16 getChannelMax(quint32 index) const;
    Q_INVOKABLE qint16 getChannelMax_0() const;
    Q_INVOKABLE qint16 getChannelMax_1() const;
    Q_INVOKABLE qint16 getChannelMax_2() const;
    Q_INVOKABLE qint16 getChannelMax_3() const;
    Q_INVOKABLE qint16 getChannelMax_4() const;
    Q_INVOKABLE qint16 getChannelMax_5() const;
    Q_INVOKABLE qint16 getChannelMax_6() const;
    Q_INVOKABLE qint16 getChannelMax_7() const;
    Q_INVOKABLE qint16 getChannelMax_8() const;
    Q_INVOKABLE qint16 getChannelMax_9() const;
    Q_INVOKABLE qint16 getChannelMax_10() const;
    Q_INVOKABLE qint16 getChannelMax_11() const;
    Q_INVOKABLE qint16 getChannelNeutral(quint32 index) const;
    Q_INVOKABLE qint16 getChannelNeutral_0() const;
    Q_INVOKABLE qint16 getChannelNeutral_1() const;
    Q_INVOKABLE qint16 getChannelNeutral_2() const;
    Q_INVOKABLE qint16 getChannelNeutral_3() const;
    Q_INVOKABLE qint16 getChannelNeutral_4() const;
    Q_INVOKABLE qint16 getChannelNeutral_5() const;
    Q_INVOKABLE qint16 getChannelNeutral_6() const;
    Q_INVOKABLE qint16 getChannelNeutral_7() const;
    Q_INVOKABLE qint16 getChannelNeutral_8() const;
    Q_INVOKABLE qint16 getChannelNeutral_9() const;
    Q_INVOKABLE qint16 getChannelNeutral_10() const;
    Q_INVOKABLE qint16 getChannelNeutral_11() const;
    Q_INVOKABLE qint16 getChannelMin(quint32 index) const;
    Q_INVOKABLE qint16 getChannelMin_0() const;
    Q_INVOKABLE qint16 getChannelMin_1() const;
    Q_INVOKABLE qint16 getChannelMin_2() const;
    Q_INVOKABLE qint16 getChannelMin_3() const;
    Q_INVOKABLE qint16 getChannelMin_4() const;
    Q_INVOKABLE qint16 getChannelMin_5() const;
    Q_INVOKABLE qint16 getChannelMin_6() const;
    Q_INVOKABLE qint16 getChannelMin_7() const;
    Q_INVOKABLE qint16 getChannelMin_8() const;
    Q_INVOKABLE qint16 getChannelMin_9() const;
    Q_INVOKABLE qint16 getChannelMin_10() const;
    Q_INVOKABLE qint16 getChannelMin_11() const;
    Q_INVOKABLE quint8 getBankMode(quint32 index) const;
    Q_INVOKABLE quint8 getBankMode_0() const;
    Q_INVOKABLE quint8 getBankMode_1() const;
    Q_INVOKABLE quint8 getBankMode_2() const;
    Q_INVOKABLE quint8 getBankMode_3() const;
    Q_INVOKABLE quint8 getBankMode_4() const;
    Q_INVOKABLE quint8 getBankMode_5() const;
    Q_INVOKABLE quint8 getChannelType(quint32 index) const;
    Q_INVOKABLE quint8 getChannelType_0() const;
    Q_INVOKABLE quint8 getChannelType_1() const;
    Q_INVOKABLE quint8 getChannelType_2() const;
    Q_INVOKABLE quint8 getChannelType_3() const;
    Q_INVOKABLE quint8 getChannelType_4() const;
    Q_INVOKABLE quint8 getChannelType_5() const;
    Q_INVOKABLE quint8 getChannelType_6() const;
    Q_INVOKABLE quint8 getChannelType_7() const;
    Q_INVOKABLE quint8 getChannelType_8() const;
    Q_INVOKABLE quint8 getChannelType_9() const;
    Q_INVOKABLE quint8 getChannelType_10() const;
    Q_INVOKABLE quint8 getChannelType_11() const;
    Q_INVOKABLE quint8 getChannelAddr(quint32 index) const;
    Q_INVOKABLE quint8 getChannelAddr_0() const;
    Q_INVOKABLE quint8 getChannelAddr_1() const;
    Q_INVOKABLE quint8 getChannelAddr_2() const;
    Q_INVOKABLE quint8 getChannelAddr_3() const;
    Q_INVOKABLE quint8 getChannelAddr_4() const;
    Q_INVOKABLE quint8 getChannelAddr_5() const;
    Q_INVOKABLE quint8 getChannelAddr_6() const;
    Q_INVOKABLE quint8 getChannelAddr_7() const;
    Q_INVOKABLE quint8 getChannelAddr_8() const;
    Q_INVOKABLE quint8 getChannelAddr_9() const;
    Q_INVOKABLE quint8 getChannelAddr_10() const;
    Q_INVOKABLE quint8 getChannelAddr_11() const;
    Q_INVOKABLE quint8 getMotorsSpinWhileArmed() const;
    Q_INVOKABLE quint8 getLowThrottleZeroAxis(quint32 index) const;
    Q_INVOKABLE quint8 getLowThrottleZeroAxis_Roll() const;
    Q_INVOKABLE quint8 getLowThrottleZeroAxis_Pitch() const;
    Q_INVOKABLE quint8 getLowThrottleZeroAxis_Yaw() const;


public slots:
    void setBankUpdateFreq(quint32 index, quint16 value);
    void setBankUpdateFreq_0(quint16 value);
    void setBankUpdateFreq_1(quint16 value);
    void setBankUpdateFreq_2(quint16 value);
    void setBankUpdateFreq_3(quint16 value);
    void setBankUpdateFreq_4(quint16 value);
    void setBankUpdateFreq_5(quint16 value);
    void setChannelMax(quint32 index, qint16 value);
    void setChannelMax_0(qint16 value);
    void setChannelMax_1(qint16 value);
    void setChannelMax_2(qint16 value);
    void setChannelMax_3(qint16 value);
    void setChannelMax_4(qint16 value);
    void setChannelMax_5(qint16 value);
    void setChannelMax_6(qint16 value);
    void setChannelMax_7(qint16 value);
    void setChannelMax_8(qint16 value);
    void setChannelMax_9(qint16 value);
    void setChannelMax_10(qint16 value);
    void setChannelMax_11(qint16 value);
    void setChannelNeutral(quint32 index, qint16 value);
    void setChannelNeutral_0(qint16 value);
    void setChannelNeutral_1(qint16 value);
    void setChannelNeutral_2(qint16 value);
    void setChannelNeutral_3(qint16 value);
    void setChannelNeutral_4(qint16 value);
    void setChannelNeutral_5(qint16 value);
    void setChannelNeutral_6(qint16 value);
    void setChannelNeutral_7(qint16 value);
    void setChannelNeutral_8(qint16 value);
    void setChannelNeutral_9(qint16 value);
    void setChannelNeutral_10(qint16 value);
    void setChannelNeutral_11(qint16 value);
    void setChannelMin(quint32 index, qint16 value);
    void setChannelMin_0(qint16 value);
    void setChannelMin_1(qint16 value);
    void setChannelMin_2(qint16 value);
    void setChannelMin_3(qint16 value);
    void setChannelMin_4(qint16 value);
    void setChannelMin_5(qint16 value);
    void setChannelMin_6(qint16 value);
    void setChannelMin_7(qint16 value);
    void setChannelMin_8(qint16 value);
    void setChannelMin_9(qint16 value);
    void setChannelMin_10(qint16 value);
    void setChannelMin_11(qint16 value);
    void setBankMode(quint32 index, quint8 value);
    void setBankMode_0(quint8 value);
    void setBankMode_1(quint8 value);
    void setBankMode_2(quint8 value);
    void setBankMode_3(quint8 value);
    void setBankMode_4(quint8 value);
    void setBankMode_5(quint8 value);
    void setChannelType(quint32 index, quint8 value);
    void setChannelType_0(quint8 value);
    void setChannelType_1(quint8 value);
    void setChannelType_2(quint8 value);
    void setChannelType_3(quint8 value);
    void setChannelType_4(quint8 value);
    void setChannelType_5(quint8 value);
    void setChannelType_6(quint8 value);
    void setChannelType_7(quint8 value);
    void setChannelType_8(quint8 value);
    void setChannelType_9(quint8 value);
    void setChannelType_10(quint8 value);
    void setChannelType_11(quint8 value);
    void setChannelAddr(quint32 index, quint8 value);
    void setChannelAddr_0(quint8 value);
    void setChannelAddr_1(quint8 value);
    void setChannelAddr_2(quint8 value);
    void setChannelAddr_3(quint8 value);
    void setChannelAddr_4(quint8 value);
    void setChannelAddr_5(quint8 value);
    void setChannelAddr_6(quint8 value);
    void setChannelAddr_7(quint8 value);
    void setChannelAddr_8(quint8 value);
    void setChannelAddr_9(quint8 value);
    void setChannelAddr_10(quint8 value);
    void setChannelAddr_11(quint8 value);
    void setMotorsSpinWhileArmed(quint8 value);
    void setLowThrottleZeroAxis(quint32 index, quint8 value);
    void setLowThrottleZeroAxis_Roll(quint8 value);
    void setLowThrottleZeroAxis_Pitch(quint8 value);
    void setLowThrottleZeroAxis_Yaw(quint8 value);


signals:
    void BankUpdateFreqChanged(quint32 index, quint16 value);
    void BankUpdateFreq_0Changed(quint16 value);
    void BankUpdateFreq_1Changed(quint16 value);
    void BankUpdateFreq_2Changed(quint16 value);
    void BankUpdateFreq_3Changed(quint16 value);
    void BankUpdateFreq_4Changed(quint16 value);
    void BankUpdateFreq_5Changed(quint16 value);
    void ChannelMaxChanged(quint32 index, qint16 value);
    void ChannelMax_0Changed(qint16 value);
    void ChannelMax_1Changed(qint16 value);
    void ChannelMax_2Changed(qint16 value);
    void ChannelMax_3Changed(qint16 value);
    void ChannelMax_4Changed(qint16 value);
    void ChannelMax_5Changed(qint16 value);
    void ChannelMax_6Changed(qint16 value);
    void ChannelMax_7Changed(qint16 value);
    void ChannelMax_8Changed(qint16 value);
    void ChannelMax_9Changed(qint16 value);
    void ChannelMax_10Changed(qint16 value);
    void ChannelMax_11Changed(qint16 value);
    void ChannelNeutralChanged(quint32 index, qint16 value);
    void ChannelNeutral_0Changed(qint16 value);
    void ChannelNeutral_1Changed(qint16 value);
    void ChannelNeutral_2Changed(qint16 value);
    void ChannelNeutral_3Changed(qint16 value);
    void ChannelNeutral_4Changed(qint16 value);
    void ChannelNeutral_5Changed(qint16 value);
    void ChannelNeutral_6Changed(qint16 value);
    void ChannelNeutral_7Changed(qint16 value);
    void ChannelNeutral_8Changed(qint16 value);
    void ChannelNeutral_9Changed(qint16 value);
    void ChannelNeutral_10Changed(qint16 value);
    void ChannelNeutral_11Changed(qint16 value);
    void ChannelMinChanged(quint32 index, qint16 value);
    void ChannelMin_0Changed(qint16 value);
    void ChannelMin_1Changed(qint16 value);
    void ChannelMin_2Changed(qint16 value);
    void ChannelMin_3Changed(qint16 value);
    void ChannelMin_4Changed(qint16 value);
    void ChannelMin_5Changed(qint16 value);
    void ChannelMin_6Changed(qint16 value);
    void ChannelMin_7Changed(qint16 value);
    void ChannelMin_8Changed(qint16 value);
    void ChannelMin_9Changed(qint16 value);
    void ChannelMin_10Changed(qint16 value);
    void ChannelMin_11Changed(qint16 value);
    void BankModeChanged(quint32 index, quint8 value);
    void BankMode_0Changed(quint8 value);
    void BankMode_1Changed(quint8 value);
    void BankMode_2Changed(quint8 value);
    void BankMode_3Changed(quint8 value);
    void BankMode_4Changed(quint8 value);
    void BankMode_5Changed(quint8 value);
    void ChannelTypeChanged(quint32 index, quint8 value);
    void ChannelType_0Changed(quint8 value);
    void ChannelType_1Changed(quint8 value);
    void ChannelType_2Changed(quint8 value);
    void ChannelType_3Changed(quint8 value);
    void ChannelType_4Changed(quint8 value);
    void ChannelType_5Changed(quint8 value);
    void ChannelType_6Changed(quint8 value);
    void ChannelType_7Changed(quint8 value);
    void ChannelType_8Changed(quint8 value);
    void ChannelType_9Changed(quint8 value);
    void ChannelType_10Changed(quint8 value);
    void ChannelType_11Changed(quint8 value);
    void ChannelAddrChanged(quint32 index, quint8 value);
    void ChannelAddr_0Changed(quint8 value);
    void ChannelAddr_1Changed(quint8 value);
    void ChannelAddr_2Changed(quint8 value);
    void ChannelAddr_3Changed(quint8 value);
    void ChannelAddr_4Changed(quint8 value);
    void ChannelAddr_5Changed(quint8 value);
    void ChannelAddr_6Changed(quint8 value);
    void ChannelAddr_7Changed(quint8 value);
    void ChannelAddr_8Changed(quint8 value);
    void ChannelAddr_9Changed(quint8 value);
    void ChannelAddr_10Changed(quint8 value);
    void ChannelAddr_11Changed(quint8 value);
    void MotorsSpinWhileArmedChanged(quint8 value);
    void LowThrottleZeroAxisChanged(quint32 index, quint8 value);
    void LowThrottleZeroAxis_RollChanged(quint8 value);
    void LowThrottleZeroAxis_PitchChanged(quint8 value);
    void LowThrottleZeroAxis_YawChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // ACTUATORSETTINGS_H
