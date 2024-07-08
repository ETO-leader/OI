#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<const size_t bitnum=(1ul<<17)>
class longerint{
private:
    bitset<bitnum> a,alx;
    size_t step;
public:
    auto&operator--(){
        const auto p=a._Find_first();
        a|=alx>>(bitnum-p);a.set(p,0);
        return*this;
    }
    auto&operator++(){
        const auto p=(a^alx)._Find_first();
        a^=(alx>>(bitnum-p));a.set(p,1);
        return*this;
    }
    auto&operator<<=(const size_t num){
        step+=num;
        a<<=num;return*this;
    }
    auto&operator>>=(const size_t num){
        step-=num;
        a>>=num;return*this;
    }
    operator bool() const{return (bool)(step);}
    auto calc(const longerint&ax,const int maxnum) const{
        auto res=0;bool rev=false;
        for(int i=step;~i;--i){
            (res*=2);
            if(a[i]^ax.a[i]){
                if(!res){
                    res=1;
                    if(ax.a[i]) rev=true;
                }else if(rev){
                    res+=(int)(ax.a[i])-a[i];
                }else{
                    res+=(int)(a[i])-ax.a[i];
                }
            }
            if(abs(res)>maxnum) return abs(res);
        }
        return abs(res);
    }
    auto highbit() const{return step;}
    longerint():step(0){alx.set();}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string a,b;cin>>a>>b;
    longerint ap,bp;
    for(auto&c:a){
        if(c=='1') ap<<=1;
        if(c=='2') ++(ap<<=1);
        if(c=='U') ap>>=1;
        if(c=='L') --ap;
        if(c=='R') ++ap;
    }
    for(auto&c:b){
        if(c=='1') bp<<=1;
        if(c=='2') ++(bp<<=1);
        if(c=='U') bp>>=1;
        if(c=='L') --bp;
        if(c=='R') ++bp;
    }
    if(bp.highbit()>ap.highbit()) swap(ap,bp);
    auto basicans=ap.highbit()-bp.highbit();
    ap>>=(basicans);
    auto ans=50000000,cnt=0;
    while(ap){
        const auto ci=ap.calc(bp,300000);
        if(ci<300000){ 
            if(ci+cnt-100>ans) break;
            ans=min(ans,ci+cnt);
            if(!ci) break;
        }
        ap>>=1;bp>>=1;cnt+=2;
    }
    cout<<ans+basicans<<'\n';
    return 0;
}
