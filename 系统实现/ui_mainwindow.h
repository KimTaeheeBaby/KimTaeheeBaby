/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QProgressBar *progressBar;
    QLabel *label_txt;
    QLabel *label_txt2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_txt3;
    QLabel *label;
    QLabel *label_time;
    QLabel *label_txtFrame;
    QLabel *label_txtFrame_label;
    QMenuBar *menuBar;
    QMenu *menuModel;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(871, 730);
        QFont font;
        font.setFamily(QString::fromUtf8("\347\255\211\347\272\277"));
        MainWindow->setFont(font);
        MainWindow->setDocumentMode(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 590, 111, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\347\255\211\347\272\277"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        pushButton->setFont(font1);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(160, 590, 111, 51));
        pushButton_2->setFont(font1);
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(300, 590, 111, 51));
        pushButton_3->setFont(font1);
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(430, 590, 61, 51));
        pushButton_4->setFont(font1);
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(670, 600, 180, 30));
        QFont font2;
        font2.setFamily(QStringLiteral("Microsoft JhengHei UI"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        progressBar->setFont(font2);
        progressBar->setValue(0);
        progressBar->setTextVisible(true);
        label_txt = new QLabel(centralWidget);
        label_txt->setObjectName(QStringLiteral("label_txt"));
        label_txt->setGeometry(QRect(10, 0, 400, 30));
        QFont font3;
        font3.setFamily(QStringLiteral("Microsoft YaHei UI Light"));
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setWeight(75);
        label_txt->setFont(font3);
        label_txt->setAlignment(Qt::AlignCenter);
        label_txt2 = new QLabel(centralWidget);
        label_txt2->setObjectName(QStringLiteral("label_txt2"));
        label_txt2->setGeometry(QRect(460, 0, 400, 30));
        QFont font4;
        font4.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setWeight(50);
        label_txt2->setFont(font4);
        label_txt2->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(460, 30, 400, 250));
        label_2->setAutoFillBackground(true);
        label_2->setFrameShape(QFrame::StyledPanel);
        label_2->setFrameShadow(QFrame::Plain);
        label_2->setMidLineWidth(0);
        label_2->setScaledContents(true);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 320, 400, 250));
        label_3->setAutoFillBackground(true);
        label_3->setFrameShape(QFrame::StyledPanel);
        label_3->setFrameShadow(QFrame::Plain);
        label_3->setMidLineWidth(0);
        label_3->setScaledContents(true);
        label_3->setAlignment(Qt::AlignCenter);
        label_txt3 = new QLabel(centralWidget);
        label_txt3->setObjectName(QStringLiteral("label_txt3"));
        label_txt3->setGeometry(QRect(10, 290, 400, 30));
        label_txt3->setFont(font3);
        label_txt3->setAlignment(Qt::AlignCenter);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(true);
        label->setGeometry(QRect(10, 40, 400, 250));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAutoFillBackground(true);
        label->setFrameShape(QFrame::StyledPanel);
        label->setLineWidth(1);
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);
        label->setOpenExternalLinks(false);
        label_time = new QLabel(centralWidget);
        label_time->setObjectName(QStringLiteral("label_time"));
        label_time->setGeometry(QRect(540, 600, 120, 30));
        QFont font5;
        font5.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font5.setPointSize(10);
        label_time->setFont(font5);
        label_txtFrame = new QLabel(centralWidget);
        label_txtFrame->setObjectName(QStringLiteral("label_txtFrame"));
        label_txtFrame->setGeometry(QRect(550, 320, 111, 30));
        QFont font6;
        font6.setFamily(QString::fromUtf8("\347\255\211\347\272\277"));
        font6.setPointSize(12);
        label_txtFrame->setFont(font6);
        label_txtFrame_label = new QLabel(centralWidget);
        label_txtFrame_label->setObjectName(QStringLiteral("label_txtFrame_label"));
        label_txtFrame_label->setGeometry(QRect(470, 320, 71, 31));
        label_txtFrame_label->setFont(font6);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setEnabled(true);
        menuBar->setGeometry(QRect(0, 0, 871, 26));
        menuModel = new QMenu(menuBar);
        menuModel->setObjectName(QStringLiteral("menuModel"));
        QFont font7;
        font7.setPointSize(11);
        menuModel->setFont(font7);
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuModel->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\350\247\206\351\242\221", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        label_txt->setText(QString());
        label_txt2->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_txt3->setText(QString());
        label->setText(QString());
        label_time->setText(QApplication::translate("MainWindow", "00:00 / 00:00", nullptr));
        label_txtFrame->setText(QApplication::translate("MainWindow", "nodata", nullptr));
        label_txtFrame_label->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\345\270\247", nullptr));
        menuModel->setTitle(QApplication::translate("MainWindow", "Model", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
