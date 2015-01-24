#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "quandl.h"

#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(ui->graph, &StockView::update_status, this, &MainWindow::makedo);



    //quandl ql;
    //    ql.auth("NzyifLBFrzi4CSD2NSuy");
    //    ql.get("YAHOO/MSFT");
    QFile f("/home/radu/dev/UTEK2015/stocks-gui/MSFT.json");
    if (! f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qFatal("NEBINE");
    }

    QGraphicsScene *scene = new QGraphicsScene(ui->graph);
    ui->graph->setScene(scene);

    QJsonObject obj(QJsonDocument::fromJson(f.readAll()).object());

    data = obj["data"].toArray();
    ui->graph->set_a(&data);
    QVector<int> closing_cents(data.size());
    for(int i = 1; i < data.size(); ++i)
    {
        closing_cents[i] = data[i].toArray()[4].toDouble() * 100;

        scene->addLine(i-1, closing_cents[i-1] / 100.0 * -10., i, closing_cents[i] / 100.0 * -10.);

        //        if(i % 500 == 0)
        //        {
        //            QGraphicsTextItem *t = scene->addText(data[i].toArray()[0].toString());
        //            t->setPos(i, 0);
        //            t->setScale(5);
        //        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_clicked()
{
}

void MainWindow::makedo(QString s)
{
    ui->infolabel->setText(s);
}
