#include <string>
#include <iostream> // remove

#include "../include/lexer.h"

const std::unordered_map<std::string_view, TokenType> Lexer::m_keywords_map {
    { "def",   TokenType::KW_DEF       },
    { "type",  TokenType::KW_TYPE      },
    { "bit",   TokenType::TYPE_BIT     },
    { "byte",  TokenType::TYPE_BYTE    },
    { "int16", TokenType::TYPE_INT16   },
	{ "int32", TokenType::TYPE_INT32   },
	{ "int64", TokenType::TYPE_INT64   },
	{ "uint16", TokenType::TYPE_UINT16 },
	{ "uint32", TokenType::TYPE_UINT32 },
	{ "uint64", TokenType::TYPE_UINT64 },
	{ "true",  TokenType::BOOL_LITERAL }, 
	{ "false", TokenType::BOOL_LITERAL },
}; 

const std::unordered_map<std::string_view, TokenType> Lexer::m_operators_map {
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
	if (m_buffer == "")
		throw std::runtime_error("Lexer could not access source string&");

	std::vector<Token> tokens; 
	
	char c = *m_cur;

	while (m_cur != m_eof) 
	{	
		if (c == ' ' || c == '\n') { c = advance(); continue; }
		if (c == '#') [[ unlikely ]] 
		{ 
			while (m_cur < m_eof && c != '\n')
				c = advance(); 	
			c = advance(); 
		} 

		if (isIdentifierStart(c)) [[ likely ]]
		{
			const char* start_ptr = m_cur; 
			Token t(m_col, m_line); 
	
			while (m_cur < m_eof && isIdentifierChar(c))
				c = advance();

			t.textptr = std::string_view(start_ptr, m_cur - start_ptr); 
			t.type = identifyToken(t.textptr, TokenHint::WORD);
			tokens.push_back(t);
		} 
		else if (isOperatorChar(c))
		{
			Token t(m_col, m_line); 
			char next_c = peek(1);
	
			t.textptr = isOperatorChar(next_c) ? std::string_view(m_cur, 2) : std::string_view(m_cur, 1);
			t.type = identifyToken(t.textptr, TokenHint::OPERATOR);
			
			c = isOperatorChar(next_c) ? advance(2) : advance(1); 
			tokens.push_back(t);
		} 
		else if (isNumericalStart(c)) 
		{
			const char* start_ptr = m_cur; 
			Token t(m_col, m_line); 
			
			t.type = TokenType::NUMERICAL_INT; 

			while (m_cur < m_eof && isNumericalChar(c))
			{
				if (c == '.' && t.type == TokenType::NUMERICAL_INT)
				{
					if (t.type != TokenType::NUMERICAL_INT)
						throw std::runtime_error("Unexpected float character '.'");
					// [[ ATTENTION ]] ^-- CompileError class here 

					t.type = TokenType::NUMERICAL_FLOAT; 
				}

				c = advance();
			}	
			
			t.textptr = std::string_view(start_ptr, m_cur - start_ptr); 
			tokens.push_back(t);
		}
		else if (c == '"')
		{
			Token t(m_col, m_line);

			const char* start_ptr = m_cur; 

			c = advance();

			while (m_cur < m_eof && c != '"') 
				c = advance();

			c = advance();
	
			t.textptr = std::string_view(start_ptr, m_cur - start_ptr);
			t.type = TokenType::STRING;
			
			tokens.push_back(t); 
		}
		else if (c == '(' || c == ')') 
		{
			Token t(m_col, m_line); 
			t.type = c == '(' ? TokenType::LPAREN : TokenType::RPAREN;
			tokens.push_back(t);
		} 
		else 
		{
			Token t(m_col, m_line);
			t.textptr = std::string_view(m_cur, 1);
			t.type = TokenType::UNKNOWN; 
			tokens.push_back(t); 
		}

		c =	advance();
	}

	return tokens;
}

char Lexer::advance(size_t step)
{
	const char* nptr = m_cur += step; 

	if (nptr >= m_eof) return '\0'; // sentinel 

	if (*nptr == '\n') [[ unlikely ]]
	{	
		m_col = 1;
		m_line++;
	}
	else m_col++; 
	return *nptr; 
}


TokenType Lexer::identifyToken(const std::string_view& text, TokenHint hint) const
{
	switch (hint)
	{
		case TokenHint::WORD: 
		{	
			auto it = m_keywords_map.find(text); // [[ optimize ]]
			return it != m_keywords_map.end() ? it->second : TokenType::ID;
		}
		case TokenHint::OPERATOR:
		{
			auto it = m_operators_map.find(text);
			return it != m_operators_map.end() ? it->second : TokenType::UNKNOWN;
		}
	}

	return TokenType::ID;
}
