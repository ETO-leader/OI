#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    const int cnum=n/2+1;
    vector<lint> a(n),b(n);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    vector<lint> n1(n),n2(n);
    [&](){
        iota(n1.begin(),n1.end(),0);
        iota(n2.begin(),n2.end(),0);
        sort(n1.begin(),n1.end(),
            [&](int i,int j){return a[i]>a[j];});
        sort(n2.begin(),n2.end(),
            [&](int i,int j){return b[i]>b[j];});
    }();
    auto aa=accumulate(b.begin(),b.end(),0LL)/2;
    unordered_set<int> us;
    lint cnx=0;
    cir(i,0,cnum){
        cnx+=b[n1[i]];
        us.insert(n1[i]);
    }
    int p1=cnum-1,p2=0;
    while(cnx<aa){
        while(us.count(n2[p2])) ++p2;
        while(b[n1[p1]]>b[n2[p2]]) --p1;
        us.erase(n1[p1]);
        us.insert(n2[p2]);
        cnx-=b[n1[p1]];cnx+=b[n2[p2]];
        --p1,++p2;
    }
    cout<<cnum<<'\n';
    for(auto&i:us) cout<<i+1<<' ';
    cout<<'\n';
    return 0;
}
