#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<vector<pair<int,int>>> vx(n*3);
    auto cnt=-1;
    map<pair<int,int>,vector<int>> id;
    auto srt=[&](int a,int b){
        return pair(min(a,b),max(a,b));
    };
    cir(i,0,n){
        int a,b,c;cin>>a>>b>>c;--a;--b;--c;
        b+=n;
        c+=n*2;
        id[srt(a,b)].emplace_back(i+1);
        id[srt(a,c)].emplace_back(i+1);
        id[srt(b,c)].emplace_back(i+1);
        ++cnt;
        vx[a].emplace_back(b,cnt);
        vx[b].emplace_back(a,cnt);
        ++cnt;
        vx[b].emplace_back(c,cnt);
        vx[c].emplace_back(b,cnt);
        ++cnt;
        vx[a].emplace_back(c,cnt);
        vx[c].emplace_back(a,cnt);
    }
    vector<int> vis(cnt+1),uvis(n*3);
    vector<pair<int,int>> ansa;
    cir(i,0,n*3) if(!uvis[i]){
        vector<int> ans;
        [&](this auto __self,int u)->void {
            uvis[u]=true;
            while(!vx[u].empty()){
                const auto[v,id]=vx[u].back();vx[u].pop_back();
                if(vis[id]) continue;
                vis[id]=true;
                __self(v);
            }
            ans.emplace_back(u);
        }(i);
        for(auto i=0;i+2<(int)(ans.size());i+=2){
            auto u=id[srt(ans[i],ans[i+1])].back();
            id[srt(ans[i],ans[i+1])].pop_back();
            const auto v=id[srt(ans[i+1],ans[i+2])].back();
            id[srt(ans[i+1],ans[i+2])].pop_back();
            ansa.emplace_back(u,v);
        }
    }
    cout<<ansa.size()<<'\n';
    for(auto&[a,b]:ansa) cout<<a<<' '<<b<<'\n';
    return 0;
}