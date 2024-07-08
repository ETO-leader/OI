#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=51061;
class link_cut_tree{
private:
    struct node{
        lint add,mul,val,sum;
        size_t siz;
        auto updadd(lint x)->void{
            (add+=x)%=MOD;
            (sum+=x*siz)%=MOD;
            (val+=x)%=MOD;
        }
        auto updmul(lint x)->void{
            (add*=x)%=MOD;
            (mul*=x)%=MOD;
            (sum*=x)%=MOD;
            (val*=x)%=MOD;
        }
        node():add(0),mul(1),val(1),sum(1),siz(1){}
    };
    vector<node> tr;
    vector<array<int,2>> ch;
    vector<int> f,rev;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto nrt(int u){return ls(f[u])==u||rs(f[u])==u;}
    auto getch(int u){return rs(f[u])==u;}
    auto push_down(int u){
        if(tr[u].mul!=1){
            tr[ls(u)].updmul(tr[u].mul);
            tr[rs(u)].updmul(tr[u].mul);
        }
        if(tr[u].add){
            if(ls(u)) tr[ls(u)].updadd(tr[u].add);
            if(rs(u)) tr[rs(u)].updadd(tr[u].add);
        }
        if(rev[u]){
            rev[ls(u)]^=true;
            rev[rs(u)]^=true;
            swap(ls(u),rs(u));
        }
        tr[u].add=0;tr[u].mul=1;rev[u]=false;
    }
    auto maintain(int u){
        tr[u].sum=(tr[ls(u)].sum+tr[rs(u)].sum+tr[u].val)%MOD;
        tr[u].siz=(tr[ls(u)].siz+tr[rs(u)].siz+1)%MOD;
    }
    auto rotate(int u){
        const auto fu=f[u],gu=f[fu];
        const auto c=getch(u);
        if(nrt(fu)) ch[gu][getch(fu)]=u;
        f[u]=gu;
        ch[fu][c]=ch[u][!c];f[ch[u][!c]]=fu;
        ch[u][!c]=fu;f[fu]=u;
        maintain(fu);maintain(u);
    }
    auto down(int u)->void{
        if(nrt(u)) down(f[u]);
        push_down(u);
    }
    auto splay(int u){
        for(down(u);nrt(u);rotate(u));
    }
    auto access(int u){
        for(auto v=0;u;u=f[v=u]){
            splay(u);rs(u)=v;
            maintain(u);
        }
    }
    auto mkrt(int u){
        access(u);splay(u);
        rev[u]^=true;push_down(u);
    }
    auto split(int u,int v){
        mkrt(v);access(u);splay(u);
    }
public:
    function<void(int,lint)> addrange=[&](int u,lint w){
        tr[u].updadd(w);
    };
    function<void(int,lint)> mulrange=[&](int u,lint w){
        tr[u].updmul(w);
    };
    function<lint(int,lint)> query=[&](int u,lint w){
        return tr[u].sum;
    };
    auto update(int u,int v,auto f,lint w=0){
        ++u;++v;
        split(u,v);splay(u);
        return f(u,w);
    }
    auto link(int u,int v){
        ++u;++v;
        mkrt(u);mkrt(v);
        f[v]=u;
    }
    auto cut(int u,int v){
        ++u;++v;
        split(u,v);splay(v);
        ls(v)=f[u]=0;
        maintain(v);
    }
    link_cut_tree(int n):tr(n+1),ch(n+1),f(n+1),rev(n+1){
        tr[0].siz=0;tr[0].val=0;tr[0].sum=0;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;link_cut_tree lct(n+1);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        lct.link(u,v);
    }
    cir(i,0,q){
        string op;cin>>op;
        if(op[0]=='+'){
            int u,v,c;cin>>u>>v>>c;
            lct.update(u,v,lct.addrange,c);
        }else if(op[0]=='-'){
            int u,v,ux,vx;cin>>u>>v>>ux>>vx;
            lct.cut(u,v);lct.link(ux,vx);
        }else if(op[0]=='*'){
            int u,v,c;cin>>u>>v>>c;
            lct.update(u,v,lct.mulrange,c);
        }else{
            int u,v;cin>>u>>v;
            cout<<lct.update(u,v,lct.query)<<'\n';
        }
    }
    return 0;
}
