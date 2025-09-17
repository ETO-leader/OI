#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,m,a[N],ans;
string s,t;
bitset<20010> f[20010];
bitset<N> g[25];
signed main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T,id;
	cin>>T>>id;
	while(T--){
		cin>>s>>t;
		n=s.size()+1;m=t.size()+1;
		s=' '+s+'/';t=' '+t+'/';
		if(id<=4){
			for(int i=1;i<=n;++i) f[i]=0;
			f[0][0]=1;
			for(int i=0;i<=n;++i){
				for(int j=1;j<=m;++j){
					if(i>0&&s[i]==t[j]&&f[i-1][j-1]) f[i][j]=1;
					if(j>1&&t[j]==t[j-1]&&f[i][j-2]) f[i][j]=1;
				}
			}
			cout<<(f[n][m]?"YES":"NO")<<'\n';
			continue;
		}
		if(id==5){
			for(int i=1;i<=n;++i) g[i]=0;
			g[0][0]=1;
			for(int i=0;i<=n;++i){
				for(int j=1;j<=m;++j){
					if(i>0&&s[i]==t[j]&&g[i-1][j-1]) g[i][j]=1;
					if(j>1&&t[j]==t[j-1]&&g[i][j-2]) g[i][j]=1;
				}
			}
			cout<<(g[n][m]?"YES":"NO")<<'\n';
			continue;
		}
		if(id==6){
			--n,--m;
			int suma=0,ssa=0;bool sol=0;
			for(int i=1;i<=m;++i){
				int lst=i;
				while(t[i+1]==t[i]) ++i;
				int l=i-lst+1;
				if(t[i]!='a'){
					if(l&1){
						cout<<"NO\n";
						sol=1;break;
					}
					continue;
				}
				suma+=i-lst+1;
				ssa+=(l&1);
			}
			if(sol) continue;
			if(n%2!=ssa%2) cout<<"NO\n";
			else if(n>suma||n<ssa) cout<<"NO\n";
			else cout<<"YES\n";
			continue;
		}
	}
	return 0;
}
