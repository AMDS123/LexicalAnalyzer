/*
 
 Create By AMDS
 2012.4.5
 
 原文法
 S     →  id  =  E  ;
 S     →  if  C  then  S
 S     →  while  C  do  S
 C     →  E  >  E
 C     →  E  <  E
 C     →  E  = = E
 E     →  TE'
 E'  →  +TE'
 E'   →  ɛ
 T     →  FT'
 T'   →  *FT'
 T'   →  ɛ
 F     →  (  E  )
 F     →  id   // id为标识符
 F     →  num  // num为无符号数
 改写后的文法
 Select(S     →  id  =  E  ;) = {id}
 Select(S     →  if  C  then  S)={if}
 Select(S     →  while  C  do  S)={while}
 Select(C     →  E  >  E)={ (, id, num}
 Select(C     →  E  <  E)={ (, id, num}
 Select(C     →  E  = = E)={ (, id, num}
 Select(E     →  TE')={(, id, num}
 Select(E'  →  +TE')={+}
 Select(E'   →  ɛ)={;then,do,),<,>,==}
 Select(T     →  FT')={(, id, num}
 Select(T'   →  *FT')={*}
 Select(T'   →  ɛ)={+}
 Select(F     →  (  E  ))={(}
 Select(F     →  id)={id}
 Select(F     →  num)={num}
 */

#include <iostream>
#include <string>
#include "Lexical.h"

using namespace std;


void Match(string str);
void Err(string msg);
void S();
void E();
void E1();
void C();
void T();
void T1();
void F();

string strs;
int token = 0;
RST tmpRslt[256];

string strtmp = "if a < b then a = b#";

void Match(string str)
{
	if (tmpRslt[token].str == str)
	{
		token++;
	}
}
void Err(string msg)
{
	cout<<"Error:"<<msg<<endl;
}

void S()
{
	if (tmpRslt[token].type == Tag)
	{
		Match(tmpRslt[token].str);
		Match("=");
		E();
		Match(";");
	}
	else if (tmpRslt[token].str == "if")
	{
		Match("if");
		C();
		Match("then");
		S();
	}
	else if (tmpRslt[token].str == "while")
	{
		Match("while");
		C();
		Match("do");
		S();
	}
	else if (tmpRslt[token].type == 0)
	{
		return;
	}
	else
	{
		Err("S");
	}
}

void E()
{
	if (tmpRslt[token].str == "(" || tmpRslt[token].type == Tag || tmpRslt[token].type == Constant)
	{
		T();
		E1();
	}
	else if (tmpRslt[token].type == 0)
	{
		return;
	}
	else
	{
		Err("E");
	}
}

void C()
{
	if (tmpRslt[token].str == "(" || tmpRslt[token].type == Tag || tmpRslt[token].type == Constant)
	{
		E();
		Match(tmpRslt[token].str);
		E();
	}
	else if (tmpRslt[token].type == 0)
	{
		return;
	}
	else
	{
		Err("C");
	}
}

void E1()
{
	if (tmpRslt[token].str == "+")
	{
		Match("+");
		T();
		E1();
	}
}

void T()
{
	if (tmpRslt[token].str == "(" || tmpRslt[token].type == Tag || tmpRslt[token].type == Constant)
	{
		F();
		T1();
	}
	else if (tmpRslt[token].type == 0)
	{
		return;
	}
	else
	{
		Err("T");
	}
}

void T1()
{
	if (tmpRslt[token].str == "*")
	{
		Match("*");
		F();
		T1();
	}
}

void F()
{
	if (tmpRslt[token].str == "(")
	{
		Match("(");
		E();
		Match(")");
	}
	else if (tmpRslt[token].type == Tag)
	{
		Match(tmpRslt[token].str);
	}
	else if (tmpRslt[token].type == Constant)
	{
		Match(tmpRslt[token].str);
	}
	else if (tmpRslt[token].type == 0)
	{
		return;
	}
	else 
	{
		Err("F");
	}
}


int main()
{
	cout << strtmp << endl << endl;
	analysis(&strtmp[0],tmpRslt);
	cout << endl;
	
	S();
	if (tmpRslt[token].str != "#")
	{
		Err("#");
	}
	else
	{
		cout << "”Ôæ‰∆•≈‰≥…π¶" << endl;
	}

	return 0;
}