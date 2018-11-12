#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPixmap>
#include <QImage>
#include <string>
#include <QString>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QVariant>
#include <QFileInfo>
#include <QTime>
#include "mythread.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    myThread bgThread;
    void closeEvent(QCloseEvent *event);
    QString titleName;

    QMenu *modelMenu;
    QAction *fileModel;
    QAction *cameraModel;

    QMenu *methodMenu;
    QAction *actionKNN;
    QAction *actionMOG;
    QAction *actionGMG;
    QAction *actionCNT;
    QAction *actionGSOC;
    QAction *actionVibe;

    QLabel *statusString;

    void creatMenu();
    QString runModel;
    QString processMethod;
    void PBInitialize(int index);
    void _stop();
    void clearWindow();
    void noSelectMethod();

    QString durationString;
private slots:
    void openFile();
    void startProcess();
    void getFrame(QImage *, QImage *, QImage *, long long);
    void pauseVideo();
    void stopProcess();
    void newProcessBar(long long);
    void updateTime(QString);

    void changeRunMode();
    void changeMethod();
};

#endif // MAINWINDOW_H
