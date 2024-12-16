#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){ranges::iota(f,0);}
};
static constexpr auto deg=360;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [](){
        int n;cin>>n;
        vector<array<int,deg>> st(22),id(22);
        vector<vector<int>> sw(deg,vector<int>(22));
        auto cnt=-1;
        for(auto&x:id) for(auto&i:x) i=++cnt;
        dsu ds(cnt+7);
        cir(i,0,n){
            string op;cin>>op;
            if(op=="C"){
                int r,ax,ay;cin>>r>>ax>>ay;
                if(ax<ay){
                    cir(i,ax,ay) st[r][i]=true;
                }else{
                    cir(i,0,ay) st[r][i]=true;
                    cir(i,ax,deg) st[r][i]=true;
                }
            }else{
                int rl,rr,a;cin>>rl>>rr>>a;
                cir(i,rl,rr) sw[a][i]=true;
            }
        }
        cir(a,0,deg-1) ds.merge(id[0][a],id[0][a+1]);
        cir(r,1,22) cir(a,0,deg){
            const auto ups=!st[r][a];
            const auto rgs=!sw[(a+1)%deg][r];
            if(ups) ds.merge(id[r][a],id[r-1][a]);
            if(rgs) ds.merge(id[r][a],id[r][(a+1)%deg]);
        }
        println("{}",(ds.findset(id[0][0])==ds.findset(id[21][0])?"YES":"NO"));
    }();
    return 0;
}

