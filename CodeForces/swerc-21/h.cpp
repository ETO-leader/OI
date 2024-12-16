#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,n,m;set<int>st;
int gcd(int x,int y){
	if(!y)return x;
	return gcd(y,x%y);
}
inline void f(int x){
	for(int i=1;i<=x/i;i++){
		if(x%i)continue;
		st.insert(i);
		if(i!=x/i)st.insert(x/i);
	}
}
int main(){
	scanf("%d",&t);while(t--){
		scanf("%d%d",&n,&m);st.insert(1);
		f(gcd(n-1,m-1));f(gcd(n-2,m));f(gcd(n,m-2));
		cout<<st.size()<<'\n';
		for(int i:st)cout<<i<<' ';
		cout<<'\n';st.clear();
	}
	return 0;
}