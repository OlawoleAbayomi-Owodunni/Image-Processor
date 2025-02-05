#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
{
    //Initisalise variables
    ui->setupUi(this);

    ui->displayWindow->setScene(scene);

    //Conncecting signals and slots:
    connect(ui->uploadButton, &QPushButton::clicked, this, &MainWindow::on_uploadButton_clicked); //high chance this throws up errors
                                                                                                    //no error but issue with calling twice
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_uploadButton_clicked()
{
    static int LOG_COUNT = 1;
    ui->logInfo->setText(ui->logInfo->text() +
                         "\n" +
                         QString::number((LOG_COUNT)) +
                         ": Upload button pressed");
    LOG_COUNT++;
    if(LOG_COUNT > 5) {
        LOG_COUNT = 1;
        ui->logInfo->clear();
        ui->logInfo->setText("LOG INFORMATION:");
    }
}
