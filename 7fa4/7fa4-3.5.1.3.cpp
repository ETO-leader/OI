#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define cir(i,a,b)\
    for(auto i=a;int(i)<b;++i)
using namespace std;
using VI=vector<int>;
using VB=vector<bool>;
const int mxp=4099,nx=2,kk=53,mx=6;
array<array<array<array<
    int,mx>,kk>,nx>,mxp> D;
array<array<array<array<
    bool,mx>,kk>,nx>,mxp> vis;
class ternary{
private:
    int p;
    int upx() const{return p>>mx;};
    int px() const{return (p-((p>>mx)<<mx));}
    void init(int x){
        cir(i,0,mx)
            (p|=((x%3)<<(i<<1))),x/=3;
    }
public:
    int operator[](const int x) const{
        return (p>>(x<<1))&3;}
    void setbyte(const int px,const int v){
        p^=(this->operator[](px)<<(
            px<<1))^(v<<(px<<1));
    }
    operator int() const{return p;}
    operator size_t() const{return p;}
    ternary(int x=0):p(0){init(x);}
};
auto count2(ternary&x,int m){
    int res=0;
    cir(i,0,m) res+=(x[i]==2);
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    vector<VI> mp(n,VI(m));
    for(auto&i:mp) for(auto&j:i) cin>>j;
    auto calc=[&](int r,ternary&s){
        int res=0;
        cir(i,0,m) if(s[i]) res+=mp[r][i];
        return res;
    };
    auto _ok=[&](ternary&x){
        bool ok=false;
        cir(i,0,m){
            if(x[i]==2) ok=true;
            if(!x[i]) ok=false;
            if((x[i]==1)&&(!ok)) return false;
        }
        return true;
    };
    const int p3=pow(3,m);
    vector<ternary> ts(p3);
    cir(i,0,p3) ts[i]=ternary(i);
    int stp=0;
    for(auto&i:ts){
        if(count2(i,m)<k+1&&_ok(i)){
            D[i][1][count2(i,m)][0]=calc(0,i);
            vis[i][1][count2(i,m)][0]=true;
        }
    }
    vector<int> cx(mxp);
    for(auto&i:ts) cx[i]=count2(i,m);
    cir(i,1,n){
        stp^=1;
        cir(w,0,k+1) cir(p,0,m){
            for(auto&s:ts){
                auto&d=D[s][stp][w][p];
                if(!vis[s][stp][w][p]) continue;
                if(cx[s]>w) continue;
                //p 不选
                [&](){
                    auto sn=s;sn.setbyte(p,0);
                    auto&dx=D[sn][stp^(p==m-1)
                        ][w][(p+1)%m];
                    vis[sn][stp^(p==m-1)
                        ][w][(p+1)%m]=true;
                    dx=max(dx,d);
                }();
                //p 衔接上一层
                if(s[p]==2) [&](){
                    int px=p,cnx=mp[i][p];
                    while(s[px+1]==1)
                        ++px,cnx+=mp[i][px];
                    auto&dx=D[s][stp^(px==m-1)
                        ][w][(px+1)%m];
                    vis[s][stp^(px==m-1)
                        ][w][(px+1)%m]=true;
                    dx=max(dx,d+cnx);
                }();
                //新建一个矩形
                if(w<k){
                    auto sn=s;sn.setbyte(p,2);
                    int cnx=0;
                    cir(x,p,m){
                        if(x!=p) sn.setbyte(x,1);
                        cnx+=mp[i][x];
                        auto&dx=D[sn][stp^(x==m-1)
                            ][w+1][(x+1)%m];
                        vis[sn][stp^(x==m-1)
                            ][w+1][(x+1)%m]=true;
                        dx=max(dx,d+cnx);
                    }
                }
                d=0;vis[s][stp][w][p]=false;
            }
        }
    }
    int ans=0;
    for(auto&i:ts) cir(w,0,k+1){
        ans=max(ans,D[i][stp^1][w][0]);
    }
    cout<<ans<<'\n';
    return 0;
}