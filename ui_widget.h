/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <ControlPanel.h>
#include <ImageView.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    ImageView *graphicsView;
    ControlPanel *widget;
    QLabel *label;
    QPushButton *resetButton;
    QPushButton *exitButton;
    QLabel *timeLabel;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(600, 600);
        graphicsView = new ImageView(Widget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(0, 0, 600, 600));
        widget = new ControlPanel(Widget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(200, 190, 181, 191));
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 560, 251, 17));
        resetButton = new QPushButton(Widget);
        resetButton->setObjectName("resetButton");
        resetButton->setGeometry(QRect(400, 560, 89, 25));
        exitButton = new QPushButton(Widget);
        exitButton->setObjectName("exitButton");
        exitButton->setGeometry(QRect(500, 560, 89, 25));
        timeLabel = new QLabel(Widget);
        timeLabel->setObjectName("timeLabel");
        timeLabel->setGeometry(QRect(520, 530, 67, 17));
        timeLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label->setText(QCoreApplication::translate("Widget", "Double click to reveal control panel", nullptr));
        resetButton->setText(QCoreApplication::translate("Widget", "Reset", nullptr));
        exitButton->setText(QCoreApplication::translate("Widget", "Exit", nullptr));
        timeLabel->setText(QCoreApplication::translate("Widget", "- ms", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
