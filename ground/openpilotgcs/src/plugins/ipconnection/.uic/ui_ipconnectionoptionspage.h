/********************************************************************************
** Form generated from reading UI file 'ipconnectionoptionspage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPCONNECTIONOPTIONSPAGE_H
#define UI_IPCONNECTIONOPTIONSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IPconnectionOptionsPage
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLineEdit *HostName;
    QLabel *label_3;
    QSpinBox *Port;
    QRadioButton *UseTCP;
    QRadioButton *UseUDP;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *IPconnectionOptionsPage)
    {
        if (IPconnectionOptionsPage->objectName().isEmpty())
            IPconnectionOptionsPage->setObjectName(QString::fromUtf8("IPconnectionOptionsPage"));
        IPconnectionOptionsPage->resize(429, 291);
        verticalLayout = new QVBoxLayout(IPconnectionOptionsPage);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(IPconnectionOptionsPage);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Plain);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 429, 125));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        HostName = new QLineEdit(groupBox);
        HostName->setObjectName(QString::fromUtf8("HostName"));

        gridLayout_2->addWidget(HostName, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 2, 1, 1);

        Port = new QSpinBox(groupBox);
        Port->setObjectName(QString::fromUtf8("Port"));
        Port->setMinimum(1);
        Port->setMaximum(999999);

        gridLayout_2->addWidget(Port, 1, 3, 1, 1);

        UseTCP = new QRadioButton(groupBox);
        UseTCP->setObjectName(QString::fromUtf8("UseTCP"));

        gridLayout_2->addWidget(UseTCP, 2, 0, 1, 1);

        UseUDP = new QRadioButton(groupBox);
        UseUDP->setObjectName(QString::fromUtf8("UseUDP"));

        gridLayout_2->addWidget(UseUDP, 2, 1, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(IPconnectionOptionsPage);

        QMetaObject::connectSlotsByName(IPconnectionOptionsPage);
    } // setupUi

    void retranslateUi(QWidget *IPconnectionOptionsPage)
    {
        IPconnectionOptionsPage->setWindowTitle(QCoreApplication::translate("IPconnectionOptionsPage", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("IPconnectionOptionsPage", "IP Network Telemetry", nullptr));
        label_2->setText(QCoreApplication::translate("IPconnectionOptionsPage", "Host Name/Number", nullptr));
        label_3->setText(QCoreApplication::translate("IPconnectionOptionsPage", "Port", nullptr));
        UseTCP->setText(QCoreApplication::translate("IPconnectionOptionsPage", "TCP connection", nullptr));
        UseUDP->setText(QCoreApplication::translate("IPconnectionOptionsPage", "UDP connection", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IPconnectionOptionsPage: public Ui_IPconnectionOptionsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPCONNECTIONOPTIONSPAGE_H
