#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class tree{
private:
    vector<vector<int>> f,gr;
    vector<lint> ans;
    auto dfs(int u,int fx=-1)->int{
        auto hx=0;
        for(auto&i:gr[u]) if(i!=fx) hx=max(hx,dfs(i,u)+1);
        f[u].resize(hx+1);f[u][0]=1;
        for(auto&i:gr[u]) if(i!=fx){
            cir(ax,0,(int)(f[i].size())) cir(bx,0,hx+1){
                if(!f[u][bx]) break;
                ans[(ax+1)^bx]+=1ll*f[i][ax]*f[u][bx];
            }
            cir(ax,0,(int)(f[i].size())){
                f[u][ax+1]+=f[i][ax];
            }
        }
        return hx;
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto check(){
        mt19937 rnd(random_device().operator()());
        for(auto&i:gr) shuffle(i.begin(),i.end(),rnd);
        dfs(1);auto res=ans;
        while((!res.empty())&&(!res.back())) res.pop_back();
        return res;
    }
    tree(int _n):gr(_n+1),f(_n+1),ans(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;tree gr(n);
    cir(i,2,n+1){
        int f;cin>>f;gr.insert(f,i);
    }
    auto ans=gr.check();
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
