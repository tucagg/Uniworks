// myShell.cpp
#include "File.h"
#include <vector>
#include <algorithm>
#include <iostream>

int main()
{
    std::vector<File *> fileSystem;
    fileSystem.push_back(new Directory("Desktop"));

    std::vector<std::string> currentDirectory;
    currentDirectory.push_back("Desktop");

    loadState(fileSystem, currentDirectory);

    while (true)
    {
        std::string command;
        std::cout << "> ";
        std::cin >> command;

        if (command == "ls")
        {
            std::string currentPath = "/";
            for (const auto &dir : currentDirectory)
            {
                currentPath += dir + "/";
            }

            std::cout << "Current directory: " << currentPath << std::endl;

            for (const auto &file : fileSystem)
            {
                if (const auto dir = dynamic_cast<Directory *>(file))
                {
                    if (dir->getParentDirectory() == currentDirectory.back())
                    {
                        std::cout << "D " << dir->getName() << "\t\t"
                                  << dir->getTimeStamp() << std::endl;
                    }
                }
                else if (const auto regFile = dynamic_cast<RegularFile *>(file))
                {
                    if (regFile->getParentDirectory() == currentDirectory.back())
                    {
                        std::cout << "F " << regFile->getName() << "\t\t"
                                  << regFile->getTimeStamp() << "\t\t" << regFile->getContent().length() << "Bytes" << std::endl;
                    }
                }
                else if (const auto softLinkFile = dynamic_cast<SoftLinkedFile *>(file))
                {
                    if (softLinkFile->getParentDirectory() == currentDirectory.back())
                    {
                        std::cout << "L " << softLinkFile->getName() << "\t\t"
                                  << softLinkFile->getTimeStamp() << "\t\t" << softLinkFile->getTarget() << std::endl;
                    }
                }
            }
        }
        else if (command == "mkdir")
        {
            std::string dirName;
            std::cin >> dirName;

            fileSystem.push_back(new Directory(dirName, currentDirectory.back(), getTimeStamp()));
        }
        else if(command == "rmdir"){
            std::string dirName;
            std::cin >> dirName;

            auto file = std::find_if(fileSystem.begin(), fileSystem.end(), [&](File *f)
                                     { return f->getName() == dirName; });

            if (file != fileSystem.end() && dynamic_cast<Directory *>(*file) && dynamic_cast<Directory *>(*file)->getParentDirectory() == currentDirectory.back())
            {
                delete *file;
                fileSystem.erase(file);
                std::cout << "Directory removed successfully." << std::endl;
            }
            else if (file != fileSystem.end() && dynamic_cast<RegularFile *>(*file) && dynamic_cast<RegularFile *>(*file)->getParentDirectory() == currentDirectory.back())
            {
                std::cout << "This is not a directory." << std::endl;
            }
            else
            {
                std::cout << "Directory not found." << std::endl;
            }
        }
        else if (command == "cd")
        {
            std::string dirName;
            std::cin >> dirName;

            if (dirName == "..")
            {
                if (currentDirectory.size() > 1)
                {
                    currentDirectory.pop_back();
                    std::cout << "Changed directory to: /" << currentDirectory.back() << std::endl;
                }
                else
                {
                    std::cout << "Already in the root directory." << std::endl;
                }
            }
            else if (dirName == ".")
            {
                std::string currentPath = "/";
                for (const auto &dir : currentDirectory)
                {
                    currentPath += dir + "/";
                }
                std::cout << "Current directory: " << currentPath << std::endl;
            }
            else
            {
                auto it = std::find_if(fileSystem.begin(), fileSystem.end(), [&](File *file)
                                       {
                    if (auto dir = dynamic_cast<Directory*>(file)) {
                        return dir->getName() == dirName;
                    }
                    return false; });

                if (it != fileSystem.end() && dynamic_cast<Directory *>(*it) && dynamic_cast<Directory *>(*it)->getParentDirectory() == currentDirectory.back())
                {
                    currentDirectory.push_back(dirName);
                    std::cout << "Changed directory to: /" << currentDirectory.back() << std::endl;
                }
                else
                {
                    std::cout << "Directory not found: " << dirName << std::endl;
                }
            }
        }
        else if (command == "cd..")
        {
            if (currentDirectory.size() > 1)
            {
                currentDirectory.pop_back();
                std::cout << "Changed directory to: /" << currentDirectory.back() << std::endl;
            }
            else
            {
                std::cout << "Already in the root directory." << std::endl;
            }
        }
        else if (command == "cp")
        {
            std::string source, destination;
            std::cin >> source >> destination;

            auto sourceFile = std::find_if(fileSystem.begin(), fileSystem.end(), [&](File *file)
                                           { return file->getName() == source; });

            auto destinationFile = std::find_if(fileSystem.begin(), fileSystem.end(), [&](File *file)
                                                { return file->getName() == destination; });

            if (sourceFile != fileSystem.end() && destinationFile != fileSystem.end())
            {
                if (auto regularSourceFile = dynamic_cast<RegularFile *>(*sourceFile))
                {
                    if (auto regularDestinationFile = dynamic_cast<RegularFile *>(*destinationFile))
                    {
                        regularDestinationFile->setContent(regularSourceFile->getContent());
                        std::cout << "File content copied successfully." << std::endl;
                    }
                    else
                    {
                        std::cout << "Destination is not a regular file." << std::endl;
                    }
                }
                else
                {
                    std::cout << "Unsupported file type for copying content." << std::endl;
                }
            }
            else
            {
                std::cout << "Source or destination not found." << std::endl;
            }
        }
        else if (command == "rm")
        {
            std::string fileName;
            std::cin >> fileName;

            auto file = std::find_if(fileSystem.begin(), fileSystem.end(), [&](File *f)
                                     { return f->getName() == fileName; });

            if (file != fileSystem.end() && dynamic_cast<RegularFile *>(*file) && dynamic_cast<RegularFile *>(*file)->getParentDirectory() == currentDirectory.back())
            {
                delete *file;
                fileSystem.erase(file);
                std::cout << "File removed successfully." << std::endl;
            }
            else if (file != fileSystem.end() && dynamic_cast<SoftLinkedFile *>(*file) && dynamic_cast<SoftLinkedFile *>(*file)->getParentDirectory() == currentDirectory.back())
            {
                delete *file;
                fileSystem.erase(file);
                std::cout << "Linked file removed successfully." << std::endl;
            }
            else if (file != fileSystem.end() && dynamic_cast<Directory *>(*file) && dynamic_cast<Directory *>(*file)->getParentDirectory() == currentDirectory.back())
            {
                std::cout << "This is not a file." << std::endl;
            }
            else
            {
                std::cout << "File not found." << std::endl;
            }
        }
        else if (command == "link")
        {
            std::string linkName, targetName;
            std::cin >> linkName >> targetName;

            auto targetFile = std::find_if(fileSystem.begin(), fileSystem.end(), [&](File *file)
                                           { return file->getName() == targetName; });

            if (targetFile != fileSystem.end())
            {
                fileSystem.push_back(new SoftLinkedFile(linkName, targetName, getTimeStamp(), currentDirectory.back()));
                std::cout << targetName << " linked to " << linkName << std::endl;
                std::cout << "Link created successfully." << std::endl;
            }
            else
            {
                std::cout << "Target file not found." << std::endl;
            }
        }
        else if (command == "ls-R")
        {
            std::string currentPath = "/";
            for (const auto &dir : currentDirectory)
            {
                currentPath += dir + "/";
            }

            std::cout << "Current directory: " << currentPath << std::endl;

            for (const auto &file : fileSystem)
            {
                if (const auto dir = dynamic_cast<Directory *>(file))
                {

                    std::cout << "D " << dir->getName() << "\t\t"
                              << dir->timeStamp << std::endl;
                }
                else if (const auto regFile = dynamic_cast<RegularFile *>(file))
                {

                    std::cout << "F " << regFile->getName() << "\t\t"
                              << regFile->getTimeStamp() << "\t\t" << regFile->getContent().length() << "Bytes" << std::endl;
                }
                else if (const auto softLinkFile = dynamic_cast<SoftLinkedFile *>(file))
                {
                    std::cout << "L " << softLinkFile->getName() << "\t\t"
                              << softLinkFile->timeStamp << "\t\t" << softLinkFile->getTarget() << std::endl;
                }
            }
        }
        else if (command == "cat>")
        {
            std::string fileName;
            std::cin >> fileName;

            // Dosya bulunamazsa yeni bir dosya oluştur
            auto file = std::find_if(fileSystem.begin(), fileSystem.end(), [&](File *f)
                                     { return f->getName() == fileName; });

            if (file == fileSystem.end())
            {
                fileSystem.push_back(new RegularFile(fileName, "", currentDirectory.back(), getTimeStamp()));
                std::cout << "New file created: " << fileName << std::endl;
            }
            else
            {
                std::cout << "Enter new content to append (Press Enter to finish):" << std::endl;
                std::string newContent;

                do
                {
                    std::getline(std::cin, newContent);
                } while (newContent.empty());

                RegularFile *regularFile = dynamic_cast<RegularFile *>(*file);
                // Dosyaya yeni içeriği ekleme işlemini burada yapabilirsiniz
                if (regularFile)
                {
                    regularFile->appendContent(newContent + "\n");
                    std::cout << "Content appended successfully." << std::endl;
                }
                else
                {
                    std::cerr << "Error: File is not a RegularFile." << std::endl;
                }
            }
        }

        else if (command == "cat")
        {
            std::string fileName;
            std::cin >> fileName;

            auto file = std::find_if(fileSystem.begin(), fileSystem.end(), [&](File *f)
                                     { return f->getName() == fileName; });
            if (file != fileSystem.end())
            {
                if (auto regularFile = dynamic_cast<RegularFile *>(*file))
                {
                    std::cout << "File Content:\n"
                              << regularFile->getContent() << std::endl;
                }
                else if (auto softLinkFile = dynamic_cast<SoftLinkedFile *>(*file))
                {
                    std::string targetName = softLinkFile->getTarget();
                    auto filetar = std::find_if(fileSystem.begin(), fileSystem.end(), [&](File *f)
                                                { return f->getName() == targetName; });
                    if (auto regularFile = dynamic_cast<RegularFile *>(*filetar))
                    {
                        std::cout << "File Content:\n"
                                  << regularFile->getContent() << std::endl;
                    }
                    else
                    {
                        std::cout << "Not a regular file." << std::endl;
                    }
                }
                else
                {
                    std::cout << "Not a regular file." << std::endl;
                }
            }
            else
            {
                std::cout << "File not found." << std::endl;
            }
        }

        else if (command == "exit")
        {
            saveState(fileSystem, currentDirectory);
            break;
        }
        else
        {
            std::cout << "Invalid command." << std::endl;
        }
    }

    for (auto file : fileSystem)
    {
        delete file;
    }

    return 0;
}
