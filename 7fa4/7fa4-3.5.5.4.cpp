#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VB=vector<bool>;
const int _inf=1e9+7;
const vector<int> mx{1,-1,0,0},my{0,0,1,-1};
vector<vector<vector<vector<VB>>>> vis,inst;
struct movement{int wcol,w;};
using VM=vector<movement>;
vector<vector<vector<vector<VM>>>> D;
bool outrange(int x,int y){
    const int n=D[0].size();
    return !(x>=0&&y>=0&&x<n&&y<n);
}
movement dfs(int c,int x,int y,int u,int v){
    if(inst[c][x][y][u][v])
        return {c^1,_inf};
    if(x==u&&y==v) return {c^1,0};
    auto&d=D[c][x][y][u][v];
    if(vis[c][x][y][u][v]) return d;
    inst[c][x][y][u][v]=true;
    int minw=_inf,maxf=0;
    cir(i,0,4) cir(j,0,c+1){
        int nx=x+mx[i]*(j+1),ny=y+my[i]*(j+1);
        if((!c)&&(x==0)&&(y==1)&&(u==1)&&(v==0))
            cout<<nx<<' '<<ny<<'\n';
        if(outrange(nx,ny)) continue;
        auto [w,wx]=dfs(c^1,u,v,nx,ny);
        //if(wx==_inf){
        //    maxf=_inf;continue;
        //}
        if(w==c) minw=min(minw,wx+1);
        else maxf=max(maxf,wx+1);
        if((!c)&&(x==0)&&(y==1)&&(u==1)&&(v==0))
            cout<<u<<' '<<v<<' '<<nx<<' '<<ny<<' '<<w<<' '<<wx<<'\n';//<<' '<<maxf<<'\n';
    }
    vis[c][x][y][u][v]=true;
    inst[c][x][y][u][v]=false;
    assert(minw>0);
    if(minw!=_inf) return d={c,minw};
    if(!maxf) maxf=_inf;
    if((!c)&&(x==1)&&(y==0)&&(u==0)&&(v==1))
        cout<<maxf<<'\n';
    return d={c^1,maxf};
}
template<typename T>
void vector_assign(vector<
    vector<vector<vector<T>>>>&v,int n){
    v.assign(2,vector<vector<vector<T>>>(n,
        vector<vector<T>>(n,vector<T>(n,T(n)))));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,x,y,u,v;cin>>n>>x>>y>>u>>v;
    vector_assign(D,n);vector_assign(vis,n);
    vector_assign(inst,n);
    auto [c,w]=dfs(0,--x,--y,--u,--v);
    if(w>=_inf){
        cout<<"DRAW\n";exit(0);
    }
    cout<<(c?"BLACK":"WHITE")<<' '<<w<<'\n';
    return 0;
}
