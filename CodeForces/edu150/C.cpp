#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const VI pow10{1,10,100,1000,10000};
const int _inf=2e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        string nx;cin>>nx;
        const int n=nx.size();
        reverse(nx.begin(),nx.end());
        vector<vector<VI>> D(n,vector<VI>(5,VI(2,-_inf)));
        cir(i,0,5) D[0][i][true]=pow10[i];
        D[0][nx[0]-'A'][false]=pow10[nx[0]-'A'];
        cir(i,1,n) cir(j,0,5) cir(ched,0,2){
            if(nx[i]-'A'<=j) D[i][j][ched]=([&](){
                int mx=-_inf;
                cir(ix,0,j+1) if(D[i-1][ix][ched]!=-_inf)
                    mx=max(mx,D[i-1][ix][ched]);
                return mx;
            }()+pow10[nx[i]-'A']*(nx[i]-'A'<j?-1:1));
            if(ched){
                D[i][j][ched]=max(([&](){
                    int mx=-_inf;
                    cir(ix,0,j+1) mx=max(mx,D[i-1][ix][false]);
                    return mx;
                }()+pow10[j]),D[i][j][ched]);
            }
        }
        cout<<[&](){
            int mx=-_inf;
            cir(ix,0,5) cir(ched,0,2)
                mx=max(mx,D[n-1][ix][ched]);
            return mx;
        }()<<'\n';
    }
    return 0;
}
