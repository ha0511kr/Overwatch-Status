#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QFile>
#include <QNetworkReply>
#include <QSslConfiguration>
#include <sstream>
#include <QString>
#include <QTimer>
#include "curl/curl.h"
#include <cstdio>
#include <stdio.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
    {
        size_t written = fwrite(ptr, size, nmemb, stream);
        return written;
    }

    void getData(QString url, QString outputname);

public slots:

    void refresh();

private slots:
    void on_Battletag_LineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QString name;
    int gData = 0;

    //QNetworkReply *reply;
};

#endif // MAINWINDOW_H
