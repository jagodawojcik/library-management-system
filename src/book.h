#pragma once

#include <string>

#include "entry.h"

/**
 * @brief Class representing a book
 * 
 */

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
