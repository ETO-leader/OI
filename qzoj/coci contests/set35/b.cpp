#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return u==f[u]?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> v(n);
    for(auto&x:v) cin>>x,--x;
    int q;cin>>q;
    vector<pair<int,int>> op(q);
    auto vx=v;
    for(auto&[x,y]:op){
        cin>>x>>y;--y;
        if(x==2) vx[y]=-1;
    }
    vector<int> circ(n);
    dsu qwq(n);
    cir(i,0,n) if(vx[i]>-1){
        if(qwq.findset(i)==qwq.findset(vx[i])) circ[qwq.findset(i)]=true;
        else qwq.merge(i,vx[i]);
    }
    vector<int> ans;
    reverse(op.begin(),op.end());
    for(auto&[x,y]:op){
        if(x==1){
            const auto u=qwq.findset(y);
            ans.emplace_back(circ[u]?-1:u);
        }else{
            vx[y]=v[y];
            if(qwq.findset(y)==qwq.findset(vx[y])) circ[qwq.findset(y)]=true;
            else qwq.merge(y,vx[y]);
        }
    }
    reverse(ans.begin(),ans.end());
    for(auto&i:ans){
        if(i>-1) cout<<i+1<<'\n';
        else cout<<"CIKLUS"<<'\n';
    }
    return 0;
}
