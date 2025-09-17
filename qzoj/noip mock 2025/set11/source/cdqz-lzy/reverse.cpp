#include <bits/stdc++.h>

using namespace std;

const int N=1e6+10;
long long a[N],d[N],id,n,k,s[N],sum,res,cnt,s2[N];

void modify(int nw,long long add)
{
	nw=n-nw+1;
	for(int i=nw;i<=n;i+=i&(-i)) s[i]+=add;
	return ;
}

long long qry(int nw) 
{
	nw=n-nw+1;
	long long res=0;
	for(int i=nw;i>=1;i-=i&(-i)) res+=s[i];
	return res; 
}

void modify2(int nw,long long add)
{
	for(int i=nw;i<=n;i+=i&(-i)) s2[i]+=add;
	return ;
}

long long qry2(int nw) 
{
	int res=0;
	for(int i=nw;i>=1;i-=i&(-i)) res+=s2[i];
	return res; 
}

int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	scanf("%lld%lld%lld",&id,&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		d[i]=qry(a[i]);
		modify(a[i],1);
	}
	for(int i=1;i<=n;i++) sum+=d[i];
	if(sum==k) printf("0");
	else 
	{
		memset(s,0,sizeof(s));
		int l=1,r=1;
		modify(a[1],1),modify2(a[1],1);
		for(;l<=n;l++)
		{
			while(r+1<=n&&res+qry(a[r+1])<=sum-k) r++,res+=qry(a[r]),modify(a[r],1),modify2(a[r],1);
			if(res==sum-k)
			{
				printf("1\n%d %d",l,r);
				return 0; 
			}
			modify(a[l],-1);
			modify2(a[l],-1);
			res-=qry2(a[l]);
		}
		for(int i=n;i>=1;i--) 
		{
			if(d[i]<k) k-=d[i];
			else if(d[i]==k)
			{
				printf("1\n1 %d",i-1);
				return 0;
			} 
			else
			{
				printf("2\n1 %d\n",i-1);
				sort(a+1,a+i);
				for(int j=i-1;j>=1;j--)
				{
					if(a[j]>a[i]) cnt++;
					if(cnt==d[i]-k) 
					{
						printf("%d %d",j,i);
						return 0; 
					}
				}
			}
		} 
	}
	return 0;
}
