#include"souvenirs.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;

using lint=long long;

void buy_souvenirs(int n,lint P0){
    vector<lint> cnt(n),val(n,-1);
    auto buy=[&](auto __self,lint w,int lim)->int {
        auto[arr,c]=transaction(w);
        for(auto&i:arr) ++cnt[i];
        auto sum=w-c;
        auto check=[&]{
            while(arr.back()>lim-1){
                sum-=val[arr.back()];
                arr.pop_back();
            }
        };
        check();
        while(arr.front()+1<lim){
            lim=__self(__self,(sum-1)/arr.size(),lim);
            check();
        }
        val[arr.front()]=sum;
        return arr.front();
    };
    val[0]=P0;
    cir(i,0,n-1) if(val[i+1]==-1) buy(buy,val[i]-1,n);
    cir(i,1,n) cir(x,cnt[i],i) transaction(val[i]); 
}

#undef cir

