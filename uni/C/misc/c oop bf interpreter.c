#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* int l(char*s){return*s?1+l(s+1):0;} */

#ifndef _INC_STDIO
#include <stdio.h>
#endif
#ifndef _INC_STDLIB
#include <stdlib.h>
#endif
#ifndef _INC_STRING
#include <string.h>
#endif

#define BUFF_SIZE 32768
#define OK 1
#define ERR 0
extern struct _bf;
typedef struct _bf Brainfuck;

struct _bf {
	struct {
		char data[BUFF_SIZE];
		int iterator,
			length,
			(*next)(Brainfuck *),
			(*back)(Brainfuck *),
			(*get)(Brainfuck *);
	} input;
	struct {
		char data[BUFF_SIZE];
		int size,
			pointer,
			subloop_counter,
			(*lshift)(Brainfuck *),
			(*rshift)(Brainfuck *),
			(*incr)(Brainfuck *),
			(*decr)(Brainfuck *),
			(*set)(Brainfuck *, char),
			(*get)(Brainfuck *),
			(*loop_start)(Brainfuck *),
			(*loop_end)(Brainfuck *);
	} buffer;
	int (*report)(Brainfuck *, char *),
		(*execute)(Brainfuck *);
	FILE *istream,
		*ostream;
};

int input_next(Brainfuck *self){
	++(self->input.iterator);
	if (self->input.iterator < self->input.length)
		return OK;
	else
		return ERR;
}

int input_back(Brainfuck *self){
	--(self->input.iterator);
	if (self->input.iterator >= 0)
		return OK;
	else
		return ERR;
}

int input_get(Brainfuck *self){
	return self->input.data[self->input.iterator];
}

int buffer_lshift(Brainfuck *self){
	--(self->buffer.pointer);
	if (self->buffer.pointer >= 0)
		return OK;
	else 
		return ERR;
}

int buffer_rshift(Brainfuck *self){
	++(self->buffer.pointer);
	if (self->buffer.pointer < self->buffer.size)
		return OK;
	else 
		return ERR;
}

int buffer_incr(Brainfuck *self){
	++(self->buffer.data[self->buffer.pointer]);
	return OK;
}

int buffer_decr(Brainfuck *self){
	--(self->buffer.data[self->buffer.pointer]);
	return OK;
}

int buffer_set(Brainfuck *self, char c){
	self->buffer.data[self->buffer.pointer] = c;
	return OK;
}

int buffer_get(Brainfuck *self){
	return self->buffer.data[self->buffer.pointer];
}

int buffer_loop_start(Brainfuck *self){
	if (self->buffer.get(self) == 0){
		self->buffer.subloop_counter = 0;
		while (self->input.next(self)){
			if (self->input.get(self) == '['){
				++(self->buffer.subloop_counter);
			}
			if (self->input.get(self) == ']'){
				if (self->buffer.subloop_counter > 0){
					--(self->buffer.subloop_counter);
				}
				else {
					break;
				}
			}
		}
		self->input.back(self);
	}
	return OK;
}

int buffer_loop_end(Brainfuck *self){
	if (self->buffer.get(self) != 0){
		self->buffer.subloop_counter = 0;
		while (self->input.back(self)){
			if (self->input.get(self) == ']'){
				++(self->buffer.subloop_counter);
			}
			if (self->input.get(self) == '['){
				if (self->buffer.subloop_counter > 0){
					--(self->buffer.subloop_counter);
				}
				else {
					break;
				}
			}
		}
		self->input.back(self);
	}
	return OK;
}

int _report(Brainfuck *self, char *additional_info){
	printf(
		"\n==================\n"
		"[buffer]\n"
		"size:     %8d\n"
		"pointer:  %8d\n"
		"value:    %8d\n"
		"[input]\n"
		"length:   %8d\n"
		"iterator: %8d\n"
		"value:    %8c\n"
		"[extra]\n"
		"%s\n"
		"==================\n", 
		self->buffer.size,
		self->buffer.pointer, 
		self->buffer.get(self), 

		self->input.length,
		self->input.iterator, 
		self->input.get(self),

		additional_info
	);
	return OK;
}

