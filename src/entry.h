#pragma once

#include <string>
#include <vector>
#include <memory>

/**
 * @brief Enum class representing the type of the entry
 * 
 */

enum class EntryType
{
    MUSIC_ALBUM,
    BOOK,
    FILM
};

/**
 * @brief Class representing an entry in the catalogue
 * 
 */

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

