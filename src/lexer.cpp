#include <string>
#include <iostream> // remove

#include "../include/lexer.h"

const std::unordered_map<std::string_view, TokenType> Lexer::keywords_map {
    { "def",   TokenType::KW_DEF       },
    { "type",  TokenType::KW_TYPE      },
    { "bit",   TokenType::TYPE_BIT     },
    { "byte",  TokenType::TYPE_BYTE    },
    { "int16", TokenType::TYPE_INT16   },
	{ "true",  TokenType::BOOL_LITERAL }, 
	{ "false", TokenType::BOOL_LITERAL },
}; 

const std::unordered_map<std::string_view, TokenType> Lexer::operators_map {
	{ "=",  TokenType::OP_EQUAL          },
	{ "==", TokenType::OP_EQUAL_EQUAL    },
	{ "+",  TokenType::OP_PLUS           },
	{ "+=", TokenType::OP_PLUS_EQUAL     },
	{ "-",  TokenType::OP_MINUS          },
	{ "-=", TokenType::OP_MINUS_EQUAL    },
	{ "*",  TokenType::OP_STAR           },
	{ "*=", TokenType::OP_STAR_EQUAL     },
	{ "/",  TokenType::OP_SLASH             },
	{ "/=", TokenType::OP_SLASH_EQUAL       },
	{ "^",  TokenType::OP_POWER             },
	{ ":=", TokenType::OP_COLON_EQUAL       },
	{ "!=", TokenType::OP_EXCLAMATION_EQUAL },
	{ "<",  TokenType::OP_LESS_THAN         },
	{ "<=", TokenType::OP_LESS_OR_EQUAL     },
	{ ">",  TokenType::OP_GREATER_THAN      },
	{ ">=", TokenType::OP_GREATER_OR_EQUAL  },
	{ ";",  TokenType::OP_SEMICOLON         },
};

std::vector<Token> Lexer::tokenize()
{
	if (buffer == "")
		throw std::runtime_error("Lexer could not access source string&");

	std::vector<Token> tokens; 
	
	char c = *this->cur;

	while (this->cur != this->eof) 
	{	
		if (c == ' ' || c == '\n') { c = advance(); continue; }
		if (c == '#') [[ unlikely ]] 
		{ 
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
			char next_c = peek(1);

			t.line = this->line;
			t.col  = this->col;
	
			if (isOperatorChar(next_c))		
				t.textptr = std::string_view(cur, 2);
			else
				t.textptr = std::string_view(cur, 1); 

			std::cout << "[[ " << t.textptr << " ]]\n"; 

			t.type = identifyToken(t.textptr, TokenHint::OPERATOR);
			
			c = isOperatorChar(next_c) ? advance(2) : advance(1); 
			tokens.push_back(t);
		}			

		c =	advance();
	}

	return tokens;
}

char Lexer::advance(size_t step) // ptr to ptr to data
{
	const char* nptr = this->cur += step; 

	if (nptr >= this->eof) return '\0'; // manage! 

	if (*nptr == '\n') [[ unlikely ]]
	{	
		this->col = 1;
		this->line++;
	}
	else this->col++; 
	return *nptr; 
}


TokenType Lexer::identifyToken(const std::string_view& text, TokenHint hint) const
{
	switch (hint)
	{
		case TokenHint::WORD: 
		{	
			auto it = this->keywords_map.find(text); // Optimize it! (if possible)
			return it != this->keywords_map.end() ? it->second : TokenType::ID;
		}
		case TokenHint::OPERATOR:
		{
			auto it = this->operators_map.find(text);
			return it != this->operators_map.end() ? it->second : TokenType::ERR_UNKNOWN;
		}
		case TokenHint::NUMERICAL:
			break;
	}

	return TokenType::ID;
}
