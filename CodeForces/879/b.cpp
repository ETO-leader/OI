#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        string l,r;cin>>l>>r;
        while(l.size()<r.size()) l.insert(l.begin(),'0');
        auto ans=0,cur=0;
        cir(i,0,(int)(l.size())){
            if(r[i]!=l[i]) ans=max(ans,cur+abs(r[i]-l[i])+(int)(l.size()-i-1)*9);
        }
        println("{}",ans);
    }();
    return 0;
}
