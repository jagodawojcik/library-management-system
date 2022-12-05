/*
*EN3085: Object Oriented Programming Computing CW2
*This is the header supplementary file
*for the Library Management System.
*Classes declarations are implemented in this file.
*/
#pragma once
#include <string>
#include <vector>
#include <memory>

enum class EntryType
{
    MUSIC_ALBUM,
    BOOK,
    FILM
};


class Entry
{
public:
    Entry() = default;
    Entry(std::string entryName, std::string year);
    ~Entry() = default;

    /**
     * @brief Assigns the entry to a library member
     * 
     * @param memberNumber Number of the library member
     */
    void entryBorrowed(std::string& memberNumber);

    /**
     * @brief Returns borrowed entry
     * 
     */
    void entryReturned();

    /**
     * @brief Prints the details of the entry, virtual keyword means that this function exists in the derived classes
     * 
     */
    virtual void printDetails() const;

    /**
     * @brief Updates the record of borrows of the entry with the given member number
     * 
     * @param memberNumber Number of library membership
     * @param inverse Indicates if the order of adding elements has to be inverted
     */
    void updateRecord(std::string& memberNumber, bool inverse);

    inline bool getBorrowed() const
    {
        return m_borrowed;
    }

    inline std::string getBorrowedBy() const
    {
        return m_borrowedBy;
    }

    inline std::string getName() const
    {
        return m_name;
    }

    inline std::string getYear() const
    {
        return m_year;
    }

    inline std::vector<std::string> getBorrowedRecord() const
    {
        return m_borrowedRecord;
    }
protected:
    /**
     * @brief Allows to dynamically write all the details of the entry
     * 
     */
    void inputMembers();

private:
    bool m_borrowed = false;
    std::string m_borrowedBy;
    std::string m_name;
    std::string m_year;
    std::vector<std::string> m_borrowedRecord;
};


class MusicAlbum : public Entry
{
public:
    MusicAlbum(std::string entryName, std::string year, std::string artist, std::string recordLabel);
    MusicAlbum();
    ~MusicAlbum() = default;

    /**
     * @brief Prints the details of the entry
     * 
     */
    virtual void printDetails() const;

    inline std::string getArtist() const
    {
        return m_artist;
    }

    inline std::string getRecordLabel() const
    {
        return m_recordLabel;
    }
private:
    std::string m_artist;
    std::string m_recordLabel;

};


class Book : public Entry
{
public:
    Book(std::string entryName, std::string year, std::string author, std::string publisher, std::string edition);
    Book();
    ~Book() = default;

    /**
     * @brief Prints the details of the entry
     * 
     */
    virtual void printDetails() const;

    inline std::string getAuthor() const
    {
        return m_author;
    }

    inline std::string getPublisher() const
    {
        return m_publisher;
    }

    inline std::string getEdition() const
    {
        return m_edition;
    }
private:
    std::string m_author;
    std::string m_publisher;
    std::string m_edition;
};


class Film : public Entry
{
public:
    Film(std::string entryName, std::string year, std::string director, std::string language);
    Film();
    ~Film() = default;

    /**
     * @brief Prints the details of the entry
     * 
     */
    virtual void printDetails() const;

    inline std::string getDirector() const
    {
        return m_director;
    }

    inline std::string getLanguage() const
    {
        return m_language;
    }
private:
    std::string m_director;
    std::string m_language;
};


struct EntryClassified
{
    std::string entryType;
    std::shared_ptr<Entry> pEntry;
};


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
