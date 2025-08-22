#include "../include/parser.h"

std::unique_ptr<Statement> Parser::parseStmt() 
{
	std::unique_ptr<Statement> stmt; 

	// Declaration Statement
	if (match(TokenType::KW_DEF)) 
	{
		Token name = consume(TokenType::ID, "Expected variable name");
		consume(TokenType::KW_TYPE, "Exptected 'type' keyword"); 
		
		// Here, it does not expected a unique TokenType, 
		// It could be a lot of them...
		//
		// How to solve it?
	}
}
