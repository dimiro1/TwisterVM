

#include <wchar.h>
#include "Parser.h"
#include "Scanner.h"




void Parser::SynErr(int n) {
	if (errDist >= minErrDist) errors->SynErr(la->line, la->col, n);
	errDist = 0;
}

void Parser::SemErr(const wchar_t* msg) {
	if (errDist >= minErrDist) errors->Error(t->line, t->col, msg);
	errDist = 0;
}

void Parser::Get() {
	for (;;) {
		t = la;
		la = scanner->Scan();
		if (la->kind <= maxT) { ++errDist; break; }

		if (dummyToken != t) {
			dummyToken->kind = t->kind;
			dummyToken->pos = t->pos;
			dummyToken->col = t->col;
			dummyToken->line = t->line;
			dummyToken->next = NULL;
			coco_string_delete(dummyToken->val);
			dummyToken->val = coco_string_create(t->val);
			t = dummyToken;
		}
		la = t;
	}
}

void Parser::Expect(int n) {
	if (la->kind==n) Get(); else { SynErr(n); }
}

void Parser::ExpectWeak(int n, int follow) {
	if (la->kind == n) Get();
	else {
		SynErr(n);
		while (!StartOf(follow)) Get();
	}
}

bool Parser::WeakSeparator(int n, int syFol, int repFol) {
	if (la->kind == n) {Get(); return true;}
	else if (StartOf(repFol)) {return false;}
	else {
		SynErr(n);
		while (!(StartOf(syFol) || StartOf(repFol) || StartOf(0))) {
			Get();
		}
		return StartOf(syFol);
	}
}

void Parser::Assembler() {
		HeadSection();
		CodeSection();
}

void Parser::HeadSection() {
		Expect(3);
		Expect(4);
		Expect(5);
		Expect(2);
		cp->alloc_instructions (atoi (coco_string_create_char (t->val))); 
		Expect(6);
		Expect(4);
}

void Parser::CodeSection() {
		Expect(3);
		Expect(7);
		while (StartOf(1)) {
			CodeInstruction();
		}
		Expect(6);
		Expect(7);
}

void Parser::CodeInstruction() {
		switch (la->kind) {
		case 8: {
			Push();
			break;
		}
		case 9: {
			Add();
			break;
		}
		case 10: {
			Sub();
			break;
		}
		case 11: {
			Mult();
			break;
		}
		case 12: {
			Div();
			break;
		}
		case 13: {
			Pop();
			break;
		}
		case 14: {
			Print();
			break;
		}
		case 15: {
			Puts();
			break;
		}
		case 16: {
			Nop();
			break;
		}
		case 17: {
			Reset();
			break;
		}
		case 18: {
			Getop();
			break;
		}
		case 19: {
			Halt();
			break;
		}
		default: SynErr(21); break;
		}
}

void Parser::Push() {
		Expect(8);
		Expect(2);
		cp->add_instruction (ByteCode (PUSH, atof (coco_string_create_char (t->val)))); 
}

void Parser::Add() {
		Expect(9);
		cp->add_instruction (ByteCode (ADD)); 
}

void Parser::Sub() {
		Expect(10);
		cp->add_instruction (ByteCode (SUB)); 
}

void Parser::Mult() {
		Expect(11);
		cp->add_instruction (ByteCode (MULT)); 
}

void Parser::Div() {
		Expect(12);
		cp->add_instruction (ByteCode (DIV)); 
}

void Parser::Pop() {
		Expect(13);
		cp->add_instruction (ByteCode (POP)); 
}

void Parser::Print() {
		Expect(14);
		cp->add_instruction (ByteCode (PRINT)); 
}

void Parser::Puts() {
		Expect(15);
		cp->add_instruction (ByteCode (PUTS)); 
}

void Parser::Nop() {
		Expect(16);
		cp->add_instruction (ByteCode (NOP)); 
}

void Parser::Reset() {
		Expect(17);
		cp->add_instruction (ByteCode (RESET)); 
}

void Parser::Getop() {
		Expect(18);
		cp->add_instruction (ByteCode (GETOP)); 
}

void Parser::Halt() {
		Expect(19);
		cp->add_instruction (ByteCode (HALT)); 
}



void Parser::Parse() {
	t = NULL;
	la = dummyToken = new Token();
	la->val = coco_string_create(L"Dummy Token");
	Get();
	Assembler();

	Expect(0);
}

Parser::Parser(Scanner *scanner) {
	maxT = 20;

	dummyToken = NULL;
	t = la = NULL;
	minErrDist = 2;
	errDist = minErrDist;
	this->scanner = scanner;
	errors = new Errors();
}

bool Parser::StartOf(int s) {
	const bool T = true;
	const bool x = false;

	static bool set[2][22] = {
		{T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x},
		{x,x,x,x, x,x,x,x, T,T,T,T, T,T,T,T, T,T,T,T, x,x}
	};



	return set[s][la->kind];
}

Parser::~Parser() {
	delete errors;
	delete dummyToken;
}

Errors::Errors() {
	count = 0;
}

void Errors::SynErr(int line, int col, int n) {
	wchar_t* s;
	switch (n) {
			case 0: s = coco_string_create(L"EOF expected"); break;
			case 1: s = coco_string_create(L"ID expected"); break;
			case 2: s = coco_string_create(L"NUM expected"); break;
			case 3: s = coco_string_create(L"\".begin\" expected"); break;
			case 4: s = coco_string_create(L"\"Header\" expected"); break;
			case 5: s = coco_string_create(L"\"@size\" expected"); break;
			case 6: s = coco_string_create(L"\".end\" expected"); break;
			case 7: s = coco_string_create(L"\"Code\" expected"); break;
			case 8: s = coco_string_create(L"\"push\" expected"); break;
			case 9: s = coco_string_create(L"\"add\" expected"); break;
			case 10: s = coco_string_create(L"\"sub\" expected"); break;
			case 11: s = coco_string_create(L"\"mult\" expected"); break;
			case 12: s = coco_string_create(L"\"div\" expected"); break;
			case 13: s = coco_string_create(L"\"pop\" expected"); break;
			case 14: s = coco_string_create(L"\"print\" expected"); break;
			case 15: s = coco_string_create(L"\"puts\" expected"); break;
			case 16: s = coco_string_create(L"\"nop\" expected"); break;
			case 17: s = coco_string_create(L"\"reset\" expected"); break;
			case 18: s = coco_string_create(L"\"getop\" expected"); break;
			case 19: s = coco_string_create(L"\"halt\" expected"); break;
			case 20: s = coco_string_create(L"??? expected"); break;
			case 21: s = coco_string_create(L"invalid CodeInstruction"); break;

		default:
		{
			wchar_t format[20];
			coco_swprintf(format, 20, L"error %d", n);
			s = coco_string_create(format);
		}
		break;
	}
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	coco_string_delete(s);
	count++;
}

void Errors::Error(int line, int col, const wchar_t *s) {
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	count++;
}

void Errors::Warning(int line, int col, const wchar_t *s) {
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
}

void Errors::Warning(const wchar_t *s) {
	wprintf(L"%ls\n", s);
}

void Errors::Exception(const wchar_t* s) {
	wprintf(L"%ls", s); 
	exit(1);
}



