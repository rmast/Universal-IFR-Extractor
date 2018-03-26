//#include <QDebug>
#include "moduleparser.h"
#include "../OldWay/EFI.h"
#include "../OldWay/UEFI.h"

UEFIModuleParser *UEFIModuleParser::_instance = nullptr;

UEFIModuleParser *UEFIModuleParser::instance()
{
    return _instance? _instance: _instance = new UEFIModuleParser();
}

UEFIModuleParser::UEFIModuleParser()
{
    this->moduleType = "Unknown";
}

void UEFIModuleParser::setModuleContent(QByteArray moduleContent)
{
    this->moduleContent = moduleContent;
}

QString UEFIModuleParser::getModuleType()
{
    return moduleType;
}

bool UEFIModuleParser::detectModuleType()
{
    std::string buffer = moduleContent.toStdString();
    moduleType = "Unknown";

    // Short file check
    if (buffer.size() < 10) return false;

    // Go through buffer
    for (unsigned int i = 0; i < buffer.size() - 9; i++)
    {
        // Check if an EFI string pakage was found
        if ((buffer[i] != '\x00' || buffer[i + 1] != '\x00' || buffer[i + 2] != '\x00' || buffer[i + 3] != '\x00')
                && buffer[i + 4] == '\x02' && buffer[i + 5] == '\x00'
                && (buffer[i + 6] != '\x00' || buffer[i + 7] != '\x00' || buffer[i + 8] != '\x00' || buffer[i + 9] != '\x00')
                && i + static_cast<unsigned char>(buffer[i + 6])
                + (static_cast<unsigned char>(buffer[i + 7]) << 8)
                + (static_cast<unsigned char>(buffer[i + 8]) << 16)
                + (static_cast<unsigned char>(buffer[i + 9]) << 24) < buffer.size()
                && buffer[i + static_cast<unsigned char>(buffer[i + 6])
                + (static_cast<unsigned char>(buffer[i + 7]) << 8)
                + (static_cast<unsigned char>(buffer[i + 8]) << 16)
                + (static_cast<unsigned char>(buffer[i + 9]) << 24) + 4] >= 'a'
                && buffer[i + static_cast<unsigned char>(buffer[i + 6])
                + (static_cast<unsigned char>(buffer[i + 7]) << 8)
                + (static_cast<unsigned char>(buffer[i + 8]) << 16)
                + (static_cast<unsigned char>(buffer[i + 9]) << 24) + 4] <= 'z'
                && i + static_cast<unsigned char>(buffer[i])
                + (static_cast<unsigned char>(buffer[i + 1]) << 8)
                + (static_cast<unsigned char>(buffer[i + 2]) << 16)
                + (static_cast<unsigned char>(buffer[i + 3]) << 24) < buffer.size()
                && buffer[i + static_cast<unsigned char>(buffer[i])
                + (static_cast<unsigned char>(buffer[i + 1]) << 8)
                + (static_cast<unsigned char>(buffer[i + 2]) << 16)
                + (static_cast<unsigned char>(buffer[i + 3]) << 24) + 4] == '\x02'
                && buffer[i + static_cast<unsigned char>(buffer[i])
                + (static_cast<unsigned char>(buffer[i + 1]) << 8)
                + (static_cast<unsigned char>(buffer[i + 2]) << 16)
                + (static_cast<unsigned char>(buffer[i + 3]) << 24) + 5] == '\x00')
        {
            moduleType = "EFI";
            return true;
            // Otherwise check if a UEFI string pakage was found
        } else if ((buffer[i] != '\x00' || buffer[i + 1] != '\x00' || buffer[i + 2] != '\x00')
                   && buffer[i + 3] == '\x04' && buffer[i + 4] == '\x34' && (buffer[i + 44] == '\x01'
                                                                             || buffer[i + 44] == '\x02') && buffer[i + 45] == '\x00'
                   && buffer[i + 48] == '\x2D'
                   && i + static_cast<unsigned char>(buffer[i])
                   + (static_cast<unsigned char>(buffer[i + 1]) << 8)
                   + (static_cast<unsigned char>(buffer[i + 2]) << 16) < buffer.size()
                   && buffer[i + static_cast<unsigned char>(buffer[i])
                   + (static_cast<unsigned char>(buffer[i + 1]) << 8)
                   + (static_cast<unsigned char>(buffer[i + 2]) << 16) - 1] == '\x00'
                   && buffer[i + static_cast<unsigned char>(buffer[i])
                   + (static_cast<unsigned char>(buffer[i + 1]) << 8)
                   + (static_cast<unsigned char>(buffer[i + 2]) << 16) - 2] == '\x00')
        {
            moduleType = "UEFI";
            return true;
        }
    }

    return false;
}

void UEFIModuleParser::setDumpFileName(const QString &fileName)
{
    dumpFileName = fileName;
}

void UEFIModuleParser::generateDump()
{
    std::string outputFile = dumpFileName.toStdString();
    std::string buffer = moduleContent.toStdString();
    std::vector<std::string> strings;

    // Check if protocol is EFI
    if (moduleType == "EFI")
    {
        // Initialize EFI variables
        std::vector<EFI_IFR_STRING_PACK> stringPackages;
        std::vector<EFI_IFR_FORM_SET_PACK> formSets;

        // Get EFI string packages
        getEFIStringPackages(stringPackages, buffer);

        // Get EFI strings
        getEFIStrings(stringPackages, strings, buffer);

        // Get EFI form sets
        getEFIFormSets(formSets, buffer, stringPackages, strings);

        // Generate EFI IFR dump
        generateEFIIFRDump(outputFile, stringPackages, formSets, buffer, strings);
    }
    // Otherwise check if protocol is UEFI
    else if (moduleType == "UEFI")
    {
        // Initialize UEFI variables
        std::vector<UEFI_IFR_STRING_PACK> stringPackages;
        std::vector<UEFI_IFR_FORM_SET_PACK> formSets;

        // Get UEFI string packages

        getUEFIStringPackages(stringPackages, buffer);

        // Get UEFI strings
        getUEFIStrings(stringPackages, strings, buffer);


        // Get UEFI form sets
        getUEFIFormSets(formSets, buffer, stringPackages, strings);


        // Generate UEFI IFR dump
        generateUEFIIFRDump(outputFile, stringPackages, formSets, buffer, strings);
    }
}
