#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#if not defined(__DEBUG__)
ifstream inf("ampm.in");
ofstream ouf("ampm.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
#define cin inf
#define cout ouf
#endif
struct relation_t{
    int delta,x;
};
auto calctime(string s){
    const auto hr=(s[0]-'0')*10+s[1]-'0';
    const auto mn=(s[3]-'0')*10+s[4]-'0';
    return pair(hr,mn);
}
auto split(string cl){
    string tla,tlb;
    auto i=0;
    for(;cl[i]!='=';++i) tla.push_back(cl[i]);
    for(++i;i<(int)(cl.size());++i) tlb.push_back(cl[i]);
    const auto rl=tla.back()-'A';
    const auto ps=tlb.back()-'A';
    const auto[ha,ma]=calctime(tla);
    const auto[hb,mb]=calctime(tlb);
    if(ma!=mb) throw exception();
    relation_t res;res.x=ps;
    res.delta=ha-hb;
    return tuple(res,rl,ha,hb);
}
ostream&operator<<(ostream&os,vector<int> q){
    for(auto&i:q) os<<i<<' ';
    return os;
}
auto impossible(){
    cout<<"Inconsistent\n";exit(0);
}
auto ambiguous(){
    cout<<"Ambiguous\n";exit(0);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n;
    cin>>m;vector<int> a(m);
    for(auto&i:a) cin>>i;
    cin>>k;vector<int> b(k);
    for(auto&i:b) cin>>i;
    vector<vector<relation_t>> rls(m);
    int q;cin>>q;
    cir(i,0,q){
        string s;cin>>s;
        try{
            const auto[rlsi,pos,hra,hrb]=split(s);
            if(hra>a[pos]-1||hrb>b[rlsi.x]-1) throw exception();
            rls[pos].push_back(rlsi);
        }catch(exception&){
            impossible();
        }
    }
    vector<int> bx(k);iota(bx.begin(),bx.end(),0);
    auto ans=0;
    vector<int> ansp,ansb;
    do{
        vector<int> f(1<<m),fr(1<<m);
        f[0]=1;
        vector<int> loc(k);
        [&](){
            auto pre=0;
            cir(i,0,k) loc[bx[i]]=pre,pre+=b[bx[i]];
        }(); 
        cir(s,0,(1<<m)) if(f[s]){
            const auto sumi=[&](){
                auto res=0;
                cir(i,0,m) if(s&(1<<i)) res+=a[i];
                return res;
            }();
            cir(i,0,m) if(!(s&(1<<i))) [&](){
                for(auto&[delta,x]:rls[i]){
                    if(loc[x]!=sumi+delta) return;
                }
                f[s|(1<<i)]+=f[s];
                fr[s|(1<<i)]=s;
            }();
        }
        if(f[(1<<m)-1]){
            ans+=f[(1<<m)-1];ansp=fr;ansb=bx;
        }
    }while(next_permutation(bx.begin(),bx.end()));
    if(!ans) impossible();
    if(ans>1) ambiguous();
    vector<int> ansa;
    auto u=(1<<m)-1;
    cir(i,0,m){
        ansa.insert(ansa.begin(),__builtin_ctz(u^(ansp[u])));
        u=ansp[u];
    }
    for(auto&i:ansa) ++i;
    for(auto&i:ansb) ++i;
    cout<<"Alde system: "<<ansa<<'\n';
    cout<<"Baran system: "<<ansb<<'\n';
    return 0;
}
