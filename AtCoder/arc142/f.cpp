#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
enum __op_types{__EQ,__AEQ,__BEQ,__SAM,__NEQ};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> types(n);
    auto cx=0,cy=0,cnt=0,sum=0;
    for(auto r=0;auto&x:types){
        int a,b,c,d;cin>>a>>b>>c>>d;
        --a;--b;--c;--d;
        ++r;
        if(a==c&&b==d){
            if(a) cx+=1,sum+=r;
            if(b) cy+=1,sum+=r;
            x=__EQ;
        }else if(a==c){
            if(a) cx+=1,sum+=r;
            x=__AEQ;
        }else if(b==d){
            if(b) cy+=1,sum+=r;
            x=__BEQ;
        }else if(a==b){
            x=__SAM;
        }else{
            ++cnt;
            x=__NEQ;
            sum+=r;
        }
    }
    vector<int> f(n+1),g(n+1);
    cir(i,0,n+1){
        f[i]=g[i]=-i*(i+1)/2;
        for(auto p=n-1,c=i,w=f[i];~p;--p){
            if(types[p]==__BEQ) w+=(p-c),++c,f[i]=max(f[i],w);
        }
        for(auto p=n-1,c=i,w=g[i];~p;--p){
            if(types[p]==__AEQ) w+=(p-c),++c,g[i]=max(g[i],w);
        }
    }
    auto ans=numeric_limits<int>::min();
    cir(x,0,cnt+1){
        ans=max(ans,f[cx+x]+g[cnt+cy-x]);
        for(auto p=n-1,c=0,w=0;~p;--p){
            if(types[p]==__SAM) ++c,w+=(p+1)*2,ans=max(ans,f[cx+c+x]+g[cy+c+cnt-x]+w);
        }
    }
    cout<<ans+sum<<'\n';
    return 0;
}
