#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
template<typename T,class comp=less<T>>
using rbt=tree<T,null_type,comp,rb_tree_tag,
    tree_order_statistics_node_update>;
enum oper{nulltp,maxtp,mintp};
template<typename T>
class exchange_segment{
private:
	T _inf;
	vector<T> mx,mn;
public:
	exchange_segment(int _sz,T _ninf=(int)(1e9+7)){
		mx.resize(4*_sz+1),mn.resize(4*_sz+1),_inf=_ninf;
		fill(mn.begin(),mn.end(),_inf);
        fill(mx.begin(),mx.end(),_inf);
	}
	inline void getmax(int u,T v){
		mx[u]=max(mx[u],v);mn[u]=max(mn[u],v);
	}
	inline void getmin(int u,T v){
		mx[u]=min(mx[u],v);mn[u]=min(mn[u],v);
	}
	void pushdown(int u){
		int lc=2*u,rc=2*u+1;T&ax=mx[u],&mi=mn[u];
		if(ax) getmax(lc,ax),getmax(rc,ax);
		if(mi!=_inf) getmin(lc,mi),getmin(rc,mi);
		ax=0;mi=_inf;
	}
	void update(int ql,int qr,int l,int r,int u,T v,oper op){
		int lc=2*u,rc=2*u+1,mid=(l+r)/2;
		if(ql<=l&&r<=qr){
			if(op==1) getmax(u,v);
			else getmin(u,v);
			return;
		}
		pushdown(u);
		if(ql<=mid) update(ql,qr,l,mid,lc,v,op);
		if(qr>mid) update(ql,qr,mid+1,r,rc,v,op);
	}
	void printtree(int u,int l,int r,vector<T>&v){
		if(l==r) return v.push_back(mx[u]);
		int lc=2*u,rc=2*u+1,mid=(l+r)/2;
		pushdown(u);
        printtree(lc,l,mid,v);printtree(rc,mid+1,r,v);
	}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,q;cin>>n>>m>>q;
    string s;cin>>s;
    exchange_segment<int> sgm(n);
    cir(i,0,m){
        int l,r;cin>>l>>r;
        sgm.update(l,r,1,n,1,i,mintp);
    }
    sgm.update(1,n,1,n,1,m,mintp);
    vector<int> result;
    sgm.printtree(1,1,n,result);
    vector<int> nid(n),cnx(m+1),c(m+1);
    for(auto&i:result) cnx[i]++;
    cir(i,1,m+1) cnx[i]+=cnx[i-1];
    cir(i,0,n){
        nid[i]=(result[i]?cnx[result[i]-1]:0)+c[result[i]];
        ++c[result[i]];
    }
    rbt<int> c0,c1;
    int cnx1=count(s.begin(),s.end(),'1');
    const int ctr=n-count(result.begin(),result.end(),m);
    cir(i,0,n){
        if(s[i]=='0') c0.insert(nid[i]);
        else c1.insert(nid[i]);
    }
    cir(i,0,q){
        int p;cin>>p;--p;
        if(c0.find(nid[p])!=c0.end()){
            ++cnx1;
            c0.erase(nid[p]);c1.insert(nid[p]);
        }else{
            --cnx1;
            c0.insert(nid[p]);c1.erase(nid[p]);
        }
        if(cnx1>ctr) cout<<ctr-c1.order_of_key(ctr)<<'\n';
        else cout<<cnx1-c1.order_of_key(cnx1)<<'\n';
    }
    return 0;
}
