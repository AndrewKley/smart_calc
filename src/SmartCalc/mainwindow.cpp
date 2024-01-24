#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->line->setReadOnly(true);
  connect(ui->add, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->sub, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->mul, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->div, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->nine, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->six, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->three, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->dot, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->two, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->five, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->eight, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->seven, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->four, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->zero, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->one, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->x, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->deg, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->open_brace, SIGNAL(clicked()), this, SLOT(write_chars()));
  connect(ui->close_brace, SIGNAL(clicked()), this, SLOT(write_chars()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::write_chars() {
  QPushButton *button = (QPushButton *)sender();
  ui->line->setText(ui->line->text() + button->text());
}

int MainWindow::is_math_operator(QChar command) {
  int is_math = 0;
  if (command == (QChar)'+' || command == (QChar)'-') is_math = 1;
  if (command == (QChar)'*' || command == (QChar)'/') is_math = 1;
  if (command == (QChar)'^' || command == (QChar)'d') is_math = 1;

  return is_math;
}

int MainWindow::is_digit(char ch) { return ch >= 48 && ch <= 57; }

void MainWindow::on_del_clicked() {
  QString str = ui->line->text();
  str.chop(1);
  ui->line->setText(str);
}

void MainWindow::on_AC_clicked() { ui->line->clear(); }

void MainWindow::on_calculate_clicked() {
  char *str = ui->line->text().toLocal8Bit().data();
  char input_str[256] = {0};
  int i;
  for (i = 0; i < 255 && *str; i++) {
    input_str[i] = *str;
    str++;
  }
  double result = 0;

  double x = (ui->x_value->text()).toDouble();
  int status = OK;
  char expression[SIZE_STR] = {0};

  if ((status = convert_polish_notation(input_str, expression)) == OK)
    status = calc(expression, &result, x);
  if (status == OK) {
    QString tmp = QString::number(result, 'g', 7);
    ui->line->setText(tmp);
  } else if (status == UNCORRECT_BRACKETS) {
    ui->line->setText((QString) "Uncorrect brackets");
  } else if (status == DIVISION_BY_ZERO) {
    ui->line->setText((QString) "Division by zero");
  } else if (status == UNCORRECT_BRACKETS) {
    ui->line->setText((QString) "Operation error");
  } else if (status == ERR_X_VALUE) {
    ui->line->setText((QString) "X value error");
  } else if (status == ERROR) {
    ui->line->setText((QString) "Error operation");
  }
}

void MainWindow::on_graph_clicked() {
  ui->widget->clearGraphs();
  char *line = ui->line->text().toLocal8Bit().data();
  int status = OK;

  double xBegin = (ui->line_x_min_graph->text()).toDouble();
  double xEnd = (ui->line_x_max_graph->text()).toDouble();
  int N = 1e6;
  double h = (xEnd - xBegin) / N;

  char expression[SIZE_STR] = {0};
  status = convert_polish_notation(line, expression);

  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange((ui->line_x_min_graph->text()).toDouble(),
                              (ui->line_x_max_graph->text()).toDouble());

  int graphs_number = 0;
  for (double X = xBegin; X <= xEnd && status == OK; X += h) {
    double Y = 0;
    int status = calc(expression, &Y, X);
    if (status == OK && Y > xBegin && Y < xEnd) {
      x.push_back(X);
      y.push_back(Y);
    } else if (!x.empty()) {
      ui->widget->addGraph();
      ui->widget->graph(graphs_number)->addData(x, y);
      x.clear();
      y.clear();
      graphs_number++;
    }
  }
  ui->widget->addGraph();
  if (!x.empty()) {
    ui->widget->graph(graphs_number)->addData(x, y);
  }
  ui->widget->replot();

  x.clear();
  y.clear();
}
