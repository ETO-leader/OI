#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
int T , id;
int ls , lt;
string a , b;
char s[MAXN] , t[MAXN];
int main()
{
	freopen("string.in" , "r" , stdin);
	freopen("string.out" , "w" , stdout);
	cin >> T >> id;
	while(T--)
	{
		scanf("%s" , s + 1);
		scanf("%s" , t + 1);
		ls = strlen(s + 1) , lt = strlen(t + 1);
		if((ls & 1) != (lt & 1))
		{
			printf("NO\n");
			continue;
		}
		a.clear() , b.clear();
		for(int i = 1 ; i <= ls ; i++) if(s[i] == s[i - 1]) s[i] = s[i - 1] = 0;
		for(int i = 1 ; i <= lt ; i++) if(t[i] == t[i - 1]) t[i] = t[i - 1] = 0;
		for(int i = 1 ; i <= ls ; i++) if(isalpha(s[i])) a = a + s[i];
		for(int i = 1 ; i <= lt ; i++) if(isalpha(t[i])) b = b + t[i];
		lt = b.size();
		for(int i = 1 ; i <= lt ; i++) t[i] = b[i - 1];
		b.clear();
		for(int i = 1 ; i <= lt ; i++) if(t[i] == t[i - 1]) t[i] = t[i - 1] = 0;
		for(int i = 1 ; i <= lt ; i++) if(isalpha(t[i])) b = b + t[i];
		if(a == b) printf("YES\n");
		else printf("NO\n");
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
/*
2 1
hllo
haalbblocc
hllo
habballocc
*/