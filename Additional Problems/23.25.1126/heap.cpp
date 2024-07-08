#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("heap.in");
ofstream fcout("heap.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int n,q;fcin>>n>>q;VI a(n);
    map<int,int> id;
    __gnu_pbds::gp_hash_table<int,int> rid;
    for(auto&i:a) fcin>>i,id.insert({i,0});
    [&](){
        int c=0;
        for(auto&[x,y]:id) rid[y=c++]=x;
    }();
    for(auto&i:a) i=id[i];
    while(q--){
        int x,pos=0;fcin>>x;
        VI cntx(id.size());
        cir(i,0,x-1)
            ++cntx[a[i]],pos=max(pos,a[i]);
        int syn=-1;int64_t ans=0;
        cir(i,0,n){
            syn*=-1;
            while(!cntx[pos]) --pos;
            if(i+x-1<n){
                if(a[i+x-1]>pos){
                    ans+=syn*rid[a[i+x-1]];
                    continue;
                }
                ++cntx[a[i+x-1]];
            }
            ans+=syn*rid[pos];--cntx[pos];
        }
        fcout<<ans<<'\n';
    }
    return 0;
}
