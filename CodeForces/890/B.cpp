#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;vector<int> v(n);
        for(auto&i:v) cin>>i;
        if(n==1){
            cout<<"NO\n";
            continue;
        }
        auto sum_n1=accumulate(v.begin(),v.end(),
            0ll)-n;
        cout<<(sum_n1>=count(v.begin(),v.end(),1)?
            "YES\n":"NO\n");
    }
    return 0;
}
