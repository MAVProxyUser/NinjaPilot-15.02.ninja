/**
 ******************************************************************************
 *
 * @file       magcalibrationmodel.h
 * @author     NinjaPilot, 2026
 *
 * @brief      Free-rotation magnetometer calibration
 *
 * Replaces the six-point procedure for the magnetometer. Six discrete
 * orientations is the bare minimum to fit a three-degree-of-freedom offset,
 * and each one has to be held square by hand; this samples continuously while
 * the vehicle is rotated and fits the sphere the readings lie on.
 *
 * With no interference every reading sits on a sphere of radius |B|. Hard iron
 * shifts that sphere's centre away from the origin -- and that centre IS
 * RevoCalibration.mag_bias. Hundreds of well-spread samples constrain it far
 * better than six can, and the fit residual and the radius give two honest
 * quality numbers that the six-point flow never reports.
 *
 * @see        The GNU Public License (GPL) Version 3
 * @defgroup
 * @{
 *
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
#ifndef MAGCALIBRATIONMODEL_H
#define MAGCALIBRATIONMODEL_H

#include "wizardmodel.h"
#include "calibration/calibrationutils.h"

#include <revocalibration.h>
#include <homelocation.h>
#include <magsensor.h>

#include <QObject>
#include <QMutex>
#include <QSet>
#include <QString>
#include <QVector>

namespace OpenPilot {
class MagCalibrationModel : public QObject {
    Q_OBJECT

public:
    explicit MagCalibrationModel(QObject *parent = 0);

    bool dirty()
    {
        return m_dirty;
    }

signals:
    void started();
    void stopped();
    void storeAndClearBoardRotation();
    void recallBoardRotation();
    void savePositionEnabledChanged(bool state);
    void progressChanged(int value);
    void displayVisualHelp(QString elementID);
    void displayInstructions(QString text, WizardModel::MessageType type = WizardModel::Info);

public slots:
    /** Begin collecting. Wired to the same button the six-point flow used. */
    void magStart();
    /** Finish early and fit with whatever has been collected so far. */
    void finish();
    void save();

private slots:
    /** Starts sampling only after the zeroed calibration has reached the
     * board -- see the comment in magStart(). */
    void beginCollecting();
    void getSample(UAVObject *obj);

private:
    /** Least-squares AXIS-ALIGNED ELLIPSOID fit.
     *
     * A sphere fit corrects hard iron only. Real installations also have soft
     * iron, which stretches the sphere into an ellipsoid -- and then no single
     * radius is right: the corrected magnitude comes out fine in some
     * orientations and badly wrong in others, which filtermag.c sees as a
     * magnitude error and alarms on. Measured here: a sphere fit reporting
     * radius 510 mGa gave 416 mGa when the board sat still in one attitude,
     * 21% off the 529 mGa reference, tripping the 15% Error threshold.
     *
     * Fitting three independent semi-axes gives the per-axis scale that
     * mag_transform's diagonal is for. Returns semi-axes in @p semi.
     */
    bool fitEllipsoid(double centre[3], double semi[3], double *rmsResidual);

    /** Fraction of 26 direction bins containing at least one sample. A blunt
     * but honest check that the vehicle was actually rotated rather than
     * waved about in one plane. */
    double coverage(const double centre[3]) const;

    UAVObjectManager *getObjectManager();

    RevoCalibration *revoCalibration;
    HomeLocation *homeLocation;
    MagSensor *magSensor;

    struct Memento {
        RevoCalibration::DataFields revoCalibrationData;
        UAVObject::Metadata magSensorMetadata;
    } memento;

    QVector<double> m_x, m_y, m_z;
    QSet<int> m_bins;
    bool m_collecting;
    bool m_dirty;

    /* Below this total spread the board is sitting still and the readings are
     * jitter, not orientation. */
    static const double MOTION_SPAN_MGA;

    /* About 40 seconds at the 20ms telemetry period this sets. 300 was far too
     * low -- roughly six seconds, so the run self-terminated almost as soon as
     * it reached the bin target and there was no time to cover the sphere. The
     * fit is over-determined either way; what more samples buy is TIME to
     * rotate through the awkward diagonals. */
    static const int MIN_SAMPLES  = 2000;
    static const int TOTAL_BINS   = 26;
    /* The eight corner bins are hard to hit by hand; requiring all 26 means the
     * run never self-terminates. 20/26 is still a well-covered sphere. */
    static const int GOOD_BINS    = 20;
};
}

#endif // MAGCALIBRATIONMODEL_H
