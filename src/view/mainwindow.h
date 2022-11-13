#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "form.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  Form *form;
  bool x_bool = false;
  QString format_line;

 private slots:
  void digits_nubs();
  void hard_funcs();
  void on_pushButton_dot_clicked();
  void on_pushButton_clear_clicked();
  void on_pushButton_clear_2_clicked();
  void calculation();
  QString transform(QString ba);
  void on_pushButton_graph_clicked();

  void on_pushButton_e_clicked();

  void on_pushButton_pi_clicked();

 public slots:
  void slotForm(QString a);
};

#endif  // MAINWINDOW_H
