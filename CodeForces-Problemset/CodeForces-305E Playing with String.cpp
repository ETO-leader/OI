#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class solution{
private:
    vector<int> f,vis;
    string qs;
    auto dfs(int x){
        if(x<1) return 0;
        if(vis[x]) return f[x];
        vis[x]=true;
        vector<int> aps(f.size());
        cir(k,1,x+1){
            const auto fxor=dfs(k-2)^dfs(x-k-1);
            aps[fxor]=true;
        }
        while(aps[f[x]]) ++f[x];
        return f[x];
    }
    auto check(string s){
        auto cntq=0,ans=0;
        cir(i,1,(int)(s.size())-1){
            if(s[i-1]==s[i+1]) ++cntq;
            else ans^=dfs(cntq),cntq=0;
        }
        ans^=dfs(cntq);
        return ans;
    }
public:
    auto solve(){
        const auto n=(int)(qs.size());
        if(!check(qs)) return cout<<"Second"<<'\n',void();
        cout<<"First"<<'\n';
        auto ans=-1;
        cir(i,1,n-1){
            if(qs[i-1]==qs[i+1]&&
                (!(check(string(qs.begin(),qs.begin()+i))^
                check(string(qs.begin()+i+1,qs.end()))))){
                ans=i;break;
            }
        }
        cout<<ans+1<<'\n';
    }
    solution(string s):qs(s),f(s.size()+1),vis(s.size()+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string s;cin>>s;
    solution(s).solve();
    return 0;
}
