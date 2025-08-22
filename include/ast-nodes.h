#ifndef AST_NODES__H__
#define AST_NODES__H__

#include "token.h"

class ASTNode
{
	public:
		virtual ~ASTNode() = default;
};

class Program: public ASTNode 
{
	public: 
		std::vector<std::unique_ptr<Statement>> stmts; 
};

class Statement: public ASTNode {};

class Assignment: public Statement
{	
	public: 
		std::string_view identifier; // pointer ? 
		TokenType op;
		std::unique_ptr<Expr> expr; 
};

class Declaration: public Statement 
{
	std::string_view identifier ;
	TokenType var_type; 
	std::unique_ptr<Expr> expr; 
};

class Expr: public ASTNode 
{ 
	public:

};

#endif
