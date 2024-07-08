#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=200;
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI v(n);
    for(auto&i:v) cin>>i,i%=MOD;
    cir(i,0,n){
        if(!v[i]){
            cout<<"Yes\n";
            if(!i) cout<<"2 1 2\n1 2\n";
            else cout<<"2 1 "<<i+1<<"\n1 1\n";
            exit(0);
        }
    }
    vector<VI> D(n+1,VI(MOD)),F(n+1,VI(MOD)),siz(n+1,VI(MOD));
    function<void(int,int,int)> print=
        [&](int x,int vx,int cnt){
        if(!x) return cout<<cnt<<' ',void();
        print(x-1,F[x][vx],cnt+(F[x][vx]!=vx||(!v[x-1])));
        if(F[x][vx]!=vx||(!v[x-1])) cout<<x<<' ';
    };
    D[0][0]=true;
    cir(i,1,n+1) cir(w,0,MOD){
        int unc=(w+MOD-v[i-1])%MOD;
        if(D[i-1][unc]&&D[i-1][w]&&siz[i-1][w]){
            F[i][w]=unc;cout<<"Yes\n";
            print(i-1,w,0);cout<<'\n';
            print(i,w,0);cout<<'\n';
            exit(0);
        }
        D[i][w]|=(D[i-1][unc]|D[i-1][w]);
        int fwc=(D[i-1][unc]?unc:w);
        if(D[i][w]) F[i][w]=fwc;
        if(D[i][w])
            siz[i][w]=siz[i-1][F[i][w]]+(F[i][w]!=w||!(v[i-1]));
    }
    cout<<"No\n";
    return 0;
}
