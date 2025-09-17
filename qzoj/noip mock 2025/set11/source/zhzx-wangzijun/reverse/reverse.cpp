#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
	ll x; scanf("%lld",&x); return x;
}
ll k,rev,all;
int id,n,a[1000005];
int c[1000005];
void add(int x,int w){
	while(x<=n){
		c[x]+=w;
		x+=(x&-x);
	}
}
int qry(int x){
	int ret=0;
	while(x){
		ret+=c[x];
		x-=(x&-x);
	}
	return ret;
}
int main(){
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);

	id=read(), n=read(), k=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		all+=qry(n)-qry(a[i]); add(a[i],1);
	}

	// cout<<"all = "<<all<<endl;
	memset(c,0,sizeof(c));

	for(int l=1,r=0;l<=n;l++){
		while(r<n && rev<all-k){
			r++;
			rev+=qry(n)-qry(a[r]);
			add(a[r],1);
		}
		// cout<<l<<"->"<<r<<" rev = "<<rev<<endl;
		if(rev==all-k){
			printf("1\n%d %d\n", l, r);
			return 0;
		}
		add(a[l],-1);
		rev-=qry(a[l]);
	}

	int i; 
	for(i=1; i<=n; i++){
		rev+=qry(n)-qry(a[i]);
		if(rev>all-k){
			rev-=qry(n)-qry(a[i]);
			--i;
			break;
		}
		add(a[i],1);
	}
	all-=(rev+k);
	printf("2\n%d %d\n%d %d\n",1,i,i+1-all,i+1);
}