#include<bits/stdc++.h>
using ll = long long;
using namespace std;

constexpr int N = 200;
struct node{char c;int num;};
int win[N][N];
void solve()
{
    string s;cin>>s;
    stack<node> st;
    for(int i=0;i<s.length();i++)
    {
        char c=s[i];
        if(!st.size()) st.push({c,1});
        else 
        {
            char cc=st.top().c;
            if(cc==c) st.top().num++;
            else if(win[cc][c]) st.push({c,1});
            else 
            {
                auto no=st.top();
                st.pop();
                no.c=c;no.num++;
                if(st.size()) 
                {
                    st.top().num+=no.num;
                }
                else st.push(no);
            }
        }
    }
    while(st.size()!=1) st.pop();
    cout<<st.top().c<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    win['S']['P']=win['P']['R']=win['R']['S']=1;
    int tt = 1;
    cin>>tt;
    while (tt--)
    {
        solve();
    }
    return 0;    
}
