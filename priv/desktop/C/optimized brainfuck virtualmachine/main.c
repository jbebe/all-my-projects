#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {
	RIGHT      = 0x2,   /* 0000000010 0x002 */
	LEFT       = 0x3,   /* 0000000011 0x003 */
	ADD        = 0x4,   /* 0000000100 0x004 */
	SUB        = 0x5,   /* 0000000101 0x005 */
	LOOP_HEAD  = 0x8,   /* 0000001000 0x008 */
	LOOP_TAIL  = 0x10,  /* 0000010000 0x010 */
	ZERO       = 0x20,  /* 0000100000 0x020 */
	PUT        = 0x40,  /* 0001000000 0x040 */
	GET        = 0x80,  /* 0010000000 0x080 */
	END        = 0x100, /* 0100000000 0x100 */
} operator_t;

typedef struct {
	operator_t operator : 16;
	int data : 16;
} command_t;

char *Clean_assist,
	 *Clean_script;
command_t *Commands;

void exit_with(char *error_str);
void remove_do_nothings(char *clean_script, char a, char b);
void replace_resets(char *clean_script);
void prepare_commands(char *clean_script);
void build_commands(char *script_ptr, char *assist_ptr, command_t *cmd_ptr);
void process_clean_script(void);
void process_raw_file(FILE *input);
void run_program(void);

int main(int argc, char *argv[]){
	/* timing */
	clock_t start = clock(), diff;
	
	FILE *script_file;

	/* check whether a script is supplied or not */
	if (argc < 2)
		exit_with("no input");

	script_file = fopen(argv[1], "r");

	if (script_file == NULL)
		exit_with("can't find input");

	/* production chain */
	process_raw_file(script_file);
	process_clean_script();

	run_program();

	free(Clean_script);
	free(Clean_assist);
	free(Commands);

	diff = clock() - start;
	printf("%ds %dms", diff/CLOCKS_PER_SEC, ((diff*1000)/CLOCKS_PER_SEC)%1000);

	return 0;
}

void exit_with(char *error_str){
	puts(error_str);

	free(Clean_script);
	free(Clean_assist);
	free(Commands);

	exit(1);
	return;
}

void remove_do_nothings(char *clean_script, char a, char b){
	while (clean_script[0] != '\0' && clean_script[1] != '\0'){
		if ((clean_script[0] == a && clean_script[1] == b) || (clean_script[0] == b && clean_script[1] == a)){
			int mirror = 1;

			while ((clean_script-mirror) >= Clean_script && *(clean_script+mirror+1) != '\0'
					&& (
							(*(clean_script-mirror) == a && *(clean_script+mirror+1) == b)
							|| (*(clean_script-mirror) == b && *(clean_script+mirror+1) == a)
					)
			){
				mirror++;
			}
			strcpy(clean_script-(mirror-1), clean_script+(mirror-1)+2);
		}
		else {
			clean_script++;
		}
	}
	return;
}

void replace_resets(char *clean_script){
	while (clean_script[2] != '\0'){
		if (clean_script[0] == '[' && (clean_script[1] == '-' || clean_script[1] == '+') && clean_script[2] == ']'){
			clean_script[0] = '0';
			strcpy(clean_script+1, clean_script+3);
		}
		clean_script++;
	}
}

void prepare_commands(char *clean_script){
	int command_length = 0;
	char prev_chr = '\0';
	char *assist_ptr = Clean_assist;

	while (*clean_script != '\0'){
		if (*clean_script != prev_chr || *clean_script == '[' || *clean_script == ']'){
			*assist_ptr++ = *clean_script;
			command_length++;
		}
		prev_chr = *clean_script;
		clean_script++;
	}

	Commands = malloc(sizeof(command_t) * (command_length + 1));

	if (Commands == NULL)
			exit_with("can't allocate memory for Commands array");

	Commands[command_length].operator = END;

	return;
}

