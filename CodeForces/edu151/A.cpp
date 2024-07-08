#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,k,x;cin>>n>>k>>x;
        vector<VI> D(k+1,VI(n+1)),C(k+1,VI(n+1));
        D[0][0]=true;
        cir(i,1,k+1){
            D[i]=D[i-1];
            if(i==x) continue;
            cir(j,i,n+1) if(D[i][j-i]&&(!D[i][j])){
                D[i][j]=true,C[i][j]=C[i][j-i]+1;
            }
        }
        if(!D[k][n]){cout<<"NO\n";continue;}
        cout<<"YES\n";
        int w=n,cnx=0;
        stringstream ss;
        for(int i=k;i;--i){
            cir(j,0,C[i][w]) ss<<i<<' ',++cnx;
            w-=i*C[i][w];
        }
        cout<<cnx<<'\n'<<ss.str()<<'\n';
    }
    return 0;
}