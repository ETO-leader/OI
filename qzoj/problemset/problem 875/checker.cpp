/*
  Code: Checker for P875
  Author: zlxFTH
*/
#include <cstdio>
#include <vector>

typedef long long LL;

const int N = 110;

int n;
LL ans, dis[N][N];
bool vis[N];
std::vector<int> path;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      scanf("%lld", &dis[i][j]);
      dis[j][i] = dis[i][j];
    }
  }
  scanf("%lld", &ans);
  int u;
  while (scanf("%d", &u) && u) path.emplace_back(u), vis[u] = 1;
  LL res = 0;
  for (int i = 1; i < int(path.size()); ++i) {
    res += dis[path[i - 1]][path[i]];
  }
  if (res != ans) {
    printf("Invalid Answer. The length you output doesn't match the path!\n");
  } else {
    bool flag = 0;
    for (int i = 1; i <= n; ++i) {
      if (!vis[i]) flag = 1; 
    }
    if (flag) {
      printf("Invalid Answer. You haven't visited all the point!\n");
    } else {
      printf("Accepted! Diana is lovely!\n");
    }
  }
  return 0;
}