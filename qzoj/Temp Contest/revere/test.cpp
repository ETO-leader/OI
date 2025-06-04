#define ONLINE_JUDGE

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
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    lint qpow(lint a,lint b) const{
        lint res=1;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    lint inv(lint x) const{
        return qpow(x,MOD-2);
    }
} math;
vector<lint> operator*(vector<lint> a,lint b){
    for(size_t i=0;i<a.size();++i) (a[i]*=b)%=MOD;
    return a;
}
vector<lint>&operator-=(vector<lint>&a,vector<lint> b){
    cir(i,0,(int)(a.size())) (a[i]+=MOD-b[i])%=MOD;
    return a;
}
class base{
private:
    const int n;
    vector<vector<lint>> b;
public:
    void emplace(vector<lint> a){
        cir(i,0,n) if(a[i]){
            if(b[i].empty()){
                b[i]=a;
                cir(j,0,n) if((i!=j)&&(!b[j].empty())&&b[j][i]){
                    lint x=b[j][i]*math.inv(a[i])%MOD;
                    b[j]-=a*x;
                }
                break;
            }else{
                lint x=a[i]*math.inv(b[i][i])%MOD;
                a-=b[i]*x;
            }
        }
    }
    vector<lint> values(){
        vector<lint> res;
        cir(i,0,n) res.emplace_back(b[i][n]*math.inv(b[i][i])%MOD);
        return res;
    }
    base(int _n):n(_n),b(_n){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;inf>>n;
    vector<vector<lint>> ax(n-1,vector<lint>(n));
    for(int i=0;i<n-1;++i) for(int j=0;j<n;++j) inf>>ax[i][j];
    ax.emplace_back(vector<lint>(n));
    auto make_eq=[&](int i,vector<lint> a){
        lint s=0;
        for(int j=0;j<n;++j) s=(s+a[j])%MOD;
        lint ivs=math.inv(s);
        for(int j=0;j<n;++j) (a[j]*=ivs)%=MOD;
        vector<lint> res(n+1);
        cir(j,0,n) res[j]=a[j];
        if(i<n-1) res[n]=MOD-1;
        (res[i]+=MOD-1)%=MOD;
        return res;
    };
    int q;inf>>q;
    cir(i,0,q){
        auto b=ax;
        int k;inf>>k;
        cir(i,0,k){
            int x,y,w;inf>>x>>y>>w;--x;--y;
            b[x][y]=w;
        }
        base qwq(n);
        cir(x,0,n) qwq.emplace(make_eq(x,b[x]));
        vector<lint> ans=qwq.values();
        ouf<<ans[1]<<'\n';
    }
    return 0;
}
