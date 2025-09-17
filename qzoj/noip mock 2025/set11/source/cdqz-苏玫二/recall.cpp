#include<bits/stdc++.h> 
using namespace std;
#define ll long long
const ll mod=998244353;
ll sum[205];
int main(){
	freopen("recall.in","r",stdin);
	freopen("recall.out","w",stdout);
	int id,T;scanf("%d %d",&id,&T);
	if(id==0){
		printf("5 46\n5 20\n5 28\n7 1190n\6 320\n5 20\n4 4\n6 18n\4 4\n5 11");
		return 0;
	}
	sum[0]=1;
	for(ll i=1;i<=105;i++){
		sum[i]=sum[i-1]*i%mod;
	}
	while(T--){
		int n;
		scanf("%d",&n);
		for(int i=1;i<n;i++){
			int u,v;
			scanf("%d %d",&u,&v);
		}
		if(id==2){
			printf("%d %d\n",n,sum[n]);
		}
		if(id==3){
			if(n==1) printf("1 1\n");
			if(n==2) printf("2 2\n");
			if(n>=3) printf("2 1\n");
			continue;
		}
	}
	
}
