#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const lint _inf=1e15+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI a(n);
    iota(a.begin(),a.end(),1);
    lint ans=0;vector<VI> ax;
    a={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,20,19,18,17,16};
    //do{
        lint ansi=0,mx=0;
        cir(i,0,n){
            ansi+=a[i]*(i+1);
            mx=max(mx,a[i]*(i+1));
        }
        const auto w=ansi-mx;
        if(w>ans) ans=w,ax.clear();
        if(w==ans) ax.push_back(a);
    //}while(next_permutation(a.begin(),a.end()));
    cout<<ans<<'\n';
    for(auto&i:ax){
        for(auto&j:i) cout<<j<<' ';
        cout<<'\n';
    }
    return 0;
}
