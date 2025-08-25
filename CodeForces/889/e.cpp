#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint n;cin>>n;
    vector<int> a(60);
    mt19937_64 eng(251);
    while(![&]{
        vector<lint> f(61);
        f[0]=1;
        auto emplace=[&](auto x){
            for(auto v=60-x;~v;--v) f[v+x]+=f[v];
        };
        auto remove=[&](auto x){
            cir(v,0,60-x+1) f[v+x]-=f[v];
        };
        for(auto&x:a) x=uniform_int_distribution<int>(1,10)(eng);
        for(auto&i:a) emplace(i);
        while(f[60]>n){
            auto p=uniform_int_distribution<int>(0,(int)(a.size())-1)(eng);
            remove(a[p]);
            a.erase(a.begin()+p);
        }
        auto w=1;
        while(w<61&&a.size()<60){
            a.emplace_back(w);
            emplace(w);
            if(f[60]>n){
                remove(w);
                a.pop_back();
                ++w;
            }
        }
        return f[60]==n;
    }());
    println(cout,"{}",a.size());
    for(auto&x:a) print(cout,"{} ",x);
    println(cout);
    return 0;
}
