#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto maxsc=650;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    auto check=[&](vector<int> high,vector<int> low){
        priority_queue<int> h,l;
        for(auto&x:high) h.emplace(x);
        for(auto&x:low) l.emplace(x);
        auto cnt=0;
        while(!h.empty()){
            const auto w=h.top();h.pop();
            while((!l.empty())&&l.top()>w-1) l.pop();
            if(!l.empty()) ++cnt,l.pop();
        }
        return cnt;
    };
    vector<int> ml,mh,fl,fh;
    cir(i,0,n){
        int x;cin>>x;
        (x<0?mh:ml).emplace_back(abs(x));
    }
    cir(i,0,n){
        int x;cin>>x;
        (x<0?fh:fl).emplace_back(abs(x));
    }
    cout<<check(mh,fl)+check(fh,ml)<<'\n';
    return 0;
}
