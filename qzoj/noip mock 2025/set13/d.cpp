#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;i++)
using namespace std;
using lint=long long;
class tree{
private:
    vector<vector<int>> gr,ans,ngr;
    vector<bool> qry;
    vector<int> siz;
    auto init(int u,int f=-1)->int{
        siz[u]=1;
        for(auto&i:gr[u]) if(i!=f){
            siz[u]+=init(i,u);
        }
        return siz[u];
    }
    auto dfs(int u,deque<vector<int>>&x,int f=-1)->lint{
        if(f>-1) ngr[u].erase(find(ngr[u].begin(),ngr[u].end(),f));
        sort(ngr[u].begin(),ngr[u].end(),[&](auto a,auto b){
            return siz[a]>siz[b];
        });
        if(ngr[u].empty()){
            x.emplace_front();
            x.front().emplace_back(u);
            auto res=0ll;
            if(f>-1){
                res+=(int)(gr[f].size())-1;
                if(qry[u]) for(auto&w:gr[f]) if(w!=u) ans[u].emplace_back(w);
            }
            return res;
        }
        auto res=0ll;
        res+=dfs(ngr[u][0],x,u);
        for(auto&i:ngr[u]) if(i!=f&&i!=ngr[u][0]){
            deque<vector<int>> v;
            res+=dfs(i,v,u);
            while(x.size()<v.size()) x.emplace_back();
            cir(c,0,(int)(v.size())){
                for(auto&j:v[c]) x[c].emplace_back(j);
            }
        }
        x.emplace_front();
        x.front().emplace_back(u);
        if(x.size()>2){
            res+=(int)(x[2].size());
            if(qry[u]) for(auto&w:x[2]) ans[u].emplace_back(w);
        }
        if(f>-1){
            res+=(int)(gr[f].size())-1;
            if(qry[u]) for(auto&w:gr[f]) if(w!=u) ans[u].emplace_back(w);
        }
        return res;
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto maketag(int u){
        qry[u]=true;
    }
    auto calc(){
        ngr=gr;
        init(0);
        deque<vector<int>> x;
        auto res=dfs(0,x);
        return res/2;
    }
    auto answer(int u){
        return ans[u];
    }
    tree(int n):gr(n),ans(n),qry(n),siz(n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;tree gr(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u,--v;
        gr.link(u,v);
    }
    int q;cin>>q;
    vector<int> qry(q);
    for(auto&i:qry) cin>>i,--i,gr.maketag(i);
    cout<<gr.calc()<<'\n';
    for(auto&i:qry){
        auto res=gr.answer(i);
        for(auto&v:res) cout<<min(i,v)+1<<' '<<max(i,v)+1<<'\n';
    }
    return 0;
}
