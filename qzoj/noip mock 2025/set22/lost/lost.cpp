#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
ifstream inf("lost.in");
ofstream ouf("lost.out");
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class dp{
private:
    vector<vector<array<array<lint,2>,2>>> f,g;
    vector<vector<array<array<bool,2>,2>>> vis;
    const int n,k;
    vector<int> lim,s;
    vector<lint> pw;
    auto calc(int p,int c,int cur,lint&ans,int l){
        if(p<0) return (lint)(c==k);
        if(vis[p][c][cur][l]) return (ans+=g[p][c][cur][l])%=MOD,f[p][c][cur][l];
        vis[p][c][cur][l]=true;
        const auto ulm=(l?lim[p]:1);
        cir(w,0,ulm+1) if(c+(s[p]^cur!=w)<k+1){
            const auto vc=calc(p-1,c+(s[p]^cur!=w),cur^(s[p]^cur!=w),ans,l&&(w==ulm));
            if(w) (ans+=vc*pw[p])%=MOD,(g[p][c][cur][l]+=vc*pw[p])%=MOD;
            if(p) (g[p][c][cur][l]+=g[p-1][c+(s[p]^cur!=w)][cur^(s[p]^cur!=w)][l&&(w==ulm)])%=MOD;
            (f[p][c][cur][l]+=vc)%=MOD;
        }
        return f[p][c][cur][l];
    }
public:
    auto calc(){
        if(lim.empty()) return 0ll;
        auto ans=0ll;
        const auto c=calc(n-2,0,0,ans,true)+calc(n-2,0,1,ans,true);
        return (ans+c*pw[n-1])%MOD;
    }
    dp(int _n,int _k,vector<int> _lim,vector<int> _s):n(_n),k(_k),s(_s),pw(_n+7,1),
        f(_n,vector<array<array<lint,2>,2>>(_k+1)),
        g(_n,vector<array<array<lint,2>,2>>(_k+1)),
        vis(_n,vector<array<array<bool,2>,2>>(_k+1)){
        assert((int)(_s.size())==n-1);
        if((int)(_lim.size())>n) lim.resize(_n,1);
        else if((int)(_lim.size())==n) lim=_lim;
        cir(i,1,n+7) pw[i]=pw[i-1]*2%MOD;
    }
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,k;inf>>n>>k;
    string s;
    if(n>1) inf>>s;
    reverse(s.begin(),s.end());
    vector<int> is(s.size());
    cir(i,0,(int)(s.size())) is[i]=(s[i]=='R');
    string ql,qr;inf>>ql>>qr;
    if(ql>qr){
        ouf<<0<<'\n';
    }else{
        reverse(ql.begin(),ql.end());
        reverse(qr.begin(),qr.end());
        if(n>1){
            auto p=0;
            while(ql[p]=='0') ql[p]='1',++p;
            ql[p]='0';
            while((!ql.empty())&&ql.back()=='0') ql.pop_back();
            vector<int> liml(ql.begin(),ql.end()),limr(qr.begin(),qr.end());
            for(auto&x:liml) x-='0';
            for(auto&x:limr) x-='0';
            ouf<<(dp(n,k,limr,is).calc()+MOD-dp(n,k,liml,is).calc())%MOD<<'\n';
        }else{
            ouf<<1<<'\n';
        }
    }
    return 0;
}
