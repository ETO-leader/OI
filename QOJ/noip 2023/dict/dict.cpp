#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<string> s(n);
    for(auto&x:s){
        cin>>x;
        ranges::sort(x,ranges::greater{});
    }
    const auto mx=*ranges::min_element(s);
    for(auto&x:s){
        ranges::reverse(x);
        cout<<(!(mx<x));
    }
    cout<<'\n';
    return 0;
}
