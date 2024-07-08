#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
template<typename T>
class matrix{
private:
    vector<T> a;T ini;int p;
public:
    auto&operator[](int x){return a[x];}
    matrix operator*(matrix b)const{
        const int n=a.size();
        matrix res(n,ini,p);
        cir(i,0,n) cir(j,0,n)
            (res[(i+j)%n]+=a[i]*b[j])%=p;
        return res;
    }
    matrix operator^(lint n) const{
        auto res=*this,pw=*this;
        assert((--n)>-1);
        while(n){
            if(n&1){
                res=res*pw;
            }
            pw=pw*pw;n>>=1;
        }
        return res;
    }
    matrix(int n,T init,int m):p(m),
        a(n,init),ini(init){}
};
lint qpow(lint a,lint b,int p){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=p;
        (a*=a)%=p;b>>=1;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,k,p,ans=0;cin>>n>>k>>p;
    cir(i,0,k){
        matrix<lint> f(k,0,p),st(k,0,p);
        cir(x,0,k){
            f[x]+=(!((x*2)%k==i%k));
        }
        st[0]=1;f=st*(f^n);
        (ans+=f[i])%=p;
    }
    cout<<(qpow(k,n,p)-ans+p)%p<<'\n';
    return 0;
}
