#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
//平面上的点
struct Point{
    lint x,y,r,c;
    // P 是移动时 x,y 的变化
    Point operator+(const Point&P) const{
        Point res=*this;
        res.x+=P.x;res.y+=P.y;
        return res;
    }
    //在地图内
    bool unout(){return x>=0&&x<r&&y>=0&&y<c;}
};
//当前每一个点的最大收益
//注意除了 1 号剧院，其余为 -∞
VI Ansi;
//剧院
vector<Point> con;
//bfs 里存储的状态
struct nownode{lint x,y,w;};
//r,c 在 mv 中是不重要的，可以为任意值
vector<Point> mv{{1,0,0,0},{-1,0,0,0},{0,1,0,0},{0,-1,0,0}};
vector<VI> mp,w;
vector<vector<VI>> conid;
const lint _inf=1e18+7;
//如果 n>√nm ,则对每一天暴力 bfs 
void bfs(lint r,lint c,lint n,lint st){
    queue<nownode> q;
    deque<nownode> wi(n);
    vector<VI> vis(r,VI(c)),D(r,VI(c,_inf));
    //将每一个剧院的最大收益加入 wi
    //w 设为 -w,转化为最短路
    cir(i,0,n) wi[i]={con[i].x,con[i].y,-Ansi[i]};
    sort(wi.begin(),wi.end(),
        [](nownode&a,nownode&b){return a.w<b.w;});
    q.push(wi.front());wi.pop_front();
    while(wi.front().w==q.front().w)
        q.push(wi.front()),wi.pop_front();
    while(!q.empty()){
        auto f=q.front();q.pop();
        if(vis[f.x][f.y]) continue;
        vis[f.x][f.y]=true;
        D[f.x][f.y]=f.w;
        Point nw={f.x,f.y,r,c};
        for(auto&i:mv){
            //前往...
            auto mvt=nw+i;
            if(!mvt.unout()||!mp[mvt.x][mvt.y]) continue;
            q.push({mvt.x,mvt.y,f.w+1});
            //可以加入更多起点了
            while(!wi.empty()&&f.w+1>=wi.front().w){
                q.push(wi.front());wi.pop_front();
            }
        }
    }
    cir(i,0,n) Ansi[i]=(-D[con[i].x][con[i].y])+w[i][st];
}
//n<=√nm,Θ(rcn) 预处理
vector<VI> init(lint r,lint c,lint n){
    vector<VI> D(n,VI(n,_inf));
    cir(i,0,n){
        queue<nownode> q;
        q.push({con[i].x,con[i].y,0});
        vector<VI> vis(r,VI(c));
        while(!q.empty()){
            auto f=q.front();q.pop();
            if(vis[f.x][f.y]) continue;
            vis[f.x][f.y]=true;
            for(auto&j:conid[f.x][f.y]) D[i][j]=f.w;
            Point nw={f.x,f.y,r,c};
            for(auto&j:mv){
                auto mvt=nw+j;
                if(!mvt.unout()||!mp[mvt.x][mvt.y]) continue;
                q.push({mvt.x,mvt.y,f.w+1});
            }
        }
    }
    return D;
}
lint run(lint r,lint c,lint n,lint m,bool less_n){
    vector<VI> dis;
    if(less_n) dis=init(r,c,n);
    int step=0;
    //滚动数组
    vector<VI> D(2,VI(n,-_inf));
    D[step][0]=0;
    cir(i,0,m){
        step^=1;
        if(!less_n){
            bfs(r,c,n,i);
        }else{
//            x=step (状态)
//            k=step^1
//            //以上方便书写公式
//            枚举剧院 i:
//                Dₓᵢ=Dₖᵢ+今天的收益
//            枚举起始剧院 i
//            枚举结束剧院 j
//            Dₓⱼ=max(Dₓⱼ,Dₖᵢ+今天的收益-disᵢⱼ);
//            Ansi=Dₓ
            cir(j,0,n) D[step][j]=D[step^1][j]+w[j][i];
//            cout<<"(";cir(k,0,n) cout<<'('<<i<<' '<<k<<' '<<w[k][i]<<')';cout<<")\n";
            cir(j,0,n) cir(k,0,n){
                D[step][k]=max(
                    D[step][k],D[step^1][j]+w[k][i]-dis[j][k]);
            }
            Ansi=D[step];
//            for(auto&i:Ansi) cout<<i<<' ';
//            cout<<"\n";
        }
    }
    return *max_element(Ansi.begin(),Ansi.end());
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint r,c,n,m;cin>>r>>c>>n>>m;
    Ansi.resize(n,-_inf);con.resize(n);
    mp.assign(r,VI(c));w.assign(n,VI(m));
    conid.assign(r,vector<VI>(c,VI(0)));
    Ansi[0]=0;
    for(auto&i:mp) for(auto&j:i){
        char c;cin>>c;j=c-'0';
    }
    lint cnt=0;
    for(auto&i:con){
        cin>>i.x>>i.y,--i.x,--i.y;
        conid[i.x][i.y].push_back(cnt);
        ++cnt;
    }
    cir(j,0,m) cir(i,0,n) cin>>w[i][j];
    cout<<run(r,c,n,m,(n<=sqrt(n*m)))<<'\n';
    return 0;
}