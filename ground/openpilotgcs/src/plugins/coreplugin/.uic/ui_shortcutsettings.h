/********************************************************************************
** Form generated from reading UI file 'shortcutsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHORTCUTSETTINGS_H
#define UI_SHORTCUTSETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShortcutSettings
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *groupBox;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QLabel *filterLabel;
    QLineEdit *filterEdit;
    QTreeWidget *commandList;
    QHBoxLayout *hboxLayout1;
    QPushButton *defaultButton;
    QSpacerItem *spacerItem;
    QPushButton *importButton;
    QPushButton *exportButton;
    QGroupBox *seqGrp;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout2;
    QLabel *label_2;
    QLineEdit *shortcutEdit;
    QToolButton *resetButton;
    QToolButton *removeButton;
    QLabel *infoLabel;

    void setupUi(QWidget *ShortcutSettings)
    {
        if (ShortcutSettings->objectName().isEmpty())
            ShortcutSettings->setObjectName(QString::fromUtf8("ShortcutSettings"));
        ShortcutSettings->resize(568, 451);
        vboxLayout = new QVBoxLayout(ShortcutSettings);
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        groupBox = new QGroupBox(ShortcutSettings);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        vboxLayout1 = new QVBoxLayout(groupBox);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        filterLabel = new QLabel(groupBox);
        filterLabel->setObjectName(QString::fromUtf8("filterLabel"));

        hboxLayout->addWidget(filterLabel);

        filterEdit = new QLineEdit(groupBox);
        filterEdit->setObjectName(QString::fromUtf8("filterEdit"));

        hboxLayout->addWidget(filterEdit);


        vboxLayout1->addLayout(hboxLayout);

        commandList = new QTreeWidget(groupBox);
        commandList->setObjectName(QString::fromUtf8("commandList"));
        commandList->setRootIsDecorated(false);
        commandList->setUniformRowHeights(true);
        commandList->setSortingEnabled(true);
        commandList->setColumnCount(3);

        vboxLayout1->addWidget(commandList);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        defaultButton = new QPushButton(groupBox);
        defaultButton->setObjectName(QString::fromUtf8("defaultButton"));

        hboxLayout1->addWidget(defaultButton);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem);

        importButton = new QPushButton(groupBox);
        importButton->setObjectName(QString::fromUtf8("importButton"));

        hboxLayout1->addWidget(importButton);

        exportButton = new QPushButton(groupBox);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));

        hboxLayout1->addWidget(exportButton);


        vboxLayout1->addLayout(hboxLayout1);


        vboxLayout->addWidget(groupBox);

        seqGrp = new QGroupBox(ShortcutSettings);
        seqGrp->setObjectName(QString::fromUtf8("seqGrp"));
        vboxLayout2 = new QVBoxLayout(seqGrp);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        label_2 = new QLabel(seqGrp);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        hboxLayout2->addWidget(label_2);

        shortcutEdit = new QLineEdit(seqGrp);
        shortcutEdit->setObjectName(QString::fromUtf8("shortcutEdit"));

        hboxLayout2->addWidget(shortcutEdit);

        resetButton = new QToolButton(seqGrp);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/core/images/reset.png"), QSize(), QIcon::Normal, QIcon::Off);
        resetButton->setIcon(icon);

        hboxLayout2->addWidget(resetButton);

        removeButton = new QToolButton(seqGrp);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/core/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        removeButton->setIcon(icon1);

        hboxLayout2->addWidget(removeButton);


        vboxLayout2->addLayout(hboxLayout2);

        infoLabel = new QLabel(seqGrp);
        infoLabel->setObjectName(QString::fromUtf8("infoLabel"));
        infoLabel->setTextFormat(Qt::RichText);

        vboxLayout2->addWidget(infoLabel);


        vboxLayout->addWidget(seqGrp);


        retranslateUi(ShortcutSettings);

        QMetaObject::connectSlotsByName(ShortcutSettings);
    } // setupUi

    void retranslateUi(QWidget *ShortcutSettings)
    {
        groupBox->setTitle(QCoreApplication::translate("ShortcutSettings", "Keyboard Shortcuts", nullptr));
        filterLabel->setText(QCoreApplication::translate("ShortcutSettings", "Filter:", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = commandList->headerItem();
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("ShortcutSettings", "Shortcut", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("ShortcutSettings", "Label", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("ShortcutSettings", "Command", nullptr));
        defaultButton->setText(QCoreApplication::translate("ShortcutSettings", "Defaults", nullptr));
        importButton->setText(QCoreApplication::translate("ShortcutSettings", "Import...", nullptr));
        exportButton->setText(QCoreApplication::translate("ShortcutSettings", "Export...", nullptr));
        seqGrp->setTitle(QCoreApplication::translate("ShortcutSettings", "Key Sequence", nullptr));
        label_2->setText(QCoreApplication::translate("ShortcutSettings", "Shortcut:", nullptr));
#if QT_CONFIG(tooltip)
        resetButton->setToolTip(QCoreApplication::translate("ShortcutSettings", "Reset", nullptr));
#endif // QT_CONFIG(tooltip)
        resetButton->setText(QString());
#if QT_CONFIG(tooltip)
        removeButton->setToolTip(QCoreApplication::translate("ShortcutSettings", "Remove", nullptr));
#endif // QT_CONFIG(tooltip)
        removeButton->setText(QString());
        (void)ShortcutSettings;
    } // retranslateUi

};

namespace Ui {
    class ShortcutSettings: public Ui_ShortcutSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHORTCUTSETTINGS_H
