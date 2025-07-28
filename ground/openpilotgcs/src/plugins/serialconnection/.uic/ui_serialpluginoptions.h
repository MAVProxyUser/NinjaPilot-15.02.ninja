/********************************************************************************
** Form generated from reading UI file 'serialpluginoptions.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALPLUGINOPTIONS_H
#define UI_SERIALPLUGINOPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SerialPluginOptionsPage
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *cb_speed;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SerialPluginOptionsPage)
    {
        if (SerialPluginOptionsPage->objectName().isEmpty())
            SerialPluginOptionsPage->setObjectName(QString::fromUtf8("SerialPluginOptionsPage"));
        SerialPluginOptionsPage->resize(400, 300);
        verticalLayout = new QVBoxLayout(SerialPluginOptionsPage);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(SerialPluginOptionsPage);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cb_speed = new QComboBox(groupBox);
        cb_speed->setObjectName(QString::fromUtf8("cb_speed"));

        gridLayout->addWidget(cb_speed, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(76, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(SerialPluginOptionsPage);

        QMetaObject::connectSlotsByName(SerialPluginOptionsPage);
    } // setupUi

    void retranslateUi(QWidget *SerialPluginOptionsPage)
    {
        SerialPluginOptionsPage->setWindowTitle(QCoreApplication::translate("SerialPluginOptionsPage", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SerialPluginOptionsPage", "Serial Connection", nullptr));
        label->setText(QCoreApplication::translate("SerialPluginOptionsPage", "Serial telemetry speed:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SerialPluginOptionsPage: public Ui_SerialPluginOptionsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALPLUGINOPTIONS_H
