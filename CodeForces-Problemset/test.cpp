#include<bits/stdc++.h>
 
#define ll long long
#define pi pair<int,int>
#define fi first
#define se second
#define cpy(x,y,s) memcpy(x,y,sizeof(x[0])*(s))
#define mem(x,v,s) memset(x,v,sizeof(x[0])*(s))
#define all(x) begin(x),end(x)
#define vi vector<int> 
#define arr array
#define pb push_back
#define mp make_pair
 
#define B 1500
#define N 200005
 
using namespace std;
 
bitset<N> t[B];
 
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9')f=(ch=='-'?-1:f),ch=getchar();
    while(ch>='0' && ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}
void write(int x){
    if(x<0)x=-x,putchar('-');
    if(x/10)write(x/10);
    putchar(x%10+'0');
}
 
int sum[200][N],a[N];
 
int main(){
    int n=read(),q=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<B;i++){
    	int now=1,ti=0;
    	for(int j=1;j<=n;j++){
    		if(now>a[j])continue;
    		t[i][j]=1;
    		ti++;if(ti==i){now++;ti=0;}
    	}
    }
    for(int i=1;i<200;i++){
    	for(int j=1;j<=n;j++){
    		sum[i][j]=sum[i][j-1]+(a[j]>=i);
    	}
    }
    for(int i=1;i<=q;i++){
    	int p=read(),k=read();
    	if(k<B){
    		if(t[k][p])printf("YES\n");
    		else printf("NO\n");
    	}
    	else{
    		int now=1,pos=1;
    		int l=1,r=n;
    		while(1){
    			l=pos;r=n;
    			while(l<r){
    				int mid=(l+r)>>1;
    				if(sum[now][mid]-sum[now][pos-1]>=k)r=mid;
    				else l=mid+1;
    			}
    			if(p<=r){
    				if(a[p]<now)printf("NO\n");
    				else printf("YES\n");break;
    			}
    			pos=r+1;now++;
    		}
    	}
    }
}