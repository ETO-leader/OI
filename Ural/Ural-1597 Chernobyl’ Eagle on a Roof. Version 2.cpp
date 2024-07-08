#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
vector<vector<lint>> ans;
auto init(){
    static constexpr auto mx=(int)(2.3e6+7);
    static constexpr auto lg=62;
    static constexpr auto mxw=(lint)(2e18l)+7;
    auto&f=ans;f.resize(lg);
    f[0]=vector<lint>(mx);
    cir(i,1,lg){
        if(i>1) f[0].resize(0);
        if(i>2) f[1].resize(0);
        if(i>3) f[2].resize(0);
        auto&fi=f[i];fi.resize(f[i-1].size());
        cir(j,1,(int)(f[i-1].size())){
            fi[j]=min(mxw,fi[j-1]+f[i-1][j-1]+1);
        }
        while(*prev(fi.end(),2)==mxw) fi.pop_back();
        f[i]=fi;
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    for(lint a,b,inited=false;cin>>b>>a&&(a||b);inited=true) [&](){
        if(!inited) init();
        if(b>(int)(log2l(a)))
            return cout<<(int)(log2l(a))+1<<'\n',void();
        if(b==1) return cout<<a<<'\n',void();
        if(b==2){
            auto ansi=(lint)(sqrtl(a*2));
            while(ansi*(ansi+1)<a*2) ++ansi;
            return cout<<ansi<<'\n',void();
        }
        cout<<lower_bound(ans[b].begin(),ans[b].end(),a)-ans[b].begin()<<'\n';
    }();
    return 0;
}
