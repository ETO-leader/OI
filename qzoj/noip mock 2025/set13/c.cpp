#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;i++)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int m,n,p;cin>>m>>n>>p;
    vector<int> k(m);
    for(auto&i:k) cin>>i;
    if(accumulate(k.begin(),k.end(),0)==n){
        vector<int> tags(n+1,1),vis(n+1);
        tags[0]=tags[1]=0;
        for(auto&x:k) cir(i,2,x+1) --tags[i];
        cir(i,2,n+1) if(!vis[i]){
            for(auto x=i*2;x<n+1;x+=i){
                auto c=0,w=x;
                while(!(w%i)) w/=i,++c;
                tags[i]+=tags[x]*c;
                vis[x]=true;
            }
        }else{
            tags[i]=0;
        }
        auto ans=1ll;
        cir(i,2,n+1) cir(c,0,tags[i]) (ans*=i)%=p;
        cout<<ans<<'\n';
    }else{
        cout<<0<<'\n';
    }
    return 0;
}
