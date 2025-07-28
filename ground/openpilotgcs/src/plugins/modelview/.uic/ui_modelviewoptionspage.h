/********************************************************************************
** Form generated from reading UI file 'modelviewoptionspage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODELVIEWOPTIONSPAGE_H
#define UI_MODELVIEWOPTIONSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "utils/pathchooser.h"

QT_BEGIN_NAMESPACE

class Ui_ModelViewOptionsPage
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    Utils::PathChooser *backgroundPathChooser;
    Utils::PathChooser *modelPathChooser;
    QSpacerItem *verticalSpacer;
    QCheckBox *enableVbo;
    QLabel *label_3;

    void setupUi(QWidget *ModelViewOptionsPage)
    {
        if (ModelViewOptionsPage->objectName().isEmpty())
            ModelViewOptionsPage->setObjectName(QString::fromUtf8("ModelViewOptionsPage"));
        ModelViewOptionsPage->resize(378, 300);
        gridLayout = new QGridLayout(ModelViewOptionsPage);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(ModelViewOptionsPage);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(ModelViewOptionsPage);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        backgroundPathChooser = new Utils::PathChooser(ModelViewOptionsPage);
        backgroundPathChooser->setObjectName(QString::fromUtf8("backgroundPathChooser"));

        gridLayout->addWidget(backgroundPathChooser, 1, 1, 1, 1);

        modelPathChooser = new Utils::PathChooser(ModelViewOptionsPage);
        modelPathChooser->setObjectName(QString::fromUtf8("modelPathChooser"));

        gridLayout->addWidget(modelPathChooser, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);

        enableVbo = new QCheckBox(ModelViewOptionsPage);
        enableVbo->setObjectName(QString::fromUtf8("enableVbo"));

        gridLayout->addWidget(enableVbo, 2, 1, 1, 1);

        label_3 = new QLabel(ModelViewOptionsPage);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);


        retranslateUi(ModelViewOptionsPage);

        QMetaObject::connectSlotsByName(ModelViewOptionsPage);
    } // setupUi

    void retranslateUi(QWidget *ModelViewOptionsPage)
    {
        ModelViewOptionsPage->setWindowTitle(QCoreApplication::translate("ModelViewOptionsPage", "Form", nullptr));
        label->setText(QCoreApplication::translate("ModelViewOptionsPage", "3D model:", nullptr));
        label_2->setText(QCoreApplication::translate("ModelViewOptionsPage", "Background image:", nullptr));
#if QT_CONFIG(tooltip)
        backgroundPathChooser->setToolTip(QCoreApplication::translate("ModelViewOptionsPage", "Select the image that is shown in the background.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        modelPathChooser->setToolTip(QCoreApplication::translate("ModelViewOptionsPage", "Select the 3D model file here.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        enableVbo->setToolTip(QCoreApplication::translate("ModelViewOptionsPage", "Click to enable the use of Vertical Blanking.\n"
"It is not enabled by default because some graphic cards do not\n"
"support it, and crash the GCS. Enabling improves performance, though, so you can experiment at your own risk.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        enableVbo->setWhatsThis(QCoreApplication::translate("ModelViewOptionsPage", "VBO allow for performance gains for GPUs that support it (most cards).  This may cause cards with faulty drivers to crash.", nullptr));
#endif // QT_CONFIG(whatsthis)
        enableVbo->setText(QString());
        label_3->setText(QCoreApplication::translate("ModelViewOptionsPage", "Enable VBOs:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModelViewOptionsPage: public Ui_ModelViewOptionsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODELVIEWOPTIONSPAGE_H
