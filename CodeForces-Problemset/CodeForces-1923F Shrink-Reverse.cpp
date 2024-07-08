#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using ull=unsigned long long;
static constexpr auto MOD=(int)(1e9+7);
class hashing{
private:
    static constexpr auto hashc=251ull;
    vector<ull> pw,h;
    auto init(const string&s){
        pw.resize(s.size()+1,1);
        cir(i,1,(int)(s.size())+1) pw[i]=pw[i-1]*hashc;
        auto hx=0ull;
        for(auto&i:s) h.push_back((hx*=hashc)+=i);
    }
public:
    auto check(int l,int r){
        return h[r]-(l?h[l-1]:0ull)*pw[r-l+1];
    }
    hashing(string s){init(s);}
};
auto norev(string s,int k){
    auto l=0,r=(int)(s.size())-1;
    while(l<r&&k){
        while(l<r&&s[l]=='0') ++l;
        while(l<r&&s[r]=='1') --r;
        if(s[l]!=s[r]) --k,swap(s[l],s[r]);
    }
    reverse(s.begin(),s.end());
    while(s.back()=='0') s.pop_back();
    reverse(s.begin(),s.end());
    return s;
}
auto cgint(const string s){
    auto ans=0ull;
    for(auto&i:s) ((ans<<=1)+=(i-'0'))%=MOD;
    return ans;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;string s;cin>>n>>k>>s;
    const auto nrs=norev(s,k);
    vector<int> pcntz(n),pcnto(n);
    auto cntz=0,cnto=0;--k;
    reverse(s.begin(),s.end());
    hashing sh(s);
    cir(i,0,n){
        pcntz[i]=(cntz+=(s[i]=='0'));
        pcnto[i]=(cnto+=(s[i]=='1'));
    }
    auto rgcnt=[&](int l,int r,vector<int>&p){
        return p[r]-(l?p[l-1]:0);
    };
    auto vaild=[&](int l,int r){
        const auto rgz=rgcnt(l,r,pcntz);
        const auto nrgo=cnto-rgcnt(l,r,pcnto);
        return nrgo-1<rgz&&nrgo<k+1;
    };
    vector<pair<int,int>> q;
    cir(i,0,n){
        auto l=i,r=n-1,ans=-1;
        while(l<r+1){
            const auto mid=(l+r)/2;
            vaild(i,mid)?((ans=mid),(r=mid-1)):(l=mid+1);
        }
        if(ans>-1) q.push_back({i,ans});
    }
    auto cmpstr=[&](int al,int ar,int bl,int br){
        assert(ar-al==br-bl);
        auto l=0,r=ar-al,ans=0;
        while(l<r+1){
            const auto mid=(l+r)/2;
            sh.check(al,al+mid)!=sh.check(bl,bl+mid)?
                ((r=mid-1),(ans=mid)):(l=mid+1);
        }
        return s[al+ans]<s[bl+ans];
    };
    sort(q.begin(),q.end(),[&](auto&a,auto&b){
        const auto[al,ar]=a;
        const auto[bl,br]=b;
        if(ar-al!=br-bl) return ar-al<br-bl;
        return cmpstr(al,ar,bl,br);
    });
    auto[rl,rr]=q.front();
    auto nco=cnto-rgcnt(rl,rr,pcnto);
    auto sans=s.substr(rl,rr-rl+1);
    reverse(sans.begin(),sans.end());
    for(auto&i:sans) if(i=='0'&&nco) i='1',--nco;
    reverse(sans.begin(),sans.end());
    if(nrs.size()==sans.size()) sans=min(sans,nrs);
    else if(nrs.size()<sans.size()) sans=nrs;
    cout<<cgint(sans)<<'\n';
    return 0;
}
