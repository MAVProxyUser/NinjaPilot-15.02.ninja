/********************************************************************************
** Form generated from reading UI file 'filewizardpage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEWIZARDPAGE_H
#define UI_FILEWIZARDPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWizardPage>
#include "filenamevalidatinglineedit.h"
#include "pathchooser.h"

namespace Utils {

class Ui_WizardPage
{
public:
    QFormLayout *formLayout;
    QLabel *nameLabel;
    Utils::FileNameValidatingLineEdit *nameLineEdit;
    QLabel *pathLabel;
    Utils::PathChooser *pathChooser;

    void setupUi(QWizardPage *Utils__WizardPage)
    {
        if (Utils__WizardPage->objectName().isEmpty())
            Utils__WizardPage->setObjectName(QString::fromUtf8("Utils__WizardPage"));
        Utils__WizardPage->resize(196, 68);
        formLayout = new QFormLayout(Utils__WizardPage);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        nameLabel = new QLabel(Utils__WizardPage);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, nameLabel);

        nameLineEdit = new Utils::FileNameValidatingLineEdit(Utils__WizardPage);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameLineEdit);

        pathLabel = new QLabel(Utils__WizardPage);
        pathLabel->setObjectName(QString::fromUtf8("pathLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, pathLabel);

        pathChooser = new Utils::PathChooser(Utils__WizardPage);
        pathChooser->setObjectName(QString::fromUtf8("pathChooser"));

        formLayout->setWidget(1, QFormLayout::FieldRole, pathChooser);


        retranslateUi(Utils__WizardPage);

        QMetaObject::connectSlotsByName(Utils__WizardPage);
    } // setupUi

    void retranslateUi(QWizardPage *Utils__WizardPage)
    {
        Utils__WizardPage->setTitle(QCoreApplication::translate("Utils::WizardPage", "Choose the location", nullptr));
        nameLabel->setText(QCoreApplication::translate("Utils::WizardPage", "Name:", nullptr));
        pathLabel->setText(QCoreApplication::translate("Utils::WizardPage", "Path:", nullptr));
    } // retranslateUi

};

} // namespace Utils

namespace Utils {
namespace Ui {
    class WizardPage: public Ui_WizardPage {};
} // namespace Ui
} // namespace Utils

#endif // UI_FILEWIZARDPAGE_H
