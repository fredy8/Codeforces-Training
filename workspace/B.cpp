char get(string &A, int k) {
    if (k >= A.size()) return '0';
    return A[A.size()-1-k];
}

class Solution {
public:
    string addBinary(string A, string B) {
        vector<char> ans;
        int l = max(A.size(), B.size()) + 1;
        bool carry = 0;
        for(int i = 0; i < l; i++) {
            char a = get(A, i);
            char b = get(B, i);
            int c = (a == '1') + (b == '1') + carry;
            carry = c > 1;
            ans.push_back(c & 1 ? '1' : '0');
        }

        auto st = ans.rbegin();
        if (ans.size() > 1 && *ans.rbegin() == '0')
            st++;
        return string(st, ans.rend());
    }
};
