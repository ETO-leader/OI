#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto mxk=12;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int k;cin>>k;
    constexpr auto n=30,m=30;
    cout<<n<<'\n';
    vector<vector<int>> a(n,vector<int>(m));
    cir(i,0,n) cir(j,0,m) a[i][j]=((i==n-1)||(j==m-1));
    cir(i,0,mxk){
        const auto p=i*2;
        cir(i,0,3) cir(j,0,3) a[p+i][p+j]=true;
    }
    auto dwset=[&](int p,int k){
        if(!k) return;
        cir(x,p*2,n){
            a[x][p*2]=true;
        }
        if(k<5){
            cir(x,0,k){
                a[n-x-1][p*2+1]=true;
            }
        }else{
            cir(x,0,3) cir(y,0,3){
                a[n-x-1][p*2+y]=true;
            }
            if(k==5) a[n-3][p*2+2]=0;
        }
    };
    auto rgset=[&](int p,int k){
        if(!k) return;
        cir(x,p*2,m){
            a[p*2][x]=true;
        }
        if(k<5){
            cir(x,0,k){
                a[p*2+1][m-x-1]=true;
            }
        }else{
            cir(x,0,3) cir(y,0,3){
                a[p*2+y][m-x-1]=true;
            }
            if(k==5) a[p*2+2][m-3]=0;
        }
    };
    cir(i,0,mxk){
        const auto c=k%6;k/=6;
        if(i&1) dwset(i,c);
        else rgset(i,c);
    }
    for(auto&i:a){
        for(auto&j:i) cout<<j<<' ';
        cout<<'\n';
    }
    return 0;
}
