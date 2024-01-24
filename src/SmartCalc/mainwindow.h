#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string.h>

#include <QByteArray>
#include <QMainWindow>
#include <QString>
#include <QVector>

#ifdef __cplusplus
extern "C" {
#endif

#include "../s21_calc.h"

#ifdef __cplusplus
}
#endif

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
  QVector<double> x, y;
  int is_digit(char ch);
  int is_math_operator(QChar command);

 private slots:
  void write_chars();
  void on_del_clicked();
  void on_graph_clicked();
  void on_AC_clicked();
  void on_calculate_clicked();
};
#endif  // MAINWINDOW_H
