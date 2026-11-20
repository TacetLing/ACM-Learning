#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAXN=50005;
constexpr int MAXL=200000;
struct node{
    int ls,rs,g;
}tree[MAXN*22];
struct edge{
    int to,l,a;
};
vector<edge> adj[MAXN];
int root[MAXN],tot;
void push_up(int cur){
    tree[cur].g=__gcd(tree[tree[cur].ls].g,tree[tree[cur].rs].g);
    return;
}
void update(int &cur,int prev,int l,int r,int pos,int val){
    cur=++tot;
    tree[cur]=tree[prev];
    if(l==r){
        tree[cur].g=val;
        return;
    }
    int mid=(l+r)>>1;
    if(pos<=mid) update(tree[cur].ls,tree[prev].ls,l,mid,pos,val);
    else update(tree[cur].rs,tree[prev].rs,mid+1,r,pos,val);
    push_up(cur);
    return;
}
int query(int cur,int l,int r,int R){
    if(cur==0 || l>R) return 0;
    if(r<=R) return tree[cur].g;
    int mid=(l+r)>>1;
    int res=query(tree[cur].ls,l,mid,R);
    if(R>mid) res=__gcd(res,query(tree[cur].rs,mid+1,r,R));
    return res;
}
void dfs(int u,int f){
    for(auto e : adj[u]){
        if(e.to==f) continue;
        update(root[e.to],root[u],1,MAXL,e.l,e.a);
        dfs(e.to,u);
    }
    return;
}
void solve(int tc){
    int n,q;
    cin>>n>>q;
    tot=0;
    root[1]=0;
    for(int i=1;i<=n;i++) adj[i].clear();
    for(int i=1;i<n;i++){
        int u,v,l,a;
        cin>>u>>v>>l>>a;
        adj[u].push_back({v,l,a});
        adj[v].push_back({u,l,a});
    }
    dfs(1,0);
    cout<<"Case #"<<tc<<":";
    while(q--){
        int c,w;
        cin>>c>>w;
        cout<<" "<<query(root[c],1,MAXL,w);
    }
    cout<<'\n';
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    for(int i=1;i<=t;i++){
        solve(i);
    }
    return 0;

}