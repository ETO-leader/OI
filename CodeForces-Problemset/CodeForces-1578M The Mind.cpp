#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
auto check(const int cnt){
    vector<int> aps(100);
    mt19937 rnd(random_device().operator()());
    cir(i,0,cnt){
        set<int> ax;
        uniform_int_distribution<> rd(0,99);
        while(ax.size()<5) ax.insert(rd(rnd));
        ++aps[*ax.begin()];
    }
    const auto cx=cnt/4;
    auto cntx=0;
    vector dff({0});
    cir(i,0,100){
        cntx+=aps[i];
        if(cntx>cx) cntx=aps[i],dff.push_back(i);
    }
    while(dff.size()>5) dff.pop_back();
    dff.push_back(101);
    return vector({0,5,9,15,21,35,101});
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;const auto p=check(200000);
    while(T--) [&](){
        vector<int> a(5);
        for(auto&i:a) cin>>i;
        cir(i,0,5){
            cout<<(a[0]>p[i]-1&&a[0]<p[i+1])<<' ';
        }
        cout<<'\n';
        cout.flush();
    }();
    return 0;
}
