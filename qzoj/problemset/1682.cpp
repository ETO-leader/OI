#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class acam{
private:
    vector<array<int,4>> v;
    vector<int> fail;
    vector<bool> vis;
    int cnt;
public:
    auto emplace(string s){
        auto u=0,res=0,x=0;
        for(auto&c:s){
            if(!v[u][c]) v[u][c]=++cnt;
            u=v[u][c];
            ++x;
            if(vis[u]) res=x;
        }
        return res;
    }
    auto init(){
        queue<int> q;q.emplace(0);
        while(!q.empty()){
            const auto u=q.front();q.pop();
            cir(vx,0,4){
                const auto id=v[u][vx];
                if(!id) continue;
                if(u){
                    auto x=fail[u];
                    while(x&&!v[x][vx]) x=fail[x];
                    fail[id]=v[x][vx];
                }
                q.emplace(id);
            }
            if(vis[u]){
                auto x=fail[u];
                while(x&&(!vis[x])) vis[x]=true,x=fail[x];
            }
        }
    }
    auto check(string&s){
        auto u=0;
        for(auto&c:s){
            while(u&&(!v[u][c])) u=fail[u];
            u=v[u][c];
            vis[u]=true;
        }
    }
    static auto transfer(string&s){
        for(auto&x:s) x=((string)("NWSE")).find(x);
    }
    acam(int _n):v(_n),fail(_n),vis(_n),cnt(0){}
};
static constexpr auto maxl=(int)(1.9e6+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    string s;cin>>s;
    acam::transfer(s);
    acam ac(maxl);
    vector<string> q(m);
    for(auto&s:q){
        cin>>s;acam::transfer(s);
        ac.emplace(s);
    }
    ac.init();
    ac.check(s);
    ac.init();
    for(auto&s:q){
        cout<<ac.emplace(s)<<'\n';
    }
    return 0;
}
