#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

/*
 * Complete the function below.
 */
vector < string > getSuspiciousList(vector < string > transactions) {
	int N = transactions.size();

	map<string, pair<string, int>> lastTransaction;

	set<string> suspicious;
	vector<pair<int, string> > suspiciousTime;

	for(int i = 0; i < N; i++) {
		char *p = strtok((char *)transactions[i].c_str(), "|");
		string name, location;
		int amount, time;
		for(int i = 0; i < 4; i++) {
			switch(i) {
				case 0:
					name = string(p);
					break;
				case 1:
					amount = atoi(p);
					break;
				case 2:
					location = string(p);
					break;
				case 3:
					time = atoi(p);
					break;
			}
			p = strtok(NULL, "|");
		}

		if (suspicious.find(name) == suspicious.end()) {
			if (lastTransaction.find(name) != lastTransaction.end() &&
					lastTransaction[name].first != location && time - lastTransaction[name].second < 60) {
				suspicious.insert(name);
				suspiciousTime.push_back(make_pair(lastTransaction[name].second, name));
			} else if (amount > 3000) {
				suspicious.insert(name);
				suspiciousTime.push_back(make_pair(time, name));
			} else {
				lastTransaction[name] = make_pair(location, time);
			}
		}
	}

	sort(suspiciousTime.begin(), suspiciousTime.end());

	vector<string> suspiciousAccounts;
	for(int i = 0; i < suspiciousTime.size(); i++) {
		suspiciousAccounts.push_back(suspiciousTime[i].second);
	}

	return suspiciousAccounts;
}

int main() {
    vector < string > res;
    
    int _transactions_size = 0;
    cin >> _transactions_size;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    vector<string> _transactions;
    string _transactions_item;
    for(int _transactions_i=0; _transactions_i<_transactions_size; _transactions_i++) {
        getline(cin, _transactions_item);
        _transactions.push_back(_transactions_item);
    }
    
    res = getSuspiciousList(_transactions);
    for(int res_i=0; res_i < res.size(); res_i++) {
    	cout << res[res_i] << endl;;
    }
    
    return 0;
}
