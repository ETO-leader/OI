#include "testlib.h"
#include<vector>
#include<bitset>

int main(int argc, char *argv[])
{
	registerTestlibCmd(argc, argv);
	int m=inf.readInt(1,10,"m");
	int n=ouf.readInt(0,1<<m,"n");
	int nn=ans.readInt();
	if(n!=nn) quitf(_wa,"incorrect n.");
	std::vector<std::bitset<1024>> b(m);
	std::vector<int> vis(n,-1);
	for(int i=0;i<m;i++)
	{
		int k=ouf.readInt(0,n,"size of S[i]");
		while(k--)
		{
			int x=ouf.readInt(1,n,"the element of S[i]")-1;
			if(vis[x]==i) quitf(_wa,"%d appeared twice in S[%d].",x+1,i+1);
			vis[x]=i; b[i].set(x);
		}
	}
	for(int j=0;j<n;j++)
	{
		int k=ouf.readInt(1,m,"k")-1;
		int lst=ouf.readInt(1,m,"i[1]")-1;
		auto c=b[lst];
		while(k--)
		{
			int now=ouf.readInt(lst+2,m,"i[*]")-1;
			c&=b[now],lst=now;
		}
		if(c.count()!=1||!c[j])
			quitf(_wa,"the intersection of S[i[1]],...,S[i[k]] is not {%d}.",j+1);
	}
	quitf(_ok,"correct.");
	return 0;
}
