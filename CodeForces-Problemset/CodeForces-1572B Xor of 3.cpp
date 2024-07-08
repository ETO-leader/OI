#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        cir(i,1,n) a[i]^=a[i-1];
        if(a.back())
            return cout<<"NO\n",void();
        auto odd=[](int l,int r,string p=""){
            for(int i=r-2;i>l-1;i-=2)
                cout<<i+1<<' ';
            for(int i=l;i<r-1;i+=2)
                cout<<i+1<<' ';
            cout<<p;
        };
        if(n&1){
            cout<<"YES\n"<<n-1<<'\n';
            return odd(0,n-1,"\n");
        }
        cir(i,0,n) if((!a[i])&&(!(i&1))){
            cout<<"YES\n"<<n-2<<'\n';
            odd(0,i);odd(i+1,n-1,"\n");
            return;
        }
        cout<<"NO\n";
    }();
    return 0;
}
