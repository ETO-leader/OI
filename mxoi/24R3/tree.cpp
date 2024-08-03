#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("tree.in");
ofstream fcout("tree.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;

#include<algorithm>

#if __cplusplus < 202000L // C++14 / C++17

#if not defined(LIGHT_RANGES_FUNCTIONS_FOR_CPP17)

#define LIGHT_RANGES_FUNCTIONS_FOR_CPP17 1

namespace ranges{
    auto sort(auto&x){
        sort(x.begin(),x.end());
    }
    auto sort(auto&x,auto cmp){
        sort(x.begin(),x.end(),cmp);
    }
    auto nth_element(auto&x,auto it){
        nth_element(x.begin(),it,x.end());
    }
    auto nth_element(auto&x,auto it,auto cmp){
        nth_element(x.begin(),it,x.end(),cmp);
    }
    auto stable_sort(auto&x){
        stable_sort(x.begin(),x.end());
    }
    auto stable_sort(auto&x,auto cmp){
        stable_sort(x.begin(),x.end(),cmp);
    }
    auto unique(auto&x){
        return unique(x.begin(),x.end());
    }
    auto is_sorted(auto&x){
        return is_sorted(x.begin(),x.end());
    }
    auto is_sorted(auto&x,auto cmp){
        return is_sorted(x.begin(),x.end(),cmp);
    }
    auto reverse(auto&x){
        reverse(x.begin(),x.end());
    }
    auto iota(auto&x,auto w){
        iota(x.begin(),x.end(),w);
    }
    auto rotate(auto&x,auto it){
        rotate(x.begin(),it,x.end());
    }
    auto shuffle(auto&x){
        shuffle(x.begin(),x.end());
    }
    auto shuffle(auto&x,auto cmp){
        shuffle(x.begin(),x.end(),cmp);
    }
    auto accumulate(auto&x,auto w){
        return accumulate(x.begin(),x.end(),w);
    }
    auto accumulate(auto&x,auto w,auto f){
        return accumulate(x.begin(),x.end(),w,f);
    }
    auto count(auto&x,auto w){
        return count(x.begin(),x.end(),w);
    }
    auto find(auto&x,auto w){
        return find(x.begin(),x.end(),w);
    }
    auto lower_bound(auto&x,auto w){
        return lower_bound(x.begin(),x.end(),w);
    }
    auto lower_bound(auto&x,auto w,auto f){
        return lower_bound(x.begin(),x.end(),w,f);
    }
    auto upper_bound(auto&x,auto w){
        return upper_bound(x.begin(),x.end(),w);
    }
    auto upper_bound(auto&x,auto w,auto f){
        return upper_bound(x.begin(),x.end(),w,f);
    }
    auto max_element(auto&x){
        return max_element(x.begin(),x.end());
    }
    auto max_element(auto&x,auto f){
        return max_element(x.begin(),x.end(),f);
    }
    auto min_element(auto&x){
        return min_element(x.begin(),x.end());
    }
    auto min_element(auto&x,auto f){
        return min_element(x.begin(),x.end(),f);
    }
    auto fill(auto&x,auto w){
        fill(x.begin(),x.end(),w);
    }
    auto for_each(auto&x,auto f){
        for_each(x.begin(),x.end(),f);
    }
    
}

#endif

#endif

class tree{
private:
    vector<vector<int>> gr;
    vector<int> siz,dep,fr,vis;
    auto dfs(int u,int f=0)->int{
        dep[u]=dep[f]+1;fr[u]=f;
        for(auto&i:gr[u]) if(i!=f) siz[u]+=dfs(i,u);
        return ++siz[u];
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto registertree(){
        dfs(1);
        for(auto&x:gr){
            ranges::sort(x,[this](int x,int y){return siz[x]>siz[y];});
        }
    }
    auto split(int u){
        vector<int> ns;
        while(u) ns.push_back(u),u=fr[u];
        ranges::reverse(ns);
        for(auto&i:ns) vis[i]=true;
        return ns;
    }
    auto check(int u,int w)->int{
        auto res=1;
        for(auto&i:gr[u]) if((!vis[i])&&siz[u]>w){
            vis[i]=true;siz[u]-=siz[i];res+=check(i,w);
        }
        return res;
    }
    auto&sizarr(){return siz;}
    auto&fatharr(){return fr;}
    auto depth(int u){return dep[u];}
    tree(int _n):gr(_n+1),siz(_n+1),dep(_n+1),fr(_n+1),vis(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;fcin>>n;tree gr(n);
    cir(i,0,n-1){
        int u,v;fcin>>u>>v;
        gr.insert(u,v);
    }
    gr.registertree();
    if((gr.depth(n)&1)==(n&1)) exit((fcout<<-1<<'\n',0));
    auto lnk=gr.split(n);
    for(auto&i:lnk) gr.sizarr()[gr.fatharr()[i]]-=gr.sizarr()[i];
    ranges::reverse(lnk);
    auto ans=0;
    for(auto&i:lnk) ans+=gr.check(i,(n+gr.depth(i)*2-gr.depth(n)-1)/2);
    fcout<<ans<<'\n';
    return 0;
}
