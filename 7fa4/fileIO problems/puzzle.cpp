#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("puzzle.in");
ofstream fcout("puzzle.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
class invaild{
public:
    static auto what(){return -1;}
};
class graph{
private:
    vector<vector<int>> gr,rgr;
    vector<int> r,in,rin,vis;
    auto dfs(int u)->void{
        vis[u]=true;
        for(auto&i:rgr[u]){
            r[i]=min(r[i],r[u]);
            if(!(--rin[i])) dfs(i);
        }
    }
    auto bfs(vector<int> imp){
        const auto n=(int)(gr.size());
        vector<int> ans(n);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
        vector<vector<pair<int,int>>> wr(n+1);
        cir(i,0,n) if(imp[i]) wr[r[i]].emplace_back(r[i],i);
        cir(i,0,n) if((!imp[i])&&(!in[i])) q.emplace(r[i],i);
        cir(x,1,n+1){
            for(auto&[w,u]:wr[x]) q.emplace(w,u);
            if(q.empty()) throw invaild();
            const auto[w,u]=q.top();q.pop();
            if(x>r[u]) throw invaild();
            ans[u]=x;
            for(auto&i:gr[u]) if((!(--in[i]))&&(!imp[i])) q.emplace(r[i],i);
        }
        return ans;
    }
public:
    auto link(int u,int v){
        gr[u].push_back(v);++in[v];
        rgr[v].push_back(u);++rin[u];
    }
    auto check(vector<int> _r,vector<int> a){
        r=_r;
        vector<int> imp(gr.size());
        cir(i,0,(int)(gr.size())) imp[i]=(bool)(a[i]);
        cir(i,0,(int)(gr.size())) if(!imp[i]) --r[i];
        // for(auto&i:r) clog<<i<<' ';
        // clog<<'\n';
        cir(i,0,(int)(gr.size())) if((!rin[i])&&(!vis[i])) dfs(i);
        return bfs(imp);
    }
    graph(int _n):gr(_n),in(_n),rgr(_n),rin(_n),vis(_n){}
};
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int T;fcin>>T;
    while(T--) []{
        int n,m;fcin>>n>>m;vector<int> a(n);
        for(auto&i:a) fcin>>i;
        vector<int> initr(n,n+1);
        cir(i,0,n) if(a[i]) initr[i]=a[i];
        graph gr(n);
        cir(i,0,m){
            int u,v;fcin>>u>>v;--u;--v;
            gr.link(u,v);
        }
        try{
            const auto ans=gr.check(initr,a);
            copy(ans.begin(),ans.end(),ostream_iterator<int>(fcout," "));
            fcout<<'\n';
        }catch(invaild info){
            fcout<<info.what()<<'\n';
        }
    }();
    return 0;
}
