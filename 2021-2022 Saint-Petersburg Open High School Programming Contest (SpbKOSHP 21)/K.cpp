#include <bits/stdc++.h>
using namespace std;

using db = long double;

int T, a;

db f(db x) {
    return 6.0 * (100 - a) / T * (x - T / 6.0) + a;    
}

db cal(db x) {
    return 1.0 * (T - x) * f(x); 
}

int main(){
    cin >> a >> T;
    cout << fixed << setprecision(15);
    db lo = T / 6.0;
    db hi = T / 3.0;
    for (int i = 1; i <= 5000; i += 1) {
        db m1 = lo + (hi - lo) / 3;
        db m2 = lo + (hi - lo) / 3 * 2;
        if(cal(m1) > cal(m2)) {
            hi = m2;
        }
        else lo = m1;
    }
    cout << double(cal(lo)) << "\n";
    return 0;
}