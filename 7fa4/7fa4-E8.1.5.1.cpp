#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class generater{
private:
    unsigned x;
public:
    template<typename _Ty,typename... Args>
    auto read(_Ty&rdx){
        x^=(x<<13);
        x^=(x>>17);
        x^=(x<<5);
        rdx=x;
    }
    template<typename _Ty,typename... _Args>
    auto read(_Ty&rdx,_Args&... args)->void{
        read(rdx);read(args...);
    }
    generater(unsigned seed):x(seed){}
};
class tree{
private:
    static constexpr auto ups=25;
    vector<vector<int>> gr,up,dw,upq;
    vector<int> hx,dep,ndtop,nhx;
    auto init(int u,int f=-1)->int{
        dep[u]=(f>-1?dep[f]:-1)+1;upq[u][0]=max(f,0);
        cir(i,1,ups) upq[u][i]=upq[upq[u][i-1]][i-1];
        for(auto&i:gr[u]) if(i!=f)
            hx[u]=max(hx[u],init(i,u)+1);
        if(f>-1) gr[u].erase(find(gr[u].begin(),gr[u].end(),f));
        return hx[u];
    }
    auto dfs(int u,int nh=-1,int top=-1,vector<int>*chs=nullptr){
        if(!chs){
            auto ux=u;top=u;
            cir(i,0,hx[u]+7){
                up[u].push_back(ux);ux=upq[ux][0];
            }
            chs=&dw[u];
        }
        ndtop[u]=top;++nh;nhx[u]=nh;
        chs->push_back(u);
        if(gr[u].empty()) return;
        nth_element(gr[u].begin(),gr[u].begin(),gr[u].end(),
            [&](auto&a,auto&b){return hx[a]>hx[b];});
        dfs(gr[u][0],nh,top,chs);
        for(auto&i:gr[u]) if(i!=gr[u][0]) dfs(i);
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto init(){init(0);dfs(0);}
    auto depth(int u){return dep[u];}
    auto kthf(int u,int k){
        if(!k) return u;
        const auto lgk=sizeof(int)*8-1-__builtin_clz(k);
        auto jmp=k-(1<<lgk);
        const auto qx=upq[u][lgk];
        const auto tpx=ndtop[qx];
        jmp-=nhx[qx];
        if(jmp<0) return dw[tpx][-jmp];
        return up[tpx][jmp];
    }
    tree(int _n):gr(_n),up(_n),dw(_n),ndtop(_n),
        nhx(_n),upq(_n,vector<int>(ups)),hx(_n),dep(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;unsigned s;cin>>n>>q>>s;
    tree gr(n+1);generater inf(s);
    cir(u,1,n+1){
        int f;cin>>f;gr.insert(u,f);
    }
    gr.init();auto ans=0ll,las=0ll;
    cir(i,0,q){
        unsigned u,k;inf.read(u,k);
        ((u^=las)%=n)+=1;(k^=las)%=gr.depth(u);
        ans^=((las=gr.kthf(u,k))*(i+1));
    }
    cout<<ans<<'\n';
    return 0;
}
