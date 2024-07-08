#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<int> p,isnp;
void init_pr(int n){
    isnp.resize(n+1);p.clear();
    cir(i,2,n+1){
        if(isnp[i]) continue;
        for(int j=i;j<=n;j+=i) isnp[j]=true;
        p.push_back(i);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        if(n==4){
            cout<<"abca\n";continue;
        }
        int p=2;
        cir(i,2,n){
            if(n%i){
                p=i;break;
            }
        }
        cir(i,0,n) cout<<(char)('a'+(i%p));
        cout<<'\n';
    }
    return 0;
}
