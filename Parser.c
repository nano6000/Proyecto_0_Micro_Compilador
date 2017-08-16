#include <Semantic_routines.h>
#include <Scanner.h>

void system_goal (void)
{
	/* <system goal> ::= <program> SCANEOF */ 
	program();
	match(SCANEOF);
}

void program (void)
{
	/* <program> ::= BEGIN <statement list> END */ 
	match(BEGIN); 
	statement_list(); 
	match(END);
}

void statement_list(void)
{
	/*
	* <statement list> ::= <statement> { <statement> }
	*/
	statement(); 
	while (TRUE) 
	{
		switch (next_token()) 
		{ 
			case ID: 
			case READ: 
			case WRITE:
				statement(); 
				break; 
			default:
				return;
		}
	}
}

void statement(void)
{
	token tok = next_token();
	switch (tok) 
	{
		case ID:
			/* <statement> ::= ID := <expression> ; */ 
			match(ID); 
			match(ASSIGNOP);
			expression();
			match(SEMICOLON); 
			break;
		case READ:
			/* <statement> :READ ( <id list> ) ; */
			match(READ); 
			match(LPAREN);
			id_list(); 
			match(RPAREN);
			match(SEMICOLON);
			break;
		case WRITE:
			/* <statement> ::= WRITE ( <expr list> ) ; */
			match(WRITE); 
			match(LPAREN);
			expr_list(); 
			match(RPAREN);
			match(SEMICOLON);
			break;
		default:
			syntax_error(tok); 
			break;
	}
}

void id_list (void)
{
	/* <id list> ::= ID { , ID } */ 
	match(ID);
	while (next_token() == COMMA) 
	{
		match(COMMA);
		match(ID);
	}
}

void expression(expr_rec *result)
{
	/*
	* <expression> ::= <primary>
	* 					{ <add op> <primary> }
	
		primary();
		for (t = next_token(); t == PLUSOP || t == MINUSOP; t = next_token()) 
		{
			add_op();
			primary () ;
		}
	*/
	expr_rec left_operand, right_operand;
	op_rec op;
	primary(& left_operand); 
	while (next_token() == PLUSOP || next_token() == MINUSOP) 
	{ 
		add_op(& op); 
		primary(& right_operand); 
		left_operand = gen_infix(left_operand, op, right_operand);
	}
	*result = left_operand;
}

void expr_list(void)
{
	/* <expr list> ::= <expression> { , <expression> } */ 
	expression();
	while (next_token() == COMMA) 
	{ 
		match(COMMA); 
		expression();
	}
}

void add_op(void)
{
	token tok = next_token();
	/* <addop> ::= PLUSOP | MINUSOP */
	if (tok == PLUSOP || tok == MINUSOP) 
		match(tok);
	else
		syntax_error(tok);
}

void primary(void)
{
	token tok = next_token();
	switch (tok) 
	{ 
		case LPAREN:
			/* <primary> ::= ( <expression> ) */ 
			match(LPAREN); 
			expression(); 
			match(RPAREN); 
			break;
		case ID:
			/* <primary> ::= ID */
			match(ID);
			break;
		case INTLITERAL:
			/* <primary> ::= INTLITERAL */
			match(INTLITERAL);
			break;
		default:
			syntax_error(tok); break;
	}
}