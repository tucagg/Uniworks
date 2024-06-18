#ifndef CATALOG_H
#define CATALOG_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "Entry.h"
#include "FieldFormat.h"

class Catalog : public Entry{
private:
    std::vector<FieldFormat> fieldFormats;
    std::vector<Entry> entries;
public:
    void addEntry( Entry entry); //add entry to entries
    void addField(FieldBase *field); //add field to entry
    size_t getEntryCount() const; //return entries.size()
    const Entry& getEntry(size_t index) const; //return entries[index]
    void sortEntries(const std::string& field);//sort entries by field
    void createFieldFormat(std::string line); //createFieldFormat refer to FieldFormat
    void readData(); //data.txt
    void readCommands(); //commands.txt 
    void searchEntries(const std::string& field, const std::string& value); //search entries by field and value
    int parseLineToField(std::string line, Entry& entry); //parse line to field
    void writeMessageToFile(const std::string& message); //write message to output.txt
    bool compareEntries(const Entry& entry1, const Entry& entry2, const std::string& field); //compare entries by field
    size_t findFieldIndex(const std::string& field) const; //find field index from fieldFormats
    void printEntries() const; //print entries
    void printFieldFormats() const; //print fieldFormats
};

#endif // CATALOG_H