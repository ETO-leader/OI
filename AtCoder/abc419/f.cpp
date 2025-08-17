#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class acam{
private:
    static constexpr auto alpha=26;
    vector<array<int,alpha>> tr,uf;
    vector<int> fail,us;
    int cnt;
public:
    auto emplace(string s,int id){
        auto u=0;
        for(auto&c:s){
            if(!tr[u][c-'a']) tr[u][c-'a']=++cnt;
            u=tr[u][c-'a'];
        }
        us[u]|=(1<<id);
    }
    auto init(){
        queue<int> q;
        q.emplace(0);
        while(!q.empty()){
            const auto u=q.front();q.pop();
            cir(i,0,26) if(tr[u][i]){
                if(u){
                    auto x=fail[u];
                    while(x&&(!tr[x][i])) x=fail[x];
                    fail[tr[u][i]]=tr[x][i];
                }
                q.emplace(tr[u][i]);
            }
            uf[u]=uf[fail[u]];
            cir(i,0,26) if(tr[u][i]) uf[u][i]=tr[u][i];
        }
    }
    auto calc(int l,int c){
        vector f(cnt+1,vector<lint>(1<<c));
        vector<int> fs(cnt+1);
        cir(i,0,cnt+1){
            auto u=i;
            while(u){
                fs[i]|=us[u];
                u=fail[u];
            }
        }
        f[0][0]=1;
        cir(i,0,l){
            const auto lf=f;
            for(auto&x:f) ranges::fill(x,0);
            cir(u,0,cnt+1) cir(s,0,(1<<c)){
                cir(c,0,alpha) (f[uf[u][c]][s|fs[uf[u][c]]]+=lf[u][s])%=MOD;
            }
        }
        auto ans=0ll;
        cir(u,0,cnt+1) (ans+=f[u][(1<<c)-1])%=MOD;
        return ans;
    }
    acam(const int _n):tr(_n),uf(_n),fail(_n),us(_n),cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,l;cin>>n>>l;
    acam ac(n*10+7);
    cir(i,0,n){
        string s;cin>>s;
        ac.emplace(s,i);
    }
    ac.init();
    cout<<ac.calc(l,n)<<'\n';
    return 0;
}
