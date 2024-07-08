#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct opt{int p,w;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,m,q;cin>>n>>m>>q;
        vector<opt> x(n),y(m);
        cir(i,0,q){
            int op,c,cl;cin>>op>>c>>cl;--c;
            (!op?x[c]:y[c])={i+1,cl};
        }
        cir(i,0,n){
            cir(j,0,m){
                cout<<(x[i].p<y[j].p?y[j]:x[i]).w<<' ';
            }
            cout<<'\n';
        }
    }
    return 0;
}
