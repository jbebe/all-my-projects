#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **args)
{
	char *file_name = "C:\\Windows\\system.ini";
	FILE *input_file = fopen(file_name, "rb");
	char output_buff[80] = {0};
	size_t i;
	char j;
	char chr_buff;

	if (input_file != NULL)
	{
		printf("--ADDR-----+--HEX--------------------------------------------+--ASCII----------\n");
		
		for (i = 0, j = 0; fread(&chr_buff, 1, 1, input_file) == 1; ++i)
		{
			if (i%16 == 0)
			{
				sprintf(output_buff, "0x%08X |", i);
			}

			sprintf(output_buff + 12 + j*3, " %02X", chr_buff);

			if (j == 15)
			{
				sprintf(output_buff + 60, " | ");
			}

			sprintf(&output_buff[63+j-1], "%c", '.');

			if (chr_buff > 31)
			{
				sprintf(&output_buff[60 + j], "%c", chr_buff);
			}
			else 
			{
				sprintf(&output_buff[60 + j], "%c", '.');
			}

			++j;

			if (j == 16)
			{
				printf("%s", output_buff);
				putchar('\n');
				j = 0;
			}
		}
	}

	fflush(stdin);
	getchar();
	return 0;
}