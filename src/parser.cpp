#include "../include/parser.h"
#include <cstdio>
#include <memory>
#include <stdexcept>

std::unique_ptr<Declaration> Parser::parseDeclaration() 
{
	std::unique_ptr<Declaration> decl = std::make_unique<Declaration>(); 

	// Declaration Statement
	if (match(TokenType::KW_DEF)) 
	{
		Token name = consume(TokenType::ID, "Expected variable name");
		consume(TokenType::KW_TYPE, "Expected 'type' keyword");

		for (int type = (int)TokenType::TYPE_BIT; type <= (int)TokenType::TYPE_INT64; type++)
		{
			if (match((TokenType)type)) 
				decl->vartype = (TokenType)type;
		}

		if (decl->vartype == TokenType::UNKNOWN) throw std::runtime_error("Expected valid type"); 

		if (match(TokenType::OP_COLON_EQUAL))
		{
			decl->expr = parseExpr();
		}

		if (!match(TokenType::OP_SEMICOLON)) throw std::runtime_error("Expected ';'");
	}

	return decl;
}

std::unique_ptr<Expr> Parser::parseExpr() 
{	
	std::unique_ptr<Expr> expr = std::make_unique<Expr>(); 
	
	return expr; 
}
