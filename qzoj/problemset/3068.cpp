#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
template<const int n>
class matrix:public array<array<lint,n>,n>{
public:
    auto operator*(const matrix x) const{
        auto res=matrix();
        cir(k,0,n) cir(i,0,n) cir(j,0,n) (res[i][j]+=(*this)[i][k]*x[k][j])%=MOD; 
        return res;
    }
    auto pow(lint k){
        auto res=matrix(1),pw=*this;
        while(k){
            if(k&1) res=res*pw;
            pw=pw*pw;k>>=1;
        }
        return res;
    }
    matrix(lint _v=0){
        for(auto&x:*this) for(auto&i:x) i=0;
        cir(i,0,n) (*this)[i][i]=_v;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint n;
    while(cin>>n) [&]{
        matrix<16> f;
        auto transfer=[&](int a,int b,int x,int y,string note){
            ++f[(a<<2)|b][((x-1)<<2)|(y-1)];
        };

        // Type "O"
        transfer(0,0,2,2,R"(
            ..
            ..
            ##
            ##
            ..
            ##
        )");

        // Type "J"
        transfer(0,0,1,3,R"(
            ..
            .#
            .#
            ##
            ..
            ##
        )");
        transfer(0,2,3,3,R"(
            ..
            ##
            #.
            ##
            .#
            ##
        )");

        // Type "L"
        transfer(0,0,3,1,R"(
            ..
            #.
            #.
            ##
            ..
            ##
        )");
        transfer(2,0,3,3,R"(
            ..
            ##
            .#
            ##
            #.
            ##
        )");
        
        // Type "I" x2
        transfer(0,0,4,4,R"(
            ##
            ##
            ##
            ##
            ..
            ##
        )");

        // Type "I"
        transfer(0,1,4,1,R"(
            #.
            #.
            #.
            #.
            .#
            ##
        )");
        transfer(0,2,4,2,R"(
            #.
            #.
            #.
            ##
            .#
            ##
        )");
        transfer(0,3,4,3,R"(
            #.
            #.
            ##
            ##
            .#
            ##
        )");
        transfer(1,0,1,4,R"(
            .#
            .#
            .#
            .#
            #.
            ##
        )");
        transfer(2,0,2,4,R"(
            .#
            .#
            .#
            ##
            #.
            ##
        )");
        transfer(3,0,3,4,R"(
            .#
            .#
            ##
            ##
            #.
            ##
        )");
        
        // Type "Z"
        transfer(0,1,2,3,R"(
            ..
            .#
            ##
            #.
            .#
            ##
        )");

        // Type "S"
        transfer(1,0,3,2,R"(
            ..
            #.
            ##
            .#
            #.
            ##
        )");

        // Type "T"
        transfer(0,1,3,2,R"(
            ..
            #.
            ##
            #.
            .#
            ##
        )");
        transfer(1,0,2,3,R"(
            ..
            .#
            ##
            .#
            #.
            ##
        )");

        cir(i,1,4) cir(j,1,4){
            transfer(i,j,i,j,R"(
                No Comment.
            )");
        }

        cout<<f.pow(n)[0][0]<<'\n';
    }();
    return 0;
}
