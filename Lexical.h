/*
 Create By AMDS
 2012.4.5
*/

#ifndef LEXICAL_H
#define LEXICAL_H

#include <string>
using namespace std;

typedef enum
{
	KeyWord = 1,
	Tag = 2,
	Constant = 3,
	Operator = 4,
	Delimit = 5,
	UNDIFINED = 6
}TYPE;

typedef struct
{
	TYPE type;
	string str;
}RST;

void analysis(char *str,RST *_rsl);

#endif