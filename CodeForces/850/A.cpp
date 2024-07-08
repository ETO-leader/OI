#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        int a1=0,b1=0,a2=0,b2=0;
        int step=0,rx=0;
        cir(i,0,n){
            if(i==rx) step++,rx+=step;
            if(step%4==2||step%4==3)
                i&1?++b2:++b1;
            else i&1?++a2:++a1;
        }
        cout<<a1<<' '<<a2<<' '<<b1<<' '<<b2<<'\n';
    }
}