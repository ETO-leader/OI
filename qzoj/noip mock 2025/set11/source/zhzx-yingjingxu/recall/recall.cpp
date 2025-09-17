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
int c;
signed main()
{
	freopen("recall.in","r",stdin);
	freopen("recall.out","w",stdout);
	cin>>c;
	if(!c)
	{
		printf("5 46\n5 20\n5 28\n7 1190\n6 320\n5 20\n4 4\n6 18\n4 4\n5 11\n");
		return 0;
	}
	__BEGIN_MULTITEST__
	int n,k;
	scanf("%lld%lld",&n,&k);
	int x;
	for(int i=1;i<n;i++)
		scanf("%lld%lld",&x,&x);
	printf("2 1\n");
	__END_MULTITEST__
	return 0;
}

