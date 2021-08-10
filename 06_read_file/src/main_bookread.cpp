#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

/**
	Define a simple book.
*/
class Book
{
public:
	std::string name;
	std::string authors;

	void print()
	{
		std::cout << name << std::endl;
		std::cout << "\t(by " << authors << ")" << std::endl;
	}

	Book(string Name, string Authors) {
		this->name = Name;
		this->authors = Authors;
	}
};

/**
	Reads a vector of books from a text file.
	Note: the text file shall contain lines of text in pairs for the book name and authors
	E.g.
		BOOK 1
		AUTHOR 1
		BOOK 2
		AUTHOR 2
		BOOK 3
		AUTHOR 1, AUTHOR 2, AUTHOR 3
	@param file_name The name of the file to read from (must include path).
	@return Vector of books.
*/
std::vector<Book*> readBooksFromTextFile(const std::string& file_name)
{
	string line;
	vector<string> Name;
	vector<string> authors;
	vector<Book*> results;
	int counter = 1;
	// TODO: BEGIN read the file -------------------------------------
	ifstream sourceFile(file_name);
	if (sourceFile.is_open()) {
		while (getline(sourceFile, line)) {
			istringstream sir(line);
				
					string A;
					string B;
					sir >> A;
					sir >> B;
					if (counter % 2 != 0) {
						Name.push_back( A + B);
					}
					else {
						authors.push_back(A + B);
					}
				

			
			
			counter++;
		}
		sourceFile.close();
	}
	else {
		cout << "Invalid Connexion" << endl;
	}
	for (int i = 0; i < Name.size(); i++) {
		Book* carte = new Book(Name[i], authors[i]);
		results.push_back(carte);
	}

	// E.g. Book myBook;
	//		...
	//		results.emplace_back(myBook);

	// TODO: END read file and add to results vector ------------------
	return results;
}

int main()
{
	// Read a collection of books from a file.
	// Simple examples can be found everywhere.
	// E.g. https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c

	// Read the data
	std::string input_data("C:/Users/yoyol/source/repos/Tema2/errmahgerd_berks.txt");
	std::cout << "Reading the data from " << input_data << std::endl;
	std::vector<Book*> books_from_file = readBooksFromTextFile(input_data);
	

	// Print the data
	std::cout << "Here are all the books found in the data file..." << std::endl;
	for (int i = 0; i < books_from_file.size(); i++) {
		books_from_file[i]->print();
	}

	return 0;
}