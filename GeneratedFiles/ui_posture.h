/********************************************************************************
** Form generated from reading UI file 'posture.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSTURE_H
#define UI_POSTURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_postureClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *postureClass)
    {
        if (postureClass->objectName().isEmpty())
            postureClass->setObjectName(QStringLiteral("postureClass"));
        postureClass->resize(600, 400);
        centralWidget = new QWidget(postureClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        postureClass->setCentralWidget(centralWidget);

        retranslateUi(postureClass);

        QMetaObject::connectSlotsByName(postureClass);
    } // setupUi

    void retranslateUi(QMainWindow *postureClass)
    {
        postureClass->setWindowTitle(QApplication::translate("postureClass", "posture", 0));
    } // retranslateUi

};

namespace Ui {
    class postureClass: public Ui_postureClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSTURE_H
