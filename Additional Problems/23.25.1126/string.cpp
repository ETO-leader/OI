#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("string.in");
ofstream fcout("string.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    string s,t;fcin>>s>>t;
    const int n=s.size(),m=t.size();
    VI D(n+1,m);D[0]=-1;
    vector<VI> suf(m,VI(26));
    [&](){
        VI cnt(26,m);
        for(int i=m-1;~i;--i){
            cnt[t[i]-'a']=i;
            suf[i]=cnt;
        }
    }();
    int ans=m;
    if(s==t) ans=1;
    cir(i,1,n+1) if(D[i-1]<m-1){
        if(suf[D[i-1]+1][s[i-1]-'a']<m)
            D[i]=suf[D[i-1]+1][s[i-1]-'a'];
        cir(x,0,s[i-1]-'a'){
            ans=min(ans,suf[D[i-1]+1][x]+1-i);
        }
        if(D[i]>m-2) ans=min(ans,D[i]+1-i);
        if(i<n&&D[i]<m) ans=min(ans,m-i);
    }
    fcout<<ans<<'\n';
    return 0;
}
