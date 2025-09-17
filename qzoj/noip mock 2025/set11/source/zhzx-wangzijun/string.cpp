#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
	ll x; scanf("%lld",&x); return x;
}
bitset<100005>f[3],g[26];
int n,m; char s[100005],t[100005];

void procedure(){
	scanf("%s", s+1); n=strlen(s+1);
	scanf("%s", t+1); m=strlen(t+1);
	for(auto o:{0,1,2}) f[o].reset();
	for(int i=0;i<26;i++) g[i].reset();

	for(int i=1;i<=n;i++) g[s[i]-'a'][i-1]=1;
	f[0][0]=1;
	for(int i=1,o=1;i<=m;i++,o=(o+1)%3){
		f[o] = ((f[(o+2)%3] & g[t[i]-'a']) << 1);
		// cerr<<"f1"<<endl;
		if(i>=2 && t[i]==t[i-1]) f[o] |= f[(o+1)%3];
		// cerr<<"f2"<<endl;
	}
	puts(f[m%3][n]?"YES":"NO");
}
int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int T=read(), id=read();
	while(T--) procedure();
}