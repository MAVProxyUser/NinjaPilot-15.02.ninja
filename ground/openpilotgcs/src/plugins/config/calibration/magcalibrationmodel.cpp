/**
 ******************************************************************************
 *
 * @file       magcalibrationmodel.cpp
 * @author     NinjaPilot, 2026
 *
 * @brief      Free-rotation magnetometer calibration -- see the header.
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
#include "magcalibrationmodel.h"

#include <extensionsystem/pluginmanager.h>
#include <uavobjectmanager.h>

#include <QDebug>
#include <QTimer>
#include <QtCore/qmath.h>

namespace OpenPilot {
const double MagCalibrationModel::MOTION_SPAN_MGA = 150.0;

MagCalibrationModel::MagCalibrationModel(QObject *parent) :
    QObject(parent), m_collecting(false), m_dirty(false)
{
    revoCalibration = RevoCalibration::GetInstance(getObjectManager());
    Q_ASSERT(revoCalibration);
    homeLocation    = HomeLocation::GetInstance(getObjectManager());
    Q_ASSERT(homeLocation);
    magSensor       = MagSensor::GetInstance(getObjectManager());
    Q_ASSERT(magSensor);
}

void MagCalibrationModel::magStart()
{
    started();

    /* The magnetometer is fitted against the local field vector, so we need to
     * know what that is -- both to judge the fitted radius and because
     * filtermag.c scores every sample against it in flight. */
    HomeLocation::DataFields home = homeLocation->getData();
    if (!home.Set) {
        displayInstructions(tr("Home location not set, please set your home location and retry."),
                            WizardModel::Warn);
        displayInstructions(tr("Aborting calibration!"), WizardModel::Failure);
        stopped();
        return;
    }

    storeAndClearBoardRotation();

    // Start from a clean slate: fitting against a previous correction would
    // measure the residual of that correction rather than the hard iron.
    memento.revoCalibrationData = revoCalibration->getData();
    RevoCalibration::DataFields cal = memento.revoCalibrationData;
    for (int i = 0; i <= RevoCalibration::MAG_TRANSFORM_R2C2; i++) {
        cal.mag_transform[i] = 0;
    }
    cal.mag_transform[RevoCalibration::MAG_TRANSFORM_R0C0] = 1;
    cal.mag_transform[RevoCalibration::MAG_TRANSFORM_R1C1] = 1;
    cal.mag_transform[RevoCalibration::MAG_TRANSFORM_R2C2] = 1;
    cal.mag_bias[RevoCalibration::MAG_BIAS_X] = 0;
    cal.mag_bias[RevoCalibration::MAG_BIAS_Y] = 0;
    cal.mag_bias[RevoCalibration::MAG_BIAS_Z] = 0;
    // Adaptive nulling would chase the very offset we are trying to measure.
    cal.MagBiasNullingRate = 0;
    revoCalibration->setData(cal);

    memento.magSensorMetadata = magSensor->getMetadata();
    UAVObject::Metadata mdata = magSensor->getMetadata();
    UAVObject::SetFlightTelemetryUpdateMode(mdata, UAVObject::UPDATEMODE_PERIODIC);
    mdata.flightTelemetryUpdatePeriod = 20;
    magSensor->setMetadata(mdata);

    m_x.clear();
    m_y.clear();
    m_z.clear();
    m_bins.clear();
    m_dirty      = false;
    m_collecting = true;

    displayInstructions(tr("Clearing the previous calibration, one moment ..."),
                        WizardModel::Info);
    savePositionEnabledChanged(false);
    progressChanged(0);

    /* Do NOT start sampling yet.
     *
     * The zeroed RevoCalibration above is still in flight to the board, and
     * sensors.c keeps applying the OLD mag_bias and mag_transform until it
     * lands. Sampling immediately therefore fits data that is already
     * corrected by the previous run -- so each calibration measured the
     * residual of the one before it rather than the raw field, the offset
     * walked between runs, and applying the result made the error worse
     * (529 mGa expected, 416 after one run, 302 after the next).
     *
     * Wait for the write to take effect before collecting anything. */
    QTimer::singleShot(1200, this, SLOT(beginCollecting()));
}

void MagCalibrationModel::beginCollecting()
{
    if (!m_collecting) {
        return; // start() was aborted while we waited
    }
    m_x.clear();
    m_y.clear();
    m_z.clear();
    m_bins.clear();

    displayInstructions(tr("Rotate the vehicle slowly through every orientation, "
                           "as if turning a dice over in your hands. Roll through "
                           "the edges and corners, not just face to face."),
                        WizardModel::Prompt);
    displayVisualHelp("plane-horizontal");
    savePositionEnabledChanged(true);

    connect(magSensor, SIGNAL(objectUpdated(UAVObject *)), this, SLOT(getSample(UAVObject *)));
}

