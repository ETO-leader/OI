#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
template<typename T,class comp=less<T>>
using rbt=tree<T,null_type,comp,rb_tree_tag,
    tree_order_statistics_node_update>;
struct query{int l,r,id;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q,idcnt=0;cin>>n>>q;
    deque<query> Q(q);map<int,int> Ans,Ap;
    rbt<int,greater<int>> rb;
    vector<int> col(n);
    for(auto&i:col) cin>>i;
    for(auto&i:Q) cin>>i.l>>i.r,i.id=idcnt++;
    sort(Q.begin(),Q.end(),
        [](query&a,query&b){return a.r<b.r;});
    cir(i,0,n){
        if(Ap.count(col[i])) rb.erase(Ap[col[i]]);
        rb.insert(i);Ap[col[i]]=i;
        while(!Q.empty()&&Q.front().r-1==i){
            auto f=Q.front();Q.pop_front();
            Ans[f.id]=rb.order_of_key(f.l-2);
        }
    }
    for(auto&i:Ans) cout<<i.second<<'\n';
    return 0;
}