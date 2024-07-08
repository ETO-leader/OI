#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
class bit2d{
private:
    vector<vector<T>> v;
    int n,m;
    int lowbit(int x){return x&(-x);}
    T query(int x,int y){
        T res=0;const int _y=y;
        for(;x;x-=lowbit(x))
            for(y=_y;y;y-=lowbit(y))
                res+=v[x][y];
        return res;
    }
public:
    void additional(int x,int y,T w){
        const int _y=y;
        for(;x<n;x+=lowbit(x))
            for(y=_y;y<m;y+=lowbit(y))
                v[x][y]+=w;
    }
    T operator()(int x,int y,int u,int v){
        return query(u,v)+query(x-1,y-1)-
            query(x-1,v)-query(u,y-1);
    }
    bit2d(int _n,int _m):n(_n+1),
        m(_m+1),v(_n+1,vector<T>(_m+1)){}
};
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    bit2d<lint> b(n,m);
    cir(i,0,n) cir(j,0,m){
        lint w;cin>>w;
        b.additional(i+1,j+1,w);
    }
    cir(i,0,k){
        int t;cin>>t;
        if(t){
            int x,y;lint w;cin>>x>>y>>w;
            b.additional(x,y,w);
        }else{
            int x,y,u,v;cin>>x>>y>>u>>v;
            cout<<b(x,y,u,v)<<'\n';
        }
    }
    return 0;
}
