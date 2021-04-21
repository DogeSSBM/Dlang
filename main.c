buf#include "Includes.h"
#define BUFSIZE		1024
/*
identifier is a case-insenstive sequence of letters and numbers but not starting with a number
variable is: identifier
literal is a number or a string enclosed in quotes ".
expression is: variable or function-call or literal
assignment is: variable = expression

procedure-call is: identifier [expression [, ...]]
function-call is: ( procedure-call )

statement is a line that does not have ! as its first non-blank character and is not emptystatement
statement is: assignment or procedure-call

builtin

x = (open "code.txt")
eval x

b = (open "data.txt")
c = 5
d = (add c, (open "data2.txt"))
a = (div (add b, c), d)

write "out.txt", a

exit

------

# (fun, x) -> (sub x, 50)
*/


void fatal(char* message) {
	printf("fatal error: %s\n", message);
	exit(1);
}




// reads entry into line, returns the number of chars read (excludes newline)
uint readLine(char *line)
{
	memset(line, '\0', sizeof(char)*BUFSIZE);
	uint len = 0;
	int c;
	while(c = getchar() != '\n' && c != EOF && len < BUFSIZE){
		line[len] = c;
		len++;
	}
	return len;
}

char* skipWhites(char* cur)
{
	while (*cur != ' ' && *cur != '\t' && *cur != '\n') cur ++;
	return cur;
}



typedef enum{TT_STR_LITERAL, TT_INT_LITERAL, TT_IDENT}TokenType;

typedef struct Token{
	TokenType type;
	union{
		char str_val[BUFSIZE];
		int int_val;
		char ident_val[BUFSIZE];
	}
	struct Token *next;
}Token;

Token* tokenizeLine(Token *tokens, char *buf)
{
	const uint len = strlen(buf);
	if(len)
		return NULL;
	Token *line = calloc(1, sizeof(Token));
	Token *current = line;
	uint pos = 0;
	// int nskip;
	while(1){
		switch(buf[pos]){
			case '"':
				current->type = TT_STR_LITERAL;
				while(*(++buf) != '"' && *buf != '\0'){
					current->str_val[pos++] = *buf;
				}
				if(*buf == '\0')
					fatal("Reached end of line with no closing '\"'\n");
				pos = 0;
				// if (tokenize_strLiteral(buf, &nskip, tokens)) {
				// 	pos += nskip;
				// } else {
				// 	fatal("error in string literal");
				// }
				break;
			case '0'...'9':
				current->type = TT_INT_LITERAL;
				while(*(++buf) >='0' && *buf <= '9' && *buf != '\0'){
					current->str_val[pos++] = *buf;
				}
				current->int_val = strToInt(current->str_val);
				pos = 0;
				break;
			case 'a'... 'z':
			case 'A'...'Z':
				current->type = TT_IDENT;
				while(
					(*(++buf) >='a' && *buf <= 'z') ||
					(*buf >= 'A' && *buf <= 'Z') &&
					*buf != '\0'
				){
					current->ident_val[pos++] = *buf;
				}
				pos = 0;
				break;
			case '\0':
				return line;
				break;
		}
		current->next = calloc(1, sizeof(Token));
		current = current->next;
	}
}


bool checkExit(Token *tokens)
{
	Token *current = tokens;
	while(current != NULL){
		if(current->TokenType == TT_IDENT && !strncmp(current->ident_val,"exit",strlen("exit")))
			return true;
		current = current->next;
	}
	return false;
}

void appendTokens(Token *tokens, Token *more)
{
	if(tokens == NULL)
		tokens = more;
	Token *current = tokens;
	while(current->next != NULL)
		current = current->next;
	current->next = more;
}

int main(int argc, char const *argv[])
{
	bool shellExit = false;
	Token *tokens = NULL;
	while(!shellExit){
		char buf[BUFSIZE] = {0};
		const uint len = readLine(buf);
		tokenizeLine(tokens, buf, len);
		statement(line)


	}
	return 0;
}

bool tokenize_expression(char *buf, int *nskip, Token* first) {
	if(tokenize_strLiteral(buf, nskip, first)) return true;
	if(tokenize_intLiteral(buf, nskip, first)) return true;
	if(tokenize_identifier(buf, nskip, first)) return true;
	return false;
}

bool is_digit(char c) {
	return (c >= '0' && c <= '9');
}

bool is_valid_ident(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || is_digit(c);
}

bool tokenize_strLiteral(char *buf, int* nskip, Token* first)
{
	if (*buf == '"') {
		char *cur = buf + 1;
		// buf points at first character past opening quote
		// (can be an ending quote too)
		// iterate before end is reached
		while (*cur != '"' && *cur != '\0') cur++;
		if (*cur == '\0') fatal("unexpected end to string literal");

		if ((int)(cur - buf) > BUFSIZE) fatal("string literal too long");

		Token* newtok = (Token*) malloc(sizeof(Token));
		newtok -> type = TT_STR_LITERAL;
		memset(newtok->str_val, '\0', BUFSIZE * sizeof(char));
		strncpy(newtok->str_val, buf + 1, (int)(cur - buf) - 1);
		newtok->next = NULL;
		appendTokens(first, newtok);

		*nskip = (int)(cur - buf);

		return true;
	}
	return false;
}

bool tokenize_identifier(char *buf, int* nskip, Token* first)
{
	if (is_valid_ident(*buf) && !is_digit(*buf)) {
		char *cur = buf;
		// buf points at first character past opening quote
		// (can be an ending quote too)
		// iterate before end is reached
		while (is_valid_ident(*buf)) cur++;
		if (*cur == '\0') fatal("unexpected end to string literal");

		if ((int)(cur - buf) > BUFSIZE) fatal("string literal too long");

		Token* newtok = (Token*) malloc(sizeof(Token));
		newtok -> type = TT_STR_LITERAL;
		memset(newtok->str_val, '\0', BUFSIZE * sizeof(char));
		strncpy(newtok->str_val, buf + 1, (int)(cur - buf) - 1);
		newtok->next = NULL;
		appendTokens(first, newtok);

		*nskip = (int)(cur - buf);

		return true;
	}
	return false;
}

bool tokenize_intLiteral(char *buf, int* nskip, Token* first)
{
	if (is_digit(*buf) || *buf == '-') {
		char* cur = buf;
		char tempbuf[BUFSIZE];

		while (is_digit(*cur) && *cur != '\0') cur++;

		if ((int)(cur - buf) + 1 > BUFSIZE) fatal("string literal too long");
		memset(tempbuf, '\0', BUFSIZE * sizeof(char));
		strncpy(tempbuf, buf, (int)(cur - buf));

		Token* newtok = (Token*) malloc(sizeof(Token));
		newtok -> type = TT_STR_LITERAL;
		sscanf(tempbuf, "%d", &newtok->int_val);
		newtok->next = NULL;
		appendTokens(first, newtok);

		*nskip = (int)(cur - buf);

		return true;
	}
	return false;
}
