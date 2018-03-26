//#include <QDebug>
#include <QFileDialog>
#include "filemanager.h"

bool FileManager::isFileNameExist() const
{
    return QFileInfo::exists(fileName)? true: false;
}

QString FileManager::getFileName() const
{
    return fileName;
}

void InputFileManager::openFileDialog()
{
    fileName = QFileDialog::getOpenFileName();

    if (fileName == "") throw FileManagerException(ERR_EMPTY_FILE_NAME);
}

void InputFileManager::readFile()
{
    QFile file(fileName);

    if (!isFileNameExist()) throw FileManagerException(ERR_FILE_NOT_EXIST);
    if (!file.open(QIODevice::ReadOnly)) throw FileManagerException(ERR_IO);

    fileContent = file.readAll();
    file.close();
    //qDebug() << "Read " << fileContent.size() << " bytes"; 
}

QByteArray InputFileManager::getFileContent()
{
    return fileContent;
}

OutputFileManager::OutputFileManager()
{
    title = "Save IFR Dump";
    path = QDir::homePath();
    filters = "IFR Dump (*.txt);;All files (*.*)";
    default_filter= "IFR Dump (*.txt)";
}

void OutputFileManager::saveFileDialog()
{
    fileName = QFileDialog::getSaveFileName(0, title, path, filters, &default_filter);

    if (fileName == "") throw FileManagerException(ERR_EMPTY_FILE_NAME);
}

FileManagerException::FileManagerException(FileError error)
{
    this->error = error;
}

FileError FileManagerException::getError()
{
    return error;
}

const QString FileManagerException::getErrorDescription()
{
    QString str_error;

    switch (error) {
    case ERR_FILE_NOT_EXIST:
        str_error = "File not exist!";
        break;
    case ERR_EMPTY_FILE_NAME:
        str_error = "Empty filename!";
        break;
    case ERR_IO:
        str_error = "File I/O error!";
        break;
    case ERR_NULL_PTR:
        str_error = "Null pointer detected!";
        break;
    default:
        str_error = "Unknown error occured!";
        break;
    }

    return str_error;
}
