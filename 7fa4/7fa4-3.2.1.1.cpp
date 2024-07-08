#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
struct dsu{
    vector<T> F,siz,Mx,Exmx;
    vector<pair<T,T>> ops;
    dsu(T n):F(n),Mx(n),siz(n,1){
        iota(F.begin(),F.end(),0);
        iota(Mx.begin(),Mx.end(),0);
    }
    T findset(int x){return x==F[x]?x:findset(F[x]);}
    T merge(int x,int y){
        x=findset(x),y=findset(y);
        if(x==y){
            ops.push_back({-1,-1});return Mx[x];
        }
        if(siz[y]<siz[x]) swap(x,y);
        ops.push_back({x,y});siz[y]+=siz[x];
        Exmx.push_back(Mx[y]);Mx[y]=max(Mx[y],Mx[x]);
        return F[x]=y,Mx[y];
    }
    void remoke(){
        if(ops.empty()) return;
        assert(ops.size());
        T x=ops.back().first,y=ops.back().second;
        ops.pop_back();
        if(x<0||y<0) return;
        F[x]=x;siz[y]-=siz[x];
        Mx[y]=Exmx.back();Exmx.pop_back();
    }
};
unordered_map<string,int> opt=
    {{"query",1},{"merge",2},{"ctrlz",3}};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;dsu<int> ds(n+1);
    cir(i,0,q){
        string op;cin>>op;
        if(opt[op]==1){
            int x,y;cin>>x>>y;
            cout<<(ds.findset(x)==ds.findset(y))<<'\n';
        }else if(opt[op]==2){
            int x,y;cin>>x>>y;
            cout<<ds.merge(x,y)<<'\n';
        }else ds.remoke();
    }
    return 0;
}