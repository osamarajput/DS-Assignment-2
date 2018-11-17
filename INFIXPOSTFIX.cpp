#include<iostream>
#include<fstream>
using namespace std;

class StackImp
{
	private:
		char* stackarray;
		int top;
		int size;
		char oparray[6];
	public:
		StackImp();
		StackImp(int s);
		void Push(char a);
		void PopAndDisplay();
		char PopAndReturn();
		void SimplePop();	
		int CheckOperator1(int el);
		int CheckOperator2();
		void Process();	
};

StackImp::StackImp()
{
	stackarray = new char[100];
	size=0;
	top=-1;
//	oparray[6]={'(','^','/','*','+','-'};
	oparray[0]='(';
	oparray[1]='^';
	oparray[2]='*';
	oparray[3]='/';
	oparray[4]='+';
	oparray[5]='-';
}

StackImp::StackImp(int s)
{
	size = s;
	stackarray = new char[s];
	top=-1;
	oparray[0]='(';
	oparray[1]='^';
	oparray[2]='*';
	oparray[3]='/';
	oparray[4]='+';
	oparray[5]='-';
}

void StackImp::Push(char a)
{
	top++;
	stackarray[top]=a;
}

void StackImp::PopAndDisplay()
{
	char temp = stackarray[top];
	top--;
	cout<<temp;
}

char StackImp::PopAndReturn()
{
	char temp = stackarray[top];
	top--;
	return temp;
}

void StackImp::SimplePop()
{
	top--;
}

int StackImp::CheckOperator1(int el)
{
	int forelement;
	for(int i=0;i<6;i++)
	{
		if(el==oparray[i])
		{
			forelement=i;
		}
	}
	return forelement;
}

int StackImp::CheckOperator2()
{
	int forelement;
	for(int i=0;i<6;i++)
	{
		if(stackarray[top]==oparray[i])
		{
			forelement=i;
		}
	}
	return forelement;
}


void StackImp::Process()
{
	
	ifstream in("infix.txt");
	ofstream out("postfix.txt");
	
	
	char el;
	//while(el>47 && el<58 || el>64 && el<91 || el>96 && el<123 || el=='(' || el=='^' || el=='/' || el=='*' || el=='+' || el=='-' || el==')') 
	//while(!in.eof())
	while(in.eof())
	{
	in>>el;
	
	int forelementt,fortopp;
	forelementt = StackImp::CheckOperator1(el);
	fortopp = StackImp::CheckOperator2();
	
	if((el>47 && el<58) || (el>64 && el<91) || (el>96 && el<123))
	{
		cout<<el;
	}
	else if(el=='(')
	{
		StackImp::Push(el);
	}
	else if(el=='^' || el=='/' || el=='*' || el=='+' || el=='-')
	{
		if(top==-1)
		{
			StackImp::Push(el);
		}
		else if(stackarray[top]=='(')
		{
			StackImp::Push(el);
		}
		else if(forelementt<=fortopp)
		{
			StackImp::Push(el);
		}
		else
		{
			//cout<<el;
			StackImp::PopAndDisplay();
		}
	
	}
	else
	//else(el==')')
	{
		while(stackarray[top]!='(')
		{
			StackImp::PopAndDisplay();
		}
		//StackImp::PopAndDisplay();
		StackImp::SimplePop();
	}
	}
	//while(stackarray[top]!=-1)
	//{
	//	StackImp::PopAndDisplay();
	//}
}

int main()
{
	StackImp s;
	s.Process();
//	s.Push('(');
//	s.PopAndDisplay();
	return 0;
}



/*
inputs

a+b*(c+d)+a*f

(a+b)*((b+c-a)/(a+b))
2*3+8/2-3+2
(300+23)*(43-21)/(84+7) 
2*(3-4)/2+3*(2+4)

outputs

a b c d + * + a f * +

a b + b c + a - a b + / *
2 3 * 8 2 / + 3 - 2 +
300 23 + 43 21 - * 84 7 + /
2 3 4 - * 2 / 3 2 4 + * +
*/
