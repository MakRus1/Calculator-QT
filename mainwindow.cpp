#include "mainwindow.h"
#include "ui_mainwindow.h"

double first_num;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits()));

    connect(ui->pushButton_plus_minus, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(operations()));

    connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_multiply, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(math_operations()));

    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits()
{
    QPushButton *button = (QPushButton*) sender();
    QString new_label;

    if (ui->result_show->text().contains(".") && button->text() == "0")
    {
        new_label = ui->result_show->text() + button->text();
    }
    else
    {
        double numbers = (ui->result_show->text() + button->text()).toDouble();
        new_label = QString::number(numbers, 'g', 10);
    }

    ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked()
{
    if (!(ui->result_show->text().contains(".")))
        ui->result_show->setText(ui->result_show->text() + ".");
}

void MainWindow::operations()
{
    QPushButton *button = (QPushButton*) sender();

    if (button->text() == "+/-")
    {
        double numbers = (ui->result_show->text()).toDouble();
        numbers *= -1;
        QString new_label = QString::number(numbers, 'g', 10);

        ui->result_show->setText(new_label);
    }
    else if(button->text() == "%")
    {
        double numbers = (ui->result_show->text()).toDouble();
        numbers *= 0.01;
        QString new_label = QString::number(numbers, 'g', 10);

        ui->result_show->setText(new_label);
    }
}

void MainWindow::math_operations()
{
    QPushButton *button = (QPushButton*) sender();

    first_num = ui->result_show->text().toDouble();

    ui->result_show->setText("");

    button->setChecked(true);
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);

    ui->result_show->setText("0");
}

void MainWindow::on_pushButton_result_clicked()
{
    double second_num, result;

    second_num = ui->result_show->text().toDouble();

    if (ui->pushButton_plus->isChecked())
    {
        result = first_num + second_num;
        QString new_label = QString::number(result, 'g', 10);

        ui->result_show->setText(new_label);

        ui->pushButton_plus->setChecked(false);
    }
    else if (ui->pushButton_minus->isChecked())
    {
        result = first_num - second_num;
        QString new_label = QString::number(result, 'g', 10);

        ui->result_show->setText(new_label);

        ui->pushButton_minus->setChecked(false);
    }
    else if (ui->pushButton_multiply->isChecked())
    {
        result = first_num * second_num;
        QString new_label = QString::number(result, 'g', 10);

        ui->result_show->setText(new_label);

        ui->pushButton_multiply->setChecked(false);
    }
    else if (ui->pushButton_divide->isChecked())
    {
        if (second_num == 0)
        {
            ui->result_show->setText("ERROR");
        }
        else
        {
            result = first_num / second_num;
            QString new_label = QString::number(result, 'g', 10);

            ui->result_show->setText(new_label);

            ui->pushButton_divide->setChecked(false);
        }
    }
}
