#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        VI a(n),D(n),mx(n+1,-1);
        for(auto&i:a) cin>>i;
        mx[a[0]]=0;
        cir(i,1,n) [&]{
            if(mx[a[i]]<0){
                D[i]=D[i-1],mx[a[i]]=i;
                return;
            }
            D[i]=max(D[i-1],(mx[a[i]]?
                D[mx[a[i]]-1]:0)+i-mx[a[i]]+1);
            if(!mx[a[i]]) return;
            if(D[i-1]>D[mx[a[i]]-1]+i-mx[a[i]]){
                mx[a[i]]=i;
            }
        }();
        cout<<D[n-1]<<'\n';
    }
    return 0;
}
