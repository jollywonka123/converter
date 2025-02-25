#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstring>
#include <string>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);

    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, this, &MainWindow::inputTextChanged);
    connect(ui->comboBox, &QComboBox::currentIndexChanged, this, &MainWindow::inputNumSystemSelected);
    connect(ui->comboBox_2, &QComboBox::currentIndexChanged, this, &MainWindow::outputNumSystemSelected);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onConvertClicked);
    MainWindow::initAppParams();
    MainWindow::initializeContext();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::inputTextChanged() {
    clearOutput();
    char* inputData;
    doOperation(createString, &context, &inputData, MAXSIZE+1);
    strncpy(inputData, ui->plainTextEdit->toPlainText().toStdString().c_str(), MAXSIZE+1);
    doOperation(textUpdating, &context, inputData);
    free(inputData);
    updateLabels();

}

void MainWindow::inputNumSystemSelected() {
    context.input.numSystem = ui->comboBox->currentData().toInt();
    doOperation(checkInputs, &context, context.input.theNumber);
    updateLabels();
    clearOutput();
}

void MainWindow::outputNumSystemSelected() {
    context.output.numSystem = ui->comboBox_2->currentData().toInt();
    clearOutput();
}

void MainWindow::onConvertClicked() {
    if (context.Error != noError)
        QMessageBox::critical(this, "Error", "Incorrect input, please update data before pushing the button.");
    char firtsOutputSym = ui->plainTextEdit_2->toPlainText().toStdString().c_str()[0];
    if (firtsOutputSym == '\0') {
        doOperation(convert, &context);
        showResult();
    }
}

void MainWindow::initAppParams() {
    int numSystemArr[] = {binary, quaternary, octal, decimal, hexadecimal};
    int sizeOfArr = sizeof(numSystemArr)/sizeof(numSystemArr[0]);
    for (int i = 0; i < sizeOfArr; i++) {
        ui->comboBox->setItemData(i, numSystemArr[i]);
        ui->comboBox_2->setItemData(i, numSystemArr[i]);
    }
    ui->label->setStyleSheet("QLabel { color : red; }");

}

void MainWindow::initializeContext() {
    int inpSys = ui->comboBox->currentData().toInt();
    int outSys = ui->comboBox_2->currentData().toInt();
    doOperation(initialization, &context, inpSys, outSys);
}

void MainWindow::updateLabels() {
    switch (context.Error) {
    case wrongInpError:
        ui->label->setText("Incorrect input number");
        break;
    case noError:
        ui->label->setText("");
        break;
    case inputSizeError:
        ui->label->setText("Number is more than 4bytes");
        break;
    default:
        break;
    }
}

void MainWindow::showResult() {
    ui->plainTextEdit_2->setPlainText(context.output.outputNumber);
}

void MainWindow::clearOutput() {
    if (ui->plainTextEdit_2->toPlainText().toStdString().c_str()[0] != '\0')
    {
        context.output.outputNumber[0] = '\0';
        showResult();
    }
}
