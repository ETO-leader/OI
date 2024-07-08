#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const lint _inf=1e15+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        vector<VI> a(n);
        lint mnw=_inf,mnsw=_inf,cnx=0;
        for(auto&i:a){
            int x;cin>>x;i.resize(x);
            for(auto&j:i) cin>>j;
            sort(i.begin(),i.end());
            if(x>1) mnw=min(mnw,i[0]);
            mnsw=min(mnsw,i[1-(x==1)]);
            cnx+=i[1-(x==1)];
        }
        if(mnsw>mnw) (cnx-=mnsw)+=mnw;
        cout<<cnx<<'\n';
    }
    return 0;
}
