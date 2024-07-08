#include"headb"

int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;
    int ans=0;VI a(n);
    function<void(int)> dfs=[&](int p){
        if(p==n){
            /*if(check(n,a)==n){
                for(auto&i:a) clog<<i<<' ';
                clog<<'\n';
            }*/
            return ans+=(check(n,k,a)==n),void();
        }
        cir(i,1,k+1) a[p]=i,dfs(p+1);
    };
    dfs(0);
    cout<<ans<<'\n';
    return 0;
}