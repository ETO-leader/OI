#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class blocks{
private:
    struct node{
        int l,r;lint cnx,cnt1;
        bool alltrue(){return r-l+1==cnt1;}
        int size(){return r-l+1;}
        node(int _l,int _r):l(_l),
            r(_r),cnx(0),cnt1(0){}
    };
    vector<node> blc;
    vector<int> arr,lp,rp,b;
    void initblocks(int n){
        const int sqr=sqrt(n)+1;
        arr.resize(n);b.resize(n);
        lp.resize(n);rp.resize(n);
        for(int l=0;l<n;l+=sqr){
            blc.push_back(node(l,min(l+sqr-1,n-1)));
            cir(i,l,min(l+sqr,n)) b[i]=blc.size()-1;
        }
        cir(i,0,blc.size())
            cir(j,blc[i].l,blc[i].r+1) b[j]=i;
    }
    struct history{
        int b,p;lint cnx;
        int chpr,lr,chpl,ll;
        history(int _b,int _p,lint _cnx):
            b(_b),p(_p),cnx(_cnx),chpr(-1),
            lr(-1),chpl(-1),ll(-1){}
    };
    stack<history> hst;
    //将位置 p 处设为 1 (保证 arr[p]==0)
    void __update(int p){
        auto&[l,r,cnx,cnt1]=blc[b[p]];
        assert(!arr[p]);++cnt1;
        auto psh=history(b[p],p,cnx);
        arr[p]=true;lp[p]=rp[p]=p;
        if(p-1>=l&&arr[p-1]){
            if(l<lp[p-1])
                cnx-=(p-lp[p-1])*(p-lp[p-1]+1)/2;
            psh.chpr=lp[p-1];psh.lr=p-1;
            rp[lp[p-1]]=p;lp[p]=lp[p-1];
        }
        if(p+1<=r&&arr[p+1]){
            if(r>rp[p+1])
                cnx-=(rp[p+1]-p)*(rp[p+1]-p+1)/2;
            psh.chpl=rp[p+1];psh.ll=p+1;
            rp[lp[p]]=rp[p+1];lp[rp[p+1]]=lp[p];
        }
        if(l<lp[p]&&rp[lp[p]]<r){
            cnx+=(rp[lp[p]]-lp[p]+1)*(rp[lp[p]]-lp[p]+2)/2;
        }
        hst.push(psh);
    }
    //暴力统计 [l,r] 区间前缀 1 数量及 val
    //返回值: {前缀 1 数量，val}
    pair<int,lint> calcpt_l(int l,int r){
        int p=l,cnx=0;lint ans=0;
        while(p<=r&&arr[p]) ++cnx,++p;
        while(p<=r){
            if(!arr[p]){
                ++p;continue;
            }
            int lpx=p;p=min(rp[p]+1,r+1);
            ans+=(p-lpx)*(p-lpx+1)/2;
        }
        return {cnx,ans};
    }
    //暴力统计 [l,r] 区间后缀 1 数量及 val
    //返回值: {后缀 1 数量，val}
    pair<int,lint> calcpt_r(int l,int r){
        int p=r,cnx=0;lint ans=0;
        while(p>=l&&arr[p]) ++cnx,--p;
        while(p>=l){
            if(!arr[p]){
                --p;continue;
            }
            int lpx=p;p=max(lp[p]-1,l-1);
            ans+=(lpx-p)*(lpx-p+1)/2;
        }
        return {cnx,ans};
    }
    //暴力计算区间 [l,r] 的答案
    lint bfcalc(int l,int r){
        lint res=0;int lx=l;
        cir(i,l,r+1){
            if(!arr[i]){
                res+=(i-lx)*(i-lx+1)/2;
                lx=i+1;
            }
        }
        if(lx!=r+1) res+=(r-lx+1)*(r-lx+2)/2;
        return res;
    }
    //将 rsize 个 1 与 node n 合并
    //返回新的 rsize 与增加的 ans
    pair<int,lint> __merge(lint rsize,node&n){
        if(n.alltrue())
            return {rsize+n.size(),0LL};
        auto&[l,r,cnx,cnt1]=n;
        const lint llen=arr[l]*(rp[l]-l+1);
        const lint rlen=arr[r]*(r-lp[r]+1);
        lint res=cnx;
        res+=(llen+rsize)*(llen+rsize+1)/2;
        return {rlen,res};
    }
    //计算答案
    lint __query(int l,int r){
        if(b[l]==b[r]) return bfcalc(l,r);
        auto[cnx,res]=calcpt_r(l,blc[b[l]].r);
        cir(i,b[l]+1,b[r]){
            auto[ci,add]=__merge(cnx,blc[i]);
            cnx=ci;res+=add;
        }
        auto[ci,add]=calcpt_l(blc[b[r]].l,r);
        res+=add;res+=1LL*(ci+cnx)*(ci+cnx+1)/2;
        return res;
    }
    void __remoke(){
        auto tp=hst.top();hst.pop();
        arr[tp.p]=false;blc[tp.b].cnx=tp.cnx;
        if(tp.chpl>-1) lp[tp.chpl]=tp.ll;
        if(tp.chpr>-1) rp[tp.chpr]=tp.lr;
        --blc[tp.b].cnt1;
    }
public:
    void update(int p){__update(p);}
    lint operator()(int l,int r){
        return __query(l,r);}
    int operator[](int p){
        return arr[p];
    }
    void remoke(){__remoke();}
    blocks(int _n){initblocks(_n);}
};
struct query{int l,r,x,y,id;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;
    vector<int> v(n),pos(n+1);
    const int sqr=sqrt(n)+1;
    [&](int cnx=0){
        for(auto&i:v) cin>>i,pos[i]=++cnx;
    }();
    vector<vector<query>> qx(n/sqr+1);
    cir(i,0,q){
        int l,r,x,y;cin>>l>>r>>x>>y;
        qx[x/sqr].push_back({l,r,x,y,i});
    }
    vector<lint> ans(q);
    for(auto&i:qx) sort(i.begin(),i.end(),
        [](query&a,query&b){return a.y<b.y;});
    int cnx=0;
    for(auto&i:qx){
        blocks blc(n+1);
        const int rblock=(++cnx)*sqr-1;
        int rx=rblock;
        for(auto&[l,r,x,y,id]:i){
            if(y<rblock){
                cir(p,x,y+1) blc.update(pos[p]);
                ans[id]=blc(l,r);
                cir(p,x,y+1) blc.remoke();
            }else{
                while(rx<y) blc.update(pos[++rx]);
                cir(i,x,rblock+1) blc.update(pos[i]);
                ans[id]=blc(l,r);
                cir(i,x,rblock+1) blc.remoke();
            }
        }
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}