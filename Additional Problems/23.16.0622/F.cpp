//Time complexity: Θ(n²m²)
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#pragma GCC optimize("Ofast")
using namespace std;
using lint=long long;
const int nx=2007;
using ary=array<array<int,nx>,nx>;
const int MOD=998244353;
void calculater(ary&v,int n,int m){
    cir(i,1,n+1) cir(j,1,m+1)
        (v[i][j]+=((v[i-1][j]+v[i][j-1])%MOD-
            v[i-1][j-1]+MOD)%MOD)%=MOD;
}
template<typename T>
T qpow(T x,T y){
    T res=1;
    while(y){
        if(y&1) (res*=x)%=MOD;
        (x*=x)%=MOD;y>>=1;
    }
    return res;
}
inline void fillx(ary&v,int x,int y,int _x,int _y){
    ++v[x][y];--v[x][_y];--v[_x][y];++v[_x][_y];
}
ary v,s,s1,s2,s3,s4;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;    
    cir(i,1,n+1) cir(j,1,m+1){
        char c;cin>>c;v[i][j]=c-'0';
        s[i][j]=s[i][j-1]+v[i][j];
    }
    cir(x,1,n+1) cir(y,1,m+1){
        for(int _y=y;_y<m+1&&v[x][_y];++_y){
            for(int _x=x;_x<n+1&&s[_x][_y]-s[_x][y-1]==_y-y+1;++_x){
                fillx(s1,x,y,_x+1,_y+1);
                fillx(s2,x,y,_x+1,_y);
                fillx(s3,x,y,_x,_y+1);
                fillx(s4,x,y,_x,_y);
            }
        }
    }
    calculater(s1,n,m);calculater(s2,n,m);
    calculater(s3,n,m);calculater(s4,n,m);
    int ans=0;
    cir(i,1,n+1) cir(j,1,m+1){
        (ans+=((qpow<lint>(s1[i][j],k)-qpow<lint>(s2[i][j],k)-
            qpow<lint>(s3[i][j],k)+qpow<lint>(s4[i][j],k))%MOD+
            MOD)%MOD)%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
