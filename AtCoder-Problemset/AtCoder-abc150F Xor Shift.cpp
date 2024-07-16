#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using ulint=unsigned long long;
template<typename _Ty>
class hash{
private:
    static constexpr auto hc=251ull;
    vector<ulint> hx,pw;
    auto init(const _Ty s){
        auto h=0ull;
        pw.resize(s.size()+7,1);
        cir(i,1,(int)(pw.size())) pw[i]=pw[i-1]*hc;
        for(auto&i:s) hx.push_back((h*=hc)+=i);
    }
public:
    auto substr(int l,int r) const{
        return hx[r]-(l?hx[l-1]:0ull)*pw[r-l+1];
    }
    auto result() const{return hx.back();}
    hash(_Ty s){init(s);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;basic_string a(n,0),b(n,0);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    a+=a;
    auto bitarr=[&](basic_string<int>&x,int bx){
        basic_string<int> res;
        for(auto&i:x) res+=((i>>bx)&1);
        return res;
    };
    auto rev=[&](basic_string<int> x){
        return valarray<int>(x.data(),x.size())^=1;
    };
    vector<ulint> bx(30);
    cir(i,0,30) bx[i]=::hash(bitarr(b,i)).result();
    map<int,int> ans;
    cir(i,0,n) ans.insert({i,0});
    for(auto i=29;~i;--i){
        const auto ar=bitarr(a,i);
        const auto rar=rev(ar);
        const auto har=::hash(ar);
        const auto hrar=::hash(rar);
        unordered_set<int> ax;
        for(auto&[x,y]:ans) ax.insert(x);
        cir(x,0,n) if(har.substr(x,x+n-1)==bx[i]){
            if(ax.count(x)) ax.erase(x);
        }
        cir(x,0,n) if(hrar.substr(x,x+n-1)==bx[i]){
            if(ax.count(x)){
                ax.erase(x);
                ans[x]^=(1<<i);
            }
        }
        for(auto&i:ax) ans.erase(i);
    }
    for(auto&[a,b]:ans) cout<<a<<' '<<b<<'\n';
    return 0;
}
