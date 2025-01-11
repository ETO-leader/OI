#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;

class Int{
private:
    uint64_t num;
    constexpr auto checkOverflow(const char op_type) const{
        if(num>numeric_limits<uint32_t>::max())
            quitf(_wa,"Overflowed in operator '%c'.\n",op_type);
    }
public:
    auto operator+(const Int x){
        auto res=*this;
        res.num+=x.num;
        res.checkOverflow('+');
        return res;
    }
    auto operator*(const Int x){
        auto res=*this;
        res.num*=x.num;
        res.checkOverflow('*');
        return res;
    }
    auto operator-(const Int x){
        
    }
};

class Node{

};

class Edge{
public:
    int v;
    int delay;
};
