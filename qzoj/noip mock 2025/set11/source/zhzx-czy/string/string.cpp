#include<bits/stdc++.h>
using namespace std;
string s,t;
int to[1001001],to2[1001001];
int f[1001001],g[1001001],n,m;
set<pair<int,int> >v[30][2];
int id;
void solve(){
    cin>>s;cin>>t;
    // cerr<<s<<"$$$"<<t<<"\n";
    n=s.size()+1;s=" "+s+"a";
    m=t.size()+1;t=" "+t+"a";
    if(id<=5){
        for (int i=1;i<=n;i++)f[i]=-1e9;
        f[0]=0;
        for (int i=1;i<=m;i++){
            to[i]=i;if(i-2>=0&&t[i]==t[i-1])to[i]=to[i-2];
            int now=to[i-1];
            for (int j=1+(i%2==0);j<=n;j+=2)
            if(s[j]==t[i]&&f[j-1]>=now)f[j]=i;
        }
        if(f[n]==m)cout<<"YES\n";
        else cout<<"NO\n";
        return ;
    }
    for (int i=1;i<=n;i++)f[i]=-1e9;
    // cerr<<"&&&\n";
    f[0]=0;
    for (int i=0;i<26;i++)
    v[i][0].clear(),v[i][1].clear();
// cerr<<"+++\n";
    for (int i=1;i<=n;i++)v[s[i]-'a'][i&1].insert({f[i-1],i});
    for (int i=m;i>=1;i--){
        to2[i]=i;
        if(i+2<=m&&t[i+1]==t[i])to2[i]=to2[i+2];
    }
    for (int i=1;i<=m;i++){
        // cerr<<i<<"%%%\n";
        to[i]=i;if(i-2>=0&&t[i]==t[i-1])to[i]=to[i-2];
        int now=to[i-1];
        int pp=to2[i];
        // cerr<<"****\n";
        // while(pp+2<=m&&t[pp+1]==t[pp])pp+=2;
        // cerr<<"####\n";
        vector<pair<int,int> >vv;
        while(v[t[i]-'a'][i&1].size()){
            int x=(*--v[t[i]-'a'][i&1].end()).second;
            int val=(*--v[t[i]-'a'][i&1].end()).first;
            // c
            assert(f[x-1]==val);
            // cerr<<x<<"~~~~~\n";
            if(f[x-1]<now)break;
            // cerr<<"^^^\n";
            v[t[i]-'a'][i&1].erase({f[x-1],x});
            vv.push_back({f[x-1],x});
            // v[t[i]-'a'][i&1].insert({f[x-1],x});
            // cerr<<"$$$\n";
            if(x+1<=n)
            v[s[x+1]-'a'][(i&1)^1].erase({f[x],x+1});
            f[x]=pp;
            if(x+1<=n)
            v[s[x+1]-'a'][(i&1)^1].insert({f[x],x+1});

        }
        for (auto j:vv)v[t[i]-'a'][i&1].insert(j);
        // cerr<<"&&&\n";
        // for (int j=1+(i%2==0);j<=n;j+=2)
        // if(s[j]==t[i]&&f[j-1]>=now)f[j]=i;
    }
    // cerr<<"+++\n";
    if(f[n]==m)cout<<"YES\n";
    else cout<<"NO\n";
}
int main(){
    freopen("string.in","r",stdin);
    freopen("string.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;cin>>T>>id;
    while(T--)solve();
}