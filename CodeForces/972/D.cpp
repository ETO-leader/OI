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
        sparsetable sta(a),stb(b);
        vector<pair<int,int>> aw(n);
        vector<int> prea(n),sufa(n),preb(n),sufb(n);
        cir(i,0,n){
            prea[i]=sta.query(0,i-1);
            preb[i]=stb.query(0,i-1);
            sufa[i]=sta.query(i+1,n-1);
            sufb[i]=stb.query(i+1,n-1);
        }
        const auto swpw=[&](int i,int lm){
            return gcd(prea[i],gcd(stb.query(i,lm),sufa[lm]))+
                 gcd(preb[i],gcd(sta.query(i,lm),sufb[lm]));
        };
        auto ans=-1;
        cir(i,0,n){
            auto ansx=pair(-1,-1);
            [&](){
                auto l=i+1,r=max(n-2,i);
                while(r-l+1>5){
                    const auto lm=l+(r-l)/3,rm=l+(r-l)/3*2;
                    const auto lw=swpw(i,lm);
                    const auto rw=swpw(i,rm);
                    lw>rw?r=rm:l=lm;
                }
                cir(p,l,r+1) ansx=max(ansx,pair(swpw(i,p),p));
            }();
            [&](){
                auto l=i+1,r=max(n-2,i);
                while(r-l+1>5){
                    const auto lm=l+(r-l)/3,rm=l+(r-l)/3*2;
                    const auto lw=swpw(i,lm);
                    const auto rw=swpw(i,rm);
                    lw<rw?l=lm:r=rm;
                }
                cir(p,l,r+1) ansx=max(ansx,pair(swpw(i,p),p));
            }();
            ans=max(ans,ansx.first);
            ans=max(ans,swpw(i,n-1));
            ans=max(ans,swpw(i,i));
            aw[i]=ansx;
        }
        auto cnt=0ll;
        auto fl=[&](int i,int p,int lx,int rx){
            auto l=lx,r=min(rx,p),ansr=p+1;
            while(l-1<r){
                const auto mid=midpoint(l,r);
                swpw(i,mid)==ans?((ansr=mid),(r=mid-1)):(l=mid+1);
            }
            return ansr;
        };
        auto fr=[&](int i,int p,int lx,int rx){
            auto l=max(p+1,lx),r=rx,ansr=p;
            while(l-1<r){
                const auto mid=midpoint(l,r);
                swpw(i,mid)==ans?((ansr=mid),(l=mid+1)):(r=mid-1);
            }
            return ansr;
        };
        cir(i,1,n-1){
            const auto[w,p]=aw[i];
            auto lx=i,rx=n-1;
            auto cx=0;
            while((++cx)<20&&lx<rx+1&&swpw(i,lx)==ans) ++lx,++cnt,++cx;
            cx=0;
            while((++cx)<20&&lx<rx+1&&swpw(i,rx)==ans) --rx,++cnt,++cx;
            if(w!=ans||lx>rx) continue;
            cnt+=fr(i,p,lx,rx)-fl(i,p,lx,rx)+1;
        }
        cnt+=(swpw(n-1,n-1)==ans);
        cir(p,0,n) cnt+=(swpw(0,p)==ans);
        cout<<ans<<' '<<cnt<<'\n';
    }();
    return 0;
}
