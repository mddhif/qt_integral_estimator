#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "muParser.h"
#include "expressionevaluator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    mu::Parser parse(std::string);
    double calculateWithMonteCarlo(const std::string&, double, double);
    double calculateWithTrapezoidal(const std::string&, double ,double);
    double calculateWithGaussian(const std::string&, double ,double);
    void clearText();

private slots:
    void on_pushButton_clicked();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
