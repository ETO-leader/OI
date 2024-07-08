#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct treenode{
    lint w,pos;
    bool operator<(const treenode&tr) const{
        return w==tr.w?pos<tr.pos:w<tr.w;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;set<treenode> valx;
    vector<lint> c(n),x(n),cxal(n),chd(n);
    for(auto&i:x) cin>>i,--i;
    cir(i,0,n) cin>>c[i],cxal[x[i]]+=c[i];
    cir(i,0,n) valx.insert({cxal[i],i});
    lint cnx=0;
    while(!valx.empty()){
        auto [w,pos]=*valx.begin();
        valx.erase(valx.begin());
        chd[pos]=true;cnx+=w;
        if(!chd[x[pos]]){
            auto fd=valx.find({cxal[x[pos]],x[pos]});
            assert(fd!=valx.end());
            cxal[x[pos]]-=c[pos];
            valx.erase(fd);
            valx.insert({cxal[x[pos]],x[pos]});
        }
    }
    cout<<cnx<<'\n';
    return 0;
}
