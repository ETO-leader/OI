#include <bits/stdc++.h>

using namespace std;

const int N=1e5+10;
bitset <N > f[3],ck[26];
int T,lens,lent,id;
char s[N],t[N];

int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	scanf("%d%d",&T,&id);
	while(T--) 
	{
		f[0]^=f[0],f[1]^=f[1],f[2]^=f[2];
		s[0]=t[0]='#';
		scanf("%s%s",s+1,t+1);
		lens=strlen(s),lent=strlen(t);
		for(int i=0;i<26;i++) ck[i]^=ck[i];
		for(int i=1;i<lens;i++) ck[s[i]-'a'][i]=1;
		f[0][0]=1;
		int op=0;
		for(int j=1;j<lent;j++) 
		{
			op=(op+1)%3;
			int ls1=((op-1)%3+3)%3,ls2=((op-2)%3+3)%3; 
			if(t[j]==t[j-1]) f[op]|=f[ls2];
			f[op]|=(f[ls1]<<1)&ck[t[j]-'a'];
			f[ls2]^=f[ls2]; 
		}
		if(f[op][lens-1]) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
