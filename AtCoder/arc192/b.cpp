#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i,i%=2;
    const auto w=accumulate(a.begin(),a.end(),0);
    cout<<
        (n==1?
            "Fennec":
            (n==2?
                "Snuke":
                ((n==3&&w==2)||(w&1)?
                    "Fennec":
                    "Snuke"
                )
            )
        )
    <<'\n';
    return 0;
}
