#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T,p;cin>>T>>p;
    while(T--){
        lint n;cin>>n;
        map<tuple<int,int,int>,lint> f;
        function<lint(lint,int,int)> dfs=[&](lint u,lint gc,lint lc)->lint {
            if(n%lc) return 0ll;
            if(u>n) return (lint)(gc==1&&lc==n);
            const auto key=make_tuple(u,gc,lc);
            if(f.count(key)) return f[key];
            return f[key]=(dfs(u+1,__gcd(gc,u),lc/__gcd(u,lc)*u)+dfs(u+1,gc,lc))%p;
        };
        cout<<dfs(1,0,1)<<'\n';
    }
    return 0;
}
