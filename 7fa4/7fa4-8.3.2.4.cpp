#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
namespace extint{
    class dint{
    private:
        unsigned x;
    public:
        operator int(){return static_cast<int>(x);}
        operator size_t(){return static_cast<size_t>(x);}
        operator bool(){return static_cast<bool>(x);}
        auto operator[](size_t p) const{return (x>>(p<<2))&15;}
        auto&operator<<=(const size_t p){
            return x<<=(p<<2),*this;
        }
        auto&operator>>=(const size_t p){
            return x>>=(p<<2),*this;
        }
        auto operator<<(const size_t p) const{
            return (dint)(*this)<<=p;
        }
        auto operator>>(const size_t p) const{
            return (dint)(*this)>>=p;
        }
        auto&operator+=(const dint a){
            return x+=a.x,*this;
        }
        auto operator+(const dint a) const{
            return (dint)(x)+=a;
        }
        auto&operator-=(const dint a){
            return x-=a.x,*this;
        }
        auto operator-(const dint a) const{
            return (dint)(x)-=a;
        }
        auto&operator*=(const dint a){
            return x*=a.x,*this;
        }
        auto operator*(const dint a) const{
            return (dint)(x)*=a;
        }
        auto&operator/=(const dint a){
            return x/=a.x,*this;
        }
        auto operator/(const dint a) const{
            return (dint)(x)/=a;
        }
        auto operator<(const dint a) const{
            return x<a.x;
        }
        auto&operator++(){return ++x,*this;}
        auto&operator--(){return --x,*this;}
        auto str(int cnt){
            string res;
            cir(i,0,cnt) res+="0123456789ABCDEF"[(*this)[i]];
            return res;
        }
        dint(int _x=0):x(_x){}
    };
}
using extint::dint;
using ulint=unsigned long long;
static constexpr auto _uinf=(ulint)(1e18l);
auto operator""d(const unsigned long long _x){return dint(_x);}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector a(n,vector<int>(m));
    for(auto&x:a) for(auto&i:x) cin>>i;
    vector<vector<int>> cross(n),apr(51);
    set<int> cntcol;
    cir(x,0,n) cir(y,0,m) if(a[x][y]>0){
        cntcol.insert(a[x][y]);
        apr[a[x][y]].push_back(x);
    }
    for(auto&x:apr) sort(x.begin(),x.end());
    for(auto c=-1;auto&x:apr){
        ++c;
        if(x.empty()) continue;
        assert(x.size()==2);
        cir(p,x[0],x[1]+1) cross[p].push_back(c);
    }
    for(auto&x:cross) if(x.size()>6) exit((cout<<"-1\n",0));
    vector f(2,vector(12,unordered_map<int,ulint>()));
    vector c(2,vector(12,unordered_map<int,ulint>()));
    auto stp=0;
    f[stp][0][0]=0;c[stp][0][0]=1;
    auto cmin=[&](auto&a,auto&b,auto c,auto d){
        if(!b) a=c;
        if(a>c) a=c,b=0;
        if(a==c) b+=d;
    };
    auto vaild=[&](dint s){
        auto cntbr=0;
        cir(p,0,m+1){
            if(s[p]==10) ++cntbr;
            if(s[p]==11) --cntbr;
            if(cntbr<0) return false;
        }
        if(cntbr) return false;
        cir(w,7,10){
            auto cntbr=0;
            cir(p,0,m+1){
                cntbr^=(s[p]==w);
            }
            if(cntbr) return false;
        }
        return true;
    };
    if(cntcol.empty()) exit((cout<<"0 1\n",0));
    cir(x,0,n) cir(y,0,m){
        map<int,int> id;
        for(auto c=0;auto&i:cross[x]) id[i]=++c;
        if(x&&(!y)){
            unordered_map<int,ulint> cf;
            unordered_map<int,ulint> cc;
            for(auto&[sx,qwq]:c[stp][0]) [&](){
                auto s=(dint)(sx);
                map<int,int> cnt;
                cir(i,0,m) if((s[i]>6||(s[i]&&(!id.count(cross[x-1][s[i]-1])))&&s[i]<10)){
                    cnt.insert({s[i],0});
                }
                if(cnt.size()>3) return;
                for(auto cx=6;auto&[a,b]:cnt) b=++cx;
                auto ns=0d;
                cir(i,0,m){
                    if(s[i]&&s[i]<7&&id.count(cross[x-1][s[i]-1])) ns+=((dint)(id[cross[x-1][s[i]-1]])<<i);
                    else if(s[i]<10) ns+=((dint)(cnt[s[i]])<<i);
                    else ns+=((dint)(s[i])<<i);
                }
                cmin(cf[ns],cc[ns],f[stp][0][s],c[stp][0][s]);
            }();
            f[stp][0]=cf;
            c[stp][0]=cc;
        }
        for(auto&x:f[stp^1]) x.clear();
        for(auto&x:c[stp^1]) x.clear();
        cir(lf,0,(y?12:1)) for(auto&[sw,qwq]:f[stp][lf]){
            auto s=dint(sw);
            if(s[y]>12) continue;
            auto findlf=[m](dint s,int p){
                auto cnt=0;
                for(;~p;--p){
                    if(s[p]==10) --cnt;
                    if(s[p]==11) ++cnt;
                    if(!cnt) return p;
                }
                return -1;
            };
            auto findrg=[m](dint s,int p){
                auto cnt=0;
                for(;p<m+1;++p){
                    if(s[p]==10) ++cnt;
                    if(s[p]==11) --cnt;
                    if(!cnt) return p;
                }
                return -1;
            };
            auto rgs=s>>y;
            auto lfs=s-(rgs<<y);
            auto fls=lfs+((dint)(lf)<<y)+(rgs<<(y+1));
            if(!vaild(fls)){
                f[stp][lf][s]=_uinf;
                c[stp][lf][s]=0;
                continue;
            }
            if(!a[x][y]){
                if(lf==s[y]) [&](){
                    auto ns=s-((dint)(lf)<<y);
                    if(lf==10){
                        cmin(
                            f[stp^1][0][ns-(1d<<(findrg(fls,y+1)-1))],
                            c[stp^1][0][ns-(1d<<(findrg(fls,y+1)-1))],
                            f[stp][lf][s]+2,
                            c[stp][lf][s]
                        );
                        cmin(
                            f[stp^1][11][ns-(1d<<(findrg(fls,y+1)-1))+(10d<<y)],
                            c[stp^1][11][ns-(1d<<(findrg(fls,y+1)-1))+(10d<<y)],
                            f[stp][lf][s]+4,
                            c[stp][lf][s]
                        );
                        return;
                    }
                    if(lf==11){
                        cmin(
                            f[stp^1][0][ns+(1d<<(findlf(fls,y)))],
                            c[stp^1][0][ns+(1d<<(findlf(fls,y)))],
                            f[stp][lf][s]+2,
                            c[stp][lf][s]
                        );
                        cmin(
                            f[stp^1][11][ns+(1d<<(findlf(fls,y)))+(10d<<y)],
                            c[stp^1][11][ns+(1d<<(findlf(fls,y)))+(10d<<y)],
                            f[stp][lf][s]+4,
                            c[stp][lf][s]
                        );
                        return;
                    }
                    cmin(
                        f[stp^1][0][ns],
                        c[stp^1][0][ns],
                        f[stp][lf][s]+2,
                        c[stp][lf][s]
                    );
                    cmin(
                        f[stp^1][11][ns+(10d<<y)],
                        c[stp^1][11][ns+(10d<<y)],
                        f[stp][lf][s]+4,
                        c[stp][lf][s]
                    );
                }();
                if(lf&&s[y]&&s[y]!=lf){
                    auto ns=s-((dint)(s[y])<<y);
                    cmin(
                        f[stp^1][s[y]][ns+((dint)(lf)<<y)],
                        c[stp^1][s[y]][ns+((dint)(lf)<<y)],
                        f[stp][lf][s]+4,
                        c[stp][lf][s]
                    );
                }
                if(s[y]){
                    auto ns=s-((dint)(s[y])<<y);
                    if(lf==10&&s[y]<10){
                        cmin(
                            f[stp^1][0][ns-((dint)(11-s[y])<<(findrg(fls,y)-1))],
                            c[stp^1][0][ns-((dint)(11-s[y])<<(findrg(fls,y)-1))],
                            f[stp][lf][s]+2,
                            c[stp][lf][s]
                        );
                        cmin(
                            f[stp^1][11][ns-((dint)(11-s[y])<<(findrg(fls,y)-1))+(10d<<y)],
                            c[stp^1][11][ns-((dint)(11-s[y])<<(findrg(fls,y)-1))+(10d<<y)],
                            f[stp][lf][s]+4,
                            c[stp][lf][s]
                        );
                    }
                    if(lf==11&&s[y]<10){
                        cmin(
                            f[stp^1][0][ns-((dint)(10-s[y])<<(findlf(fls,y)))],
                            c[stp^1][0][ns-((dint)(10-s[y])<<(findlf(fls,y)))],
                            f[stp][lf][s]+2,
                            c[stp][lf][s]
                        );
                        cmin(
                            f[stp^1][11][ns-((dint)(10-s[y])<<(findlf(fls,y)))+(10d<<y)],
                            c[stp^1][11][ns-((dint)(10-s[y])<<(findlf(fls,y)))+(10d<<y)],
                            f[stp][lf][s]+4,
                            c[stp][lf][s]
                        );
                    }
                    if(s[y]==10&&lf<10){
                        cmin(
                            f[stp^1][0][ns-((dint)(11-lf)<<(findrg(fls,y+1)-1))],
                            c[stp^1][0][ns-((dint)(11-lf)<<(findrg(fls,y+1)-1))],
                            f[stp][lf][s]+2,
                            c[stp][lf][s]
                        );
                        cmin(
                            f[stp^1][11][ns-((dint)(11-lf)<<(findrg(fls,y+1)-1))+(10d<<y)],
                            c[stp^1][11][ns-((dint)(11-lf)<<(findrg(fls,y+1)-1))+(10d<<y)],
                            f[stp][lf][s]+4,
                            c[stp][lf][s]
                        );
                    }
                    if(s[y]==11&&lf<10){
                        cmin(
                            f[stp^1][0][ns-((dint)(10-lf)<<(findlf(fls,y+1)))],
                            c[stp^1][0][ns-((dint)(10-lf)<<(findlf(fls,y+1)))],
                            f[stp][lf][s]+2,
                            c[stp][lf][s]
                        );
                        cmin(
                            f[stp^1][11][ns-((dint)(10-lf)<<(findlf(fls,y+1)))+(10d<<y)],
                            c[stp^1][11][ns-((dint)(10-lf)<<(findlf(fls,y+1)))+(10d<<y)],
                            f[stp][lf][s]+4,
                            c[stp][lf][s]
                        );
                    }
                }
                if(lf&&(!s[y])){
                    auto ns=s;
                    cmin(
                        f[stp^1][0][ns+((dint)(lf)<<y)],
                        c[stp^1][0][ns+((dint)(lf)<<y)],
                        f[stp][lf][s]+2,
                        c[stp][lf][s]
                    );
                    cmin(
                        f[stp^1][lf][ns],
                        c[stp^1][lf][ns],
                        f[stp][lf][s]+2,
                        c[stp][lf][s]
                    );
                }
                if((!lf)&&s[y]){
                    auto ns=s-((dint)(s[y])<<y);
                    cmin(
                        f[stp^1][0][ns+((dint)(s[y])<<y)],
                        c[stp^1][0][ns+((dint)(s[y])<<y)],
                        f[stp][lf][s]+2,
                        c[stp][lf][s]
                    );
                    cmin(
                        f[stp^1][s[y]][ns],
                        c[stp^1][s[y]][ns],
                        f[stp][lf][s]+2,
                        c[stp][lf][s]
                    );
                }
                if((!lf)&&(!s[y])){
                    auto ns=s;
                    cmin(
                        f[stp^1][11][ns+(10d<<y)],
                        c[stp^1][11][ns+(10d<<y)],
                        f[stp][lf][s]+2,
                        c[stp][lf][s]
                    );
                    cmin(
                        f[stp^1][0][ns],
                        c[stp^1][0][ns],
                        f[stp][lf][s],
                        c[stp][lf][s]
                    );
                }
                if(lf==10&&s[y]==9){
                    auto ns=s-(9d<<y);
                    cmin(
                        f[stp^1][0][ns],
                        c[stp^1][0][ns],
                        f[stp][lf][s]+2,
                        c[stp][lf][s]
                    );
                }
            }
            if(a[x][y]>0){
                const auto ls=a[x][y];
                a[x][y]=id[ls];
                if((!lf)&&(!s[y])){
                    auto ns=s;
                    cmin(
                        f[stp^1][a[x][y]][ns],
                        c[stp^1][a[x][y]][ns],
                        f[stp][lf][s]+1,
                        c[stp][lf][s]
                    );
                    cmin(
                        f[stp^1][0][ns+((dint)(a[x][y])<<y)],
                        c[stp^1][0][ns+((dint)(a[x][y])<<y)],
                        f[stp][lf][s]+1,
                        c[stp][lf][s]
                    );
                }
                if(lf==10&&(!s[y])){
                    auto ns=s;
                    cmin(
                        f[stp^1][0][ns-((dint)(11-a[x][y])<<(findrg(fls,y)-1))],
                        c[stp^1][0][ns-((dint)(11-a[x][y])<<(findrg(fls,y)-1))],
                        f[stp][lf][s]+1,
                        c[stp][lf][s]
                    );
                }
                if(lf==11&&(!s[y])){
                    auto ns=s;
                    cmin(
                        f[stp^1][0][ns-((dint)(10-a[x][y])<<(findlf(fls,y)))],
                        c[stp^1][0][ns-((dint)(10-a[x][y])<<(findlf(fls,y)))],
                        f[stp][lf][s]+1,
                        c[stp][lf][s]
                    );
                }
                if(lf==a[x][y]&&(!s[y])){
                    auto ns=s;
                    cmin(
                        f[stp^1][0][ns],
                        c[stp^1][0][ns],
                        f[stp][lf][s]+1,
                        c[stp][lf][s]
                    );
                }
                if(s[y]==10&&(!lf)){
                    auto ns=s-((dint)(s[y])<<y);
                    cmin(
                        f[stp^1][0][ns-((dint)(11-a[x][y])<<(findrg(fls,y+1)-1))],
                        c[stp^1][0][ns-((dint)(11-a[x][y])<<(findrg(fls,y+1)-1))],
                        f[stp][lf][s]+1,
                        c[stp][lf][s]
                    );
                }
                if(s[y]==11&&(!lf)){
                    auto ns=s-((dint)(s[y])<<y);
                    cmin(
                        f[stp^1][0][ns-((dint)(10-a[x][y])<<(findlf(fls,y+1)))],
                        c[stp^1][0][ns-((dint)(10-a[x][y])<<(findlf(fls,y+1)))],
                        f[stp][lf][s]+1,
                        c[stp][lf][s]
                    );
                }
                if(s[y]==a[x][y]&&(!lf)){
                    auto ns=s-((dint)(s[y])<<y);
                    cmin(
                        f[stp^1][0][ns],
                        c[stp^1][0][ns],
                        f[stp][lf][s]+1,
                        c[stp][lf][s]
                    );
                }
                a[x][y]=ls;
            }
            if(a[x][y]==-1){
                if((!lf)&&(!s[y])){
                    auto ns=s;
                    cmin(
                        f[stp^1][0][ns],
                        c[stp^1][0][ns],
                        f[stp][lf][s],
                        c[stp][lf][s]
                    );
                }
            }
            f[stp][lf][s]=_uinf;
            c[stp][lf][s]=0;
        }
        stp^=1;
    }
    if(!c[stp][0][0]) cout<<"-1\n";
    else cout<<f[stp][0][0]<<' '<<c[stp][0][0]<<'\n';
    return 0;
}
