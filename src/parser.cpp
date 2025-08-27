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
			{
				decl->vartype = (TokenType)type;
				break;
			}
		}

		if (decl->vartype == TokenType::UNKNOWN) 
			throw std::runtime_error("Expected valid type"); 

		if (match(TokenType::OP_COLON_EQUAL))
		{
			decl->expr = parseExpr();
		}

		if (!match(TokenType::OP_SEMICOLON)) 
			throw std::runtime_error("Expected ';'");
	}

	return decl;
}

std::unique_ptr<Expr> Parser::parseExpr() 
{	
	std::unique_ptr<Expr> expr = std::make_unique<Expr>(); 
	
	expr->left = parseTerm(); 

	expr->oper = consumeRange(peek().type, TokenType::OP_MINUS, TokenType::OP_PLUS_EQUAL, "Expected Valid Operator").type;

	expr->right = parseTerm();

	return expr; 
}

std::unique_ptr<Term> Parser::parseTerm()
{
	std::unique_ptr<Term> term = std::make_unique<Term>(); 

	// youre here, things got confused :P
	return term;
}
