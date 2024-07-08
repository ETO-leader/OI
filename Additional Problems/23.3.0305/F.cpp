#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,cnt=0;cin>>n;vector<int> v(n);
    const int half=(n+1)/2;
    stringstream ans;
    for(auto&i:v) cin>>i;
    auto print=[&](int l,int r){
        cir(i,0,l) ans<<0;
        cir(i,l,r+1) ans<<1;
        cir(i,r+1,n) ans<<0;
        ++cnt;
    };
    auto rotate=[&](int l,int r){
        int bg=v[r];
        for(int i=r;i>l;--i) v[i]=v[i-1];
        v[l]=bg;
    };
    int pos=0;
    cir(i,half,n){
        if(v[i]<=half){
            while(v[pos]<=half) ++pos;
            rotate(pos,i);print(pos,i);
        }
    }
    cout<<half<<"\n\n";
    for(auto&i:v) cout<<i<<' ';cout<<'\n';
    cout<<ans.str()<<'\n';
    return 0;
}
