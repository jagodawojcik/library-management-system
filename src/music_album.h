#pragma once

#include "entry.h"
#include <string>

/**
 * @brief Class representing a music album
 * 
 */

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
