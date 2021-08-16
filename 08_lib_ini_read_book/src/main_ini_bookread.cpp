// Includes

// C++ system headers
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// 3rd party libs headers
#include <SimpleIni.h>
// am folosit fisiere header si cpp
// aici este fisierul Book.h
class Book
{
private:
	std::string name;
	std::string authors;
public:
	Book(std::string Name, std::string Authors);

	//afisare carti
	void print();

	//citire fisier
	std::vector<Book> static readBooksFromIniFile(const std::string& file_name);

};
// pana aici
//apoi fisierul Book.cpp
//#include"Book.h"
//#include <iostream>
Book::Book(std::string Name, std::string Authors) {
	this->name = Name;
	this->authors = Authors;
}

void Book::print() {
	std::cout << this->name << std::endl;
	std::cout << "\t(by " << this->authors << ")" << std::endl;
}

std::vector<Book> Book::readBooksFromIniFile(const std::string& file_name) {
	std::vector<Book> results;

	CSimpleIniA ini;
	ini.SetUnicode();

	SI_Error rc = ini.LoadFile(file_name.c_str());
	if (rc < 0) {
		std::cout << "crapa" << std::endl;
	}

	CSimpleIniA::TNamesDepend sections;
	ini.GetAllSections(sections);
	
	for (auto index : sections) {
		CSimpleIniA::TNamesDepend keys;
		ini.GetAllKeys(index.pItem, keys);
		
			const char* carte_name = ini.GetValue(index.pItem, "name");

			const char* carte_author = ini.GetValue(index.pItem, "author");
			if (carte_name == NULL) {
				break;
			}
			Book carte(carte_name, carte_author);
			results.emplace_back(carte);
		
	}
	return results;
}
//pana aici ulterior fisierul main...

int main()
{
	// Read a collection of books from an INI file.
	// Using the SimpleINI C++ Lib: https://github.com/brofield/simpleini

	// Read the data
	const std::string input_data("ermahgerd_berks.ini");
	std::cout << "Reading the data from " << input_data << std::endl;
	std::vector<Book> books_from_file;
	books_from_file = Book::readBooksFromIniFile(input_data);
	std::cout << "Here are all the books found in the data file..." << std::endl;
	for (auto book : books_from_file)
	{
		book.print();
	}
	return 0;
}