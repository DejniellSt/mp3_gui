#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    videoo = new QVideoWidget(this);

    player->setVideoOutput(videoo);
    this -> setCentralWidget(videoo);

    slider = new QSlider(this);
    bar = new QProgressBar(this);

    slider-> setOrientation(Qt::Horizontal);

    ui->statusbar->addPermanentWidget(slider);
    ui->statusbar->addPermanentWidget(bar);

    connect(player,&QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,slider,&QSlider::setValue);
    connect(slider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);


    connect(player,&QMediaPlayer::durationChanged,bar,&QProgressBar::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,bar,&QProgressBar::setValue);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOtw_rz_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Otwórz plik","","Pliki (*.*)");
    on_actionStop_triggered();
    player -> setMedia(QUrl::fromLocalFile(filename));

    on_actionPlay_triggered();
}

void MainWindow::on_actionStop_triggered()
{
    player-> stop();
    ui->statusbar->showMessage("Zatrzymanie");
}

void MainWindow::on_actionPlay_triggered()
{
    player-> play();
    ui->statusbar->showMessage("Odtwarzanie");
}

void MainWindow::on_actionPause_triggered()
{
    player-> pause();
    ui->statusbar->showMessage("Pauza");
}
