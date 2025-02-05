#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("wind.in");
ofstream ouf("wind.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
using qint=__int128_t;
static constexpr auto _infs=(lint)(3e13l);
static constexpr auto _infl=(lint)(4e18l);
auto&operator>>(istream&is,qint&x){
    string s;is>>s;x=0;auto sgn=1;
    if(s[0]=='-') sgn=-sgn,s.erase(s.begin());
    for(auto&w:s) (x*=10)+=(w-'0');
    x*=sgn;
    return is;
}
constexpr auto abs(qint x){return x<0?-x:x;}
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int T;inf>>T;
    while(T--) [&]{
        int n;qint k,x,y;inf>>n>>k>>x>>y;
        vector<qint> a(n),b(n);
        cir(i,0,n) inf>>a[i]>>b[i];
        // |\sum a - X| + |\sum b - Y| \le mK
        // X + Y - \sum (a + b + K) \le 0
        // X - Y - \sum (a - b + K) \le 0
        // - X + Y - \sum (- a + b + K) \le 0
        // - X - Y - \sum (- a - b + K) \le 0
        auto chkl=[&](qint w,qint v){
            if(w<0) return 0ll;
            return v<1?_infs+1:(lint)((w+v-1)/v);
        };
        auto chkr=[&](qint w,qint v){
            if(v>0) return _infs;
            if(w>0) return -1ll;
            if(!v) return _infs;
            return (lint)((-w)/(-v));
        };
        auto check=[&](qint w,qint v){
            // w - v * x \le 0
            return make_pair(chkl(w,v),chkr(w,v));
        };
        auto cap=[&](auto a,auto b){return make_pair(max(a.first,b.first),min(a.second,b.second));};
        auto ans=_infl;
        const auto suma=accumulate(a.begin(),a.end(),(qint)(0));
        const auto sumb=accumulate(b.begin(),b.end(),(qint)(0));
        if(!k){
            auto prea=(qint)(0),preb=(qint)(0);
            cir(i,0,n){
                if((!suma)||(!sumb)){
                    if(prea==x&&preb==y) ans=min(ans,(lint)(i));
                }else{
                    if((!(abs(x-prea)%abs(suma)))&&(!(abs(y-preb)%abs(sumb)))){
                        if((x-prea)/suma==(y-preb)/sumb&&(x-prea)/suma>-1) ans=min(ans,(lint)((x-prea)/suma*n+i));
                    }
                }
                prea+=a[i];preb+=b[i];
            }
        }
        auto vaild=[&](const auto cx,const auto cy,const auto w){
            if(!k) return !(abs(cx-x)+abs(cy-y));
            return (abs(cx-x)+abs(cy-y)+k-1)/k<w+1;
        };
        auto checkw=[&](const auto c){
            auto prea=(qint)(0),preb=(qint)(0);
            cir(i,0,n) if(vaild(suma*c+prea,sumb*c+preb,(lint)(c)*n+i)){
                ans=min(ans,(lint)(c)*n+i);
                return true;
            }else{
                prea+=a[i];preb+=b[i];
            }
            return false;
        };
        checkw(0);
        auto prea=(qint)(0),preb=(qint)(0);
        cir(i,0,n){
            const auto result=cap(
                cap(
                    check(x+y-(prea+preb+i*k),suma+sumb+n*k),
                    check(x-y-(prea-preb+i*k),suma-sumb+n*k)
                ),
                cap(
                    check(-x+y-(-prea+preb+i*k),-suma+sumb+n*k),
                    check(-x-y-(-prea-preb+i*k),-suma-sumb+n*k)
                )
            );
            prea+=a[i];preb+=b[i];
            if(result.first<result.second+1) ans=min(ans,result.first*n+i);
        }
        ouf<<(ans==_infl?-1:ans)<<'\n';
    }();
    return 0;
}
