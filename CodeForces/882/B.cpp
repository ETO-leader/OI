#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        vector<int> v(n);
        for(auto&i:v) cin>>i;
        int cnx=0,aland=-1;
        for(auto&i:v){
            if(aland<0) aland=i;
            else if(!aland) ++cnx,aland=i;
            aland&=i;
        }
        if((!aland)||(!cnx)) ++cnx;
        cout<<cnx<<'\n';
    }
    return 0;
}
