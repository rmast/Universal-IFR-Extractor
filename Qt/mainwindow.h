#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#ifdef UNIVERSAL_IFR_EXTRACTOR
    #define PROJECT_NAME    "Universal IFR Extractor"
    #define PROJECT_VERSION "v0.6"
#else
    #define PROJECT_NAME    "EFI/UEFI IFR Extractor LS"
    #define PROJECT_VERSION "v0.3.2"
#endif

// forward declaration
class InputFileManager;
class OutputFileManager;
class UEFIModuleParser;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_buttonBrowse_clicked();
    void on_buttonExtract_clicked();

private:
    Ui::MainWindow *ui;
    InputFileManager *inputFileManager;
    OutputFileManager *outputFileManager;
    UEFIModuleParser *moduleParser;
    bool isExtractButtonActive;
    //
    void setupUi();
    void setExtractButtonGeometry();
    void lockExtractButton();
    void unlockExtractButton();
    void showError(const QString &message);
    void displayInputFileName();
    void setModuleType(const QString &moduleType);
};
#endif // MAINWINDOW_H
