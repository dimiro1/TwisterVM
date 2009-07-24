

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

void Parser::Twisterc() {
		if (la->kind == 4) {
			OptionsSection();
		}
		CodeSection();
}

void Parser::OptionsSection() {
		Expect(4);
		while (la->kind == 6) {
			OptionsOptionsSection();
		}
		Expect(5);
}

void Parser::CodeSection() {
		Expect(7);
		while (StartOf(1)) {
			CodeInstruction();
		}
		Expect(5);
}

void Parser::OptionsOptionsSection() {
		Expect(6);
		Expect(1);
		gen->set_output_file_name (coco_string_create_char (t->val)); 
}

void Parser::CodeInstruction() {
		int A, B, C; string label_name; gen->inc_code_line (); 
		switch (la->kind) {
		case 8: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_ABS_N, A, B, C); 
			break;
		}
		case 9: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_ACOS_N, A, B, C); 
			break;
		}
		case 10: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_ADD_N, A, B, C); 
			break;
		}
		case 11: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_ASIN_N, A, B, C); 
			break;
		}
		case 12: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_ATAN_N, A, B, C); 
			break;
		}
		case 13: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_CEIL_N, A, B, C); 
			break;
		}
		case 14: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_COS_N, A, B, C); 
			break;
		}
		case 15: {
			Get();
			Register(C);
			gen->add_instruction (OP_DEC_N, A, B, C); 
			break;
		}
		case 16: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_DIV_N, A, B, C); 
			break;
		}
		case 17: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_FLOOR_N, A, B, C); 
			break;
		}
		case 18: {
			Get();
			Register(A);
			gen->add_instruction (OP_INC_N, A); 
			break;
		}
		case 19: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_LOG_N, A, B, C); 
			break;
		}
		case 20: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_MOD_N, A, B, C); 
			break;
		}
		case 21: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_MULT_N, A, B, C); 
			break;
		}
		case 22: {
			Get();
			Register(A);
			gen->add_instruction (OP_NEG_N, A); 
			break;
		}
		case 23: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_POW_N, A, B, C); 
			break;
		}
		case 24: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_SIN_N, A, B, C); 
			break;
		}
		case 25: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_SQRT_N, A, B, C); 
			break;
		}
		case 26: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_SUB_N, A, B, C); 
			break;
		}
		case 27: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_TAN_N, A, B, C); 
			break;
		}
		case 28: {
			Get();
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_GOTO, label_name); 
			break;
		}
		case 29: {
			Get();
			gen->add_instruction (OP_HALT); 
			break;
		}
		case 30: {
			Get();
			gen->add_instruction (OP_NOP); 
			break;
		}
		case 31: {
			Get();
			Register(A);
			gen->add_instruction (OP_INPUT_N, A); 
			break;
		}
		case 32: {
			Get();
			Register(A);
			gen->add_instruction (OP_INPUT_S, A); 
			break;
		}
		case 33: {
			Get();
			Register(A);
			gen->add_instruction (OP_PRINT_N, A); 
			break;
		}
		case 34: {
			Get();
			Register(A);
			gen->add_instruction (OP_PRINT_S, A); 
			break;
		}
		case 35: {
			Get();
			Register(A);
			gen->add_instruction (OP_PUT_N, A); 
			break;
		}
		case 36: {
			Get();
			Register(A);
			gen->add_instruction (OP_PUT_S, A); 
			break;
		}
		case 37: {
			Get();
			Register(A);
			Register(C);
			gen->add_instruction (OP_MOV_N, A, C); 
			break;
		}
		case 38: {
			Get();
			Register(A);
			Register(C);
			gen->add_instruction (OP_MOV_S, A, C); 
			break;
		}
		case 39: {
			Get();
			int n, index; 
			Expect(2);
			n = atof (coco_string_create_char (t->val));
			index = gen->add_num (n); 
			Register(C);
			gen->add_instruction (OP_STORE_N, index, C); 
			break;
		}
		case 40: {
			Get();
			int index; 
			Expect(3);
			index = gen->add_string (string (coco_string_create_char (t->val))); 
			Register(C);
			gen->add_instruction (OP_STORE_S, index, C); 
			break;
		}
		case 41: {
			Get();
			Register(A);
			Register(B);
			Register(C);
			gen->add_instruction (OP_CONCAT_S, A, B, C); 
			break;
		}
		case 42: {
			Get();
			Register(A);
			Expect(2);
			gen->add_instruction (OP_CHARAT_S, A, 1); 
			break;
		}
		case 43: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_LT_S, A, B, label_name); 
			break;
		}
		case 44: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_GT_S, A, B, label_name); 
			break;
		}
		case 45: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_LTE_S, A, B, label_name); 
			break;
		}
		case 46: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_GTE_S, A, B, label_name); 
			break;
		}
		case 47: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_EQ_S, A, B, label_name); 
			break;
		}
		case 48: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_LT_N, A, B, label_name); 
			break;
		}
		case 49: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_GT_N, A, B, label_name); 
			break;
		}
		case 50: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_LTE_N, A, B, label_name); 
			break;
		}
		case 51: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_GTE_S, A, B, label_name); 
			break;
		}
		case 52: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_EQ_N, A, B, label_name); 
			break;
		}
		case 53: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_NOT_LT_S, A, B, label_name); 
			break;
		}
		case 54: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_NOT_GT_S, A, B, label_name); 
			break;
		}
		case 55: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_NOT_LTE_S, A, B, label_name); 
			break;
		}
		case 56: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_NOT_GTE_S, A, B, label_name); 
			break;
		}
		case 57: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_NOT_EQ_S, A, B, label_name); 
			break;
		}
		case 58: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_NOT_LT_N, A, B, label_name); 
			break;
		}
		case 59: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_NOT_GT_N, A, B, label_name); 
			break;
		}
		case 60: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_NOT_LTE_N, A, B, label_name); 
			break;
		}
		case 61: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_NOT_GTE_N, A, B, label_name); 
			break;
		}
		case 62: {
			Get();
			Register(A);
			Register(B);
			Label(label_name);
			gen->add_label (label_name);
			gen->add_instruction (OP_NOT_EQ_N, A, B, label_name); 
			break;
		}
		case 1: {
			LabelDec(label_name);
			gen->dec_code_line ();
			gen->add_label (label_name, true);
			gen->update_references_to_label_table (label_name);
			
			break;
		}
		default: SynErr(66); break;
		}
}

