#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
const int NN=1e6+7;
vector<int> isnp,P;
bool IsPrime(lint k){
    for(lint i=2;i*i<=k;++i) if(!(k%i)) return false;
    return true;
}
void init_pr(int n=NN){
    isnp.resize(n+1);
    cir(i,2,n){
        if(isnp[i]) continue;
        for(int j=i;j<n;j+=i) isnp[j]=true;
        P.push_back(i);
        assert(IsPrime(i));
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    init_pr();int T;cin>>T;
    cout<<P.size()<<'\n'<<flush;
    while(T--){
        lint x,y,ans=0;cin>>x>>y;
        cir(i,x,y+x+1){
            for(auto&j:P){
                if(j*j>i) break;
                if(!(i%j)){--ans;break;}
            }
            ++ans;
        }
        cout<<ans<<'\n';
    }
    return 0;
}