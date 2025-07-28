/********************************************************************************
** Form generated from reading UI file 'workspacesettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKSPACESETTINGS_H
#define UI_WORKSPACESETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "utils/pathchooser.h"

namespace Core {
namespace Internal {

class Ui_WorkspaceSettings
{
public:
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLabel *label_6;
    QComboBox *comboBoxTabBarPlacement;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_7;
    QCheckBox *checkBoxAllowTabMovement;
    QLabel *label_8;
    QCheckBox *checkBoxRestoreSelectedOnStartup;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QSpinBox *numberOfWorkspacesSpinBox;
    QLabel *label_5;
    QComboBox *workspaceComboBox;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label_2;
    Utils::PathChooser *iconPathChooser;
    QLineEdit *nameEdit;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Core__Internal__WorkspaceSettings)
    {
        if (Core__Internal__WorkspaceSettings->objectName().isEmpty())
            Core__Internal__WorkspaceSettings->setObjectName(QString::fromUtf8("Core__Internal__WorkspaceSettings"));
        Core__Internal__WorkspaceSettings->resize(468, 436);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Core__Internal__WorkspaceSettings->sizePolicy().hasHeightForWidth());
        Core__Internal__WorkspaceSettings->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(Core__Internal__WorkspaceSettings);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scrollArea = new QScrollArea(Core__Internal__WorkspaceSettings);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Plain);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 468, 436));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);

        comboBoxTabBarPlacement = new QComboBox(groupBox_3);
        comboBoxTabBarPlacement->addItem(QString());
        comboBoxTabBarPlacement->addItem(QString());
        comboBoxTabBarPlacement->setObjectName(QString::fromUtf8("comboBoxTabBarPlacement"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBoxTabBarPlacement->sizePolicy().hasHeightForWidth());
        comboBoxTabBarPlacement->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(comboBoxTabBarPlacement, 1, 1, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 3, 1, 1);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_3->addWidget(label_7, 2, 0, 1, 1);

        checkBoxAllowTabMovement = new QCheckBox(groupBox_3);
        checkBoxAllowTabMovement->setObjectName(QString::fromUtf8("checkBoxAllowTabMovement"));

        gridLayout_3->addWidget(checkBoxAllowTabMovement, 2, 1, 1, 1);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_3->addWidget(label_8, 3, 0, 1, 1);

        checkBoxRestoreSelectedOnStartup = new QCheckBox(groupBox_3);
        checkBoxRestoreSelectedOnStartup->setObjectName(QString::fromUtf8("checkBoxRestoreSelectedOnStartup"));

        gridLayout_3->addWidget(checkBoxRestoreSelectedOnStartup, 3, 1, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        numberOfWorkspacesSpinBox = new QSpinBox(groupBox);
        numberOfWorkspacesSpinBox->setObjectName(QString::fromUtf8("numberOfWorkspacesSpinBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(numberOfWorkspacesSpinBox->sizePolicy().hasHeightForWidth());
        numberOfWorkspacesSpinBox->setSizePolicy(sizePolicy2);
        numberOfWorkspacesSpinBox->setMinimum(1);
        numberOfWorkspacesSpinBox->setMaximum(10);
        numberOfWorkspacesSpinBox->setValue(2);

        gridLayout_2->addWidget(numberOfWorkspacesSpinBox, 0, 2, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        workspaceComboBox = new QComboBox(groupBox);
        workspaceComboBox->setObjectName(QString::fromUtf8("workspaceComboBox"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(workspaceComboBox->sizePolicy().hasHeightForWidth());
        workspaceComboBox->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(workspaceComboBox, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 3, 1, 1);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        iconPathChooser = new Utils::PathChooser(groupBox_2);
        iconPathChooser->setObjectName(QString::fromUtf8("iconPathChooser"));

        gridLayout->addWidget(iconPathChooser, 2, 1, 1, 1);

        nameEdit = new QLineEdit(groupBox_2);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        gridLayout->addWidget(nameEdit, 3, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 3, 0, 1, 4);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);


        retranslateUi(Core__Internal__WorkspaceSettings);

        comboBoxTabBarPlacement->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Core__Internal__WorkspaceSettings);
    } // setupUi

    void retranslateUi(QWidget *Core__Internal__WorkspaceSettings)
    {
        Core__Internal__WorkspaceSettings->setWindowTitle(QCoreApplication::translate("Core::Internal::WorkspaceSettings", "Form", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Core::Internal::WorkspaceSettings", "General", nullptr));
        label_6->setText(QCoreApplication::translate("Core::Internal::WorkspaceSettings", "Placement:", nullptr));
        comboBoxTabBarPlacement->setItemText(0, QCoreApplication::translate("Core::Internal::WorkspaceSettings", "Top", nullptr));
        comboBoxTabBarPlacement->setItemText(1, QCoreApplication::translate("Core::Internal::WorkspaceSettings", "Bottom", nullptr));

        label_7->setText(QCoreApplication::translate("Core::Internal::WorkspaceSettings", "Allow reordering:", nullptr));
        checkBoxAllowTabMovement->setText(QString());
#if QT_CONFIG(tooltip)
        label_8->setToolTip(QCoreApplication::translate("Core::Internal::WorkspaceSettings", "Restore last selected workspace on startup", nullptr));
#endif // QT_CONFIG(tooltip)
        label_8->setText(QCoreApplication::translate("Core::Internal::WorkspaceSettings", "Remember last used workspace on restart", nullptr));
        checkBoxRestoreSelectedOnStartup->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("Core::Internal::WorkspaceSettings", "Workspaces", nullptr));
        label->setText(QCoreApplication::translate("Core::Internal::WorkspaceSettings", "Number of workspaces:", nullptr));
        label_5->setText(QCoreApplication::translate("Core::Internal::WorkspaceSettings", "Change details of workspace:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Core::Internal::WorkspaceSettings", "Details", nullptr));
        label_2->setText(QCoreApplication::translate("Core::Internal::WorkspaceSettings", "Icon:", nullptr));
        label_3->setText(QCoreApplication::translate("Core::Internal::WorkspaceSettings", "Name:", nullptr));
    } // retranslateUi

};

} // namespace Internal
} // namespace Core

namespace Core {
namespace Internal {
namespace Ui {
    class WorkspaceSettings: public Ui_WorkspaceSettings {};
} // namespace Ui
} // namespace Internal
} // namespace Core

#endif // UI_WORKSPACESETTINGS_H
