#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#ifdef __DEBUG__
    ofstream cerrf("error-stream.err");
    #define cerr cerrf
    #define clog cerrf
#endif
#ifdef __SPEED_TEST__
    int checkcnt=0;
#endif
static constexpr int maxsiz=2e5+7;
/*class trie{
private:
    vector<vector<int>> tr;
    vector<int> visc,edc;
    auto vecint(int x) const{
        vector<int> res;
        cir(i,0,22) res.push_back(x&1),x>>=1;
        reverse(res.begin(),res.end());
        return res;
    }
    int cnt;
    auto allocm(){
        return visc.push_back(0),
            edc.push_back(0),tr.push_back({0,0}),++cnt;
    }
    auto getints(int u,vector<int>&a,int pre)->void{
        cir(i,0,edc[u]) a.push_back(pre);
        if(tr[u][0]) getints(tr[u][0],a,(pre<<1));
        if(tr[u][1]) getints(tr[u][1],a,((pre<<1)|1));
    }
public:
    auto insert(const int a){
        const auto ins=vecint(a);
        int u=0;
        for(auto&i:ins){
            ++visc[u=(tr[u][i]?tr[u][i]:(tr[u][i]=allocm()))];
        }
        ++edc[u];
    }
    auto remove(const int a){
        //const auto rmv=vecint(a);
        int u=0;
        /*for(auto&i:rmv){
            if(!tr[u][i]) return cerr<<"WARNING: REMOVE A UNAPPEARED ELEMENT.\n",void();
            --visc[u=tr[u][i]];
        }
        --edc[u];
    }
    auto find(const int a){
        if(!cnt) return -1;
        //const auto fnd=vecint(a);
        int u=0,res=0;
        /*for(auto&i:fnd){
            const auto nxt=(tr[u][i^1])&&visc[tr[u][i^1]]?i^1:i;
//            cout<<i<<' '<<nxt<<' '<<tr.count({u,i^1})<<' '<<(tr.count({u,i^1})?visc[tr[{u,i^1}]]:-1)<<"       ";
            (res<<=1)|=(i^nxt);
            if(!tr[u][nxt]) return cerr<<"WARNING: VISIT A UNAPPEARED ELEMENT.\n",-1;
            u=tr[u][nxt];
        }
//        cout<<'\n';
        return res;
    }
    auto getints(){
        vector<int> res;getints(0,res,0);
        return res;
    }
    auto clear(){
        tr.clear();visc.clear();edc.clear();
        visc.reserve(100);tr.reserve(100);edc.reserve(100);
        visc.push_back(0);edc.push_back(0);cnt=0;
        tr.push_back({0,0});
    }
    trie():visc(1),edc(1),tr(1,{0,0}),cnt(0){}
};*/
namespace trie{
    array<array<int,2>,(maxsiz*90)> tr;
    array<int,(maxsiz*90)> apr,edc;
    stack<int> use;
    int cnt;
    inline auto allocm(){
        if(use.empty()) return cnt++;
        //cerr<<cnt<<' '<<use.size()<<' '<<tr.size()<<'\n';
        auto res=use.top();use.pop();
        apr[res]=0;edc[res]=0;tr[res]={0,0};
        return res;
    }
    class trie{
    private:
        unordered_set<int> nds;
        int root;
        auto getints(int u,vector<int>&a,int pre)->void{
            cir(i,0,edc[u]) a.push_back(pre);
            if(tr[u][0]) getints(tr[u][0],a,pre<<1);
            if(tr[u][1]) getints(tr[u][1],a,(pre<<1)|1);
        }
    public:
        auto insert(const int x){
            int u=root;
            for(int i=19;~i;--i){
                const auto wi=(x>>i)&1;
                if(!tr[u][wi]) nds.insert(tr[u][wi]=allocm());
                ++apr[u=tr[u][wi]];
            }
            ++edc[u];
        }
        auto remove(const int x){
            int u=root;
            stack<int> stc;
            for(int i=19;~i;--i){
                const auto wi=(x>>i)&1;
                stc.push(u);
                --apr[u=tr[u][wi]];
            }
            --edc[u];
            while(!stc.empty()){
                auto ux=stc.top();stc.pop();
                if((tr[ux][0])&&(!apr[tr[ux][0]])){
                    use.push(tr[ux][0]);
                    nds.erase(tr[ux][0]);
                    tr[ux][0]=0;
                }
                if((tr[ux][1])&&(!apr[tr[ux][1]])){
                    use.push(tr[ux][1]);
                    nds.erase(tr[ux][1]);
                    tr[ux][1]=0;
                }
            }
        }
        auto find(const int x){
            int u=root,res=0;
            if(!(tr[u][0]||tr[u][1])) return -1;
            for(int i=19;~i;--i){
                const auto wi=(x>>i)&1;
                u=apr[tr[u][wi^1]]?(((res<<=1)|=1),
                    tr[u][wi^1]):((res<<=1),tr[u][wi]);
            }
            return res;
        }
        auto getints(){
            vector<int> res;getints(root,res,0);
            return res;
        }
        auto clear(){
            for(auto&i:nds) use.push(i);
            nds=unordered_set<int>();root=allocm();
        }
        trie(){root=allocm();}
    };
}
template<int maxmem>
class bst{
private:
#ifndef __DEBUG__
    static constexpr auto alpha=0.93;
#else
    static constexpr auto alpha=1.05;
#endif
    struct node{
        node*ls,*rs;
        int siz,val;
        trie::trie tr;bool deleted;
        auto check(){
            return ls->siz*1.0/siz>alpha||
                rs->siz*1.0/siz>alpha;
        }
        auto maintain(){siz=ls->siz+rs->siz+(!deleted);}
        auto update(){
            tr.clear();
            if(!deleted) tr.insert(val);
            auto expls=ls->tr.getints(),exprs=rs->tr.getints();
            for(auto&i:expls) tr.insert(i);
            for(auto&i:exprs) tr.insert(i);
        }
        node():ls(nullptr),rs(nullptr),
            siz(1),val(0),deleted(false){}
    };
    constexpr auto midpnt(int a,int b){return (a+b)/2;}
    node*null,*root;int cnt;
    array<node,maxmem> mem;
    auto allocm(){return&mem[++cnt];}
    auto newnode(int val){
        auto res=allocm();res->val=val;
        res->ls=null;res->rs=null;res->tr.insert(val);
        return res;
    }
    auto clear(node*u){
        u->ls=null;u->rs=null;u->tr.clear();
        return u;
    }
    vector<node*> rb;
    auto rebuild(int l,int r){
        if(l>r) return null;
        const auto midp=midpnt(l,r);
        auto res=rb[midp];
        res->ls=rebuild(l,midp-1);
        res->rs=rebuild(midp+1,r);
        return res->maintain(),res->update(),res;
    }
    auto destroy(node*u){
        if(u==null) return;
        auto uls=u->ls,urs=u->rs;
        destroy(uls);
        rb.push_back(clear(u));
#ifdef __DEBUG__
        if(u->val==6) clog<<"LEFT SON VALUE: "<<urs->val<<" NULL VALUE: "<<null->val<<'\n';
#endif
        destroy(urs);
    }
    int rbdcnt=0;
    auto rebuild(node*u){
        //cerr<<"REBUILD:"<<++rbdcnt<<'\n';
        rb.clear();destroy(u);
#ifdef __DEBUG__
        clog<<"node: "<<u->val<<"  size="<<rb.size()<<'\n';
#endif
        return rebuild(0,(int)(rb.size())-1);
    }
    auto insert(node*&u,int rk,int k){
        if(u==null) return u=newnode(k);
        u->tr.insert(k);
        auto res=rk<u->ls->siz+1?insert(u->ls,rk,k):
            insert(u->rs,rk-u->ls->siz-(!u->deleted),k);
        u->maintain();
        if(u->check()) u=rebuild(u);
        return u->maintain(),res;
    }
    auto remove(node*u,int rk,int k){
        if(u==null) return false;
        u->tr.remove(k);
        if((!u->deleted)&&u->ls->siz+1==rk){
            return --u->siz,u->deleted=true;
        }
        auto res=rk<u->ls->siz+1?remove(u->ls,rk,k):
            remove(u->rs,rk-u->ls->siz-(!u->deleted),k);
        return u->maintain(),res;
    }
    auto check(node*u,int lrk,int rrk,int a){
#ifdef __SPEED_TEST__
        ++checkcnt;
#endif
        if(u==null) return -1;
#ifdef __DEBUG__
        clog<<u->val<<'\n';
#endif
        if(lrk<2&&u->siz<rrk+1) return /*u->update(),*/u->tr.find(a);
        if(rrk<1||lrk>u->siz) return -1;
        int nx=((!u->deleted)&&lrk<u->ls->siz+2&&
            u->ls->siz<rrk?(a^u->val):(-1));
        return max({check(u->ls,lrk,rrk,a),check(u->rs,
            lrk-u->ls->siz-(!u->deleted),
            rrk-u->ls->siz-(!u->deleted),a),nx});
    }
public:
#ifdef __DEBUG__
    auto print(node*u,int sum){
        string s;
        cir(i,0,sum) s+="    ";
        if(u==null) return clog<<s<<"null\n",void();
        clog<<s<<u->val<<" rank="<<u->siz<<" deleted="<<(u->deleted?"true":"false")<<" trie elements: [";
        auto exp=u->tr.getints();int cnt=0;
        for(auto&i:exp) clog<<i<<((++cnt)==exp.size()?"":",");
        clog<<"]\n"<<s<<"ls{\n";
        print(u->ls,sum+1);
        clog<<s<<"}\n"<<s<<"rs{\n";
        print(u->rs,sum+1);
        clog<<s<<"}\n";
    }
    auto prt(){
        print(root,0);
    }
#endif
    using iterator=node*;
    auto insert(int rk,int k){
        return insert(root,rk,k);
    }
    auto remove(int rk,int k){
        return remove(root,rk,k);
    }
    auto check(int l,int r,int x){
        return check(root,l,r,x);
    }
    bst():cnt(0){null=&mem[0];root=null;null->siz=0;}
};
template<int maxmem>
class treap{
private:
    mt19937_64 rnd;
    random_device rd;
    struct node{
        node*ls,*rs;
        pair<int,int> num;
        int val;int siz;
        auto maintain(){
            auto[a,b]=ls->num;
            auto[x,y]=rs->num;
            vector<int> arr={a,b,x,y,val};
            sort(arr.begin(),arr.end(),greater<int>());
            num={arr[0],arr[1]};
            siz=ls->siz+rs->siz+1;
        }
        node():num(-1,-1),val(-1),
            siz(1),ls(nullptr),rs(nullptr){}
    };
    array<node,maxmem> mem;int cnt;
    auto allocm(){return&mem[++cnt];}
    auto newnode(int val){
        auto res=allocm();res->ls=res->rs=null;
        return res->val=val,res->maintain(),res;
    }
    node*null,*root;
    auto split(node*u,int rk){
        if(u==null) return pair(null,null);
        if(u->ls->siz<rk){
            auto[ux,vx]=split(u->rs,rk-u->ls->siz-1);
            u->rs=ux;
            return u->maintain(),pair(u,vx);
        }else{
            auto[ux,vx]=split(u->ls,rk);
            u->ls=vx;
            return u->maintain(),pair(ux,u);
        }
    }
    auto merge(node*u,node*v){
        if(u==null) return v;
        if(v==null) return u;
        if((rnd()%(u->siz+v->siz))<u->siz){
            u->rs=merge(u->rs,v);
            return u->maintain(),u;
        }else{
            v->ls=merge(u,v->ls);
            return v->maintain(),v;
        }
    }
public:
    auto insert(int rk,int a){
        auto[ux,vx]=split(root,rk);
        root=merge(ux,merge(newnode(a),vx));
    }
    auto remove(int rk){
        auto[ux,qx]=split(root,rk-1);
        auto[rm,vx]=split(qx,1);
        root=merge(ux,vx);
    }
    auto query(int l,int r){
        auto[ux,qx]=split(root,l-1);
        auto[qy,vx]=split(qx,r-l+1);
        auto res=qy->num.second;
        //cerr<<"query: "<<qy->siz<<":"<<r-l+1<<'\n';
        root=merge(ux,merge(qy,vx));
        return res;
    }
    treap():cnt(0),rd(){
        null=&mem[0];root=null;null->siz=0;
        #ifndef __DEBUG__
            rnd=mt19937_64(rd());
        #else
            rnd=mt19937_64(114514);
        #endif
    }
};
#ifdef __DEBUG__
    #undef cerr
    #undef clog
