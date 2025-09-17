#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct node{
    uint64_t hw,hc;
    friend auto operator+(node a,node b){
        auto res=node();
        res.hw=a.hw*b.hc+b.hw;
        res.hc=a.hc*b.hc;
        return res;
    }
    auto&operator=(node a){
        hw=a.hw;hc=a.hc;
        return*this;
    }
    node():hw(0),hc(1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,k;cin>>n>>m>>k;
    vector<string> a(n);
    for(auto&x:a) cin>>x;
    k=min(k,n*m/__gcd(n,m));
    const auto lgk=__lg(k)+1;
    vector<vector<vector<node>>> qwq(n,vector<vector<node>>(m,vector<node>(lgk)));
    cir(i,0,n) cir(j,0,m){
        qwq[i][j][0].hw=a[i][j];
        qwq[i][j][0].hc=251;
    }
    unordered_map<uint64_t,int64_t> cnt;
    auto calc=[&](int dx,int dy){
        cir(x,1,lgk){
            cir(i,0,n) cir(j,0,m){
                const auto u=((i+dx*(1<<(x-1)))%n+n)%n;
                const auto v=((j+dy*(1<<(x-1)))%m+m)%m;
                qwq[i][j][x]=qwq[i][j][x-1]+qwq[u][v][x-1];
            }
        }
        cir(i,0,n) cir(j,0,m){
            auto w=node();
            auto u=i,v=j;
            cir(c,0,lgk) if((k>>c)&1){
                w=w+qwq[u][v][c];
                (((u+=dx*(1<<c))%=n)+=n)%=n;
                (((v+=dy*(1<<c))%=m)+=m)%=m;
            }
            ++cnt[w.hw];
        }
    };
    cir(i,-1,2) cir(j,-1,2) if(i||j) calc(i,j);
    auto ans=(int64_t)(0);
    const auto c=(int64_t)(n)*m*n*m*8*8;
    for(auto&[a,b]:cnt) ans+=b*b;
    const auto g=__gcd(ans,c);
    cout<<ans/g<<'/'<<c/g<<'\n';
    return 0;
}
