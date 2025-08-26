#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#ifndef ONLINE_JUDGE
ifstream inf("frac.in");
ofstream ouf("frac.out");
#else
auto&inf(cin);
auto&ouf(cout);
#endif
using lint=long long;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,q;inf>>n>>q;
    vector<double> a(n),b(n);
    for(auto&i:a){
        int w;inf>>w;i=w;
    }
    for(auto&i:b){
        int w;inf>>w;i=w;
    }
    vector<vector<tuple<int,int,int,int>>> qry(15);
    cir(i,0,q){
        int l,r,x;inf>>l>>r>>x;--l;--r;
        auto nx=1,pw=0;
        cir(c,0,15){
            if(abs((x-nx)*1.0/nx)<0.5){
                qry[pw].emplace_back(l,r,x-nx,i);
                break;
            }
            nx*=3;
            ++pw;
        }
    }
    vector<double> ans(q);
    vector<double> pre(n),val(n);
    cir(i,0,15){
        auto x=1ll;
        cir(c,0,i) x*=3;
        const auto k=qry[i].size();
        vector<double> pd(k,1);
        fill(val.begin(),val.end(),1);
        cir(k,0,40){
            pre=val;
            cir(i,0,n) pre[i]=val[i]*(a[i]/(b[i]+x));
            cir(i,1,n) pre[i]+=pre[i-1];
            for(auto p=-1;auto&[l,r,w,id]:qry[i]){
                ++p;
                ans[id]+=pd[p]*(pre[r]-(l?pre[l-1]:0));
                pd[p]*=-1.0*w/x;
            }
            cir(i,0,n) val[i]*=x*1.0/(b[i]+x);
        }
    }
    ouf<<fixed<<setprecision(9);
    for(auto&x:ans) ouf<<x<<'\n';
    return 0;
}
