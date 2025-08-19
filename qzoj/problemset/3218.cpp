#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class tree{
private:
    vector<vector<int>> gr;
    vector<long double> f;
    vector<int> siz,fs,imp;
    auto dfs(int u)->int{
        siz[u]=(int)(gr[u].empty());
        for(auto&i:gr[u]) siz[u]+=dfs(i),fs[u]+=fs[i]+2;
        f[u]=1e18l;
        do{
            auto w=0.0l;
            auto usz=siz[u];
            for(auto&i:gr[u]){
                usz-=siz[i];
                w+=siz[i]+f[i];
                w+=usz*(fs[i]+2);
            }
            f[u]=min(f[u],w);
        }while(next_permutation(gr[u].begin(),gr[u].end()));
        if(imp[u]) fs[u]=0;
        return siz[u];
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
    }
    auto stimp(int u){imp[u]=true;}
    auto calc(){
        dfs(0);
        return f[0]/siz[0];
    }
    tree(int _n):gr(_n),f(_n),siz(_n),fs(_n),imp(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;
    while(cin>>n&&n){
        tree gr(n);
        cir(u,0,n){
            int f;string s;cin>>f>>s;--f;
            if(f>-1) gr.link(f,u);
            if(s[0]=='Y') gr.stimp(u);
        }
        cout<<fixed<<setprecision(15)<<gr.calc()<<'\n';
    }
    return 0;
}
