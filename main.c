#include "Includes.h"

typedef enum{T_SEP, T_IDENT, T_OPER, T_LIT, T_NUM}TokenType;

typedef struct Token{
	TokenType;
	union{
		char sep;
		char *ident;
		char *oper;
		i64 lit;
	};
	struct Token *next;
}Token;

bool isWhiteSepT(const int c)
{
	const uint WHITE_NUM = 4;
	const int whiteChars[WHITE_NUM] = {EOF, ' ', '\n', '\t'};
	for(uint i = 0; i < SEP_NUM; i++){
		if(c == whiteChars[i])
			return true;
	}
	return false;
}

bool isSepT(const int c)
{
	const uint SEP_NUM = 7;
	const int seperatorChars[SEP_NUM] = {EOF, ' ', '\n', '\t', ')', '(', ','};
	for(uint i = 0; i < SEP_NUM; i++){
		if(c == seperatorChars[i])
			return true;
	}
	return false;
}

File* parseToken(Token* token, File *input)
{
	char buffer[256] = {0};
	memset(buffer, '\0', 256);
	const int c=fgetc(input);
	if(isSepT(c)){
		token->TokenType=T_SEP;
		if(isWhiteSepT(c)){
			t->sep = ' ';
			// long prev = ftell(input);
			while(isWhiteSepT(c)){
				// prev = ftell(input);
				c = fgetc(input);
			}
			fseek(input, -1, SEEK_CUR);
		}else{
			t->sep = (char)c;
		}
	}else if(isLit(c)){
		i64 val = (char)c-'0';
		uint place = 0;
		while(isLit(c = fgetc(input))){
			place++
			v
		}
	}
}

Token* lexer(File *input)
{
	Token *tokens = malloc(sizeof(Token));


}

int main(int argc, const char *argv [])
{
	File *fin = fopen("./in.dogein", "r");
	if(fin == NULL){
		printf("Could not open input file in.dogein for reading\n");
		exit(-1);
	}
	File *fout = fopen("./out.dogeout", "w");;
	if(fout == NULL){
		printf("Could not create output file out.dogeout for writing\n");
		exit(-1);
	}


	return 0;
}
