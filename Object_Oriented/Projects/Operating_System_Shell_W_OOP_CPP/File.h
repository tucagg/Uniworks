//File.h

#ifndef FILE_H
#define FILE_H

#include <string>
#include <ctime>
#include <vector>

class File {
public:
    virtual void ls() const = 0;
    virtual std::string getName() const = 0;
    virtual std::string getTimeStamp() const;  // Eklenen fonksiyon
    virtual ~File() {}
    private:
    std::string timeStamp;  // Eklenen fonksiyon
};

class RegularFile : public File {
private:
    std::string name;
    std::string content;
    std::string parentDirectory;
    std::string timeStamp;  // Eklenen fonksiyon

public:
    void ls() const override;
    std::string getName() const override;
    std::string getContent() const;
    void setContent(const std::string& newContent);
    void appendContent(const std::string& newContent); 
    RegularFile(const std::string& fileName, const std::string& content, const std::string& parentDir="", const std::string& timeStamp="");
    std::string getParentDirectory() const;  
    void setParentDirectory(const std::string& parentDir);  
    std::string getTimeStamp() const override;  // Eklenen fonksiyon
    ~RegularFile();
};

class SoftLinkedFile : public File {
private:
    std::string name;
    std::string target;
    std::string parentDirectory;// Eklenen fonksiyon
public:
    SoftLinkedFile(const std::string& fileName, const std::string& target, const std::string& timeStamp="", const std::string& parentDir="");
    void ls() const override;
    std::string getName() const override;
    std::string getTarget() const;
    std::string getTimeStamp() const override;  // Eklenen fonksiyon
    std::string getParentDirectory() const;  // Eklenen fonksiyon
    void setParentDirectory(const std::string& parentDir); // Eklenen fonksiyon
    std::string timeStamp;  // Eklenen fonksiyon
    ~SoftLinkedFile();
};

class Directory : public File {
private:
    std::string name;
    std::string parentDirectory;
    std::vector<File*> files;
   

public:
    Directory(const std::string& dirName, const std::string& parentDir = "", const std::string& timeStamp="");
    void ls() const override;
    std::string getName() const override;
    std::string getParentDirectory() const;
    void addFile(File* file);
    const std::vector<File*>& getFiles() const;
    void setParentDirectory(const std::string& parentDir); // Eklenen fonksiyon
    std::string timeStamp;  // Eklenen fonksiyon
    std::string getTimeStamp() const override;  // Eklenen fonksiyon
    ~Directory();
};

std::string getTimeStamp();
//saveState fonksiyonu kalınan yerden devam edilebilmesini sağla, dosyaları parentDirectory'lerine göre kaydeder, içeriklerini ve timeStamp'lerini de kaydeder.
void saveState(const std::vector<File*>& fileSystem, const std::vector<std::string>& currentDirectory);
void loadState(std::vector<File*>& fileSystem, std::vector<std::string>& currentDirectory);
#endif // FILE_H
