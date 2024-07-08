#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class tree{
private:
    vector<vector<int>> gr;
    vector<vector<pair<int,int>>> q;
    vector<int> hx,siz,dis;
    vector<lint> ans;
    auto init(int u,int f=0)->int{
        dis[u]=dis[f]+1;
        for(auto&i:gr[u]) if(i!=f)
            hx[u]=max(hx[u],init(i,u)+1),siz[u]+=siz[i];
        if(f) gr[u].erase(find(gr[u].begin(),gr[u].end(),f));
        return hx[u];
    }
    auto dfs(int u,deque<lint>*f){
        if(!f) f=new deque<lint>();
        auto&fu=*f;
        if(gr[u].empty()){
            for(auto&[qw,id]:q[u]) ans[id]=0;
            return fu.push_back(0),pair(f,0ll);
        }
        nth_element(gr[u].begin(),gr[u].begin(),gr[u].end(),
            [&](auto&a,auto&b){return hx[a]>hx[b];});
        auto adx=dfs(gr[u][0],f).second+siz[gr[u][0]]-1;
        fu.push_front(-adx);
        for(auto&i:gr[u]) if(i!=gr[u][0]){
            auto[fx,adi]=dfs(i,nullptr);
            fu.front()-=(adi+siz[i]-1);adx+=adi+siz[i]-1;
            cir(w,0,(int)(fx->size())) fu[w+1]+=(*fx)[w];
            delete fx;
        }
        for(auto&[qw,id]:q[u]){
            ans[id]=fu[min(qw,(int)(fu.size())-1)]+adx;
        }
        return pair(f,adx);
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto addquery(int u,int k){
        q[u].push_back({k,(int)(ans.size())});
        ans.push_back(-1);
    }
    auto cnormal(int u,int k){
        return 1ll*min(dis[u]-1,k)*(siz[u]-1);
    }
    auto check(){
        init(1);
        delete dfs(1,nullptr).first;
        return ans;
    }
    tree(int _n):gr(_n+1),q(_n+1),
        hx(_n+1),siz(_n+1,1),dis(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;tree gr(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;gr.insert(u,v);
    }
    vector<pair<int,int>> qx(q);
    for(auto&[p,k]:qx){
        cin>>p>>k;gr.addquery(p,k);
    }
    auto ans=gr.check();
    for(auto c=0;auto&[p,k]:qx) ans[c++]+=gr.cnormal(p,k);
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
