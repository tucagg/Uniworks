// File.cpp

#include "File.h"
#include <iostream>
#include <sstream>
#include <fstream>

std::string getTimeStamp()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%b %d %H:%M", &tstruct);
    return buf;
}

RegularFile::RegularFile(const std::string &fileName, const std::string &content, const std::string &parentDir, const std::string &timeStampok)
    : name(fileName), content(content), parentDirectory(parentDir), timeStamp(timeStampok) {}

void RegularFile::ls() const
{
    std::cout << "F " << name << "\t\t" << timeStamp << "\t" << content.length() << " Bytes" << std::endl;
}

std::string RegularFile::getName() const
{
    return name;
}

std::string RegularFile::getContent() const
{
    return content;
}

void RegularFile::setContent(const std::string &newContent)
{
    content = newContent;
}

RegularFile::~RegularFile() {}

SoftLinkedFile::SoftLinkedFile(const std::string &fileName, const std::string &target, const std::string &timeStampok, const std::string &parentDir)
    : name(fileName), target(target), timeStamp(timeStampok), parentDirectory(parentDir) {}

void SoftLinkedFile::ls() const
{
    std::cout << "L " << name << "\t\t" << timeStamp << "\t" << target << std::endl;
}

std::string SoftLinkedFile::getName() const
{
    return name;
}

std::string SoftLinkedFile::getTarget() const
{
    return target;
}

SoftLinkedFile::~SoftLinkedFile() {}

Directory::Directory(const std::string &dirName, const std::string &parentDir, const std::string &timeStampok)
    : name(dirName), parentDirectory(parentDir), timeStamp(timeStampok) {}

void Directory::ls() const
{
    std::cout << "D " << name << "\t\t" << timeStamp << std::endl;
    for (const auto &file : files)
    {
        file->ls();
    }
}

std::string Directory::getName() const
{
    return name;
}
std::string Directory::getParentDirectory() const
{
    return parentDirectory;
}

std::string RegularFile::getParentDirectory() const
{
    return parentDirectory;
}

std::string SoftLinkedFile::getParentDirectory() const
{
    return parentDirectory;
}

void Directory::addFile(File *file)
{
    files.push_back(file);
}

const std::vector<File *> &Directory::getFiles() const
{
    return files;
}

Directory::~Directory() {}

void RegularFile::appendContent(const std::string &newContent)
{
    content += newContent;
}

void RegularFile::setParentDirectory(const std::string &parentDir)
{
    parentDirectory = parentDir;
}

std::string File::getTimeStamp() const
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%b %d %H:%M", &tstruct);
    return buf;
}

std::string RegularFile::getTimeStamp() const
{
    if (timeStamp != "")
    {
        return timeStamp;
    }
    else
    {
        return getTimeStamp(); // Base sınıftaki fonksiyonu çağır
    }
}

std::string SoftLinkedFile::getTimeStamp() const
{
    if (timeStamp != "")
    {
        return timeStamp;
    }
    else
    {
        return getTimeStamp(); // Base sınıftaki fonksiyonu çağır
    }
}

std::string Directory::getTimeStamp() const
{
    if (timeStamp != "")
    {
        return timeStamp;
    }
    else
    {
        return getTimeStamp(); // Base sınıftaki fonksiyonu çağır
    }
}

void saveState(const std::vector<File *> &fileSystem, const std::vector<std::string> &currentDirectory)
{
    std::ofstream file("diskSpace.txt");
    if (!file)
    {
        std::cout << "Error opening file for saving state." << std::endl;
        return;
    }

    for (const auto &fileItem : fileSystem)
    {
        if (auto regularFile = dynamic_cast<RegularFile *>(fileItem))
        {
            file << "F " << regularFile->getName() << "\t\t" << regularFile->getTimeStamp() << "\t" << regularFile->getParentDirectory() << "\t" << regularFile->getContent() << std::endl;
        }
        else if (auto softLinkedFile = dynamic_cast<SoftLinkedFile *>(fileItem))
        {
            file << "L " << softLinkedFile->getName() << "\t\t" << softLinkedFile->timeStamp << "\t\t" << softLinkedFile->getTarget()  << "\t\t"<< softLinkedFile->getParentDirectory()<< std::endl;
        }

        else if (auto directory = dynamic_cast<Directory *>(fileItem))
        {
            file << "D " << directory->getName() << "\t\t" << directory->timeStamp << "\t" << directory->getParentDirectory() << std::endl;
        }
    }
    file.close();
    std::cout << "State saved successfully." << std::endl;
}

void loadState(std::vector<File *> &fileSystem, std::vector<std::string> &currentDirectory)
{
    std::ifstream file("diskSpace.txt");
    if (!file)
    {
        std::cout << "No saved state found." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string type, name, month, day, clock, content, target, parentDirectory;
        std::string timeStamp = "";
        iss >> type >> name >> month >> day >> clock;
        timeStamp += month + " " + day + " " + clock;

        if (type == "F")
        {
            iss >> parentDirectory;
            std::getline(iss >> std::ws, content);
            fileSystem.push_back(new RegularFile(name, content, parentDirectory, timeStamp));
        }
        else if (type == "L")
        {
            iss >> target >> parentDirectory;
            fileSystem.push_back(new SoftLinkedFile(name, target, timeStamp, parentDirectory));
        }
        else if (type == "D")
        {
            iss >> parentDirectory;
            if (name == "Desktop")
            {
                continue;
            }
            fileSystem.push_back(new Directory(name, parentDirectory, timeStamp));
        }
    }

    file.close();
    std::cout << "State loaded successfully." << std::endl;
}


void SoftLinkedFile::setParentDirectory(const std::string &parentDir)
{
    parentDirectory = parentDir;
}

void Directory::setParentDirectory(const std::string &parentDir)
{
    parentDirectory = parentDir;
}