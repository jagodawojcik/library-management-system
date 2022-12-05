/*
*EN3085: Object Oriented Programming Computing CW2
*This is the implementation supplementary file
*for the Library Management System.
*Classes definitions are implemented in this file.
*/


#include "coursework.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>




Entry::Entry(std::string entryName, std::string year) :
m_name(entryName),
m_year(year)
{
    
}

void Entry::entryBorrowed(std::string& memberNumber)
{
    m_borrowed = true;
    m_borrowedBy = memberNumber;
}

void Entry::entryReturned()
{
    m_borrowed = false;
    m_borrowedBy.clear(); 
}

void Entry::printDetails() const
{
    std::cout << "Name: " << m_name << std::endl;
    std::cout << "Year: " << m_year << std::endl;
    std::cout << "Borrowed: " << std::boolalpha << m_borrowed << std::endl;
    std::cout << "Borrowed by: " << m_borrowedBy << std::endl;
    std::cout << "Record of borrows: ";
    for (const auto& element : m_borrowedRecord)
    {
        std::cout << element << ", ";
    }
    std::cout << std::endl;
}

void Entry::inputMembers()
{
    while (m_name.empty() || m_year.empty())
    {
        std::cout << "Please provide the name and the year of the entry." << std::endl;
        std::cout << "Name: ";
        std::cin.ignore(); // Ignore the end of line character from the buffer
        std::getline(std::cin >> std::ws, m_name); // Don't accept spaces at the beginning of line
        std::cout << "Year: ";
        std::cin >> m_year;
    }
}

void Entry::updateRecord(std::string& memberNumber, bool inverse)
{
    if (inverse)
        m_borrowedRecord.insert(m_borrowedRecord.begin(), memberNumber);
    else
        m_borrowedRecord.push_back(memberNumber);
}


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


Book::Book(std::string entryName, std::string year, std::string author, std::string publisher, std::string edition) :
Entry(entryName, year),
m_author(author),
m_publisher(publisher),
m_edition(edition)
{

}

Book::Book() :
m_author(),
m_publisher(),
m_edition()
{
    Entry::inputMembers();
    while (m_author.empty() || m_publisher.empty() || m_edition.empty())
    {
        std::cout << "Please provide the author, the publisher and the edition of the book." << std::endl;
        std::cout << "Author: ";
        std::cin.ignore(); // Ignore the end of line character from the buffer
        std::getline(std::cin >> std::ws, m_author); // Don't accept spaces at the beginning of line
        std::cout << "Publisher: ";
        std::getline(std::cin >> std::ws, m_publisher); // Don't accept spaces at the beginning of line
        std::cout << "Edition: ";
        std::getline(std::cin >> std::ws, m_edition); // Don't accept spaces at the beginning of line

    }
}

void Book::printDetails() const
{
    std::cout << "Entry type: Book" << std::endl;
    Entry::printDetails();
    std::cout << "Author: " << m_author << std::endl;
    std::cout << "Publisher: " << m_publisher << std::endl;
    std::cout << "Edition: " << m_edition << std::endl;
}


Film::Film(std::string entryName, std::string year, std::string director, std::string language) :
Entry(entryName, year),
m_director(director),
m_language(language)
{

}

Film::Film() :
m_director(),
m_language()
{
    Entry::inputMembers();
    while (m_director.empty() || m_language.empty())
    {
        std::cout << "Please provide the director and the language of the film." << std::endl;
        std::cout << "Director: ";
        std::cin.ignore(); // Ignore the end of line character from the buffer
        std::getline(std::cin >> std::ws, m_director); 
        std::cout << "Language: ";
        std::cin >> m_language;
    }
}

void Film::printDetails() const
{
    std::cout << "Entry type: Film" << std::endl;
    Entry::printDetails();
    std::cout << "Director: " << m_director << std::endl;
    std::cout << "Language: " << m_language << std::endl;
}