void build_commands(char *script_ptr, char *assist_ptr, command_t *cmd_ptr){
	int i;
	operator_t enum_table[']'+1];
	enum_table['>'] = RIGHT;
	enum_table['<'] = LEFT;
	enum_table['+'] = ADD;
	enum_table['-'] = SUB;
	enum_table['.'] = PUT;
	enum_table[','] = GET;
	enum_table['['] = LOOP_HEAD;
	enum_table[']'] = LOOP_TAIL;
	enum_table['0'] = ZERO;

	i = 0;
	while (*script_ptr != '\0'){
		char *tmp_pos = script_ptr+1;
		char *tmp_assist = &assist_ptr[i];
		int is_match,
			j;

		cmd_ptr[i].operator = enum_table[(int)*script_ptr];

		switch (*script_ptr) {
			case '0': break;
			case '[':
				is_match = 1;
				j = 0;
				while (is_match != 0){
					++j;
					if (tmp_assist[j] == '[')
						is_match++;
					else if (tmp_assist[j] == ']')
						is_match--;
				}
				cmd_ptr[i].data = j;
				break;
			case ']':
				is_match = 1;
				j = 0;
				while (is_match != 0){
					++j;
					if (*(tmp_assist-j) == ']')
						is_match++;
					else if (*(tmp_assist-j) == '[')
						is_match--;
				}
				cmd_ptr[i].data = j;
				break;
			default:
				cmd_ptr[i].data = 1;
				while (*tmp_pos == *script_ptr){
					cmd_ptr[i].data += 1;
					tmp_pos++;
				}
				if (*script_ptr == '<' || *script_ptr == '-'){
					cmd_ptr[i].data = -cmd_ptr[i].data;
				}
				break;
		}

		i++;
		script_ptr = tmp_pos;
	}

	return;
}

void process_clean_script(void){

	/* elõször kitakarítjuk a legnyilvánvalóbb szemetet: <> >< +- -+ */
	remove_do_nothings(Clean_script, '>', '<');
	remove_do_nothings(Clean_script, '+', '-');

	/* most pedig a lenullázókat [-] [+] */
	replace_resets(Clean_script);

	/* TODO: 256 x valami-nél valami mod 256 legyen */

	/* [++++<<<<----] felismerje: add shift add*/

	/* most pedig felépítjük a Command tömböt és a segéd sztringet */
	prepare_commands(Clean_script);

	/* és belepakolunk mindent */
	build_commands(Clean_script, Clean_assist, Commands);

	return;
}

void process_raw_file(FILE *input){
	int i = 0,
		ch,
		size;
	char *clean_ptr;

	fseek(input, 0L, SEEK_END);
	size = ftell(input);
	rewind(input);

	Clean_script = malloc(size + 1);
	Clean_assist = malloc(size + 1);

	if (Clean_script == NULL)
		exit_with("can't allocate memory for clean script");
	if (Clean_assist == NULL)
		exit_with("can't allocate memory for assist script");


	clean_ptr = Clean_script;
	for (; i < size; i++){
		ch = fgetc(input);
		switch (ch) {
			case '<':
			case '>':
			case '+':
			case '-':
			case '.':
			case ',':
			case '[':
			case ']':
				*clean_ptr++ = ch;
				break;
			default:
				break;
		}
	}
	*clean_ptr = '\0';

	return;
}

void run_program(void){
	int i, j;
	char buffer[30000];
	char *buffer_ptr = buffer;

	for (i = 0; i < 30000; i++)
		buffer[i] = 0;

	for (i = 0;;){

		/* RIGHT LEFT */
		if ((Commands[i].operator & RIGHT) != 0){
			buffer_ptr += Commands[i].data;
		}

		/* ADD SUB */
		else if ((Commands[i].operator & ADD) != 0){
			*buffer_ptr += Commands[i].data;
		}

		else if ((Commands[i].operator & LOOP_HEAD) != 0){
			if (*buffer_ptr == 0){
				i += Commands[i].data;
			}
		}

		else if ((Commands[i].operator & LOOP_TAIL) != 0){
			if (*buffer_ptr != 0){
				i -= Commands[i].data;
			}
		}

		else if ((Commands[i].operator & ZERO) != 0){
			*buffer_ptr = 0;
		}

		else if ((Commands[i].operator & PUT) != 0){
			for(j = Commands[i].data; j; --j)
				putchar(*buffer_ptr);
		}

		else if ((Commands[i].operator & GET) != 0){
			*buffer_ptr = getchar();
		}

		else {
			return;
		}
		i++;
	}
}