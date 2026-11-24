#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAXN=200005;
vector<int> adj[MAXN];
int dp[MAXN][2];
int white[MAXN];
void dfs(int u,int f){
    dp[u][0]=0;
    dp[u][1]=1;
    for(auto v : adj[u]){
        if(v==f) continue;
        dfs(v,u);
        dp[u][0]+=max(dp[v][0],dp[v][1]);
        dp[u][1]+=dp[v][0];
    }
    return;
}
void init(int sz){
    for(int i=1;i<=sz;i++){
        dp[i][0]=dp[i][1]=0;
        adj[i].clear();
    }
    return;
}
int k,n;
void solve(){
    cin>>k;
    int p=1;
    for(int i=1;i<=k;i++){
        cin>>n;
        for(int j=1;j<=n-1;j++){
            int u,v;
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        if(n==1) white[i]=1;
        else{
            p=i;
            dfs(1,0);
            if(dp[1][0]>=dp[1][1]) white[i]=1;
            else white[i]=adj[1][0];
        }
        init(n);
    }
    for(int i=1;i<=k;i++){
        if(i==p) continue;
        cout<<i<<' '<<white[i]<<' '<<p<<' '<<white[p]<<'\n';
    }
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}
