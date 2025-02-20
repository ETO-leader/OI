#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
#ifdef ONLINE_JUDGE
class interactor{
public:
    auto getn(){
        int n;cin>>n;
        return n;
    }
    auto ask(int u,int v){
        cout<<"? "<<u+1<<' '<<v+1<<'\n';
        cout.flush();
        lint w;cin>>w;
        assert(w>-1);
        return w;
    }
    auto answer(vector<int> p,vector<lint> a){
        cout<<"! ";
        for(auto&i:p) cout<<i+1<<' ';
        for(auto&i:a) cout<<i<<' ';
        cout<<'\n';
        cout.flush();
    }
} interact;
#else
#include"grader.h"
#endif
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto n=interact.getn();
    vector<lint> w0(n),w1(n);
    const auto sumx=interact.ask(0,1);
    cir(i,2,n) w0[i]=interact.ask(0,i),w1[i]=interact.ask(1,i);
    w1[0]=w0[1]=sumx;
    vector<int> p0,p1;
    p0.emplace_back(0);
    p1.emplace_back(1);
    cir(i,2,n) ((w0[i]>w1[i])?p1:p0).emplace_back(i);
    ranges::sort(p0,[&](auto u,auto v){return w1[u]>w1[v];});
    ranges::sort(p1,[&](auto u,auto v){return w0[u]<w0[v];});
    vector<int> p(n),rp(n);
    auto cnt=-1;
    for(auto&i:p0) rp[p[i]=++cnt]=i;
    for(auto&i:p1) rp[p[i]=++cnt]=i;
    vector<lint> val(n);
    if(p[0]==0){
        const auto w0x=interact.ask(rp[0],rp[n-1])-interact.ask(rp[1],rp[n-1]);
        w0[0]=w0x;
        cir(i,0,p[0]) val[i]=w0[rp[i]]-w0[rp[i+1]];
        val[p[0]]=w0x;
        cir(i,p[0]+1,n) val[i]=w0[rp[i]]-w0[rp[i-1]];
        interact.answer(p,val);
    }else{
        const auto w0x=interact.ask(rp[p[0]-1],0)+interact.ask(rp[p[0]+1],0)-interact.ask(rp[p[0]-1],rp[p[0]+1]);
        w0[0]=w0x;
        cir(i,0,p[0]) val[i]=w0[rp[i]]-w0[rp[i+1]];
        val[p[0]]=w0x;
        cir(i,p[0]+1,n) val[i]=w0[rp[i]]-w0[rp[i-1]];
        interact.answer(p,val);    
    }
    return 0;
}
