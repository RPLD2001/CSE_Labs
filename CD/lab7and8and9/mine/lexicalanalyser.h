#define MAX_SIZE 20
typedef struct node *Node;
typedef struct symbol *Symbol;
typedef struct token *Token;
Node hashTable[MAX_SIZE]; // hash table
Symbol st[MAX_SIZE];	  // symbol table
char keywords[34][10] = {
	"true",
	"false",
	"auto",
	"double",
	"int",
	"struct",
	"break",
	"else",
	"long",
	"switch",
	"case",
	"enum",
	"register",
	"typedef",
	"char",
	"extern",
	"return",
	"union",
	"const",
	"float",
	"short",
	"unsigned",
	"continue",
	"for",
	"signed",
	"void",
	"default",
	"goto",
	"sizeof",
	"voltile",
	"do",
	"if",
	"static",
	"while"};			  // list of keywords
char data_types[][10] = { // list of data types
	"double",
	"int",
	"char",
	"float"};
char operators[5] = { // list of operators
	'+',
	'-',
	'/',
	'%',
	'*'};
char brackets[6] = { // list of brackets
	'(',
	')',
	'[',
	']',
	'{',
	'}'};
char special_symbols[12] = { // list of special symbols
	'*',
	';',
	':',
	'.',
	',',
	'^',
	'&',
	'!',
	'>',
	'<',
	'~',
	'`'};

enum TYPE // lexeme type enumerator
{
	IDENTIFIER,
	KEYWORD,
	STRING_LITERAL,
	NUMERIC_CONSTANT,
	OPERATOR,
	BRACKET,
	SPECIAL_SYMBOL,
	RELATIONAL_OPERATOR,
	CHARACTER_CONSTANT
};

char types[][30] = { // map for type to string
	"IDENTIFIER",
	"KEYWORD",
	"STRING_LITERAL",
	"NUMERIC_CONSTANT",
	"OPERATOR",
	"BRACKET",
	"SPECIAL_SYMBOL",
	"RELATIONAL_OPERATOR",
	"CHARACTER_CONSTANT"};

struct node
{
	char *cur;
	int row, col;
	struct node *next;
	enum TYPE type;
}; // element for hash table

struct symbol
{
	char *name;
	char *data_type;
	struct symbol *next;
	unsigned int size, row, col;
}; // element for symbol table

struct token
{
	char *lexeme;
	enum TYPE type;
	int row, col;
}; // token returned by getNextToken()
int hash(int size) // hashing function
{
	return (size) % MAX_SIZE;
}

void display_st() // display the symbol table
{
	printf("      Name    |      Type    |      Size     |     Row     |     Col     \n");
	printf("-------------------------------------------------------------------------\n");
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (st[i] == NULL)
			continue;
		else
		{
			Symbol cur = st[i];
			while (cur)
			{
				printf("%10s    |%10s    |%10d    |%10d    |%10d    \n", cur->name, cur->data_type, cur->size, cur->row, cur->col);
				cur = cur->next;
			}
		}
	}
}
int search_symbol(char identifier[]) // to search in symbol_table
{
	int index = hash(strlen(identifier));
	if (st[index] == NULL)
		return -1;
	Symbol cur = st[index];
	int i = 0;
	while (cur != NULL)
	{
		if (strcmp(identifier, cur->name) == 0)
			return i;
		cur = cur->next;
		i++;
	}
	return -1;
}

int search(char buffer[], enum TYPE type) // to search in hash table
{
	int index = hash(strlen(buffer));
	if (hashTable[index] == NULL)
		return 0;
	Node cur = hashTable[index];
	while (cur != NULL)
	{
		if (strcmp(cur->cur, buffer) == 0)
			return 1;
		cur = cur->next;
	}
	return 0;
}