void Catalogue::addEntry(EntryType type)
{	
	const char* const MUSIC_ALBUM_STR = "Music album";
	const char* const BOOK_STR = "Book";
	const char* const FILM_STR = "Film";

    EntryClassified newEntry;
    switch (type)
    {
        case EntryType::MUSIC_ALBUM:
        {
            newEntry.entryType = MUSIC_ALBUM_STR;
            newEntry.pEntry = std::make_shared<MusicAlbum>();
            m_entries.emplace_back(newEntry);
            break;
        }
        case EntryType::BOOK:
        {
            newEntry.entryType = BOOK_STR;
            newEntry.pEntry = std::make_shared<Book>();
            m_entries.emplace_back(newEntry);
            break;
        }
        case EntryType::FILM:
        {
            newEntry.entryType = FILM_STR;
            newEntry.pEntry = std::make_shared<Film>();
            m_entries.emplace_back(newEntry);
            break;
        }
        default:
        {
            break;
        }
    }
}

void Catalogue::removeEntry(unsigned int index)
{
    if (this->numberOfEntries() >= index && index > 0)
    {
        m_entries.erase(m_entries.begin() + index - 1); //erase contents of the Entry the pointer was pointing to
        std::cout << "Removed entry number " << index << std::endl;
    }
    else
    {
        std::cout << "Wrong index" << std::endl;
    }
}

void Catalogue::findEntry(std::string& name)
{
    std::cout << "Entries found: " << std::endl;

    for (auto it = m_entries.begin(); it != m_entries.end(); ++it)
    {
        if (it->pEntry->getName() == name)
        {
            std::cout << it->entryType << ", index: " << std::distance(m_entries.begin(), it) + 1 << std::endl;
        }
    }
}

void Catalogue::printCatalogue() const
{
	const char SEPARATOR = ' ';
	const uint8_t TYPE_WIDTH = 14;
	const uint8_t NUMBER_WIDTH = 5;

    unsigned int counter = 1;

    std::cout << "Number of entries: " << this->numberOfEntries() << std::endl;
    // Header row
    std::cout << std::left << std::setw(NUMBER_WIDTH) << std::setfill(SEPARATOR) << "NO.";
    std::cout << std::left << std::setw(TYPE_WIDTH) << std::setfill(SEPARATOR) << "ENTRY TYPE";
    std::cout << std::left << std::setw(TYPE_WIDTH) << std::setfill(SEPARATOR) << "ENTRY NAME" << std::endl;

    // Data rows
    for (const auto& entry : m_entries)
    {
        std::cout << std::left << std::setw(NUMBER_WIDTH) << std::setfill(SEPARATOR) << counter;
        std::cout << std::left << std::setw(TYPE_WIDTH) << std::setfill(SEPARATOR) << entry.entryType;
        std::cout << entry.pEntry->getName() << std::endl; 
        counter++;
    }
}

void Catalogue::issueItem(unsigned int index, std::string& memberNumber)
{
    if (this->numberOfEntries() >= index && index > 0)
    {
        m_entries[index - 1].pEntry->entryBorrowed(memberNumber);
        m_entries[index - 1].pEntry->updateRecord(memberNumber, true);
        std::cout << "Item issued to member number: " << memberNumber << std::endl;
    }
    else
    {
        std::cout << "Wrong index" << std::endl;
    }
}

void Catalogue::returnItem(unsigned int index)
{
    if (this->numberOfEntries() >= index && index > 0)
    {
        if (m_entries[index - 1].pEntry->getBorrowed() == false)
        {
            std::cout << "Item is not borrowed" << std::endl;
            return;
        }

        m_entries[index - 1].pEntry->entryReturned();
        std::cout << "Item returned" << std::endl;
    }
    else
    {
        std::cout << "Wrong index" << std::endl;
    }
}

void Catalogue::displayDetails(unsigned int index) const
{
    if (this->numberOfEntries() >= index && index > 0)
    {
        m_entries[index - 1].pEntry->printDetails();
    }
    else
    {
        std::cout << "Wrong index" << std::endl;
    }
}

