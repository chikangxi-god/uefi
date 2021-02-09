#include <stdio.h>

int main(int argc,char *argv[])
{
	if (argc<3)
	{
		printf("error \n");
		return -1;
	}
	FILE* in = fopen(argv[1],"r");
	FILE* out = fopen(argv[2],"w");
	while (1)
	{
		char c=fgetc(in);
		if (feof(in))break;
		if (c=='\n')continue;
		if (c=='0')
		{
			fputc(0,out);
		}
		else if (c=='1')
		{
			fputc(200,out);
		}
	}
	fclose(in);
	fclose(out);
	return 0;
}
