#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)

#ifndef _MODINT_H

#define _MODINT_H 1

#include<iostream>

template<typename basic_type,basic_type mod>
class mod_integer_reader;

template<typename basic_type,basic_type mod>
class mod_integer_printer;

template<class basic_type,basic_type mod>
class mod_integer{
private:
    basic_type num;
    template<typename _Ty>
    static _Ty pow_type(_Ty a,size_t pw){
        _Ty res=1;
        while(pw){
            if(pw&1) (res*=a)%=mod;
            (a*=a)%=mod;pw>>=1;
        }
        return res;
    }
    template<typename _Ty>
    static _Ty inv_type(_Ty a){
        return pow_type(a,mod-2);
    }
public:
    operator bool() const{
        return static_cast<bool>(num);
    }
    operator int() const{
        return static_cast<int>(num);
    }
    operator long() const{
        return static_cast<long>(num);
    }
    operator unsigned() const{
        return static_cast<unsigned>(num);
    }
    operator char() const{
        return static_cast<char>(num);
    }
    mod_integer&operator+=(const mod_integer<basic_type,mod> x){
        (num+=x.num)%=mod;
        return *this;
    }
    template<typename _Ty>
    mod_integer&operator+=(const _Ty x){
        (num+=x)%=mod;
        return *this;
    }
    template<typename _Ty>
    mod_integer operator+(const _Ty x) const{
        auto res=*this;
        return res+=x;
    }
    mod_integer&operator*=(const mod_integer<basic_type,mod> x){
        (num*=x.num)%=mod;
        return *this;
    }
    template<typename _Ty>
    mod_integer&operator*=(const _Ty x){
        (num*=x)%=mod;
        return *this;
    }
    template<typename _Ty>
    mod_integer operator*(const _Ty x) const{
        auto res=*this;
        return res*=x;
    }
    mod_integer&operator-=(const mod_integer<basic_type,mod> x){
        (num+=mod-x.num)%=mod;
        return *this;
    }
    template<typename _Ty>
    mod_integer&operator-=(const _Ty x){
        (num+=mod-x)%=mod;
        return *this;
    }
    template<typename _Ty>
    mod_integer operator-(const _Ty x) const{
        auto res=*this;
        return res-=x;
    }
    mod_integer pow(size_t pw) const{
        mod_integer<basic_type,mod> res(1);
        auto a=*this;
        while(pw){
            if(pw&1) res*=a;
            a*=a;pw>>=1;
        }
        return res;
    }
    mod_integer inv() const{
        return pow(mod-2);
    }
    mod_integer&operator/=(const mod_integer<basic_type,mod> x){
        return (*this)*=x.inv();
    }
    mod_integer operator/(const mod_integer<basic_type,mod> x) const{
        auto res=*this;
        return res/=x;
    }
    template<typename _Ty>
    mod_integer&operator/=(const _Ty x){
        return (*this)*=inv_type(x*1ll);
    }
    template<typename _Ty>
    mod_integer operator/(const _Ty x) const{
        auto res=*this;
        return res/=x;
    }
    mod_integer&operator<<=(const size_t x){
        return (*this)*=pow_type(2ll,x);
    }
    mod_integer operator<<(const size_t x) const{
        auto res=*this;
        return res<<=x;
    }
    mod_integer&operator>>=(const size_t x){
        num>>=x;
        return *this;
    }
    mod_integer operator>>(const size_t x){
        auto res=*this;
        return res>>=x;
    }
    bool operator<(const mod_integer<basic_type,mod> x) const{
        return num<x.num;
    }
    bool operator==(const mod_integer<basic_type,mod> x) const{
        return num==x.num;
    }
    bool operator>(const mod_integer<basic_type,mod> x) const{
        return num>x.num;
    }
    bool operator!=(const mod_integer<basic_type,mod> x) const{
        return num!=x.num;
    }
    bool operator<=(const mod_integer<basic_type,mod> x) const{
        return num<=x.num;
    }
    bool operator>=(const mod_integer<basic_type,mod> x) const{
        return num>=x.num;
    }
    template<typename _Ty>
    bool operator<(const _Ty x) const{
        return num<x;
    }
    template<typename _Ty>
    bool operator==(const _Ty x) const{
        return num==x;
    }
    template<typename _Ty>
    bool operator>(const _Ty x) const{
        return num>x;
    }
    template<typename _Ty>
    bool operator!=(const _Ty x) const{
        return num!=x;
    }
    template<typename _Ty>
    bool operator<=(const _Ty x) const{
        return num<=x;
    }
    template<typename _Ty>
    bool operator>=(const _Ty x) const{
        return num>=x;
    }
    mod_integer&operator=(const mod_integer<basic_type,mod> x){
        num=x.num;
        return *this;
    }
    template<typename _Ty>
    mod_integer&operator=(const _Ty x){
        num=x%mod;
        return *this;
    }
    friend class mod_integer_reader<basic_type,mod>;
    friend class mod_integer_printer<basic_type,mod>;
    mod_integer(basic_type x):num(x){}
    mod_integer(mod_integer<basic_type,mod>&x):num(x.num){}
    mod_integer(){num=0;}
};

template<typename basic_type,basic_type mod>
class mod_integer_reader{
public:
    static void read(std::istream&is,mod_integer<basic_type,mod>&x){
        is>>x.num;x.num%=mod;
    }
};

template<typename basic_type,basic_type mod>
class mod_integer_printer{
public:
    static void print(std::ostream&os,mod_integer<basic_type,mod>&x){
        os<<x.num;
    }
};

template<typename basic_type,basic_type mod>
std::istream&operator>>(std::istream&is,mod_integer<basic_type,mod>&x){
    mod_integer_reader<basic_type,mod>::read(is,x);
    return is;
}

template<typename basic_type,basic_type mod>
std::ostream&operator<<(std::ostream&os,mod_integer<basic_type,mod> x){
    mod_integer_printer<basic_type,mod>::print(os,x);
    return os;
}

template<int mod>
using modint=mod_integer<int,mod>;

template<long mod>
using modlong=mod_integer<long,mod>;

template<short mod>
using modshort=mod_integer<short,mod>;

#endif// _MODINT_H

using namespace std;
ifstream fcin("circle.in");
ofstream fcout("circle.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
static constexpr int MOD=1e9+7;
using mlong=modlong<MOD>;
using VI=vector<mlong>;
auto limited(mlong n){
    return n*(n+1)/2;
}
auto unlimited(mlong n){
    return (n*n-1)*n/6;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;fcin>>n;VI a(n);
    for(auto&i:a) fcin>>i;
    vector<vector<VI>> D(2,
        vector<VI>(2,VI(2)));
    cir(i,0,2) D[i][0][0]=D[i][1][1]=1;
    cir(i,0,n) cir(x,0,2) cir(nx,0,2){
        auto t00=limited(a[i]-x),t10=(a[i]+1-x);
        auto t01=unlimited(a[i]),t11=limited(a[i]);
        auto cp=D[x][nx];
        D[x][nx][0]=t00*cp[0]+t10*cp[1];
        D[x][nx][1]=t01*cp[0]+t11*cp[1];
    }
    fcout<<(D[0][0][0]+D[0][1][1]-
        D[1][0][0]-D[1][1][1])<<'\n';
    return 0;
}
