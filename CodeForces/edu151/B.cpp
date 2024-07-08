#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int ax,bx,cx,ay,by,cy;
        cin>>ax>>ay>>bx>>by>>cx>>cy;
        int ans=1;
        if(bx>ax&&cx>ax) ans+=min(bx,cx)-ax;
        if(bx<ax&&cx<ax) ans+=ax-max(bx,cx);
        if(by>ay&&cy>ay) ans+=min(by,cy)-ay;
        if(by<ay&&cy<ay) ans+=ay-max(by,cy);
        cout<<ans<<'\n';
    }
    return 0;
}