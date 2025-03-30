#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
class mathbase{
public:
    auto isprime(auto x) const{
        for(auto i=2;i*i<x+1;++i) if(!(x%i)) return false;
        return true;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        const auto c=n/3-1;
        cir(i,2,n+1){
            if(min(i,n-1-i)+1>c-1&&math.isprime(i)){
                cir(x,0,n+1){
                    if(i-x>0) cout<<i-x<<' ';
                    if(x&&i+x<n+1) cout<<i+x<<' ';
                }
                break;
            }
        }
        cout<<'\n';
    }();
    return 0;
}
