int memo[1000][1000];

bool first = true;
char *p01, *p02;

typedef long long ll;

bool isMatch2(const char *p2, const char *p1) {
  if (memo[(ll)(p2-p02)][(ll)(p1-p01)] != -1) return memo[(ll)(p2-p02)][(ll)(p1-p01)];
  if (!*p1) return !*p2;
  if (*p1 == *p2 || (*p1 == '.' && *p2)) {
    if (*(p1+1) == '*')
      return memo[(ll)(p2-p02)][(ll)(p1-p01)] = isMatch2(p2+1, p1+2) || isMatch2(p2+1, p1) || isMatch2(p2, p1+2);
    else
      return memo[(ll)(p2-p02)][(ll)(p1-p01)] = isMatch2(p2+1, p1+1);
  } else if (*(p1+1) == '*') return memo[(ll)(p2-p02)][(ll)(p1-p01)] = isMatch2(p2, p1+2);
  return memo[(ll)(p2-p02)][(ll)(p1-p01)] = false;
}

bool isMatch(const char *p2, const char *p1) {
  memset(memo, -1, sizeof memo);
  p02 = (char *)p2;
  p01 = (char *)p1;
  return isMatch2(p2, p1);
}
