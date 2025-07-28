/********************************************************************************
** Form generated from reading UI file 'projectintropage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTINTROPAGE_H
#define UI_PROJECTINTROPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWizardPage>
#include "pathchooser.h"
#include "projectnamevalidatinglineedit.h"

namespace Utils {

class Ui_ProjectIntroPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *descriptionLabel;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QFormLayout *formLayout;
    QLabel *nameLabel;
    Utils::ProjectNameValidatingLineEdit *nameLineEdit;
    QLabel *pathLabel;
    Utils::PathChooser *pathChooser;
    QSpacerItem *horizontalSpacer;
    QLabel *stateLabel;

    void setupUi(QWizardPage *Utils__ProjectIntroPage)
    {
        if (Utils__ProjectIntroPage->objectName().isEmpty())
            Utils__ProjectIntroPage->setObjectName(QString::fromUtf8("Utils__ProjectIntroPage"));
        Utils__ProjectIntroPage->resize(208, 143);
        verticalLayout = new QVBoxLayout(Utils__ProjectIntroPage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        descriptionLabel = new QLabel(Utils__ProjectIntroPage);
        descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));
        descriptionLabel->setWordWrap(true);

        verticalLayout->addWidget(descriptionLabel);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame = new QFrame(Utils__ProjectIntroPage);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(frame);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        nameLabel = new QLabel(frame);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, nameLabel);

        nameLineEdit = new Utils::ProjectNameValidatingLineEdit(frame);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameLineEdit);

        pathLabel = new QLabel(frame);
        pathLabel->setObjectName(QString::fromUtf8("pathLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, pathLabel);

        pathChooser = new Utils::PathChooser(frame);
        pathChooser->setObjectName(QString::fromUtf8("pathChooser"));

        formLayout->setWidget(1, QFormLayout::FieldRole, pathChooser);


        horizontalLayout->addWidget(frame);

        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        stateLabel = new QLabel(Utils__ProjectIntroPage);
        stateLabel->setObjectName(QString::fromUtf8("stateLabel"));
        stateLabel->setWordWrap(true);

        verticalLayout->addWidget(stateLabel);


        retranslateUi(Utils__ProjectIntroPage);

        QMetaObject::connectSlotsByName(Utils__ProjectIntroPage);
    } // setupUi

    void retranslateUi(QWizardPage *Utils__ProjectIntroPage)
    {
        Utils__ProjectIntroPage->setTitle(QCoreApplication::translate("Utils::ProjectIntroPage", "Introduction and project location", nullptr));
        nameLabel->setText(QCoreApplication::translate("Utils::ProjectIntroPage", "Name:", nullptr));
        pathLabel->setText(QCoreApplication::translate("Utils::ProjectIntroPage", "Create in:", nullptr));
    } // retranslateUi

};

} // namespace Utils

namespace Utils {
namespace Ui {
    class ProjectIntroPage: public Ui_ProjectIntroPage {};
} // namespace Ui
} // namespace Utils

#endif // UI_PROJECTINTROPAGE_H
