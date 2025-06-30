#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename _Ty,const size_t len> requires is_unsigned_v<_Ty>
class static_bitset{
private:
    static constexpr auto ulen=numeric_limits<_Ty>::max();
    array<_Ty,len/ulen+7> a;
public:
    auto set(int p){
        a[p/_len]|=((_Ty)(1)<<(p%_len));
    }
    auto count(const auto k) const{
        auto res=0;
        cir(i,0,k/_len) res+=popcount(a[i]);
        res+=popcount(a[i]<<(_len-k%_len-1));
        return res;
    }
    auto operator<<=(const auto k){
        const auto bl=k/_len,v=k-k/_len;
        for(auto i=(int)(a.size());~i;--i){
            a[i]=(a[i-bl]<<k);
            if(i-bl-1<0) break;
            a[i]|=(a[i-bl-1]>>(_len-k))<<(_len-k);
        }
    }
    auto operator&=(const bitset<_Ty,len> x){
        cir(i,0,(int)(a.size())) a[i]&=x.a[i];
    }
    auto operator|=(const bitset<_Ty,len> x){
        cir(i,0,(int)(a.size())) a[i]|=x.a[i];
    }
    static_bitset(){
        memset(a.begin(),0,sizeof(a));
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    
    return 0;
}


