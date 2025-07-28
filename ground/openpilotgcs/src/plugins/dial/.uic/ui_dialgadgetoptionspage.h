/********************************************************************************
** Form generated from reading UI file 'dialgadgetoptionspage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALGADGETOPTIONSPAGE_H
#define UI_DIALGADGETOPTIONSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "utils/pathchooser.h"

QT_BEGIN_NAMESPACE

class Ui_DialGadgetOptionsPage
{
public:
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    Utils::PathChooser *svgSourceFile;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_28;
    QPushButton *fontPicker;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *backgroundID;
    QLabel *label_3;
    QLineEdit *foregroundID;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_12;
    QComboBox *moveNeedle1;
    QLabel *label_5;
    QLineEdit *needle1ID;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QDoubleSpinBox *needle1Min;
    QLabel *label_7;
    QDoubleSpinBox *needle1Max;
    QLabel *label_10;
    QDoubleSpinBox *factor1;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_8;
    QComboBox *uavObject1;
    QLabel *label_9;
    QComboBox *objectField1;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_13;
    QComboBox *moveNeedle2;
    QLabel *label_17;
    QLineEdit *needle2ID;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_18;
    QDoubleSpinBox *needle2Min;
    QLabel *label_19;
    QDoubleSpinBox *needle2Max;
    QLabel *label_11;
    QDoubleSpinBox *factor2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_20;
    QComboBox *uavObject2;
    QLabel *label_21;
    QComboBox *objectField2;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_14;
    QComboBox *moveNeedle3;
    QLabel *label_23;
    QLineEdit *needle3ID;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_24;
    QDoubleSpinBox *needle3Min;
    QLabel *label_25;
    QDoubleSpinBox *needle3Max;
    QLabel *label_15;
    QDoubleSpinBox *factor3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_26;
    QComboBox *uavObject3;
    QLabel *label_27;
    QComboBox *objectField3;
    QHBoxLayout *horizontalLayout_12;
    QCheckBox *useOpenGL;
    QCheckBox *smoothUpdates;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *DialGadgetOptionsPage)
    {
        if (DialGadgetOptionsPage->objectName().isEmpty())
            DialGadgetOptionsPage->setObjectName(QString::fromUtf8("DialGadgetOptionsPage"));
        DialGadgetOptionsPage->resize(561, 392);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialGadgetOptionsPage->sizePolicy().hasHeightForWidth());
        DialGadgetOptionsPage->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(DialGadgetOptionsPage);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scrollArea = new QScrollArea(DialGadgetOptionsPage);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Plain);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 561, 392));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout->setContentsMargins(-1, -1, -1, 0);
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label);

        svgSourceFile = new Utils::PathChooser(scrollAreaWidgetContents);
        svgSourceFile->setObjectName(QString::fromUtf8("svgSourceFile"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(svgSourceFile->sizePolicy().hasHeightForWidth());
        svgSourceFile->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(svgSourceFile);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(-1, -1, -1, 0);
        label_28 = new QLabel(scrollAreaWidgetContents);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        sizePolicy1.setHeightForWidth(label_28->sizePolicy().hasHeightForWidth());
        label_28->setSizePolicy(sizePolicy1);

        horizontalLayout_13->addWidget(label_28);

        fontPicker = new QPushButton(scrollAreaWidgetContents);
        fontPicker->setObjectName(QString::fromUtf8("fontPicker"));

        horizontalLayout_13->addWidget(fontPicker);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        backgroundID = new QLineEdit(scrollAreaWidgetContents);
        backgroundID->setObjectName(QString::fromUtf8("backgroundID"));

        horizontalLayout_2->addWidget(backgroundID);

        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        foregroundID = new QLineEdit(scrollAreaWidgetContents);
        foregroundID->setObjectName(QString::fromUtf8("foregroundID"));

        horizontalLayout_2->addWidget(foregroundID);


        verticalLayout->addLayout(horizontalLayout_2);

        tabWidget = new QTabWidget(scrollAreaWidgetContents);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy3);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_3 = new QVBoxLayout(tab);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_12 = new QLabel(tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_5->addWidget(label_12);

        moveNeedle1 = new QComboBox(tab);
        moveNeedle1->setObjectName(QString::fromUtf8("moveNeedle1"));

        horizontalLayout_5->addWidget(moveNeedle1);

        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        needle1ID = new QLineEdit(tab);
        needle1ID->setObjectName(QString::fromUtf8("needle1ID"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(needle1ID->sizePolicy().hasHeightForWidth());
        needle1ID->setSizePolicy(sizePolicy4);
        needle1ID->setMinimumSize(QSize(50, 0));
        needle1ID->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_5->addWidget(needle1ID);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, -1);
        label_6 = new QLabel(tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_3->addWidget(label_6);

        needle1Min = new QDoubleSpinBox(tab);
        needle1Min->setObjectName(QString::fromUtf8("needle1Min"));
        sizePolicy4.setHeightForWidth(needle1Min->sizePolicy().hasHeightForWidth());
        needle1Min->setSizePolicy(sizePolicy4);
        needle1Min->setDecimals(3);
        needle1Min->setMinimum(-100000.000000000000000);
        needle1Min->setMaximum(100000.000000000000000);

        horizontalLayout_3->addWidget(needle1Min);

        label_7 = new QLabel(tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_3->addWidget(label_7);

        needle1Max = new QDoubleSpinBox(tab);
        needle1Max->setObjectName(QString::fromUtf8("needle1Max"));
        sizePolicy4.setHeightForWidth(needle1Max->sizePolicy().hasHeightForWidth());
        needle1Max->setSizePolicy(sizePolicy4);
        needle1Max->setDecimals(3);
        needle1Max->setMinimum(-100000.000000000000000);
        needle1Max->setMaximum(100000.000000000000000);

        horizontalLayout_3->addWidget(needle1Max);

        label_10 = new QLabel(tab);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_3->addWidget(label_10);

        factor1 = new QDoubleSpinBox(tab);
        factor1->setObjectName(QString::fromUtf8("factor1"));
        sizePolicy4.setHeightForWidth(factor1->sizePolicy().hasHeightForWidth());
        factor1->setSizePolicy(sizePolicy4);
        factor1->setDecimals(5);
        factor1->setMinimum(-100000.000000000000000);
        factor1->setMaximum(100000.000000000000000);

        horizontalLayout_3->addWidget(factor1);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        label_8 = new QLabel(tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_4->addWidget(label_8);

        uavObject1 = new QComboBox(tab);
        uavObject1->setObjectName(QString::fromUtf8("uavObject1"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(uavObject1->sizePolicy().hasHeightForWidth());
        uavObject1->setSizePolicy(sizePolicy5);

        horizontalLayout_4->addWidget(uavObject1);

        label_9 = new QLabel(tab);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_4->addWidget(label_9);

        objectField1 = new QComboBox(tab);
        objectField1->setObjectName(QString::fromUtf8("objectField1"));
        sizePolicy5.setHeightForWidth(objectField1->sizePolicy().hasHeightForWidth());
        objectField1->setSizePolicy(sizePolicy5);

        horizontalLayout_4->addWidget(objectField1);


        verticalLayout_3->addLayout(horizontalLayout_4);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_6 = new QVBoxLayout(tab_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_13 = new QLabel(tab_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_6->addWidget(label_13);

        moveNeedle2 = new QComboBox(tab_2);
        moveNeedle2->setObjectName(QString::fromUtf8("moveNeedle2"));

        horizontalLayout_6->addWidget(moveNeedle2);

        label_17 = new QLabel(tab_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        horizontalLayout_6->addWidget(label_17);

        needle2ID = new QLineEdit(tab_2);
        needle2ID->setObjectName(QString::fromUtf8("needle2ID"));
        sizePolicy4.setHeightForWidth(needle2ID->sizePolicy().hasHeightForWidth());
        needle2ID->setSizePolicy(sizePolicy4);

        horizontalLayout_6->addWidget(needle2ID);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout_6->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(-1, 0, -1, -1);
        label_18 = new QLabel(tab_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout_7->addWidget(label_18);

        needle2Min = new QDoubleSpinBox(tab_2);
        needle2Min->setObjectName(QString::fromUtf8("needle2Min"));
        sizePolicy4.setHeightForWidth(needle2Min->sizePolicy().hasHeightForWidth());
        needle2Min->setSizePolicy(sizePolicy4);
        needle2Min->setDecimals(3);
        needle2Min->setMinimum(-10000.000000000000000);
        needle2Min->setMaximum(100000.000000000000000);

        horizontalLayout_7->addWidget(needle2Min);

        label_19 = new QLabel(tab_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        horizontalLayout_7->addWidget(label_19);

        needle2Max = new QDoubleSpinBox(tab_2);
        needle2Max->setObjectName(QString::fromUtf8("needle2Max"));
        sizePolicy4.setHeightForWidth(needle2Max->sizePolicy().hasHeightForWidth());
        needle2Max->setSizePolicy(sizePolicy4);
        needle2Max->setDecimals(3);
        needle2Max->setMinimum(-100000.000000000000000);
        needle2Max->setMaximum(100000.000000000000000);

        horizontalLayout_7->addWidget(needle2Max);

        label_11 = new QLabel(tab_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_7->addWidget(label_11);

        factor2 = new QDoubleSpinBox(tab_2);
        factor2->setObjectName(QString::fromUtf8("factor2"));
        sizePolicy4.setHeightForWidth(factor2->sizePolicy().hasHeightForWidth());
        factor2->setSizePolicy(sizePolicy4);
        factor2->setDecimals(5);
        factor2->setMinimum(-100000.000000000000000);
        factor2->setMaximum(100000.000000000000000);

        horizontalLayout_7->addWidget(factor2);


        verticalLayout_6->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, 0, -1, -1);
        label_20 = new QLabel(tab_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        horizontalLayout_8->addWidget(label_20);

        uavObject2 = new QComboBox(tab_2);
        uavObject2->setObjectName(QString::fromUtf8("uavObject2"));
        sizePolicy5.setHeightForWidth(uavObject2->sizePolicy().hasHeightForWidth());
        uavObject2->setSizePolicy(sizePolicy5);

        horizontalLayout_8->addWidget(uavObject2);

        label_21 = new QLabel(tab_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        horizontalLayout_8->addWidget(label_21);

        objectField2 = new QComboBox(tab_2);
        objectField2->setObjectName(QString::fromUtf8("objectField2"));
        sizePolicy5.setHeightForWidth(objectField2->sizePolicy().hasHeightForWidth());
        objectField2->setSizePolicy(sizePolicy5);

        horizontalLayout_8->addWidget(objectField2);


        verticalLayout_6->addLayout(horizontalLayout_8);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_7 = new QVBoxLayout(tab_3);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_14 = new QLabel(tab_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_9->addWidget(label_14);

        moveNeedle3 = new QComboBox(tab_3);
        moveNeedle3->setObjectName(QString::fromUtf8("moveNeedle3"));

        horizontalLayout_9->addWidget(moveNeedle3);

        label_23 = new QLabel(tab_3);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        horizontalLayout_9->addWidget(label_23);

        needle3ID = new QLineEdit(tab_3);
        needle3ID->setObjectName(QString::fromUtf8("needle3ID"));
        sizePolicy4.setHeightForWidth(needle3ID->sizePolicy().hasHeightForWidth());
        needle3ID->setSizePolicy(sizePolicy4);

        horizontalLayout_9->addWidget(needle3ID);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);


        verticalLayout_7->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(-1, 0, -1, -1);
        label_24 = new QLabel(tab_3);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        horizontalLayout_10->addWidget(label_24);

        needle3Min = new QDoubleSpinBox(tab_3);
        needle3Min->setObjectName(QString::fromUtf8("needle3Min"));
        sizePolicy4.setHeightForWidth(needle3Min->sizePolicy().hasHeightForWidth());
        needle3Min->setSizePolicy(sizePolicy4);
        needle3Min->setDecimals(3);
        needle3Min->setMinimum(-10000.000000000000000);
        needle3Min->setMaximum(100000.000000000000000);

        horizontalLayout_10->addWidget(needle3Min);

        label_25 = new QLabel(tab_3);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        horizontalLayout_10->addWidget(label_25);

        needle3Max = new QDoubleSpinBox(tab_3);
        needle3Max->setObjectName(QString::fromUtf8("needle3Max"));
        sizePolicy4.setHeightForWidth(needle3Max->sizePolicy().hasHeightForWidth());
        needle3Max->setSizePolicy(sizePolicy4);
        needle3Max->setDecimals(3);
        needle3Max->setMinimum(-100000.000000000000000);
        needle3Max->setMaximum(100000.000000000000000);

        horizontalLayout_10->addWidget(needle3Max);

        label_15 = new QLabel(tab_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_10->addWidget(label_15);

        factor3 = new QDoubleSpinBox(tab_3);
        factor3->setObjectName(QString::fromUtf8("factor3"));
        sizePolicy4.setHeightForWidth(factor3->sizePolicy().hasHeightForWidth());
        factor3->setSizePolicy(sizePolicy4);
        factor3->setDecimals(5);
        factor3->setMinimum(-100000.000000000000000);
        factor3->setMaximum(100000.000000000000000);

        horizontalLayout_10->addWidget(factor3);


        verticalLayout_7->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(-1, 0, -1, -1);
        label_26 = new QLabel(tab_3);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        horizontalLayout_11->addWidget(label_26);

        uavObject3 = new QComboBox(tab_3);
        uavObject3->setObjectName(QString::fromUtf8("uavObject3"));
        sizePolicy5.setHeightForWidth(uavObject3->sizePolicy().hasHeightForWidth());
        uavObject3->setSizePolicy(sizePolicy5);

        horizontalLayout_11->addWidget(uavObject3);

        label_27 = new QLabel(tab_3);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        horizontalLayout_11->addWidget(label_27);

        objectField3 = new QComboBox(tab_3);
        objectField3->setObjectName(QString::fromUtf8("objectField3"));
        sizePolicy5.setHeightForWidth(objectField3->sizePolicy().hasHeightForWidth());
        objectField3->setSizePolicy(sizePolicy5);

        horizontalLayout_11->addWidget(objectField3);


        verticalLayout_7->addLayout(horizontalLayout_11);

        tabWidget->addTab(tab_3, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        useOpenGL = new QCheckBox(scrollAreaWidgetContents);
        useOpenGL->setObjectName(QString::fromUtf8("useOpenGL"));

        horizontalLayout_12->addWidget(useOpenGL);

        smoothUpdates = new QCheckBox(scrollAreaWidgetContents);
        smoothUpdates->setObjectName(QString::fromUtf8("smoothUpdates"));

        horizontalLayout_12->addWidget(smoothUpdates);


        verticalLayout->addLayout(horizontalLayout_12);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);


        retranslateUi(DialGadgetOptionsPage);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DialGadgetOptionsPage);
    } // setupUi

    void retranslateUi(QWidget *DialGadgetOptionsPage)
    {
        DialGadgetOptionsPage->setWindowTitle(QCoreApplication::translate("DialGadgetOptionsPage", "Form", nullptr));
        label->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Dial SVG: ", nullptr));
        label_28->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Dial font:", nullptr));
        fontPicker->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Select...", nullptr));
        label_2->setText(QCoreApplication::translate("DialGadgetOptionsPage", "BackgroundID", nullptr));
#if QT_CONFIG(tooltip)
        backgroundID->setToolTip(QCoreApplication::translate("DialGadgetOptionsPage", "XML ID of the SVG source file used to display the dial background.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_3->setText(QCoreApplication::translate("DialGadgetOptionsPage", "ForegroundID", nullptr));
#if QT_CONFIG(tooltip)
        foregroundID->setToolTip(QCoreApplication::translate("DialGadgetOptionsPage", "XML ID of the SVG source file used to display the dial foreground (above everything else, needles included).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_12->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Movement:", nullptr));
        label_5->setText(QCoreApplication::translate("DialGadgetOptionsPage", "ID:", nullptr));
#if QT_CONFIG(tooltip)
        needle1ID->setToolTip(QCoreApplication::translate("DialGadgetOptionsPage", "XML ID of the SVG source file used to display the first needle/indicator.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_6->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Min:", nullptr));
        label_7->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Max:", nullptr));
        label_10->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Factor:", nullptr));
        label_8->setText(QCoreApplication::translate("DialGadgetOptionsPage", "DataObject", nullptr));
        label_9->setText(QCoreApplication::translate("DialGadgetOptionsPage", "ObjectField", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("DialGadgetOptionsPage", "Indicator 1", nullptr));
        label_13->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Movement:", nullptr));
        label_17->setText(QCoreApplication::translate("DialGadgetOptionsPage", "ID:", nullptr));
        label_18->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Min:", nullptr));
        label_19->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Max:", nullptr));
        label_11->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Factor:", nullptr));
        label_20->setText(QCoreApplication::translate("DialGadgetOptionsPage", "DataObject", nullptr));
        label_21->setText(QCoreApplication::translate("DialGadgetOptionsPage", "ObjectField", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("DialGadgetOptionsPage", "Indicator 2", nullptr));
        label_14->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Movement:", nullptr));
        label_23->setText(QCoreApplication::translate("DialGadgetOptionsPage", "ID:", nullptr));
        label_24->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Min:", nullptr));
        label_25->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Max:", nullptr));
        label_15->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Factor:", nullptr));
        label_26->setText(QCoreApplication::translate("DialGadgetOptionsPage", "DataObject", nullptr));
        label_27->setText(QCoreApplication::translate("DialGadgetOptionsPage", "ObjectField", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("DialGadgetOptionsPage", "Indicator 3", nullptr));
#if QT_CONFIG(tooltip)
        useOpenGL->setToolTip(QCoreApplication::translate("DialGadgetOptionsPage", "Use OpenGL for rendering. Will lower CPU usage, depending on the capabilities of your graphics card, but might slightly alter the look & feel of the dial.", nullptr));
#endif // QT_CONFIG(tooltip)
        useOpenGL->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Use OpenGL", nullptr));
#if QT_CONFIG(tooltip)
        smoothUpdates->setToolTip(QCoreApplication::translate("DialGadgetOptionsPage", "When checked, the Dial plugin will make needle moves smoother by simulating inertia.", nullptr));
#endif // QT_CONFIG(tooltip)
        smoothUpdates->setText(QCoreApplication::translate("DialGadgetOptionsPage", "Smooth updates", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialGadgetOptionsPage: public Ui_DialGadgetOptionsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALGADGETOPTIONSPAGE_H
