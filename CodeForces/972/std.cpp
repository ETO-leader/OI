#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class sparsetable{
private:
    static constexpr auto ups=21;
    vector<vector<int>> a;
    vector<int> lgx;
    auto init(vector<int> x){
        const auto n=(int)(x.size());
        a.resize(ups,vector<int>(n));
        a[0]=x;
        cir(i,1,ups) cir(p,0,n-(1<<i)+1){
            a[i][p]=gcd(a[i-1][p],a[i-1][p+(1<<(i-1))]);
        }
        lgx.resize(n+7);
        cir(i,2,n+7) lgx[i]=lgx[i>>1]+1;
    }
public:
    auto query(int l,int r){
        if(l>r) return 0;
        const auto ql=(int)(lgx[r-l+1]);
        return gcd(a[ql][l],a[ql][r-(1<<ql)+1]);
    }
    sparsetable(vector<int> x){init(x);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        vector<int> a(n),b(n);
        for(auto&i:a) cin>>i;
        for(auto&i:b) cin>>i;
        auto ans=2,cnt=0;
        cir(i,0,n){
            auto ga=0,gb=0;
            cir(p,0,i) ga=gcd(ga,a[p]),gb=gcd(gb,b[p]); 
            cir(j,i,n){
                auto gx=ga,gy=gb;
                cir(p,i,j+1) gx=gcd(gx,b[p]),gy=gcd(gy,a[p]);
                cir(p,j+1,n) gx=gcd(gx,a[p]),gy=gcd(gy,b[p]);
                if(gx+gy==3) clog<<i<<' '<<j<<'\n';
                if(gx+gy>ans) ans=gx+gy,cnt=0; 
                if(gx+gy==ans) ++cnt;
            }
        }
        cout<<ans<<' '<<cnt<<'\n';
    }();
    return 0;
}
