#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<int> p,np;
void init_pr(int n){
    vector<bool> isnp(n+1);p.clear();
    cir(i,2,n+1){
        if(isnp[i]){
            np.push_back(i);
            continue;
        }
        for(int j=i;j<=n;j+=i) isnp[j]=true;
        p.push_back(i);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;init_pr((int)(3e5));
    while(T--){
        int n;cin>>n;
        if(n==2){
            cout<<"1 2"<<'\n';
            continue;
        }
        const int psiz=upper_bound(p.begin(),
            p.end(),n)-p.begin();
        int pos=0;
        cir(i,0,psiz/2) cout<<p[i]<<' ',++pos;
        int cnx=-1;
        while(pos<n/2) cout<<np[(++cnx)]<<' ',++pos;
        cout<<1<<' ';
        while(np[(++cnx)]<=n) cout<<np[cnx]<<' ';
        cir(i,psiz/2,psiz) cout<<p[i]<<' ';
        cout<<'\n';
    }
    return 0;
}