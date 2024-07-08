#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
namespace rngmex{
#define ll long long
#define N 100005
array<int,N> rt;
int tot;
struct Node{
	int l,r,last,ls,rs;
	#define l(x) tr[x].l
	#define r(x) tr[x].r
	#define la(x) tr[x].last
	#define ls(x) tr[x].ls
	#define rs(x) tr[x].rs
}tr[N<<5];
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0' || ch>'9') ch=getchar();
	while(ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x;
}
void build(int &x,int l,int r){
	if(!x) x=++tot;
	l(x)=l;r(x)=r;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(ls(x),l,mid);build(rs(x),mid+1,r);
}
void push_up(int x){
	la(x)=min(la(ls(x)),la(rs(x)));
}
int insert(int x,int p,int val){
	int np=++tot;tr[np]=tr[x];
	if(l(x)==r(x)){
		la(np)=val;
		return np;
	}
	int mid=(l(x)+r(x))>>1;
	if(p<=mid) ls(np)=insert(ls(x),p,val);
	else rs(np)=insert(rs(x),p,val);
	push_up(np);
	return np;
}
int query(int x,int lim){
	if(l(x)==r(x)) return l(x);
	if(la(ls(x))<lim) return query(ls(x),lim);
	else return query(rs(x),lim);
}
#undef l
#undef r
#undef ls
#undef rs
#undef la
auto init(vector<int>&a){
    build(rt[0],0,N);
    cir(i,0,a.size()) rt[i+1]=insert(rt[i],a[i],i+1);
}
auto check(int l,int r){
    return query(rt[r+1],l+1);
}
#undef ll
#undef N
}
struct seg{
    int l,r;
    bool operator<(const seg&s) const{
        return l==s.l?r<s.r:l<s.l;
    }
};
auto qyrg(int p,int n,int mn){
    int l=p,r=n-1,res=-1;
    while(l<r+1){
        const auto mid=(l+r)/2;
        rngmex::check(p,mid)>mn?
            ((r=mid-1),(res=mid)):(l=mid+1);
    }
    return res;
}
auto qylf(int p,int mn){
    int l=0,r=p,res=-1;
    while(l<r+1){
        const auto mid=(l+r)/2;
        rngmex::check(mid,p)>mn?
            ((l=mid+1),(res=mid)):(r=mid-1);
    }
    return res;
}
struct tag{int c,cxk;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    rngmex::init(a);
    set<seg> sg;
    cir(i,0,n){
        auto q=qyrg(i,n,a[i]);
        if(q>-1) sg.insert({i,q});
        auto qx=qylf(i,a[i]);
        if(qx>-1) sg.insert({qx,i});
    }
    cir(i,0,n) sg.insert({i,i});
    vector<seg> sgs(sg.begin(),sg.end());
    vector<vector<seg*>> ql(n),qr(n);
    vector<vector<tag>> qx(n+3);
    [&](){
        int c=-1;
        for(auto&[l,r]:sgs){
            ++c;
            ql[l].push_back(&sgs[c]);
            qr[r].push_back(&sgs[c]);
            qx[r-l+1].push_back({
                rngmex::check(l,r),1});
        }
    }();
    auto cpsg=sgs;
    vector<int> cl(n+1,-1),cr(n+1,n);
    cir(i,0,n){
        cl[a[i]]=i;
        for(auto&x:ql[i]){
            auto&[l,r]=*x;
            auto qx=rngmex::check(l,r);
            l=cl[qx]+1;
        }
    }
    for(int i=n-1;~i;--i){
        cr[a[i]]=i;
        for(auto&x:qr[i]){
            auto&[l,r]=*x;
            auto qx=rngmex::check(l,r);
            r=cr[qx]-1;
        }
    }
    for(auto&[l,r]:sgs){
        qx[r-l+2].push_back({
            rngmex::check(l,r),-1});
    }
    set<int> nap;
    unordered_map<int,int> cnt;
    cir(i,0,n+1) nap.insert(i);
    cir(i,1,n+1){
        for(auto&[c,k]:qx[i]){
            cnt[c]+=k;
            if(k==-1&&(!cnt[c])) nap.insert(c);
            if(k==1&&cnt[c]==1) nap.erase(c);
        }
        cout<<*nap.begin()<<' ';
    }
    cout<<'\n';
    return 0;
}
