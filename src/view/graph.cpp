#include "graph.h"

#include "../controller/controller.hpp"
#include "ui_graph.h"

Graph::Graph(QWidget* parent, QString str_out)
    : QDialog(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
  strOut = str_out + '=';
}

Graph::~Graph() { delete ui; }

void Graph::on_pushButton_graph_clicked() {
  step = 0.01;
  xStart = ui->xStart->value();
  xEnd = ui->xEnd->value();
  yStart = ui->yStart->value();
  yEnd = ui->yEnd->value();

  int err = 0;
  if (xStart >= xEnd || yStart >= yEnd) {
    err = 1;
  } else {
    ui->widget->xAxis->setRange(xStart, xEnd);
    ui->widget->yAxis->setRange(yStart, yEnd);

    s21::Controller control;

    try {
      if (control.ValidateExpression(strOut.toStdString())) {
        char* x_ch = (char*)calloc(100, sizeof(char));
        strOut = transform(strOut);

        QString input;
        for (X = xStart; X <= xEnd; X += step) {
          input = strOut;
          x.push_back(X);
          sprintf(x_ch, "(%f)", X);

          input.replace("x", x_ch);
          y.push_back(control.CalculateExpression(input.toStdString()));
        }
        free(x_ch);

      } else {
        std::cout << "war" << std::endl;
        throw(0);
      }
    } catch (int a) {
      close();
    }
  }

  if (!err) {
    ui->widget->addGraph();
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssDisc, 2));
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    ui->widget->setInteraction(QCP::iRangeDrag, true);
    ui->widget->setInteraction(QCP::iRangeZoom, true);
  }
}

QString Graph::transform(QString ba) {
  ba.replace("acos", "k");
  ba.replace("asin", "z");
  ba.replace("atan", "d");
  ba.replace("sqrt", "q");
  ba.replace("mod", "m");
  ba.replace("cos", "c");
  ba.replace("sin", "s");
  ba.replace("tan", "t");
  ba.replace("ln", "n");
  ba.replace("log", "g");

  return ba;
}
