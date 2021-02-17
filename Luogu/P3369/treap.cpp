// vim: et sw=2 fdm=marker
#include <bits/stdc++.h>
using namespace std;

//{{{
inline int gi() {
  int x, f = 0;
  char c;
  while (!isdigit(c = getchar()))
    if (c == '-')
      f = 1;
  for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
    ;
  return f ? -x : x;
}

inline long long gll() {
  int f = 0;
  long long x;
  char c;
  while (!isdigit(c = getchar()))
    if (c == '-')
      f = 1;
  for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
    ;
  return f ? -x : x;
}

template <typename T> void puti(T x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x > 9)
    puti(x / 10);
  putchar(x % 10 + '0');
}

template <typename T> inline void putsp(T x) { puti(x), putchar(' '); }

template <typename T> inline void putln(T x) { puti(x), putchar('\n'); }
//}}}

const int N = 100010, inf = ~0U >> 1;
int seed = 19260817, key[N], pri[N], cnt[N], sz[N], c[N][2], tot = 0;

inline int ran() { return seed = (seed * 1103515245LL + 12345LL) & inf; }

inline int mk(int k) {
  key[++tot] = k, pri[tot] = ran(), sz[tot] = cnt[tot] = 1,
  c[tot][0] = c[tot][1] = 0;
  return tot;
}

inline void upd(int p) { sz[p] = cnt[p] + sz[c[p][0]] + sz[c[p][1]]; }

inline int tpred(int rt) {
  if (!c[rt][0])
    return 0;
  rt = c[rt][0];
  while (c[rt][1])
    rt = c[rt][1];
  return rt;
}

inline int tsucc(int rt) {
  if (!c[rt][1])
    return 0;
  rt = c[rt][1];
  while (c[rt][0])
    rt = c[rt][0];
  return rt;
}

inline int rot(int p, bool d) {
  int s = c[p][!d];
  if (!s)
    return p;
  int t = c[s][d];
  c[s][d] = p, c[p][!d] = t, upd(p), upd(s);
  return s;
}

int insitem(int rt, int k) {
  if (!rt)
    return mk(k);
  if (k == key[rt]) {
    ++cnt[rt], ++sz[rt];
    return rt;
  }
  bool d = k > key[rt];
  c[rt][d] = insitem(c[rt][d], k), upd(rt);
  if (pri[c[rt][d]] > pri[rt])
    rt = rot(rt, !d);
  return rt;
}

int delitem(int rt, int k) {
  if (!rt)
    return rt;
  if (k < key[rt]) {
    c[rt][0] = delitem(c[rt][0], k), upd(rt);
    return rt;
  } else if (k > key[rt]) {
    c[rt][1] = delitem(c[rt][1], k), upd(rt);
    return rt;
  } else if (cnt[rt] > 1) {
    --cnt[rt], --sz[rt];
    return rt;
  } else if (!c[rt][0] || !c[rt][1])
    return c[rt][0] | c[rt][1];
  else {
    bool d = pri[c[rt][0]] < pri[c[rt][1]];
    rt = rot(rt, !d), c[rt][!d] = delitem(c[rt][!d], k), upd(rt);
    return rt;
  }
}

int getlesscnt(int rt, int k) {
  if (!rt)
    return 0;
  int lsz = sz[c[rt][0]];
  if (k < key[rt])
    return getlesscnt(c[rt][0], k);
  else if (k == key[rt])
    return lsz;
  else
    return lsz + cnt[rt] + getlesscnt(c[rt][1], k);
}

int getkth(int rt, int rk) {
  if (!rt)
    return -inf;
  int lsz = sz[c[rt][0]];
  if (rk <= lsz)
    return getkth(c[rt][0], rk);
  else if (rk <= lsz + cnt[rt])
    return key[rt];
  else
    return getkth(c[rt][1], rk - lsz - cnt[rt]);
}

int pred(int rt, int k) {
  if (!rt)
    return -inf;
  if (k == key[rt]) {
    int p = tpred(rt);
    if (!p)
      return -inf;
    else
      return key[p];
  } else if (k < key[rt])
    return pred(c[rt][0], k);
  else
    return max(key[rt], pred(c[rt][1], k));
}

int succ(int rt, int k) {
  if (!rt)
    return inf;
  if (k == key[rt]) {
    int p = tsucc(rt);
    if (!p)
      return inf;
    else
      return key[p];
  } else if (k > key[rt])
    return succ(c[rt][1], k);
  else
    return min(key[rt], succ(c[rt][0], k));
}

int main() {
  int _ = gi(), rt = 0;
  while (_--) {
    int opt = gi(), x = gi();
    if (opt == 1)
      rt = insitem(rt, x);
    else if (opt == 2)
      rt = delitem(rt, x);
    else if (opt == 3)
      putln(1 + getlesscnt(rt, x));
    else if (opt == 4)
      putln(getkth(rt, x));
    else if (opt == 5)
      putln(pred(rt, x));
    else if (opt == 6)
      putln(succ(rt, x));
  }
  return 0;
}
