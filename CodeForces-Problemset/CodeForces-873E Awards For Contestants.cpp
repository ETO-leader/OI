#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
struct stu{int v,id;};
bool comp(int x,int y,int z,
	int xx1,int yx1,int zx1){
	return xx1==x?(yx1==y?z<zx1:y<yx1):x<xx1;
}
template<typename T>
class segment{
private:
    int _n;vector<T> val;
    T change(int u,int l,int r,int s,int v){
        if(l==s&&r==s){val[u]=v;return val[u];}
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;
        val[u]=max((mid<s?change(rs,mid+1,r,s,v):
        change(ls,l,mid,s,v)),(mid<s?val[ls]:val[rs]));
        return val[u];
    }
    T quary(int u,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr) return val[u];
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;T res=0;
        if(mid>=ql) res=max(quary(ls,l,mid,ql,qr),res);
        if(mid<qr) res=max(quary(rs,mid+1,r,ql,qr),res);
        return res;
    }
public:
    segment(int __n=1):_n(__n-1),val(__n*8){}
    void resize(int __n){(*this)=segment(__n);}
    void change(int s,int v){change(1,1,_n,s,v);}
    T quary(int l,int r){return r<l?-1:quary(1,1,_n,l,r);}
};
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int n,idx=0;cin>>n;vector<stu> v(n);
	vector<int> ans(n);
	for(auto&i:v) cin>>i.v,i.id=idx++;
	sort(v.begin(),v.end(),
		[](stu&a,stu&b){return a.v>b.v;});
	segment<int> seg(n+5);
	seg.change(n,v[n-1].v);
	cir(i,1,n) seg.change(i,v[i-1].v-v[i].v);
	int u=0,vx=0,w=0,c1=1,c2=2;
	cir(i,1,n-2) cir(j,i+1,n-1){
		if(i>(j-i)*2||(j-i)>i*2) continue;
		int k=min(j-i,i),f=max(j-i,i);
		if((n-j+1)*2<f) continue;
		int _x=v[i-1].v-v[i].v,_y=v[j-1].v-v[j].v,
			_z=seg.quary(j+f/2+(f&1),min(n,j+2*k));
		if(_z==-1) continue;
		if(comp(u,vx,w,_x,_y,_z)){
			u=_x;vx=_y;w=_z;c1=i;c2=j;
		}
	}
	cir(i,0,c1) ans[v[i].id]=1;
	cir(i,c1,c2) ans[v[i].id]=2;
	int cx=c2;
	while((cx<n&&v[cx-1].v-v[cx].v!=w)||
		((cx-c2)*2<c1||(cx-c2)*2<(c2-c1))) ans[v[cx].id]=3,++cx;
	cir(i,cx,n) ans[v[i].id]=-1;
	for(auto&i:ans) cout<<i<<' ';
	cout<<'\n';
	return 0;
}