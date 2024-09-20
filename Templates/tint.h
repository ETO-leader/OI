#include<vector>
#include<string>

#pragma system_headers

#ifndef ETOEXTLIB_TINT

#define ETOEXTLIB_TINT 1

#define cir(i,a,b) for(auto i=a;i<b;++i)

namespace extint{
    using lint=long long;
    using qint=__int128_t;
    std::vector<qint> pw3;
    bool inited;
    auto init(){
        if(inited) return;
        const auto lim=58;
        pw3.resize(lim,1);
        cir(i,1,lim) pw3[i]=pw3[i-1]*3;
    }
    template<typename _Ty>
    class ternaryint{
    private:
        _Ty x;
    public:
        operator int(){return static_cast<int>(x);}
        operator long(){return static_cast<long>(x);}
        operator long long(){return static_cast<long long>(x);}
        operator short(){return static_cast<short>(x);}
        operator unsigned int(){return static_cast<unsigned int>(x);}
        operator unsigned long(){return static_cast<unsigned long>(x);}
        operator unsigned long long(){return static_cast<unsigned long long>(x);}
        operator unsigned short(){return static_cast<unsigned short>(x);}
        operator __int128_t(){return static_cast<__int128_t>(x);}
        operator __uint128_t(){return static_cast<__uint128_t>(x);}
        operator bool(){return static_cast<bool>(x);}
        auto operator[](size_t p){return (x/pw3[p])%3;}
        auto&operator<<=(const size_t p){
            return x*=pw3[p],*this;
        }
        auto&operator>>=(const size_t p){
            return x/=pw3[p],*this;
        }
        auto operator<<(const size_t p) const{
            return (ternaryint<_Ty>)(*this)<<=p;
        }
        auto operator>>(const size_t p) const{
            return (ternaryint<_Ty>)(*this)>>=p;
        }
        auto&operator+=(const ternaryint<_Ty> a){
            return x+=a.x,*this;
        }
        auto operator+(const ternaryint<_Ty> a) const{
            return (ternaryint<_Ty>)(x)+=a;
        }
        auto&operator-=(const ternaryint<_Ty> a){
            return x-=a.x,*this;
        }
        auto operator-(const ternaryint<_Ty> a) const{
            return (ternaryint<_Ty>)(x)-=a;
        }
        auto&operator*=(const ternaryint<_Ty> a){
            return x*=a.x,*this;
        }
        auto operator*(const ternaryint<_Ty> a) const{
            return (ternaryint<_Ty>)(x)*=a;
        }
        auto&operator/=(const ternaryint<_Ty> a){
            return x/=a.x,*this;
        }
        auto operator/(const ternaryint<_Ty> a) const{
            return (ternaryint<_Ty>)(x)/=a;
        }
        auto&operator%=(const ternaryint<_Ty> a){
            return x%=a.x,*this;
        }
        auto operator%(const ternaryint<_Ty> a) const{
            return (ternaryint<_Ty>)(x)%=a;
        }
        auto operator<(const ternaryint<_Ty> a) const{
            return x<a.x;
        }
        auto operator>(const ternaryint<_Ty> a) const{
            return x>a.x;
        }
        auto operator==(const ternaryint<_Ty> a) const{
            return x==a.x;
        }
        auto operator<=(const ternaryint<_Ty> a) const{
            return x<=a.x;
        }
        auto operator>=(const ternaryint<_Ty> a) const{
            return x>=a.x;
        }
        auto operator!=(const ternaryint<_Ty> a) const{
            return x!=a.x;
        }
        auto&operator+=(const auto a){
            return x+=a,*this;
        }
        auto operator+(const auto a) const{
            return (ternaryint<_Ty>)(x)+=a;
        }
        auto&operator-=(const auto a){
            return x-=a,*this;
        }
        auto operator-(const auto a) const{
            return (ternaryint<_Ty>)(x)-=a;
        }
        auto&operator*=(const auto a){
            return x*=a,*this;
        }
        auto operator*(const auto a) const{
            return (ternaryint<_Ty>)(x)*=a;
        }
        auto&operator/=(const auto a){
            return x/=a,*this;
        }
        auto operator/(const auto a) const{
            return (ternaryint<_Ty>)(x)/=a;
        }
        auto&operator%=(const auto a){
            return x%=a,*this;
        }
        auto operator%(const auto a) const{
            return (ternaryint<_Ty>)(x)%=a;
        }
        auto operator<(const auto a) const{
            return x<a;
        }
        auto operator>(const auto a) const{
            return x>a;
        }
        auto operator==(const auto a) const{
            return x==a;
        }
        auto operator<=(const auto a) const{
            return x<=a;
        }
        auto operator>=(const auto a) const{
            return x>=a;
        }
        auto operator!=(const auto a) const{
            return x!=a;
        }
        auto&operator++(){return ++x,*this;}
        auto&operator--(){return --x,*this;}
        auto str(int cnt){
            std::string res;
            cir(i,0,cnt) res+=(char)((*this)[i])+'0';
            return res;
        }
        ternaryint(int _x=0):x(_x){init();}
    };
}

#ifndef NO_USING_TERNARY_TYPE

using tint16_t=extint::ternaryint<int16_t>;
using utint16_t=extint::ternaryint<u_int16_t>;
using tint32_t=extint::ternaryint<int32_t>;
using utint32_t=extint::ternaryint<u_int32_t>;
using tint64_t=extint::ternaryint<int64_t>;
using utint64_t=extint::ternaryint<u_int64_t>;
using tint128_t=extint::ternaryint<__int128_t>;
using utint128_t=extint::ternaryint<__uint128_t>;

using tint=tint32_t;
using utint=utint32_t;

auto operator""ts(const unsigned long long _x){return tint16_t(_x);}
auto operator""uts(const unsigned long long _x){return utint16_t(_x);}
auto operator""t(const unsigned long long _x){return tint32_t(_x);}
auto operator""ut(const unsigned long long _x){return utint32_t(_x);}
auto operator""tl(const unsigned long long _x){return tint64_t(_x);}
auto operator""utl(const unsigned long long _x){return utint64_t(_x);}
auto operator""tq(const unsigned long long _x){return tint128_t(_x);}
auto operator""utq(const unsigned long long _x){return utint128_t(_x);}

#endif

#undef cir

#endif
