#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    cout<<300<<' '<<108<<' '<<2<<'\n';
    cir(i,1,300) cout<<0<<' ';
    cout<<1<<'\n';
    cout<<1<<' '<<100<<' '<<"EPS"<<' '<<0<<' '<<1<<'\n';
    cout<<1<<'\n';
    cir(c,0,26){
        cout<<100<<' '<<100<<' '<<(char)('a'+c)<<' '<<1<<' '<<c+3<<'\n';
        cout<<1<<' ';
        cir(i,0,c+1) cout<<2<<' ';
        cout<<1<<'\n';
    }
    cir(c,0,26){
        cout<<100<<' '<<200<<' '<<(char)('a'+c)<<' '<<1<<' '<<0<<'\n'<<'\n';
    }
    cout<<100<<' '<<200<<' '<<"EPS"<<' '<<1<<' '<<0<<'\n';
    cout<<'\n';
    cir(c,0,27){
        cout<<200+c<<' '<<200+c+1<<' '<<"EPS"<<' '<<2<<' '<<0<<'\n'<<'\n';
        if(c) cout<<200+c<<' '<<200<<' '<<(char)('a'+c-1)<<' '<<1<<' '<<0<<'\n'<<'\n';
    }
    cout<<200<<' '<<300<<' '<<"EPS"<<' '<<0<<' '<<0<<'\n'<<'\n';
    return 0;
}
