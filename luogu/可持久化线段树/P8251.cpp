#include<bits/stdc++.h>
using namespace std;
//#define int long long
constexpr int MAXN=500005;
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
    if(r<=target) return tree[u].sum-tree[v].sum;
    if(u==v) return 0;
    if(l>target) return 0;
    int mid=(l+r)>>1;
    return query(tree[u].ls,tree[v].ls,l,mid,target)+query(tree[u].rs,tree[v].rs,mid+1,r,target);
}
int arr[MAXN],b[MAXN],d[MAXN];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>arr[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    stack<int> st;
    for(int i=1;i<=n;i++){
        while(!st.empty() && (b[st.top()]<=b[i] || arr[st.top()]==arr[i])) st.pop();
        d[i]=st.empty() ? 0 : st.top();
        st.push(i);
    }
    for(int i=1;i<=n;i++){
        update(root[i],root[i-1],0,n,d[i]);
    }
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<query(root[r],root[l-1],0,n,l-1)<<'\n';
    }
    return 0;
}
