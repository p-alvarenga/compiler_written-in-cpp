#ifndef AST_NODES__H__
#define AST_NODES__H__

#include <locale>
#include <memory>
#include "token.h"

class ASTNode
{
	public:
		virtual ~ASTNode() = default;
};

// forward definition
class Statement; 
class Declaration; 
class Assignment; 
//class PrintStatement

class Expr;
class Term; 
class Expo; 
class Factor;

class Program: public ASTNode 
{
	public: 
		std::vector<std::unique_ptr<Statement>> stmts; 

};

// STATEMENTS ::= Assignment | Declaration | PrintStatement

class Statement: public ASTNode {};

class Assignment: public Statement
{	
	public: 
		std::string_view identifier; // pointer ?
		TokenType op;
		std::unique_ptr<Expr> expr;

		Assignment(): op(TokenType::UNKNOWN) {;}
};

class Declaration: public Statement 
{
	public: 
		std::string_view identifier;
		TokenType vartype; 
		std::unique_ptr<Expr> expr; 

		Declaration(): vartype(TokenType::UNKNOWN) {;} 
};


class Expr: public ASTNode 
{ 
	public:
		bool is_nil;

		std::unique_ptr<Term> left, right;
		TokenType oper; // TokenType::OP_MINUS | TokenType::OP_PLUS

		Expr(): oper(TokenType::UNKNOWN), is_nil(true) {}
};


class Term: public ASTNode 
{
	public:
		std::unique_ptr<Expo> left, right;
		TokenType oper; // OP_SLASH | OP_STAR
};

class Expo: public ASTNode
{
	public:
		std::unique_ptr<Factor> left, right; 
};

class Factor: public ASTNode 
{
	TokenType data_T; 

	public: 
};

#endif
