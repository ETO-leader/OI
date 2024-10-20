#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
const auto mx=vector{1,0,-1,0},my=vector{0,1,0,-1};
class movemap{
private:
    vector<vector<array<pair<int,int>,4>>> f;
    vector<vector<array<int,4>>> vis;
    set<pair<int,int>> lf,rg,wl;
    int n,m;
    auto inrange(pair<int,int> nw) const{
        return nw.first>-1&&nw.first<n&&nw.second>-1&&nw.second<m;
    }
    auto vaild(pair<int,int> x) const{
        return inrange(x)&&(!wl.count(x));
    }
    auto nextn(int u,int v,int dir){
        return pair(u+mx[dir],v+my[dir]);
    }
    class invaildsign{};
    auto dfs(int u,int v,int dir){
        if(vis[u][v][dir]==-1) throw invaildsign();
        if(vis[u][v][dir]) return f[u][v][dir];
        vis[u][v][dir]=-1;
        const auto rdir=dir;
        if(lf.count({u,v})) (++dir)%=4;
        if(rg.count({u,v})) (dir+=3)%=4;
        const auto[ux,vx]=nextn(u,v,dir);
        if(vaild({ux,vx})){
            const auto res=dfs(ux,vx,dir);
            vis[u][v][rdir]=1;
            return f[u][v][rdir]=res;
        }
        return vis[u][v][rdir]=1,f[u][v][rdir]={u,v};
    }
public:
    auto insertlr(int u,int v){lf.emplace(u,v);}
    auto insertrr(int u,int v){rg.emplace(u,v);}
    auto insertwl(int u,int v){wl.emplace(u,v);}
    auto init(){
        cir(i,0,n) cir(j,0,m) cir(d,0,4) if(!vis[i][j][d]) try{
            dfs(i,j,d);
        }catch(invaildsign){}
    }
    auto nextpos(int u,int v,int dir){
        return vis[u][v][dir]<0?pair(-1,-1):f[u][v][dir];
    }
    movemap(int _n,int _m):n(_n),m(_m),vis(_n,vector<array<int,4>>(_m)),
        f(_n,vector<array<pair<int,int>,4>>(_m)){}
};
class graph{
private:
    vector<vector<vector<pair<int,int>>>> gr;
    vector<vector<int>> w,inq;
    auto spfa(){
        deque<pair<int,int>> qx,qy;
        vector<tuple<int,int,int>> ax;
        cir(i,0,(int)(w.size())) cir(j,0,(int)(w[i].size())) if(w[i][j]<_inf){
            ax.emplace_back(w[i][j],i,j);inq[i][j]=true;
        }
        sort(ax.begin(),ax.end());
        for(auto&[w,u,v]:ax) qx.emplace_back(u,v);
        while(!(qx.empty()&&qy.empty())){
            auto&nq=(qx.empty()?qy:(qy.empty()?qx:(w[qx.front().first][qx.front().second]<w[qy.front().first][qy.front().second]?qx:qy)));
            const auto[u,v]=nq.front();nq.pop_front();
            inq[u][v]=false;
            for(auto&[ux,vx]:gr[u][v]){
                if(w[u][v]+1>w[ux][vx]-1) continue;
                w[ux][vx]=w[u][v]+1;
                if(!inq[ux][vx]){
                    if(qy.empty()||w[qy.front().first][qy.front().second]<w[u][v]+1) qy.emplace_back(ux,vx);
                    else qy.emplace_front(ux,vx);
                }
                inq[ux][vx]=true;
            }
        }
    }
public:
    auto insert(pair<int,int> u,pair<int,int> v){
        if(min({u.first,u.second,v.first,v.second})<0) return;
        gr[u.first][u.second].push_back(v);
    }
    auto updvalue(pair<int,int> u,int wx){w[u.first][u.second]=wx;}
    auto flush(){
        for(auto&x:w) fill(x.begin(),x.end(),_inf);
    }
    auto init(){spfa();}
    auto value(pair<int,int> u){return w[u.first][u.second];}
    graph(int _n,int _m):gr(_n,vector<vector<pair<int,int>>>(_m)),
        w(_n,vector<int>(_m,_inf)),inq(_n,vector<int>(_m)){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,r;cin>>r>>m>>n;vector<string> str(n);
    for(auto&i:str) cin>>i;
    movemap mp(n,m);
    vector f(r,vector(r,vector(n,vector(m,_inf))));
    cir(i,0,n) cir(j,0,m){
        if(str[i][j]=='x'){
            mp.insertwl(i,j);
        }else if(str[i][j]=='A'){
            mp.insertlr(i,j);
        }else if(str[i][j]=='C'){
            mp.insertrr(i,j);
        }else if(isdigit(str[i][j])){
            const auto id=str[i][j]-'1';
            f[id][id][i][j]=0;
        }
    }
    mp.init();
    graph gr(n,m);
    cir(i,0,n) cir(j,0,m) cir(d,0,4) gr.insert(pair(i,j),mp.nextpos(i,j,d));
    cir(len,1,r+1) cir(lf,0,r-len+1){
        const auto rg=lf+len-1;
        cir(mid,lf,rg) cir(i,0,n) cir(j,0,m){
            f[lf][rg][i][j]=min(f[lf][rg][i][j],f[lf][mid][i][j]+f[mid+1][rg][i][j]);
        }
        gr.flush();
        cir(i,0,n) cir(j,0,m) gr.updvalue(pair(i,j),f[lf][rg][i][j]);
        gr.init();
        cir(i,0,n) cir(j,0,m) f[lf][rg][i][j]=gr.value(pair(i,j));
    }
    auto ans=_inf;
    cir(i,0,n) cir(j,0,m) ans=min(ans,f[0][r-1][i][j]);
    cout<<(ans==_inf?-1:ans)<<'\n';
    return 0;
}
