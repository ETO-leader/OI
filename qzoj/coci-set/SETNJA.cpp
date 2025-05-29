#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<const int bits>
class bigint{
private:
    vector<int> w;
    void check(){
        auto cur=0ll;
        cir(i,0,bits){
            w[i]+=cur;
            cur=w[i]/10;
            w[i]%=10;
        }
    }
public:
    bigint<bits>&operator*=(int x){
        for(auto&p:w) p*=x;
        check();
        return*this;
    }
    bigint<bits>&operator+=(bigint<bits> x){
        cir(i,0,bits) w[i]+=x.w[i];
        check();
        return*this;
    }
    string str(){
        string res;
        auto prt=w;
        while((int)(prt.size())>1&&(!prt.back())) prt.pop_back();
        reverse(prt.begin(),prt.end());
        for(auto&i:prt) res+=i+'0';
        return res;
    }
    bigint():w(bits){}
    bigint(int x):w(bits){
        w[0]=x;
        check();
    }
};
static constexpr auto maxn=10007;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    const auto n=(int)(s.size());
    auto f=bigint<maxn>(1),c=bigint<maxn>(1);
    cir(i,0,n){
        const auto u=s[i];
        if(u=='*'){
            f*=5;
            f+=c;
            c*=3;
        }else if(u=='L'){
            f*=2;
        }else if(u=='R'){
            f*=2;
            f+=c;
        }
    }
    cout<<f.str()<<'\n';
    return 0;
}
