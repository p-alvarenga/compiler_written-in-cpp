#include <string>
#include <iostream> // remove

#include "token.h"

std::vector<Token> Lexer::tokenize()
{
	if (src == "")
		throw std::runtime_error("Lexer could not access source string&");

	std::vector<Token> tokens; 
	char c = *this->cur;
	
	while (this->cur != this->eof) 
	{	
		if (c == ' ' || c == '\n') { c = advance(); continue; }
		if (c == '#') [[ unlikely ]] { 
			while (this->cur < this->eof && c != '\n')
				c = advance(); 
			
			c = advance(); 
		} 

		if (isIdentifierStart(c)) [[ likely ]]
		{
			const char* start_ptr = this->cur; 
			Token t; 

			t.col = this->col;
			t.line = this->line;

			while (this->cur < this->eof && isIdentifierChar(c)) 
				c = advance();

			t.textptr = std::string_view(start_ptr, this->cur - start_ptr); 
			t.type = identifyToken(t.textptr, TokenHint::WORD);
			tokens.push_back(t);
		} 
		else if (isOperatorChar(c))
		{
			Token t;

			t.line = this->line;
			t.col  = this->col;
			
			switch (c) 
			{
				case '=':
					if (peek(1) == '=')
					break; 

				case '+':
					break;
			}
		}


		
		//else if (isDigit(c)) 
		//{
			
		//}

		c =	advance();
	}

	return tokens;
}

char Lexer::advance() // ptr to ptr to data
{
	char c = *(++this->cur);

	if (c == '\n') [[ unlikely ]]
	{	
		this->col = 1;
		this->line++;
	}
	else this->col++; 
	return c; 
}

char Lexer::peek(size_t offset) const 
{
	const char* ptr = cur + offset;
	return *ptr; 
	// You are here! Need to write the peek() function to use it in tokenize()
}

TokenType Lexer::identifyToken(const std::string_view& text, TokenHint hint)
{
	switch (hint)
	{
		case TokenHint::WORD: {
			if (text == "true" || text == "false")
				return TokenType::BOOL_LITERAL; 

			auto it = this->keywords.find(text); // Optimize it! (if possible)
			return (it != keywords.end() ? it->second : TokenType::ID);
		}
		case TokenHint::OPERATOR:
			std::cout << "test";

		case TokenHint::NUMERICAL:
			break;
	}

	return TokenType::ID;
}
