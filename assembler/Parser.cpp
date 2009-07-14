

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
		OptionsSection();
		CodeSection();
}

void Parser::OptionsSection() {
		Expect(3);
		while (la->kind == 5 || la->kind == 6) {
			OptionsOptionsSection();
		}
		Expect(4);
}

void Parser::CodeSection() {
		Expect(7);
		while (StartOf(1)) {
			CodeInstruction();
		}
		Expect(4);
}

void Parser::OptionsOptionsSection() {
		if (la->kind == 5) {
			Get();
			Expect(2);
			gen->alloc_instruction_section (atoi (coco_string_create_char (t->val))); 
		} else if (la->kind == 6) {
			Get();
			Expect(1);
			gen->set_output_file_name (coco_string_create_char (t->val)); 
		} else SynErr(21);
}

void Parser::CodeInstruction() {
		switch (la->kind) {
		case 16: {
			Push();
			break;
		}
		case 8: {
			Add();
			break;
		}
		case 19: {
			Sub();
			break;
		}
		case 12: {
			Mult();
			break;
		}
		case 9: {
			Div();
			break;
		}
		case 14: {
			Pop();
			break;
		}
		case 15: {
			Print();
			break;
		}
		case 17: {
			Puts();
			break;
		}
		case 13: {
			Nop();
			break;
		}
		case 18: {
			Reset();
			break;
		}
		case 10: {
			Getop();
			break;
		}
		case 11: {
			Halt();
			break;
		}
		default: SynErr(22); break;
		}
}

void Parser::Push() {
		Expect(16);
		Expect(2);
		gen->emit_push (atof (coco_string_create_char (t->val))); 
}

void Parser::Add() {
		Expect(8);
		gen->emit_add (); 
}

void Parser::Sub() {
		Expect(19);
		gen->emit_sub (); 
}

void Parser::Mult() {
		Expect(12);
		gen->emit_mult (); 
}

void Parser::Div() {
		Expect(9);
		gen->emit_div (); 
}

void Parser::Pop() {
		Expect(14);
		gen->emit_pop (); 
}

void Parser::Print() {
		Expect(15);
		gen->emit_print (); 
}

void Parser::Puts() {
		Expect(17);
		gen->emit_puts (); 
}

void Parser::Nop() {
		Expect(13);
		gen->emit_nop (); 
}

void Parser::Reset() {
		Expect(18);
		gen->emit_reset (); 
}

void Parser::Getop() {
		Expect(10);
		gen->emit_getop (); 
}

void Parser::Halt() {
		Expect(11);
		gen->emit_halt (); 
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
			case 3: s = coco_string_create(L"\".options\" expected"); break;
			case 4: s = coco_string_create(L"\".end\" expected"); break;
			case 5: s = coco_string_create(L"\"@size\" expected"); break;
			case 6: s = coco_string_create(L"\"@name\" expected"); break;
			case 7: s = coco_string_create(L"\".code\" expected"); break;
			case 8: s = coco_string_create(L"\"add\" expected"); break;
			case 9: s = coco_string_create(L"\"div\" expected"); break;
			case 10: s = coco_string_create(L"\"getop\" expected"); break;
			case 11: s = coco_string_create(L"\"halt\" expected"); break;
			case 12: s = coco_string_create(L"\"mult\" expected"); break;
			case 13: s = coco_string_create(L"\"nop\" expected"); break;
			case 14: s = coco_string_create(L"\"pop\" expected"); break;
			case 15: s = coco_string_create(L"\"print\" expected"); break;
			case 16: s = coco_string_create(L"\"push\" expected"); break;
			case 17: s = coco_string_create(L"\"puts\" expected"); break;
			case 18: s = coco_string_create(L"\"reset\" expected"); break;
			case 19: s = coco_string_create(L"\"sub\" expected"); break;
			case 20: s = coco_string_create(L"??? expected"); break;
			case 21: s = coco_string_create(L"invalid OptionsOptionsSection"); break;
			case 22: s = coco_string_create(L"invalid CodeInstruction"); break;

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



