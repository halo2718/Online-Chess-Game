/********************************************************************************
** Form generated from reading UI file 'option.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTION_H
#define UI_OPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Option
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QPushButton *pushButton;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_5;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit;
    QLabel *label_5;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_2;
    QLabel *label_6;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton_4;
    QLabel *label;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QTextBrowser *textBrowser;
    QTextBrowser *textBrowser_2;
    QLabel *label_7;
    QLabel *label_8;

    void setupUi(QDialog *Option)
    {
        if (Option->objectName().isEmpty())
            Option->setObjectName(QString::fromUtf8("Option"));
        Option->resize(904, 380);
        buttonBox = new QDialogButtonBox(Option);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(190, 320, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        gridLayoutWidget = new QWidget(Option);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 50, 601, 261));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 2, 1, 1);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 2, 1, 1, 1);

        lineEdit_3 = new QLineEdit(gridLayoutWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 1, 1, 1, 1);

        pushButton_5 = new QPushButton(gridLayoutWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 4, 3, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 4, 1, 1, 1);

        lineEdit_5 = new QLineEdit(gridLayoutWidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        gridLayout->addWidget(lineEdit_5, 3, 1, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        lineEdit_6 = new QLineEdit(gridLayoutWidget);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        gridLayout->addWidget(lineEdit_6, 3, 3, 1, 1);

        lineEdit_2 = new QLineEdit(gridLayoutWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 0, 3, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 3, 2, 1, 1);

        lineEdit_4 = new QLineEdit(gridLayoutWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 1, 3, 1, 1);

        pushButton_4 = new QPushButton(gridLayoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 2, 3, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 2, 1, 1);

        gridLayoutWidget_2 = new QWidget(Option);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(630, 50, 261, 261));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        textBrowser = new QTextBrowser(gridLayoutWidget_2);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        gridLayout_2->addWidget(textBrowser, 0, 1, 1, 1);

        textBrowser_2 = new QTextBrowser(gridLayoutWidget_2);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));

        gridLayout_2->addWidget(textBrowser_2, 1, 1, 1, 1);

        label_7 = new QLabel(gridLayoutWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 1, 0, 1, 1);


        retranslateUi(Option);
        QObject::connect(buttonBox, SIGNAL(accepted()), Option, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Option, SLOT(reject()));

        QMetaObject::connectSlotsByName(Option);
    } // setupUi

    void retranslateUi(QDialog *Option)
    {
        Option->setWindowTitle(QCoreApplication::translate("Option", "Dialog", nullptr));
        label_4->setText(QCoreApplication::translate("Option", "\350\276\223\345\205\245\347\253\257\345\217\243\347\272\265\345\235\220\346\240\207:", nullptr));
        pushButton->setText(QCoreApplication::translate("Option", "\345\212\240\345\205\245\350\276\223\345\205\245\347\253\257\345\217\243", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Option", "\345\210\240\351\231\244\350\276\223\345\207\272\347\253\257\345\217\243", nullptr));
        label_2->setText(QCoreApplication::translate("Option", "\350\241\214\346\225\260:", nullptr));
        label_3->setText(QCoreApplication::translate("Option", "\350\276\223\345\205\245\347\253\257\345\217\243\346\250\252\345\235\220\346\240\207:", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Option", "\345\210\233\345\273\272\350\276\223\345\207\272\347\253\257\345\217\243", nullptr));
        label_5->setText(QCoreApplication::translate("Option", "\350\276\223\345\207\272\347\253\257\345\217\243\346\250\252\345\235\220\346\240\207:", nullptr));
        label_6->setText(QCoreApplication::translate("Option", "\350\276\223\345\207\272\347\253\257\345\217\243\347\272\265\345\235\220\346\240\207:", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Option", "\345\210\240\351\231\244\350\276\223\345\205\245\347\253\257\345\217\243", nullptr));
        label->setText(QCoreApplication::translate("Option", "\345\210\227\346\225\260:", nullptr));
        label_7->setText(QCoreApplication::translate("Option", "\345\267\262\346\234\211\350\276\223\345\205\245\347\253\257\345\217\243:", nullptr));
        label_8->setText(QCoreApplication::translate("Option", "\345\267\262\346\234\211\350\276\223\345\207\272\347\253\257\345\217\243:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Option: public Ui_Option {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTION_H
