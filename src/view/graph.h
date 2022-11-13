#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QMessageBox>
#include <QWidget>

#include "ui_graph.h"

namespace Ui {
class Graph;
}

class Graph : public QDialog {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent, QString abc);
  ~Graph();
  QString transform(QString ba);

 private slots:
  void on_pushButton_graph_clicked();

 private:
  Ui::Graph *ui;
  QString strOut;
  double xStart, xEnd, step, X, yStart, yEnd;
  QVector<double> x, y;
};

#endif  // GRAPH_H
