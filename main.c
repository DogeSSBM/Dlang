#include "Includes.h"
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

typedef enum{TT_STR_LITERAL, TT_INT_LITERAL, TT_IDENT}TokenType;
typedef struct Token{
	TokenType type;
	union{
		char str_val[BUFSIZE];
		int int_val;
		char ident_val[BUFSIZE];
	};
	struct Token *next;
}Token;

void fatal(char* message)
{
	printf("fatal error: %s\n", message);
	exit(1);
}

char* skipWhiteSpace(char* cur)
{
	while (*cur == ' ' || *cur == '\t' || *cur == '\n') cur ++;
	return cur;
}

uint readLine(char *line)
{
	printf("Reading line...\n");
	memset(line, '\0', sizeof(char)*BUFSIZE);
	uint len = 0;
	int c;
	while((c = getchar()) != '\n' && c != EOF && len < BUFSIZE){
		line[len] = c;
		len++;
	}
	printf("...read %2u char(s)\n", len);
	line = skipWhiteSpace(line);
	return len;
}

Token* appendTokens(Token *tokens, Token *more)
{
	if(tokens == NULL)
		return more;
	Token *current = tokens;
	while(current->next != NULL)
		current = current->next;
	current->next = more;
	return tokens;
}

char* getToken(char *buf, Token *token)
{
	uint pos = 0;
	switch(*buf){
		case '"':
			printf("TT_STR_LITERAL\n");
			token->type = TT_STR_LITERAL;
			buf++;
			while(*buf != '"'){
				if(*buf == '\0')
					fatal("Reached end of line with no closing '\"'\n");
				token->str_val[pos++] = *buf;
				buf++;
			}
			printf("\tval: %s\n", token->ident_val);
			buf++;
			break;
		case '0'...'9':
			printf("TT_INT_LITERAL\n");
			token->type = TT_INT_LITERAL;
			while(*buf >='0' && *buf <= '9'){
				token->int_val = token->int_val*10+(*buf - '0');
				buf++;
			}
			printf("\tval: %u\n", token->int_val);
			break;
		case 'a'... 'z':
		case 'A'...'Z':
			printf("TT_IDENT\n");
			token->type = TT_IDENT;
			while((*buf >='a' && *buf <= 'z') || (*buf >= 'A' && *buf <= 'Z')){
				token->ident_val[pos++] = *buf;
				buf++;
			}
			printf("\tval: %s\n", token->ident_val);
			break;
		case '\0':
			break;
		default:
			printf("Unexpected \"%c\"\n", *buf);
			// exit(-1);
			return buf+1;
			break;
	}
	return skipWhiteSpace(buf);
}

Token* tokenizeLine(char *buf)
{
	const uint len = strlen(buf);
	if(len == 0){
		printf("Line empty, skipping\n");
		return NULL;
	}
	printf("Tokenizing line of len %2u\n", len);
	Token *line = calloc(1, sizeof(Token));
	Token *current = line;
	uint i = 1;
	while(strlen(buf) != 0){
		printf("Token count: %2u\n", i);
		i++;
		char* newbuf = getToken(buf, current);
		if(buf == newbuf)
			return line;
		buf = newbuf;
		current->next = calloc(1, sizeof(Token));
		current = current->next;
	}
	return line;
}

// Token* tokenizeLine(Token *tokens, char *buf)
// {
// 	const uint len = strlen(buf);
// 	if(len)
// 		return NULL;
// 	Token *line = calloc(1, sizeof(Token));
// 	if(tokens == NULL) {}
//
// 	Token *current = line;
// 	uint pos = 0;
// 	while(1){
// 		switch(buf[pos]){
// 			case '"':
// 				current->type = TT_STR_LITERAL;
// 				while(*(++buf) != '"' && *buf != '\0'){
// 					current->str_val[pos++] = *buf;
// 				}
// 				if(*buf == '\0')
// 					fatal("Reached end of line with no closing '\"'\n");
// 				pos = 0;
// 				break;
// 			case '0'...'9':
// 				current->type = TT_INT_LITERAL;
// 				while(*(++buf) >='0' && *buf <= '9' && *buf != '\0'){
// 					current->str_val[pos++] = *buf;
// 				}
// 				current->int_val = strToInt(current->str_val);
// 				pos = 0;
// 				break;
// 			case 'a'... 'z':
// 			case 'A'...'Z':
// 				current->type = TT_IDENT;
// 				while(
// 					((*(++buf) >='a' && *buf <= 'z') ||
// 					(*buf >= 'A' && *buf <= 'Z')) &&
// 					*buf != '\0'
// 				){
// 					current->ident_val[pos++] = *buf;
// 				}
// 				pos = 0;
// 				break;
// 			case '\0':
// 				return line;
// 				break;
// 		}
// 		current->next = calloc(1, sizeof(Token));
// 		current = current->next;
// 	}
// 	return tokens;
// }

bool checkExit(Token *tokens)
{
	Token *current = tokens;
	while(current != NULL){
		if(current->type == TT_IDENT && !strncmp(current->ident_val,"exit",strlen("exit")))
			return true;
		current = current->next;
	}
	return false;
}

int main(int argc, char const *argv[])
{
	bool shellExit = false;
	Token *tokens = NULL;
	while(!shellExit){
		char buf[BUFSIZE] = {0};
		if(readLine(buf) > 0)
			tokens = appendTokens(tokens, tokenizeLine(buf));


	}
	return 0;
}
