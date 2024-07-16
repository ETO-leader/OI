#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
constexpr auto qpow(lint a,lint b,const int MOD){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
constexpr auto inv(lint x,const int MOD){
    return qpow(x,MOD-2,MOD);
}
class bfpolya{
private:
    VI f;int MOD;
public:
    auto&operator[](size_t p){return f[p];}
    bfpolya&operator*=(auto x){
        auto[a,b]=x;
        VI ax(f.size());
        cir(i,0,f.size()-1){
            ax[i+1]=f[i]*a%MOD;
            (f[i]*=b)%=MOD;
        }
        (f.back()*=b)%=MOD;
        cir(i,0,f.size()) (f[i]+=ax[i])%=MOD;
        return*this;
    }
    bfpolya operator*(auto x) const{
        return bfpolya(*this)*=x;
    }
    bfpolya&operator+=(bfpolya x){
        cir(i,0,f.size()) (f[i]+=x[i])%=MOD;
        return*this;
    }
    bfpolya&operator/=(auto x){
        auto[a,b]=x;
        const auto iv=inv(a,MOD);
        bfpolya res(f.size(),MOD);
        for(int i=f.size()-1;i;--i){
            int k=f[i]*iv;res[i-1]=k;
            (((f[i]-=a*k)%=MOD)+=MOD)%=MOD;
            (((f[i-1]-=b*k)%=MOD)+=MOD)%=MOD;
        }
        return (*this)=res;
    }
    bfpolya operator/(auto x) const{
        return bfpolya(*this)/=x;
    }
    bfpolya(int siz,int p):f(siz),MOD(p){}
};
auto polya(auto a,auto b){
    return pair(a,b);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI a(n),b(n);
    cir(i,0,n) a[i]=i,cin>>b[i];
    bfpolya ans(n+1,n),f(n+1,n);f[0]=1;
    cir(i,0,n) f*=polya(1,-a[i]);
    cir(i,0,n){
        const auto c=[&](){
            lint x=1;
            cir(j,0,n) if(i!=j){
                (x*=(a[i]+n-a[j])%n)%=n;
            }
            return inv(x,n);
        }()*b[i]%n;
        ans+=(f/polya(1,-a[i]))*polya(0,c);
    }
    cir(i,0,n) cout<<ans[i]<<' ';
    cout<<'\n';
    return 0;
}
