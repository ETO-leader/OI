#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class simplecase{
public:
    auto registercase(const int n){
        vector<int> a(n*2);
        for(auto&i:a) cin>>i;
        auto mx=0,mn=numeric_limits<int>::max();
        cir(i,0,n/2){
            vector qx({
                a[i*2]+a[i*2+1],
                a[i*2]+a[i*2+n+1],
                a[i*2+n]+a[i*2+1],
                a[i*2+n]+a[i*2+n+1]
            });
            ranges::sort(qx);
            mn=min(mn,qx[1]);
            mx=max(mx,qx[2]);
        }
        cout<<mx-mn<<'\n';
    }
};
class hardcase{
public:
    auto registercase(const int n){
        vector<int> a(n*2);
        for(auto&i:a) cin>>i;
        if(n==1) return cout<<0<<'\n',void();
        auto u=0;
        vector<int> na;
        cir(i,0,n){
            na.push_back(a[u]);
            na.push_back(a[u+1]);
            (u+=n+1)%=(n*2);
        }
        auto check=[&](int x,int y){
            vector f(2,vector<int>(n*2,numeric_limits<int>::max()));
            const auto mnw=na[(-x+n*2)%(n*2)]+na[y+1];
            f[y][0]=mnw;
            cir(i,1,n) cir(lx,0,2) cir(nx,0,2){
                if(f[lx][i-1]>numeric_limits<int>::max()-1) continue;
                const auto wx=na[i*2-lx]+na[(i*2+1+nx)%(n*2)];
                if(wx>mnw-1) f[nx][i]=min(f[nx][i],max(f[lx][i-1],wx));
            }
            if(f[x][n-1]<numeric_limits<int>::max()) return f[x][n-1]-mnw;
            return numeric_limits<int>::max();
        };
        auto ans=numeric_limits<int>::max();
        cir(i,0,n){
            ranges::rotate(na,na.begin()+2);
            cir(x,0,2) cir(y,0,2) ans=min(ans,check(x,y));
        }
        cout<<ans<<'\n';
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        n&1?hardcase().registercase(n):simplecase().registercase(n);
    }();
    return 0;
}
      
 
      
 
       