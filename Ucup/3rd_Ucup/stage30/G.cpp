#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 2e5 + 10;
constexpr int mod = 998244353;

int n,K,a;
ll cnt = 0;

struct mat{
    int a[20][20];
    mat(){
        memset(a,0,sizeof a);
    }
}F[N],A,B;

bool st[N];

mat operator *(mat a,mat b)
{
    mat c;
    for(int i=0;i<K;i++)
        for(int k=0;k<K;k++)
        {
            for(int j=0;j<K;j++) c.a[i][j]=(c.a[i][j]+1ll*a.a[i][k]*b.a[k][j])%mod;
        }
    return c;
}

void print(mat A){
    for(int i=0;i<K;i++){
        for(int j=0;j<K;j++){
            cout<<A.a[i][j]<<' ';
        }
        cout<<endl;
    }
}

void solve()
{
    cin >> n >> K >> a;
    for(int i=0;i<K;i++){
        A.a[i][0] = 1;
    }
    for(int i=1;i<K;i++){
        A.a[i-1][i] = 1;
        B.a[i-1][i] = 1;
    }
    for(int i=1;i<=n;i++){
        string s;cin>>s;
        //string s = string(100000,'O');
        
        //st[i] = s[0] == 'O' : 1 ? 0;
        F[i] = s[0] == 'O' ? A : B;
        for(int j=1;j<s.size();j++){
            if(s[j]=='O')F[i] = F[i] * A;
            else F[i] = F[i] * B;
        }

    }
    for(int i=n+1;i<=n+a;i++){
        int l,r;cin>>l>>r;
        //int l = 1,r = 1;
        F[i] = F[l] * F[r];
    }

    for(int i=1;i<=n+a;i++){
        cout<<F[i].a[K-1][0]<<'\n';
    }
    cerr<<cnt<<endl;
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
   // cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
