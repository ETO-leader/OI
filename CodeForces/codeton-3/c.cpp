#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;string a,b;
        cin>>a>>b;
        auto cnt=0,opc=0;
        stringstream op;
        cir(i,0,n) if(a[i]=='1'){
            a[i]='0';
            b[i]=(b[i]=='1'?'0':'1');
            cnt^=1;++opc;
            op<<i+1<<' '<<i+1<<'\n';
        }
        if(cnt) cir(i,0,n) b[i]=(b[i]=='1'?'0':'1');
        if(ranges::count(b,'0')&&ranges::count(b,'1')) return cout<<"NO"<<'\n',void();
        cout<<"YES"<<'\n';
        if(ranges::count(b,'1')){
            op<<1<<' '<<1<<'\n';
            op<<1<<' '<<2<<'\n';
            op<<2<<' '<<2<<'\n';
            opc+=3;
        }
        cout<<opc<<'\n'<<op.str();
    }();
    return 0;
}
