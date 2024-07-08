#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr int MOD=1e9+7;
class dsu{
private:
    vector<int> f;
public:
    int findset(int x){
        return f[x]==x?x:(f[x]=findset(f[x]));}
    void merge(int x,int y){
        f[findset(x)]=findset(y);}
    dsu(int x):f(x){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    freopen("bracket.in","r",stdin);
    freopen("bracket.out","w",stdout);
    string s;cin>>s;dsu fx(s.size());
    const int n=s.size();
    stack<int> psx;VI w(n),f(n,-1),vis(n);
    cir(i,0,n){
        if(s[i]=='('){
            psx.push(i);
            //if(i&&(s[i-1]==')')) fx.merge(i,i-1);
        }else{
            if(psx.empty()) continue;
            //fx.merge(i,psx.top());
            f[i]=psx.top();
            psx.pop();
            //const int fi=fx.findset(i);
            //++w[fi];
            //if(i<n-1) --w[i+1];
        }
    }
    for(int i=n-1;i;--i) if(!vis[i]){
        vis[i]=true;
        lint siz=0,cnx=0,u=i;
        while(u>-1&&f[u]>-1){
            u=f[u];++siz;
            if(u&&s[u-1]=='(') break;
            if(u) vis[--u]=true;
        }
        u=i;
        while(u>-1&&f[u]>-1){
            w[u]+=siz-cnx;
            if(f[u]>0) w[f[u]-1]-=(++cnx);
            u=f[u];
            if(u&&s[u-1]=='(') break;
            --u;
        }
    }
    lint ans=0,suf=0;
    for(int i=n-1;~i;--i){
        ans+=((((suf+=w[i])%=MOD)+=
            MOD)%=MOD)*(i+1)%MOD;
    }
    cout<<ans<<'\n';
    return 0;
}