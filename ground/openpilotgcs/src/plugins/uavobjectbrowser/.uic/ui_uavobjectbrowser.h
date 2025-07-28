/********************************************************************************
** Form generated from reading UI file 'uavobjectbrowser.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UAVOBJECTBROWSER_H
#define UI_UAVOBJECTBROWSER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UAVObjectBrowser
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *requestButton;
    QToolButton *sendButton;
    QSpacerItem *horizontalSpacer;
    QFrame *line;
    QToolButton *readSDButton;
    QToolButton *saveSDButton;
    QToolButton *eraseSDButton;
    QSpacerItem *horizontalSpacer_5;
    QFrame *line_2;
    QSpacerItem *horizontalSpacer_8;
    QToolButton *tbView;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QTreeView *treeView;
    QTextEdit *descriptionText;

    void setupUi(QWidget *UAVObjectBrowser)
    {
        if (UAVObjectBrowser->objectName().isEmpty())
            UAVObjectBrowser->setObjectName(QString::fromUtf8("UAVObjectBrowser"));
        UAVObjectBrowser->resize(786, 462);
        verticalLayout = new QVBoxLayout(UAVObjectBrowser);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        requestButton = new QToolButton(UAVObjectBrowser);
        requestButton->setObjectName(QString::fromUtf8("requestButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/uavobjectbrowser/images/down_alt.png"), QSize(), QIcon::Normal, QIcon::Off);
        requestButton->setIcon(icon);
        requestButton->setIconSize(QSize(32, 32));
        requestButton->setCheckable(false);
        requestButton->setChecked(false);

        horizontalLayout->addWidget(requestButton);

        sendButton = new QToolButton(UAVObjectBrowser);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/uavobjectbrowser/images/up_alt.png"), QSize(), QIcon::Normal, QIcon::Off);
        sendButton->setIcon(icon1);
        sendButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(sendButton);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        line = new QFrame(UAVObjectBrowser);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        readSDButton = new QToolButton(UAVObjectBrowser);
        readSDButton->setObjectName(QString::fromUtf8("readSDButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/uavobjectbrowser/images/install.png"), QSize(), QIcon::Normal, QIcon::Off);
        readSDButton->setIcon(icon2);
        readSDButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(readSDButton);

        saveSDButton = new QToolButton(UAVObjectBrowser);
        saveSDButton->setObjectName(QString::fromUtf8("saveSDButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/uavobjectbrowser/images/remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveSDButton->setIcon(icon3);
        saveSDButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(saveSDButton);

        eraseSDButton = new QToolButton(UAVObjectBrowser);
        eraseSDButton->setObjectName(QString::fromUtf8("eraseSDButton"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/uavobjectbrowser/images/trash.png"), QSize(), QIcon::Normal, QIcon::Off);
        eraseSDButton->setIcon(icon4);
        eraseSDButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(eraseSDButton);

        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        line_2 = new QFrame(UAVObjectBrowser);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        horizontalSpacer_8 = new QSpacerItem(5, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);

        tbView = new QToolButton(UAVObjectBrowser);
        tbView->setObjectName(QString::fromUtf8("tbView"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/uavobjectbrowser/images/1343241276_eye.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbView->setIcon(icon5);
        tbView->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(tbView);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        widget = new QWidget(UAVObjectBrowser);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(widget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setLineWidth(0);
        splitter->setOrientation(Qt::Vertical);
        treeView = new QTreeView(splitter);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy);
        splitter->addWidget(treeView);
        descriptionText = new QTextEdit(splitter);
        descriptionText->setObjectName(QString::fromUtf8("descriptionText"));
        sizePolicy.setHeightForWidth(descriptionText->sizePolicy().hasHeightForWidth());
        descriptionText->setSizePolicy(sizePolicy);
        descriptionText->setMinimumSize(QSize(0, 150));
        descriptionText->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        descriptionText->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        splitter->addWidget(descriptionText);

        verticalLayout_3->addWidget(splitter);


        verticalLayout->addWidget(widget);


        retranslateUi(UAVObjectBrowser);

        QMetaObject::connectSlotsByName(UAVObjectBrowser);
    } // setupUi

    void retranslateUi(QWidget *UAVObjectBrowser)
    {
        UAVObjectBrowser->setWindowTitle(QCoreApplication::translate("UAVObjectBrowser", "Form", nullptr));
#if QT_CONFIG(tooltip)
        requestButton->setToolTip(QCoreApplication::translate("UAVObjectBrowser", "Request", nullptr));
#endif // QT_CONFIG(tooltip)
        requestButton->setText(QCoreApplication::translate("UAVObjectBrowser", "...", nullptr));
#if QT_CONFIG(tooltip)
        sendButton->setToolTip(QCoreApplication::translate("UAVObjectBrowser", "Send", nullptr));
#endif // QT_CONFIG(tooltip)
        sendButton->setText(QCoreApplication::translate("UAVObjectBrowser", "...", nullptr));
#if QT_CONFIG(tooltip)
        readSDButton->setToolTip(QCoreApplication::translate("UAVObjectBrowser", "Load", nullptr));
#endif // QT_CONFIG(tooltip)
        readSDButton->setText(QCoreApplication::translate("UAVObjectBrowser", "...", nullptr));
#if QT_CONFIG(tooltip)
        saveSDButton->setToolTip(QCoreApplication::translate("UAVObjectBrowser", "Save", nullptr));
#endif // QT_CONFIG(tooltip)
        saveSDButton->setText(QCoreApplication::translate("UAVObjectBrowser", "...", nullptr));
#if QT_CONFIG(tooltip)
        eraseSDButton->setToolTip(QCoreApplication::translate("UAVObjectBrowser", "Erase", nullptr));
#endif // QT_CONFIG(tooltip)
        eraseSDButton->setText(QCoreApplication::translate("UAVObjectBrowser", "...", nullptr));
#if QT_CONFIG(tooltip)
        tbView->setToolTip(QCoreApplication::translate("UAVObjectBrowser", "View Options", nullptr));
#endif // QT_CONFIG(tooltip)
        tbView->setText(QCoreApplication::translate("UAVObjectBrowser", "...", nullptr));
        descriptionText->setPlaceholderText(QCoreApplication::translate("UAVObjectBrowser", "This space shows a description of the selected UAVObject.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UAVObjectBrowser: public Ui_UAVObjectBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UAVOBJECTBROWSER_H
