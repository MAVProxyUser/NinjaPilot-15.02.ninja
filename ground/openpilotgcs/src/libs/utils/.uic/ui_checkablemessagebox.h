/********************************************************************************
** Form generated from reading UI file 'checkablemessagebox.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKABLEMESSAGEBOX_H
#define UI_CHECKABLEMESSAGEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

namespace Utils {

class Ui_CheckableMessageBox
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *pixmapLabel;
    QSpacerItem *pixmapSpacer;
    QLabel *messageLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *checkBoxLeftSpacer;
    QCheckBox *checkBox;
    QSpacerItem *checkBoxRightSpacer;
    QSpacerItem *buttonSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Utils__CheckableMessageBox)
    {
        if (Utils__CheckableMessageBox->objectName().isEmpty())
            Utils__CheckableMessageBox->setObjectName(QString::fromUtf8("Utils__CheckableMessageBox"));
        Utils__CheckableMessageBox->resize(195, 107);
        verticalLayout_2 = new QVBoxLayout(Utils__CheckableMessageBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pixmapLabel = new QLabel(Utils__CheckableMessageBox);
        pixmapLabel->setObjectName(QString::fromUtf8("pixmapLabel"));

        verticalLayout->addWidget(pixmapLabel);

        pixmapSpacer = new QSpacerItem(0, 5, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout->addItem(pixmapSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        messageLabel = new QLabel(Utils__CheckableMessageBox);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));

        horizontalLayout_2->addWidget(messageLabel);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBoxLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(checkBoxLeftSpacer);

        checkBox = new QCheckBox(Utils__CheckableMessageBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout->addWidget(checkBox);

        checkBoxRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(checkBoxRightSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        buttonSpacer = new QSpacerItem(0, 5, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(buttonSpacer);

        buttonBox = new QDialogButtonBox(Utils__CheckableMessageBox);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(Utils__CheckableMessageBox);
        QObject::connect(buttonBox, SIGNAL(accepted()), Utils__CheckableMessageBox, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Utils__CheckableMessageBox, SLOT(reject()));

        QMetaObject::connectSlotsByName(Utils__CheckableMessageBox);
    } // setupUi

    void retranslateUi(QDialog *Utils__CheckableMessageBox)
    {
        Utils__CheckableMessageBox->setWindowTitle(QCoreApplication::translate("Utils::CheckableMessageBox", "Dialog", nullptr));
        messageLabel->setText(QCoreApplication::translate("Utils::CheckableMessageBox", "TextLabel", nullptr));
        checkBox->setText(QCoreApplication::translate("Utils::CheckableMessageBox", "CheckBox", nullptr));
    } // retranslateUi

};

} // namespace Utils

namespace Utils {
namespace Ui {
    class CheckableMessageBox: public Ui_CheckableMessageBox {};
} // namespace Ui
} // namespace Utils

#endif // UI_CHECKABLEMESSAGEBOX_H
