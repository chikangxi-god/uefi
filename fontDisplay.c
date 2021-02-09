#include <stdio.h>

int main(int argc, char* argv[])
{
	if (argc<2)
	{
		printf("error\n");
		return 1;
	}
	FILE* in = fopen(argv[1],"r");
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			char c = fgetc(in);
			putchar(c?'1':'0');
		}
		putchar('\n');
	}
	return 0;
}
