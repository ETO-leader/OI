#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
int main(int argc,char* argv[])
{
    registerTestlibCmd(argc,argv);
    int n=inf.readInt(),m=inf.readInt(),i;
    long double mx=0;
    for(i=1;i<=m;i++)
    {
    	long double a=ouf.readReal(),b=ans.readReal();
    	if(fabs(a-b)>1e-6)
    	{
    		quitf(_wa,"Wrong answer. %Lf %Lf,Delta=%Lf,Query %d.",a,b,fabs(a-b),i);
    		return 0;
		}
		mx=max(mx,fabs(a-b));
	}
	quitf(_ok,"Accept.Max delta=%.12Lf.",mx);	
}

