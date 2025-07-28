/**
 ******************************************************************************
 *
 * @file       stabilizationsettingsbank1.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: stabilizationsettingsbank1.xml. 
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
#ifndef STABILIZATIONSETTINGSBANK1_H
#define STABILIZATIONSETTINGSBANK1_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT StabilizationSettingsBank1: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float ManualRate_Roll READ getManualRate_Roll WRITE setManualRate_Roll NOTIFY ManualRate_RollChanged);
    Q_PROPERTY(float ManualRate_Pitch READ getManualRate_Pitch WRITE setManualRate_Pitch NOTIFY ManualRate_PitchChanged);
    Q_PROPERTY(float ManualRate_Yaw READ getManualRate_Yaw WRITE setManualRate_Yaw NOTIFY ManualRate_YawChanged);
    Q_PROPERTY(float MaximumRate_Roll READ getMaximumRate_Roll WRITE setMaximumRate_Roll NOTIFY MaximumRate_RollChanged);
    Q_PROPERTY(float MaximumRate_Pitch READ getMaximumRate_Pitch WRITE setMaximumRate_Pitch NOTIFY MaximumRate_PitchChanged);
    Q_PROPERTY(float MaximumRate_Yaw READ getMaximumRate_Yaw WRITE setMaximumRate_Yaw NOTIFY MaximumRate_YawChanged);
    Q_PROPERTY(float RollRatePID_Kp READ getRollRatePID_Kp WRITE setRollRatePID_Kp NOTIFY RollRatePID_KpChanged);
    Q_PROPERTY(float RollRatePID_Ki READ getRollRatePID_Ki WRITE setRollRatePID_Ki NOTIFY RollRatePID_KiChanged);
    Q_PROPERTY(float RollRatePID_Kd READ getRollRatePID_Kd WRITE setRollRatePID_Kd NOTIFY RollRatePID_KdChanged);
    Q_PROPERTY(float RollRatePID_ILimit READ getRollRatePID_ILimit WRITE setRollRatePID_ILimit NOTIFY RollRatePID_ILimitChanged);
    Q_PROPERTY(float PitchRatePID_Kp READ getPitchRatePID_Kp WRITE setPitchRatePID_Kp NOTIFY PitchRatePID_KpChanged);
    Q_PROPERTY(float PitchRatePID_Ki READ getPitchRatePID_Ki WRITE setPitchRatePID_Ki NOTIFY PitchRatePID_KiChanged);
    Q_PROPERTY(float PitchRatePID_Kd READ getPitchRatePID_Kd WRITE setPitchRatePID_Kd NOTIFY PitchRatePID_KdChanged);
    Q_PROPERTY(float PitchRatePID_ILimit READ getPitchRatePID_ILimit WRITE setPitchRatePID_ILimit NOTIFY PitchRatePID_ILimitChanged);
    Q_PROPERTY(float YawRatePID_Kp READ getYawRatePID_Kp WRITE setYawRatePID_Kp NOTIFY YawRatePID_KpChanged);
    Q_PROPERTY(float YawRatePID_Ki READ getYawRatePID_Ki WRITE setYawRatePID_Ki NOTIFY YawRatePID_KiChanged);
    Q_PROPERTY(float YawRatePID_Kd READ getYawRatePID_Kd WRITE setYawRatePID_Kd NOTIFY YawRatePID_KdChanged);
    Q_PROPERTY(float YawRatePID_ILimit READ getYawRatePID_ILimit WRITE setYawRatePID_ILimit NOTIFY YawRatePID_ILimitChanged);
    Q_PROPERTY(float RollPI_Kp READ getRollPI_Kp WRITE setRollPI_Kp NOTIFY RollPI_KpChanged);
    Q_PROPERTY(float RollPI_Ki READ getRollPI_Ki WRITE setRollPI_Ki NOTIFY RollPI_KiChanged);
    Q_PROPERTY(float RollPI_ILimit READ getRollPI_ILimit WRITE setRollPI_ILimit NOTIFY RollPI_ILimitChanged);
    Q_PROPERTY(float PitchPI_Kp READ getPitchPI_Kp WRITE setPitchPI_Kp NOTIFY PitchPI_KpChanged);
    Q_PROPERTY(float PitchPI_Ki READ getPitchPI_Ki WRITE setPitchPI_Ki NOTIFY PitchPI_KiChanged);
    Q_PROPERTY(float PitchPI_ILimit READ getPitchPI_ILimit WRITE setPitchPI_ILimit NOTIFY PitchPI_ILimitChanged);
    Q_PROPERTY(float YawPI_Kp READ getYawPI_Kp WRITE setYawPI_Kp NOTIFY YawPI_KpChanged);
    Q_PROPERTY(float YawPI_Ki READ getYawPI_Ki WRITE setYawPI_Ki NOTIFY YawPI_KiChanged);
    Q_PROPERTY(float YawPI_ILimit READ getYawPI_ILimit WRITE setYawPI_ILimit NOTIFY YawPI_ILimitChanged);
    Q_PROPERTY(float AcroInsanityFactor READ getAcroInsanityFactor WRITE setAcroInsanityFactor NOTIFY AcroInsanityFactorChanged);
    Q_PROPERTY(float ThrustPIDScaleCurve_0 READ getThrustPIDScaleCurve_0 WRITE setThrustPIDScaleCurve_0 NOTIFY ThrustPIDScaleCurve_0Changed);
    Q_PROPERTY(float ThrustPIDScaleCurve_25 READ getThrustPIDScaleCurve_25 WRITE setThrustPIDScaleCurve_25 NOTIFY ThrustPIDScaleCurve_25Changed);
    Q_PROPERTY(float ThrustPIDScaleCurve_50 READ getThrustPIDScaleCurve_50 WRITE setThrustPIDScaleCurve_50 NOTIFY ThrustPIDScaleCurve_50Changed);
    Q_PROPERTY(float ThrustPIDScaleCurve_75 READ getThrustPIDScaleCurve_75 WRITE setThrustPIDScaleCurve_75 NOTIFY ThrustPIDScaleCurve_75Changed);
    Q_PROPERTY(float ThrustPIDScaleCurve_100 READ getThrustPIDScaleCurve_100 WRITE setThrustPIDScaleCurve_100 NOTIFY ThrustPIDScaleCurve_100Changed);
    Q_PROPERTY(quint8 RollMax READ getRollMax WRITE setRollMax NOTIFY RollMaxChanged);
    Q_PROPERTY(quint8 PitchMax READ getPitchMax WRITE setPitchMax NOTIFY PitchMaxChanged);
    Q_PROPERTY(quint8 YawMax READ getYawMax WRITE setYawMax NOTIFY YawMaxChanged);
    Q_PROPERTY(qint8 StickExpo_Roll READ getStickExpo_Roll WRITE setStickExpo_Roll NOTIFY StickExpo_RollChanged);
    Q_PROPERTY(qint8 StickExpo_Pitch READ getStickExpo_Pitch WRITE setStickExpo_Pitch NOTIFY StickExpo_PitchChanged);
    Q_PROPERTY(qint8 StickExpo_Yaw READ getStickExpo_Yaw WRITE setStickExpo_Yaw NOTIFY StickExpo_YawChanged);
    Q_PROPERTY(quint8 EnablePiroComp READ getEnablePiroComp WRITE setEnablePiroComp NOTIFY EnablePiroCompChanged);
    Q_PROPERTY(quint8 EnableThrustPIDScaling READ getEnableThrustPIDScaling WRITE setEnableThrustPIDScaling NOTIFY EnableThrustPIDScalingChanged);
    Q_PROPERTY(quint8 ThrustPIDScaleSource READ getThrustPIDScaleSource WRITE setThrustPIDScaleSource NOTIFY ThrustPIDScaleSourceChanged);
    Q_PROPERTY(quint8 ThrustPIDScaleTarget READ getThrustPIDScaleTarget WRITE setThrustPIDScaleTarget NOTIFY ThrustPIDScaleTargetChanged);
    Q_PROPERTY(quint8 ThrustPIDScaleAxes READ getThrustPIDScaleAxes WRITE setThrustPIDScaleAxes NOTIFY ThrustPIDScaleAxesChanged);


public:
    // Field structure
    typedef struct {
        float ManualRate[3];
        float MaximumRate[3];
        float RollRatePID[4];
        float PitchRatePID[4];
        float YawRatePID[4];
        float RollPI[3];
        float PitchPI[3];
        float YawPI[3];
        float AcroInsanityFactor;
        float ThrustPIDScaleCurve[5];
        quint8 RollMax;
        quint8 PitchMax;
        quint8 YawMax;
        qint8 StickExpo[3];
        quint8 EnablePiroComp;
        quint8 EnableThrustPIDScaling;
        quint8 ThrustPIDScaleSource;
        quint8 ThrustPIDScaleTarget;
        quint8 ThrustPIDScaleAxes;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field ManualRate information
    /* Array element names for field ManualRate */
    typedef enum { MANUALRATE_ROLL=0, MANUALRATE_PITCH=1, MANUALRATE_YAW=2 } ManualRateElem;
    /* Number of elements for field ManualRate */
    static const quint32 MANUALRATE_NUMELEM = 3;
    // Field MaximumRate information
    /* Array element names for field MaximumRate */
    typedef enum { MAXIMUMRATE_ROLL=0, MAXIMUMRATE_PITCH=1, MAXIMUMRATE_YAW=2 } MaximumRateElem;
    /* Number of elements for field MaximumRate */
    static const quint32 MAXIMUMRATE_NUMELEM = 3;
    // Field RollRatePID information
    /* Array element names for field RollRatePID */
    typedef enum { ROLLRATEPID_KP=0, ROLLRATEPID_KI=1, ROLLRATEPID_KD=2, ROLLRATEPID_ILIMIT=3 } RollRatePIDElem;
    /* Number of elements for field RollRatePID */
    static const quint32 ROLLRATEPID_NUMELEM = 4;
    // Field PitchRatePID information
    /* Array element names for field PitchRatePID */
    typedef enum { PITCHRATEPID_KP=0, PITCHRATEPID_KI=1, PITCHRATEPID_KD=2, PITCHRATEPID_ILIMIT=3 } PitchRatePIDElem;
    /* Number of elements for field PitchRatePID */
    static const quint32 PITCHRATEPID_NUMELEM = 4;
    // Field YawRatePID information
    /* Array element names for field YawRatePID */
    typedef enum { YAWRATEPID_KP=0, YAWRATEPID_KI=1, YAWRATEPID_KD=2, YAWRATEPID_ILIMIT=3 } YawRatePIDElem;
    /* Number of elements for field YawRatePID */
    static const quint32 YAWRATEPID_NUMELEM = 4;
    // Field RollPI information
    /* Array element names for field RollPI */
    typedef enum { ROLLPI_KP=0, ROLLPI_KI=1, ROLLPI_ILIMIT=2 } RollPIElem;
    /* Number of elements for field RollPI */
    static const quint32 ROLLPI_NUMELEM = 3;
    // Field PitchPI information
    /* Array element names for field PitchPI */
    typedef enum { PITCHPI_KP=0, PITCHPI_KI=1, PITCHPI_ILIMIT=2 } PitchPIElem;
    /* Number of elements for field PitchPI */
    static const quint32 PITCHPI_NUMELEM = 3;
    // Field YawPI information
    /* Array element names for field YawPI */
    typedef enum { YAWPI_KP=0, YAWPI_KI=1, YAWPI_ILIMIT=2 } YawPIElem;
    /* Number of elements for field YawPI */
    static const quint32 YAWPI_NUMELEM = 3;
    // Field AcroInsanityFactor information
    // Field ThrustPIDScaleCurve information
    /* Array element names for field ThrustPIDScaleCurve */
    typedef enum { THRUSTPIDSCALECURVE_0=0, THRUSTPIDSCALECURVE_25=1, THRUSTPIDSCALECURVE_50=2, THRUSTPIDSCALECURVE_75=3, THRUSTPIDSCALECURVE_100=4 } ThrustPIDScaleCurveElem;
    /* Number of elements for field ThrustPIDScaleCurve */
    static const quint32 THRUSTPIDSCALECURVE_NUMELEM = 5;
    // Field RollMax information
    // Field PitchMax information
    // Field YawMax information
    // Field StickExpo information
    /* Array element names for field StickExpo */
    typedef enum { STICKEXPO_ROLL=0, STICKEXPO_PITCH=1, STICKEXPO_YAW=2 } StickExpoElem;
    /* Number of elements for field StickExpo */
    static const quint32 STICKEXPO_NUMELEM = 3;
    // Field EnablePiroComp information
    /* Enumeration options for field EnablePiroComp */
    typedef enum { ENABLEPIROCOMP_FALSE=0, ENABLEPIROCOMP_TRUE=1 } EnablePiroCompOptions;
    // Field EnableThrustPIDScaling information
    /* Enumeration options for field EnableThrustPIDScaling */
    typedef enum { ENABLETHRUSTPIDSCALING_FALSE=0, ENABLETHRUSTPIDSCALING_TRUE=1 } EnableThrustPIDScalingOptions;
    // Field ThrustPIDScaleSource information
    /* Enumeration options for field ThrustPIDScaleSource */
    typedef enum { THRUSTPIDSCALESOURCE_MANUALCONTROLTHROTTLE=0, THRUSTPIDSCALESOURCE_STABILIZATIONDESIREDTHRUST=1, THRUSTPIDSCALESOURCE_ACTUATORDESIREDTHRUST=2 } ThrustPIDScaleSourceOptions;
    // Field ThrustPIDScaleTarget information
    /* Enumeration options for field ThrustPIDScaleTarget */
    typedef enum { THRUSTPIDSCALETARGET_PID=0, THRUSTPIDSCALETARGET_PI=1, THRUSTPIDSCALETARGET_PD=2, THRUSTPIDSCALETARGET_ID=3, THRUSTPIDSCALETARGET_P=4, THRUSTPIDSCALETARGET_I=5, THRUSTPIDSCALETARGET_D=6 } ThrustPIDScaleTargetOptions;
    // Field ThrustPIDScaleAxes information
    /* Enumeration options for field ThrustPIDScaleAxes */
    typedef enum { THRUSTPIDSCALEAXES_ROLLPITCHYAW=0, THRUSTPIDSCALEAXES_ROLLPITCH=1, THRUSTPIDSCALEAXES_ROLLYAW=2, THRUSTPIDSCALEAXES_ROLL=3, THRUSTPIDSCALEAXES_PITCHYAW=4, THRUSTPIDSCALEAXES_PITCH=5, THRUSTPIDSCALEAXES_YAW=6 } ThrustPIDScaleAxesOptions;

  
    // Constants
    static const quint32 OBJID = 0xE8EBBD48;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    StabilizationSettingsBank1();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static StabilizationSettingsBank1* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getManualRate(quint32 index) const;
    Q_INVOKABLE float getManualRate_Roll() const;
    Q_INVOKABLE float getManualRate_Pitch() const;
    Q_INVOKABLE float getManualRate_Yaw() const;
    Q_INVOKABLE float getMaximumRate(quint32 index) const;
    Q_INVOKABLE float getMaximumRate_Roll() const;
    Q_INVOKABLE float getMaximumRate_Pitch() const;
    Q_INVOKABLE float getMaximumRate_Yaw() const;
    Q_INVOKABLE float getRollRatePID(quint32 index) const;
    Q_INVOKABLE float getRollRatePID_Kp() const;
    Q_INVOKABLE float getRollRatePID_Ki() const;
    Q_INVOKABLE float getRollRatePID_Kd() const;
    Q_INVOKABLE float getRollRatePID_ILimit() const;
    Q_INVOKABLE float getPitchRatePID(quint32 index) const;
    Q_INVOKABLE float getPitchRatePID_Kp() const;
    Q_INVOKABLE float getPitchRatePID_Ki() const;
    Q_INVOKABLE float getPitchRatePID_Kd() const;
    Q_INVOKABLE float getPitchRatePID_ILimit() const;
    Q_INVOKABLE float getYawRatePID(quint32 index) const;
    Q_INVOKABLE float getYawRatePID_Kp() const;
    Q_INVOKABLE float getYawRatePID_Ki() const;
    Q_INVOKABLE float getYawRatePID_Kd() const;
    Q_INVOKABLE float getYawRatePID_ILimit() const;
    Q_INVOKABLE float getRollPI(quint32 index) const;
    Q_INVOKABLE float getRollPI_Kp() const;
    Q_INVOKABLE float getRollPI_Ki() const;
    Q_INVOKABLE float getRollPI_ILimit() const;
    Q_INVOKABLE float getPitchPI(quint32 index) const;
    Q_INVOKABLE float getPitchPI_Kp() const;
    Q_INVOKABLE float getPitchPI_Ki() const;
    Q_INVOKABLE float getPitchPI_ILimit() const;
    Q_INVOKABLE float getYawPI(quint32 index) const;
    Q_INVOKABLE float getYawPI_Kp() const;
    Q_INVOKABLE float getYawPI_Ki() const;
    Q_INVOKABLE float getYawPI_ILimit() const;
    Q_INVOKABLE float getAcroInsanityFactor() const;
    Q_INVOKABLE float getThrustPIDScaleCurve(quint32 index) const;
    Q_INVOKABLE float getThrustPIDScaleCurve_0() const;
    Q_INVOKABLE float getThrustPIDScaleCurve_25() const;
    Q_INVOKABLE float getThrustPIDScaleCurve_50() const;
    Q_INVOKABLE float getThrustPIDScaleCurve_75() const;
    Q_INVOKABLE float getThrustPIDScaleCurve_100() const;
    Q_INVOKABLE quint8 getRollMax() const;
    Q_INVOKABLE quint8 getPitchMax() const;
    Q_INVOKABLE quint8 getYawMax() const;
    Q_INVOKABLE qint8 getStickExpo(quint32 index) const;
    Q_INVOKABLE qint8 getStickExpo_Roll() const;
    Q_INVOKABLE qint8 getStickExpo_Pitch() const;
    Q_INVOKABLE qint8 getStickExpo_Yaw() const;
    Q_INVOKABLE quint8 getEnablePiroComp() const;
    Q_INVOKABLE quint8 getEnableThrustPIDScaling() const;
    Q_INVOKABLE quint8 getThrustPIDScaleSource() const;
    Q_INVOKABLE quint8 getThrustPIDScaleTarget() const;
    Q_INVOKABLE quint8 getThrustPIDScaleAxes() const;


