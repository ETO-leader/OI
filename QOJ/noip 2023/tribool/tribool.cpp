#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
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
    dsu(int _n):f(_n){
        ranges::iota(f,0);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int c,T;cin>>c>>T;
    while(T--) []{
        int n,m;cin>>n>>m;
        const auto T=n,F=n+1,U=n+2;
        vector<pair<int,int>> sgn(n+3);
        cir(i,0,n+3) sgn[i].first=i;
        cir(i,0,m){
            char c;cin>>c;
            if(c=='T'){
                int x;cin>>x;--x;
                sgn[x]={T,0};
            }else if(c=='F'){
                int x;cin>>x;--x;
                sgn[x]={F,0};
            }else if(c=='U'){
                int x;cin>>x;--x;
                sgn[x]={U,0};
            }else if(c=='+'){
                int x,y;cin>>x>>y;--x;--y;
                sgn[x]=sgn[y];
            }else{
                int x,y;cin>>x>>y;--x;--y;
                sgn[x]=sgn[y];
                sgn[x].second^=1;
            }
        }
        dsu qwq((n+3)*2);
        qwq.merge(T,F+n+3);
        qwq.merge(F,T+n+3);
        qwq.merge(U,U+n+3);
        cir(i,0,n){
            if(sgn[i].second){
                qwq.merge(i,sgn[i].first+n+3);
                qwq.merge(i+n+3,sgn[i].first);
            }else{
                qwq.merge(i,sgn[i].first);
                qwq.merge(i+n+3,sgn[i].first+n+3);
            }
        }
        auto ans=0;
        cir(i,0,n) ans+=(qwq.findset(i)==qwq.findset(i+n+3));
        cout<<ans<<'\n';
    }();
    return 0;
}
