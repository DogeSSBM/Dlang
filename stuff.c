"a:=(443+23)*3"		// find '('
"a:=" parse("443+23") "*3"
	"443+23"		// find ###
	parseNum("443")"+23"
		443"+23"		// find ##
		443"+"parse("23")
			443+23		// find +
			parseBinOper()
				443+23	// find VAL + VAL
				466
"a:=" 466 "*3"


"a:=" "443+23" "*3"

typedef struct{
	SymbolType type;

}Symbol;

/*
# is a char '0'...'9'
num(# _)
if


look for '('
	if pattern doesnt match ( _ )
		error
	( _ ) -> parse(_)
look for '#'
	# ... # -> num(# ... #)

*/

typedef enum{T_DIGIT, T_LPAREN, T_RPAREN, T_ASSIGN, T_AR_ADD, T_AR_SUB, T_CMP_EQ, T_CMP_LE, T_CMP_GE, T_CMP_L, T_CMP_G, T_VAR, T_NUMT}TerminalType;
const char* TerminalSymbols[T_NUMT] = {"(", ")", ":=", "+", "-", "=", "<=", ">="}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	for(uint i = 0; i < argc; i++)
		printf("%2u: \"%s\"\n", i, argv[i]);
	return 0;
}
