class Solution {
public:
    int minDistance(string A, string B) {
        int n = A.length(), m = B.length();
    	int dist[n+1][m+1];
    	dist[0][0] = 0;
    	for(int i = 1; i < n+1; i++) dist[i][0] = i;
    	for(int j = 1; j < m+1; j++) dist[0][j] = j;
    	for(int i = 1; i < n+1; i++)
    		for(int j = 1; j < m+1; j++)
    			dist[i][j] = min(dist[i-1][j-1] + (A[i-1] != B[j-1]), min(dist[i-1][j] + 1, dist[i][j-1] + 1));
    	return dist[n][m];
    }
};
