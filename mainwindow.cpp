#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>
#include <QThread>
#include "datadisplay.h"
#include "settingsdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    readSettings();
    makeDisplays();
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
            this, &MainWindow::replyFinished);
    update();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
    timer->start(60*1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mousePressEvent(QMouseEvent *evt)
{
    start = mapToGlobal(evt->pos());
    pressing = true;
}

void MainWindow::mouseMoveEvent(QMouseEvent *evt)
{
    if(pressing){
        end = mapToGlobal(evt->pos());
        movement = end - start;
        this->setGeometry(mapToGlobal(movement).x(),mapToGlobal(movement).y(),width(),height());
        start = end;

    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *evt)
{
    pressing = false;
}

void MainWindow::update()
{
    QNetworkRequest request;
    QString s = pairs.join(",");
    request.setUrl(QUrl("https://free.currconv.com/api/v7/convert?q="+s+"&compact=ultra&apiKey="+APIKey));

    QNetworkReply *reply = manager->get(request);

}

void MainWindow::replyFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qWarning() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());

    QJsonObject jsonObject = jsonResponse.object();
    QList<double> currentValues;
    for(int i=0;i<pairs.length();i++){
        currentValues << jsonObject[pairs[i]].toDouble();
    }
    emit valuesChanged(currentValues);
    lastValues = currentValues;
    qDebug() << currentValues;
    reply->deleteLater();
    lastUpdated = QTime::currentTime();
    ui->statusBar->showMessage("Last updated: "+lastUpdated.toString());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue("MainWindow/geometry", saveGeometry());
    settings.setValue("MainWindow/windowState", saveState());
    settings.setValue("APIKey",APIKey);
    settings.setValue("Pairs",pairs.join(","));
    qApp->quit();

}
void MainWindow::readSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("MainWindow/geometry").toByteArray());
    restoreState(settings.value("MainWindow/windowState").toByteArray());
    APIKey = settings.value("APIKey").toString();
    pairs = settings.value("Pairs").toString().split(",");
}

void MainWindow::makeDisplays()
{
    QLayoutItem *child;
    while ((child = ui->verticalLayout_2->layout()->takeAt(0)) != 0) {
        disconnect(this,&MainWindow::valuesChanged,child->widget(),nullptr);
        delete child->widget();
        delete child;
    }
    for(int i=0;i<pairs.length();i++){
        DataDisplay *dd = new DataDisplay(this);
        dd->setObjectName(pairs[i]);
        ui->verticalLayout_2->layout()->addWidget(dd);
        dd->setSymbol(pairs[i]);
        connect(this,&MainWindow::valuesChanged,dd,[=](QList<double> values){
            int direction;
            if(values[i]>lastValues[i]){
                direction = 1;
            }else if(values[i]<lastValues[i]){
                direction = -1;
            }else{
                direction=0;
            }
//            qDebug()<<lastValues;
            dd->updateValue(values[i],direction);
        });
    }
}

void MainWindow::openSettings()
{
    SettingsDialog * dialog = new SettingsDialog(this);
    dialog->setPairs(pairs.join(","));
    dialog->setAPIKey(APIKey);
//    dialog->setAttribute(Qt::WA_TranslucentBackground);
    connect(dialog,&SettingsDialog::accepted,[=](){
        APIKey = dialog->getAPIKey();
        pairs = dialog->getPairs().split(",");
        makeDisplays();
        update();
    });
    dialog->exec();

}
