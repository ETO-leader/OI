#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class tree{
private:
    vector<vector<int>> gr;
    vector<lint> v;
    auto dfs(int u,int f=-1)->__gnu_pbds::priority_queue<lint>*{
        auto res=new __gnu_pbds::priority_queue<lint>();
        for(auto&i:gr[u]) if(i!=f){
            auto nq=dfs(i,u);
            res->join(*nq);
            delete nq;
        }
        res->push(0);
        const auto w=res->top();
        res->pop();
        res->push(w+v[u]);
        return res;
    }
public:
    auto link(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto check(int k){
        const auto res=dfs(0);
        auto ans=0ll;
        k=min<int>(k,res->size());
        cir(i,0,k) ans+=res->top(),res->pop();
        delete res;
        return ans;
    }
    tree(vector<lint> _v):v(_v),gr(_v.size()){}
};
class caseistream{
private:
    stringstream inf;
public:
    auto init(){
        int n,k;cin>>n>>k;
        inf<<n<<' '<<k<<'\n';
        cir(i,0,n){
            int w;cin>>w;inf<<w<<' ';
        }
        inf<<'\n';
        cir(i,0,n-1){
            int u,v;cin>>u>>v;
            inf<<u<<' '<<v<<'\n';
        }
    }
    auto&stream(){return inf;}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    caseistream inf;inf.init();
    int n,k;inf.stream()>>n>>k;
    vector<lint> v(n);
    for(auto&i:v) inf.stream()>>i;
    tree gr(v);
    cir(i,0,n-1){
        int u,v;inf.stream()>>u>>v;--u;--v;
        gr.link(u,v);
    }
    cout<<gr.check(k)<<'\n';
    return 0;
}
