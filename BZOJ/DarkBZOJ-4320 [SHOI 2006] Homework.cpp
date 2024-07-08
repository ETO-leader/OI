#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int _inf=1e9+7;
const int maxx=3e5+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;const int sqr=2e3;
    vector<int> lsssum(sqr,_inf);
    set<int> sx;
    cir(i,0,n){
        char op;int k;cin>>op>>k;
        if(op=='A'){
            cir(i,1,sqr)
                lsssum[i]=min(lsssum[i],k%i);
            sx.insert(k);
        }else if(k<sqr){
            cout<<lsssum[k]<<'\n';
        }else{
            int x=0,ansx=_inf;
            while(x*k<maxx&&sx.lower_bound(x*k)!=sx.end()){
                ansx=min(ansx,(*sx.lower_bound(x*k))%k);
                ++x;
            }
            cout<<ansx<<'\n';
        }
    }
    return 0;
}
