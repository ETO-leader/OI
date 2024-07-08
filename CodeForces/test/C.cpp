#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
constexpr auto ls(int u){return u*2;}
constexpr auto rs(int u){return u*2+1;}
vector<int> from,ans;
auto ask(int l,int r){
    cout<<"? "<<l<<' '<<r<<'\n';
    cout.flush();
    char record;cin>>record;
    return record=='>';
}
auto tell(int a,int b){
    cout<<"! "<<a<<' '<<b<<'\n';
    cout.flush();
}
auto dfs(int u,int l,int r){
    if(l==r) return ans[u]=l;
    const auto mid=(l+r)/2;
    auto lx=dfs(ls(u),l,mid),rx=dfs(rs(u),mid+1,r);
    if(ask(lx,rx)){
        from[u]=false;
        return ans[u]=lx;
    }
    from[u]=true;
    return ans[u]=rx;
}
auto check(int u,int l,int r)->int{
    if(l==r) throw exception();
    const auto mid=(l+r)/2;
    if(from[u]){
        try{
            auto ck=check(rs(u),l,mid);
            return ask(ans[ls(u)],ck)?ans[ls(u)]:ck;
        }catch(exception&){
            return ans[ls(u)];
        }
    }
    try{
        auto ck=check(ls(u),l,mid);
        return ask(ans[rs(u)],ck)?ans[rs(u)]:ck;
    }catch(exception&){
        return ans[rs(u)];
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    from.resize(n<<2);ans.resize(n<<2);
    const auto a1=dfs(1,1,n),a2=check(1,1,n);
    tell(a1,a2);
    return 0;
}