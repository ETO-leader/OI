#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;vector<int> v(n);
        lint cnt=0;
        for(auto&i:v) cin>>i;
        sort(v.begin(),v.end());
        int step=0;
        cir(i,0,n){
            ++step;
            while(i<n-1&&v[i]==v[i+1])
                cnt+=v[i]-step,++i,step+=(v[i]>step);
            cnt+=v[i]-step;
        }
        cout<<cnt<<'\n';
    }
    return 0;
}