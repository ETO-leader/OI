#include <bits/stdc++.h>
//#include <bits/extc++.h>
#define int long long
#define INLINE inline __attribute__((always_inline))
#define BreakPlus break
#define liuhengxi continue
#define __BEGIN_MULTITEST__ \
	signed T; \
	scanf("%d",&T); \
	while(T--) \
	{
#define __END_MULTITEST__ }
using ll=long long;
using i128=__int128;
using namespace std;
//using namespace __gnu_cxx;
//using namespace __gnu_pbds;
const int N=1e6+5;
int c,n,k;
int a[N];
int sum=0;
struct FenwickTree
{
	int tr[N];
	void _Update(int x,int k)
	{
		for(int i=x;i<=n;i+=i&-i)
			tr[i]+=k;
	}
	int _Query(int x)
	{
		int ret=0;
		for(int i=x;i;i-=i&-i)
			ret+=tr[i];
		return ret;
	}
}BIT;
pair<int,int> ans[3];
int p=0; 
signed main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	scanf("%lld%lld%lld",&c,&n,&k);
//	__BEGIN_MULTITEST__
	int tmp=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		BIT._Update(a[i],1);
		tmp+=i-BIT._Query(a[i]);
	}
	k=tmp-k;
	if(!k)
	{
		printf("0\n");
		return 0;
	}
	for(int i=1;i<=n;i++)
		BIT._Update(a[i],-1);
	int l=1,r=1,sum=0;
	while(l<=n&&r<=n)
	{
		while(sum<k)
		{
			BIT._Update(a[r],1);
			sum+=r-l+1-BIT._Query(a[r]);
			r++;
		}
		if(sum==k)
		{
			ans[++p]={l,r-1};
			break;
		}
		while(sum>k)
		{
			BIT._Update(a[l],-1);
			sum-=BIT._Query(a[l]);
			l++;
		}
	}
	printf("%lld\n",p);
	for(int i=1;i<=p;i++)
		printf("%lld %lld\n",ans[i].first,ans[i].second);
	memset(BIT.tr,0,sizeof BIT.tr);
	sort(a+l,a+r);
	k=tmp-k;
	tmp=0;
	for(int i=1;i<=n;i++)
	{
		BIT._Update(a[i],1);
		tmp+=i-BIT._Query(a[i]);
	}
//	cerr<<tmp<<'\n';
	assert(tmp==k);
//	__END_MULTITEST__
	return 0;
}

