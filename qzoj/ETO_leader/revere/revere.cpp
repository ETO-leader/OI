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
    int n=a.size(),i=0;
    for(;i+4<=n;i+=4){
        (a[i]*=b)%=MOD;(a[i+1]*=b)%=MOD;
        (a[i+2]*=b)%=MOD;(a[i+3]*=b)%=MOD;
    }
    for(;i<n;++i) (a[i]*=b)%=MOD;
    return a;
}
vector<lint>& operator-=(vector<lint>&a,const vector<lint>&b){
    int n=a.size(),i=0;
    for(;i+4<=n;i+=4){
        (a[i]+=MOD-b[i])%=MOD;(a[i+1]+=MOD-b[i+1])%=MOD;
        (a[i+2]+=MOD-b[i+2])%=MOD;(a[i+3]+=MOD-b[i+3])%=MOD;
    }
    for(;i<n;++i) (a[i]+=MOD-b[i])%=MOD;
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
                cir(j,0,n) if(i!=j&&!b[j].empty()&&b[j][i]){
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
    pair<vector<vector<int>>,vector<lint>> valued(){
        vector<vector<int>> res(n);
        vector<lint> ivx(n);
        cir(i,0,n) if(!b[i].empty()){
            cir(j,0,n+1) if(b[i][j]) res[i].push_back(j);
            ivx[i]=math.inv(b[i][i]);
        }
        return make_pair(res,ivx);
    }
    lint valuez(vector<lint> a,const vector<vector<int>>&vd,const vector<lint>&ivx) const{
        cir(i,0,n) if(a[i]&&!b[i].empty()){
            lint x=a[i]*ivx[i]%MOD;
            for(size_t j=0;j<vd[i].size();++j){
                int p=vd[i][j];
                (a[p]+=MOD-b[i][p]*x%MOD)%=MOD;
            }
        }
        int p=-1;
        cir(i,0,n) if(b[i].empty()) p=i;
        lint va=a[n]*math.inv(a[p])%MOD;
        if(p==0) return va;
        return (b[0][n]+MOD-b[0][p]*va%MOD)*ivx[0]%MOD;
    }
    lint valuez(){
        return b[0][n]*math.inv(b[0][0])%MOD;
    }
    base(int _n):n(_n),b(_n){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;inf>>n;
    vector<vector<lint>> ax(n-1,vector<lint>(n));
    for(int i=0;i<n-1;++i)
        for(int j=0;j<n;++j)
            inf>>ax[i][j];
    ax.emplace_back(vector<lint>(n));
    auto make_eq=[&](int i,vector<lint> a){
        lint s=0;
        for(int j=0;j<n;++j) s=(s+a[j])%MOD;
        lint ivs=math.inv(s);
        for(int j=0;j<n;++j) (a[j]*=ivs)%=MOD;
        vector<lint> res(n+1);
        for(int j=0;j<n;++j) res[j]=a[j];
        if(i<n-1) res[n]=MOD-1;
        (res[i]+=MOD-1)%=MOD;
        return res;
    };
    int q;inf>>q;
    if(q<10){
        cir(i,0,q){
            auto b=ax;
            int k;inf>>k;
            cir(j,0,k){
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
            int k,x,y,w;inf>>k>>x>>y>>w;--x;--y;
            qlp[x].push_back(make_tuple(y,w,i));
        }
        const int sq=16;
        base tat(n);
        for(int l=0;l<n;l+=sq){
            int r=min(l+sq,n);
            base qaq=tat;
            for(int i=r;i<n;++i) qaq.emplace(eqs[i]);
            for(int x=l;x<r;++x){
                tat.emplace(eqs[x]);
                base qwq=qaq;
                for(int i=l;i<r;++i) if(i!=x) qwq.emplace(eqs[i]);
                pair<vector<vector<int>>,vector<lint>> t=qwq.valued();
                const vector<vector<int>>&vd=t.first;
                const vector<lint>&ivx=t.second;
                for(size_t j=0;j<qlp[x].size();++j){
                    int p,w,id;
                    tie(p,w,id)=qlp[x][j];
                    vector<lint> b=ax[x];
                    b[p]=w;
                    ans[id]=qwq.valuez(make_eq(x,b),vd,ivx);
                }
            }
        }
        for(int i=0;i<q;++i) ouf<<ans[i]<<'\n';
    }
    return 0;
}