void MagCalibrationModel::getSample(UAVObject *obj)
{
    Q_UNUSED(obj);
    if (!m_collecting) {
        return;
    }

    MagSensor::DataFields m = magSensor->getData();
    if (m.x == 0.0f && m.y == 0.0f && m.z == 0.0f) {
        return;
    }
    m_x.append(m.x);
    m_y.append(m.y);
    m_z.append(m.z);

    /* Progress is COVERAGE, not sample count -- a stationary board streaming at
     * 50Hz must not fill the bar.
     *
     * Bin against the midpoint of the bounding box seen so far, NOT the running
     * mean. The mean sits wherever the operator has dwelt longest, so early on
     * it is nowhere near the sphere's centre and directions measured from it
     * scatter across many bins at once: the bar raced to 100% while the true
     * coverage, measured later from the fitted centre, was 77%. The bounding
     * box midpoint converges on the centre as the sphere is explored, and does
     * not chase the dwell time.
     *
     * Also refuse to bin at all until there is enough spread to be a rotation
     * rather than noise -- otherwise a motionless board bins its own jitter. */
    double minv[3] = { m_x[0], m_y[0], m_z[0] };
    double maxv[3] = { m_x[0], m_y[0], m_z[0] };
    for (int i = 1; i < m_x.size(); i++) {
        minv[0] = qMin(minv[0], (double)m_x[i]);
        maxv[0] = qMax(maxv[0], (double)m_x[i]);
        minv[1] = qMin(minv[1], (double)m_y[i]);
        maxv[1] = qMax(maxv[1], (double)m_y[i]);
        minv[2] = qMin(minv[2], (double)m_z[i]);
        maxv[2] = qMax(maxv[2], (double)m_z[i]);
    }
    double span = qMax(maxv[0] - minv[0], qMax(maxv[1] - minv[1], maxv[2] - minv[2]));

    if (span > MOTION_SPAN_MGA) {
        double cx = 0.5 * (minv[0] + maxv[0]);
        double cy = 0.5 * (minv[1] + maxv[1]);
        double cz = 0.5 * (minv[2] + maxv[2]);

        double vx = m.x - cx, vy = m.y - cy, vz = m.z - cz;
        double n  = qSqrt(vx * vx + vy * vy + vz * vz);
        /* Ignore samples close to the centre: their direction is noise. */
        if (n > 0.3 * span) {
            int bx = qBound(-1, qRound(vx / n * 1.5), 1);
            int by = qBound(-1, qRound(vy / n * 1.5), 1);
            int bz = qBound(-1, qRound(vz / n * 1.5), 1);
            if (bx || by || bz) {
                m_bins.insert((bx + 1) * 9 + (by + 1) * 3 + (bz + 1));
            }
        }
    }

    /* Show progress toward the ACTUAL finish condition, so 100% means "it is
     * about to stop" rather than "it stopped at 80%". Both criteria must be
     * met, so the bar is the lesser of the two -- previously it showed
     * bins/26 while finishing at 20/26, and could never reach 100%. */
    int binPct    = (100 * m_bins.size()) / GOOD_BINS;
    int samplePct = (100 * m_x.size()) / MIN_SAMPLES;
    progressChanged(qBound(0, qMin(binPct, samplePct), 100));

    if (m_bins.size() >= GOOD_BINS && m_x.size() >= MIN_SAMPLES) {
        finish();
    }
}

