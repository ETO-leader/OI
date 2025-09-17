#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("recall.in");
ofstream ouf("recall.out");
using lint=unsigned long long;
static constexpr auto MOD=998244353;
class tree{
private:
    vector<vector<int>> gr;
    vector<int> hx,nsmx,dep,mxdep;
    auto dfs(int u,int f=0)->int{
        hx[u]=1;dep[u]=mxdep[u]=dep[f]+1;
        for(auto&i:gr[u]) if(i!=f){
            hx[u]=max(hx[u],dfs(i,u)+1);
            mxdep[u]=max(mxdep[u],mxdep[i]);
        }
        return hx[u];
    }
    auto getnodes(int u,vector<int>&a,int f=0)->void{
        auto mx=0,smx=0;
        for(auto&i:gr[u]) if(i!=f){
            if(mxdep[i]>mx) swap(mx,smx),mx=mxdep[i];
            else if(mxdep[i]>smx) smx=mxdep[i];
        }
        nsmx[u]=smx;
        a.push_back(u);
        for(auto&i:gr[u]) if(i!=f&&mxdep[i]==mx){
            getnodes(i,a,u);
            break;
        }
    }
    auto init_c(int n,int m){
        array<array<lint,207>,207> c;
        c[0][0]=1;
        cir(i,1,n) cir(j,0,m){
            c[i][j]=c[i-1][j];
            if(j) (c[i][j]+=c[i-1][j-1])%=MOD;
        }
        return c;
    }
    auto dp(vector<int> px){
        array<array<array<lint,107>,207>,307> f;
        memset(f.begin(),0,sizeof(f));
        const auto h=(int)(px.size());
        const auto C=init_c(h+7,h+7);
        cir(i,1,h) cir(cnt,0,h+1) f[i][i-1][cnt]=1;
        cir(len,1,h+1) cir(l,0,h-len+1){
            const auto r=l+len-1;
            cir(cnt,0,hx[px[l]]+1){
                auto premd=nsmx[px[l]]-cnt-1;
                cir(m,l+1,r+1){
                    premd=max(premd,nsmx[px[m-1]]-cnt-1);
                    if(premd-m>r-m-1) break;
                    auto adcnt=max(premd-m+1,0);
                    for(;adcnt+8<r-m+1;adcnt+=8){
                        if(cnt+adcnt+1>h) break;
                        (f[l][r][cnt]+=
                            f[l][m-1][cnt+adcnt]*             //断开后 m 左边的方案数
                            f[m][r-adcnt-1][cnt+adcnt+1]%MOD* //断开后 m 及 m 右边的方案数
                            C[r-l+1-adcnt-1][m-l]             //分配
                        );
                        (f[l][r][cnt]+=
                            f[l][m-1][cnt+adcnt+1]*             //断开后 m 左边的方案数
                            f[m][r-adcnt-2][cnt+adcnt+2]%MOD* //断开后 m 及 m 右边的方案数
                            C[r-l+1-adcnt-2][m-l]             //分配
                        );
                        (f[l][r][cnt]+=
                            f[l][m-1][cnt+adcnt+2]*           //断开后 m 左边的方案数
                            f[m][r-adcnt-3][cnt+adcnt+3]%MOD* //断开后 m 及 m 右边的方案数
                            C[r-l+1-adcnt-3][m-l]             //分配
                        );
                        (f[l][r][cnt]+=
                            f[l][m-1][cnt+adcnt+3]*           //断开后 m 左边的方案数
                            f[m][r-adcnt-4][cnt+adcnt+4]%MOD* //断开后 m 及 m 右边的方案数
                            C[r-l+1-adcnt-4][m-l]             //分配
                        );
                        if(cnt+adcnt+5>h) break;
                        (f[l][r][cnt]+=
                            f[l][m-1][cnt+adcnt+4]*           //断开后 m 左边的方案数
                            f[m][r-adcnt-5][cnt+adcnt+5]%MOD* //断开后 m 及 m 右边的方案数
                            C[r-l+1-adcnt-5][m-l]             //分配
                        );
                        (f[l][r][cnt]+=
                            f[l][m-1][cnt+adcnt+5]*           //断开后 m 左边的方案数
                            f[m][r-adcnt-6][cnt+adcnt+6]%MOD* //断开后 m 及 m 右边的方案数
                            C[r-l+1-adcnt-6][m-l]             //分配
                        );
                        (f[l][r][cnt]+=
                            f[l][m-1][cnt+adcnt+6]*           //断开后 m 左边的方案数
                            f[m][r-adcnt-7][cnt+adcnt+7]%MOD* //断开后 m 及 m 右边的方案数
                            C[r-l+1-adcnt-7][m-l]             //分配
                        );
                        (f[l][r][cnt]+=
                            f[l][m-1][cnt+adcnt+7]*           //断开后 m 左边的方案数
                            f[m][r-adcnt-8][cnt+adcnt+8]%MOD* //断开后 m 及 m 右边的方案数
                            C[r-l+1-adcnt-8][m-l]             //分配
                        );
                        f[l][r][cnt]%=MOD;
                    }
                    if(adcnt+4<r-m+1&&cnt+adcnt<h){
                        (f[l][r][cnt]+=
                            f[l][m-1][cnt+adcnt]*             //断开后 m 左边的方案数
                            f[m][r-adcnt-1][cnt+adcnt+1]%MOD* //断开后 m 及 m 右边的方案数
                            C[r-l+1-adcnt-1][m-l]             //分配
                        );
                        (f[l][r][cnt]+=
                            f[l][m-1][cnt+adcnt+1]*           //断开后 m 左边的方案数
                            f[m][r-adcnt-2][cnt+adcnt+2]%MOD* //断开后 m 及 m 右边的方案数
                            C[r-l+1-adcnt-2][m-l]             //分配
                        );
                        (f[l][r][cnt]+=
                            f[l][m-1][cnt+adcnt+2]*           //断开后 m 左边的方案数
                            f[m][r-adcnt-3][cnt+adcnt+3]%MOD* //断开后 m 及 m 右边的方案数
                            C[r-l+1-adcnt-3][m-l]             //分配
                        );
                        (f[l][r][cnt]+=
                            f[l][m-1][cnt+adcnt+3]*           //断开后 m 左边的方案数
                            f[m][r-adcnt-4][cnt+adcnt+4]%MOD* //断开后 m 及 m 右边的方案数
                            C[r-l+1-adcnt-4][m-l]             //分配
                        );
                        adcnt+=4;
                    }
                    for(;adcnt<r-m+1;++adcnt){
                        if(cnt+adcnt+1>h) break;
                        (f[l][r][cnt]+=
                            f[l][m-1][cnt+adcnt]*             //断开后 m 左边的方案数
                            f[m][r-adcnt-1][cnt+adcnt+1]%MOD* //断开后 m 及 m 右边的方案数
                            C[r-l+1-adcnt-1][m-l]             //分配
                        );
                    }
                    f[l][r][cnt]%=MOD;
                }
                ++f[l][r][cnt];                               //直接扫完
            }
        }
        return make_pair(hx[1],f[0][h-1][0]);
    }
public:
    auto emplace(int u,int v){
        // cerr<<gr.size()<<' '<<u<<' '<<v<<'\n';
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto check(){
        dfs(1);
        vector<int> px;getnodes(1,px);
        assert(px.size()<101);
        return dp(px);
    }
    tree(int n):gr(n+1),hx(n+1),nsmx(n+1),dep(n+1),mxdep(n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int c,T;inf>>c>>T;
    while(T--) []{
        int n;inf>>n;tree gr(n);
        cir(i,0,n-1){
            int u,v;inf>>u>>v;
            gr.emplace(u,v);
        }
        auto[ans,cnt]=gr.check();
        ouf<<ans<<' '<<cnt<<'\n';
    }();
    return 0;
}

