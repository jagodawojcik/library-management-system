#include <iostream>

#include "entry.h"


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
