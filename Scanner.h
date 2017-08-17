typedef enum token_types {
		BEGIN, END, READ, WRITE, ID, INTLITERAL,
		LPAREN, RPAREN, SEMICOLON, COMMA, ASSIGNOP,
		PLUSOP, MINUSOP, SCANEOF 
	} token;
	
extern token scanner(void);

extern char token_buffer[];

void clear_buffer();

void buffer_char (char c); 