#include <iostream>
#include <algorithm>
#include <cstdint>
#include <unordered_set>
using namespace std;

const int N = 1e5;

uint64_t x;

uint64_t f() {
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return x;
}

int main(){
    cin>>x;
    const auto lx=x;
    auto T=0;
    unordered_set<uint64_t> s;
    while(true){
        const auto w=f();
        if(s.count(w)){
            cerr<<w<<' '<<lx<<'\n';break;
        }
        ++T;
        s.emplace(w);
    }
    cout<<"T = "<<T<<'\n';
}

