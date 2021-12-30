#ifndef FUNCTION_PLOTTER_H
#define FUNCTION_PLOTTER_H

#include <QMainWindow>
#include "ui_function_plotter.h"
#include "qcustomplot.h"
#include <QLineEdit>
#include <QPushButton>
#include <QtWidgets>
#include <iostream>
#include <string>
#include <vector>
#include <QVector>
#include <stack>
#include <QTextEdit>
#include <QMessageBox>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class function_plotter; }
QT_END_NAMESPACE

class function_plotter : public QMainWindow
{
    Q_OBJECT

public:
    function_plotter(QWidget *parent = nullptr);
    ~function_plotter();
private slots:
    void on_push_button_clicked();
private:
    Ui::function_plotter *ui;
    QLineEdit *line_edit =new QLineEdit();
    QLineEdit *line_edit2 =new QLineEdit();
    QLineEdit *line_edit3 =new QLineEdit();
    QLineEdit *text_edit =new QLineEdit();
    QWidget *widget= new QWidget() ;
    QHBoxLayout *main_layout =new QHBoxLayout();
    QVBoxLayout *vertical_layout =new QVBoxLayout();
    QHBoxLayout *horizontal_layout = new QHBoxLayout();
    QPushButton *pushButton =new QPushButton();
    QCustomPlot *custom_plot =new QCustomPlot();
    QVBoxLayout *vertical_layout2 =new QVBoxLayout();

};
#endif // FUNCTION_PLOTTER_H
