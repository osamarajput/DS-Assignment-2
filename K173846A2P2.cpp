#include<iostream>
#include<cmath>
#include<string.h>
#include<fstream>
using namespace std;

class StackImp
{
	private:
		char* stackarray;
		char* postarray;
		int top;
		int size;
		int psize;
		int* intstack;
		int inttop;
		int final;
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
		void Deleter();
		void CreatePost();
		void Evaluate();
		bool CheckEvaluate();
		void IntPush(int a);
		int IntPopAndReturn();
};

StackImp::StackImp()
{
	stackarray = new char[100];
	postarray = new char[100];
	intstack = new int[100];
	size=0;
	top=-1;
	inttop=-1;
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
	postarray = new char[s];
	intstack = new int[s];
	top=-1;
	inttop=-1;
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

void StackImp::Deleter()
{
	delete[] stackarray;
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

void StackImp::IntPush(int a)
{
	top++;
	intstack[inttop]=a;
}

int StackImp::IntPopAndReturn()
{
	int temp=intstack[inttop];
	inttop--;
	return temp;
}


void StackImp::Process()
{
	
	ifstream in("infix.txt");
	ifstream in1("infix.txt");
	ofstream out("postfix.txt");
	
	char a;
	int i;
	string s;
	in1>>s;
	int l=s.length();
	//cout<<l<<endl;
	char data[l];
	for(i=0;i<l;i++)
	{
		
	in>>data[i];
	
	int forelementt,fortopp;
	forelementt = StackImp::CheckOperator1(data[i]);
	fortopp = StackImp::CheckOperator2();
	
	if((data[i]>47 && data[i]<58) || (data[i]>64 && data[i]<91) || (data[i]>96 && data[i]<123))
	{
		cout<<data[i];
		out<<data[i];
	}
	else if(data[i]=='(')
	{
		StackImp::Push(data[i]);
	}
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
		else if(forelementt>fortopp)
		{
			StackImp::Push(data[i]);
		}
		else
		{
			while(forelementt<=fortopp)
			{
			if(stackarray[top]=='(')
			{
				StackImp::SimplePop();
				break;
				
			}
			a=StackImp::PopAndReturn();
			cout<<a;
			out<<a;
			fortopp = StackImp::CheckOperator2();
			}
			StackImp::Push(data[i]);
		}
	}
	else
	{
		if(data[i]==')')
		{
		while(stackarray[top]!='(')
		{
			a=StackImp::PopAndReturn();
			cout<<a;
			out<<a;
		}
		StackImp::SimplePop();
		}
	}
	}
	while(stackarray[top]!=-1 && stackarray[top]=='^' || stackarray[top]=='/' || stackarray[top]=='*' || stackarray[top]=='+' || stackarray[top]=='-')
	{
		a=StackImp::PopAndReturn();
		cout<<a;
		out<<a;
	}
}

void StackImp::CreatePost()
{
	ifstream postin("postfix.txt");
	int i=0;
	char a;
	while(!postin.eof())
	{
		postin>>a;
		postarray[i]=a;
		//cout<<endl<<postarray[i];
		i++;
	}
	psize=i-1;
}

bool StackImp::CheckEvaluate()
{
	bool flag=false;
	if(postarray[0]>47 && postarray[0]<58)
	{
		flag=true;
		cout<<endl<<"Can be evaluated."<<endl;
	}
	cout<<endl<<"Cannot be evaluated."<<endl;
	return flag;
}

void StackImp::Evaluate()
{
	//StackImp::Deleter();
	ofstream out;
	out.open("postfix.text",ios::app);
	//bool flag = StackImp::CheckEvaluate();
	if(postarray[0]>47 && postarray[0]<58)
	{
		int i,j,op1,op2,result;
		char sign;
		for(i=0;i<psize;i++)
		{
			//if(inttop<1 && (postarray[i]>47 && postarray[i]<58))
			if(postarray[i]>47 && postarray[i]<58)
			{
				j=int(postarray[i])-48;
				StackImp::IntPush(j);
			}
			//else if(postarray[i]=='^' || postarray[i]=='/' || postarray[i]=='*' || postarray[i]=='+' || postarray[i]=='-')
			else
			{
				sign = postarray[i];
				op1=StackImp::IntPopAndReturn();
				op2=StackImp::IntPopAndReturn();
				switch(sign)
				{
					case '^' :
						{
							result=pow(op2,op1);
							break;
						}
					case '/' :
						{
							result=op2/op1;
							break;
						}
					case '*' :
						{
							result=op2*op1;
							break;
						}
					case '+' :
						{
							result=op2+op1;
							break;
						}
					case '-' :
						{
							result=op2-op1;
							break;
						}
				}
				StackImp::IntPush(result);
			}
		}
	}
	final=StackImp::IntPopAndReturn();
	cout<<endl<<final<<endl;
	out<<endl<<final;
}



int main()
{
	StackImp s;
	s.Process();
	s.CreatePost();
	s.Evaluate();
	return 0;
}