#endif
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;
    bst<maxsiz*12> b;treap<maxsiz*12> tr;
    __gnu_cxx::rope<int> arr;
    cir(i,0,n){
        int x;cin>>x;arr.append(x);
    }
    cir(i,0,n) tr.insert(i,arr[i]);
    __gnu_pbds::tree<int,__gnu_pbds::null_type,less<int>,
        __gnu_pbds::rb_tree_tag,
        __gnu_pbds::tree_order_statistics_node_update> pre;
    vector<int> order(n);iota(order.begin(),order.end(),0);
    random_device rd;mt19937 rnd(rd());
    shuffle(order.begin(),order.end(),rnd);
    for(auto&i:order){
        b.insert(pre.order_of_key(i),arr[i]);
        pre.insert(i);
    }
    int lastans=0;
    constexpr auto mod=(1<<20);
    cir(i,0,q){
        string s;cin>>s;
        if(s[0]=='I'){
            int x,y;cin>>x>>y;
            (x+=lastans)%=arr.size();
            (y+=lastans)%=mod;
            tr.insert(x,y);
            b.insert(x,y);
            arr.insert(x,y);
        }else if(s[0]=='D'){
            int x;cin>>x;
            (x+=lastans)%=arr.size();
            tr.remove(x+1);
            b.remove(x+1,arr[x]);
            arr.erase(x,1);
        }else if(s[0]=='C'){
            int x,y;cin>>x>>y;
            (x+=lastans)%=arr.size();
            (y+=lastans)%=mod;
            tr.remove(x+1);
            b.remove(x+1,arr[x]);
            arr.erase(x,1);
            tr.insert(x,y);
            b.insert(x,y);
            arr.insert(x,y);
        }else{
            int l,r;cin>>l>>r;
            (l+=lastans)%=arr.size();
            (r+=lastans)%=arr.size();
            if(l>r) swap(l,r);
        //    clog<<tr.query(l+1,r+1)<<'\n';
        //    cerr<<((lastans=b.check(l+1,r+1,
        //        tr.query(l+1,r+1)))^tr.query(l+1,r+1))<<' '<<l<<' '<<r<<'\n';
        #ifdef __SPEED_TEST__
            checkcnt=0;
        #endif
            cout<<(lastans=b.check(l+1,r+1,
                tr.query(l+1,r+1)))<<'\n'<<flush;
        #ifdef __SPEED_TEST__
            cerr<<"Running Time="<<checkcnt<<'\n';
        #endif
        }
#ifdef __DEBUG__
        clog<<i<<":\n";
        b.prt();
        clog<<"\n";
        for(const auto&i:arr) clog<<i<<' ';
        clog<<"\n\n";
#endif
    }
    return 0;
}
