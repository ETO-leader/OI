#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
auto chk(int x,int y){
    auto res=false;
    while(x&&y){
        if(x>y) swap(x,y);
        y%=(x*2);
        if(x-1<y) y-=x,res^=true;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    auto ans=0;
    cir(i,0,n){
        int x,y;cin>>x>>y;
        cir(dx,0,2) cir(dy,0,2){
            ans^=chk(x-dx,y-dy);
        }
    }
    cout<<(ans?"FIRST":"SECOND")<<'\n';
    return 0;
}
