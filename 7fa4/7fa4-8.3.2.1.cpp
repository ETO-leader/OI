#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
using qint=__int128_t;
namespace extint{
    vector<int> pw3;
    bool inited;
    auto init(){
        if(inited) return;
        const auto lim=16;
        pw3.resize(lim,1);
        cir(i,1,lim) pw3[i]=pw3[i-1]*3;
    }
    class tint{
    private:
        int x;
    public:
        operator int(){return static_cast<int>(x);}
        operator size_t(){return static_cast<size_t>(x);}
        operator bool(){return static_cast<bool>(x);}
        auto operator[](size_t p){return (x/pw3[p])%3;}
        auto&operator<<=(const size_t p){
            return x*=pw3[p],*this;
        }
        auto&operator>>=(const size_t p){
            return x/=pw3[p],*this;
        }
        auto operator<<(const size_t p) const{
            return (tint)(*this)<<=p;
        }
        auto operator>>(const size_t p) const{
            return (tint)(*this)>>=p;
        }
        auto operator+=(const tint a){
            return x+=a.x,*this;
        }
        auto operator+(const tint a) const{
            return (tint)(x)+=a;
        }
        auto operator-=(const tint a){
            return x-=a.x,*this;
        }
        auto operator-(const tint a) const{
            return (tint)(x)-=a;
        }
        auto operator*=(const tint a){
            return x*=a.x,*this;
        }
        auto operator*(const tint a) const{
            return (tint)(x)*=a;
        }
        auto operator/=(const tint a){
            return x/=a.x,*this;
        }
        auto operator/(const tint a) const{
            return (tint)(x)/=a;
        }
        auto operator<(const tint a) const{
            return x<a.x;
        }
        auto&operator++(){return ++x,*this;}
        auto&operator--(){return --x,*this;}
        auto str(int cnt){
            string res;
            cir(i,0,cnt) res+=(char)((*this)[i])+'0';
            return res;
        }
        tint(int _x=0):x(_x){init();}
    };
}
using extint::tint;
auto operator""t(const unsigned long long _x){return tint(_x);}
ostream&operator<<(ostream&os,qint x){
    if(x>9) os<<x/10;
    return os<<(int)(x%10);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int m,n;cin>>m>>n;
    if(m==1||n==1) exit((cout<<1<<'\n',0));
    vector f(n,vector(m,vector<qint>(1t<<m)));
    f[0][0][0]=2;
    cir(x,0,n-1) cir(y,0,m) cir(s,0t,(1t<<m)){
        auto lnx=x+(y==m-1),lny=(y+1)%m;
        if(s[y]) f[lnx][lny][s]+=f[x][y][s];
        if(!s[y]){
            cir(p,y+1,m){
                if(s[p]) break;
                auto nx=x+(p==m-1),ny=(p+1)%m;
                f[nx][ny][s+(1t<<y)+(2t<<p)]+=f[x][y][s];
            }
            cir(p,y+1,m){
                if(!s[p]) continue;
                auto nx=x+(p==m-1),ny=(p+1)%m;
                f[nx][ny][s-((tint)(s[p])<<p)+((tint)(s[p])<<y)]+=f[x][y][s];
                break;
            }
        }
        auto fndlf=[&](int p){
            auto cnt=0;
            for(;~p;--p) if(s[p]){
                cnt+=((s[p]==1?-1:1));
                if(!cnt) return p;
            }
            return -1;
        };
        auto fndrg=[&](int p){
            auto cnt=0;
            for(;p<m;++p) if(s[p]){
                cnt+=((s[p]==1?1:-1));
                if(!cnt) return p;
            }
            return -1;
        };
        if(s[y]==1){
            cir(p,y+1,m){
                if(s[p]) break;
                auto nx=x+(p==m-1),ny=(p+1)%m;
                f[nx][ny][s+(1t<<p)-(1t<<y)]+=f[x][y][s];
            }
            cir(p,y+1,m){
                if(!s[p]) continue;
                auto nx=x+(p==m-1),ny=(p+1)%m;
                if(s[p]==2) break;
                const auto ly=fndrg(y),lp=fndrg(p);
                if(ly<0||lp<0) break;
                f[nx][ny][s-(1t<<p)-(1t<<y)-(1t<<lp)]+=f[x][y][s];
                break;
            }
        }
        if(s[y]==2){
            cir(p,y+1,m){
                if(s[p]) break;
                auto nx=x+(p==m-1),ny=(p+1)%m;
                f[nx][ny][s+(2t<<p)-(2t<<y)]+=f[x][y][s];
            }
            cir(p,y+1,m){
                if(!s[p]) continue;
                auto nx=x+(p==m-1),ny=(p+1)%m;
                if(s[p]==1){
                    f[nx][ny][s-(2t<<y)-(1t<<p)]+=f[x][y][s];
                }else{
                    const auto ly=fndlf(y),lp=fndlf(p);
                    if(ly<0||lp<0) break;
                    f[nx][ny][s+(1t<<ly)-(2t<<y)-(2t<<p)]+=f[x][y][s];
                }
                break;
            }
        }
    }
    auto ans=f[n-1][0][1t+(2t<<(m-1))];
    cir(s,0t,(1t<<m)) if(s[0]&&s[m-1]) [&](){
        stack<int> st;
        cir(i,0,m) if(s[i]){
            if(i&&s[i]==1&&st.empty()) return;
            if(st.empty()||(st.top()==1&&s[i]==2)) st.push(s[i]);
            else st.pop();
            if(st.size()>1) return;
        }else if(st.empty()) return;
        ans+=f[n-1][0][s];
    }();
    cout<<ans<<'\n';
    return 0;
}