int _execute(Brainfuck *self){
	char buffer[2] = " ";
	do {
		switch (self->input.get(self)){
		case '<': 
			if (!self->buffer.lshift(self))
				return ERR;
			break;
		case '>': 
			if (!self->buffer.rshift(self))
				return ERR;
			break;
		case '+': 
			if (!self->buffer.incr(self))
				return ERR;
			break;
		case '-': 
			if (!self->buffer.decr(self))
				return ERR;
			break;
		case '.': 
			fflush(self->ostream);
			buffer[0] = self->buffer.get(self);
			if ((buffer[0] > 31 && buffer[0] < 127) 
				|| (buffer[0] == '\r' || buffer[0] == '\n'))
				fwrite(buffer, 1, 1, self->ostream);
			else
				fprintf(self->ostream, "[%d]", buffer[0]);
			break;
		case ',': 
			fflush(self->istream);
			fread(buffer, 1, 1, self->istream);
			self->buffer.set(self, buffer[0]);
			break;
		case '[': 
			self->buffer.loop_start(self);
			break;
		case ']':
			self->buffer.loop_end(self);
			break;
		default: 
			break;
		}
	} while (self->input.next(self));
	return OK;
}

int _execute_pool(Brainfuck *self){
	if (!_execute(self)){
		self->report(self, "ERROR, EXITED");
	}
	else {
		self->report(self, "ALL OK");
	}
	return OK;
}

static Brainfuck *new_Brainfuck(char *input_code, FILE *input_stream, FILE *output_stream){
	Brainfuck *output_struct = (Brainfuck *)malloc(sizeof(Brainfuck));
	int input_code_length = strlen(input_code),
		i;
	
	for (i = 0; i < BUFF_SIZE; ++i){
		output_struct->buffer.data[i] = 0;
		output_struct->input.data[i] = 0;
	}

	for (i = 0; i < input_code_length; ++i)
		output_struct->input.data[i] = input_code[i];
	
	output_struct->input.length = input_code_length;
	output_struct->input.next = input_next;
	output_struct->input.back = input_back;
	output_struct->input.get = input_get;
	output_struct->input.iterator = 0;

	output_struct->buffer.lshift = buffer_lshift;
	output_struct->buffer.rshift = buffer_rshift;
	output_struct->buffer.incr = buffer_incr;
	output_struct->buffer.decr = buffer_decr;
	output_struct->buffer.set = buffer_set;
	output_struct->buffer.get = buffer_get;
	output_struct->buffer.loop_start = buffer_loop_start;
	output_struct->buffer.loop_end = buffer_loop_end;
	output_struct->buffer.size = BUFF_SIZE;
	output_struct->buffer.pointer = 0;

	output_struct->report = _report;
	output_struct->execute = _execute_pool;

	output_struct->istream = input_stream;
	output_struct->ostream = output_stream;

	return output_struct;
}

#undef BUFF_SIZE
#undef OK
#undef ERR

char *beepitvetartalmazza = 
	"+++++++++[>++++++++<-]>++.           #1: J"
	"<++++++++++++[>>++++++++++<<-]>>---. #2: u"
	"-------------.                       #2: h"
	"-------.                             #2: a"
	"<<++++[>>++++<<-]>>++.               #2: s"
	"+++++++.                             #2: z"
	"<<++++++[>------<-]>------.          #1: ' '"
	"<++++++[>++++++<-]>--.               #1: B"
	"<+++++[>>-----<<-]>>.                #2: a"
	"+++++++++++.                         #2: l"
	"---.                                 #2: i"
	"+++++.                               #2: n"
	"++++++.                              #2: t";

int main(void){
	char programkod[1000];
	Brainfuck *interpreter = (Brainfuck *)NULL;

	printf("Insert brainfuck code here:\n");
	fgets(programkod, 1000, stdin);
	interpreter = new_Brainfuck(programkod, stdin, stdout);
	interpreter->execute(interpreter);

	return 0;
}