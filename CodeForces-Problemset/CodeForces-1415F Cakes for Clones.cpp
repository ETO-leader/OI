#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
constexpr lint _inf=1e18+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI p(n+1),t(n+1);
    cir(i,1,n+1) cin>>t[i]>>p[i];
    vector<VI> D(n+1,VI(n+1));
    VI C(n+1,_inf);D[0][0]=true;C[0]=0;
    auto __dis=[&](int x,int y){
        return abs(p[x]-p[y]);
    };
    cir(i,1,n+1){
        cir(j,i+1,n+1) [&](){
            if(i>2&&D[i-2][i-1]&&t[i]>=max(t[i-1],t[i-2]+__dis(i-2,j))+__dis(i,j))
                return D[i][j]=true,void();
            if(D[i-1][j]&&__dis(i,i-1)<=abs(t[i]-t[i-1]))
                return D[i][j]=true,void();
            if(t[i]>=max(t[i-1],__dis(i-1,j)+C[i-1])+__dis(i,j))
                return D[i][j]=true,void();
        }();
        [&](){
            if(i>2&&D[i-2][i-1])
                C[i]=max(t[i-2]+__dis(i-2,i),t[i-1]);
            cir(j,i,n+1) if(D[i-1][j])
                C[i]=min(C[i],t[i-1]+__dis(i-1,i));
            C[i]=min(C[i],max(C[i-1]+__dis(i-1,i),t[i-1]));
            if(t[i]<C[i]) C[i]=_inf;
        }();
    }
    cout<<((C[n]<=t[n]||D[n-1][n])?"YES\n":"NO\n");
    return 0;
}
