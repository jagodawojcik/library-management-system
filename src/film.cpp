#include <iostream>
#include <string>

#include "film.h"


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