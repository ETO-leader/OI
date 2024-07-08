#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const int MOD=1e9+7;
lint qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
lint inv(lint x){
    return qpow(x,MOD-2);
}
const int inv2=inv(2);
lint&add_e(lint&x,lint k){
    return (x+=k)%=MOD;
}
lint&minus_e(lint&x,lint k){
    return (((x-=k)%=MOD)+=MOD)%=MOD;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;VI s(n);
    lint ans=0;
    for(auto&i:s){
        cin>>i;
        ((ans+=(m+1))-=i)%=MOD;
    }
    cir(cur,0,n-1){
        vector<VI> D(m+7,VI(m+7));
        D[0][0]=1;
        const auto gp=s[cur+1]-s[cur];
        const auto w=(m+1)*2-s[cur]-s[cur+1];
        cir(sum,0,w+1){
            cir(i,0,min<int>(sum,m+1-s[cur])+1){
                const auto j=sum-i;
                if(j<m+1-s[cur+1]+1){
                    if(i-j==gp){
                        minus_e(ans,(m+1-s[cur]-
                            i)*D[i][j]);
                    }else{
                        const auto p=D[i][j]*inv2;
                        add_e(D[i+1][j],p);
                        add_e(D[i][j+1],p);
                    }
                } 
            }
        }
    }
    cout<<ans<<'\n';
    return 0;
}
