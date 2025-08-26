#include"ep1.cpp"

static constexpr auto _inf=(int)(1e9+7);

class graph{
private:
    vector<vector<pair<int,int>>> gr;
    auto dijkstra(int s){
        const auto n=(int)(gr.size());
        vector<int> vis(n),dis(n,_inf);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> q;
        dis[s]=0;q.emplace(0,s);
        while(!q.empty()){
            const auto[w,u]=q.top();q.pop();
            if(vis[u]) continue;
            vis[u]=true;
            for(auto&[v,vw]:gr[u]) if(dis[v]>w+vw){
                dis[v]=w+vw;
                q.emplace(w+vw,v);
            }
        }
        return dis;
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w);
    }
    auto sp(const int s){return dijkstra(s);}
    graph(int _n):gr(_n){}
};

int main(){
    auto n=5000;
    cerr<<"QwQ\n";
    mt19937 eng(random_device().operator()());
    vector<int64_t> d(n);
    for(auto&i:d) i=uniform_int_distribution<int>(0,1000000000)(eng);
    graph gr(n);
    sp spqwq(d,0);
    cir(i,0,n) cir(j,0,n) gr.link(i,(i+j)%n,d[j]);
    // assert(spqwq.calc(0,n-1));
    const auto gdis=gr.sp(0);
    auto ans=0ll;
    cir(i,0,n){
        // if(!(i%10000)) cerr<<i<<'\n';
        // ans^=spqwq.calc(i);
        assert(spqwq.calc(i)==gdis[i]);
    }
    // cerr<<ans<<'\n';
}
