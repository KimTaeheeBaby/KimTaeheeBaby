#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    titleName(u8"视频车辆检测"),
    runModel(u8"Video File Model"),
    processMethod(u8"KNN"),
    durationString(u8"00:00 / 00:00")
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(openFile()), Qt::UniqueConnection);
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(startProcess()), Qt::UniqueConnection);
    setWindowTitle(titleName);
    ui->progressBar->setVisible(false);
    creatMenu();
    ui->label_time->setText(durationString);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    switch ( QMessageBox::information(this, tr(u8"提示"), tr(u8"你确定退出该软件?"), tr(u8"确定"), tr(u8"取消"), 0, 1))
    {
    case 0:
        this->_stop();
        event->accept();
        break;
    case 1:
    default:
        event->ignore();
        break;
    }
}

void MainWindow::creatMenu()
{
    modelMenu = new QMenu("Model");
    fileModel = new QAction("File Model");
    fileModel->setData(QVariant(0));
    cameraModel = new QAction("Camera Model");
    cameraModel->setData(QVariant(1));
    modelMenu->addAction(fileModel);
    modelMenu->addAction(cameraModel);
    fileModel->setCheckable(true);
    cameraModel->setCheckable(true);
    fileModel->setChecked(true);
    cameraModel->setChecked(false);

    methodMenu = new QMenu("Method");
    actionKNN = new QAction("KNN");
    actionMOG = new QAction("MOG");
    actionGMG = new QAction("GMG");
    actionCNT = new QAction("CNT");
    actionGSOC = new QAction("GSOC");
    actionVibe = new QAction("Vibe");

    methodMenu->addAction(actionKNN);
    methodMenu->addAction(actionMOG);
    methodMenu->addAction(actionGMG);
    methodMenu->addAction(actionCNT);
    methodMenu->addAction(actionGSOC);
    methodMenu->addAction(actionVibe);

    actionKNN->setCheckable(true);
    actionMOG->setCheckable(true);
    actionGMG->setCheckable(true);
    actionCNT->setCheckable(true);
    actionGSOC->setCheckable(true);
    actionVibe->setCheckable(true);
    actionKNN->setChecked(true);
    actionMOG->setChecked(false);
    actionGMG->setChecked(false);
    actionCNT->setChecked(false);
    actionGSOC->setChecked(false);
    actionVibe->setChecked(false);

    ui->menuBar->clear();
    ui->menuBar->addMenu(modelMenu);
    ui->menuBar->addMenu(methodMenu);
    ui->menuBar->setVisible(true);
    statusString = new QLabel();
    ui->statusBar->addWidget(statusString);
    statusString->setText(QString(u8"Run Model: %1.\tProcess Method: %2.").arg(runModel).arg(processMethod));

    connect(fileModel, SIGNAL(triggered(bool)), this, SLOT(changeRunMode()), Qt::UniqueConnection);
    connect(cameraModel, SIGNAL(triggered(bool)), this, SLOT(changeRunMode()), Qt::UniqueConnection);

    connect(actionKNN, SIGNAL(triggered(bool)), this, SLOT(changeMethod()), Qt::UniqueConnection);
    connect(actionMOG, SIGNAL(triggered(bool)), this, SLOT(changeMethod()), Qt::UniqueConnection);
    connect(actionGMG, SIGNAL(triggered(bool)), this, SLOT(changeMethod()), Qt::UniqueConnection);
    connect(actionCNT, SIGNAL(triggered(bool)), this, SLOT(changeMethod()), Qt::UniqueConnection);
    connect(actionGSOC, SIGNAL(triggered(bool)), this, SLOT(changeMethod()), Qt::UniqueConnection);
    connect(actionVibe, SIGNAL(triggered(bool)), this, SLOT(changeMethod()), Qt::UniqueConnection);
    bgThread._setUP();
    connect(bgThread.processObject, SIGNAL(emitImgPtr2(QImage *, QImage *, QImage *, long long)), this, SLOT(getFrame(QImage *, QImage *, QImage *, long long)), Qt::UniqueConnection);
    connect(bgThread.processObject, SIGNAL(emitTime(QString)), this, SLOT(updateTime(QString)), Qt::UniqueConnection);
}

