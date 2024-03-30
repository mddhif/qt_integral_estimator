#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "muParser.h"
#include <random>
#include <QDebug>
#include <QFileDialog>
#include <boost/math/quadrature/trapezoidal.hpp>
#include <boost/math/quadrature/gauss.hpp>

const int N = 100000;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->centralwidget->setStyleSheet("background-color: rgb(87, 227, 137);");


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
           std::string expression = ui->lineEdit_3->text().toStdString();
           int begin = ui->lineEdit_2->text().toDouble();
           int end = ui->lineEdit->text().toDouble();


           auto callCalculator = [](const std::string& expression, double begin, double end, std::function<double(const std::string&, double, double)> calculator) {
              // return calculator(expression, begin, end);
           };

           std::map<int, std::function<double(const std::string&, double, double)>> calculator = {
               {0, [this](const std::string& expression, double begin, double end) { return calculateWithMonteCarlo(expression, begin, end); }},
               {1, [this](const std::string& expression, double begin, double end) { return calculateWithTrapezoidal(expression, begin, end); }},
               {2, [this](const std::string& expression, double begin, double end) { return calculateWithGaussian(expression, begin, end); }}
           };


           double result = calculator[ui->comboBox->currentIndex()](expression, begin, end);

           ui->label_2->setText(QString::number(result));

           QList<QLineEdit*> lineEdits = findChildren<QLineEdit*>(QString(), Qt::FindChildrenRecursively);

                   // Clear text in each found QLineEdit
                   for (QLineEdit *lineEdit : lineEdits) {
                       lineEdit->clear();
                   }

}


mu::Parser MainWindow::parse(std::string input) {

    double x = 5;
    mu::Parser parser;
    parser.SetExpr(input);
    parser.DefineVar("x", &x);

    return parser;

}

double MainWindow::calculateWithMonteCarlo(const std::string& expression, double begin, double end ) {

       double x ;
       double y = 0;
       mu::Parser function = parse(expression) ;
       std::mt19937_64 dre;

       std::uniform_real_distribution<double> urd(begin, end);

       //function.SetExpr(function.GetExpr());
       qDebug() <<  "function expression :" << QString::fromStdString(function.GetExpr());
       function.DefineVar("x", &x);



      for (size_t i = 0; i <= N; ++i)
      {

        x = urd(dre);
        y += function.Eval();


      }

      //qDebug() << "Final result :" << y;

    //  connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::clearText);
      qDebug() << "Y = " << y * (end - begin) / N;
      return y * (end - begin) / N;

}

double MainWindow::calculateWithTrapezoidal(const std::string& expression, double begin, double end) {


    ExpressionEvaluator evaluator(expression);
    qDebug() << "trapezoidal called ..." ;
    return boost::math::quadrature::trapezoidal(evaluator, begin, end,1e-6, N);
}


double MainWindow::calculateWithGaussian(const std::string& expression, double begin, double end) {

    ExpressionEvaluator evaluator(expression);
    qDebug() << "gaussian function ...." ;
    return boost::math::quadrature::gauss<double,10>::integrate(evaluator, begin, end);
}



void MainWindow::clearText() {

    ui->lineEdit_3->clear();
}




