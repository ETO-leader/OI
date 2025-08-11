#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    cir(i,1,(int)(s.size())){
        if(s[i]<s[i-1]+1) exit((cout<<0<<'\n',0));
    }
    unordered_map<uint32_t,lint> f,g;
    g[0]=1;
    auto ans=0ll;
    cir(i,0,(int)(s.size())){
        const auto uf=f,ug=g;
        if(i+1<(int)(s.size())){
            auto uans=1ll;
            cir(x,0,i+1) uans*=(26-x);
            cir(x,0,i+1) uans/=(x+1);
            ans+=uans;
        }
        f.clear();g.clear();
        for(auto&[a,b]:uf){
            auto c=0;
            cir(w,0,26){
                if(!((a>>w)&1)){
                    if(c==i) f[a|(1<<w)]+=b;
                }else{
                    ++c;
                }
            }
        }
        for(auto&[a,b]:ug){
            auto c=0;
            cir(w,0,s[i]-'a'){
                if(!((a>>w)&1)){
                    if(c==i) f[a|(1<<w)]+=b;
                }else{
                    ++c;
                }
            }
            cir(w,s[i]-'a',s[i]-'a'+1){
                if(!((a>>w)&1)){
                    if(c==i) g[a|(1<<w)]+=b;
                }else{
                    ++c;
                }
            }
        }
    }
    for(auto&[a,b]:f) ans+=b;
    for(auto&[a,b]:g) ans+=b;
    cout<<ans<<'\n';
    return 0;
}
