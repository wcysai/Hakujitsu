//
// Created by 65350 on 2021/11/13.
//
#include <bits/stdc++.h>

#define F(i, j, k) for(int i=(j);i<=(k);++i)
#define D(i, j, k) for(int i=(j);i>=(k);--i)
#define rep(it, s) for(__typeof(s.begin()) it=s.begin();it!=s.end();++it)
#define Rep(a, s) for(auto a:s)
#define PB push_back
#define EB emplace_back
#define MP make_pair
#define FF first
#define SS second
typedef long long ll;
typedef unsigned long long ull;
using namespace std;

const int N  = 100005;

int a[N];

struct T{
    ll mx, mn, sum;
    //int setv;
    ll  addv;
}t[N<<2];

#define max(a, b) ((a) > (b)? (a) : (b))
#define min(a, b) ((a) < (b)? (a) : (b))

void pushup(int pos){
    t[pos].mx = max (t[pos<<1].mx, t[pos<<1|1].mx);
    t[pos].mn = min (t[pos<<1].mn, t[pos<<1|1].mn);
    t[pos].sum = t[pos<<1].sum + t[pos<<1|1].sum;
}

void build(int pos, int l, int r){
    if(l == r){
        t[pos].mx = t[pos].mn = t[pos].sum = a[l];
        return ;
    }
    int mid = (l + r) >> 1;
    build(pos<<1, l, mid);
    build(pos<<1|1, mid + 1, r);
    pushup(pos);
}

void pushdown(int pos, int l, int r){
//    if(t[pos].setv){
//        t[pos<<1].setv = t[pos<<1|1].setv = t[pos].setv;
//        t[pos<<1].addv = t[pos<<1|1].addv = 0;
//        t[pos<<1].mx = t[pos<<1].mn = t[pos<<1|1].mx = t[pos<<1|1].mn = t[pos].setv;
//        int mid = (l + r) >> 1;
//        t[pos<<1].sum = 1LL * (mid - l + 1) * t[pos].setv;
//        t[pos<<1|1].sum = 1LL * (r - mid) * t[pos].setv;
//        t[pos].setv = 0;
//    }
    if(t[pos].addv){
        t[pos<<1].addv += t[pos].addv;
        t[pos<<1|1].addv += t[pos].addv;
        t[pos<<1].mx += t[pos].addv;
        t[pos<<1].mn += t[pos].addv;
        t[pos<<1|1].mx += t[pos].addv;
        t[pos<<1|1].mn += t[pos].addv;
        int mid = (l + r) >> 1;
        t[pos<<1].sum += 1LL * (mid - l + 1) * t[pos].addv;
        t[pos<<1|1].sum += 1LL * (r - mid) * t[pos].addv;
        t[pos].addv = 0;
    }
}

void update_sqrt(int pos, int l, int r, int a, int b){
    if(a <= l && r <= b){
        //int v = ((int)sqrt(t[pos].mx));
        if(t[pos].mx == t[pos].mn){
            int v = t[pos].mx - ((int)sqrt(t[pos].mx));
            //t[pos].setv = v;
            //t[pos].addv = 0;
            //t[pos].mx = t[pos].mn = v;
            //t[pos].sum = 1LL * (r - l + 1) * v;
            t[pos].addv -= v;
            t[pos].mx -= v;
            t[pos].mn -= v;
            t[pos].sum -= 1LL * (r - l + 1) * v;
            return ;
        }
    }
    if(l > b || r < a) return ;
    pushdown(pos, l, r);
    int mid = (l + r)>>1;
    update_sqrt(pos<<1, l, mid, a, b);
    update_sqrt(pos<<1|1, mid + 1, r, a, b);
    pushup(pos);
}

void update_add(int pos, int l, int r, int a, int b, int v){
    if(a <= l && r <= b){
        t[pos].addv += v;
        t[pos].mx += v;
        t[pos].mn += v;
        t[pos].sum += 1LL * (r - l + 1) * v;
        return ;
    }
    if(l > b || r < a) return ;
    pushdown(pos, l, r);
    int mid = (l + r)>>1;
    update_add(pos<<1, l, mid, a, b, v);
    update_add(pos<<1|1, mid + 1, r, a, b, v);
    pushup(pos);
}

ll query(int pos, int l, int r, int a, int b){
    if(a <= l && r <= b) return t[pos].sum;
    if(l > b || r < a) return 0;
    pushdown(pos, l, r);
    int mid = (l + r)>>1;
    return query(pos<<1, l, mid, a, b) + query(pos<<1|1, mid+1, r, a, b);
}

void print(int pos, int l, int r){
    cout << l << ' ' << r << ' ' << t[pos].mx << ' ' << t[pos].mn << endl;
    if(l == r){
        //cout << t[pos].mn << ' ';
        return ;
    }
    int mid = (l + r) >> 1;
    pushdown(pos, l, r);
    print(pos<<1, l, mid);
    print(pos<<1|1, mid + 1, r);
}

int main() {
#ifndef ONLINE_JUDGE
    //freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, Q;
    cin >> n >> Q;
    F(i,1,n) cin >> a[i];
    build(1, 1, n);
    //print(1, 1, n);cout << endl;
    while(Q --){
        int opt, l, r, v;
        cin >> opt;
        if(opt == 1){
            cin >> l >> r >> v;
            update_add(1, 1, n, l, r, v);
        }
        if(opt == 2){
            cin >> l >> r;
            update_sqrt(1, 1, n, l, r);
        }
        if(opt == 3){
            cin >> l >> r;
            cout << query(1, 1, n, l, r) << '\n';
        }
        //print(1, 1, n);cout << endl;
    }
    //int v = ((int)sqrt(2)); cout << v << endl;
    return 0;
}