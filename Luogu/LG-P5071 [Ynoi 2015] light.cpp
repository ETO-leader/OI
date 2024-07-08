#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int MOD=19260817;
const int pr_lss_1k=168;
const vector<int> mrp{
    2,3,5,7,11,13,17,19};
mt19937_64 rnd(time(NULL));
vector<lint> p;
unordered_map<int,int> id;
void initpr(int n){
    vector<bool> isp(n,true);
    cir(i,2,n){
        if(!isp[i]) continue;
        for(int j=i*2;j<n;j+=i) isp[j]=false;
        id[i]=p.size();p.push_back(i);
    }
}
lint qpow(lint a,lint b,int mod=MOD){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=mod;
        (a*=a)%=mod;b>>=1;
    }
    return res;
}
lint __inv(lint p){return qpow(p,MOD-2);}
vector<lint> inv;
void initinv(int n){
    inv.resize(n);
    cir(i,0,n) inv[i]=__inv(i);
}
struct query{int l,r,idx;};
bool miller_rabin(lint p){
    if(p<2) return false;
    if(p==2||p==3) return true;
    if((!(p%2))||(!(p%3))) return false;
    int b=p-1,t=0;
    while(b&1) (b>>=1),(++t);
    for(auto&i:mrp){
        int r=qpow(i,b,p);
        if(r==1||r==p-1) continue;
        bool isnp=true;
        for(int j=1;j<=t&&isnp;++j){
            (r*=r)%=p;isnp=(r!=p-1);
        }
        if(isnp) return false;
    }
    return true;
}
lint pollard_rho(lint x){
    lint s=0,t=0,c=rnd()%(x-1)+1,v=1;
    for(int g=1;;g*=2,s=t,v=1){
        cir(stp,1,g+1){
            t=(t*t+c)%x;v=v*abs(t-s)%x;
            if(!(stp%127)){
                lint d=__gcd(v,x);
                if(d>1) return d;
            }
        }
        lint d=__gcd(v,x);
        if(d>1) return d;
    }
}
void prime_alg(lint x,lint&md){
    if(x<md||x<2) return;
    if(miller_rabin(x))
        return md=max(md,x),void();
    lint p=x;
    while(p>=x) p=pollard_rho(p);
    while(!(x%p)) x/=p;
    prime_alg(x,md);prime_alg(p,md);
}
const int blcs=1e3;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;initpr(1000);
    initinv(200007);
    const int sqr=sqrt(n)+1;
    vector<lint> v(n);
    vector<int> sum(pr_lss_1k);
    vector<vector<int>> pre(n+1,vector<int>(
        pr_lss_1k)),mxp(n+1);
    for(auto&i:v) cin>>i;
    v.insert(v.begin(),0);
    int numsum=[&](){
        int cnx=p.size();
        cir(i,1,n+1){
            cir(j,0,p.size()){
                while(!(v[i]%p[j])){
                    (v[i]/=p[j]);sum[j]++;
                }
            }
            if(v[i]>1){
                lint mxd=1;prime_alg(v[i],mxd);
                if(!(id.count(mxd))) id[mxd]=cnx++;
                mxp[i].push_back(id[mxd]);
                if(mxd!=v[i]){
                    mxd=v[i]/mxd;
                    if(!(id.count(mxd))) id[mxd]=cnx++;
                    mxp[i].push_back(id[mxd]);
                }
            }
            pre[i]=sum;
        }
        return cnx;
    }();
    vector<query> qx(q);
    [&](int c=0){
        for(auto&[l,r,idx]:qx){
            cin>>l>>r;idx=c++;
        }
    }();
    sort(qx.begin(),qx.end(),[&](query&a,query&b){
        return a.l/sqr==b.l/sqr?a.r<b.r:a.l<b.l;
    });
    vector<int> cnx(numsum);lint ansi=1;
    auto chgpos=[&](int p,int w){
        if(mxp[p].empty()) return;
        if(mxp[p].size()<2||mxp[p][0]==mxp[p][1]){
            (ansi*=inv[cnx[mxp[p][0]]+1])%=MOD;
            (ansi*=((cnx[mxp[p][0]]+=
                w*(int)(mxp[p].size()))+1))%=MOD;
            return;
        }
        (((ansi*=inv[cnx[mxp[p][0]]+1])%=MOD)*=
            inv[cnx[mxp[p][1]]+1])%=MOD;
        cnx[mxp[p][0]]+=w;cnx[mxp[p][1]]+=w;
        (((ansi*=(cnx[mxp[p][0]]+1))%=MOD)*=
            (cnx[mxp[p][1]]+1))%=MOD;
    };
    int lx=0,rx=-1;vector<lint> ans(q);
    for(auto&[l,r,idx]:qx){
        while(rx<r) chgpos(++rx,1);
        while(lx>l) chgpos(--lx,1);
        while(rx>r) chgpos(rx--,-1);
        while(lx<l) chgpos(lx++,-1);
        ans[idx]=ansi;
        cir(j,0,pr_lss_1k) (ans[idx]*=
            ((pre[r][j]-pre[l-1][j]+1)))%=MOD;
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
