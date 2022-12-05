/*
*This is a software developed for the purpose of
*EN3085: Object Oriented Programming Computing CW2
*
*This is the Library Management System 
*It allows to store and manage detailed information
*on books, films and movies collections.
*
*This is the main function.
*Run the programme to start.
*
*Developed by: Jagoda Wojcik (C1835840)
*Last modified: 11.05.2022
*/


#include "coursework.h"

#include <iostream>
#include <limits>


int main()
{
	enum class Choices
	{
		DISPLAY_ALL = 1,
		ADD_NEW = 2,
		REMOVE = 3,
		FIND = 4,
		ISSUE = 5,
		RETURN = 6,
		DISPLAY_DETAILS = 7,
		SAVE_AS_FILE = 8,
		READ_FROM_FILE = 9,
		EXIT = 10
	};

    Catalogue catalogue;
    while (true)
    {
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "1 - display all entries in the catalogue" << std::endl;
        std::cout << "2 - add new entry" << std::endl;
        std::cout << "3 - remove entry" << std::endl;
        std::cout << "4 - find entry" << std::endl;
        std::cout << "5 - issue an item" << std::endl;
        std::cout << "6 - return an item" << std::endl;
        std::cout << "7 - display the details of the entry" << std::endl;
        std::cout << "8 - save the catalogue to a file" << std::endl;
        std::cout << "9 - read the catalogue from the file" << std::endl;
        std::cout << "10 - exit" << std::endl << "Choice: ";

        unsigned short choiceInput = 0;
        std::cin >> choiceInput;
		Choices choice = static_cast<Choices>(choiceInput);
        switch (choice)
        {
			case Choices::DISPLAY_ALL:
            {
                catalogue.printCatalogue();
                break;
            }
			case Choices::ADD_NEW:
            {
                std::cout << "What kind of entry would you like to add?" << std::endl;
                std::cout << "1 - music album" << std::endl << "2 - book" << std::endl << "3 - film" << std::endl;
                
                unsigned short choiceEntryType = 0;
                std::cin >> choiceEntryType;
                switch (choiceEntryType)
                {
                    case 1:
                    {
                        catalogue.addEntry(EntryType::MUSIC_ALBUM);
                        std::cout << "Press enter to continue";
                        break;
                    }
                    case 2:
                    {
                        catalogue.addEntry(EntryType::BOOK);
                        std::cout << "Press enter to continue";
                        break;
                    }
                    case 3:
                    {
                        catalogue.addEntry(EntryType::FILM);
                        break;
                    }
                    default:
                    {
                        std::cout << "Unknown type" << std::endl;
                        break;
                    }
                }
                break;
            }
            case Choices::REMOVE:
            {
                std::cout << "Please provide the index of the entry to be removed: ";
                unsigned int index = 0;
                std::cin >> index;

                if (!std::cin.fail())
                    catalogue.removeEntry(index);
                else
                    std::cout << "Wrong index" << std::endl;

                break;
            }
            case Choices::FIND:
            {
                std::cout << "Please provide the name of the entry you would like to find: ";
                std::string name;
                std::cin.ignore(); // Ignore the end of line character from the buffer
                std::getline(std::cin >> std::ws, name); // Allow spaces in the input but ignore initial whitespaces
                catalogue.findEntry(name);

                std::cout << "Press enter to continue";
                break;
            }
            case Choices::ISSUE:
            {
                std::cout << "Please provide the index of the entry you would like to issue: ";
                unsigned int index = 0;
                std::cin >> index;
                if (!std::cin.fail())
                {
                    std::cout << "Please provide the member number: ";
                    std::string memberNumber;
                    std::cin >> memberNumber;
                    catalogue.issueItem(index, memberNumber);
                }
                else
                {
                    std::cout << "Wrong index" << std::endl;
                }
                break;
            }
            case Choices::RETURN:
            {
                std::cout << "Please provide the index of the entry you would like to return: ";
                unsigned int index = 0;
                std::cin >> index;
                if (!std::cin.fail())
                    catalogue.returnItem(index);
                else
                    std::cout << "Wrong index" << std::endl;

                break;
            }
            case Choices::DISPLAY_DETAILS:
            {
                std::cout << "Please provide the index of the entry you would like to display the details for: ";
                unsigned int index = 0;
                std::cin >> index;
                if (!std::cin.fail())
                    catalogue.displayDetails(index);
                else
                    std::cout << "Wrong index" << std::endl;

                break;
            }
            case Choices::SAVE_AS_FILE:
            {
                std::cout << "Please provide the name of the file: ";
                std::string fileName;
                std::cin.ignore(); // Ignore the end of line character from the buffer
                std::getline(std::cin >> std::ws, fileName); // Allow spaces in the input but ignore initial whitespaces 
                fileName += ".csv";
                catalogue.saveCatalogueToFile(fileName);

                std::cout << "Press enter to continue";
                break;
            }
            case Choices::READ_FROM_FILE:
            {
                std::cout << "Please provide the name of the file: ";
                std::string fileName;
                std::cin.ignore(); // Ignore the end of line character from the buffer
                std::getline(std::cin, fileName); // Allow spaces in the input but ignore initial whitespaces 
                fileName += ".csv";
                catalogue.readCatalogueFromFile(fileName);

                std::cout << "Press enter to continue";
                break;
            }
            case Choices::EXIT:
            {
                return 0; //exit
            }
            default:
            {
                std::cout << "Unknown action" << std::endl;
                break;
            }
        }
        // Clear the buffer to prevent an infinite loop when the non integer value was provided
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << std::endl << std::endl << std::endl;
    }
    
    return 0;
}
