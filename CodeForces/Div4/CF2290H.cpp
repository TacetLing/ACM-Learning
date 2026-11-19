#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAXN=200005;
vector<int> adj[MAXN];
int sz[MAXN],dfn[MAXN],dep[MAXN],son[MAXN],fa[MAXN],top[MAXN],rev[MAXN];
int tot;
int n;
void dfs_1(int u,int f,int d){
    dep[u]=d;
    fa[u]=f;
    sz[u]=1;
    int max_sz=-1;
    for(auto v : adj[u]){
        if(v==f) continue;
        dfs_1(v,u,d+1);
        sz[u]+=sz[v];
        if(sz[v]>max_sz){
            max_sz=sz[v];
            son[u]=v;
        }
    }
    return;
}
void dfs_2(int u,int t){
    dfn[u]=++tot;
    rev[tot]=u;
    top[u]=t;
    if(!son[u]) return;
    dfs_2(son[u],t);
    for(auto v : adj[u]){
        if(v==fa[u] || v==son[u]) continue;
        dfs_2(v,v);
    }
    return;
}
int ans;
void dfs(int u,int f){
    for(auto v : adj[u]){
        if(v==f) continue;
        if(v==son[u]){
            dfs(v,u);
        }
        else{
            ans=max(ans,sz[v]);
        }
    }
    return;
}
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++) adj[i].clear(),son[i]=0;
    for(int i=1;i<=n-1;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    ans=0;
    dfs_1(1,0,0);
    dfs_2(1,1);
    vector<int> arr;
    for(auto v : adj[1]){
        dfs(v,1);
        arr.push_back(sz[v]);
    }
    sort(arr.begin(),arr.end(),greater<int>());
    if((int)arr.size()>=3) ans=max(ans,arr[2]);
    cout<<n-ans<<'\n';
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