/**
 ******************************************************************************
 *
 * @file       txpidsettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: txpidsettings.xml. 
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
#ifndef TXPIDSETTINGS_H
#define TXPIDSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT TxPIDSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float ThrottleRange_Min READ getThrottleRange_Min WRITE setThrottleRange_Min NOTIFY ThrottleRange_MinChanged);
    Q_PROPERTY(float ThrottleRange_Max READ getThrottleRange_Max WRITE setThrottleRange_Max NOTIFY ThrottleRange_MaxChanged);
    Q_PROPERTY(float MinPID_Instance1 READ getMinPID_Instance1 WRITE setMinPID_Instance1 NOTIFY MinPID_Instance1Changed);
    Q_PROPERTY(float MinPID_Instance2 READ getMinPID_Instance2 WRITE setMinPID_Instance2 NOTIFY MinPID_Instance2Changed);
    Q_PROPERTY(float MinPID_Instance3 READ getMinPID_Instance3 WRITE setMinPID_Instance3 NOTIFY MinPID_Instance3Changed);
    Q_PROPERTY(float MaxPID_Instance1 READ getMaxPID_Instance1 WRITE setMaxPID_Instance1 NOTIFY MaxPID_Instance1Changed);
    Q_PROPERTY(float MaxPID_Instance2 READ getMaxPID_Instance2 WRITE setMaxPID_Instance2 NOTIFY MaxPID_Instance2Changed);
    Q_PROPERTY(float MaxPID_Instance3 READ getMaxPID_Instance3 WRITE setMaxPID_Instance3 NOTIFY MaxPID_Instance3Changed);
    Q_PROPERTY(quint8 UpdateMode READ getUpdateMode WRITE setUpdateMode NOTIFY UpdateModeChanged);
    Q_PROPERTY(quint8 BankNumber READ getBankNumber WRITE setBankNumber NOTIFY BankNumberChanged);
    Q_PROPERTY(quint8 Inputs_Instance1 READ getInputs_Instance1 WRITE setInputs_Instance1 NOTIFY Inputs_Instance1Changed);
    Q_PROPERTY(quint8 Inputs_Instance2 READ getInputs_Instance2 WRITE setInputs_Instance2 NOTIFY Inputs_Instance2Changed);
    Q_PROPERTY(quint8 Inputs_Instance3 READ getInputs_Instance3 WRITE setInputs_Instance3 NOTIFY Inputs_Instance3Changed);
    Q_PROPERTY(quint8 PIDs_Instance1 READ getPIDs_Instance1 WRITE setPIDs_Instance1 NOTIFY PIDs_Instance1Changed);
    Q_PROPERTY(quint8 PIDs_Instance2 READ getPIDs_Instance2 WRITE setPIDs_Instance2 NOTIFY PIDs_Instance2Changed);
    Q_PROPERTY(quint8 PIDs_Instance3 READ getPIDs_Instance3 WRITE setPIDs_Instance3 NOTIFY PIDs_Instance3Changed);


public:
    // Field structure
    typedef struct {
        float ThrottleRange[2];
        float MinPID[3];
        float MaxPID[3];
        quint8 UpdateMode;
        quint8 BankNumber;
        quint8 Inputs[3];
        quint8 PIDs[3];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field ThrottleRange information
    /* Array element names for field ThrottleRange */
    typedef enum { THROTTLERANGE_MIN=0, THROTTLERANGE_MAX=1 } ThrottleRangeElem;
    /* Number of elements for field ThrottleRange */
    static const quint32 THROTTLERANGE_NUMELEM = 2;
    // Field MinPID information
    /* Array element names for field MinPID */
    typedef enum { MINPID_INSTANCE1=0, MINPID_INSTANCE2=1, MINPID_INSTANCE3=2 } MinPIDElem;
    /* Number of elements for field MinPID */
    static const quint32 MINPID_NUMELEM = 3;
    // Field MaxPID information
    /* Array element names for field MaxPID */
    typedef enum { MAXPID_INSTANCE1=0, MAXPID_INSTANCE2=1, MAXPID_INSTANCE3=2 } MaxPIDElem;
    /* Number of elements for field MaxPID */
    static const quint32 MAXPID_NUMELEM = 3;
    // Field UpdateMode information
    /* Enumeration options for field UpdateMode */
    typedef enum { UPDATEMODE_NEVER=0, UPDATEMODE_WHENARMED=1, UPDATEMODE_ALWAYS=2 } UpdateModeOptions;
    // Field BankNumber information
    /* Enumeration options for field BankNumber */
    typedef enum { BANKNUMBER_BANK1=0, BANKNUMBER_BANK2=1, BANKNUMBER_BANK3=2 } BankNumberOptions;
    // Field Inputs information
    /* Enumeration options for field Inputs */
    typedef enum { INPUTS_THROTTLE=0, INPUTS_ACCESSORY0=1, INPUTS_ACCESSORY1=2, INPUTS_ACCESSORY2=3, INPUTS_ACCESSORY3=4, INPUTS_ACCESSORY4=5, INPUTS_ACCESSORY5=6 } InputsOptions;
    /* Array element names for field Inputs */
    typedef enum { INPUTS_INSTANCE1=0, INPUTS_INSTANCE2=1, INPUTS_INSTANCE3=2 } InputsElem;
    /* Number of elements for field Inputs */
    static const quint32 INPUTS_NUMELEM = 3;
    // Field PIDs information
    /* Enumeration options for field PIDs */
    typedef enum { PIDS_DISABLED=0, PIDS_ROLLRATEKP=1, PIDS_ROLLRATEKI=2, PIDS_ROLLRATEKD=3, PIDS_ROLLRATEILIMIT=4, PIDS_ROLLRATERESP=5, PIDS_PITCHRATEKP=6, PIDS_PITCHRATEKI=7, PIDS_PITCHRATEKD=8, PIDS_PITCHRATEILIMIT=9, PIDS_PITCHRATERESP=10, PIDS_ROLLPITCHRATEKP=11, PIDS_ROLLPITCHRATEKI=12, PIDS_ROLLPITCHRATEKD=13, PIDS_ROLLPITCHRATEILIMIT=14, PIDS_ROLLPITCHRATERESP=15, PIDS_YAWRATEKP=16, PIDS_YAWRATEKI=17, PIDS_YAWRATEKD=18, PIDS_YAWRATEILIMIT=19, PIDS_YAWRATERESP=20, PIDS_ROLLATTITUDEKP=21, PIDS_ROLLATTITUDEKI=22, PIDS_ROLLATTITUDEILIMIT=23, PIDS_ROLLATTITUDERESP=24, PIDS_PITCHATTITUDEKP=25, PIDS_PITCHATTITUDEKI=26, PIDS_PITCHATTITUDEILIMIT=27, PIDS_PITCHATTITUDERESP=28, PIDS_ROLLPITCHATTITUDEKP=29, PIDS_ROLLPITCHATTITUDEKI=30, PIDS_ROLLPITCHATTITUDEILIMIT=31, PIDS_ROLLPITCHATTITUDERESP=32, PIDS_YAWATTITUDEKP=33, PIDS_YAWATTITUDEKI=34, PIDS_YAWATTITUDEILIMIT=35, PIDS_YAWATTITUDERESP=36, PIDS_ROLLEXPO=37, PIDS_PITCHEXPO=38, PIDS_ROLLPITCHEXPO=39, PIDS_YAWEXPO=40, PIDS_GYROTAU=41, PIDS_ACROPLUSFACTOR=42 } PIDsOptions;
    /* Array element names for field PIDs */
    typedef enum { PIDS_INSTANCE1=0, PIDS_INSTANCE2=1, PIDS_INSTANCE3=2 } PIDsElem;
    /* Number of elements for field PIDs */
    static const quint32 PIDS_NUMELEM = 3;

  
    // Constants
    static const quint32 OBJID = 0x857B51F2;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    TxPIDSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static TxPIDSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getThrottleRange(quint32 index) const;
    Q_INVOKABLE float getThrottleRange_Min() const;
    Q_INVOKABLE float getThrottleRange_Max() const;
    Q_INVOKABLE float getMinPID(quint32 index) const;
    Q_INVOKABLE float getMinPID_Instance1() const;
    Q_INVOKABLE float getMinPID_Instance2() const;
    Q_INVOKABLE float getMinPID_Instance3() const;
    Q_INVOKABLE float getMaxPID(quint32 index) const;
    Q_INVOKABLE float getMaxPID_Instance1() const;
    Q_INVOKABLE float getMaxPID_Instance2() const;
    Q_INVOKABLE float getMaxPID_Instance3() const;
    Q_INVOKABLE quint8 getUpdateMode() const;
    Q_INVOKABLE quint8 getBankNumber() const;
    Q_INVOKABLE quint8 getInputs(quint32 index) const;
    Q_INVOKABLE quint8 getInputs_Instance1() const;
    Q_INVOKABLE quint8 getInputs_Instance2() const;
    Q_INVOKABLE quint8 getInputs_Instance3() const;
    Q_INVOKABLE quint8 getPIDs(quint32 index) const;
    Q_INVOKABLE quint8 getPIDs_Instance1() const;
    Q_INVOKABLE quint8 getPIDs_Instance2() const;
    Q_INVOKABLE quint8 getPIDs_Instance3() const;


