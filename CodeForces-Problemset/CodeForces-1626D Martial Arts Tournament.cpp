#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr int mxa=2*1e5+7;
static constexpr int _inf=1e9+7;
class init_io{
public:
    init_io(){
        ios::sync_with_stdio(false),cin.tie(0);
    }
} in_use;
class getans{
private:
    int clc(int x){
        int res=1;
        while(res<x) res*=2;
        return res;
    }
    vector<int> pre;
    void rdnums(int n){
        pre.clear();pre.resize(n+1);
        cir(i,0,n){
            int x;cin>>x;++pre[x];
        }
        cir(i,1,n+1) pre[i]+=pre[i-1];
    }
    int ckans(int n){
        int res=_inf;
        for(int i=1;i<n+1;i*=2){
            for(int j=1;j<n+1;j*=2){
                int p1=upper_bound(pre.begin(),
                    pre.end(),i)-pre.begin()-1;
                int p2=upper_bound(pre.begin(),
                    pre.end(),j+pre[p1])-pre.begin()-1;
                res=min(res,i+j+clc(n-pre[p2])-n);
            }
        }
        return res;
    }
    void slvrnd(){
        int n;cin>>n;rdnums(n);
        cout<<ckans(n)<<'\n';
    }
public:
    getans(){
        int T;cin>>T;
        while(T--) slvrnd();
    }
} entry;
int main(){
    
}
