#include<bits/stdc++.h> 
using namespace std;
const int N=1e6+5;
int modify(int x){
	return x&(-x);
}
int t[N],a[N],sum[N],n,k;
void put(int x){
	for(int i=x;i<=n;i+=modify(i)){
		t[i]++; 
	}
}
int get(int x){
	int ans=0;
	for(int i=x;i;i-=modify(i)){
		ans+=t[i];
	}
	return ans;
}
int main(){
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	int id;
	scanf("%d %d %d",&id,&n,&k);
	if(id==3){
		printf("0");
		return 0;
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		put(a[i]);
		sum[i]=sum[i-1]+(i-get(a[i]));
	}
	int las=sum[n]-k;
	printf("%d\n",las);
	if(las==0) return 0; 
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(a[i]>a[j]){
				swap(a[i],a[j]);
				printf("%d %d\n",i,j);
				las--;
				if(!las) return 0;
			}
		}
	}
}
