#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
static constexpr auto _infl=(lint)(1e18l);
template<class comp>
class sparsetable{
private:
    vector<vector<int>> a;
    vector<int> lg;
    static constexpr auto ups=21;
    auto init(vector<int> x){
        a.resize(ups,vector<int>(x.size()));
        a[0]=x;
        lg.resize(x.size()+7,-1);
        const auto n=(int)(x.size());
        cir(i,1,ups) cir(j,0,n-(1<<i)+1){
            a[i][j]=min(a[i-1][j],a[i-1][j+(1<<(i-1))],comp());
        }
        cir(i,1,n+7) lg[i]=lg[i>>1]+1;
    }
public:
    auto query(int l,int r){
        const auto lx=lg[r-l+1];
        return min(a[lx][l],a[lx][r-(1<<lx)+1],comp());
    }
    sparsetable(vector<int> ax){init(ax);}
};
class question1{
public:
    auto check(int n,int k,vector<int>&h){
        auto l=0ll,r=(lint)(2e9l),ans=-1ll;
        while(l-1<r){
            const auto mid=(l+r)/2;
            [&](lint midh){
                auto c=1,mn=_inf,mx=-1;
                cir(i,0,n){
                    mn=min(mn,h[i]);
                    mx=max(mx,h[i]);
                    if(mx-mn>midh){
                        ++c;
                        mx=mn=h[i];
                    }
                }
                return c<k+1;
            }(mid)?((r=mid-1),(ans=mid)):(l=mid+1);
        }
        return ans;
    }
};
class question2{
public:
    auto check(int n,int d,vector<int>&h){
        auto c=1,mn=_inf,mx=-1;
        cir(i,0,n){
            mn=min(mn,h[i]);
            mx=max(mx,h[i]);
            if(mx-mn>d){
                ++c;
                mx=mn=h[i];
            }
        }
        return c;
    }
};
class question3{
public:
    auto check(int n,int k,int d,sparsetable<less<int>>&hl,sparsetable<greater<int>>&hr){
        vector<int> rg(n);
        cir(i,0,n){
            auto l=i,r=n-1,ans=i;
            while(l<r+1){
                const auto mid=(l+r)/2;
                hr.query(i,mid)-hl.query(i,mid)<d+1?
                    ((l=mid+1),(ans=mid)):(r=mid-1);
            }
            rg[i]=ans+1;
        }
        constexpr auto ups=21;
        vector up(ups,vector<int>(n+1));
        up[0]=rg;
        up[0].push_back(n);
        cir(i,0,ups) up[i][n]=n;
        cir(i,1,ups) cir(p,0,n) up[i][p]=up[i-1][up[i-1][p]];
        auto ans=0;
        cir(i,0,n){
            auto px=i;
            cir(x,0,ups) if(k&(1<<x)) px=up[x][px];
            ans=max(ans,px-i);
        }
        return ans;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k,d;cin>>n>>k>>d;
    vector<int> h(n);
    for(auto&i:h) cin>>i;
    const auto ans1=question1().check(n,k,h);
    const auto ans2=question2().check(n,d,h);
    sparsetable<less<int>> hl(h);
    sparsetable<greater<int>> hr(h);
    const auto ans3=question3().check(n,k,d,hl,hr);
    cout<<ans1<<'\n'<<ans2<<'\n'<<ans3<<'\n';
    return 0;
}

