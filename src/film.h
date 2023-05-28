#pragma once

#include "entry.h"
#include <string>

/**
 * @brief Class representing a film
 * 
 */

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