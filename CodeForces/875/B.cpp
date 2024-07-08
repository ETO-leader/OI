#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        unordered_map<int,int> amx,bmx;
        auto input=[&](unordered_map<int,int>&x){
            int li=-114514,cnx=0;
            cir(i,0,n){
                int w;cin>>w;
                if(w!=li){
                    if(cnx) x[li]=max(x[li],cnx);
                    cnx=0;li=w;
                }
                ++cnx;
            }
            if(cnx) x[li]=max(x[li],cnx);
        };
        input(amx);input(bmx);
        int mx=0;
        for(auto&[a,b]:amx) mx=max(mx,b+bmx[a]);
        for(auto&[a,b]:bmx) mx=max(mx,b+amx[a]);
        cout<<mx<<'\n';
    }
    return 0;
}
