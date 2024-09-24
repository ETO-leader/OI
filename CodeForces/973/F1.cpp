#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class sparsetable{
private:
    static constexpr auto ups=21;
    vector<vector<int>> a;
    vector<int> lgx;
    auto init(vector<int> x){
        const auto n=(int)(x.size());
        a.resize(ups,vector<int>(n));
        a[0]=x;
        cir(c,1,ups) cir(i,0,n-(1<<c)+1){
            a[c][i]=max(a[c-1][i],a[c-1][i+(1<<(c-1))]);
        }
        lgx.resize(n+7);
        cir(i,2,n+7) lgx[i]=(lgx[i>>1]+1);
    }
public:
    auto query(int l,int r){
        if(l>r) return -1;
        const auto c=lgx[r-l+1];
        return max(a[c][l],a[c][r-(1<<c)+1]);
    }
    sparsetable(vector<int> x){init(x);}
};
class tree{
private:
    vector<vector<int>> gr;
    vector<int> fr,dep;
    auto dfs(int u,int f=0)->int{
        fr[u]=f;dep[u]=1;
        for(auto&i:gr[u]) if(i!=f) dep[u]=max(dep[u],dfs(i,u)+1);
        return dep[u];
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto init(int u){
        dfs(0);
        vector id{u};
        while(u) id.push_back(u=fr[u]);
        ranges::reverse(id);
        unordered_set aps(id.begin(),id.end());
        vector<int> du(id.size());
        cir(i,0,(int)(id.size())){
            const auto ux=id[i];
            du[i]=1;
            for(auto&x:gr[ux]) if(!aps.count(x)) du[i]=max(du[i],dep[x]+1);
        }
        vector<int> a(id.size()),b(id.size());
        cir(i,0,(int)(id.size())) a[i]=du[i]+i,b[i]=du[i]+(int)(id.size())-i-1;
        return pair(a,b);
    }
    tree(int _n):gr(_n),fr(_n),dep(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;tree gr(n);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;--u;--v;
            gr.insert(u,v);
        }
        int sv;cin>>sv>>sv;--sv;
        const auto[a,b]=gr.init(sv);
        sparsetable sta(a),stb(b);
        auto u=0,v=(int)(a.size())-1;
        while(u<v){
            const auto x=stb.query(u+1,v);
            if(x<a[u]) return println(cout,"Alice");
            ++u;
            if(u==v) return println(cout,"Bob");
            const auto y=sta.query(u,v-1);
            if(y-1<b[v]) return println(cout,"Bob");
            --v;
        }
        println(cout,"Alice");
    }();
    return 0;
}
