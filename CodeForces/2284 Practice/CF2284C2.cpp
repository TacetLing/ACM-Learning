#include<bits/stdc++.h>
using namespace std;
#define int long long
void solve(){
    int a,b;
    cin>>a>>b;
    if(a==b){
        cout<<0<<'\n';
        return;
    }
    if(__gcd(a,b-a)==1){
        cout<<1<<'\n'<<(b-a)<<'\n';
        return;
    }
    for(int p=a+1;p<b;p++){
        if(__gcd(p,a)==1 && __gcd(p,b)==1){
            cout<<2<<'\n'<<(p-a)<<" "<<(b-p)<<'\n';
            return;
        }
    }
    int n=(b-a+1);
    vector<int> parent(n,-1);
    vector<bool> vis(n+5,false);
    queue<int> q;
    vis[0]=true;
    q.push(0);
    bool found=false;
    while(!q.empty() && !found){
        int u=q.front();
        q.pop();
        for(int v=u+1;v<n;v++){
            if(!vis[v] && __gcd(a+u,a+v)==1){
                vis[v]=true;
                parent[v]=u;
                q.push(v);
                if(v==n-1){
                    found=true;
                    break;
                }
            }
        }
    }
    vector<int> ops;
    for(int cur=n-1;cur!=0;cur=parent[cur]){
        ops.push_back(cur-parent[cur]);
    }
    reverse(ops.begin(),ops.end());
    cout<<(int)ops.size()<<'\n';
    for(int i=0;i<(int)ops.size();i++){
        cout<<ops[i]<<(i+1==(int)ops.size() ? '\n' : ' ');
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