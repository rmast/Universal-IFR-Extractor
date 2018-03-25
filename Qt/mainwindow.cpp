//#include <QDebug>
#include <QMessageBox>
#include <QPalette>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filemanager.h"
#include "moduleparser.h"

void MainWindow::showError(const QString &message)
{
    QMessageBox box(QMessageBox::Critical, "Error", message);
    box.exec();
}

void MainWindow::setExtractButtonGeometry() {
    QRect geometry = ui->buttonExtract->geometry();
    geometry.setX((width() - geometry.width()) / 2);
    ui->buttonExtract->setGeometry(geometry);
}

void MainWindow::lockExtractButton() {
    ui->buttonExtract->setEnabled(false);
}

void MainWindow::unlockExtractButton() {
    ui->buttonExtract->setEnabled(true);
}

void MainWindow::setupUi()
{
    setWindowTitle(QString(PROJECT_NAME) + " " + PROJECT_VERSION);
    setExtractButtonGeometry();
    lockExtractButton();
}

void MainWindow::displayInputFileName()
{
    ui->editFileName->setText(inputFileManager->getFileName());
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    inputFileManager(new InputFileManager),
    outputFileManager(new OutputFileManager),
    moduleParser(UEFIModuleParser::instance()),
    isExtractButtonActive(true)
{
    ui->setupUi(this);
    this->setupUi();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete inputFileManager;
    delete outputFileManager;
    delete moduleParser;
}

void MainWindow::setModuleType(const QString &moduleType)
{
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::black);

    if (moduleType.contains("EFI")) {
        palette.setColor(QPalette::WindowText, Qt::darkGreen);
    } else {
        palette.setColor(QPalette::WindowText, Qt::darkRed);
    }

    ui->labelProtocolType->setPalette(palette);
    ui->labelProtocolType->setText(moduleType);
}

void MainWindow::on_buttonBrowse_clicked()
{
    try {
        inputFileManager->openFileDialog();
    } catch (FileManagerException &exception) {
        if (exception.getError() != ERR_EMPTY_FILE_NAME) {
            showError(exception.getErrorDescription());
        }
        return;
    }
    displayInputFileName();

    try {
        inputFileManager->readFile();
    } catch (FileManagerException &exception) {
        showError(exception.getErrorDescription());
        return;
    }

    moduleParser->setModuleContent(inputFileManager->getFileContent());
    if (moduleParser->detectModuleType()) {
        unlockExtractButton();
    } else {
        lockExtractButton();
    }

    setModuleType(moduleParser->getModuleType());
}

void MainWindow::on_buttonExtract_clicked()
{
    try {
        outputFileManager->saveFileDialog();
    } catch (FileManagerException &exception) {
        if (exception.getError() != ERR_EMPTY_FILE_NAME) {
            showError(exception.getErrorDescription());
        }
        return;
    }

    moduleParser->setDumpFileName(outputFileManager->getFileName());
    moduleParser->generateDump();
}
