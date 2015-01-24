#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QJsonArray data;

private:
    Ui::MainWindow *ui;

private slots:
    void on_button_clicked();
    void makedo(QString s);
};

#endif // MAINWINDOW_H
