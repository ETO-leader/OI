#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class acam{
private:
    vector<array<int,26>> tr,uf;
    vector<int> fail,slen;
    int cnt;
public:
    auto emplace(string s){
        auto u=0;
        for(auto&c:s){
            if(!tr[u][c-'a']) tr[u][c-'a']=++cnt;
            u=tr[u][c-'a'];
        }
        slen[u]=(int)(s.size());
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
        const auto n=(int)(tr.size());
        vector<vector<int>> vx(n);
        cir(i,1,cnt+1) vx[fail[i]].emplace_back(i);
        auto dfs=[&](auto __self,int u,int ft)->void {
            slen[u]=ft=max(ft,slen[u]);
            for(auto&i:vx[u]) __self(__self,i,ft);
        };
        dfs(dfs,0,0);
    }
    auto eval(string s){
        auto res=(string)("");
        auto u=0;
        stack<int> h;
        h.emplace(u);
        for(auto&i:s){
            res+=i;
            h.emplace(u=uf[u][i-'a']);
            if(slen[u]) cir(i,0,slen[u]) res.pop_back(),h.pop();
            u=h.top();
        }
        return res;
    }
    acam(const int _n):tr(_n),uf(_n),fail(_n),slen(_n),cnt(0){}
};
const auto maxl=(int)(1e5+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    acam ac(maxl);
    int n;cin>>n;
    cir(i,0,n){
        string x;cin>>x;
        ac.emplace(x);
    }
    ac.init();
    cout<<ac.eval(s)<<'\n';
    return 0;
}
