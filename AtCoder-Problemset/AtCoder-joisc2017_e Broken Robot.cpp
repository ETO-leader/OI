#include"Broken_device_lib.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

using random_engine=mt19937_64;
using randint=uniform_int_distribution<int>;
static constexpr auto _seed='MikeMirzayanov';

void Anna(int N,long long X,int K,int P[]){
    random_engine eng(_seed);
    vector<int> a(N);
    iota(a.begin(),a.end(),0);
    ranges::shuffle(a,eng);
    vector<int> ternary;
    while(X) ternary.emplace_back(X%3),X/=3;
    ranges::reverse(ternary);
    auto pos=0;
    set<int> invaild(P,P+K);
    for(auto&i:ternary){
        if(!i){            // Type '01'
            while(pos+2<N&&invaild.contains(a[pos+1])){
                Set(a[pos++],false);
                Set(a[pos++],false);
            }
            Set(a[pos++],false);
            Set(a[pos++],true);
        }else if(i==1){    // Type '10'
            while(pos+2<N&&invaild.contains(a[pos])){
                Set(a[pos++],false);
                Set(a[pos++],false);
            }
            Set(a[pos++],true);
            Set(a[pos++],false);
        }else{             // Type '11'
            while(pos+2<N&&(invaild.contains(a[pos])||invaild.contains(a[pos+1]))){
                Set(a[pos++],false);
                Set(a[pos++],false);
            }
            Set(a[pos++],true);
            Set(a[pos++],true);
        }
        if(pos+2>N-1) break;
    }
    for(;pos<N;++pos) Set(a[pos],false);
}

long long Bruno(int N,int A[]){
    random_engine eng(_seed);
    vector<int> a(N);
    iota(a.begin(),a.end(),0);
    ranges::shuffle(a,eng);
    auto ans=0ll;
    for(auto pos=0;pos<N;pos+=2){
        if(A[a[pos]]||A[a[pos+1]]){
            (ans*=3)+=(map{
                pair(pair(0,1),0),
                pair(pair(1,0),1),
                pair(pair(1,1),2)
            })[{A[a[pos]],A[a[pos+1]]}];
        }
    }
    return ans;
}