public slots:
    void setManualRate(quint32 index, float value);
    void setManualRate_Roll(float value);
    void setManualRate_Pitch(float value);
    void setManualRate_Yaw(float value);
    void setMaximumRate(quint32 index, float value);
    void setMaximumRate_Roll(float value);
    void setMaximumRate_Pitch(float value);
    void setMaximumRate_Yaw(float value);
    void setRollRatePID(quint32 index, float value);
    void setRollRatePID_Kp(float value);
    void setRollRatePID_Ki(float value);
    void setRollRatePID_Kd(float value);
    void setRollRatePID_ILimit(float value);
    void setPitchRatePID(quint32 index, float value);
    void setPitchRatePID_Kp(float value);
    void setPitchRatePID_Ki(float value);
    void setPitchRatePID_Kd(float value);
    void setPitchRatePID_ILimit(float value);
    void setYawRatePID(quint32 index, float value);
    void setYawRatePID_Kp(float value);
    void setYawRatePID_Ki(float value);
    void setYawRatePID_Kd(float value);
    void setYawRatePID_ILimit(float value);
    void setRollPI(quint32 index, float value);
    void setRollPI_Kp(float value);
    void setRollPI_Ki(float value);
    void setRollPI_ILimit(float value);
    void setPitchPI(quint32 index, float value);
    void setPitchPI_Kp(float value);
    void setPitchPI_Ki(float value);
    void setPitchPI_ILimit(float value);
    void setYawPI(quint32 index, float value);
    void setYawPI_Kp(float value);
    void setYawPI_Ki(float value);
    void setYawPI_ILimit(float value);
    void setAcroInsanityFactor(float value);
    void setThrustPIDScaleCurve(quint32 index, float value);
    void setThrustPIDScaleCurve_0(float value);
    void setThrustPIDScaleCurve_25(float value);
    void setThrustPIDScaleCurve_50(float value);
    void setThrustPIDScaleCurve_75(float value);
    void setThrustPIDScaleCurve_100(float value);
    void setRollMax(quint8 value);
    void setPitchMax(quint8 value);
    void setYawMax(quint8 value);
    void setStickExpo(quint32 index, qint8 value);
    void setStickExpo_Roll(qint8 value);
    void setStickExpo_Pitch(qint8 value);
    void setStickExpo_Yaw(qint8 value);
    void setEnablePiroComp(quint8 value);
    void setEnableThrustPIDScaling(quint8 value);
    void setThrustPIDScaleSource(quint8 value);
    void setThrustPIDScaleTarget(quint8 value);
    void setThrustPIDScaleAxes(quint8 value);


