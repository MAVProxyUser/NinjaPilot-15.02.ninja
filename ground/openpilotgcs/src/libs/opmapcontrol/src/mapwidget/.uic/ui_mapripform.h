/********************************************************************************
** Form generated from reading UI file 'mapripform.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPRIPFORM_H
#define UI_MAPRIPFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapRipForm
{
public:
    QProgressBar *progressBar;
    QLabel *mainlabel;
    QLabel *statuslabel;
    QPushButton *cancelButton;

    void setupUi(QWidget *MapRipForm)
    {
        if (MapRipForm->objectName().isEmpty())
            MapRipForm->setObjectName(QString::fromUtf8("MapRipForm"));
        MapRipForm->resize(521, 133);
        progressBar = new QProgressBar(MapRipForm);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(20, 60, 481, 23));
        progressBar->setValue(0);
        mainlabel = new QLabel(MapRipForm);
        mainlabel->setObjectName(QString::fromUtf8("mainlabel"));
        mainlabel->setGeometry(QRect(30, 10, 481, 16));
        statuslabel = new QLabel(MapRipForm);
        statuslabel->setObjectName(QString::fromUtf8("statuslabel"));
        statuslabel->setGeometry(QRect(30, 40, 341, 16));
        cancelButton = new QPushButton(MapRipForm);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(220, 100, 75, 23));

        retranslateUi(MapRipForm);

        QMetaObject::connectSlotsByName(MapRipForm);
    } // setupUi

    void retranslateUi(QWidget *MapRipForm)
    {
        MapRipForm->setWindowTitle(QCoreApplication::translate("MapRipForm", "MapRipper", nullptr));
        mainlabel->setText(QCoreApplication::translate("MapRipForm", "Currently ripping from:", nullptr));
        statuslabel->setText(QCoreApplication::translate("MapRipForm", "Downloading tile", nullptr));
        cancelButton->setText(QCoreApplication::translate("MapRipForm", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MapRipForm: public Ui_MapRipForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPRIPFORM_H
