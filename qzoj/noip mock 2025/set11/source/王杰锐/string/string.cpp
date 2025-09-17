#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define mid ((l+r)>>1)
using namespace std;
bool mtd;
const int N=1e5+5;
bitset<N>st[26],dp[3];
string s,t;
int n,m,id;
bool mtt;
signed main(){
    freopen("string.in","r",stdin);
    freopen("string.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    int T;cin>>T>>id;
    while(T--){
        cin>>s>>t;
        n=s.size(),m=t.size();
        s=' '+s,t=' '+t;
        for(int i=0;i<26;i++)st[i]=0;
        for(int i=1;i<=n;i++)st[s[i]-'a'][i]=1;
        dp[0][0]=1;
        int p=1;
        for(int i=1;i<=m;i++){
            dp[p]=(dp[(p+2)%3]<<1)&st[t[i]-'a'];
            if(t[i]==t[i-1])dp[p]|=dp[(p+1)%3];
            p=(p+1)%3;
        }   
        p=(p+2)%3;
        if(dp[p][n])cout<<"YES\n";
        else cout<<"NO\n";
    }
	return 0;
}
/*
2 1
hllo
haalbblocc
hllo
habballocc
*/