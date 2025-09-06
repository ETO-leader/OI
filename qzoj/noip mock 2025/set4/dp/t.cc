#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=5e5+5,inf=1e18;
int mx[MAXN],stk[MAXN];
inline void init(int n,int *a,int *c) {
	mx[0]=inf,fill(c+1,c+n+1,inf);
	for(int i=1,tp=0;i<=n;++i) {
		while(tp&&a[stk[tp]]>a[i]) --tp,mx[tp]=max(mx[tp],mx[tp+1]);
		c[i]=min(c[i],max(mx[tp],a[i])),++tp,stk[tp]=i,mx[tp]=a[i];
	}
	for(int i=n,tp=0;i>=1;--i) {
		while(tp&&a[stk[tp]]>=a[i]) --tp,mx[tp]=max(mx[tp],mx[tp+1]);
		c[i]=min(c[i],max(mx[tp],a[i])),++tp,stk[tp]=i,mx[tp]=a[i];
	}
}
int n,m,k,ans=0;
int a[MAXN],b[MAXN],f[MAXN],g[MAXN];
vector <int> B[MAXN];
vector <array<int,2>> Q[MAXN];
struct FenwickTree {
	int s,tr[MAXN];
	inline void add(int x) { for(;x<MAXN;x+=x&-x) ++tr[x]; }
	inline int q(int x) { for(s=0;x;x&=x-1) s+=tr[x]; return s; }
}	T;
signed main() {
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	for(int i=1;i<=m;++i) scanf("%lld",&b[i]);
	init(n,a,f),init(m,b,g);
    for(int i=1;i<=n;++i) clog<<f[i]<<' ';
    clog<<'\n';
    for(int i=1;i<=m;++i) clog<<g[i]<<' ';
    clog<<'\n';
    //a[i]+b[j]<=k, a[i]+g[j]>k, f[i]+b[j]>k ==> k-f[i]<b[j]<=k-a[i], g[j]>k-a[i]
	for(int i=1;i<=m;++i) B[min(MAXN-1,g[i])].push_back(i);
	for(int i=1;i<=n;++i) if(a[i]<k) Q[max(0ll,k-a[i])].push_back({max(0ll,k-f[i]),k-a[i]});
	for(int i=MAXN-1;~i;--i) {
		for(auto z:Q[i]) clog<<i<<": "<<z[0]<<' '<<z[1]<<'\n',ans+=T.q(z[1])-T.q(z[0]);
		for(auto z:B[i]) T.add(b[z]);
        // if(ans) clog<<i<<' '<<ans<<'\n';
	}
	printf("%lld\n",ans);
	return 0;
}
