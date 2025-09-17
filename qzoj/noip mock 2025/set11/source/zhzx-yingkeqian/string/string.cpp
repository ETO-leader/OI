#include<bits/stdc++.h>
#define maxn 150005
#define fi first
#define se second
#define pii pair<int,int>
#define lowbit(x) ((x)&-(x))
#define conc(x,y,w) son[x][w]=y,fa[y]=x
#define int long long
typedef long long ll;
//inline ll sqr(ll x){return x*x;}
inline ll min(ll x,ll y){return x+=(y<x)*(y-x);}
inline ll max(ll x,ll y){return x+=(x<y)*(y-x);}
inline ll min(ll x,ll y,ll z){return min(min(x,y),z);}
inline ll max(ll x,ll y,ll z){return max(max(x,y),z);}
using namespace std;
mt19937_64 yrand((std::chrono::high_resolution_clock::now()).time_since_epoch().count());
const int N=1145,Mod=998244353,L=2e6+10,inf=(int)1e9+7,Inv=(Mod+1)/2,FM=402653184,Blen=450,G=3,iG=(Mod+1)/G,V=1e9;
inline int reduce(int x){return x-(x>=Mod)*Mod;}
inline int reduce(int x,int Mod){return x-(x>=Mod)*Mod;}

int _C;
int n,m;
char c1[maxn],c2[maxn];
namespace solve1{
	int f[2][maxn];
	inline void solve(){
		int op=0;
		for(int i=0;i<=m;i++) f[op][i]=0;
		f[0][0]=1;
		for(int i=2;i<=m;i+=2) if(c2[i-1]==c2[i-2]) f[0][i]=f[0][i-2];
		for(int i=1;i<=n;i++){
			op^=1;
			for(int j=i;j<=min(m,m-(n-i));j++){
				f[op][j]=0;
				if(c1[i-1]==c2[j-1]) f[op][j]|=f[op^1][j-1];
				if(j>1&&c2[j-1]==c2[j-2]) f[op][j]|=f[op][j-2];
			}
		}
		cout<<(f[op][m]?"YES":"NO")<<'\n';
	}
}
namespace solve2{
	void solve(){
		int k=0;
		stack<int>st;
		for(int i=0,j=0;i<m;i){
			while(j<m&&c2[i]==c2[j]) j++;
			if((i-j)%2&&(k==n||c1[k]!=c2[i])){
				while(!st.empty()&&st.top()!=c2[i]) k-=2,st.pop();
				if(st.empty()||k<2||c1[k-2]!=c2[i]) return cout<<"NO\n",void();
				k-=2,st.pop();
			}
			if((i-j)&1){
				i++,k++;
				while(!st.empty()) st.pop();
			}
			while(i+1<j&&k+1<n&&c1[k]==c2[i]&&c1[k+1]==c2[i+1]) i+=2,k+=2,st.push(c2[i]);
			// cerr<<i<<' '<<k<<'\n';
			i=j;
		}
		cout<<(k==n?"YES":"NO")<<'\n';
	}
}
namespace solve3{
	void solve(){
		for(int k=0;k<26;k++){
			int id=0,cnt=0;
			for(int i=0;i<m;i++) cnt+=c2[i]==k;
			for(int i=0;i<n;i++) cnt-=c1[i]==k;
			if(cnt<0||cnt&1) return cout<<"NO\n",void();
			cnt=0;
			for(int i=0,j=0;i<m;i){
				while(j<m&&c2[i]==c2[j]) j++;
				if((j-i)&1){
					if(c2[i]==k) cnt++;
				}
				i=j;
			}
			for(int i=0;i<n;i++) cnt-=(c1[i]==k);
			if(cnt<0) return cout<<"NO\n",void();
		}
		cout<<"YES\n";
	}
}
inline void solve(){
	int fl=1;
	cin>>c1>>c2;
	n=strlen(c1),m=strlen(c2);
	for(int i=0;i<n;i++) fl&=(c1[i]==c1[0]);
	if(m<=n+12||n*m<=(1e7)) solve1::solve();
	else solve3::solve();
}
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	#endif
	ios::sync_with_stdio(0),cin.tie(0);
	// init();
	signed T=1;
	// scanf("%d",&T);
	cin>>T>>_C;
	while(T--) solve();
	cerr<<"Time: "<<clock()*1000/CLOCKS_PER_SEC<<" ms\n";
	return 0;
}
/*
(j-p[i])/i>=k
*/ 
