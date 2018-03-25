#ifndef MODULEPARSER_H
#define MODULEPARSER_H

#include <QString>

// forward declaration
class InputFileManager;
class OutputFileManager;
class UEFIModuleParser;

class UEFIModuleParser {
private:
    static UEFIModuleParser *_instance;
    UEFIModuleParser();
    UEFIModuleParser(const QString &moduleContent);
    //
    QByteArray moduleContent;
    QString moduleType;
    //
    QString dumpFileName;

public:
    UEFIModuleParser(UEFIModuleParser const &) = delete;
    UEFIModuleParser &operator=(UEFIModuleParser const &) = delete;
    static UEFIModuleParser *instance();
    //
    void setModuleContent(QByteArray moduleContent);
    QString getModuleType();
    bool detectModuleType();
    void setDumpFileName(const QString &fileName);
    void generateDump();
};
#endif // MODULEPARSER_H
