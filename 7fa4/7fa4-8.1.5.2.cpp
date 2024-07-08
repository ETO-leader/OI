#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class tree{
private:
    vector<vector<int>> gr;
    vector<int> hx;
    auto init(int u,int f=0)->int{
        for(auto&i:gr[u]) if(i!=f)
            hx[u]=max(hx[u],init(i,u)+1);
        if(f) gr[u].erase(find(gr[u].begin(),gr[u].end(),f));
        return hx[u];
    }
    auto dfs(int u,lint&ans,deque<int>*f,deque<lint>*g){
        if(!f) f=new deque<int>(),g=new deque<lint>();
        auto&fu=*f;auto &gu=*g;
        if(gr[u].empty()) return pair(&(fu=deque(1,1)),&(gu=deque(1,0ll)));
        nth_element(gr[u].begin(),gr[u].begin(),gr[u].end(),
            [&](auto&a,auto&b){return hx[a]>hx[b];});
        dfs(gr[u][0],ans,f,g);fu.push_front(1);gu.pop_front();
        gu.push_back(0);gu.push_back(0);
        for(auto&i:gr[u]) if(i!=gr[u][0]){
            auto[fx,gx]=dfs(i,ans,nullptr,nullptr);
            cir(w,0,(int)(fx->size())){
                ans+=1ll*(*fx)[w]*gu[w+1];
                if(w>1) ans+=1ll*(*gx)[w]*fu[w-1];
                gu[w+1]+=1ll*fu[w+1]*(*fx)[w];
                if(w) gu[w-1]+=(*gx)[w];
            }
            cir(w,0,(int)(fx->size())) fu[w+1]+=(*fx)[w];
            delete fx;delete gx;
        }
        ans+=gu[0];
        return pair(f,g);
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto check(){
        init(1);auto ans=0ll;
        auto[fx,gx]=dfs(1,ans,nullptr,nullptr);
        delete fx;delete gx;
        return ans;
    }
    tree(int _n):gr(_n+1),hx(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;tree gr(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        gr.insert(u,v);
    }
    cout<<gr.check()<<'\n';
    return 0;
}