void Catalogue::saveCatalogueToFile(std::string& fileName)
{
	const char* const MUSIC_ALBUM_STR = "Music album";
	const char* const BOOK_STR = "Book";
	const char* const FILM_STR = "Film";
	const char CSV_FILE_SEPARATOR = ';';
	
    std::ofstream file(fileName);
    if (file.is_open())
    {   
        file << "Entry type;Name;Year;Borrowed;Borrowed by;Record of borrows;" 
                "Artist/Author/Director;Label/Publisher/Language;Edition (book)\n";

        for (const auto& entry : m_entries)
        {
            std::vector<std::string> borrowedRecord = entry.pEntry->getBorrowedRecord();
            std::string borrowedRecordInString;
            for (const auto& element : borrowedRecord)
            {
                borrowedRecordInString += element + ",";
            }

            file << entry.entryType << CSV_FILE_SEPARATOR << entry.pEntry->getName() << CSV_FILE_SEPARATOR 
            << entry.pEntry->getYear() << CSV_FILE_SEPARATOR  << entry.pEntry->getBorrowed() << CSV_FILE_SEPARATOR 
            << entry.pEntry->getBorrowedBy() << CSV_FILE_SEPARATOR << borrowedRecordInString << CSV_FILE_SEPARATOR;

            if (entry.entryType == MUSIC_ALBUM_STR)
            {
                file << std::dynamic_pointer_cast<MusicAlbum>(entry.pEntry)->getArtist() << CSV_FILE_SEPARATOR
                << std::dynamic_pointer_cast<MusicAlbum>(entry.pEntry)->getRecordLabel();
            }
            else if (entry.entryType == BOOK_STR)
            {
                file << std::dynamic_pointer_cast<Book>(entry.pEntry)->getAuthor() << CSV_FILE_SEPARATOR
                << std::dynamic_pointer_cast<Book>(entry.pEntry)->getPublisher() << CSV_FILE_SEPARATOR
                << std::dynamic_pointer_cast<Book>(entry.pEntry)->getEdition();
            }
            else if (entry.entryType == FILM_STR)
            {
                file << std::dynamic_pointer_cast<Film>(entry.pEntry)->getDirector() << CSV_FILE_SEPARATOR
                << std::dynamic_pointer_cast<Film>(entry.pEntry)->getLanguage();
            }
            // else do nothing

            file << "\n"; // End of the row
        }
        file.close();
    }
}

void Catalogue::readCatalogueFromFile(std::string& fileName)
{
    
	
	const char* const MUSIC_ALBUM_STR = "Music album";
	const char* const BOOK_STR = "Book";
	const char* const FILM_STR = "Film";
	const char CSV_FILE_SEPARATOR = ';';
	
	
	std::ifstream file(fileName);
    std::string row, ceil;
    std::vector<std::string> separatedRow;

    if (file.is_open())
    {
        std::getline(file, row); // Skip the first row which are the columns' titles
        while (std::getline(file, row))
        {
            std::stringstream rowStringStream(row);

            // Parse the row by a delimiter and split it to a vector
            while (std::getline(rowStringStream, ceil, CSV_FILE_SEPARATOR))
                separatedRow.push_back(ceil);
			
			//separatedRow[0]=TypeName, [1]=Name, ... 

            EntryClassified newEntry;
            if (separatedRow[0] == MUSIC_ALBUM_STR)
            {
                newEntry.entryType = MUSIC_ALBUM_STR;
                newEntry.pEntry = std::make_shared<MusicAlbum>(separatedRow[1], separatedRow[2], separatedRow[6], separatedRow[7]);
            }
            else if (separatedRow[0] == BOOK_STR)
            {
                newEntry.entryType = BOOK_STR;
                newEntry.pEntry = std::make_shared<Book>(separatedRow[1], separatedRow[2], separatedRow[6], separatedRow[7], separatedRow[8]);
            }
            else if (separatedRow[0] == FILM_STR)
            {
                newEntry.entryType = FILM_STR;
                newEntry.pEntry = std::make_shared<Film>(separatedRow[1], separatedRow[2], separatedRow[6], separatedRow[7]);
            }
            // else do nothing

            if (!newEntry.entryType.empty())
            {
                // Check if the item is currently borrowed
                if (separatedRow[3] != "0")
                    newEntry.pEntry->entryBorrowed(separatedRow[4]);

                // Check the record of borrows
                if (!separatedRow[5].empty())
                {
                    std::stringstream recordOfBorrows(separatedRow[5]);
                    std::string singleRecordRead;

                    // Parse the record by a delimiter (',') and split it to a vector
                    while (std::getline(recordOfBorrows, singleRecordRead, ','))
                        newEntry.pEntry->updateRecord(singleRecordRead, false);
                }

                m_entries.emplace_back(newEntry);
            }
            // else do nothing

            separatedRow.clear();
        }

        file.close();
    }
    else
    {
        std::cout << "File not found" << std::endl;
    }
}
