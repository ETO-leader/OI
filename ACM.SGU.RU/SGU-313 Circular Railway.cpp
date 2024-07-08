#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct location{
    int pos,type,id;
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,l;cin>>n>>l;vector<int> a(n),b(n);
    vector<location> loc;
    cir(i,0,n){
        auto&p=a[i];
        cin>>p;loc.push_back({p,1,i});
    }
    cir(i,0,n){
        auto&p=b[i];
        cin>>p;loc.push_back({p,-1,i});
    }
    sort(loc.begin(),loc.end(),[](auto&u,auto&v){
        return u.pos<v.pos;
    });
    loc.push_back(loc.front());
    auto cnt=0ll,sum=0ll,sop=0ll;
    vector<int> lseg,sopi;
    cir(i,0,(int)(loc.size())){
        sop+=loc[i].type;
        lseg.push_back(loc[i+1].pos-loc[i].pos);
        sopi.push_back(sop);
        sum+=lseg.back();
        cnt+=sop*lseg.back();
    }
    vector<int> px(n*2);
    iota(px.begin(),px.end(),0);
    sort(px.begin(),px.end(),[&](auto u,auto v){
        return sopi[u]<sopi[v];
    });
    auto len=0ll,las=0ll,ans=cnt,pos=0ll;
    return 0;
}