void Parser::Register(int &n) {
		Expect(64);
		Expect(2);
		n =  atoi (coco_string_create_char (t->val)); 
}

void Parser::Label(string &label_name) {
		Expect(1);
		label_name = string (coco_string_create_char(t->val)); 
}

void Parser::LabelDec(string &label_name) {
		Expect(1);
		label_name = string (coco_string_create_char(t->val)); 
		Expect(63);
}



void Parser::Parse() {
	t = NULL;
	la = dummyToken = new Token();
	la->val = coco_string_create(L"Dummy Token");
	Get();
	Twisterc();

	Expect(0);
}

Parser::Parser(Scanner *scanner) {
	maxT = 65;

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

	static bool set[2][67] = {
		{T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,T,x,x, x,x,x,x, T,T,T,T, T,T,T,T, T,T,T,T, T,T,T,T, T,T,T,T, T,T,T,T, T,T,T,T, T,T,T,T, T,T,T,T, T,T,T,T, T,T,T,T, T,T,T,T, T,T,T,T, T,T,T,x, x,x,x}
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
			case 3: s = coco_string_create(L"STRING expected"); break;
			case 4: s = coco_string_create(L"\".options\" expected"); break;
			case 5: s = coco_string_create(L"\".end\" expected"); break;
			case 6: s = coco_string_create(L"\".name\" expected"); break;
			case 7: s = coco_string_create(L"\".main\" expected"); break;
			case 8: s = coco_string_create(L"\"abs_n\" expected"); break;
			case 9: s = coco_string_create(L"\"acos_n\" expected"); break;
			case 10: s = coco_string_create(L"\"add_n\" expected"); break;
			case 11: s = coco_string_create(L"\"asin_n\" expected"); break;
			case 12: s = coco_string_create(L"\"atan_n\" expected"); break;
			case 13: s = coco_string_create(L"\"ceil_n\" expected"); break;
			case 14: s = coco_string_create(L"\"cos_n\" expected"); break;
			case 15: s = coco_string_create(L"\"dec_n\" expected"); break;
			case 16: s = coco_string_create(L"\"div_n\" expected"); break;
			case 17: s = coco_string_create(L"\"floor_n\" expected"); break;
			case 18: s = coco_string_create(L"\"inc_n\" expected"); break;
			case 19: s = coco_string_create(L"\"log_n\" expected"); break;
			case 20: s = coco_string_create(L"\"mod_n\" expected"); break;
			case 21: s = coco_string_create(L"\"mult_n\" expected"); break;
			case 22: s = coco_string_create(L"\"neg_n\" expected"); break;
			case 23: s = coco_string_create(L"\"pow_n\" expected"); break;
			case 24: s = coco_string_create(L"\"sin_n\" expected"); break;
			case 25: s = coco_string_create(L"\"sqrt_n\" expected"); break;
			case 26: s = coco_string_create(L"\"sub_n\" expected"); break;
			case 27: s = coco_string_create(L"\"tan_n\" expected"); break;
			case 28: s = coco_string_create(L"\"goto\" expected"); break;
			case 29: s = coco_string_create(L"\"halt\" expected"); break;
			case 30: s = coco_string_create(L"\"nop\" expected"); break;
			case 31: s = coco_string_create(L"\"input_n\" expected"); break;
			case 32: s = coco_string_create(L"\"input_s\" expected"); break;
			case 33: s = coco_string_create(L"\"print_n\" expected"); break;
			case 34: s = coco_string_create(L"\"print_s\" expected"); break;
			case 35: s = coco_string_create(L"\"put_n\" expected"); break;
			case 36: s = coco_string_create(L"\"put_s\" expected"); break;
			case 37: s = coco_string_create(L"\"mov_n\" expected"); break;
			case 38: s = coco_string_create(L"\"mov_s\" expected"); break;
			case 39: s = coco_string_create(L"\"store_n\" expected"); break;
			case 40: s = coco_string_create(L"\"store_s\" expected"); break;
			case 41: s = coco_string_create(L"\"concat_s\" expected"); break;
			case 42: s = coco_string_create(L"\"charat_s\" expected"); break;
			case 43: s = coco_string_create(L"\"lt_s\" expected"); break;
			case 44: s = coco_string_create(L"\"gt_s\" expected"); break;
			case 45: s = coco_string_create(L"\"lte_s\" expected"); break;
			case 46: s = coco_string_create(L"\"gte_s\" expected"); break;
			case 47: s = coco_string_create(L"\"eq_s\" expected"); break;
			case 48: s = coco_string_create(L"\"lt_n\" expected"); break;
			case 49: s = coco_string_create(L"\"gt_n\" expected"); break;
			case 50: s = coco_string_create(L"\"lte_n\" expected"); break;
			case 51: s = coco_string_create(L"\"gte_n\" expected"); break;
			case 52: s = coco_string_create(L"\"eq_n\" expected"); break;
			case 53: s = coco_string_create(L"\"not_lt_s\" expected"); break;
			case 54: s = coco_string_create(L"\"not_gt_s\" expected"); break;
			case 55: s = coco_string_create(L"\"not_lte_s\" expected"); break;
			case 56: s = coco_string_create(L"\"not_gte_s\" expected"); break;
			case 57: s = coco_string_create(L"\"not_eq_s\" expected"); break;
			case 58: s = coco_string_create(L"\"not_lt_n\" expected"); break;
			case 59: s = coco_string_create(L"\"not_gt_n\" expected"); break;
			case 60: s = coco_string_create(L"\"not_lte_n\" expected"); break;
			case 61: s = coco_string_create(L"\"not_gte_n\" expected"); break;
			case 62: s = coco_string_create(L"\"not_eq_n\" expected"); break;
			case 63: s = coco_string_create(L"\":\" expected"); break;
			case 64: s = coco_string_create(L"\"$\" expected"); break;
			case 65: s = coco_string_create(L"??? expected"); break;
			case 66: s = coco_string_create(L"invalid CodeInstruction"); break;

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



