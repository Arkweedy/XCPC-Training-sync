#include <bits/stdc++.h>
using ll = long long;
using i64 = long long;
using namespace std;
const int N = 1e6 + 9;
bool ck(char a,char b)
{
    if(a == '+') return b == '+';
    else return b == 'T' || b == 'F';
}
void solve()
{
    int n;
    cin >> n;
    set<int> s;
    map<int,int> ma;
    int cnt = 0;
    vector<char> ch(n);
    vector<int> num(n);
    for(int i = 0;i < n;i ++)
    {
        cin >> ch[i] >> num[i];
        s.insert(num[i]);
    }
    for(const int num : s)
    {
        ma[num] = ++cnt;
    }
    for(int i = 0;i < n;i++)
    {
        num[i] = ma[num[i]];
    }
    vector<bool> ist(cnt + 1,false);
    vector<int> la(cnt + 1,-1);
    vector<bool> isf(cnt + 1,false);

    vector<char> ans;

    stack<int> st;
    vector<bool> isinst(cnt + 1,false);
    int l = 0,r = 0;
    while(l < n)
    {

        while(r < n && ck(ch[l],ch[r])) 
        {
            r++;

        }
        if(ch[l] == '+')
        {
            int jl = r;
            int jr = r;
            while(jr < n && ck(ch[jl],ch[jr])) jr++;
            for(int i = jl ;i < jr;i++)
            {
                if(ch[i] == 'F')
                {
                    isf[num[i]] = true;
                }
                else ist[num[i]] = true;
            }
            
            for(int i = l;i < r;i ++)
            {
                la[num[i]] = i;
            }
            for(int i = l;i < r;i ++)
            {
                if(ist[num[i]] || (!ist[num[i]] && !isf[num[i]]))
                {
                    if(la[num[i]] == i)
                    {

                        ans.push_back('+');
                        isinst[num[i]] = true;
                        st.push(num[i]);
                    }
                    else
                    {
                        ans.push_back('+');
                        ans.push_back('-');
                    }
                }
                else
                {
                    ans.push_back('+');
                    ans.push_back('-');
                }
            }
            for(int i = jl ;i < jr;i++)
            {
                if(ch[i] == 'F')
                {
                    isf[num[i]] = false;
                }
                else ist[num[i]] = false;
            }
        }
        else
        {

            for(int i = l;i < r;i++)
            {
                if(ch[i] == 'F')
                {
                    //cerr << num[i] << ' ' << isinst[num[i]] << '\n';
                    while(isinst[num[i]])
                    {
                        isinst[st.top()] = false;
                        st.pop();
                        ans.push_back('-');
                    }
                }
                ans.push_back('?');
            }
            int jl = r;
            int jr = r;
            while(jr < n && ck(ch[jl],ch[jr])) jr++;
            for(int i = jl;i < jr;i++)
            {
                if(isinst[num[i]])
                {
                    isinst[st.top()] = false;
                    st.pop();
                    ans.push_back('-');
                }
            }   

        }
        l = r;
    }
    while(!st.empty())
    {
        isinst[st.top()] = false;
        st.pop();
        ans.push_back('-');
    }
    for(const char ch : ans)
    {
        cout << ch;
    }
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}