void MagCalibrationModel::finish()
{
    if (!m_collecting) {
        return;
    }
    m_collecting = false;
    disconnect(magSensor, SIGNAL(objectUpdated(UAVObject *)), this, SLOT(getSample(UAVObject *)));

    magSensor->setMetadata(memento.magSensorMetadata);
    savePositionEnabledChanged(false);
    recallBoardRotation();

    double centre[3], semi[3], rms;
    if (!fitEllipsoid(centre, semi, &rms)) {
        displayInstructions(tr("Could not fit those samples. Either the vehicle was "
                               "tilted but never rolled, or the readings do not "
                               "describe an ellipsoid at all."),
                            WizardModel::Failure);
        revoCalibration->setData(memento.revoCalibrationData);
        stopped();
        return;
    }

    double radius = (semi[0] + semi[1] + semi[2]) / 3.0;
    double cov    = coverage(centre);

    /* Judge the fit before offering it. A bad correction is worse than none:
     * filtermag.c scores every sample against HomeLocation.Be either way, so a
     * wrong one fails just as hard as a missing one while looking like it
     * worked. */
    HomeLocation::DataFields home = homeLocation->getData();
    double expected = qSqrt(home.Be[0] * home.Be[0] + home.Be[1] * home.Be[1]
                            + home.Be[2] * home.Be[2]);

    displayInstructions(tr("Fitted %1 samples: offset %2 %3 %4 mGa, axes %5 %6 %7 mGa "
                           "(local field %8), residual %9 mGa, coverage %10%.")
                        .arg(m_x.size())
                        .arg(centre[0], 0, 'f', 1).arg(centre[1], 0, 'f', 1).arg(centre[2], 0, 'f', 1)
                        .arg(semi[0], 0, 'f', 1).arg(semi[1], 0, 'f', 1).arg(semi[2], 0, 'f', 1)
                        .arg(expected, 0, 'f', 1)
                        .arg(rms, 0, 'f', 1).arg(cov * 100.0, 0, 'f', 0),
                        WizardModel::Info);

    if (cov < 0.5) {
        displayInstructions(tr("Rejected: only %1% of orientations were visited. "
                               "A partial shell fits badly -- rotate through more of them.")
                            .arg(cov * 100.0, 0, 'f', 0), WizardModel::Failure);
        revoCalibration->setData(memento.revoCalibrationData);
        stopped();
        return;
    }
    if (rms > 0.15 * radius) {
        displayInstructions(tr("Rejected: residual is %1% of the mean axis even after "
                               "fitting an ellipsoid, so something magnetic moved during "
                               "the run.")
                            .arg(100.0 * rms / radius, 0, 'f', 0), WizardModel::Failure);
        revoCalibration->setData(memento.revoCalibrationData);
        stopped();
        return;
    }
    if (expected > 1.0 && (radius < 0.5 * expected || radius > 2.0 * expected)) {
        displayInstructions(tr("Rejected: fitted axes average %1 mGa, nowhere near the "
                               "local field %2 mGa. Something nearby is magnetic.")
                            .arg(radius, 0, 'f', 1).arg(expected, 0, 'f', 1),
                            WizardModel::Failure);
        revoCalibration->setData(memento.revoCalibrationData);
        stopped();
        return;
    }

    RevoCalibration::DataFields cal = revoCalibration->getData();
    cal.mag_bias[RevoCalibration::MAG_BIAS_X] = centre[0];
    cal.mag_bias[RevoCalibration::MAG_BIAS_Y] = centre[1];
    cal.mag_bias[RevoCalibration::MAG_BIAS_Z] = centre[2];

    /* Soft iron: scale each axis so the corrected vector has magnitude Be in
     * EVERY orientation, not merely on average. Without this the corrected
     * magnitude is right in some attitudes and wrong in others, and
     * filtermag.c alarms on exactly that -- measured at 416 mGa against a 529
     * reference while the sphere fit was reporting a 510 radius.
     *
     * sensors.c multiplies this matrix by the board rotation at runtime, so a
     * pure diagonal scale stored here composes correctly. */
    if (expected > 1.0) {
        for (int i = 0; i <= RevoCalibration::MAG_TRANSFORM_R2C2; i++) {
            cal.mag_transform[i] = 0;
        }
        cal.mag_transform[RevoCalibration::MAG_TRANSFORM_R0C0] = expected / semi[0];
        cal.mag_transform[RevoCalibration::MAG_TRANSFORM_R1C1] = expected / semi[1];
        cal.mag_transform[RevoCalibration::MAG_TRANSFORM_R2C2] = expected / semi[2];
    }
    revoCalibration->setData(cal);

    m_dirty = true;
    displayInstructions(tr("Calibration succeeded. Press Save to store it."), WizardModel::Success);
    stopped();
}

void MagCalibrationModel::save()
{
    if (!m_dirty) {
        return;
    }
    revoCalibration->updated();
    m_dirty = false;
}

