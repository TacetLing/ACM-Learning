#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAXN=100005;
struct node{
    int ls,rs,sum;
}tree[MAXN*40];
int root[MAXN],tot;
void update(int &cur,int prev,int l,int r,int val,int delta){
    cur=++tot;
    tree[cur]=tree[prev];
    tree[cur].sum+=delta;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(val<=mid) update(tree[cur].ls,tree[prev].ls,l,mid,val,delta);
    else update(tree[cur].rs,tree[prev].rs,mid+1,r,val,delta);
    return;
}
int query(int cur,int l,int r,int v){
    if(l>=v) return tree[cur].sum;
    if(r<v || cur==0) return 0;
    int mid=(l+r)>>1;
    int res=query(tree[cur].ls,l,mid,v)+query(tree[cur].rs,mid+1,r,v);
    return res;
}
void solve(){
    int n;
    cin>>n;
    string line;
    getline(cin,line);
    for(int i=1;i<=n;i++){
        root[i]=root[i-1];
        getline(cin,line);
        stringstream ss(line);
        string op;
        while(ss>>op){
            int val=stoi(op.substr(1));
            int delta=(op[0]=='+') ? 1 : -1;
            update(root[i],root[i],0,n-1,val,delta);
        }
    }
    int x=0;
    for(int i=0;i<n;i++){
        int d;
        cin>>d;
        int y=query(root[d],0,n-1,x);
        x=(x+y)%n;
    }
    cout<<x<<'\n';
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}