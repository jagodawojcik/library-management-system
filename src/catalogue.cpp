#include "catalogue.h"
#include "entry.h"
#include "entry_classified.h"
#include "music_album.h"
#include "book.h"
#include "film.h"


#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>




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
