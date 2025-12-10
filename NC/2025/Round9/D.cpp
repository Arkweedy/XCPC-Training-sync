#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


constexpr int MAXN = 305 , MAXK = 26;
string str;
struct Palindromes_Automaton {
    int Size , Last , Root0 , Root1 , Trans[ MAXN + 5 ][ MAXK + 5 ] , Link[ MAXN + 5 ];
    int Len[ MAXN + 5 ] , Cnt[ MAXN + 5 ];

    Palindromes_Automaton( ) {
        Root0 = Size ++ , Root1 = Size ++; Last = Root1;
        Len[ Root0 ] = 0  , Link[ Root0 ] = Root1;
        Len[ Root1 ] = -1 , Link[ Root1 ] = Root1; 
    }

    void Extend( int ch , int dex ) {
        int u = Last;
        for( ; str[ dex ] != str[ dex - Len[ u ] - 1 ] ; u = Link[ u ] );
        if( !Trans[ u ][ ch ] ) {
            int Newnode = ++ Size , v = Link[ u ];
            Len[ Newnode ] = Len[ u ] + 2;
            for( ; str[ dex ] != str[ dex - Len[ v ] - 1 ] ; v = Link[ v ] );
            Link[ Newnode ] = Trans[ v ][ ch ]; Trans[ u ][ ch ] = Newnode;
        }
        Last = Trans[ u ][ ch ];
        Cnt[ Last ] ++;
    }
    void Build( string str ) {
        int len = str.length();
        for( int i = 0 ; i < len ; i ++ )
            Extend( str[ i ] - 'a' + 1 , i );
    }
    ll Calc() {
        ll Ans = 0;
        for( int i = Size ; i >= 0 ; i -- ){
            Cnt[Link[ i ]] += Cnt[ i ] ;
        }
        for(int i = 2;i <= Size;i++){
            if(Len[i] - Len[Link[i]] != 0 && Len[i] % (Len[i] - Len[Link[i]]) == 0){
                Ans += 1ll *  Cnt[i] * (Len[i] / (Len[i] - Len[Link[i]]) - 1);
            }
        }
        return Ans;
    }
}PAM;


void solve()
{
    int n;
    cin>>n;
    cin>>str;
    PAM.Build(str);
    cout<<PAM.Calc()<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}