public slots:
    void setThrottleRange(quint32 index, float value);
    void setThrottleRange_Min(float value);
    void setThrottleRange_Max(float value);
    void setMinPID(quint32 index, float value);
    void setMinPID_Instance1(float value);
    void setMinPID_Instance2(float value);
    void setMinPID_Instance3(float value);
    void setMaxPID(quint32 index, float value);
    void setMaxPID_Instance1(float value);
    void setMaxPID_Instance2(float value);
    void setMaxPID_Instance3(float value);
    void setUpdateMode(quint8 value);
    void setBankNumber(quint8 value);
    void setInputs(quint32 index, quint8 value);
    void setInputs_Instance1(quint8 value);
    void setInputs_Instance2(quint8 value);
    void setInputs_Instance3(quint8 value);
    void setPIDs(quint32 index, quint8 value);
    void setPIDs_Instance1(quint8 value);
    void setPIDs_Instance2(quint8 value);
    void setPIDs_Instance3(quint8 value);


signals:
    void ThrottleRangeChanged(quint32 index, float value);
    void ThrottleRange_MinChanged(float value);
    void ThrottleRange_MaxChanged(float value);
    void MinPIDChanged(quint32 index, float value);
    void MinPID_Instance1Changed(float value);
    void MinPID_Instance2Changed(float value);
    void MinPID_Instance3Changed(float value);
    void MaxPIDChanged(quint32 index, float value);
    void MaxPID_Instance1Changed(float value);
    void MaxPID_Instance2Changed(float value);
    void MaxPID_Instance3Changed(float value);
    void UpdateModeChanged(quint8 value);
    void BankNumberChanged(quint8 value);
    void InputsChanged(quint32 index, quint8 value);
    void Inputs_Instance1Changed(quint8 value);
    void Inputs_Instance2Changed(quint8 value);
    void Inputs_Instance3Changed(quint8 value);
    void PIDsChanged(quint32 index, quint8 value);
    void PIDs_Instance1Changed(quint8 value);
    void PIDs_Instance2Changed(quint8 value);
    void PIDs_Instance3Changed(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // TXPIDSETTINGS_H
