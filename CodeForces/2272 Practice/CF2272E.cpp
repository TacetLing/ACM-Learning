#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAXN=200005;
string s1,s2;
int pre_1[MAXN],pre_2[MAXN];
int cnt[MAXN];
int f[MAXN];
int suf[MAXN];
int n,m;
void work(string &B,int b,int pre_b[],string &A,int a,int q){
    for(int i=0;i<=a+1;i++){
        cnt[i]=suf[i]=f[i]=0;
    }
    int last_w=0;
    for(int i=1;i<=a;i++){
        if(A[i]=='W'){
            if(last_w!=0){
                cnt[i-last_w]++;
            }
            last_w=i;
        }
    }
    for(int k=a;k>=1;k--){
        suf[k]=suf[k+1]+cnt[k];
    }
    for(int k=1;k<=a;k++){
        f[k]=f[k-1]+suf[k];
    }
    for(int x=1;x<=b;x++){
        if(B[x]=='R'){
            int p=pre_b[x-1];
            int ans;
            if(p!=0){
                ans=(q==0 ? a+1 : max(a+1,q+x-p));
            }
            else ans=(q==0 ? 1 : 1+x+f[min(x,a)]);
            cout<<ans<<" ";
        }
    }
    cout<<'\n';
    return;
}
void solve(){
    cin>>n>>m>>s1>>s2;
    s1=' '+s1;
    s2=' '+s2;
    for(int i=1;i<=n;i++){
        if(s1[i]=='W') pre_1[i]=i;
        else pre_1[i]=pre_1[i-1];
    }
    for(int i=1;i<=m;i++){
        if(s2[i]=='W') pre_2[i]=i;
        else pre_2[i]=pre_2[i-1];
    }
    work(s1,n,pre_1,s2,m,pre_2[m]);
    work(s2,m,pre_2,s1,n,pre_1[n]);
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
