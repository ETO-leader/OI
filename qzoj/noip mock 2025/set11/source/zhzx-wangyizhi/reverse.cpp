#include<bits/stdc++.h>
//#include<bits/extc++.h>
//bool Mst;
using namespace std;
using ll=long long;
using ld=long double;
#define int ll
using pii=pair<int,int>;
const int N=1e6+5;
int a[N];
struct BIT
{
	int t[N];
	BIT(){clear();}
	inline void clear(){memset(t,0,sizeof(t));}
	inline void upd(int s,int x,int n){for(;s<=n;s+=s&(-s))t[s]+=x;}
	inline int qry(int s){int res=0;for(;s;s-=s&(-s))res+=t[s];return res;}
}t;
//bool Med;
signed main()
{
//	cerr<<"Memory Size: "<<abs((&Med)-(&Mst))/1024.0/1024<<" MB\n";
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	int id,n,k,cnt=0;vector<pii> ans;
	cin>>id>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],cnt+=(i-1)-t.qry(a[i]),t.upd(a[i],1,n);
	cnt-=k;
//	cerr<<cnt<<"\n";
	while(cnt)
	{
		int L=0,R=0,mx=-1,tmp=0;
		t.clear();
		for(int r=1,l=1;r<=n;r++)
		{
			tmp+=(r-l)-t.qry(a[r]),t.upd(a[r],1,n);
			while(l<=r&&tmp>cnt) t.upd(a[l],-1,n),tmp-=t.qry(a[l]),l++;
			if(tmp>mx) L=l,R=r,mx=tmp;
		}
//		cerr<<L<<" "<<R<<" "<<mx<<"\n";
		ans.push_back({L,R}),cnt-=mx,sort(a+L,a+R+1);
	}
	cout<<(int)ans.size()<<"\n";
	for(auto e:ans) cout<<e.first<<" "<<e.second<<"\n";
	return 0;
}
