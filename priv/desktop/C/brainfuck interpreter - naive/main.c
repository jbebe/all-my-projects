#include <stdio.h>
#define MAX_SIZE 32768
#define OP 0
#define VAL 1

int main(void)
{
	static char		bf_buffer[MAX_SIZE];
	char			bf_code_raw[MAX_SIZE];
	unsigned short	bf_code[MAX_SIZE][2],
					cursor = 0,
					i,
					j,
					k,
					subloop_count = 0;

	scanf("%[^\n]s", bf_code_raw);

	// nyers bf script �talak�t�sa, el�sz�r csak t�m�r�t�s, [ �s ] jelet ut�na dolgozzuk fel
	for (i = 0, k = 0; bf_code_raw[i] != '\0';)
	{
		switch (bf_code_raw[i])
		{
		case '+':
		case '>':
		case '<':
		case '-':
			bf_code[k][OP] = bf_code_raw[i];
			for (j = i + 1; bf_code_raw[j] == bf_code_raw[i]; ++j);
			bf_code[k][VAL] = j - i;
			i = j;
			++k;
			break;
		case '.':
		case ',':
		case '[':
		case ']':
			bf_code[k][OP] = bf_code_raw[i];
			++i;
			++k;
			break;
		default:
			++i;
			break;
		}
	}

	// todo: h�lyes�g kisz�r�se: x*[+] x*[-], x*[>] x*[<]

	for (i = 0; i < k; ++i)
	{
		// [ �s ] feldolgoz�sa. el�g csak [-t�l menni, ha megtal�ljuk a p�rj�t, 
		// a p�rj�nak az �rt�ke is megadhat�
		if ( bf_code[i][OP] == '[' ) // ha [
		{
			for (j = i + 1; j < k; ++j){
				if (bf_code[j][OP] == '[') // ha j�n m�g egy [
				{
					++subloop_count;
				}
				else 
				{
					if (bf_code[j][OP] == ']') // ha j�n a ]
					{
						if ( subloop_count > 0)
						{
							--subloop_count;
						}
						else 
						{
							// [
							bf_code[i][VAL] = j; // [ �rt�ke a ] indexe
							bf_code[j][VAL] = i; // ] �rt�ke a [ indexe
							break;
						}
					}
				}
			}
			if (subloop_count != 0)
			{
				return 0;	
			}
		}
	}

	// itt j�n az interpret�l�s
	// ekkor k �rt�ke pont az �tmeneti k�d hossza
	for (i = 0; i < k; ++i)
	{
		switch (bf_code[i][OP])
		{
		case '+':
			bf_buffer[cursor] += bf_code[i][VAL];
			break;
		case '>':
			cursor += bf_code[i][VAL];
			if (cursor >= MAX_SIZE)
			{
				return 0;
			}
			break;
		case '<':
			cursor -= bf_code[i][VAL];
			if (cursor >= MAX_SIZE)
			{
				return 0;
			}
			break;
		case '[':
			if (bf_buffer[cursor] == 0)
			{
				i = bf_code[i][VAL];
			}
			if (i + 1 >= k)
			{
				return 0;
			}
			break;
		case ']':
			i = bf_code[i][VAL] - 1;
			if (i >= k)
			{
				return 0;
			}
			break;
		case '-':
			bf_buffer[cursor] -= bf_code[i][VAL];
			break;
		case '.':
			fwrite(&bf_buffer[cursor], 1, 1, stdout);
			break;
		case ',':
			if (scanf("%c", &bf_buffer[cursor]) != 1)
			{
				bf_buffer[cursor] = -1;
			}
			break;
		}
	}
	return 0;
}
