/********************************************************************************
** Form generated from reading UI file 'importexportgadgetwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPORTEXPORTGADGETWIDGET_H
#define UI_IMPORTEXPORTGADGETWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImportExportGadgetWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBoxItems;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBoxGeneral;
    QCheckBox *checkBoxAllGadgets;
    QCheckBox *checkBoxPlugins;
    QHBoxLayout *horizontalLayout;
    QPushButton *helpButton;
    QPushButton *exportButton;
    QPushButton *importButton;
    QPushButton *resetButton;

    void setupUi(QWidget *ImportExportGadgetWidget)
    {
        if (ImportExportGadgetWidget->objectName().isEmpty())
            ImportExportGadgetWidget->setObjectName(QString::fromUtf8("ImportExportGadgetWidget"));
        ImportExportGadgetWidget->resize(483, 174);
        horizontalLayout_2 = new QHBoxLayout(ImportExportGadgetWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBoxItems = new QGroupBox(ImportExportGadgetWidget);
        groupBoxItems->setObjectName(QString::fromUtf8("groupBoxItems"));
        verticalLayout = new QVBoxLayout(groupBoxItems);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        checkBoxGeneral = new QCheckBox(groupBoxItems);
        checkBoxGeneral->setObjectName(QString::fromUtf8("checkBoxGeneral"));
        checkBoxGeneral->setChecked(true);

        verticalLayout->addWidget(checkBoxGeneral);

        checkBoxAllGadgets = new QCheckBox(groupBoxItems);
        checkBoxAllGadgets->setObjectName(QString::fromUtf8("checkBoxAllGadgets"));
        checkBoxAllGadgets->setChecked(true);

        verticalLayout->addWidget(checkBoxAllGadgets);

        checkBoxPlugins = new QCheckBox(groupBoxItems);
        checkBoxPlugins->setObjectName(QString::fromUtf8("checkBoxPlugins"));
        checkBoxPlugins->setChecked(true);

        verticalLayout->addWidget(checkBoxPlugins);


        verticalLayout_2->addWidget(groupBoxItems);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        helpButton = new QPushButton(ImportExportGadgetWidget);
        helpButton->setObjectName(QString::fromUtf8("helpButton"));
        helpButton->setMaximumSize(QSize(32, 32));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/core/images/helpicon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        helpButton->setIcon(icon);
        helpButton->setIconSize(QSize(32, 32));
        helpButton->setFlat(true);

        horizontalLayout->addWidget(helpButton);

        exportButton = new QPushButton(ImportExportGadgetWidget);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));

        horizontalLayout->addWidget(exportButton);

        importButton = new QPushButton(ImportExportGadgetWidget);
        importButton->setObjectName(QString::fromUtf8("importButton"));

        horizontalLayout->addWidget(importButton);

        resetButton = new QPushButton(ImportExportGadgetWidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));

        horizontalLayout->addWidget(resetButton);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);


        retranslateUi(ImportExportGadgetWidget);

        QMetaObject::connectSlotsByName(ImportExportGadgetWidget);
    } // setupUi

    void retranslateUi(QWidget *ImportExportGadgetWidget)
    {
        ImportExportGadgetWidget->setWindowTitle(QCoreApplication::translate("ImportExportGadgetWidget", "Form", nullptr));
        groupBoxItems->setTitle(QCoreApplication::translate("ImportExportGadgetWidget", "Items", nullptr));
        checkBoxGeneral->setText(QCoreApplication::translate("ImportExportGadgetWidget", "General (Workspace, Key-Bindings)", nullptr));
        checkBoxAllGadgets->setText(QCoreApplication::translate("ImportExportGadgetWidget", "All Gadgets", nullptr));
        checkBoxPlugins->setText(QCoreApplication::translate("ImportExportGadgetWidget", "Plugins", nullptr));
        helpButton->setText(QString());
#if QT_CONFIG(tooltip)
        exportButton->setToolTip(QCoreApplication::translate("ImportExportGadgetWidget", "Export the GCS settings selected in the checkboxes above.", nullptr));
#endif // QT_CONFIG(tooltip)
        exportButton->setText(QCoreApplication::translate("ImportExportGadgetWidget", "Export...", nullptr));
#if QT_CONFIG(tooltip)
        importButton->setToolTip(QCoreApplication::translate("ImportExportGadgetWidget", "Import settings from the config file, only for the items checked above.", nullptr));
#endif // QT_CONFIG(tooltip)
        importButton->setText(QCoreApplication::translate("ImportExportGadgetWidget", "Import...", nullptr));
#if QT_CONFIG(tooltip)
        resetButton->setToolTip(QCoreApplication::translate("ImportExportGadgetWidget", "Resets your GCS configuration to its default configuration.", nullptr));
#endif // QT_CONFIG(tooltip)
        resetButton->setText(QCoreApplication::translate("ImportExportGadgetWidget", "Reset Config", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImportExportGadgetWidget: public Ui_ImportExportGadgetWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORTEXPORTGADGETWIDGET_H
