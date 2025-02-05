#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void logUpdate(QString log_message);

    void OpenFile();

    void UpdateImage(QString file_path);

private slots:
    void onUploadButtonClicked();

    void onPrcGrayButtonClicked();

    void onSaveButtonClicked();

    void on_prcBrghtButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    QString CURRENT_IMG_PATH = "";
};
#endif // MAINWINDOW_H