bool MagCalibrationModel::fitEllipsoid(double centre[3], double semi[3], double *rmsResidual)
{
    const int n = m_x.size();

    if (n < 10) {
        return false;
    }

    /* Axis-aligned ellipsoid through the origin-shifted samples:
     *
     *     p1 x^2 + p2 y^2 + p3 z^2 + p4 x + p5 y + p6 z = 1
     *
     * which is LINEAR in p1..p6, so it is another normal-equations solve --
     * 6x6 this time rather than the sphere's 4x4. Recovering the centre and
     * the semi-axes from p is then algebra:
     *
     *     cx = -p4 / 2 p1,  and  S = 1 + p1 cx^2 + p2 cy^2 + p3 cz^2
     *     a  = sqrt(S / p1)
     *
     * Deliberately axis-aligned: a general ellipsoid needs the three cross
     * terms too, and recovering its rotation means an eigen-decomposition and
     * a full 3x3 mag_transform. The axis-aligned form captures per-axis scale,
     * which is the dominant part of soft iron for a small board, and maps onto
     * mag_transform's diagonal directly. */
    /* Shift to the data's mean before fitting. The samples sit at a hard-iron
     * offset of several hundred mGa with a radius of the same order, so the
     * squared terms are ~1e5 while the linear terms are ~1e2. Normal equations
     * square that ratio again, and the solve then fails its pivot test and
     * reports "degenerate" on data that is perfectly good -- which is exactly
     * what happened to a well-rolled 100%-coverage run. Fitting about the mean
     * makes the linear terms small and the system well conditioned; the offset
     * is added back afterwards. */
    double mx = 0, my = 0, mz = 0;
    for (int i = 0; i < n; i++) {
        mx += m_x[i];
        my += m_y[i];
        mz += m_z[i];
    }
    mx /= n;
    my /= n;
    mz /= n;

    const int N = 6;
    double A[6][7] = { { 0 } };

    for (int i = 0; i < n; i++) {
        double x = m_x[i] - mx, y = m_y[i] - my, z = m_z[i] - mz;
        double row[6] = { x * x, y * y, z * z, x, y, z };
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                A[r][c] += row[r] * row[c];
            }
            A[r][N] += row[r] * 1.0;
        }
    }

    for (int col = 0; col < N; col++) {
        int piv = col;
        for (int r = col + 1; r < N; r++) {
            if (qAbs(A[r][col]) > qAbs(A[piv][col])) {
                piv = r;
            }
        }
        if (qAbs(A[piv][col]) < 1e-12) {
            return false;
        }
        for (int c = 0; c <= N; c++) {
            qSwap(A[col][c], A[piv][c]);
        }
        for (int r = 0; r < N; r++) {
            if (r == col) {
                continue;
            }
            double f = A[r][col] / A[col][col];
            for (int c = col; c <= N; c++) {
                A[r][c] -= f * A[col][c];
            }
        }
    }

    double p[6];
    for (int i = 0; i < N; i++) {
        p[i] = A[i][N] / A[i][i];
    }

    // All three quadratic terms must be positive, or this is not an ellipsoid
    // (a hyperboloid fits a partial shell happily and means nothing).
    if (p[0] <= 0 || p[1] <= 0 || p[2] <= 0) {
        return false;
    }

    centre[0] = -p[3] / (2.0 * p[0]) + mx;
    centre[1] = -p[4] / (2.0 * p[1]) + my;
    centre[2] = -p[5] / (2.0 * p[2]) + mz;

    /* S is computed in the SHIFTED frame the coefficients belong to. */
    double sx = centre[0] - mx, sy = centre[1] - my, sz = centre[2] - mz;
    double S  = 1.0 + p[0] * sx * sx + p[1] * sy * sy + p[2] * sz * sz;
    if (S <= 0) {
        return false;
    }

    semi[0] = qSqrt(S / p[0]);
    semi[1] = qSqrt(S / p[1]);
    semi[2] = qSqrt(S / p[2]);

    /* Residual is measured AFTER scaling to the unit sphere, so it reports how
     * well the ellipsoid model actually describes the data rather than how far
     * the data is from a sphere it was never going to be. */
    double acc = 0;
    for (int i = 0; i < n; i++) {
        double dx = (m_x[i] - centre[0]) / semi[0];
        double dy = (m_y[i] - centre[1]) / semi[1];
        double dz = (m_z[i] - centre[2]) / semi[2];
        double d  = qSqrt(dx * dx + dy * dy + dz * dz) - 1.0;
        acc += d * d;
    }
    *rmsResidual = qSqrt(acc / n) * ((semi[0] + semi[1] + semi[2]) / 3.0);

    return true;
}

double MagCalibrationModel::coverage(const double centre[3]) const
{
    QSet<int> bins;

    for (int i = 0; i < m_x.size(); i++) {
        double vx = m_x[i] - centre[0];
        double vy = m_y[i] - centre[1];
        double vz = m_z[i] - centre[2];
        double n  = qSqrt(vx * vx + vy * vy + vz * vz);
        if (n < 1e-6) {
            continue;
        }
        int bx = qBound(-1, qRound(vx / n * 1.5), 1);
        int by = qBound(-1, qRound(vy / n * 1.5), 1);
        int bz = qBound(-1, qRound(vz / n * 1.5), 1);
        if (bx || by || bz) {
            bins.insert((bx + 1) * 9 + (by + 1) * 3 + (bz + 1));
        }
    }
    return (double)bins.size() / (double)TOTAL_BINS;
}

UAVObjectManager *MagCalibrationModel::getObjectManager()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    UAVObjectManager *objMngr = pm->getObject<UAVObjectManager>();

    Q_ASSERT(objMngr);
    return objMngr;
}
}
