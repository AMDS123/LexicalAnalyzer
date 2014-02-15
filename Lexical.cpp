/*
  Create By AMDS
  2012.4.5
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lexical.h"

#define ANALYSISTEMP 			*q = 0; \
analysisTemp(temp); \
*temp = 0; \
q = temp;

//char strs[] = "main(){int a,b;       \
//			  a = 10;     \n   \
//			  b = a + 20; \n  \
//			  }";

char keywords[10][10] = {"if","else","int","for","while","do","return","break","continue","then"};
char operators[10][3] = {"+","-","*","/","=",">","<","!=",">=","<="};
char delimits[6] = {',', ';', '{', '}', '(', ')'};
char spaces[6] = {' ','\t','\n'};
char nums[] = {'0','1','2','3','4','5','6','7','8','9'};
char dot = '.';

int count = 0; //µ±«∞◊÷∑˚ ˝¡ø
RST rslt[256];

void printStr(TYPE type,char *str)
{
	printf("(%d,\"%s\")\n",type,str);
	rslt[count].type = type;
	rslt[count].str = str;
	count++;
}

void printChar(TYPE type,char ch)
{
	printf("(%d,\"%c\")\n",type,ch);
	rslt[count].type = type;
	char temp[10];
	sprintf(temp,"%c",ch);
	rslt[count].str = temp;
	count++;
}

void printInt(TYPE type,int i)
{
	printf("(%d,\"%d\")\n",type,i);
	rslt[count].type = type;
	char temp[100];
	sprintf(temp,"%d",i);
	rslt[count].str = temp;
	count++;
}


int isSpace(char p)
{
	return (p==' '||p=='\n'||p=='\t');
}

int isOperator(char p)
{
	for (int i=0;i<8;i++)
	{
		if (p == operators[i][0])
		{
			return 1;
		}
	}
	return 0;
}

int isDelimit(char ch)
{
	for (int i=0;i<6;i++)
	{
		if(ch == delimits[i])
			return 1;
	}
	return 0;
}

int isNum(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return 1;
	}
	return 0;
}

void analysisTemp(char *str)
{
	if (*str == 0)
	{
		return;
	}
	for (int i=0;i<10;i++)
	{
		if (strcmp(str,keywords[i]) == 0)
		{
			//printf("(%d,\"%s\")\n",KeyWord,str);
			printStr(KeyWord,str);
			return;
		}
	}
	//printf("(%d,\"%s\")\n",Tag,str);
	printStr(Tag,str);
}

void analysis(char *str,RST *_rsl)
{
	char temp[1024] = {0};
	double d = 0.0;

	char *p = str;
	char *q = temp;

	int bNum = 0;

	while (*p != 0)
	{
		if (*p >= 'A' && *p <= 'z')
		{
			*q++ = *p;
		} 
		else if (isNum(*p))
		{
			d = d * 10 + (*p - '0');
			if (!isNum(*(p+1)))
			{
				printInt(Constant,d);
				d = 0.0;
			}
		}
		else if (isDelimit(*p))
		{
			ANALYSISTEMP
				printChar(Delimit,*p);
		}
		else if ((*p == '!' || *p == '<' || *p == '>') && *(p+1) == '=')
		{
			ANALYSISTEMP
				if (*p == '!') printStr(Operator,"!=");
				else if (*p == '<') printStr(Operator,"<=");
				else if (*p == '>') printStr(Operator,">=");
				++p;
		}
		else if (isOperator(*p))
		{
			ANALYSISTEMP
				printChar(Operator,*p);
		}
		else if (isSpace(*p))
		{
			ANALYSISTEMP
		}

		++p;
	}

	for (int i=0;i<count;i++)
	{
		_rsl[i] = rslt[i];
	}

	_rsl[count].str = "#";
	
}