#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>
#include <QtNetwork/QNetworkAccessManager>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);
    void mouseReleaseEvent(QMouseEvent *evt);
    void closeEvent(QCloseEvent *event);
public slots:
    void update();
    void replyFinished(QNetworkReply *reply);
    void readSettings();
    void makeDisplays();
    void openSettings();
signals:
    void valuesChanged(QList<double> values);
private:
    Ui::MainWindow *ui;
    QPoint start;
    QPoint end;
    QPoint movement;
    bool pressing = false;
    QTimer *timer;
    QNetworkAccessManager *manager;
//    double lastValue = 0.0;
    QTime lastUpdated;
    QStringList pairs;
    QList<double> lastValues;
    QString APIKey;

};
#endif // MAINWINDOW_H
