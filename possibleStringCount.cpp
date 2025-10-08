class Solution {
public:
    const int MOD = 1e9 + 7;

    int possibleStringCount(string word, int k) {
        int n = word.size();
        vector<int> runs;
        int runLen = 1;

        for (int i = 1; i < n; ++i) {
            if (word[i] == word[i - 1]) {
                runLen++;
            } else {
                runs.push_back(runLen);
                runLen = 1;
            }
        }
        runs.push_back(runLen);

        int m = runs.size();
        long long total = 1;
        for (int L : runs) {
            total = total * L % MOD;
        }

        int maxReduction = n - m;
        int T = n - k;

        if (T >= maxReduction) {
            return total;
        }

        vector<int> dp(T + 1, 0);
        dp[0] = 1;

        for (int L : runs) {
            vector<int> ndp(T + 1, 0);
            for (int s = 0; s <= T; ++s) {
                if (dp[s] == 0) continue;
                for (int r = 0; r < L; ++r) {
                    if (s + r <= T) {
                        ndp[s + r] = (ndp[s + r] + dp[s]) % MOD;
                    }
                }
            }
            dp = ndp;
        }

        long long valid = 0;
        for (int s = 0; s <= T; ++s) {
            valid = (valid + dp[s]) % MOD;
        }

        return valid;
    }
};
