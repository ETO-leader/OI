#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;string a,b;cin>>a>>b;
        auto px=n+7,py=n+7;
        cir(i,0,n) if(a[i]=='1'){
            px=i;break;
        }
        cir(i,0,n) if(b[i]=='1'){
            py=i;break;
        }
        cout<<(px>py?"NO":"YES")<<'\n';
    }();
    return 0;
}
