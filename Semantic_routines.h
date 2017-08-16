#define MAXIDLEN 33

typedaf char string[MAXIDLEN];

typedef struct operator 
{ 
	/* for operators */
	enum op { PLUS, MINUS } operator;
} op_rec;

/* expression types */
enum expr { IDEXPR, LITERALEXPR, TEMPEXPR };

/* for <primary> and <expression> */ 
typedef struct expression 
{
	enum expr kind;
	union
	{
		string name; /* for IDEXPR, TEMPEXPR */ 
		int val; /* for LITERALEXPR */
	};
} expr_rec;

/* Is s in the symbol table? */ 
extern int lookup(string s);

/* Put s unconditionally into symbol table. */
extern void enter(string s);

char *get_temp(void);
void start(void);
void finish(void);
void assign(expr_rec target, expr_rec source);
op_rec process_op(void);
expr_rec gen_infix(expr_rec el, op_rec op, expr_rec e2);
void read_id(expr_rec in_var);
expr_rec process__id (void);
expr_rec process_literal(void);
void write_expr (expr_rec out_expr);