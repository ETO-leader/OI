#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<int>;
VI&calculate(VI&D,VI&v,int m){
    const int n=v.size();
    VI cnx(n);
    cir(i,0,m){
        int mxi=0;
        for(int j=i;j<n;j+=m)
            mxi=max(mxi,v[j]);
        for(int j=i;j<n;j+=m)
            cnx[j]=(v[j]==mxi);
    }
    D[0]=cnx[0];
    cir(i,1,n){
        if(cnx[i])
            D[i]=min<int>((cnx[i-1]?D[i-1]:0)
                +1,n/2-1);
        else D[i]=0;
    }
    return D;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI v(n),D(n*2);
    for(auto&i:v) cin>>i;
    v=[&](){
        auto vx=v,vy=v;
        for(auto&i:vy) vx.push_back(i);
        return vx;
    }();
    lint ans=0;
    cir(i,1,n) if(!(n%i)){
        const int nwhi=n/i;
        calculate(D,v,i);
        VI cnx(nwhi);
        cir(j,1,nwhi)
            cnx[j]=cnx[j-1]+(__gcd(j,nwhi)==1);
        cir(j,n,(n*2)) ans+=cnx[D[j]/i]; 
    }
    cout<<ans<<'\n';
    return 0;
}
