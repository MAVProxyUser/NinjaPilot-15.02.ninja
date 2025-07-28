/********************************************************************************
** Form generated from reading UI file 'uavgadgetoptionspage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UAVGADGETOPTIONSPAGE_H
#define UI_UAVGADGETOPTIONSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TopOptionsPage
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *configurationBox;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *nameLineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *cloneButton;
    QPushButton *deleteButton;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *lockCheckBox;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *settingsBox;
    QVBoxLayout *verticalLayout_4;

    void setupUi(QWidget *TopOptionsPage)
    {
        if (TopOptionsPage->objectName().isEmpty())
            TopOptionsPage->setObjectName(QString::fromUtf8("TopOptionsPage"));
        TopOptionsPage->resize(555, 311);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TopOptionsPage->sizePolicy().hasHeightForWidth());
        TopOptionsPage->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(TopOptionsPage);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        configurationBox = new QGroupBox(TopOptionsPage);
        configurationBox->setObjectName(QString::fromUtf8("configurationBox"));
        verticalLayout_2 = new QVBoxLayout(configurationBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        nameLineEdit = new QLineEdit(configurationBox);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(nameLineEdit->sizePolicy().hasHeightForWidth());
        nameLineEdit->setSizePolicy(sizePolicy1);
        nameLineEdit->setMaxLength(50);

        verticalLayout_2->addWidget(nameLineEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cloneButton = new QPushButton(configurationBox);
        cloneButton->setObjectName(QString::fromUtf8("cloneButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cloneButton->sizePolicy().hasHeightForWidth());
        cloneButton->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(cloneButton);

        deleteButton = new QPushButton(configurationBox);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        sizePolicy2.setHeightForWidth(deleteButton->sizePolicy().hasHeightForWidth());
        deleteButton->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(deleteButton);

        horizontalSpacer_2 = new QSpacerItem(20, 9, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        lockCheckBox = new QCheckBox(configurationBox);
        lockCheckBox->setObjectName(QString::fromUtf8("lockCheckBox"));

        horizontalLayout->addWidget(lockCheckBox);

        horizontalSpacer_3 = new QSpacerItem(100, 9, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(configurationBox);

        settingsBox = new QGroupBox(TopOptionsPage);
        settingsBox->setObjectName(QString::fromUtf8("settingsBox"));
        verticalLayout_4 = new QVBoxLayout(settingsBox);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));

        verticalLayout->addWidget(settingsBox);


        retranslateUi(TopOptionsPage);

        QMetaObject::connectSlotsByName(TopOptionsPage);
    } // setupUi

    void retranslateUi(QWidget *TopOptionsPage)
    {
        TopOptionsPage->setWindowTitle(QString());
        configurationBox->setTitle(QCoreApplication::translate("TopOptionsPage", "Configuration", nullptr));
        nameLineEdit->setText(QString());
        cloneButton->setText(QCoreApplication::translate("TopOptionsPage", "Clone", nullptr));
        deleteButton->setText(QCoreApplication::translate("TopOptionsPage", "Delete", nullptr));
        lockCheckBox->setText(QCoreApplication::translate("TopOptionsPage", "Lock", nullptr));
        settingsBox->setTitle(QCoreApplication::translate("TopOptionsPage", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TopOptionsPage: public Ui_TopOptionsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UAVGADGETOPTIONSPAGE_H
