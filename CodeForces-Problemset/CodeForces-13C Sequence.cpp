#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,st=0;cin>>n;vector<int> vi(n),vx;
    for(auto&i:vi) cin>>i;vx=vi;
    sort(vx.begin(),vx.end());
    vector<vector<lint>> D(2,vector<lint>(n));
    cir(i,0,n){
        st^=1;
        D[st][0]=D[st^1][0]+abs(vi[i]-vx[0]);
        cir(j,1,n){
            D[st][j]=min(D[st][j-1],D[st^1][j]+abs(vi[i]-vx[j]));
        }
    }
    cout<<(*min_element(D[st].begin(),D[st].end()))<<'\n';;
    return 0;
}