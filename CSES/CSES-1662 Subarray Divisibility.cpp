#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
template<typename T>
T modifine(T a,T b){return a>=0?a%b:(b-(-a)%b)%b;}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n;cin>>n;vector<lint> v(n);
    for(auto&i:v) cin>>i;
    cir(i,1,n) v[i]+=v[i-1];
    unordered_map<int,int> um;
    lint ans=0;um[0]=1;
    for(auto&i:v){
        ans+=um[modifine(i,n)];um[modifine(i,n)]++;
    }
    cout<<ans<<'\n';
    return 0;
}