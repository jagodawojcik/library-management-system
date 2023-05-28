#include <iostream>
#include <string>

#include "book.h"


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
