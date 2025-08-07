#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e8+7);
class terinfo:public vector<int>{
public:
    using vector<int>::vector;
    auto vaild() const{
        auto cnt=0;
        cir(i,0,(this->size())){
            cnt+=((*this)[i]==1?1:((*this)[i]==2?-1:0));
            if(cnt<0) return false;
        } 
        return true;
    }
    auto value() const{
        auto res=0;
        for(auto&i:(*this)) (res*=3)+=i;
        return res;
    }
    terinfo(int x,int n){
        cir(i,0,n) this->emplace_back(x%3),x/=3;
        reverse(this->begin(),this->end());
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<vector<int>> ban(n,vector<int>(m));
    int b;cin>>b;
    cir(i,0,b){
        int x,y;cin>>x>>y;--x;--y;
        ban[x][y]=true;
    }
    vector<int> vaild;
    cir(s,0,(int)(roundl(pow(3,m+1)))) if(terinfo(s,m+1).vaild()) vaild.emplace_back(s);
    vector<vector<lint>> f(2,vector<lint>((int)(roundl(pow(3,m+1)))));
    auto p=0;
    f[p][0]=1;
    vector<vector<lint>> ans(n,vector<lint>(m));
    cir(i,0,n) cir(j,0,m){
        for(auto&s:vaild) if(f[p][s]){
            auto ns=terinfo(s,m+1);
            if(!j) ns.emplace(ns.begin(),ns.back()),ns.pop_back();
            const auto lplug=ns[j];
            const auto uplug=ns[j+1];
            if((lplug||uplug)&&(ban[i][j])) continue;
            if((!j)&&lplug) continue;
            if(lplug==2&&uplug==1){
                ns[j]=ns[j+1]=0;
                (f[p^1][ns.value()]+=f[p][s])%=MOD;
            }else if(lplug&&(!uplug)){
                (f[p^1][ns.value()]+=f[p][s])%=MOD;
                swap(ns[j],ns[j+1]);
                (f[p^1][ns.value()]+=f[p][s])%=MOD;
            }else if(uplug&&(!lplug)){
                (f[p^1][ns.value()]+=f[p][s])%=MOD;
                swap(ns[j],ns[j+1]);
                (f[p^1][ns.value()]+=f[p][s])%=MOD;
            }else if(lplug==1&&uplug==2){
                ns[j]=ns[j+1]=0;
                if(!ns.value()) (ans[i][j]+=f[p][s])%=MOD;
            }else if(lplug==1&&uplug==1){
                auto up=j+1;
                auto w=0;
                cir(x,up,m+1){
                    w+=(ns[x]==1?1:(ns[x]==2?-1:0));
                    if(!w){
                        up=x;break;
                    }
                }
                ns[j]=ns[j+1]=0;
                ns[up]=1;
                (f[p^1][ns.value()]+=f[p][s])%=MOD;
            }else if(lplug==2&&uplug==2){
                auto up=j;
                auto w=0;
                for(auto x=up;~x;--x){
                    w+=(ns[x]==1?1:(ns[x]==2?-1:0));
                    if(!w){
                        up=x;break;
                    }
                }
                ns[j]=ns[j+1]=0;
                ns[up]=2;
                (f[p^1][ns.value()]+=f[p][s])%=MOD;
            }else if((!ban[i][j])&&(!lplug)&&(!uplug)){
                ns[j]=1;ns[j+1]=2;
                (f[p^1][ns.value()]+=f[p][s])%=MOD;
            }else if(ban[i][j]){
                (f[p^1][ns.value()]+=f[p][s])%=MOD;
            }
        }
        fill(f[p].begin(),f[p].end(),0);
        p^=true;
    }
    auto uans=0;
    [&]{
        for(auto i=n-1;~i;--i) for(auto j=m-1;~j;--j){
            if(!ban[i][j]){
                uans=ans[i][j];
                return;
            }
        }
    }();
    cout<<uans<<'\n';
    return 0;
}
