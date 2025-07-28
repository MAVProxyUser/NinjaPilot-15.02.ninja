/********************************************************************************
** Form generated from reading UI file 'generalsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERALSETTINGS_H
#define UI_GENERALSETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "utils/qtcolorbutton.h"

namespace Core {
namespace Internal {

class Ui_GeneralSettings
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *labelExpert;
    QCheckBox *cbUseUDPMirror;
    QCheckBox *checkAutoSelect;
    QLabel *label_5;
    QCheckBox *checkBoxSaveOnExit;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QToolButton *resetButton;
    Utils::QtColorButton *colorButton;
    QSpacerItem *horizontalSpacer;
    QLabel *colorLabel;
    QLabel *labelExpert_2;
    QWidget *widget_2;
    QGridLayout *gridLayout_3;
    QCheckBox *cbExpertMode;
    QCheckBox *checkAutoConnect;
    QLabel *labelUDP;
    QHBoxLayout *horizontalLayout;
    QComboBox *languageBox;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QLabel *label_6;
    QCheckBox *cbUsageData;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Core__Internal__GeneralSettings)
    {
        if (Core__Internal__GeneralSettings->objectName().isEmpty())
            Core__Internal__GeneralSettings->setObjectName(QString::fromUtf8("Core__Internal__GeneralSettings"));
        Core__Internal__GeneralSettings->resize(536, 322);
        verticalLayout_2 = new QVBoxLayout(Core__Internal__GeneralSettings);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(Core__Internal__GeneralSettings);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        labelExpert = new QLabel(groupBox);
        labelExpert->setObjectName(QString::fromUtf8("labelExpert"));

        gridLayout->addWidget(labelExpert, 14, 0, 1, 1);

        cbUseUDPMirror = new QCheckBox(groupBox);
        cbUseUDPMirror->setObjectName(QString::fromUtf8("cbUseUDPMirror"));

        gridLayout->addWidget(cbUseUDPMirror, 13, 2, 1, 1);

        checkAutoSelect = new QCheckBox(groupBox);
        checkAutoSelect->setObjectName(QString::fromUtf8("checkAutoSelect"));
        checkAutoSelect->setEnabled(false);
        checkAutoSelect->setChecked(true);

        gridLayout->addWidget(checkAutoSelect, 12, 2, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setWordWrap(true);

        gridLayout->addWidget(label_5, 11, 0, 1, 1);

        checkBoxSaveOnExit = new QCheckBox(groupBox);
        checkBoxSaveOnExit->setObjectName(QString::fromUtf8("checkBoxSaveOnExit"));
        checkBoxSaveOnExit->setChecked(true);

        gridLayout->addWidget(checkBoxSaveOnExit, 10, 2, 1, 1);

        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        resetButton = new QToolButton(widget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/core/images/reset.png"), QSize(), QIcon::Normal, QIcon::Off);
        resetButton->setIcon(icon);

        gridLayout_2->addWidget(resetButton, 0, 1, 1, 1);

        colorButton = new Utils::QtColorButton(widget);
        colorButton->setObjectName(QString::fromUtf8("colorButton"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(colorButton->sizePolicy().hasHeightForWidth());
        colorButton->setSizePolicy(sizePolicy);
        colorButton->setMinimumSize(QSize(64, 0));
        colorButton->setProperty("alphaAllowed", QVariant(false));

        gridLayout_2->addWidget(colorButton, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);


        gridLayout->addWidget(widget, 1, 2, 1, 1);

        colorLabel = new QLabel(groupBox);
        colorLabel->setObjectName(QString::fromUtf8("colorLabel"));

        gridLayout->addWidget(colorLabel, 1, 0, 1, 1);

        labelExpert_2 = new QLabel(groupBox);
        labelExpert_2->setObjectName(QString::fromUtf8("labelExpert_2"));

        gridLayout->addWidget(labelExpert_2, 15, 0, 1, 1);

        widget_2 = new QWidget(groupBox);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout_3 = new QGridLayout(widget_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);

        gridLayout->addWidget(widget_2, 9, 2, 1, 1);

        cbExpertMode = new QCheckBox(groupBox);
        cbExpertMode->setObjectName(QString::fromUtf8("cbExpertMode"));

        gridLayout->addWidget(cbExpertMode, 14, 2, 1, 1);

        checkAutoConnect = new QCheckBox(groupBox);
        checkAutoConnect->setObjectName(QString::fromUtf8("checkAutoConnect"));
        checkAutoConnect->setChecked(true);

        gridLayout->addWidget(checkAutoConnect, 11, 2, 1, 1);

        labelUDP = new QLabel(groupBox);
        labelUDP->setObjectName(QString::fromUtf8("labelUDP"));

        gridLayout->addWidget(labelUDP, 13, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        languageBox = new QComboBox(groupBox);
        languageBox->setObjectName(QString::fromUtf8("languageBox"));

        horizontalLayout->addWidget(languageBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout, 0, 2, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setWordWrap(true);

        gridLayout->addWidget(label_4, 10, 0, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setWordWrap(true);

        gridLayout->addWidget(label_6, 12, 0, 1, 1);

        cbUsageData = new QCheckBox(groupBox);
        cbUsageData->setObjectName(QString::fromUtf8("cbUsageData"));
        cbUsageData->setChecked(true);

        gridLayout->addWidget(cbUsageData, 15, 2, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 111, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(Core__Internal__GeneralSettings);

        QMetaObject::connectSlotsByName(Core__Internal__GeneralSettings);
    } // setupUi

    void retranslateUi(QWidget *Core__Internal__GeneralSettings)
    {
        groupBox->setTitle(QCoreApplication::translate("Core::Internal::GeneralSettings", "General settings", nullptr));
        label_3->setText(QCoreApplication::translate("Core::Internal::GeneralSettings", "Language:", nullptr));
        labelExpert->setText(QCoreApplication::translate("Core::Internal::GeneralSettings", "Expert Mode:", nullptr));
        cbUseUDPMirror->setText(QString());
        checkAutoSelect->setText(QString());
        label_5->setText(QCoreApplication::translate("Core::Internal::GeneralSettings", "Automatically connect an OpenPilot USB device:", nullptr));
        checkBoxSaveOnExit->setText(QString());
#if QT_CONFIG(tooltip)
        resetButton->setToolTip(QCoreApplication::translate("Core::Internal::GeneralSettings", "Reset to default", nullptr));
#endif // QT_CONFIG(tooltip)
        resetButton->setText(QCoreApplication::translate("Core::Internal::GeneralSettings", "R", nullptr));
        colorLabel->setText(QCoreApplication::translate("Core::Internal::GeneralSettings", "User interface color:", nullptr));
        labelExpert_2->setText(QCoreApplication::translate("Core::Internal::GeneralSettings", "Contribute usage statistics:", nullptr));
        cbExpertMode->setText(QString());
        checkAutoConnect->setText(QString());
        labelUDP->setText(QCoreApplication::translate("Core::Internal::GeneralSettings", "Use UDP Mirror:", nullptr));
        label_4->setText(QCoreApplication::translate("Core::Internal::GeneralSettings", "Save configuration settings on exit:", nullptr));
        label_6->setText(QCoreApplication::translate("Core::Internal::GeneralSettings", "Automatically select an OpenPilot USB device:", nullptr));
        cbUsageData->setText(QString());
        (void)Core__Internal__GeneralSettings;
    } // retranslateUi

};

} // namespace Internal
} // namespace Core

namespace Core {
namespace Internal {
namespace Ui {
    class GeneralSettings: public Ui_GeneralSettings {};
} // namespace Ui
} // namespace Internal
} // namespace Core

#endif // UI_GENERALSETTINGS_H
