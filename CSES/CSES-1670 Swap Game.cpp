#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using MAP=vector<vector<int>>;
struct MapHash{
    static size_t hashing(const MAP&mp){
        size_t res=0;
        for(auto&i:mp) for(auto&j:i) (res*=10)+=j;
        return res;
    }
    inline size_t operator()(const MAP&mp) const{
        return hashing(mp);}
};
unordered_map<MAP,int,MapHash> D;
const size_t ENDTYPE=123456789;
vector<int> mx{1,-1,0,0},my{0,0,1,-1};
inline bool inrange(int x,int y){
    return x>=0&&x<3&&y>=0&&y<3;
}
const int _inf=1e6+7;
int mxa=_inf,val=-1;
int dfs(MAP&mp){
    auto&d=D[mp];
    if((++val)>=mxa) return --val,_inf;;
    if(d) return d;
    if(MapHash::hashing(mp)==ENDTYPE) return mxa=val,--val,d=0;
    int dx=_inf;d=dx;
    cir(x,0,3) cir(y,0,3) cir(i,0,4){
        auto nx=x+mx[i],ny=y+my[i];
        if(inrange(nx,ny)){
            swap(mp[x][y],mp[nx][ny]);
            if(!(D.count(mp)&&D[mp]==_inf)) dx=min(dx,dfs(mp)+1);
            swap(mp[x][y],mp[nx][ny]);
        }
    }
    return --val,d=dx;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    MAP mp(3,vector<int>(3));
    for(auto&i:mp) for(auto&j:i) cin>>j;
    cout<<dfs(mp)<<'\n';
    return 0;
}