signals:
    void ManualRateChanged(quint32 index, float value);
    void ManualRate_RollChanged(float value);
    void ManualRate_PitchChanged(float value);
    void ManualRate_YawChanged(float value);
    void MaximumRateChanged(quint32 index, float value);
    void MaximumRate_RollChanged(float value);
    void MaximumRate_PitchChanged(float value);
    void MaximumRate_YawChanged(float value);
    void RollRatePIDChanged(quint32 index, float value);
    void RollRatePID_KpChanged(float value);
    void RollRatePID_KiChanged(float value);
    void RollRatePID_KdChanged(float value);
    void RollRatePID_ILimitChanged(float value);
    void PitchRatePIDChanged(quint32 index, float value);
    void PitchRatePID_KpChanged(float value);
    void PitchRatePID_KiChanged(float value);
    void PitchRatePID_KdChanged(float value);
    void PitchRatePID_ILimitChanged(float value);
    void YawRatePIDChanged(quint32 index, float value);
    void YawRatePID_KpChanged(float value);
    void YawRatePID_KiChanged(float value);
    void YawRatePID_KdChanged(float value);
    void YawRatePID_ILimitChanged(float value);
    void RollPIChanged(quint32 index, float value);
    void RollPI_KpChanged(float value);
    void RollPI_KiChanged(float value);
    void RollPI_ILimitChanged(float value);
    void PitchPIChanged(quint32 index, float value);
    void PitchPI_KpChanged(float value);
    void PitchPI_KiChanged(float value);
    void PitchPI_ILimitChanged(float value);
    void YawPIChanged(quint32 index, float value);
    void YawPI_KpChanged(float value);
    void YawPI_KiChanged(float value);
    void YawPI_ILimitChanged(float value);
    void AcroInsanityFactorChanged(float value);
    void ThrustPIDScaleCurveChanged(quint32 index, float value);
    void ThrustPIDScaleCurve_0Changed(float value);
    void ThrustPIDScaleCurve_25Changed(float value);
    void ThrustPIDScaleCurve_50Changed(float value);
    void ThrustPIDScaleCurve_75Changed(float value);
    void ThrustPIDScaleCurve_100Changed(float value);
    void RollMaxChanged(quint8 value);
    void PitchMaxChanged(quint8 value);
    void YawMaxChanged(quint8 value);
    void StickExpoChanged(quint32 index, qint8 value);
    void StickExpo_RollChanged(qint8 value);
    void StickExpo_PitchChanged(qint8 value);
    void StickExpo_YawChanged(qint8 value);
    void EnablePiroCompChanged(quint8 value);
    void EnableThrustPIDScalingChanged(quint8 value);
    void ThrustPIDScaleSourceChanged(quint8 value);
    void ThrustPIDScaleTargetChanged(quint8 value);
    void ThrustPIDScaleAxesChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // STABILIZATIONSETTINGSBANK1_H