void insert_symbol(char identifier[], char data_type[], int row, int col)
{ // insert in symbol table
	if (search_symbol(identifier) == -1)
	{
		Symbol n = (Symbol)malloc(sizeof(struct symbol));
		char *str = (char *)calloc(strlen(identifier) + 1, sizeof(char));
		strcpy(str, identifier);
		n->name = str;
		n->next = NULL;
		n->row = row;
		n->col = col;
		char *typee = (char *)calloc(strlen(data_type) + 1, sizeof(char));
		strcpy(typee, data_type);
		n->data_type = typee;
		if (strcmp(data_type, "int") == 0)
			n->size = 4;
		else if (strcmp(data_type, "double") == 0)
			n->size = 8;
		else if (strcmp(data_type, "char") == 0)
			n->size = 1;
		else if (strcmp(data_type, "function") == 0)
			n->size = 0;
		else
			n->size = 4;
		int index = hash(strlen(identifier));
		//
		if (st[index] == NULL)
		{
			st[index] = n;
			return;
		}
		Symbol cur = st[index];
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = n;
	}
}
int iskeyword(char buffer[]) // function to check for keyword
{
	for (int i = 0; i < 34; i++)
	{
		if (strcmp(buffer, keywords[i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int isdatatype(char buffer[])
{ // function to check for data_Type
	for (int i = 0; i < 4; i++)
	{
		if (strcmp(buffer, data_types[i]) == 0)
			return 1;
	}
	return 0;
}

int isoperator(char c)
{ // function to check for operator
	for (int i = 0; i < 5; i++)
	{
		if (operators[i] == c)
			return 1;
	}
	return 0;
}

int isspecial(char c)
{ // function to check for special symbol
	for (int i = 0; i < 12; i++)
	{
		if (special_symbols[i] == c)
			return 1;
	}
	return 0;
}

int isbracket(char c)
{ // function to check for bracket
	for (int i = 0; i < 6; i++)
	{
		if (brackets[i] == c)
			return 1;
	}
	return 0;
}

Token insert(char buffer[], int row, int col, enum TYPE type)
{ // insert in hash table
	Token tkn = (Token)malloc(sizeof(struct token));
	char *lexeme = (char *)calloc(strlen(buffer) + 1, sizeof(char));
	strcpy(lexeme, buffer);
	tkn->lexeme = lexeme;
	tkn->type = type;
	tkn->col = col;
	tkn->row = row;
	if (type == IDENTIFIER || search(buffer, type) == 0)
	{
		// printf("< %s | %d | %d | %s >\n", buffer, row, col, types[type]);
		int index = hash(strlen(buffer));
		Node n = (Node)malloc(sizeof(struct node));
		char *str = (char *)calloc(strlen(buffer) + 1, sizeof(char));
		strcpy(str, buffer);
		n->cur = str;
		n->next = NULL;
		n->row = row;
		n->col = col;
		n->type = type;
		if (hashTable[index] == NULL)
		{
			hashTable[index] = n;
			return tkn;
		}
		Node cur = hashTable[index];
		while (cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = n;
	}
	return tkn;
}

Token getNextToken(FILE *finp, int *row_pointer, int *col_pointer, char data_type_buffer[], char *c)
{
	char buffer[100];
	int i = 0, col;
	Token tkn = NULL;
	if (isalpha(*c) != 0 || *c == '_')
	{
		buffer[i++] = *c;
		col = (*col_pointer);
		while (isalpha(*c) != 0 || *c == '_' || isdigit(*c) != 0)
		{
			*c = fgetc(finp);
			(*col_pointer)++;
			if (isalpha(*c) != 0 || *c == '_' || isdigit(*c) != 0)
				buffer[i++] = *c;
		}
		buffer[i] = '\0';
		if (isdatatype(buffer) == 1)
		{
			strcpy(data_type_buffer, buffer);
			tkn = insert(buffer, (*row_pointer), col - 1, KEYWORD); // data type
		}
		else if (iskeyword(buffer) == 1)
		{
			tkn = insert(buffer, (*row_pointer), col - 1, KEYWORD); // keyword
		}
		else
		{
			tkn = insert(buffer, (*row_pointer), col - 1, IDENTIFIER); // identifier
			if (*c == '(')
				insert_symbol(buffer, "function", *row_pointer, col - 1);
			else
				insert_symbol(buffer, data_type_buffer, *row_pointer, col - 1);
			// data_type_buffer[0] = '\0';
		}
		i = 0;
		if (*c == '\n')
			(*row_pointer)++, (*col_pointer) = 1;
		buffer[0] = '\0';
	}
	else if (isdigit(*c) != 0)
	{
		buffer[i++] = *c;
		col = (*col_pointer);
		while (isdigit(*c) != 0 || *c == '.')
		{
			*c = fgetc(finp);
			(*col_pointer)++;
			if (isdigit(*c) != 0 || *c == '.')
				buffer[i++] = *c;
		}
		buffer[i] = '\0';
		tkn = insert(buffer, (*row_pointer), col - 1, NUMERIC_CONSTANT); // numerical constant
		i = 0;
		if (*c == '\n')
			(*row_pointer)++, (*col_pointer) = 1;
		buffer[0] = '\0';
	}
	else if (*c == '\"')
	{
		col = (*col_pointer);
		buffer[i++] = *c;
		*c = 0;
		while (*c != '\"')
		{
			*c = fgetc(finp);
			(*col_pointer)++;
			buffer[i++] = *c;
		}
		buffer[i] = '\0';
		tkn = insert(buffer, (*row_pointer), col - 1, STRING_LITERAL); // string literals
		buffer[0] = '\0';
		i = 0;
		*c = fgetc(finp);
		(*col_pointer)++;
	}
	else if (*c == '\'')
	{
		col = (*col_pointer);
		buffer[i++] = *c;
		*c = 0;
		*c = fgetc(finp);
		(*col_pointer)++;
		buffer[i++] = *c;
		if (*c == '\\')
		{
			*c = fgetc(finp);
			(*col_pointer)++;
			buffer[i++] = *c;
		}
		*c = fgetc(finp);
		(*col_pointer)++;
		buffer[i++] = *c;
		buffer[i] = '\0';
		tkn = insert(buffer, (*row_pointer), col - 1, CHARACTER_CONSTANT); // character constants
		buffer[0] = '\0';
		i = 0;
		*c = fgetc(finp);
		(*col_pointer)++;
	}
	else
	{
		col = (*col_pointer);
		if (*c == '=')
		{ // relational and logical operators
			*c = fgetc(finp);
			(*col_pointer)++;
			if (*c == '=')
			{
				tkn = insert("==", (*row_pointer), col - 1, RELATIONAL_OPERATOR);
			}
			else
			{
				tkn = insert("=", (*row_pointer), col - 1, RELATIONAL_OPERATOR);
				fseek(finp, -1, SEEK_CUR);
				(*col_pointer)--;
			}
		}
		else if (*c == '>' || *c == '<' || *c == '!')
		{
			char temp = *c;
			*c = fgetc(finp);
			(*col_pointer)++;
			if (*c == '=')
			{
				char temp_str[3] = {
					temp,
					'=',
					'\0'};
				tkn = insert(temp_str, (*row_pointer), col - 1, RELATIONAL_OPERATOR);
			}
			else
			{
				char temp_str[2] = {
					temp,
					'\0'};
				tkn = insert(temp_str, (*row_pointer), col - 1, RELATIONAL_OPERATOR);
				fseek(finp, -1, SEEK_CUR);
				(*col_pointer)--;
			}
		}
		else if (isbracket(*c) == 1)
		{ // parentheses and special symbols
			char temp_string[2] = {
				*c,
				'\0'};
			tkn = insert(temp_string, (*row_pointer), col - 1, BRACKET);
		}
		else if (isspecial(*c) == 1)
		{ // parentheses and special symbols
			char temp_string[2] = {
				*c,
				'\0'};
			tkn = insert(temp_string, (*row_pointer), col - 1, SPECIAL_SYMBOL);
		}
		else if (isoperator(*c) == 1)
		{ // operators
			char temp = *c;
			*c = fgetc(finp);
			(*col_pointer)++;
			if (*c == '=' || (temp == '+' && *c == '+') || (temp == '-' && *c == '-'))
			{
				char temp_string[3] = {
					temp,
					*c,
					'\0'};
				tkn = insert(temp_string, (*row_pointer), col - 1, OPERATOR);
			}
			else
			{
				char temp_String[2] = {
					temp,
					'\0'};
				tkn = insert(temp_String, (*row_pointer), col - 1, OPERATOR);
				fseek(finp, -1, SEEK_CUR);
				(*col_pointer)--;
			}
		}
		else if (*c == '\n') // new line
			(*row_pointer)++, (*col_pointer) = 1;
		else if (*c == '$')
		{
			Token eof = (Token)malloc(sizeof(struct token));
			eof->lexeme = "EOF";
			return eof;
		}
		*c = fgetc(finp);
		(*col_pointer)++;
	}
	return tkn;
}

int removeExcess(char *fileName)
{ // to remove spaces, tabs and comments
	FILE *fa, *fb;
	int ca, cb;
	fa = fopen(fileName, "r");
	if (fa == NULL)
	{
		printf("Cannot open file \n");
		exit(0);
	}
	fb = fopen("space_output.c", "w");
	ca = getc(fa);
	while (ca != EOF)
	{
		if (ca == ' ' || ca == '\t')
		{
			putc(' ', fb);
			while (ca == ' ' || ca == '\t')
				ca = getc(fa);
		}
		if (ca == '/')
		{
			cb = getc(fa);
			if (cb == '/')
			{
				while (ca != '\n')
					ca = getc(fa);
			}
			else if (cb == '*')
			{
				do
				{
					while (ca != '*')
						ca = getc(fa);
					ca = getc(fa);
				} while (ca != '/');
			}
			else
			{
				putc(ca, fb);
				putc(cb, fb);
			}
		}
		else
			putc(ca, fb);
		ca = getc(fa);
	}
	putc('$', fb);
	fclose(fa);
	fclose(fb);
	return 0;
}
int removePreprocess()
{ // to ignore preprocessor directives
	FILE *finp = fopen("space_output.c", "r");
	char c = 0;
	char buffer[100];
	buffer[0] = '\0';
	int i = 0;
	char *includeStr = "include", *defineStr = "define", *mainStr = "main";
	int mainFlag = 0, row = 1;
	while (c != EOF)
	{
		c = fgetc(finp);
		if (c == '#' && mainFlag == 0)
		{
			c = 'a';
			while (isalpha(c) != 0)
			{
				c = fgetc(finp);
				buffer[i++] = c;
			}
			buffer[i] = '\0';
			if (strstr(buffer, includeStr) != NULL || strstr(buffer, defineStr) != NULL)
			{
				row++;
				while (c != '\n')
				{
					c = fgetc(finp);
				}
			}
			else
			{
				for (int j = 0; j < i; j++)
					;
				while (c != '\n')
				{
					c = fgetc(finp);
				}
			}
			i = 0;
			buffer[0] = '\0';
		}
		else
		{
			if (mainFlag == 0)
			{
				buffer[i++] = c;
				buffer[i] = '\0';
				if (strstr(buffer, mainStr) != NULL)
				{
					mainFlag = 1;
				}
			}
			if (c == ' ' || c == '\n')
			{
				buffer[0] = '\0';
				i = 0;
			}
		}
	}
	fclose(finp);
	return row;
}
