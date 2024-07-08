#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class tree{
private:
    vector<vector<int>> gr;
    vector<int> ans,hx;
    auto init(int u,int f=0)->int{
        for(auto&i:gr[u]) if(i!=f)
            hx[u]=max(hx[u],init(i,u)+1);
        if(f) gr[u].erase(find(gr[u].begin(),gr[u].end(),f));
        return hx[u];
    }
    auto dfs(int u,deque<int>*fx){
        if(fx==nullptr){
            fx=new deque<int>();
        }
        auto&fu=*fx;
        nth_element(gr[u].begin(),gr[u].begin(),gr[u].end(),
            [&](int&a,int&b){return hx[a]>hx[b];});
        if(gr[u].empty()){
            fu.push_front(1);return fx;
        }
        dfs(gr[u][0],fx);fu.push_front(1);
        ans[u]=ans[gr[u][0]]+1;
        for(auto&i:gr[u]) if(i!=gr[u][0]){
            auto fi=dfs(i,nullptr);
            cir(w,0,(int)(fi->size())){
                fu[w+1]+=(*fi)[w];
            }
            cir(w,0,(int)(fi->size())){
                if(fu[w+1]>fu[ans[u]]||(fu[w+1]==fu[ans[u]]&&w+1<ans[u])){
                    ans[u]=w+1;
                }
            }
            delete fi;
        }
        if(fu[ans[u]]==1) ans[u]=0;
        return fx;
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto calc(){
        init(1);
        delete dfs(1,nullptr);
        return ans;
    }
    tree(int _n):gr(_n+1),ans(_n+1),hx(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;tree gr(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;gr.insert(u,v);
    }
    auto ans=gr.calc();
    ans.erase(ans.begin());
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
