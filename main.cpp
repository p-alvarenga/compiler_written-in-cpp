#include <iostream> 
#include <fstream>

#include "include/lexer.h"

std::string readFile(std::string& path);

void test_();

int main(int argc, char* argv[])
{	
	std::string fpath = argv[1]; 
	std::string src = readFile(fpath);

	Lexer lexer(src); 
	std::vector<Token> tokens = lexer.tokenize(); 

	for (Token t : tokens) 
	{	
		std::cout << "[ line: " << t.line << ", column: " << t.col << " ]  " 
			<< t.textptr
			<< " TokenType: " << (int)t.type << std::endl;
	}	

	return 0; 
}

std::string readFile(std::string& path) 
{
	std::ifstream fs(path, std::ios::binary | std::ios::ate); 
	std::string buffer; 

	if (!fs.is_open())
		throw std::runtime_error("COULD NOT OPEN FILE");
	
	std::streamsize size = fs.tellg(); 
	fs.seekg(0, std::ios::beg); 

	buffer.resize(size); // resize std::string to fit fs size
	buffer.assign(std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>());

	return buffer;
}

void test_() { return; }
