#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using complf=complex<double>;
static const auto str=(string)(
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
class basic_poly{
private:
    static constexpr auto pi=acosl(-1);
    auto change(vector<complf>&a,const int n){
        vector<int> rev(n);
        cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
        cir(i,0,n) if(i<rev[i]) swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto fft(vector<complf>&a,const int n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            const auto wx=complf(cos(pi*2/h),sin(pi*2*type/h));
            for(auto i=0;i<n;i+=h){
                auto u=complf(1,0);
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*u;
                    a[k+midh]=a[k]-wk;
                    a[k]+=wk;
                    u*=wx;
                }
            }
        }
        if(type==-1){
            for(auto&i:a) i/=n;
        }
    }
public:
    auto mul(const vector<int>&a,const vector<int>&b){
        const auto n=1<<((int)(log2(a.size()+b.size()))+1);
        vector<complf> fx(n);
        cir(i,0,(int)(a.size())) fx[i]+=complf(a[i],0);
        cir(i,0,(int)(b.size())) fx[i]+=complf(0,b[i]);
        fft<1>(fx,n);
        for(auto&i:fx) i*=i;
        fft<-1>(fx,n);
        vector<int> res(n);
        cir(i,0,n) res[i]=floor(fx[i].imag()/2+0.6);
        return res;
    }
} poly;
class bigint{
private:
    int m;
    vector<int> num;
    auto check(int cnt=0){
        for(auto&i:num){
            cnt=(i+=cnt)/m;i%=m;
        }
        while(num.empty()||cnt){
            num.push_back(cnt%m),cnt/=m; 
        }
    }
public:
    auto fit(){
        while(num.size()>1&&(!num.back())) num.pop_back();
    }
    auto&operator+=(const bigint&a){
        while(num.size()<a.num.size()) num.push_back(0);
        cir(i,0,(int)(a.num.size())) num[i]+=a.num[i];
        check();fit();
        return*this;
    }
    auto operator+(const bigint&a) const{
        return bigint(*this)+=a;
    }
    auto&operator*=(const bigint&a){
        num=poly.mul(num,a.num);
        check();fit();
        return*this;
    }
    auto operator*(const bigint&a) const{
        return bigint(*this)*=a;
    }
    auto at(const size_t p){return num[p];}
    auto length(){return num.size();}
    bigint(int _m,int w=0):m(_m){check(w);}
};
ostream&operator<<(ostream&os,bigint a){
    a.fit();
    for(auto i=(int)(a.length()-1);~i;--i)
        os<<str[a.at(i)];
    return os;
}
auto change(vector<int>&a,int l,int r,const int fm,const int m){
    if(l==r) return pair(bigint(m,a[l]),bigint(m,fm));
    const auto mid=(l+r)/2;
    auto[sl,pwl]=change(a,l,mid,fm,m);
    auto[sr,pwr]=change(a,mid+1,r,fm,m);
    return pair(sl+sr*pwl,pwl*pwr);
}
auto change(string s,const int fm,const int m){
    const auto n=(int)(s.size());
    reverse(s.begin(),s.end());
    auto rk=[&](const char c){
        return find(str.begin(),str.end(),c)-str.begin();
    };
    vector<int> ins(n);
    cir(i,0,n) ins[i]=rk(s[i]);
    return change(ins,0,n-1,fm,m).first;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int a,b;cin>>a>>b;
    string s;cin>>s;
    cout<<change(s,a,b)<<'\n';
    return 0;
}
