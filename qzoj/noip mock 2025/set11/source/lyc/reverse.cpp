#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
int id,n,k,a[N];
int conf[N],conb[N],sum[N],fro[N];
struct BIT{
	int c1[N],c2[N],c3[N],c4[N];
	
	int lowbit(int x){
		return x&(-x);
	}
	void add(int x,int c[],int k){
		while(x<=n){
			c[x]+=k;
			x+=lowbit(x);
		}
	}
	int query(int x,int c[]){
		int res=0;
		while(x){
			res+=c[x];
			x-=lowbit(x);
		}
		return res;
	}
}T;

namespace SLV0{
	bool solve(){
		for(int i=n;i>=1;i--){
			conb[i]=T.query(a[i],T.c2);
			T.add(a[i],T.c2,1);
		}
		for(int i=n;i>=1;i--) sum[i]=sum[i+1]+conb[i];
		if(sum[1]==k) return 1;
		return 0;
	}
}

namespace SLV1{
	int l,r,req,b[N];
	bool solve(){
		req=sum[1]-k;
		int pos=0,maxn=0,cnt=0;
		memset(T.c1,0,sizeof(T.c1));
		memset(T.c2,0,sizeof(T.c2));
		for(int i=1;i<=n;i++) T.add(a[i],T.c3,1),T.add(a[i],T.c4,1);
		for(int i=1;i<=n;i++){
			while(pos+1<=n){
				int v1=T.query(n-a[pos+1]+1,T.c1),v2=T.query(n-a[pos+1]+1,T.c2);
				if(cnt+v2-v1<=req){cnt+=v2-v1,pos++,T.add(n-a[pos]+1,T.c2,1),T.add(a[pos],T.c4,-1);}
				else break;
			}
			if(cnt>maxn) maxn=cnt,l=i,r=pos;
			if(cnt==req) break;
			T.add(n-a[i]+1,T.c1,1),T.add(a[i],T.c3,-1);
			int v3=T.query(a[i],T.c3),v4=T.query(a[i],T.c4);
			cnt-=(v3-v4);
		}
		req-=maxn;
		if(!req){
			cout<<"1\n"<<l<<" "<<r<<endl;
			return 1;
		}
		else{
			cout<<"2\n"<<l<<" "<<r<<endl; return 0;
		}
	}
	void solve2(){
		int ansl,ansr,cnt=0;
		for(int i=l;i<=r;i++) b[++cnt]=a[i];
		sort(b+1,b+cnt+1); int pos=1;
		for(int i=l;i<=r;i++) a[i]=b[pos],pos++;
		cnt=0;
		if(r==n){
			ansl=l-1;
			for(int i=l;i<=r;i++){
				if(cnt==req){ansr=i-1; break;}
				if(a[ansl]>a[i]) cnt++;
			}
		}
		else{
			ansr=r+1;
			for(int i=r;i>=l;i--){
				if(cnt==req){ansl=i+1; break;}
				if(a[i]>a[ansr]) cnt++;
			}
		}
		cout<<ansl<<" "<<ansr<<endl;
	}
}

signed main(){
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>id>>n>>k; for(int i=1;i<=n;i++) cin>>a[i];
	if(SLV0::solve()){cout<<"0\n"; return 0;}
	if(SLV1::solve()) return 0;
	SLV1::solve2(); return 0;
}
