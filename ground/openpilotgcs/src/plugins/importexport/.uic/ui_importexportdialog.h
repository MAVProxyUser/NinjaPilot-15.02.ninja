/********************************************************************************
** Form generated from reading UI file 'importexportdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPORTEXPORTDIALOG_H
#define UI_IMPORTEXPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QVBoxLayout>
#include "importexportgadgetwidget.h"

QT_BEGIN_NAMESPACE

class Ui_ImportExportDialog
{
public:
    QVBoxLayout *verticalLayout;
    ImportExportGadgetWidget *widget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ImportExportDialog)
    {
        if (ImportExportDialog->objectName().isEmpty())
            ImportExportDialog->setObjectName(QString::fromUtf8("ImportExportDialog"));
        ImportExportDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(ImportExportDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new ImportExportGadgetWidget(ImportExportDialog);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout->addWidget(widget);

        buttonBox = new QDialogButtonBox(ImportExportDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ImportExportDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ImportExportDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ImportExportDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ImportExportDialog);
    } // setupUi

    void retranslateUi(QDialog *ImportExportDialog)
    {
        ImportExportDialog->setWindowTitle(QCoreApplication::translate("ImportExportDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImportExportDialog: public Ui_ImportExportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORTEXPORTDIALOG_H
