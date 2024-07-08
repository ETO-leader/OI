//20% tasks
//N,Q \le 2000
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;vector<lint> ax(n);
    cir(qx,0,q){
        int op;cin>>op;
        if(op==1){
            int l,r,a,b;cin>>l>>r>>a>>b;
            lint x=0;--l;--r;
            cir(i,l,r+1) ax[i]=((x+=a)%=b);
        }else{
            int l,r;cin>>l>>r;--l;--r;
            lint ans=0;
            cir(i,l,r+1) ans+=ax[i];
            cout<<ans<<'\n';
        }
    }
    return 0;
}
