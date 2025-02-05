#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

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

void MainWindow::logUpdate(QString log_message)
{
    static int LOG_COUNT = 1;
    ui->logInfo->setText(ui->logInfo->text() +
                         "\n" +
                         QString::number((LOG_COUNT)) + ": " +
                         log_message);
    LOG_COUNT++;
    if(LOG_COUNT > 5) {
        LOG_COUNT = 1;
        ui->logInfo->clear();
        ui->logInfo->setText("LOG INFORMATION:");
    }
}

void MainWindow::OpenFile()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Upload Image", "", "Image Files (*.png *.jpg *.jpeg *.bmp)");

    if(file_path.isEmpty()) return; //empty means no path was set

    QPixmap pixmap(file_path);  //pixelmap of file
    if(pixmap.isNull()){
        QMessageBox::critical(this, "ERROR LOADING FILE", "Incorrect file type: selected file does not generate Pixel Map.\n"
                                                          "make sure to select Image Files (*.png *.jpg *.jpeg *.bmp)");
        return;
    }

    scene->clear();
    scene->addPixmap(pixmap);
    ui->displayWindow->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_uploadButton_clicked()
{
    QString log_message = "upload button pressed";
    logUpdate(log_message);

    OpenFile();
}
