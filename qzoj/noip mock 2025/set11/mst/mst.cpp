#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("mst.in");
ofstream ouf("mst.out");
template<class _Ty,const _Ty c>
class hashbase{
private:
    vector<_Ty> h,pw;
    auto init(vector<_Ty> s){
        auto w=0ll;
        for(auto&i:s) h.emplace_back((w*=c)+=i);
        pw.resize(s.size()+7);
        auto x=(_Ty)(1);
        for(auto&i:pw) i=x,x*=c;
    }
public:
    constexpr auto substr(int l,int r) const{
        return l>r?0:h[r]-(l?h[l-1]:0)*pw[r-l+1];
    }
    hashbase(vector<_Ty> _s){init(_s);}
};
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return u==f[u]?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int c,T;inf>>c>>T;
    while(T--) [c]{
        int n;inf>>n;
        vector<uint64_t> a(n);
        for(auto&x:a) inf>>x;
        hashbase<uint64_t,512251> qwq(a);
        vector<int64_t> w(n/2);
        for(auto&x:w) inf>>x;
        dsu qaq(n);
        if(c<4){
            vector<pair<int,int>> ord;
            cir(i,0,n/2) ord.emplace_back(w[i],i+1);
            sort(ord.begin(),ord.end());
            auto ans=0ll;
            for(auto&[w,k]:ord){
                vector<int> tag(n);
                cir(i,0,n-k*2+1) if(qwq.substr(i,i+k-1)==qwq.substr(i+k,i+k*2-1)){
                    ++tag[i];--tag[i+k];
                }
                cir(i,1,n) tag[i]+=tag[i-1];
                cir(i,0,n) if(tag[i]){
                    if(qaq.findset(i)!=qaq.findset(i+k)){
                        ans+=w;
                        qaq.merge(i,i+k);
                    }
                }
            }
            ouf<<ans<<'\n';
        }else if(c==4){
            vector<pair<int,int>> ord;
            cir(i,0,min(n/2,100)) ord.emplace_back(w[i],i+1);
            sort(ord.begin(),ord.end());
            auto ans=0ll;
            for(auto&[w,k]:ord){
                vector<int> tag(n);
                cir(i,0,n-k*2+1) if(qwq.substr(i,i+k-1)==qwq.substr(i+k,i+k*2-1)){
                    ++tag[i];--tag[i+k];
                }
                cir(i,1,n) tag[i]+=tag[i-1];
                cir(i,0,n) if(tag[i]){
                    if(qaq.findset(i)!=qaq.findset(i+k)){
                        ans+=w;
                        qaq.merge(i,i+k);
                    }
                }
            }
            ouf<<ans<<'\n';
        }else{
            vector<pair<int,int>> ord;
            cir(i,0,min(n/2,4500)) ord.emplace_back(w[i],i+1);
            sort(ord.begin(),ord.end());
            auto ans=0ll;
            for(auto&[w,k]:ord){
                vector<int> tag(n);
                cir(i,0,n-k*2+1) if(qwq.substr(i,i+k-1)==qwq.substr(i+k,i+k*2-1)){
                    ++tag[i];--tag[i+k];
                }
                cir(i,1,n) tag[i]+=tag[i-1];
                cir(i,0,n) if(tag[i]){
                    if(qaq.findset(i)!=qaq.findset(i+k)){
                        ans+=w;
                        qaq.merge(i,i+k);
                    }
                }
            }
            ouf<<ans<<'\n';
        }
    }();
    return 0;
}
