#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct chsop{lint a,b,id;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<chsop> a(n);
    cir(i,0,n) cin>>a[i].a,a[i].id=i;
    cir(i,0,n) cin>>a[i].b;
    lint suma=0,sumb=0;
    for(auto&[ai,bi,id]:a){
        suma+=ai;sumb+=bi;
    }
    stringstream ansx;
    auto chk=[&](){
        lint cxa=0,cxb=0;
        cir(i,0,n/2+1){
            cxa+=a[i].a;cxb+=a[i].b;
        }
        if(cxa*2<suma||cxb*2<sumb)
            return false;
        ansx<<(n/2+1)<<'\n';
        cir(i,0,n/2+1) ansx<<a[i].id+1<<' ';
        return true;
    };
    while(!chk())
        random_shuffle(a.begin(),a.end());
    cout<<ansx.str()<<'\n';
    return 0;
}
