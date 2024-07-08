#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace __gnu_pbds;
using namespace std;
template<typename T,class comp=less<T>>
using heap=__gnu_pbds::priority_queue<
    T,comp,pairing_heap_tag>;
struct dsu{
    vector<int> F;
    int findset(int x){
        return x==F[x]?x:F[x]=findset(F[x]);}
    void merge(int x,int y){
        F[findset(x)]=findset(y);}
    void new_node(){F.push_back(F.size());}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;dsu ds;ds.new_node();
    vector<heap<int>> b(1);
    auto ckn=[&](int x){return b[x].empty()?-1:b[x].top();};
    vector<bool> del(1);map<int,int> idx;
    auto poping=[&](int pos){
        while((!b[pos].empty())&&del[idx[b[pos].top()]])
            b[pos].pop();
    };
    while(n--){
        int op;cin>>op;
        if(op==1){
            int v;cin>>v;ds.new_node();
            heap<int> bk;bk.push(v);
            b.push_back(bk);idx[v]=del.size();
            del.push_back(false);
        }else if(op==2){
            int x,y;cin>>x>>y;
            auto i1=ds.findset(x),i2=ds.findset(y);
            if(del[x]&&del[y]){cout<<"-1\n";continue;}
            if(del[x]||del[y]||i1==i2){
                cout<<(del[x]?ckn(i2):ckn(i1))<<'\n';
                continue;
            }
            ds.merge(i1,i2);
            b[i2].join(b[i1]);b[i1].clear();
            poping(i2);
            cout<<ckn(i2)<<'\n';
        }else{
            int x;cin>>x;
            if(del[x]){cout<<"-1\n";continue;}
            auto fx=ds.findset(x);
            poping(fx);
            if(!(b[fx].empty()))
                del[idx[b[fx].top()]]=true,b[fx].pop();
            cout<<ckn(fx)<<'\n';
        }
    }
    return 0;
}
