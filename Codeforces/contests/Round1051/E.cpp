#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    string s;
    cin>>s;
    n = s.length();

    //cin>>n>>s;
    int cl = count(s.begin(),s.end(), '(');
    int cr = n - cl;
    if(abs(cr - cl) % 4 != 0){
        ///cerr<<"check invaild"<<endl;
        //cerr<<cl<<" "<<cr<<endl;
        cout<<-1<<endl;
        return;
    }

    

    stack<char>st;
    //first (( -> ))
    //second flip it early
    reverse(s.begin(),s.end());
    for(int i = 0;i < n;i++){
        if(st.empty())st.push(i);
        else{
            if(s[i] == '('){
                if(s[st.top()] == '('){
                    s[i] = ')';
                    s[st.top()] = ')';
                    st.pop();
                }
                else{
                    st.push(i);
                }
            }
            else{//')'
                if(s[st.top()] == '('){
                    //st.push(i);
                    int x = st.top();
                    st.pop();
                    if(st.empty() || st.top() == ')'){
                        st.push(x);
                        st.push(i);
                    }
                    else{
                        s[x] = ')';
                        s[st.top()] = ')';
                        st.pop();
                        st.push(i);
                    }
                }
                else{
                    st.push(i);
                }
            }
        }
    }
    reverse(s.begin(),s.end());
    cerr<<s<<endl;

    while(!st.empty())st.pop();

    cl = count(s.begin(),s.end(), '(');
    cr = n - cl;
    
    int opcnt = (cr - cl) / 4;

    for(int i = 0;i < n;i++){
        if(st.empty())st.push(i);
        else{
            if(s[i] == '('){
                if(s[st.top()] == '('){
                    st.push(i);
                }
                else{
                    int x = st.top();
                    st.pop();
                    //))( -> ())
                    if(st.empty() || st.top() == '('){
                        st.push(x);
                        st.push(i);
                    }
                    else{
                        s[st.top()] = '(';
                        st.pop();
                        s[x] = ')';
                        s[i] = ')';
                        st.push(x);
                        st.push(i);
                    }
                    
                }
            }
            else{//')'
                if(s[st.top()] == '('){
                    //st.pop();
                    st.push(i);
                }
                else{
                    if(opcnt > 0){
                        opcnt--;
                        s[i] = '(';
                        s[st.top()] = '(';
                        st.pop();
                    }
                }
            }
        }
    }
    cerr<<s<<endl;

    

    int ok = 1;
    int sum = 0;
    for(int i = 0;i < n;i++){
        if(s[i] == '(')sum++;
        else sum--;
        if(sum < 0){
            ok = 0;
            break;
        }
    }
    

    if(ok){
        cout<<s<<endl;
    }
    else{
        cout<<-1<<endl;
    }
    return;

}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}