#include "mainwindow.h"

#include <QDebug>
#include <string>

#include "../controller/controller.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_nubs()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_nubs()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_nubs()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_nubs()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_nubs()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_nubs()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_nubs()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_nubs()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_nubs()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_nubs()));
  connect(ui->pushButton_00, SIGNAL(clicked()), this, SLOT(digits_nubs()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digits_nubs()));

  connect(ui->pushButton_opbr, SIGNAL(clicked()), this, SLOT(digits_nubs()));
  connect(ui->pushButton_clbr, SIGNAL(clicked()), this, SLOT(digits_nubs()));

  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_nubs()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(digits_nubs()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_nubs()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(digits_nubs()));

  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_nubs()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(hard_funcs()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(hard_funcs()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(hard_funcs()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(hard_funcs()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(hard_funcs()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(hard_funcs()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(hard_funcs()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(hard_funcs()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(hard_funcs()));

  connect(ui->pushButton_equil, SIGNAL(clicked()), this, SLOT(digits_nubs()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_nubs()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_nubs() {
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == 'x') this->x_bool = true;

  if (button->text() == '=') {
    format_line = (ui->format->text() + '=');
    if (this->x_bool == true && ui->format->text().contains("x")) {
      form = new Form;
      form->show();
      connect(form, &Form::signalForm, this, &MainWindow::slotForm);
    } else {
      calculation();
    }
    this->x_bool = false;
  } else {
      format_line = (ui->format->text() + button->text());
      ui->format->setText(format_line);
  }
}

void MainWindow::on_pushButton_dot_clicked() {
  ui->format->setText(ui->format->text() + '.');
}

void MainWindow::hard_funcs() {
  QPushButton *button = (QPushButton *)sender();
  ui->format->setText(ui->format->text() + button->text() + '(');
}

void MainWindow::on_pushButton_clear_clicked() { ui->format->setText(""); }

void MainWindow::calculation() {
  if (!ui->format->text().isEmpty()) {
    s21::Controller control;
    QString format = transform(format_line);

    try {
      if (control.ValidateExpression(format.toStdString())) {
        char *result_char = (char *)calloc(100, sizeof(char));
        sprintf(result_char, "%g",
                control.CalculateExpression(format.toStdString()));
        QString string(result_char);
        free(result_char);
        ui->format->setText(string);
      } else {
        throw(0);
      }
    } catch (int a) {
      ui->format->setText("You're Invalid. Retry!");
    }
  }
}

void MainWindow::on_pushButton_clear_2_clicked() {
  QString str = ui->format->text();
  if (str.contains("You")) {
    str = "";
  } else {
    str = str.left(str.count() - 1);
  }
  ui->format->setText(str);
}

void MainWindow::slotForm(QString a) {
  format_line.replace("x", a);
  calculation();
}

void MainWindow::on_pushButton_graph_clicked() {
  Graph window(nullptr, ui->format->text());
  window.setModal(true);
  window.exec();
}

QString MainWindow::transform(QString ba) {
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

void MainWindow::on_pushButton_e_clicked() {
  ui->format->setText(ui->format->text() + "e");
}

void MainWindow::on_pushButton_pi_clicked() {
  ui->format->setText(ui->format->text() + "3.141592");
}
