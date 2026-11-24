#include<bits/stdc++.h>
using namespace std;
//#define int long long
constexpr int MAXN=100005;
struct node{
    int ls,rs,sum;
}tree[MAXN*23];
int root[MAXN],tot;
void update(int &cur,int prev,int l,int r,int val){
    cur=++tot;
    tree[cur]=tree[prev];
    tree[cur].sum++;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(val<=mid) update(tree[cur].ls,tree[prev].ls,l,mid,val);
    else update(tree[cur].rs,tree[prev].rs,mid+1,r,val);
    return;
}
int query(int u,int v,int l,int r,int target){
    if(tree[u].sum-tree[v].sum==0) return 0;
    if(l==r) return tree[u].sum-tree[v].sum;
    int mid=(l+r)>>1;
    if(target<=mid) return query(tree[u].ls,tree[v].ls,l,mid,target);
    else return query(tree[u].rs,tree[v].rs,mid+1,r,target);
}
vector<int> adj[MAXN];
int dfn[MAXN],dep[MAXN],fa[MAXN],son[MAXN],top[MAXN],rev[MAXN],sz[MAXN],cnt;
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
    top[u]=t;
    dfn[u]=++cnt;
    rev[cnt]=u;
    if(!son[u]) return;
    dfs_2(son[u],t);
    for(auto v : adj[u]){
        if(v==fa[u] || v==son[u]) continue;
        dfs_2(v,v);
    }
    return;
}
int n,m;
int arr[MAXN];
bool check(int u,int v,int c){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        if(query(root[dfn[u]],root[dfn[top[u]]-1],1,n,c)>0) return true;
        u=fa[top[u]];
    }
    if(dep[u]>dep[v]) swap(u,v);
    if(query(root[dfn[v]],root[dfn[u]-1],1,n,c)>0) return true;
    return false;
}
void solve(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<=n-1;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs_1(1,0,0);
    dfs_2(1,1);
    for(int i=1;i<=n;i++){
        update(root[i],root[i-1],1,n,arr[rev[i]]);
    }
    for(int i=1;i<=m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        cout<<(check(a,b,c) ? '1' : '0');
    }
    cout<<'\n';
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}
