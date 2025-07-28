/********************************************************************************
** Form generated from reading UI file 'uavobjectbrowseroptionspage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UAVOBJECTBROWSEROPTIONSPAGE_H
#define UI_UAVOBJECTBROWSEROPTIONSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "utils/qtcolorbutton.h"

QT_BEGIN_NAMESPACE

class Ui_UAVObjectBrowserOptionsPage
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    Utils::QtColorButton *recentlyUpdatedButton;
    QLabel *label_3;
    QCheckBox *hilightBox;
    QSpinBox *recentlyUpdatedTimeoutSpinBox;
    Utils::QtColorButton *manuallyChangedButton;
    QLabel *label_2;
    QLabel *label_4;
    Utils::QtColorButton *unknownButton;

    void setupUi(QWidget *UAVObjectBrowserOptionsPage)
    {
        if (UAVObjectBrowserOptionsPage->objectName().isEmpty())
            UAVObjectBrowserOptionsPage->setObjectName(QString::fromUtf8("UAVObjectBrowserOptionsPage"));
        UAVObjectBrowserOptionsPage->resize(482, 194);
        verticalLayout = new QVBoxLayout(UAVObjectBrowserOptionsPage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(UAVObjectBrowserOptionsPage);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Plain);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 507, 178));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        recentlyUpdatedButton = new Utils::QtColorButton(scrollAreaWidgetContents);
        recentlyUpdatedButton->setObjectName(QString::fromUtf8("recentlyUpdatedButton"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(recentlyUpdatedButton->sizePolicy().hasHeightForWidth());
        recentlyUpdatedButton->setSizePolicy(sizePolicy);
        recentlyUpdatedButton->setMinimumSize(QSize(64, 0));

        gridLayout->addWidget(recentlyUpdatedButton, 0, 1, 1, 1);

        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        hilightBox = new QCheckBox(scrollAreaWidgetContents);
        hilightBox->setObjectName(QString::fromUtf8("hilightBox"));

        gridLayout->addWidget(hilightBox, 5, 0, 1, 1);

        recentlyUpdatedTimeoutSpinBox = new QSpinBox(scrollAreaWidgetContents);
        recentlyUpdatedTimeoutSpinBox->setObjectName(QString::fromUtf8("recentlyUpdatedTimeoutSpinBox"));
        sizePolicy.setHeightForWidth(recentlyUpdatedTimeoutSpinBox->sizePolicy().hasHeightForWidth());
        recentlyUpdatedTimeoutSpinBox->setSizePolicy(sizePolicy);
        recentlyUpdatedTimeoutSpinBox->setMaximum(100000000);
        recentlyUpdatedTimeoutSpinBox->setSingleStep(100);

        gridLayout->addWidget(recentlyUpdatedTimeoutSpinBox, 4, 1, 1, 1);

        manuallyChangedButton = new Utils::QtColorButton(scrollAreaWidgetContents);
        manuallyChangedButton->setObjectName(QString::fromUtf8("manuallyChangedButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(manuallyChangedButton->sizePolicy().hasHeightForWidth());
        manuallyChangedButton->setSizePolicy(sizePolicy1);
        manuallyChangedButton->setMinimumSize(QSize(64, 0));

        gridLayout->addWidget(manuallyChangedButton, 1, 1, 1, 1);

        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        unknownButton = new Utils::QtColorButton(scrollAreaWidgetContents);
        unknownButton->setObjectName(QString::fromUtf8("unknownButton"));
        sizePolicy1.setHeightForWidth(unknownButton->sizePolicy().hasHeightForWidth());
        unknownButton->setSizePolicy(sizePolicy1);
        unknownButton->setMinimumSize(QSize(64, 0));

        gridLayout->addWidget(unknownButton, 3, 1, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        QWidget::setTabOrder(scrollArea, recentlyUpdatedButton);
        QWidget::setTabOrder(recentlyUpdatedButton, manuallyChangedButton);
        QWidget::setTabOrder(manuallyChangedButton, unknownButton);
        QWidget::setTabOrder(unknownButton, recentlyUpdatedTimeoutSpinBox);
        QWidget::setTabOrder(recentlyUpdatedTimeoutSpinBox, hilightBox);

        retranslateUi(UAVObjectBrowserOptionsPage);

        QMetaObject::connectSlotsByName(UAVObjectBrowserOptionsPage);
    } // setupUi

    void retranslateUi(QWidget *UAVObjectBrowserOptionsPage)
    {
        UAVObjectBrowserOptionsPage->setWindowTitle(QCoreApplication::translate("UAVObjectBrowserOptionsPage", "Form", nullptr));
        label->setText(QCoreApplication::translate("UAVObjectBrowserOptionsPage", "Recently updated color:", nullptr));
        recentlyUpdatedButton->setText(QString());
        label_3->setText(QCoreApplication::translate("UAVObjectBrowserOptionsPage", "Recently updated timeout (ms):", nullptr));
        hilightBox->setText(QCoreApplication::translate("UAVObjectBrowserOptionsPage", "Only highlight nodes when value actually changes", nullptr));
        manuallyChangedButton->setText(QString());
        label_2->setText(QCoreApplication::translate("UAVObjectBrowserOptionsPage", "Manually changed color:", nullptr));
        label_4->setText(QCoreApplication::translate("UAVObjectBrowserOptionsPage", "Unknown object color:", nullptr));
        unknownButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UAVObjectBrowserOptionsPage: public Ui_UAVObjectBrowserOptionsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UAVOBJECTBROWSEROPTIONSPAGE_H
