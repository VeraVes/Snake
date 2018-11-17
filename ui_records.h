/********************************************************************************
** Form generated from reading UI file 'records.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDS_H
#define UI_RECORDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Records
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QDialog *Records)
    {
        if (Records->objectName().isEmpty())
            Records->setObjectName(QStringLiteral("Records"));
        Records->resize(252, 95);
        gridLayout = new QGridLayout(Records);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton = new QPushButton(Records);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(10, 10));
        pushButton->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(pushButton, 2, 0, 1, 1, Qt::AlignHCenter);

        lineEdit = new QLineEdit(Records);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 0, 1, 1);

        label = new QLabel(Records);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(Records);
        QObject::connect(pushButton, SIGNAL(clicked()), Records, SLOT(accept()));

        QMetaObject::connectSlotsByName(Records);
    } // setupUi

    void retranslateUi(QDialog *Records)
    {
        Records->setWindowTitle(QApplication::translate("Records", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("Records", "Ok", nullptr));
        lineEdit->setText(QString());
        label->setText(QApplication::translate("Records", "Enter your name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Records: public Ui_Records {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDS_H
