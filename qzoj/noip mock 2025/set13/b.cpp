#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class bigint_size_exceeded{};
class bigint:public vector<int>{
private:
    auto ensure(){
        auto w=(int64_t)(0);
        for(auto&i:*this){
            i+=w;
            w=i/10;
            i%=10;
        }
        while(w) this->push_back(w%10),w/=10;
    }
public:
    friend auto operator*(const bigint a,const bigint b){
        auto res=bigint(a.size()+b.size()-1,0);
        cir(i,0,(int)(a.size())) cir(j,0,(int)(b.size())){
            res[i+j]+=a[i]*b[j];
        }
        res.ensure();
        return res;
    }
    friend auto operator<(const bigint a,const bigint b){
        if(a.size()!=b.size()) return a.size()<b.size();
        for(auto i=(int)(a.size())-1;~i;--i){
            if(a[i]!=b[i]) return a[i]<b[i];
        }
        return false;
    }
    static auto pow(bigint a,auto b,int limit){
        auto res=bigint(1);
        while(b){
            if((int)(a.size())>limit) throw bigint_size_exceeded();
            if(b&1) res=res*a;
            a=a*a;b>>=1;
        }
        return res;
    }
    using vector<int>::vector;
    bigint(int val){
        this->resize(1,val);
        this->ensure();
    }
    bigint(string val){
        reverse(val.begin(),val.end());
        this->assign(val.begin(),val.end());
        for(auto&x:*this) x-='0';
        this->ensure();
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,p;string m;cin>>n>>p>>m;
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    auto sgn=1;
    if(m[0]=='-'){
        assert(p&1);
        m.erase(m.begin());
        sgn*=-1;
    }
    const auto v=bigint(m);
    auto l=0,r=(int)(1e9),ans=0;
    while(l-1<r){
        const auto mid=(l+r)/2;
        try{
            const auto nv=bigint::pow(bigint(mid),p,(int)(m.size())+7);
            (nv<v)?l=mid+1:((ans=mid),(r=mid-1));
        }catch(bigint_size_exceeded&){
            ans=mid;r=mid-1;
        }
    }
    if(bigint::pow(bigint(ans),p,(int)(m.size())+7)==v){
        ans*=sgn;
        const auto lc=n/2;
        unordered_map<int,int> lw;
        auto dfsl=[&](auto __self,int p,int w)->void {
            if(p==lc) return ++lw[w],void();
            cir(uw,-50,51) if(uw) __self(__self,p+1,w+uw*uw*uw*a[p]);
        };
        auto dfsr=[&](auto __self,int pos,int w)->int64_t {
            if(pos==n){
                const auto ad=(p==2?(lw.count(-ans-w)?lw[-ans-w]:0):0);
                return ad+((lw.count(ans-w))?lw[ans-w]:0);
            }
            auto res=(int64_t)(0);
            cir(uw,-50,51) if(uw) res+=__self(__self,pos+1,w+uw*uw*uw*a[pos]);
            return res;
        };
        dfsl(dfsl,0,0);
        cout<<dfsr(dfsr,lc,0)<<'\n';
    }else{
        cout<<0<<'\n';
    }
    return 0;
}
