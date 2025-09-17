#include<bits/stdc++.h>
using namespace std;
long long id,n,k;
int a[1000051];
struct tree
{
	int l,r;
	long long sum;
}t[4000051];
int b[1000051];
vector<long long>l,r;
long long merge_sort(int l,int r,int u)
{
	t[u].l=l,t[u].r=r;
	if(l==r)
	{
		t[u].sum=0;
		return 0;
	}
	int mid=l+r>>1;
	long long p=0;
	p+=merge_sort(l,mid,u<<1);
	p+=merge_sort(mid+1,r,u<<1|1);
	long long s=0;
	int ll=l,rr=mid,tot=l;
	while(ll<=mid&&rr<=r)
	{
		while(a[ll]<a[rr]&&ll<=mid&&rr<=r) b[tot++]=a[ll],ll++;
		while(a[ll]>a[rr]&&rr<=r&&ll<=mid) b[tot++]=a[rr],s+=(1ll*mid-ll+1),rr++;
	}
	if(ll>mid)
	{
		for(int i=rr;i<=r;i++)
			b[tot++]=a[i];
	}
	if(rr>r)
	{
		for(int i=ll;i<=mid;i++)
			b[tot++]=a[i];
	}
	for(int i=l;i<=r;i++)
		a[i]=b[i];
	t[u].sum=s;
	return s+p;
}
int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	cin>>id>>n>>k;
	k=(n-1)*n/2-k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	if(id==3)
	{
		cout<"0\n";
		return 0;
	}
	else if(id==4)
	{
		//cout<<k<<"\n";
		long long ll=1ll,rr=2ll;
		for(int i=2;k&&i<=n;i++,rr++)
			if((rr-ll+1)*(rr-ll)/2>k*1ll)
			{
				l.push_back(ll),r.push_back(rr-1);k-=(rr-ll)*(rr-ll-1)/2; 
				ll=i,rr=i+1;i++;
			}
		cout<<l.size()<<"\n";
		for(int i=0;i<l.size();i++)
			cout<<l[i]<<" "<<r[i]<<"\n";
		return 0;
	}
//	int ll=1,rr=n;
//	for(int i=1;i<=n;i++)
//	{
//		int j;
//		for(j=i+1;j<=n;j++)
//		{
//			merge_sort(i,j,1);
//		}
//	}
}
