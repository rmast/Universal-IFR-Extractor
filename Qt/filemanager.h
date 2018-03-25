#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>

// forward declaration
class InputFileManager;
class OutputFileManager;
class UEFIModuleParser;

class FileManager {
protected:
    QString fileName;

public:
    const QString getFileName() const;
    bool isFileNameExist() const;
};

class InputFileManager: public FileManager {
protected:
    QByteArray fileContent;

public:
    void openFileDialog();
    void readFile();
    QByteArray getFileContent();
};

class OutputFileManager: public FileManager {
private:
    QString title, path, filters, default_filter;
public:
    OutputFileManager();
    void saveFileDialog();
};

enum FileError {
    ERR_IO,
    ERR_FILE_NOT_EXIST,
    ERR_EMPTY_FILE_NAME,
    ERR_NULL_PTR
};

class FileManagerException: public std::exception {
private:
    FileError error;

public:
    FileManagerException(FileError error);
    FileError getError();
    const QString getErrorDescription();
};
#endif // FILEMANAGER_H
