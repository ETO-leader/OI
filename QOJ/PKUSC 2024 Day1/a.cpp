#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class hashbase{
private:
    vector<uint64_t> a,ra,pw;
    static constexpr auto hc=251ull;
    auto init(string s){
        auto h=0ull;
        for(auto&i:s) a.emplace_back((h*=hc)+=i);
        ra.emplace_back(h=0);
        for(auto&i:views::reverse(s)) ra.emplace_back((h*=hc)+=i);
        ranges::reverse(ra);
        pw.resize(s.size()+7,1);
        cir(i,1,(int)(s.size())+7) pw[i]=pw[i-1]*hc;
    }
public:
    auto substr(int l,int r){
        return a[r]-(l?a[l-1]:0)*pw[r-l+1];
    }
    auto rsubstr(int l,int r){
        return ra[l]-ra[r+1]*pw[r-l+1];
    }
    hashbase(string s){init(s);}
};
auto change(string&s){
    auto res=(string)("#");
    for(auto&i:s) (res+=i)+='#';
    s=res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<string> s(2);
    cin>>s[0]>>s[1];
    for(auto&x:s) change(x);
    vector hx{hashbase(s[0]),hashbase(s[1])};
    vector ax(2,vector<int>(n*2+1));
    cir(i,0,2) cir(p,0,n*2+1){
        auto l=1,r=min(n*2+1-p,p+1),ans=1;
        while(l-1<r){
            const auto mid=(l+r)/2;
            hx[i].substr(p-mid+1,p+mid-1)==hx[i].rsubstr(p-mid+1,p+mid-1)?
                ((l=mid+1),(ans=mid)):(r=mid-1);
        }
        ax[i][p]=ans;
    }
    auto ans=0;
    cir(i,0,2) cir(j,1,n*2+1) ans=max(ans,ax[i][j]-1);
    cir(p,0,n*2+1){
        auto lp=p-ax[0][p]+1,rp=p+ax[0][p]-1;
        if(lp==rp) continue;
        if(!lp) continue;
        ++lp;--rp;
        auto l=2,r=min(lp,n*2+2-rp),answ=1;
        while(l-1<r){
            const auto mid=(l+r)/2;
            hx[0].substr(lp-mid,lp-2)==hx[1].rsubstr(rp,rp+mid-2)?
                ((l=mid+1),(answ=mid)):(r=mid-1);
        }
        ans=max(ans,ax[0][p]+answ-2);
    }
    cir(p,0,n*2+1){
        auto lp=p-ax[1][p]+1,rp=p+ax[1][p]-1;
        if(lp==rp) continue;
        if(rp==n*2+1) continue;
        ++lp;--rp;
        auto l=2,r=min(lp+2,n*2-rp),answ=1;
        while(l-1<r){
            const auto mid=(l+r)/2;
            hx[0].substr(lp-mid+2,lp)==hx[1].rsubstr(rp+2,rp+mid)?
                ((l=mid+1),(answ=mid)):(r=mid-1);
        }
        ans=max(ans,ax[1][p]+answ-2);
    }
    cir(p,0,n*2+1) if((p&1)&&(s[0][p]==s[1][p])){
        auto l=1,r=min(n*2+1-p,p+1),answ=1;
        while(l-1<r){
            const auto mid=(l+r)/2;
            hx[0].substr(p-mid+1,p)==hx[1].rsubstr(p,p+mid-1)?
                ((l=mid+1),(answ=mid)):(r=mid-1);
        }
        ans=max(ans,answ);
    }
    println("{}",ans);
    return 0;
}
