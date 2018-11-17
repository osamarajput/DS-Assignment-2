#include<iostream>
#include<string.h>
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
		int CheckOperator1(char el);
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

int StackImp::CheckOperator1(char el)
{
	int forelement;
		if(el==oparray[5]||el==oparray[4])
		{
			forelement=1;
		}
		else if(el==oparray[3]||el==oparray[2])
		{
			forelement=2;
		}
		else if(el==oparray[1])
		{
			forelement=3;
		}
		else if(el==oparray[0])
		{
			forelement=4;
		}
		else
		{
			forelement=0;
		}
	return forelement;
}

int StackImp::CheckOperator2()
{
	int forelement;
		if(stackarray[top]==oparray[5]||stackarray[top]==oparray[4])
		{
			forelement=1;
		}
		else if(stackarray[top]==oparray[3]||stackarray[top]==oparray[2])
		{
			forelement=2;
		}
		else if(stackarray[top]==oparray[1])
		{
			forelement=3;
		}
		else if(stackarray[top]==oparray[0])
		{
			forelement=4;
		}
		else
		{
			forelement=0;
		}
	return forelement;
}


void StackImp::Process()
{
	
	ifstream in("infix.txt");
	ifstream in1("infix.txt");
	ofstream out("postfix.txt");
	
	int i;
	string s;
	in1>>s;
	int l=s.length();
	cout<<l<<endl;
	char data[l];
	//while(el>47 && el<58 || el>64 && el<91 || el>96 && el<123 || el=='(' || el=='^' || el=='/' || el=='*' || el=='+' || el=='-' || el==')') 
	//while(!in.eof())
	for(i=0;i<l;i++)
	{
	in>>data[i];
	
	int forelementt,fortopp;
	forelementt = StackImp::CheckOperator1(data[i]);
	fortopp = StackImp::CheckOperator2();
	
	if((data[i]>47 && data[i]<58) || (data[i]>64 && data[i]<91) || (data[i]>96 && data[i]<123))
	{
		cout<<data[i];
	}
	else if(data[i]=='(')
	{
		StackImp::Push(data[i]);
	}
	//else if(data[i]=='(' || data[i]=='^' || data[i]=='/' || data[i]=='*' || data[i]=='+' || data[i]=='-')
	else if(data[i]=='^' || data[i]=='/' || data[i]=='*' || data[i]=='+' || data[i]=='-')
	{
		if(top==-1)
		{
			StackImp::Push(data[i]);
		}
		else if(stackarray[top]=='(')
		{
			StackImp::Push(data[i]);
		}
		else if(forelementt<=fortopp)
		{
			StackImp::Push(data[i]);
		}
		else
		{
			while(forelementt>=fortopp)
			{
			if(stackarray[top]=='(')
			{
				StackImp::SimplePop();
				break;
				
			}
			StackImp::PopAndDisplay();
			fortopp = StackImp::CheckOperator2();
			}
			StackImp::Push(data[i]);
		}
	}
	else
	//else(data[i]==')')
	{
		if(data[i]==')')
		{
		while(stackarray[top]!='(')
		{
			StackImp::PopAndDisplay();
		}
		//StackImp::PopAndDisplay();
		StackImp::SimplePop();
		}
	}
	}
	while(stackarray[top]!=-1 && stackarray[top]=='^' || stackarray[top]=='/' || stackarray[top]=='*' || stackarray[top]=='+' || stackarray[top]=='-')
	//while(stackarray[top]!=-1)
	{
		StackImp::PopAndDisplay();
	}
}

int main()
{
	StackImp s;
	s.Process();
//	s.Push('(');
//	s.PopAndDisplay();
	return 0;
}

