#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct treenode{
    int r,id;
    bool operator<(const treenode&p) const{
        return r>p.r;
    }
};
const int maxr=2e5+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;
    multiset<treenode> tr;
    vector<vector<treenode>> tn(maxr);
    cir(i,0,n){
        int l,r;cin>>l>>r;
        tn[l].push_back({r,i+1});
    }
    vector<int> ans;
    cir(i,0,maxr){
        for(auto&x:tn[i]) tr.insert(x);
        while(tr.size()>k){
            ans.push_back(tr.begin()->id);
            tr.erase(tr.begin());
        }
        while((!tr.empty())&&(tr.rbegin()->r==i)){
            tr.erase(--tr.end());
        }
    }
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<'\n';
    for(auto&i:ans) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
