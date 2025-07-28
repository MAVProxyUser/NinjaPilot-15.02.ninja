/********************************************************************************
** Form generated from reading UI file 'pluginview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGINVIEW_H
#define UI_PLUGINVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

namespace ExtensionSystem {
namespace Internal {

class Ui_PluginView
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *pluginWidget;

    void setupUi(QWidget *ExtensionSystem__Internal__PluginView)
    {
        if (ExtensionSystem__Internal__PluginView->objectName().isEmpty())
            ExtensionSystem__Internal__PluginView->setObjectName(QString::fromUtf8("ExtensionSystem__Internal__PluginView"));
        ExtensionSystem__Internal__PluginView->resize(773, 304);
        gridLayout = new QGridLayout(ExtensionSystem__Internal__PluginView);
        gridLayout->setContentsMargins(2, 2, 2, 2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pluginWidget = new QTreeWidget(ExtensionSystem__Internal__PluginView);
        pluginWidget->setObjectName(QString::fromUtf8("pluginWidget"));
        pluginWidget->setAlternatingRowColors(true);
        pluginWidget->setIndentation(0);
        pluginWidget->setRootIsDecorated(false);
        pluginWidget->setUniformRowHeights(true);
        pluginWidget->setItemsExpandable(false);
        pluginWidget->setSortingEnabled(true);
        pluginWidget->setColumnCount(5);

        gridLayout->addWidget(pluginWidget, 0, 0, 1, 1);


        retranslateUi(ExtensionSystem__Internal__PluginView);

        QMetaObject::connectSlotsByName(ExtensionSystem__Internal__PluginView);
    } // setupUi

    void retranslateUi(QWidget *ExtensionSystem__Internal__PluginView)
    {
        QTreeWidgetItem *___qtreewidgetitem = pluginWidget->headerItem();
        ___qtreewidgetitem->setText(4, QCoreApplication::translate("ExtensionSystem::Internal::PluginView", "Location", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("ExtensionSystem::Internal::PluginView", "Developer", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("ExtensionSystem::Internal::PluginView", "Version", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("ExtensionSystem::Internal::PluginView", "Name", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("ExtensionSystem::Internal::PluginView", "State", nullptr));
        (void)ExtensionSystem__Internal__PluginView;
    } // retranslateUi

};

} // namespace Internal
} // namespace ExtensionSystem

namespace ExtensionSystem {
namespace Internal {
namespace Ui {
    class PluginView: public Ui_PluginView {};
} // namespace Ui
} // namespace Internal
} // namespace ExtensionSystem

#endif // UI_PLUGINVIEW_H
