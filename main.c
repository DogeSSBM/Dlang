#include "Includes.h"

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	for(uint i = 0; i < argc; i++)
		printf("%2u: \"%s\"\n", i, argv[i]);
	return 0;
}
