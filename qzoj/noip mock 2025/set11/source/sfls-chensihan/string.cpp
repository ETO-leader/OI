#include<bitset>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
const int N=1e5+9;
bitset<N> f[3],ch[26];
char s[N],t[N]; int n,m;
void solve(){
    scanf("%s%s",t+1,s+1),n=strlen(s+1),m=strlen(t+1);
    for(int i=0;i<26;i++) ch[i].reset();
    for(int i=1;i<=m;i++) ch[t[i]-'a'].set(i);
    f[0].reset(); f[0].set(0);
    for(int i=1;i<=n;i++){
        f[i%3]=f[(i+2)%3]<<1&ch[s[i]-'a'];
        if(s[i]==s[i-1]) f[i%3]|=f[(i+1)%3];
        // for(int j=0;j<=m;j++) if(f[i%3].test(j)) printf("%d %d\n",i,j);
    }
    if(f[n%3].test(m)) puts("YES");
    else puts("NO");
}
int main(){
    freopen("string.in","r",stdin);
    freopen("string.out","w",stdout);
    int T,SJQ; scanf("%d%d",&T,&SJQ);
    while(T--) solve();
    return 0;
}