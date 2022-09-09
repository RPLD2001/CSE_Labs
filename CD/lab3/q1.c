#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int num = 0; // No. of preprocessor directives
char keywords[32][10] = {"auto", "double", "int", "struct", "break", "else", "long", "switch", "case", "enum", "register",
						 "typedef", "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void",
						 "default", "goto", "sizeof", "volatile", "do", "if", "static", "while"};
char symbols[] = {'=', '<', '>', '!', '+', '-', '*', '/', '%', '(', ')', '{', '}', '[', ']', ',', ';'};
typedef struct
{
	unsigned int row, col;
	char token_name[100];
} token;
void RemovesWsComments(FILE *fptr1, FILE *fptr2)
{
	char ch = fgetc(fptr1), ch2;
	for (int i = 0; i < num; i++)
		ch = fgetc(fptr1); // To remove blank lines left after removing preprocessor directives
	while (ch != EOF)
	{
		if (ch == ' ')
		{
			fputc(ch, fptr2);
			while (ch == ' ')
				ch = fgetc(fptr1);
			continue;
		}
		else if (ch == '	')
		{
			fputc(' ', fptr2);
			ch = fgetc(fptr1);
			continue;
		}
		else if (ch == '/')
		{
			ch2 = fgetc(fptr1);
			if (ch2 == '/')
			{
				while (ch != '\n')
					ch = fgetc(fptr1);
				fputc('\n', fptr2);
			}
			else if (ch2 == '*')
			{
				do
				{
					while (ch != '*')
						ch = fgetc(fptr1);
					ch = fgetc(fptr1);
				} while (ch != '/');
				ch = fgetc(fptr1);
			}
			else
			{
				fputc(ch, fptr2);
				fputc(ch2, fptr2);
			}
		}
		else
			fputc(ch, fptr2);
		ch = fgetc(fptr1);
	}
}
void DiscardsPreProc(FILE *fptr1, char src[], FILE *fptr2)
{
	int p = 0, c = 0;
	char ch = fgetc(fptr1);
	while (ch != EOF)
	{
		p++;
		ch = fgetc(fptr1);
		if (ch == 'm')
		{
			ch = fgetc(fptr1);
			if (ch == 'a')
			{
				ch = fgetc(fptr1);
				if (ch == 'i')
				{
					ch = fgetc(fptr1);
					if (ch == 'n')
						break;
					else continue;
				}
				else continue;
			}
			else continue;
		}
		else continue;
	}
	fclose(fptr1);
	fptr1 = fopen(src, "r");
	ch = fgetc(fptr1);
	while (c < p)
	{
		c++;
		if (ch == '#')
		{
			num++;
			while (ch != '\n')
				ch = fgetc(fptr1);
		}
		fputc(ch, fptr2);
		ch = fgetc(fptr1);
	}
	while (ch != EOF)
	{
		fputc(ch, fptr2);
		ch = fgetc(fptr1);
	}
}
int compKeywords(char buf[])
{
	for (int i = 0; i < 32; i++)
		if (strcmp(buf, keywords[i]) == 0)
			return 1;
	return 0;
}
int compSymbols(char ch)
{
	for (int i = 0; i < 17; i++)
		if (ch == symbols[i])
			return 1;
	return 0;
}
void printToken(token t, FILE *fptr)
{
	char buf[256];
	sprintf(buf, "<%s,%d,%d>", t.token_name, t.row, t.col);
	fputs(buf, fptr);
}
void getNextToken(FILE *fptr1, FILE *fptr2)
{
	int r = 1, c = 1, i;
	char ch = fgetc(fptr1), buf[256], ch2;
	while (ch != EOF)
	{
		i = 0;
		buf[0] = '\0';
		c++;
		token t;
		if (ch == '\n')
		{
			r++;
			c = 1;
			fputc(ch, fptr2);
			ch = fgetc(fptr1);
			continue;
		} // To modify row and col
		else if (ch == ' ')
		{
			ch = fgetc(fptr1);
			continue;
		}
		else if (compSymbols(ch) == 1) // Relational and arithmetic operators, and brackets, comma, and semi-colon
		{
			buf[i++] = ch;
			ch2 = fgetc(fptr1);
			if (ch2 == '=')
				buf[i++] = ch2;
			buf[i] = '\0';
			t.row = r;
			t.col = (--c);
			strcpy(t.token_name, buf);
			printToken(t, fptr2);
			c += strlen(buf);
			ch = ch2;
			continue;
		}
		else if (ch == '|' || ch == '&') // Logical operators
		{
			buf[i++] = ch;
			ch = fgetc(fptr1);
			if (ch == '|' || ch == '&')
				buf[i++] = ch;
		}
		else if (ch == '\"') // String literals
		{
			do
			{
				buf[i++] = ch;
				ch = fgetc(fptr1);
			} while (ch != '\"');
			buf[i++] = ch;
		}
		else if (isdigit(ch) != 0) // Numeric constants
		{
			buf[i++] = ch;
			ch2 = fgetc(fptr1);
			while (isdigit(ch2) != 0)
			{
				buf[i++] = ch2;
				ch2 = fgetc(fptr1);
			}
			if (ch2 == '.')
				do
				{
					buf[i++] = ch2;
					ch2 = fgetc(fptr1);
				} while (isdigit(ch2) != 0);
			if (ch2 == 'E' || ch2 == 'e')
			{
				buf[i++] = ch2;
				ch2 = fgetc(fptr1);
				if (ch2 == '+' || ch2 == '-')
				{
					buf[i++] = ch2;
					ch2 = fgetc(fptr1);
				}
				while (isdigit(ch2) != 0)
				{
					buf[i++] = ch2;
					ch2 = fgetc(fptr1);
				}
			}
			buf[i] = '\0';
			t.row = r;
			t.col = (--c);
			strcpy(t.token_name, buf);
			printToken(t, fptr2);
			c += strlen(buf);
			ch = ch2;
			continue;
		}
		else if (isalpha(ch) != 0 || ch == '_') // Identifiers and Keywords
		{
			buf[i++] = ch;
			ch2 = fgetc(fptr1);
			while (isalnum(ch2) != 0 || ch2 == '_')
			{
				buf[i++] = ch2;
				ch2 = fgetc(fptr1);
			}
			buf[i] = '\0';
			t.row = r;
			t.col = (--c);
			if (compKeywords(buf) == 1)
				strcpy(t.token_name, buf);
			else
				strcpy(t.token_name, "id");
			printToken(t, fptr2);
			c += strlen(buf);
			ch = ch2;
			continue;
		}
		else
			buf[i++] = ch; // Special characters
		buf[i] = '\0';
		t.row = r;
		t.col = (--c);
		strcpy(t.token_name, buf);
		printToken(t, fptr2);
		c += strlen(buf);
		ch = fgetc(fptr1);
	}
}
int main()
{
	FILE *fptr1, *fptr2;
	char file[100];
	char op[50];
	printf("Enter input file: ");
	scanf("%s", file);
	fptr1 = fopen(file, "r");
	fptr2 = fopen("file1.txt", "w");
	if (fptr1 == NULL)
	{
		printf("File does not exist\n");
		exit(0);
	}
	DiscardsPreProc(fptr1, file, fptr2);
	fclose(fptr1);
	fclose(fptr2);
	fptr1 = fopen("file1.txt", "r");
	fptr2 = fopen("file2.txt", "w");
	RemovesWsComments(fptr1, fptr2);
	fclose(fptr1);
	fclose(fptr2);
	fptr1 = fopen("file2.txt", "r");
	printf("Enter name of output file:");
	scanf("%s",op);
	fptr2 = fopen(op, "w");
	getNextToken(fptr1, fptr2);
	fclose(fptr1);
	fclose(fptr2);
	printf("Tokens are generated in %s\n",op);
}
