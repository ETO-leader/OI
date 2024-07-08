#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define int long long
using namespace std;
const int _inf=1e9+7;
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int p,q,n1,n2,n3;cin>>p>>q>>n1>>n2>>n3;
    if(1LL*n1*p>q){
        assert(false);
        cout<<"-1\n";
        exit(0);
    }
    const int a=n2-n1,b=n3-n1,k=q-n1*p;
    if((!a)&&(!b)){
        if(1LL*n1*p==q){
            cout<<0<<' '<<p<<'\n';
        }else{
            cout<<"-1\n";
        }
        exit(0);
    }
    if(!a){
        if(k%b) cout<<"-1\n";
        else cout<<k/b<<' '<<k/b<<'\n';
        exit(0);
    }
    if(!b){
        int mx=-1;
        for(int y=0;y*n2<q+1;++y){
            if(!((q-y*n2)%n1)){
                const int nx=(q-y*n2)/n1;
                if(nx+y==p) mx=y;
            }
        }
        if(mx<0){
            cout<<"-1\n";
        }else{
            cout<<0<<' '<<mx<<'\n';
        }
        exit(0);
    }
    //ax+by=k,Q:max_y,min_y
    int mn=_inf,mx=-1;
    for(int y=0;y*b<k+1;++y){
        if(!((k-y*b)%a)){
            const auto x=(k-y*b)/a;
            if((x*n2+y*n3>q)||(q-x*n2-y*n3)/n1!=p-x-y)
                continue;
            mn=min(mn,y),mx=max(mx,y);
        }
    }
    if(mn==_inf||mx<0){
        cout<<"-1\n";
    }else{
        cout<<mn<<' '<<mx<<'\n';
    }
    return 0;
}
