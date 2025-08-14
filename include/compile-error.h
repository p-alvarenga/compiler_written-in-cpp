#ifndef COMPILE_ERROR__H__
#define COMPILE_ERROR__H__

#include <sstream>

class CompileError {
	private: 
		std::string msg; 
		int line;
		int col;
	
	public: 
		explicit CompileError(const std::string& msg, int ln, int col):
			msg(msg), 
			line(ln), 
			col(col)
		{;}

		void throw_err();
};

void CompileError::throw_err() 
{
	std::ostringstream oss; 
	oss << "ERROR: " << this->msg << "(:" << this->line << ":" << this->col << ");\n";
	throw std::runtime_error(oss.str()); 
}

#endif
