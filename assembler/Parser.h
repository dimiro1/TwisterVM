

#if !defined(COCO_PARSER_H__)
#define COCO_PARSER_H__

#include "AsmGen.h"
#include <ctype.h>


#include "Scanner.h"



class Errors {
public:
	int count;			// number of errors detected

	Errors();
	void SynErr(int line, int col, int n);
	void Error(int line, int col, const wchar_t *s);
	void Warning(int line, int col, const wchar_t *s);
	void Warning(const wchar_t *s);
	void Exception(const wchar_t *s);

}; // Errors

class Parser {
private:
	enum {
		_EOF=0,
		_ID=1,
		_NUM=2,
		_STRING=3,
	};
	int maxT;

	Token *dummyToken;
	int errDist;
	int minErrDist;

	void SynErr(int n);
	void Get();
	void Expect(int n);
	bool StartOf(int s);
	void ExpectWeak(int n, int follow);
	bool WeakSeparator(int n, int syFol, int repFol);

public:
	Scanner *scanner;
	Errors  *errors;

	Token *t;			// last recognized token
	Token *la;			// lookahead token

AsmGen *gen;

	

	Parser(Scanner *scanner);
	~Parser();
	void SemErr(const wchar_t* msg);

	void Assembler();
	void OptionsSection();
	void StaticSection();
	void CodeSection();
	void OptionsOptionsSection();
	void StaticOptions();
	void CodeInstruction();
	void Push();
	void Add();
	void Sub();
	void Mult();
	void Div();
	void Pop();
	void Print();
	void Puts();
	void Nop();
	void Reset();
	void Getop();
	void Goto();
	void Halt();
	void Label();
	void Discard();
	void Clsp();

	void Parse();

}; // end Parser



#endif // !defined(COCO_PARSER_H__)