void MainWindow::PBInitialize(int index)
{
    bool tempFlge;
    switch (index)
    {
    case 0:
        ui->pushButton->setText(u8"打开文件");
        ui->pushButton_2->setText(u8"启动");
        ui->pushButton_3->setText(u8"暂停");
        ui->pushButton_4->setText(u8"停止");
        ui->progressBar->setValue(0);
        tempFlge = true;
        break;
    case 1:
        tempFlge = false;
    default:
        break;
    }
    ui->pushButton->setVisible(tempFlge);
    ui->pushButton_2->setVisible(tempFlge);
    ui->pushButton_3->setVisible(tempFlge);
    ui->pushButton_4->setVisible(tempFlge);
    ui->progressBar->setVisible(tempFlge);
    ui->label_time->setVisible(tempFlge);
    ui->label_time->setText(durationString);
}

void MainWindow::_stop()
{
    if (bgThread.isRunning())
    {
        if (bgThread.getIndex() == 0)
        {
            bgThread.processObject->videoStop();
            bgThread.processObject->videoMutex.lock();
            bgThread.processObject->videoMutex.unlock();
        }
        else if (bgThread.getIndex() == 1)
        {
            bgThread.processObject->cameraStop();
            bgThread.processObject->cameraMutex.lock();
            bgThread.processObject->cameraMutex.unlock();
        }
    }
}

void MainWindow::clearWindow()
{
    ui->label->clear();
    ui->label_2->clear();
    ui->label_3->clear();

    ui->label_txt->clear();
    ui->label_txt2->clear();
    ui->label_txt3->clear();

    ui->label_txtFrame->setText("nodata");
}

void MainWindow::noSelectMethod()
{
    actionKNN->setChecked(false);
    actionMOG->setChecked(false);
    actionGMG->setChecked(false);
    actionCNT->setChecked(false);
    actionGSOC->setChecked(false);
    actionVibe->setChecked(false);
}

void MainWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Select a video file"), ".", tr("Image Files(*.avi *.mp4)"));
    if (!QFileInfo::exists(path))
    {
        QMessageBox::information(this, u8"打开错误", QString(u8"文件\" %1 \" 无法解析!").arg(path), QMessageBox::Ok);
        setWindowTitle(titleName);
        return;
    }
    if (bgThread.isRunning())
    {
        _stop();
        this->clearWindow();
    }
    setWindowTitle(titleName + "--" + path);
    bgThread.setUp(path.toStdString());
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(pauseVideo()), Qt::UniqueConnection);
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(stopProcess()), Qt::UniqueConnection);
    connect(bgThread.processObject, SIGNAL(emitFrameCount(long long)), this, SLOT(newProcessBar(long long)), Qt::UniqueConnection);
    ui->pushButton_2->setText(u8"启动");
    ui->progressBar->setVisible(false);

    VideoCapture tempVideo(path.toStdString());
    if (!tempVideo.isOpened())
        QMessageBox::information(this, u8"视频文件打开失败", QString(u8"文件\" %1 \" 无法解析!").arg(path), QMessageBox::Ok);
    int totalMSec = tempVideo.get(CAP_PROP_FRAME_COUNT) * 1000 / tempVideo.get(CAP_PROP_FPS);
    tempVideo.release();
    durationString = "00:00 / " + QTime::fromMSecsSinceStartOfDay(totalMSec).toString("mm:ss");
    ui->label_time->setText(durationString);
}

void MainWindow::startProcess()
{
    if (bgThread.processObject->status() && bgThread.isRunning())
    {
        ui->pushButton_2->setText(u8"启动");
        bgThread.processObject->processContinue();
    }
    else if (!bgThread.isRunning())
        bgThread.start();
}

