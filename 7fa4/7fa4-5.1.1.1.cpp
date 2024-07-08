#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
class vector_t{
private:
    static auto get(const vector_t&a,
        const vector_t&b){
        return a+(b*(db)(-1));
    }
public:
    db x,y;
    auto&operator+=(const vector_t&a){
        x+=a.x;y+=a.y;return *this;
    }
    auto operator+(const vector_t&a) const{
        auto res=*this;return res+=a;
    }
    auto operator*(const db a) const{
        return vector_t(a*x,b*x);
    }
    auto dot(const vector_t&a) const{
        return x*a.x+y*a.y;
    }
    auto abs() const{return sqrtl(x*x+y*y);}
    auto angle(const vector_t&a) const{
        return acosl(dot(a)/(abs()*a.abs()));
    }
    auto rotate(){

    }
};
