#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int MOD=20130427;
vector<lint> arr;
vector<vector<lint>> D,L,S;
lint sum(lint x){return x*(x-1)/2%MOD;}
lint runx(int n,const lint b){
    vector<lint> nm(n);
    cir(i,0,n){
        const lint ad=(bool)(i)*b-1;
        nm[i]=((i?nm[i-1]:0)*b+arr[i]+ad)%MOD;
        L[i][0]=(i?L[i-1][0]:0)+1;
        L[i][1]=(L[i][0]*arr[i]+(((i?L[i-1][1]:0)
            +(i?nm[i-1]:0))*b+ad))%MOD;
        S[i][0]=((i?S[i-1][0]:0)*b+L[i][0]*arr[i])%MOD;
        S[i][1]=(sum(ad+1)+(i?S[i-1][0]:0)*b*arr[i]%MOD+
            sum(arr[i])*L[i][0]+(i?S[i-1][1]:0)*b%MOD*b+
            (i?L[i-1][1]+nm[i-1]:0)*sum(b))%MOD;
        D[i][0]=((i?D[i-1][0]:0)+S[i][0])%MOD;
        D[i][1]=((i?D[i-1][0]:0)*arr[i]+(i?D[i-1][1]:0)*
            b+S[i][1])%MOD;
    }
    return (D[n-1][0]+D[n-1][1])%MOD;
}
lint runans(bool qx,lint b){
    int x;cin>>x;arr.clear();arr.resize(x);
    D.clear();D.assign(x,vector<lint>(2));
    L.clear();L.assign(x,vector<lint>(2));
    S.clear();S.assign(x,vector<lint>(2));
    for(auto&i:arr) cin>>i;
    reverse(arr.begin(),arr.end());
    if(qx&&(count(arr.begin(),arr.end(),0
        )!=arr.size())) for(auto&i:arr){
        if(i){--i;break;}
        i=9;
    }
    reverse(arr.begin(),arr.end());
    return runx(x,b);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint b;cin>>b;
    lint ansx=-runans(true,b);
    cout<<(ansx+runans(false,b)+MOD)%MOD<<'\n';
    return 0;
}
