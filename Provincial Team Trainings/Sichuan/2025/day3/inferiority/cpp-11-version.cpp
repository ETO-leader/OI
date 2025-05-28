#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("inferiority.in");
ofstream ouf("inferiority.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
using bdata=array<uint,18>;
bdata&operator+=(bdata&a,bdata b){
    cir(i,0,(int)(a.size())) a[i]+=b[i];
    return a;
}
bdata operator+(bdata a,bdata b){
    return a+=b;
}
bdata operator-(bdata a){
    for(auto&i:a) i=-i;
    return a;
}
template<typename _Ty>
class bit{
private:
    vector<_Ty> a;
    int lowbit(int x) const{return x&(-x);}
public:
    void update(int u,_Ty x){
        for(++u;u<(int)(a.size());u+=lowbit(u)) a[u]+=x;
    }
    _Ty query(int u,_Ty res){
        for(u=min<int>(u+1,a.size()-1);u;u-=lowbit(u)) res+=a[u];
        return res;
    }
    bit(int _n):a(_n+1){}
};
class blocks{
private:
    struct block{
        vector<bdata> pre;
        block(int _n):pre(_n){}
    };
    vector<block> datas;
    vector<bdata> pre;
    const int len;
    const int n;
    int blcof(int u) const{return u/len;}
    int blclef(int u) const{return blcof(u)*len;}
public:
    void update(int u,bdata ndata){
        int b=blcof(u);
        int p=blclef(u);
        cir(i,b,(int)(pre.size())) pre[i]+=ndata;
        cir(i,u-p,(int)(datas[b].pre.size())) datas[b].pre[i]+=ndata;
    }
    bdata query(int u){
        u=min(u,n-1);
        int b=blcof(u);
        int p=blclef(u);
        if(!b) return datas[b].pre[u];
        return pre[b-1]+datas[b].pre[u-p];
    }
    blocks(int _n)
        :n(_n),len((int)(sqrt(_n)+1)),
         datas((int)(sqrt(_n)+7),block((int)(sqrt(_n)+7))),
         pre((int)(sqrt(_n)+7)){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,q;inf>>n>>q;
    vector<int> a(n);
    for(auto&i:a) inf>>i;
    vector<tuple<int,int,int>> qry(q);
    int c=-1;
    for(int i=0;i<q;++i){
        int l,r;inf>>l>>r;--l;--r;
        qry[i]=make_tuple(l,r,++c);
    }
    int sqr=(int)(sqrt(q));
    sort(qry.begin(),qry.end(),[&](const tuple<int,int,int>& x,const tuple<int,int,int>& y){
        int bx=get<1>(x)/sqr;
        int by=get<1>(y)/sqr;
        if(bx==by) return get<0>(x)<get<0>(y);
        return bx<by;
    });
    vector<set<pair<int,int>>> ql(n);
    bdata empty;
    fill(empty.begin(),empty.end(),0);
    {
        int l=0,r=-1;
        for(int i=0;i<q;++i){
            int qlval=get<0>(qry[i]);
            int qrval=get<1>(qry[i]);
            if(r<qrval){
                auto inc_r=[&](int target){
                    if(l) ql[l-1].emplace(r+1,target);
                    r=target;
                };
                inc_r(qrval);
            }
            if(qlval<l){
                auto dec_l=[&](int target){
                    ql[r].emplace(target,l-1);
                    l=target;
                };
                dec_l(qlval);
            }
            if(qrval<r){
                auto dec_r=[&](int target){
                    if(l) ql[l-1].emplace(target+1,r);
                    r=target;
                };
                dec_r(qrval);
            }
            if(l<qlval){
                auto inc_l=[&](int target){
                    ql[r].emplace(l,target-1);
                    l=target;
                };
                inc_l(qlval);
            }
        }
    }
    vector<lint> upre(n);
    vector<map<pair<int,int>,lint>> ansi(n);
    {
        vector<bdata> ux(n);
        cir(i,0,n) cir(c,0,18) ux[i][c]=((a[i]>>c)&1);
        bit<int> nums(n+7);
        blocks cur(n+7);
        bdata all=empty;
        cir(i,0,n){
            cur.update(a[i],ux[i]);
            nums.update(a[i],1);
            all+=ux[i];
            for(set<pair<int,int>>::iterator it=ql[i].begin();it!=ql[i].end();++it){
                int bl=it->first;
                int br=it->second;
                lint &q = ansi[i][make_pair(bl,br)];
                cir(p,bl,br+1){
                    int _v=a[p];
                    int lb=(_v-1)/2;
                    int ub=_v*2;
                    bdata inrange = all + (-cur.query(ub)) + cur.query(lb);
                    int inrange_c = (i+1) - nums.query(ub,0) + nums.query(lb,0);
                    cir(x,0,18){
                        q += (lint)(((_v>>x)&1)
                            ? (inrange_c - inrange[x])
                            : (inrange[x])) << x;
                    }
                }
            }
            {
                lint &q = upre[i];
                int p=i;
                int _v=a[p];
                int lb=(_v-1)/2;
                int ub=_v*2;
                bdata inrange = all + (-cur.query(ub)) + cur.query(lb);
                int inrange_c = (i+1) - nums.query(ub,0) + nums.query(lb,0);
                cir(x,0,18){
                    q += (lint)(((_v>>x)&1)
                        ? (inrange_c - inrange[x])
                        : (inrange[x])) << x;
                }
            }
        }
    }
    vector<lint> uans(q);
    {
        int l=0,r=-1;
        lint ans=0;
        for(int i=0;i<q;++i){
            int qlval=get<0>(qry[i]);
            int qrval=get<1>(qry[i]);
            int qid=get<2>(qry[i]);
            if(r<qrval){
                auto inc_r=[&](int target){
                    if(l) ans -= ansi[l-1][make_pair(r+1,target)];
                    cir(j,r+1,target+1) ans += upre[j];
                    r = target;
                };
                inc_r(qrval);
            }
            if(qlval<l){
                auto dec_l=[&](int target){
                    ans += ansi[r][make_pair(target,l-1)];
                    cir(j,target,l) ans -= upre[j];
                    l = target;
                };
                dec_l(qlval);
            }
            if(qrval<r){
                auto dec_r=[&](int target){
                    if(l) ans += ansi[l-1][make_pair(target+1,r)];
                    cir(j,target+1,r+1) ans -= upre[j];
                    r = target;
                };
                dec_r(qrval);
            }
            if(l<qlval){
                auto inc_l=[&](int target){
                    ans -= ansi[r][make_pair(l,target-1)];
                    cir(j,l,target) ans += upre[j];
                    l = target;
                };
                inc_l(qlval);
            }
            uans[qid] = ans;
        }
    }
    for(int i=0;i<q;++i) ouf<<uans[i]<<'\n';
    return 0;
}
