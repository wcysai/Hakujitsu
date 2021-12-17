#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 4e5 + 233;
const int sigma_size = 10;
 
const int mod = 998244353;
using ll = long long;
 
int ch[maxn][sigma_size];
int val[maxn];
int f[maxn];
int last[maxn];
int sz;
int tag[maxn];
 
void init(){
    sz = 1;
    memset(ch[0], 0, sizeof(ch[0]));
}
 
int idx(char c) {
    return c - '0';
}

void add(int &x, int y) {
    x += y;
    if(x >= mod) x -= mod;
}
 
void insert(char *s, int value) {
    int n = strlen(s);
    int u = 0;
    for (int i = 0; i < n; i += 1) {
        int c = idx(s[i]);
        if(!ch[u][c]) {
            ch[u][c] = sz;
            memset(ch[sz], 0, sizeof(ch[sz]));
            val[sz++] = 0;
        }
        u = ch[u][c];
    }
    add(val[u], value);
    tag[u] = 1;
}
 
void getfail(){
    queue<int> q;
    f[0] = 0;
    for (int i = 0; i < sigma_size; i += 1) {
        int u = ch[0][i];
        if(u) {
            f[u] = last[u] = 0;
            q.push(u);
        }
    }
    while(!q.empty()) {
        int r = q.front();
        q.pop();
        add(val[r], val[f[r]]);
        tag[r] |= tag[f[r]];
        for (int c = 0; c < sigma_size; c += 1) {
            int u = ch[r][c];
            if(!u) {
                ch[r][c] = ch[f[r]][c];
                continue;
            }
            q.push(u);
            int v = f[r];
            while(v && !ch[v][c]) v = f[v];
            f[u] = ch[v][c];
            last[u] = tag[f[u]] ? f[u] : last[f[u]];
        }
    }
}
 
int n, q;
char s[maxn];
int go[10][100005][21];
int sum[10][100005][21];
vector<tuple<int, int, int, int, int> > lst;


pair<int, int> find_nx(int pos, int d, int step) {
    int ret = 0;
    for (int i = 20; i >= 0; i -= 1) {
        if(step >= (1 << i)) {
            step -= 1 << i;
            add(ret, sum[d][pos][i]);
            pos = go[d][pos][i];
        }
    }
    return make_pair(pos, ret);
}
 
int main(){
    scanf("%d", &n);
    init();
    for (int i = 0; i < n; i += 1) {
        int x;
        scanf("%s %d", s, &x);
        insert(s, x);
    }
    getfail();
    for (int d = 0; d < 10; d += 1) {
        for (int i = 0; i < sz; i += 1) {
            go[d][i][0] = ch[i][d];
            sum[d][i][0] = val[ch[i][d]];
        }
    }
    for (int d = 0; d < 10; d += 1) {
        for (int i = 1; i <= 20; i += 1) {
            for (int j = 0; j < sz; j += 1) {
                go[d][j][i] = go[d][go[d][j][i - 1]][i - 1];
                sum[d][j][i] = (sum[d][j][i - 1] + sum[d][go[d][j][i - 1]][i - 1]) % mod;
            }
        }
    }
    lst.emplace_back(0, 0, 0, 0, 0);
    scanf("%s", s + 1);
    n = strlen(s + 1);
    {
        int u = 0;
        for (int i = 1; i <= n; i += 1) {
            u = ch[u][idx(s[i])];
            lst.emplace_back(i, i, u, idx(s[i]), (get<4>(lst.back()) + val[u]) % mod);
        }
    }
    scanf("%d", &q);
    while(q--) {
        int op, l, c;
        scanf("%d %d", &op, &l);
        if(op == 1) {
            l = n - l + 1;
            scanf("%d", &c);
            while(get<0>(lst.back()) >= l) {
                lst.pop_back();
            }
            if(get<1>(lst.back()) >= l) {
                auto [pl, pr, pos, nd, cur_sum] = lst.back();
                lst.pop_back();
                auto [nxt, nxt_sum] = find_nx(get<2>(lst.back()), nd, l - pl);
                lst.emplace_back(pl, l - 1, nxt, nd, (get<4>(lst.back()) + nxt_sum) % mod);
            }
            auto [nxt, nxt_sum] = find_nx(get<2>(lst.back()), c, n - l + 1);
            lst.emplace_back(l, n, nxt, c, (get<4>(lst.back()) + nxt_sum) % mod);
        }
        else{
            int lo = 0, hi = int(lst.size()) - 1, ans = 0;
            while(hi >= lo) {
                int mid = lo + hi >> 1;
                if(get<1>(lst[mid]) <= l) {
                    lo = mid + 1;
                    ans = mid;
                }
                else hi = mid - 1;
            }
            int res = get<4>(lst[ans]);
            if(get<1>(lst[ans]) < l) {
                auto [nxt, nxt_sum] = find_nx(get<2>(lst[ans]), get<3>(lst[ans + 1]), l - get<1>(lst[ans]));
                add(res, nxt_sum);
            }
            printf("%d\n", res);
        }
 
        /*
        for (auto [pl, pr, pos, nd, sum] : lst) {
            cerr << pl << " " << pr << " " << pos << " " << nd << " " << sum << endl;
        }
        */
 
    }
    return 0;
}
 
/*
2
479 1
666 2
666479
5
2 6
1 3 6
2 5
1 4 2
2 4
 
3
123 2
234 3
333 5
123234345123    
8
2 5
2 6
1 4 3
2 8
2 9
2 12
1 6 5
2 12
*/