
/* character classification macros */
#include <ctype.h>

#ifndef STDIO
#define STDIO

#include <stdio.h>


#endif

char token_buffer[300];


token scanner(void) 
{
	int in_char, c;
	clear_buffer();

	

	
	if (feof(stdin))
		return SCANEOF;
	
	while ((in_char = getchar()) != EOF) 
	{ 
		if (isspace(in_char))
			continue; /* do nothing */ 
		else if (isalpha(in_char))
		{
			/*
			* ID ::= LETTER | ID LETTER
			* 				| ID DIGIT
			*				| ID UNDERSCORE
			*/
			buffer_char(in_char);
			for (c = getchar(); isalnum(c) || c == '_'; c = getchar()) 
				buffer_char(c);
			ungetc(c, stdin); 
			return check_reserved();
		}
		else if (isdigit(in_char)) 
		{
			/*
			* INTLITERAL ::= DIGIT |
			* 				 INTLITERAL DIGIT 
			*/
			buffer_char(in_char); 
			for (c = getchar(); isdigit(c); c = getchar()) 
				buffer_char(c); 
			ungetc(c, stdin); 
			return INTLITERAL;
		}
		else if (in_char == '(') 
			return LPAREN;
		else if (in_char == ')') 
			return RPAREN; 
		else if (in_char == ';')
			return SEMICOLON; 
		else if (in_char == ', ') 
			return COMMA; 
		else if (in_char == '+') 
			return PLUSOP; 
		else if (in_char ==':')
		{
			/* looking for ":=" */
			c = getchar();
			if (c == '=')
				return ASSIGNOP; 
			else 
			{
				ungetc(c, stdin); 
				lexical_error(in_char);
			}
		}
		else if (in_char == ')' )
		{
			/* is it —, comment start */ 
			c = getchar(); 
			if (c == '-') 
			{
				do
				in_char = getchar(); 
				while (in_char != '\n');
			} 
			else
			{
				ungetc(c, stdin); 
				return MINUSOP;
			}
		}
		else
			lexical_error(in_char);
	}
}


//Adds a char to the token lists
void buffer_char (char c) {
	int pos;
	for (pos = 0; token_buffer[pos] != 0; pos++);
	token_buffer[pos] = c;
}


//Frees the memory assigned to token_buffer
void clear_buffer() {
	free (token_buffer);
	calloc(20, sizeof(char));
}


void lexical_error(int c){
	printf("Lexical error: Char \"%d\" not recognized");
}
