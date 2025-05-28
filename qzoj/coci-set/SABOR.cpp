#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
enum party_type{party_a,party_b};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<vector<int>> gr(n);
    cir(i,0,5){
        int c;cin>>c;
        cir(x,0,c){
            int u,v;cin>>u>>v;--u;--v;
            gr[u].emplace_back(v);
            gr[v].emplace_back(u);
        }
    }
    vector<party_type> usr(n,party_a);
    auto check_fail=[&](int u){
        auto cnta=0,cntb=0;
        for(auto&v:gr[u]) (cnta+=(usr[v]==party_a)),(cntb+=(usr[v]==party_b));
        if(usr[u]==party_a) return cnta>2;
        return cntb>2;
    };
    unordered_set<int> fail;
    cir(i,0,n) if(check_fail(i)) fail.emplace(i);
    while(!fail.empty()){
        const auto u=*fail.begin();
        fail.erase(u);
        if(!check_fail(u)) continue;
        usr[u]=(usr[u]==party_a?party_b:party_a);
        assert(!check_fail(u));
        for(auto&v:gr[u]) if(check_fail(v)) fail.emplace(v);
    }
    cir(u,0,n) cout<<(usr[u]==party_a?'A':'B');
    cout<<'\n';
    return 0;
}