void MainWindow::getFrame(QImage *frameResult, QImage *imgBgsegm, QImage *dectBgsegm, long long value)
{
    if (!bgThread.isRunning())
        return;
    else
    {
        ui->label->setPixmap(QPixmap::fromImage(*frameResult));
        ui->label_2->setPixmap(QPixmap::fromImage(*imgBgsegm));
        ui->label_3->setPixmap(QPixmap::fromImage(*dectBgsegm));

        ui->label_txt->setText("Source Frame");
        ui->label_txt2->setText(processMethod + " Method");
        ui->label_txt3->setText(processMethod + " detect result");

        ui->centralWidget->update();
        if (value >= 0)
        {
            ui->progressBar->setValue(value);
            ui->label_txtFrame->setText(QString::number(value));
        }
    }
}

void MainWindow::pauseVideo()
{
    if (bgThread.isRunning() && (!bgThread.processObject->status()))
    {
        ui->pushButton_2->setText(u8"继续");
        bgThread.processObject->processPause();
    }
}

void MainWindow::stopProcess()
{
    this->_stop();
    ui->pushButton_2->setText(u8"启动");
    ui->progressBar->setValue(0);
    this->clearWindow();
    ui->label_time->setText(durationString);
}

void MainWindow::newProcessBar(long long n)
{
    ui->progressBar->setRange(0, n - 1);
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(true);
}

void MainWindow::updateTime(QString str)
{
    ui->label_time->setText(str);
}

void MainWindow::changeRunMode()
{
    QAction *temp = dynamic_cast<QAction *>(sender());
    int index = temp->data().toInt();
    if (index != bgThread.getIndex())
    {
        this->_stop();
        clearWindow();
        bgThread.changeMode(index);
        if (index == 0)
        {
            cameraModel->setChecked(false);
            fileModel->setChecked(true);
            runModel = bgThread.getModeName();
            this->PBInitialize(index);
            statusString->setText(QString(u8"Run Model: %1.\tProcess Method: %2.").arg(runModel).arg(processMethod));
        }
        else if (index == 1)
        {
            fileModel->setChecked(false);
            cameraModel->setChecked(true);
            runModel = bgThread.getModeName();
            this->PBInitialize(index);
            statusString->setText(QString(u8"Run Model: %1.\tProcess Method: %2.").arg(runModel).arg(processMethod));
            bgThread.start();
        }
    }
}

void MainWindow::changeMethod()
{
    QAction *temp = dynamic_cast<QAction *>(sender());
    QString str = temp->text();
    if (QString::compare(str, bgThread.getMethodName(), Qt::CaseInsensitive) != 0)
    {
        this->_stop();
        this->clearWindow();
        methodNAME name;
        noSelectMethod();
        if (QString::compare(str, "KNN", Qt::CaseInsensitive) == 0)
        {
            name = methodNAME::KNN;
            actionKNN->setChecked(true);
        }
        else if (QString::compare(str, "MOG", Qt::CaseInsensitive) == 0)
        {
            name = methodNAME::MOG;
            actionMOG->setChecked(true);
        }

        else if (QString::compare(str, "GMG", Qt::CaseInsensitive) == 0)
        {
            name = methodNAME::GMG;
            actionGMG->setChecked(true);
        }
        else if (QString::compare(str, "CNT", Qt::CaseInsensitive) == 0)
        {
            name = methodNAME::CNT;
            actionCNT->setChecked(true);
        }
        else if (QString::compare(str, "GSOC", Qt::CaseInsensitive) == 0)
        {
            name = methodNAME::GSOC;
            actionGSOC->setChecked(true);
        }
        else if (QString::compare(str, "Vibe", Qt::CaseInsensitive) == 0)
        {
            name = methodNAME::VIBE;
            actionVibe->setChecked(true);
        }
        bgThread.changeMethod(name);
        processMethod = bgThread.getMethodName();
        this->PBInitialize(bgThread.getIndex());
        statusString->setText(QString(u8"Run Model: %1.\tProcess Method: %2.").arg(runModel).arg(processMethod));
        if (bgThread.getIndex() == 1)
            bgThread.start();
    }
}
