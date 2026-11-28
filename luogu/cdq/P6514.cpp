#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAXN=100005;
int n,q;
int limit;
vector<int> tree;
int lowbit(int x){
    return x&-x;
}
void add(int x,int val){
    for(;x<=limit;x+=lowbit(x)){
        tree[x]+=val;
    }
    return;
}
int query(int x){
    int res=0;
    if(x<=0) return 0;
    for(;x>0;x-=lowbit(x)){
        res+=tree[x];
    }
    return res;
}
struct node{
    int l,r,id,type;
    bool operator<(const node&other) const{
        if(l!=other.l) return l<other.l;
        else return r<other.r;
    }
}qrys[MAXN];
int ans[MAXN];
void cdq(int l,int r){
    if(l>=r) return;
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    vector<node> q_1,q_2;
    vector<int> used;
    for(int i=l;i<=mid;i++) if(qrys[i].type==1) q_1.push_back({qrys[i].l,qrys[i].r,0});
    for(int i=mid+1;i<=r;i++) if(qrys[i].type==2) q_2.push_back({qrys[i].l,qrys[i].r,qrys[i].id});
    if(q_1.empty() || q_2.empty()) return;
    sort(q_1.begin(),q_1.end());
    sort(q_2.begin(),q_2.end());
    int p=0;
    for(auto pq : q_2){
        while(p<(int)q_1.size() && q_1[p].l<=pq.l){
            int pos=n-q_1[p].r+1;
            add(pos,1);
            used.push_back(pos);
            p++;
        }
        ans[pq.id]+=query(n-pq.r+1);
    }
    for(auto e : used){
        add(e,-1);
    }
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>q;
    limit=n;
    tree.assign(n+5,0);
    int qcnt=0;
    for(int i=1;i<=q;i++){
        cin>>qrys[i].type>>qrys[i].l>>qrys[i].r;
        if(qrys[i].type==2) qrys[i].id=++qcnt;
    }
    cdq(1,q);
    for(int i=1;i<=qcnt;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}
