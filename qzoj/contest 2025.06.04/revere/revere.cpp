#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#ifndef ONLINE_JUDGE
ifstream inf("revere.in");
ofstream ouf("revere.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
#else
auto&inf=cin;
auto&ouf=cout;
#endif
using lint=unsigned long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ull;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{
        return qpow(x,MOD-2);
    }
} math;
auto operator*(vector<lint> a,auto b){
    const auto n=(int)(a.size());
    auto i=0;
    for(;i+4<n;i+=4){
        (a[i]*=b)%=MOD;
        (a[i+1]*=b)%=MOD;
        (a[i+2]*=b)%=MOD;
        (a[i+3]*=b)%=MOD;
    }
    for(;i<n;++i) (a[i]*=b)%=MOD;
    return a;
}
auto&operator-=(vector<lint>&a,vector<lint> b){
    const auto n=(int)(a.size());
    auto i=0;
    for(;i+4<n;i+=4){
        (a[i]+=MOD-b[i])%=MOD;
        (a[i+1]+=MOD-b[i+1])%=MOD;
        (a[i+2]+=MOD-b[i+2])%=MOD;
        (a[i+3]+=MOD-b[i+3])%=MOD;
    }
    for(;i<n;++i) (a[i]+=MOD-b[i])%=MOD;
    return a;
}
class base{
private:
    const int n;
    vector<vector<lint>> b;
public:
    auto emplace(vector<lint> a){
        cir(i,0,n) if(a[i]){
            if(b[i].empty()){
                b[i]=a;
                cir(j,0,n) if((i!=j)&&(!b[j].empty())&&b[j][i]){
                    const auto x=b[j][i]*math.inv(a[i])%MOD;
                    b[j]-=a*x;
                }
                break;
            }else{
                const auto x=a[i]*math.inv(b[i][i])%MOD;
                a-=b[i]*x;
            }
        }
    }
    auto valued(){
        vector<vector<int>> res(n);
        vector<lint> ivx(n);
        cir(i,0,n) if(!b[i].empty()) cir(j,0,n+1) if(b[i][j]) res[i].emplace_back(j);
        cir(i,0,n) if(!b[i].empty()) ivx[i]=math.inv(b[i][i]);
        return make_pair(res,ivx);
    }
    auto valuez(vector<lint> a,const auto&vd,const auto&ivx) const{
        cir(i,0,n) if(a[i]&&(!b[i].empty())){
            const auto x=a[i]*ivx[i]%MOD;
            for(auto&p:vd[i]) (a[p]+=MOD-b[i][p]*x%MOD)%=MOD;
        }
        auto p=-1;
        cir(i,0,n) if(b[i].empty()) p=i;
        const auto va=a[n]*math.inv(a[p])%MOD;
        if(!p) return va;
        return (b[0][n]+MOD-b[0][p]*va%MOD)*ivx[0]%MOD;
    }
    auto valuez(){
        return b[0][n]*math.inv(b[0][0])%MOD;
    }
    base(int _n):n(_n),b(_n){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;inf>>n;
    vector<vector<lint>> ax(n-1,vector<lint>(n));
    for(auto&x:ax) for(auto&i:x) inf>>i;
    ax.emplace_back(vector<lint>(n));
    auto make_eq=[&](int i,vector<lint> a){
        const auto s=accumulate(a.begin(),a.end(),0ull)%MOD;
        const auto ivs=math.inv(s);
        for(auto&i:a) (i*=ivs)%=MOD;
        vector<lint> res(n+1);
        cir(j,0,n) res[j]=a[j];
        if(i<n-1) res[n]=MOD-1;
        (res[i]+=MOD-1)%=MOD;
        return res;
    };
    int q;inf>>q;
    if(q<10){
        cir(i,0,q){
            auto b=ax;
            int k;inf>>k;
            cir(i,0,k){
                int x,y,w;inf>>x>>y>>w;--x;--y;
                b[x][y]=w;
            }
            base qwq(n);
            cir(x,0,n-1) qwq.emplace(make_eq(x,b[x]));
            ouf<<qwq.valuez()<<'\n';
        }
    }else{
        vector<vector<lint>> eqs(n);
        cir(i,0,n) eqs[i]=make_eq(i,ax[i]);
        vector<lint> ans(q);
        vector<vector<tuple<int,lint,int>>> qlp(n);
        cir(i,0,q){
            int k;inf>>k;
            assert(k==1);
            int x,y,w;inf>>x>>y>>w;--x;--y;
            qlp[x].emplace_back(y,w,i);
        }
        const auto sq=16;
        base tat(n);
        for(auto l=0;l<n;l+=sq){
            const auto r=min(l+sq,n);
            auto qaq=tat;
            cir(i,r,n) qaq.emplace(eqs[i]);
            cir(x,l,r){
                tat.emplace(eqs[x]);
                auto qwq=qaq;
                cir(i,l,r) if(i!=x) qwq.emplace(eqs[i]);
                const auto[vd,ivx]=qwq.valued();
                for(auto&[p,w,id]:qlp[x]){
                    auto b=ax[x];
                    b[p]=w;
                    ans[id]=qwq.valuez(make_eq(x,b),vd,ivx);
                }
            }
        }
        for(auto&i:ans) ouf<<i<<'\n';
    }
    return 0;
}
