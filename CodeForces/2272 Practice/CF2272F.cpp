#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAXN=500005;
vector<int> adj[MAXN];
int f[MAXN];
int n,t;
int cnt[MAXN];
bool win[MAXN];
void dfs_1(int u,int fa){
    cnt[u]=0;
    int child_cnt=0;
    for(auto v : adj[u]){
        if(v==fa) continue;
        child_cnt++;
        dfs_1(v,u);
        if(f[v]==0) cnt[u]++;
    }
    if(cnt[u]==0 && child_cnt%2==1){
        f[u]=0;
    }
    else f[u]=1;
    return;
}
void dfs_2(int u,int fa,int up_f){
    int total_zero=cnt[u];
    if(u!=1 && up_f==0) total_zero++;
    if(total_zero==0 && adj[u].size()%2==0){
        win[u]=true;
    }
    int mv=adj[u].size()-1;
    for(auto v : adj[u]){
        if(v==fa) continue;
        int zv=total_zero-(f[v]==0 ? 1 : 0);
        int nxt_up_f=(zv==0 && mv%2==1) ? 0 : 1;
        dfs_2(v,u,nxt_up_f);
    }
    return;
}
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        adj[i].clear();
        win[i]=false;
    }
    for(int i=1;i<=n-1;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs_1(1,0);
    dfs_2(1,0,1);
    vector<int> ans;
    for(int i=1;i<=n;i++){
        if(win[i]) ans.push_back(i);
    }
    if(ans.empty()){
        cout<<"Alice\n";
    }
    else{
        cout<<"Bob\n";
        cout<<(int)ans.size()<<'\n';
        for(auto e : ans){
            cout<<e<<' ';
        }
        cout<<'\n';
    }
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>t;
    while(t--) solve();
    return 0;
}
