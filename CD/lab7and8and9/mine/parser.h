void get();
void Program();
void Declarations();
void Statement_List();
void Statement();
void Expn();
void EPrime();
void Simple_Exp();
void SePrime();
void Term();
void TPrime();
void Factor();
void Relop();
void Addop();
void Mulop();
void DataType();
void Identifier();
void IdentifierPrime();
void IdentifierPrimePrime();
void AssignStat();
void Decision();
void DPrime();
void Looping();
enum NON_TERMINALS
{ // types for non terminals.
	PROGRAM,
	DECLARATIONS,
	DATA_TYPE,
	IDENTIFIERLIST,
	IDENTIFIERLISTPRIME,
	IDENTIFIERLISTPRIMEPRIME,
	STATEMENT_LIST,
	STATEMENT,
	ASSIGN_STAT,
	EXPN,
	EPRIME,
	SIMPLE_EXP,
	SEPRIME,
	TERM,
	TPRIME,
	FACTOR,
	DECISION,
	DPRIME,
	LOOPING,
	RELOP,
	ADDOP,
	MULOP
};

// ToDo: calculate the first and follow of the grammar

char first[][6][20] = {
	{"int"},
	{"int", "char", "double", "float"},
	{"int", "char", "double", "float"},
	{"id"},
	{",", "["},
	{","},
	{"id", "if", "while", "for"},
	{"id", "if", "while", "for"},
	{"id"},
	{"id", "num"},
	{"==", "!=", ">=", "<=", ">", "<"},
	{"id", "num"},
	{"+", "-"},
	{"id", "num"},
	{"*", "/", "%"},
	{"id", "num"},
	{"if"},
	{"else"},
	{"while", "for"},
	{"==", "!=", ">=", "<=", ">", "<"},
	{"+", "-"},
	{"*", "/", "%"},
};
char follow[][15][20] = {
	{"$"},
	{"return", "}", "id", "if", "while", "for"},
	{"id"},
	{";"},
	{";"},
	{";"},
	{"}"},
	{"id", "if", "while", "for", "}"},
	{";", ")"},
	{";", ")", "==", "!=", ">=", "<=", ">", "<"},
	{";", ")", "==", "!=", ">=", "<=", ">", "<"},
	{";", ")", "==", "!=", ">=", "<=", ">", "<", "id", "num"},
	{";", ")", "==", "!=", ">=", "<=", ">", "<", "id", "num"},
	{"+", "-", ";", ")", "==", "!=", ">=", "<=", ">", "<", "id", "num"},
	{"+", "-", ";", ")", "==", "!=", ">=", "<=", ">", "<", "id", "num"},
	{"*", "/", "%", "+", "-", ";", ")", "==", "!=", ">=", "<=", ">", "<", "id", "num"},
	{"id", "if", "while", "for", "}"},
	{"id", "if", "while", "for", "}"},
	{"id", "if", "while", "for", "}"},
	{"id", "num"},
	{"id", "num"},
	{"id", "num"}};

int firstSz[] = {1, 4, 4, 1, 2, 1, 4, 4, 1, 2, 6, 2, 2, 2, 3, 2, 1, 1, 2, 6, 2, 3};
int followSz[] = {1, 6, 1, 1, 1, 1, 1, 5, 2, 8, 8, 10, 10, 12, 12, 15, 5, 5, 5, 2, 2, 2};
int row, col_global;
char data_type_buffer[100], c = 0;
FILE *finp;
Token tkn = NULL;
int prev_flag = false;

