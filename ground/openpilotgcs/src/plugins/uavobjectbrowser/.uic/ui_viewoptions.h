/********************************************************************************
** Form generated from reading UI file 'viewoptions.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWOPTIONS_H
#define UI_VIEWOPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_viewoptions
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *cbMetaData;
    QCheckBox *cbCategorized;
    QCheckBox *cbScientific;
    QCheckBox *cbDescription;

    void setupUi(QDialog *viewoptions)
    {
        if (viewoptions->objectName().isEmpty())
            viewoptions->setObjectName(QString::fromUtf8("viewoptions"));
        viewoptions->resize(172, 124);
        verticalLayout = new QVBoxLayout(viewoptions);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        cbMetaData = new QCheckBox(viewoptions);
        cbMetaData->setObjectName(QString::fromUtf8("cbMetaData"));

        verticalLayout->addWidget(cbMetaData);

        cbCategorized = new QCheckBox(viewoptions);
        cbCategorized->setObjectName(QString::fromUtf8("cbCategorized"));

        verticalLayout->addWidget(cbCategorized);

        cbScientific = new QCheckBox(viewoptions);
        cbScientific->setObjectName(QString::fromUtf8("cbScientific"));

        verticalLayout->addWidget(cbScientific);

        cbDescription = new QCheckBox(viewoptions);
        cbDescription->setObjectName(QString::fromUtf8("cbDescription"));

        verticalLayout->addWidget(cbDescription);


        retranslateUi(viewoptions);

        QMetaObject::connectSlotsByName(viewoptions);
    } // setupUi

    void retranslateUi(QDialog *viewoptions)
    {
        viewoptions->setWindowTitle(QCoreApplication::translate("viewoptions", "View Options", nullptr));
        cbMetaData->setText(QCoreApplication::translate("viewoptions", "Show MetaData", nullptr));
        cbCategorized->setText(QCoreApplication::translate("viewoptions", "Show Categorized", nullptr));
        cbScientific->setText(QCoreApplication::translate("viewoptions", "Show Scientific", nullptr));
        cbDescription->setText(QCoreApplication::translate("viewoptions", "Show Description", nullptr));
    } // retranslateUi

};

namespace Ui {
    class viewoptions: public Ui_viewoptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWOPTIONS_H
