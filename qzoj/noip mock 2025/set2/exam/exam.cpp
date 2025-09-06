#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#ifndef ONLINE_JUDGE
ifstream inf("exam.in");
ofstream ouf("exam.out");
#else
auto&inf(cin);
auto&ouf(cout);
#endif
static constexpr auto _inf=(int)(1e9+7);
constexpr auto lowbit(auto x){return x&(-x);}
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m;inf>>n>>m;
    vector<int> a(n),b(n);
    for(auto&i:a) inf>>i,--i;
    for(auto&i:b) inf>>i,--i;
    map<int,int> ids;
    for(auto&x:a) ids.emplace(x,0);
    for(auto&x:b) ids.emplace(x,0);
    auto c=-1;
    for(auto&[x,y]:ids) y=++c;
    m=(int)(ids.size());
    vector<int> nxt(m);
    cir(i,0,n) if(a[i]!=b[i]) nxt[ids[b[i]]]|=(1<<ids[a[i]]);
    int k;inf>>k;
    vector<int> fil(m);
    cir(i,0,k){
        int u,v,w;inf>>u>>v>>w;--u;--v;
        fil[ids[v]]|=(1<<ids[u]);
    }
    auto cnt=0;
    cir(s,0,(1<<m)){
        auto ok=true;
        cir(i,0,m) if(s&(1<<i)) ok&=((s&nxt[i])==nxt[i]);
        cir(i,0,m) if(!(s&(1<<i))) ok&=(!(s&nxt[i]));
        cnt+=ok;
    }
    vector<uint8_t> ulg(1<<m);
    cir(i,0,m) ulg[1<<i]=i;
    if(*max_element(nxt.begin(),nxt.end())){
        vector<int> f(1<<m,_inf);
        cir(i,0,m) if(nxt[i]) f[1<<i]=0;
        cir(s,0,(1<<m)) for(auto vx=((1<<m)-1)^s;vx;vx^=lowbit(vx)){
            const auto v=ulg[lowbit(vx)];
            f[s|(1<<v)]=min(f[s|(1<<v)],f[s]+1+((fil[v]&s)==s)+((bool)(nxt[v]&s)));
        }
        ouf<<f[(1<<m)-1]<<'\n';
    }else{
        ouf<<0<<'\n';
    }
    return 0;
}
