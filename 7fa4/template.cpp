#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
class random_engine{
private:
	mt19937_64 rnd;
public:
	template<typename _Ty>
	auto randint(auto l,auto r){
		return uniform_int_distribution<_Ty>(l,r)(eng);
	}
	template<typename _Ty>
	auto randreal(auto l,auto r){
		return uniform_real_distribution<_Ty>(l,r)(eng);
	}
	random_engine():rnd(random_device().operator()()){}
};

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);

    return 0;
}
