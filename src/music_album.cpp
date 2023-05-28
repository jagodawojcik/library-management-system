#include "music_album.h"

#include <iostream>
#include <string>


MusicAlbum::MusicAlbum(std::string entryName, std::string year, std::string artist, std::string recordLabel) :
Entry(entryName, year),
m_artist(artist),
m_recordLabel(recordLabel)
{
    
}

MusicAlbum::MusicAlbum() :
m_artist(),
m_recordLabel()
{
    Entry::inputMembers();
    while (m_artist.empty() || m_recordLabel.empty())
    {
        std::cout << "Please provide the artist and the label of the music album." << std::endl;
        std::cout << "Artist: ";
        std::cin.ignore(); // Ignore the end of line character from the buffer
        std::getline(std::cin >> std::ws, m_artist); // Don't accept spaces at the beginning of line
        std::cout << "Label: ";
        std::getline(std::cin >> std::ws, m_recordLabel); // Don't accept spaces at the beginning of line
    }
}

void MusicAlbum::printDetails() const
{
    std::cout << "Entry type: Music Album" << std::endl;
    Entry::printDetails();
    std::cout << "Artist: " << m_artist << std::endl;
    std::cout << "Record label: " << m_recordLabel << std::endl;
}