#include "Catalog.h"

void Catalog::addEntry(Entry entry)
{
    entries.push_back(entry); // Add entry to the end of the vector
}

size_t Catalog::getEntryCount() const
{
    return entries.size(); // Return the number of entries
}

const Entry &Catalog::getEntry(size_t index) const
{
    return entries[index]; // Return the entry at the specified index
}

void Catalog::searchEntries(const std::__1::string &field, const std::__1::string &value)
{
    try
    {
        if (field.empty() || value.empty())
        {
            throw std::runtime_error("Exception: command is wrong");
        }

        int found = 0;
        int index = findFieldIndex(field); // Find the index of the specified field in FieldFormats
        if (index == -1)
        {
            throw std::runtime_error("Exception: command is wrong");
        }
        for (size_t i = 0; i < getEntryCount(); ++i)
        {
            const Entry &entry = getEntry(i); // Get the entry at the specified index
            if (entry.getField(index)->toString().find(value) != std::string::npos)
            {
                std::cout << "search " << '"' << value << '"' << " in " << '"' << field << '"' << std::endl;
                std::cout << entry << std::endl; // Print the entry
                found++;
            }
        }
        if (found == 0)
        {
            throw std::runtime_error("Exception: command is wrong");
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        std::cout << "search " << '"' << value << '"' << " in " << '"' << field << '"' << std::endl;
        return;
    }
}

void Catalog::sortEntries(const std::string &field)
{
    try
    {
        if (field.empty())
        {
            throw std::runtime_error("Exception: command is wrong");
        }
        int index = findFieldIndex(field); // Find the index of the specified field in FieldFormats
        if (index == -1)
        {
            throw std::runtime_error("Exception: command is wrong");
        }
        std::sort(entries.begin(), entries.end(), [index](const Entry &entry1, const Entry &entry2)
                  { return entry1.getField(index)->toString() < entry2.getField(index)->toString(); });
        std::cout << "sort " << '"' << field << '"' << std::endl;
        printEntries(); // Print the sorted entries
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        std::cout << "sort " << '"' << field << '"' << std::endl;
        return;
    }
}

void Catalog::createFieldFormat(std::string line)
{
    std::istringstream iss(line);
    std::string field;
    while (std::getline(iss, field, '|'))
    {
        std::istringstream fieldIss(field);
        std::string name, type, isArrayStr;
        std::getline(fieldIss, name, ':');
        std::getline(fieldIss, type, ':');
        std::getline(fieldIss, isArrayStr, ':');
        bool isArray = isArrayStr == "multi";
        FieldFormat fieldFormat(name, type, isArray, fieldFormats.empty());
        fieldFormats.push_back(fieldFormat);
    }
    printFieldFormats(); // Print the field formats
}

void Catalog::readData()
{
    std::ifstream file;
    try
    {
        file.open("data.txt");
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open file");
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    createFieldFormat(line); // Create field formats

    while (std::getline(file, line)) // Read the entries from the file line by line
    {
        Entry *entry = new Entry();
        int isValid = parseLineToField(line, *entry); // Parse the line to field and check if it is valid
        if (isValid == -1)
        {
            delete entry;
            continue;
        }
        bool isDuplicate = false;
        try
        {
            for (size_t i = 0; i < getEntryCount(); ++i)
            {
                if (compareEntries(*entry, getEntry(i), fieldFormats[0].getName()))
                {
                    throw std::runtime_error("Exception: duplicate entry");
                }
            }
        }
        catch (const std::runtime_error &e)
        {
            std::cout << e.what() << std::endl;
            std::cout << line << std::endl;
            delete entry;
            isDuplicate = true;
        }

        if (isDuplicate)
        {
            continue;
        }
        addEntry(*entry);
        delete entry;
    }
    std::cout << getEntryCount() << " unique entries" << std::endl;

    try
    {
        file.close();
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }
}

bool Catalog::compareEntries(const Entry &entry1, const Entry &entry2, const std::__1::string &field)
{
    // get File count, if the all of the fields are equal, return true
    for (size_t i = 0; i < entry1.getFieldCount(); ++i)
    {
        if (entry1.getField(i)->toString() != entry2.getField(i)->toString())
        {
            return false;
        }
    }
    return true;
}

void Catalog::addField(FieldBase *field)
{
    entries.back().addField(field);
}

int Catalog::parseLineToField(std::string line, Entry &entry)
{
    std::istringstream iss(line);
    std::string field_line;
    int i = 0;

    try
    {
        if (fieldFormats.empty())
        {
            throw std::runtime_error("Exception: missing field");
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        std::cout << line << std::endl;
        return -1;
    }

    try
    {
        int pipeCount = std::count(line.begin(), line.end(), '|'); // Count the number of pipes and check if it is matching with the number of fields
        if (pipeCount != fieldFormats.size() - 1)
        {
            throw std::runtime_error("Exception: missing field");
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        std::cout << line << std::endl;
        return -1;
    }

    while (std::getline(iss, field_line, '|'))
    {
        if (fieldFormats[i].isArrayField())
        { // Check if the field is an array field
            std::istringstream fieldIss(field_line);
            if (fieldFormats[i].getType() == "string")
            {
                std::string value;
                std::vector<std::string> values;
                while (std::getline(fieldIss, value, ':'))
                {
                    values.push_back(value);
                }
                Field<std::string> *field = new Field<std::string>(values);
                entry.addField(field);
            }
            else if (fieldFormats[i].getType() == "integer")
            {
                std::vector<int> intValues;
                std::string value;
                while (std::getline(fieldIss, value, ':'))
                {
                    if (!value.empty())
                    {
                        intValues.push_back(std::stoi(value));
                    }
                }
                Field<int> *field = new Field<int>(intValues);
                entry.addField(field);
            }
            else if (fieldFormats[i].getType() == "double")
            {
                std::vector<double> doubleValues;
                std::string value;
                while (std::getline(fieldIss, value, ':'))
                {
                    if (!value.empty())
                    {
                        doubleValues.push_back(std::stod(value));
                    }
                }
                Field<double> *field = new Field<double>(doubleValues);
                entry.addField(field);
            }
            else if (fieldFormats[i].getType() == "float")
            {
                std::vector<float> floatValues;
                std::string value;
                while (std::getline(fieldIss, value, ':'))
                {
                    if (!value.empty())
                    {
                        floatValues.push_back(std::stof(value));
                    }
                }
                Field<float> *field = new Field<float>(floatValues);
                entry.addField(field);
            }
            else if (fieldFormats[i].getType() == "char")
            {
                std::vector<char> charValues;
                std::string value;
                while (std::getline(fieldIss, value, ':'))
                {
                    if (!value.empty())
                    {
                        charValues.push_back(value[0]);
                    }
                }
                Field<char> *field = new Field<char>(charValues);
                entry.addField(field);
            }
        }
        else
        { // If the field is not an array field
            std::istringstream fieldIss(field_line);
            std::string value;
            std::getline(fieldIss, value);
            if (fieldFormats[i].getType() == "string")
            {
                if (!value.empty())
                {
                    Field<std::string> *field = new Field<std::string>(value);
                    entry.addField(field);
                }
                else
                {
                    Field<std::string> *field = new Field<std::string>(""); // Handle empty string field
                    entry.addField(field);
                }
            }
            else if (fieldFormats[i].getType() == "integer")
            {
                if (!value.empty())
                {
                    Field<int> *field = new Field<int>(std::stoi(value));
                    entry.addField(field);
                }
                else
                {
                    Field<int> *field = new Field<int>(0); // Handle empty integer field
                    entry.addField(field);
                }
            }
            else if (fieldFormats[i].getType() == "double")
            {
                if (!value.empty())
                {
                    Field<double> *field = new Field<double>(std::stod(value));
                    entry.addField(field);
                }
                else
                {
                    Field<double> *field = new Field<double>(0.0); // Handle empty double field
                    entry.addField(field);
                }
            }
            else if (fieldFormats[i].getType() == "float")
            {
                if (!value.empty())
                {
                    Field<float> *field = new Field<float>(std::stof(value));
                    entry.addField(field);
                }
                else
                {
                    Field<float> *field = new Field<float>(0.0f); // Handle empty float field
                    entry.addField(field);
                }
            }
            else if (fieldFormats[i].getType() == "char")
            {
                if (!value.empty())
                {
                    Field<char> *field = new Field<char>(value[0]);
                    entry.addField(field);
                }
                else
                {
                    Field<char> *field = new Field<char>('\0'); // Handle empty char field
                    entry.addField(field);
                }
            }
        }
        i++;
    }
    return 0;
}

const FieldBase *Entry::getField(size_t index) const
{
    return fields[index]; // Return the field at the specified index
}

void Catalog::readCommands()
{
    std::ifstream file;
    try
    {
        file.open("commands.txt");
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open file");
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        try
        {
            //getline ile al ve  search "Joe Satriani" in "artist" buna göre tırnak içini bir stringe at
            std::istringstream iss(line);
            std::string command;
            iss >> command;
            if (command == "search")
            {
                std::string search;
                std::string in;
                std::string field;
                //if search contains " then take the string until the next "
                //boşluk sayısı 4 ise 
                int bosluk = std::count(line.begin(), line.end(), ' ');
                if(bosluk >3){
                    iss >> search >> in;
                    std::string temp;
                    search = search + temp + '"';
                    iss >> in >> field;
                }
                else{
                    iss >> search >> in >> field;
                }
                if (iss.rdbuf()->in_avail() != 0)
                {
                    throw std::runtime_error("Exception: command is wrong");
                }
                search = search.substr(1, search.size() - 2); // Remove quotes
                field = field.substr(1, field.size() - 2);    // Remove quotes
                searchEntries(field, search);
            }
            else if (command == "sort")
            {
                std::string field;
                iss >> field;
                if (iss.rdbuf()->in_avail() != 0) // Check if there are any more fields
                {
                    throw std::runtime_error("Exception: command is wrong");
                }
                field = field.substr(1, field.size() - 2); // Remove quotes
                sortEntries(field);
            }
            else
            {
                throw std::runtime_error("Exception: command is wrong");
            }
        }
        catch (const std::runtime_error &e)
        {
            std::cout << e.what() << std::endl;
            std::cout << line << std::endl;
            continue;
        }
    }

    try
    {
        file.close();
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void Catalog::writeMessageToFile(const std::string &message)
{
    std::ofstream file("output.txt", std::ios::app);
    if (!file.is_open())
    {
        std::cout << "Could not open file" << std::endl;
    }
    file << message << std::endl;
    file.close();
}

size_t Catalog::findFieldIndex(const std::__1::string &field) const
{ // Find the index of the specified field in FieldFormats
    for (size_t i = 0; i < fieldFormats.size(); ++i)
    {
        if (fieldFormats[i].getName() == field)
        {
            return i;
        }
    }
    return -1;
}

void Catalog::printEntries() const
{
    for (size_t i = 0; i < getEntryCount(); ++i)
    {
        std::cout << getEntry(i) << std::endl; // Print the entry with the output operator <<
    }
}

void Catalog::printFieldFormats() const
{
    int size = fieldFormats.size();
    for (auto i : fieldFormats)
    {
        size -= 1;
        std::cout << i.getName(); // Print the field formats
        if (size != 0)
        {
            std::cout << "|";
        }
    }
    std::cout << std::endl;
}