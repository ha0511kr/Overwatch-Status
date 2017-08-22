#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSystemTrayIcon>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh()
{
    QString battletag = ui->Battletag_LineEdit->text();
    ui->Battletag_Label->setText("Getting Data - Please wait.");
    qDebug() << "test";
    battletag.replace("#", "-");

        if(ui->tabWidget->indexOf(ui->tabWidget->currentWidget()) == 0)
        {
        getData("https://api.lootbox.eu/pc/us/" + battletag + "/profile", "profile.json");
        QFile loadfile("/Users/cripplingdepression/Google Drive/Qt_Code/build-Overwatch_Stats-Desktop_Qt_5_8_0_clang_64bit-Debug/profile.json");
        loadfile.open(QFile::ReadOnly);
        QJsonDocument json(QJsonDocument::fromJson(loadfile.readAll()));
        QJsonObject obj(json.object());


        QJsonObject data(obj["data"].toObject());

        QJsonObject comprank(data["competitive"].toObject());

        ui->Battletag_Label->setText(data["username"].toString());
        name = data["username"].toString();

        ui->Level_ProgressBar->setValue(data["level"].toInt());

        if(!(data["level"].toInt() <= 100))
        {
        ui->Level_ProgressBar->setMaximum(((data["level"].toInt() / 100) + 1) * 100);
        }

        ui->Competitive_Label->setText("Competitive | Rank: " + comprank["rank"].toString());

        QJsonObject gametime(data["playtime"].toObject());

        ui->QuickPlaytime_Label->setText("Playtime: " + gametime["quick"].toString());
        ui->CompetitivePlaytime_Label->setText("Playtime: " + gametime["competitive"].toString());

        QJsonObject gamestat(data["games"].toObject());
        QJsonObject quickstat(gamestat["quick"].toObject());

        ui->QuickPlayWin_Label->setText("Wins: " + quickstat["wins"].toString());
        ui->QuickPlayLost_Label->setText("Losts: " + QString::number(quickstat["lost"].toInt()));

        QJsonObject compstat(gamestat["competitive"].toObject());

        ui->CompetitiveWin_Label->setText("Wins: " + compstat["wins"].toString());
        ui->CompetitiveLost_Label->setText("Losts: " + QString::number(compstat["lost"].toInt()));
        }else if(ui->tabWidget->indexOf(ui->tabWidget->currentWidget()) == 1){

        getData("https://api.lootbox.eu/pc/us/" + battletag + "/quickplay/allHeroes/", "/Users/cripplingdepression/Google Drive/Qt_Code/build-Overwatch_Stats-Desktop_Qt_5_8_0_clang_64bit-Debug/quickplay.json");
        QFile loadfile("quickplay.json");
        loadfile.open(QFile::ReadOnly);
        QJsonDocument json(QJsonDocument::fromJson(loadfile.readAll()));
        QJsonObject obj(json.object());

        ui->Battletag_Label->setText(name);

        ui->QSoloKills_Label->setText("Solo Kills: " + obj["SoloKills"].toString());
        ui->QObjectiveKills_Label->setText("Objective Kills: " + obj["ObjectiveKills"].toString());
        ui->QDeaths_Label->setText("Deaths: " +obj["Deaths"].toString());
        ui->QFinalBlows_Label->setText("Final Blows: " +obj["FinalBlows"].toString());
        ui->QDamageDone_Label->setText("Damage Done: " +obj["DamageDone"].toString());
        ui->QEliminations_Label->setText("Elimination: " +obj["Eliminations"].toString());
        ui->QMedals_Label->setText("Medals: " +obj["Medals"].toString());
        ui->QHealingDone_Label->setText("Healing Done: " +obj["HealingDone"].toString());

        }
}

void MainWindow::getData(QString url, QString outputname)
{
    FILE *test;
    QString final = "/Users/cripplingdepression/Google Drive/Qt_Code/build-Overwatch_Stats-Desktop_Qt_5_8_0_clang_64bit-Debug/" + outputname;
    test = fopen(final.toStdString().c_str(), "wb");
    CURL *curl =  curl_easy_init();
    //char *url = "https://api.lootbox.eu/pc/us/ha0511kr-1270/profile";
    if(curl)
    {
        qDebug() << url;
    curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());
    curl_easy_setopt(curl, CURLOPT_CAINFO, "/Users/cripplingdepression/Google Drive/Qt_Code/build-Overwatch_Stats-Desktop_Qt_5_8_0_clang_64bit-Debug/ca-bundle.crt");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, test);

    //CURLcode res =
    curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    fclose(test);
    }
}

void MainWindow::on_Battletag_LineEdit_returnPressed()
{
    ui->Battletag_Label->setText("Getting Data - Please wait.");
    ui->Battletag_LineEdit->setVisible(false);
    ui->Battletag_Label->setVisible(true);
    ui->tabWidget->setEnabled(true);
    refresh();
    timer->start(5000);
}
