#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class bit2d{
private:
    vector<vector<lint>> a;
    constexpr auto lowbit(auto x) const{return x&(-x);}
    auto query(int x,int y){
        auto res=0ll;
        const int _y=y;
        for(++x;x;x-=lowbit(x)) for(y=_y+1;y;y-=lowbit(y)) res+=a[x][y];
        return res;
    }
public:
    void update(int x,int y,lint w){
        const int _y=y;
        for(++x;x<(int)(a.size());x+=lowbit(x)){
            for(y=_y+1;y<(int)(a[x].size());y+=lowbit(y)) a[x][y]+=w;
        }
    }
    auto query(int x,int y,int u,int v){
        return query(u,v)+query(x-1,y-1)-query(x-1,v)-query(u,y-1);
    }
    bit2d(int _n,int _m):a(_n+1,vector<lint>(_m+1)){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    bit2d qwq(n+7,m+7);
    int op;
    while(cin>>op){
        if(op==1){
            int x,y,w;cin>>x>>y>>w;--x;--y;
            qwq.update(x,y,w);
        }else{
            int a,b,c,d;cin>>a>>b>>c>>d;--a;--b;--c;--d;
            cout<<qwq.query(a,b,c,d)<<'\n';
        }
    }
    return 0;
}
