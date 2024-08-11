#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("array.in");
ofstream fcout("array.ans");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,lint b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint x){return qpow(x,MOD-2);}
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;fcin>>n;vector<int> l(n),r(n);
    cir(i,0,n) fcin>>l[i]>>r[i];
    l.insert(l.begin(),1e9+7);r.insert(r.begin(),1e9+7);
    l.push_back(-1);r.push_back(-1);
    for(int i=n;~i;--i) l[i]=max(l[i],l[i+1]);
    cir(i,1,n+1) r[i]=min(r[i],r[i-1]);
    const auto m=n+2;
    vector<int> id;
    for(auto&i:l) id.push_back(i-1);
    for(auto&i:r) id.push_back(i);
    sort(id.begin(),id.end());
    id.erase(unique(id.begin(),id.end()),id.end());
    const auto mxw=id.size();
    vector<int> lx(mxw-1),rx(mxw-1),len(mxw-1);
    cir(i,0,mxw-1){
        lx[i]=id[i]+1;rx[i]=id[i+1];
        len[i]=rx[i]-lx[i]+1;
    }
    vector f(m,vector<lint>(mxw-1)),pre(m,vector<lint>(mxw-1));
    vector<lint> iv(m+7);
    cir(i,1,m+7) iv[i]=math.inv(i);
    f[0][mxw-2]=1;
    cir(i,0,m-1){
        auto pref=0ll;
        for(auto p=mxw-2;~p;--p) (f[i][p]+=((pref+=pre[i][p])%=MOD))%=MOD;
        cir(p,0,mxw-1) if(l[i]<lx[p]+1&&rx[p]<r[i]+1){
           auto prew=1ll,prek=1ll;
            cir(k,i+1,m){
                if(!(l[k-1]<lx[p]+1&&rx[p]<r[k-1]+1)) break;
                const auto kx=k-i;
                (prek*=iv[kx])%=MOD;
                (prew*=(len[p]+kx-1))%=MOD;
                const auto c=prew*prek%MOD;
                if(p) (pre[k][p-1]+=f[i][p]*c)%=MOD;
            }
        }
    }
    auto pref=0ll;
    for(auto p=mxw-2;~p;--p) (f[m-1][p]+=((pref+=pre[m-1][p])%=MOD))%=MOD;
    fcout<<f[m-1][0]<<'\n';
    return 0;
}
