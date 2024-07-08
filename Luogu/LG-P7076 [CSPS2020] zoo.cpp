#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
typedef long long lint;
inline lint lowbit(lint&x){return x&-x;}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,c,k;cin>>n>>m>>c>>k;
    unordered_set<int> al,gots;
    cir(i,0,k) al.insert(i);
    cir(i,0,n){
        lint li;cin>>li;
        cir(j,0,64) if(li&(1LL<<j)){gots.insert(j);}
    }
    cir(i,0,m){
        int pi,qi;cin>>pi>>qi;
        if(!gots.count(pi)) al.erase(pi);
    }
    cout<<(1LL<<(al.size()))-n<<endl;
    return 0;
}