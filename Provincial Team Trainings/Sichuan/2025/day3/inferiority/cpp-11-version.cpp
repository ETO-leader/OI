#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#define inf cin
#define ouf cout
using lint=long long;
using uint=unsigned int;
using bdata=array<uint,24>;
bdata&operator+=(bdata&a,bdata b){
    a[0]+=b[0];
    a[1]+=b[1];
    a[2]+=b[2];
    a[3]+=b[3];
    a[4]+=b[4];
    a[5]+=b[5];
    a[6]+=b[6];
    a[7]+=b[7];
    a[8]+=b[8];
    a[9]+=b[9];
    a[10]+=b[10];
    a[11]+=b[11];
    a[12]+=b[12];
    a[13]+=b[13];
    a[14]+=b[14];
    a[15]+=b[15];
    a[16]+=b[16];
    a[17]+=b[17];
    a[18]+=b[18];
    a[19]+=b[19];
    a[20]+=b[20];
    a[21]+=b[21];
    a[22]+=b[22];
    a[23]+=b[23];
    return a;
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
        for(u=min(u+1,(int)(a.size())-1);u;u-=lowbit(u)) res+=a[u];
        return res;
    }
    bit(int _n):a(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,q;inf>>n>>q;
    vector<int> a(n);
    for(auto&i:a) inf>>i;
    vector<tuple<int,int,int>> qry(q);
    for(int idx=0;idx<q;++idx){
        int l,r;inf>>l>>r;--l;--r;
        qry[idx]=make_tuple(l,r,idx);
    }
    const auto sqr=(int)(sqrt(q*log2(n)));
    sort(qry.begin(),qry.end(),[&](const tuple<int,int,int>&a,const tuple<int,int,int>&b){
        return get<1>(a)/sqr==get<1>(b)/sqr?get<0>(a)<get<0>(b):get<1>(a)<get<1>(b);
    });
    bit<int> ucnt(n+7);
    bit<bdata> cur(n+7);
    vector<bdata> numi(n+7);
    cir(i,0,n){
        for(int x=23;~x;--x) if((a[i]>>x)&1) numi[i][x]=1;
    }
    bdata all;
    fill(all.begin(),all.end(),0);
    const auto empty=all;
    auto ans=0ll;
    int l=0,r=-1;
    auto ins=[&](int p){
        const auto _v=a[p];
        ucnt.update(_v,1);
        cur.update(_v,numi[p]);
        all+=numi[p];
        const auto upb=_v*2;
        const auto lwb=(_v-1)/2;
        const auto qa=cur.query(upb,empty);
        const auto qb=cur.query(lwb,empty);
        const auto vaild_cnt=(r-l+1)-ucnt.query(upb,0)+ucnt.query(lwb,0);
        cir(i,0,20){
            if(!((_v>>i)&1)) ans+=(lint)(all[i]-qa[i]+qb[i])<<i;
            else ans+=(lint)(vaild_cnt-all[i]+qa[i]-qb[i])<<i;
        }
    };
    auto rmv=[&](int p){
        const auto _v=a[p];
        const auto upb=_v*2;
        const auto lwb=(_v-1)/2;
        const auto qa=cur.query(upb,empty);
        const auto qb=cur.query(lwb,empty);
        const auto vaild_cnt=(r-l+2)-ucnt.query(upb,0)+ucnt.query(lwb,0);
        cir(i,0,20){
            if(!((_v>>i)&1)) ans-=(lint)(all[i]-qa[i]+qb[i])<<i;
            else ans-=(lint)(vaild_cnt-all[i]+qa[i]-qb[i])<<i;
        }
        ucnt.update(_v,-1);
        cur.update(_v,-numi[p]);
        all+=-numi[p];
    };
    vector<lint> uans(q);
    for(int i=0;i<q;++i){
        int ql=get<0>(qry[i]);
        int qr=get<1>(qry[i]);
        int qid=get<2>(qry[i]);
        while(r<qr) ins(++r);
        while(ql<l) ins(--l);
        while(qr<r) rmv(r--);
        while(l<ql) rmv(l++);
        uans[qid]=ans;
    }
    for(auto&i:uans) ouf<<i<<'\n';
    return 0;
}
