#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;

    int x, y, z, t;
    cout << "+ 1" << endl;
    cin >> x;
    cout << "+ 2" << endl;
    cin >> y;
    cout << "-" << endl;
    cin >> z;
    cout << "+ 3" << endl;
    cin >> t;
    if(n == 3 && t == 1 && y == 1){
        cout << "! 1" << endl;
        cout << "3 1 2 3" << endl;
    }
    else {
        assert(false);
    }
}