int search_first(enum NON_TERMINALS val, char *buffer, enum TYPE type)
{
	if (type == IDENTIFIER)
	{
		return search_symbol(buffer) != -1 && search_first(val, "id", KEYWORD);
	}
	if (type == NUMERIC_CONSTANT)
	{
		return search_first(val, "num", KEYWORD);
	}
	for (int i = 0; i < firstSz[val]; i++)
	{
		if (strcmp(buffer, first[val][i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int search_follow(enum NON_TERMINALS val, char *buffer, enum TYPE type)
{
	if (type == IDENTIFIER)
	{
		return search_follow(val, "id", KEYWORD) && search_symbol(buffer) != -1;
	}
	if (type == NUMERIC_CONSTANT)
	{
		return search_follow(val, "num", KEYWORD);
	}
	for (int i = 0; i < followSz[val]; i++)
	{
		if (strcmp(buffer, follow[val][i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}

void failure(char *msg)
{
	printf("\n ### Failed to accept file!! ###\nError : %s at\n Row : %d, Col : %d\n", msg, tkn->row, tkn->col);
	exit(0);
}

void success()
{
	printf("\n**** File is accepted successfully!! ****\n");
}
void AssignStat()
{
	get();
	if (search_symbol(tkn->lexeme) != -1)
	{
		get();
		if (strcmp(tkn->lexeme, "=") == 0)
		{
			get();
			prev_flag = true;
			if (search_first(EXPN, tkn->lexeme, tkn->type) == 1)
				Expn();
			else
				failure("Invalid Identifier or number : Assign.");
		}
		else
		{
			failure("= sign not found! : Assign.");
		}
	}
	else
	{
		failure("Invalid Identifier! : Assign.");
	}
}

void DataType()
{
	get();
	if (isdatatype(tkn->lexeme) == 0)
	{
		failure("Data Type Expected! : Data_Type.");
	}
}

void Decision()
{
	get();
	if (strcmp(tkn->lexeme, "if") == 0)
	{
		get();
		if (strcmp(tkn->lexeme, "(") == 0)
		{
			get();
			prev_flag = true;
			if (search_first(EXPN, tkn->lexeme, tkn->type) == 1)
			{
				Expn();
				get();
				if (strcmp(tkn->lexeme, ")") == 0)
				{
					get();
					if (strcmp(tkn->lexeme, "{") == 0)
					{
						get();
						prev_flag = true;
						if (search_first(STATEMENT_LIST, tkn->lexeme, tkn->type) == 1)
						{
							Statement_List();
							get();
							if (strcmp(tkn->lexeme, "}") == 0)
							{
								get();
								prev_flag = true;
								if (search_first(DPRIME, tkn->lexeme, tkn->type) == 1)
								{
									DPrime();
								}
							}
							else
								failure("} expected! : Decision.");
						}
					}
					else
						failure("{ expected! : Decision.");
				}
				else
					failure(") expected! Decision.");
			}
			else
			{
				failure("Invalid Expression. : Decision.");
			}
		}
		else
			failure("( expected! : Decision.");
	}
	else
		failure("No decision statement found! : Decision.");
}

void DPrime()
{
	get();
	if (strcmp(tkn->lexeme, "else") == 0)
	{
		get();
		if (strcmp(tkn->lexeme, "{") == 0)
		{
			get();
			prev_flag = true;
			if (search_first(STATEMENT_LIST, tkn->lexeme, tkn->type) == 1)
			{
				Statement_List();
				get();
				if (strcmp(tkn->lexeme, "}") != 0)
				{
					failure("} expected! : DPrime.");
				}
			}
			else
			{
				failure("Invalid Statement! : DPrime.");
			}
		}
		else
			failure("{ expected! : DPrime.");
	}
	else
	{
		prev_flag = true;
	}
}

void Declarations()
{
	get();
	prev_flag = true;
	if (search_first(DATA_TYPE, tkn->lexeme, tkn->type) == 1)
	{
		DataType();
		get();
		if (search_first(IDENTIFIERLIST, tkn->lexeme, tkn->type) == 1)
		{
			prev_flag = true;
			Identifier();
			get();
			if (strcmp(tkn->lexeme, ";") == 0)
			{
				get();
				prev_flag = true;
				if (search_first(DECLARATIONS, tkn->lexeme, tkn->type) == 1)
				{
					Declarations();
				}
				else if (search_follow(DECLARATIONS, tkn->lexeme, tkn->type) == 0)
				{
					failure("Invalid Identifier : Declaration.");
				}
			}
			else
			{
				failure("Semi Colon Expected! : Declaration.");
			}
		}
		else
		{
			failure("Identifier expected! : Declaration.");
		}
	}
}

void Expn()
{
	if (search_first(SIMPLE_EXP, tkn->lexeme, tkn->type) == 1)
	{
		Simple_Exp();
		if (search_first(EPRIME, tkn->lexeme, tkn->type) == 1)
			EPrime();
	}
	else
	{
		failure("Invalid Identifier or Number! : Expn.");
	}
}

void EPrime()
{
	if (search_first(RELOP, tkn->lexeme, tkn->type) == 1)
	{
		Relop();
		get();
		prev_flag = true;
		if (search_first(SIMPLE_EXP, tkn->lexeme, tkn->type) == 1)
			Simple_Exp();
		else
			failure("Invalid Identifier or Number! : EPrime.");
	}
	else if (search_follow(EPRIME, tkn->lexeme, tkn->type) != 1)
	{
		failure("Invalid Operator or ; expected! : EPrime.");
	}
}

void Simple_Exp()
{
	if (search_first(TERM, tkn->lexeme, tkn->type) == 1)
	{
		Term();
		if (search_first(SEPRIME, tkn->lexeme, tkn->type) == 1)
			SePrime();
	}
	else
	{
		failure("Invalid Identifier or number! : Simple Exp.");
	}
}

void SePrime()
{
	if (search_first(ADDOP, tkn->lexeme, tkn->type) == 1)
	{

		Addop();
		get();
		prev_flag = true;
		if (search_first(TERM, tkn->lexeme, tkn->type) == 1)
		{
			Term();
			if (search_first(SEPRIME, tkn->lexeme, tkn->type) == 1)
				SePrime();
		}
		else
			failure("Invalid Identifier or number! : SePrime.");
	}
	else if (search_follow(SEPRIME, tkn->lexeme, tkn->type) != 1)
	{
		failure("Invalid Operator! : SePrime.");
	}
}

void Term()
{
	if (search_first(FACTOR, tkn->lexeme, tkn->type) == 1)
	{
		Factor();
		get();
		prev_flag = true;
		if (search_first(TPRIME, tkn->lexeme, tkn->type) == 1)
		{
			TPrime();
		}
	}
	else
	{
		failure("Invalid Identifier or number! : Term.");
	}
}

void TPrime()
{
	if (search_first(MULOP, tkn->lexeme, tkn->type) == 1)
	{
		Mulop();
		get();
		prev_flag = true;
		if (search_first(FACTOR, tkn->lexeme, tkn->type) == 1)
		{
			Factor();
			get();
			prev_flag = true;
			if (search_first(TPRIME, tkn->lexeme, tkn->type) == 1)
			{
				TPrime();
			}
		}
		else
		{
			failure("Invalid Identifier! : TPrime.");
		}
	}
	else if (search_follow(TPRIME, tkn->lexeme, tkn->type) != 1)
	{
		failure("Invalid Operator! : TPrime.");
	}
}

void Factor()
{
	get();
	if (search_symbol(tkn->lexeme) == -1 && tkn->type != NUMERIC_CONSTANT)
	{
		failure("Invalid Identifier or Number : Factor.");
	}
}
void Identifier()
{
	get();
	if (search_symbol(tkn->lexeme) != -1)
	{
		get();
		prev_flag = true;
		if (search_first(IDENTIFIERLISTPRIME, tkn->lexeme, tkn->type) == 1)
		{
			IdentifierPrime();
		}
		else if (search_follow(IDENTIFIERLIST, tkn->lexeme, tkn->type) != 1)
		{
			failure("; expected! : Identifier.");
		}
	}
	else
	{
		failure("Invalid Identifier! : Identifier.");
	}
}

void IdentifierPrime()
{
	get();
	if (strcmp(tkn->lexeme, ",") == 0)
	{
		get();
		if (search_first(IDENTIFIERLIST, tkn->lexeme, tkn->type) == 1)
		{
			prev_flag = true;
			Identifier();
		}
		else if (strcmp(tkn->lexeme, "[") == 0)
		{
		}
		else
		{
			failure("Invalid Identifier! : Identifier.");
		}
	}
	else if (strcmp(tkn->lexeme, "[") == 0)
	{
		get();
		if (tkn->type == NUMERIC_CONSTANT)
		{
			get();
			if (strcmp(tkn->lexeme, "]") == 0)
			{
				if (search_first(IDENTIFIERLISTPRIMEPRIME, tkn->lexeme, tkn->type) == 1)
					IdentifierPrimePrime();
			}
			else
			{
				failure("] expected!  : Identifier`.");
			}
		}
		else
		{
			failure("Number expected!  : Identifier`.");
		}
	}
	else
	{
		if (search_follow(IDENTIFIERLISTPRIME, tkn->lexeme, tkn->type) == 1)
			prev_flag = true;
		else
		{
			failure("; expected!  : Identifier`.");
		}
	}
}

void IdentifierPrimePrime()
{
	get();
	if (strcmp(tkn->lexeme, ",") == 0)
	{
		if (search_first(IDENTIFIERLIST, tkn->lexeme, tkn->type) == 1)
			Identifier();
		else
		{
			failure("Invalid Identifier!  : Identifier``.");
		}
	}
	else
	{
		if (search_follow(IDENTIFIERLISTPRIMEPRIME, tkn->lexeme, tkn->type) == 1)
			prev_flag = true;
		else
		{
			failure("; expected!  : Identifier``.");
		}
	}
}
void Looping()
{
	get();
	if (strcmp(tkn->lexeme, "while") == 0)
	{
		get();
		if (strcmp(tkn->lexeme, "(") == 0)
		{
			get();
			prev_flag = true;
			if (search_first(EXPN, tkn->lexeme, tkn->type) == 1)
			{
				Expn();
				get();
				if (strcmp(tkn->lexeme, ")") != 0)
				{
					failure(") expected! : W Looping.");
				}
				get();
				if (strcmp(tkn->lexeme, "{") == 0)
				{
					get();
					prev_flag = true;
					// if (search_first(STATEMENT_LIST, tkn->lexeme, tkn->type) == 1)
					{
						Statement_List();
						get();
						if (strcmp(tkn->lexeme, "}") != 0)
						{
							failure("} expected! : W Looping.");
						}
					}
					// else printf("%s\n", tkn->lexeme), failure("Invalid statement! : Looping.");
				}
				else
					failure("{ expected! : W Looping");
			}
			else
				failure("Invalid Expression. : W Looping.");
		}
		else
			failure("( expected! : W Looping");
	}
	else if (strcmp(tkn->lexeme, "for") == 0)
	{
		get();
		if (strcmp(tkn->lexeme, "(") == 0)
		{
			get();
			prev_flag = true;
			if (search_first(ASSIGN_STAT, tkn->lexeme, tkn->type) == 1)
			{
				AssignStat();
				get();
				if (strcmp(tkn->lexeme, ";") == 0)
				{
					get();
					prev_flag = true;
					if (search_first(EXPN, tkn->lexeme, tkn->type) == 1)
					{
						Expn();
						get();
						if (strcmp(tkn->lexeme, ";") == 0)
						{
							get();
							prev_flag = true;
							if (search_first(ASSIGN_STAT, tkn->lexeme, tkn->type) == 1)
							{
								AssignStat();
								get();
								if (strcmp(tkn->lexeme, ")") == 0)
								{
									get();
									if (strcmp(tkn->lexeme, "{") == 0)
									{
										get();
										prev_flag = true;
										if (search_first(STATEMENT_LIST, tkn->lexeme, tkn->type) == 1)
										{
											Statement_List();
											get();
											if (strcmp(tkn->lexeme, "}") != 0)
											{
												failure("} expected! : F Looping");
											}
										}
										else
											failure("Invalid Identifier! : F Looping");
									}
									else
									{
										failure("{ expected! : F Looping");
									}
								}
								else
									failure(") expected : F Looping");
							}
							else
								failure("Invalid Identifier! : F Looping");
						}
						else
							failure("; expected! : F Looping");
					}
					else
						failure("Invalid Expression! : F Looping");
				}
				else
					failure("; expected! : F Looping");
			}
			else
				failure("Invalid Identifier! : F Looping");
		}
		else
			failure("( expected! : F Looping");
	}
	else
		failure("Invalid Loop! : F Looping");
}
void Relop()
{
	get();
	if (strcmp(tkn->lexeme, "==") == 0 || strcmp(tkn->lexeme, "!=") == 0 || strcmp(tkn->lexeme, ">=") == 0 || strcmp(tkn->lexeme, "<=") == 0 || strcmp(tkn->lexeme, ">") == 0 || strcmp(tkn->lexeme, "<") == 0)
	{
		return;
	}
	else
	{
		failure("Invalid Operator! : Operators.");
	}
}

void Addop()
{
	get();
	if (strcmp(tkn->lexeme, "+") == 0 || strcmp(tkn->lexeme, "-") == 0)
	{
		return;
	}
	else
	{
		failure("Invalid Operator! : Operators.");
	}
}

void Mulop()
{
	get();
	if (strcmp(tkn->lexeme, "*") == 0 || strcmp(tkn->lexeme, "/") == 0 || strcmp(tkn->lexeme, "%%") == 0)
	{
		return;
	}
	else
	{
		failure("Invalid Operator! : Operators.");
	}
}
void Program()
{
	get();
	if (strcmp(tkn->lexeme, "int") == 0)
	{
		get();
		if (strcmp(tkn->lexeme, "main") == 0)
		{
			get();
			if (strcmp(tkn->lexeme, "(") == 0)
			{
				get();
				if (strcmp(tkn->lexeme, ")") == 0)
				{
					get();
					if (strcmp(tkn->lexeme, "{") == 0)
					{
						get();
						if (search_first(DECLARATIONS, tkn->lexeme, tkn->type) == 1)
						{
							prev_flag = true;
							Declarations();
							get();
							if (search_first(STATEMENT_LIST, tkn->lexeme, tkn->type) == 1)
							{
								prev_flag = true;
								Statement_List();
								get();
								if (strcmp(tkn->lexeme, "return") == 0)
								{
									get();
									if (tkn->type == NUMERIC_CONSTANT)
									{
										get();
										if (strcmp(tkn->lexeme, ";") == 0)
										{
											get();
											if (strcmp(tkn->lexeme, "}") == 0)
											{
												success();
											}
											else
											{
												failure("No closing curly braces found! : Program.");
											}
										}
										else
										{
											failure("No Semi-Colon found! : Program.");
										}
									}
									else
									{
										failure("Numeric Value Expected! : Program.");
									}
								}
								else
								{
									failure("No return statement found! : Program.");
								}
							}
							else
							{
								failure("Invalid Identifier! : Program.");
							}
						}
						else
						{
							failure("Data Type expected! : Program.");
						}
					}
					else
					{
						failure("No starting curly bracket found! : Program.");
					}
				}
				else
				{
					failure("No function closing parentheses found! : Program.");
				}
			}
			else
			{
				failure("No function starting parentheses found! : Program.");
			}
		}
		else
		{
			failure("No main found! : Program.");
		}
	}
	else
	{
		failure("No return type found! : Program.");
	}
}

void Statement_List()
{
	get();
	prev_flag = true;
	if (search_first(STATEMENT, tkn->lexeme, tkn->type) == 1)
	{
		Statement();
		get();
		prev_flag = true;
		if (search_first(STATEMENT_LIST, tkn->lexeme, tkn->type) == 1)
		{
			Statement_List();
		}
	}
	else if (search_follow(STATEMENT_LIST, tkn->lexeme, tkn->type) != 1)
	{
		failure("Invalid Statement! : Statement List.");
	}
}

void Statement()
{
	get();
	prev_flag = true;
	if (search_first(ASSIGN_STAT, tkn->lexeme, tkn->type) == 1)
	{
		AssignStat();
		get();
		if (strcmp(tkn->lexeme, ";") != 0)
		{
			failure("; expected! : Statement.");
		}
	}
	else if (search_first(DECISION, tkn->lexeme, tkn->type) == 1)
	{
		Decision();
	}
	else if (search_first(LOOPING, tkn->lexeme, tkn->type) == 1)
	{
		Looping();
	}
	else if (search_follow(STATEMENT, tkn->lexeme, tkn->type) != 1)
	{
		failure("Invalid Statement! : Statement.");
	}
}

