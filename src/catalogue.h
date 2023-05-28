#pragma once
#include "entry_classified.h"
#include <string>


class Catalogue
{
public:
    Catalogue() = default;
    ~Catalogue() = default;

    /**
     * @brief Adds a new entry to the catalogue
     * 
     * @param type Type of the entry
     */
    void addEntry(EntryType type);

    /**
     * @brief Removes the entry from the catalogue
     * 
     * @param index Index of the entry to be removed
     */
    void removeEntry(unsigned int index);

    /**
     * @brief Finds the entries and prints their indexes
     * 
     * @param name Name of the entry to be found
     */
    void findEntry(std::string& name);
    
    /**
     * @brief Prints the catalogue in the table view by displaying its index, type and name
     * 
     */
    void printCatalogue() const;

    /**
     * @brief Issues an item to a library member, updates the borrowed status and the record of borrows
     * 
     * @param index Index of the entry to be issued
     * @param memberNumber Library member number
     */
    void issueItem(unsigned int index, std::string& memberNumber);

    /**
     * @brief Returns the item by changing its borrowed status
     * 
     * @param index Index of the entry to be returned
     */
    void returnItem(unsigned int index);

    /**
     * @brief Displays all the details of the entry
     * 
     * @param index Index of the entry
     */
    void displayDetails(unsigned int index) const;
    
    /**
     * @brief Saves the whole catalogue with its details to the .csv file
     * 
     * @param fileName Name of the file to save to
     */
    void saveCatalogueToFile(std::string& fileName);

    /**
     * @brief Reads the .csv file and adds the entries to the catalogue
     * 
     * @param fileName Name of the file to read from
     */
    void readCatalogueFromFile(std::string& fileName);

    inline size_t numberOfEntries() const
    {
        return m_entries.size();
    }

private:
     std::vector<EntryClassified> m_entries;
};