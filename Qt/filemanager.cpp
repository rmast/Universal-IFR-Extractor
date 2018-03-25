//#include <QDebug>
#include <QFileDialog>
#include "filemanager.h"

bool FileManager::isFileNameExist() const
{
    return QFileInfo::exists(fileName)? true: false;
}

const QString FileManager::getFileName() const
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
    if (!isFileNameExist()) throw FileManagerException(ERR_FILE_NOT_EXIST);

    QFile file(fileName);
    QDataStream stream(&file);
    stream.setVersion(5);

    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    fileContent = file.readAll();

    //qDebug() << "Read " << fileContent.size() << " bytes";
    file.close();
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
    //qDebug() << "FileManager Exception: " << getErrorDescription();
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
