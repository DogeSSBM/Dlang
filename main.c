#include "Includes.h"


int main(int argc, char const *argv[])
{
	if(argc != 2){
		printf("Usage:\n");
		printf("\t./main.out <input file>\n");
		return -1;
	}
	File *inputFile = fopen(argv[1], "r");
	if(inputFile == NULL){
		printf("Could not open input file \"%s\"\n", argv[1]);
		return -1;
	}
	
	return 0;
}
