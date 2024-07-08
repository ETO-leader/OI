#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
constexpr auto qpow(lint a,lint b,const lint p){
    auto res=1ll;
    while(b){
        if(b&1) (res*=a)%=p;
        (a*=a)%=p;b>>=1;
    }
    return res;
}
auto bsgs(lint a,lint b,const lint p){
    const auto sqr=(int)(sqrt(p)+7);
    __gnu_pbds::gp_hash_table<lint,int> pws;
    auto cur=1ll;a%=p;b%=p;
    if(p==1) return to_string(0);
    cir(i,0,sqr){
        if(cur==b) return to_string(i);
        pws[cur*b%p]=i;(cur*=a)%=p;
    }
    const auto px=cur;cur=px;
    if(!px) return (string)("No Solution");
    cir(i,1,(int)(p/sqr)+2){
        (cur*=px)%=p;
        if(!cur) break;
        if(pws.find(cur)!=pws.end()){
            if(qpow(a,(i+1)*sqr-pws[cur],p)!=b) break;
            return to_string((i+1)*sqr-pws[cur]);
        }
    }
    return (string)("No Solution");
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint a,b,p;
    for(cin>>a>>p>>b;a||b||p;cin>>a>>p>>b){
        cout<<bsgs(a,b,p)<<'\n';
    }
    return 0;
}
