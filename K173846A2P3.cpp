#include<iostream>
#include<ctime>
#include<fstream>
#include<cstdlib>
#include<cmath>
using namespace std;

class SNC{
	public:
		int front;
		int rear;
		int capacity;
		int size;
		int* at;
		int* st;
		int* wt;
		int* totalwt;
		int* totalcust;
		int* totalser;
		int avgwt;
		int avgcust;
		int avgser;
		int finalcust;
		
		SNC(){}
		SNC(int c);
		void Enqueue(int a,int b,int c);
		void Dequeue();
		bool isFull();
		bool isEmpty();
		
		void Process();
};

SNC::SNC(int c)
{
	capacity=c;
	front=0;
	size=0;
	rear=capacity-1;
	totalcust= new int[18];
	totalwt=new int[18];
	totalser=new int[18];
	at = new int[capacity];
	st = new int[capacity];
	wt = new int[capacity];
}

bool SNC::isEmpty()
{
	bool flag=false;
	if(size==0)
	{
		flag=true;
	}
	return flag;
}

bool SNC::isFull()
{
	bool flag=false;
	if(size==capacity)
	{
		flag=true;
	}
	return flag;
}

void SNC::Enqueue(int a, int b, int c)
{
	if(!SNC::isFull())
	{
		rear=(rear+1)%capacity;
		at[rear]=a;
		wt[rear]=b;
		st[rear]=c;
		size++;
	}
}

void SNC::Dequeue()
{
	if(!SNC::isEmpty())
	{
		front=(front+1)%capacity;
		size--;
	}
}

void SNC::Process()
{
	ofstream out("queue.txt");
	int i,n,j,k,l,s,counter;
	for(i=0;i<18;i++)
	{
				//n=rand()%30+1;
				n=(rand()%(30-1+1))+1;
				SNC hour(n);
				counter=n*2;
				while(j<=counter)
				{	
					if(j==0)
					{
					s=rand()%8+3;
					hour.Enqueue(0,0,s);
					k++;
					}
					else
					{
						s=(rand()%(8-3+1))+3;
						hour.Enqueue(j,hour.st[k-1]-j,s);
						k++;
					}
					j+=2;
				}
				this->totalcust[i]=n;
				for(l=0;l<n;l++)
				{
					this->totalwt[i]+=hour.wt[l];
					this->totalser[i]+=hour.st[l];
				}
	}
	int tcust=0,twt=0,tser=0,tn=0;
	for(i=0;i<18;i++)
	{
		tcust+=this->totalcust[i];
		twt+=this->totalwt[i];
		tser+=this->totalser[i];
	}
	finalcust=tcust;
	avgcust=finalcust/18;
	avgser=tser/18;
	avgwt=twt/18;
	cout<<endl<<"Total customers = "<<finalcust<<endl<<"Average customers = "<<avgcust<<endl<<"Average service time = "<<avgser/1000000<<endl<<"Average waiting time = "<<avgwt/10000000<<endl;
	out<<endl<<"Total customers = "<<finalcust<<endl<<"Average customers = "<<avgcust<<endl<<"Average service time = "<<avgser/1000000<<endl<<"Average waiting time = "<<avgwt/10000000<<endl;
}

int main()
{
	SNC S(1);
	S.Process();
}
