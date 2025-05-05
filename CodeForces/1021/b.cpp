#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:(f[u]=findset(f[u]));
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int n):f(n){ranges::iota(f,0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,m,k;cin>>n>>m>>k;
        vector ban(n,vector<int>(m)),id(n,vector<int>(m));
        vector<pair<int,int>> p(k+1);
        for(auto&[x,y]:p){
            cin>>x>>y;--x;--y;
            ban[x][y]=true;
        }
        for(auto c=-1;auto&x:id) for(auto&w:x) w=++c;
        vector<vector<int>> u(k);
        cir(i,1,k+1){
            if(p[i].first==p[i-1].first){
                if(abs(p[i].second-p[i-1].second)!=2) return cout<<0<<'\n',void();
                const auto ux=p[i].first,vx=(p[i].second+p[i-1].second)/2;
                if(ban[ux][vx]) return cout<<0<<'\n',void();
                u[i-1].emplace_back(id[ux][vx]);
            }else if(p[i].second==p[i-1].second){
                if(abs(p[i].first-p[i-1].first)!=2) return cout<<0<<'\n',void();
                const auto ux=(p[i].first+p[i-1].first)/2,vx=p[i].second;
                if(ban[ux][vx]) return cout<<0<<'\n',void();
                u[i-1].emplace_back(id[ux][vx]);
            }else if(abs(p[i].first-p[i-1].first)==1&&abs(p[i].second-p[i-1].second)==1){
                if(!ban[p[i].first][p[i-1].second]) u[i-1].emplace_back(id[p[i].first][p[i-1].second]);
                if(!ban[p[i-1].first][p[i].second]) u[i-1].emplace_back(id[p[i-1].first][p[i].second]);
            }else{
                return cout<<0<<'\n',void();
            }
        }
        dsu uid(n*m);
        for(auto&x:u){
            if(x.empty()) return cout<<0<<'\n',void();
            if(x.size()==2) uid.merge(x[0],x[1]);
        }
        vector<int> cnt(n*m),chk(n*m),ucnt(n*m);
        for(auto&x:u){
            ++chk[uid.findset(x[0])];
            if(x.size()==1) ++cnt[uid.findset(x[0])];
        }
        cir(i,0,n*m) ++ucnt[uid.findset(i)];
        auto ans=1ll;
        cir(i,0,n*m) if(chk[i]){
            if(chk[i]>ucnt[i]) ans=0;
            if(chk[i]<ucnt[i]) (ans*=ucnt[i])%=MOD;
            if(chk[i]==ucnt[i]&&(!cnt[i])) (ans*=2)%=MOD;
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
