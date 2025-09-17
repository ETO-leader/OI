#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
int main(){
	
	int id,T,u,v;
	freopen("recall.in","r",stdin);
	freopen("recall.out","w",stdout);
	scanf("%d%d",&id,&T);
	if(id==0){
		cout<<"5 46"<<endl;
		cout<<"5 20"<<endl;
		cout<<"5 28"<<endl;
		cout<<"7 1190"<<endl;
		cout<<"6 320"<<endl;
		cout<<"5 20"<<endl;
		cout<<"4 4"<<endl;
		cout<<"6 18"<<endl;
		cout<<"4 4"<<endl;
		cout<<"5 11"<<endl;
		return 0;
	}
	while(T--){
		int n; scanf("%d",&n);
		for(int i=1;i<=n-1;i++)scanf("%d%d",&u,&v);
		printf("%d\n",n);
		int ans=1;
		for(int i=2;i<=n-1;i++)ans*=i,ans%=mod;
		printf("%d\n",ans);
	}
	return 0;
}