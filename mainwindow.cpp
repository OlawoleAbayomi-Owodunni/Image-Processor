#include "halideFunctions.h"

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
    connect(ui->uploadButton, &QPushButton::clicked, this, &MainWindow::onUploadButtonClicked); //high chance this throws up errors
        //no error but issue with calling twice

    connect(ui->prcGrayButton, &QPushButton::clicked, this, &MainWindow::onPrcGrayButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onUploadButtonClicked()
{
    QString log_message = "Upload button pressed";
    logUpdate(log_message);

    OpenFile();
}

void MainWindow::onPrcGrayButtonClicked()
{
    QString log_message = "Grayscale button pressed";
    logUpdate(log_message);

    if(CURRENT_IMG_PATH == ""){
        QMessageBox::critical(this, "INVALID OPERATION!", "No image has been selected: Please Upload an image first :)");
        return;
    }

    QString save_path = "tempImg.png";

    makeGrayscale(CURRENT_IMG_PATH, save_path);

    //CURRENT_IMG_PATH = save_path;
    //UpdateImage(CURRENT_IMG_PATH);
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

void MainWindow::UpdateImage(QString t_filePath)
{
    QPixmap pixmap(t_filePath);  //pixelmap of file used to display image (DOESN'T ACTUALLY CONTAIN IMAGE INFO)
    if(pixmap.isNull()){
        QMessageBox::critical(this, "ERROR LOADING FILE", "Incorrect file type: selected file does not generate Pixel Map.\n"
                                                          "Make sure to select Image Files (*.png *.jpg *.jpeg *.bmp)");
        return;
    }

    scene->clear();
    scene->addPixmap(pixmap);
    ui->displayWindow->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::OpenFile()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Upload Image", "", "Image Files (*.png *.jpg *.jpeg *.bmp)");

    if(file_path.isEmpty()) return; //empty means no path was set

    UpdateImage(file_path);

    CURRENT_IMG_PATH = file_path;
}
