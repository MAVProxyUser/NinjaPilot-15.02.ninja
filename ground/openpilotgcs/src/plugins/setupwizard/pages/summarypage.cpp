/**
 ******************************************************************************
 *
 * @file       summarypage.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @addtogroup
 * @{
 * @addtogroup SummaryPage
 * @{
 * @brief
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

#include "summarypage.h"
#include "ui_summarypage.h"
#include "setupwizard.h"
#include "connectiondiagram.h"

#include <QAbstractButton>
#include <QApplication>

SummaryPage::SummaryPage(SetupWizard *wizard, QWidget *parent) :
    AbstractWizardPage(wizard, parent),
    ui(new Ui::SummaryPage), m_saving(false)
{
    ui->setupUi(this);
    connect(ui->illustrationButton, SIGNAL(clicked()), this, SLOT(showDiagram()));
}

SummaryPage::~SummaryPage()
{
    delete ui;
}

bool SummaryPage::validatePage()
{
    // setupVehicle() below spins a nested QEventLoop per object while it waits
    // for each transaction to complete. That loop delivers mouse events, so a
    // second click on Next re-enters this function and starts another save on
    // top of the one still running. Refuse to re-enter, and take the buttons
    // away for the duration the way every other long-running page here does.
    if (m_saving) {
        return false;
    }
    m_saving = true;
    enableButtons(false);

    // Save settings so far.
    VehicleConfigurationHelper helper(getWizard());

    helper.setupVehicle(false);

    enableButtons(true);
    m_saving = false;
    return true;
}

void SummaryPage::enableButtons(bool enable)
{
    getWizard()->button(QWizard::NextButton)->setEnabled(enable);
    getWizard()->button(QWizard::CancelButton)->setEnabled(enable);
    getWizard()->button(QWizard::BackButton)->setEnabled(enable);
    getWizard()->button(QWizard::CustomButton1)->setEnabled(enable);
    QApplication::processEvents();
}

void SummaryPage::initializePage()
{
    ui->configurationSummary->setText(getWizard()->getSummaryText());
}

void SummaryPage::showDiagram()
{
    ConnectionDiagram diagram(this, getWizard());

    diagram.exec();
}
