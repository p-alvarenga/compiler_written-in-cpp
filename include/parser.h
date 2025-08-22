#ifndef PARSER__H__
#define PARSER__H__

#include "token.h"
#include "ast-nodes.h"

class Parser 
{
	private: 
		int m_it;
		std::vector<Token> m_tokens; 

	public: 
		explicit Parser(std::vector<Token>& tkns): m_it(0), m_tokens(t); 
	
		inline Token peek();  
		inline Token advance(); 
		Token consume(TokenType type, const std::string& msg); 

		bool match(TokenType type); 
		std::unique_ptr<Statement> parseStmt();
};

Token Parser::peek() { return m_tokens[it]; }
Token Parser::advance()
{
	it++; 

	if (it >= m_tokens.size())
	{
		Token t(0, 0); 
		t.type = TokenType::EOF; 
		return t; 
	}

	return m_tokens[it];
}

bool Parser::match(TokenType type)
{
	if (m_tokens[it].type == type)
	{
		advance(); 
		return true; 
	}

	return false;
}

Token Parser::consume(TokenType type, const std::string& msg)
{
	if (type == peek().type) return advance(); 
	throw std::runtime_error(msg);
}

#endif
