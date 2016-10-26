#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

typedef long long ll;

int main(int argc, char **argv) {
	if (argc < 2) {
		cerr << "Missing argument" << endl;
		return 1;
	}

	int N = atoi(argv[1]);

	if (N <= 0) {
		cerr << "Invalid argument" << endl;
		return 1;
	}

	ll K = max(500000, int(N*4.05)); //FOR N > 100000, density <= 4.05

	vector<bool> isPrime(K + 1);

	// Sieve of atkin to generate all primes up to K
	// O(n)
	isPrime[2] = isPrime[3] = true;
	for (ll i = 5; i <= K; i++)
		isPrime[i] = false;

	ll lim = ceil(sqrt(K));
	for (ll x = 1; x <= lim; x++) {
		for (ll y = 1; y <= lim; y++) {
			ll num = (4 * x * x + y * y);
			if (num <= K && (num % 12 == 1 || num % 12 == 5))
				isPrime[num] = true;
			num = (3 * x * x + y * y);
			if (num <= K && (num % 12 == 7))
				isPrime[num] = true;
			if (x > y) {
				num = (3 * x * x - y * y);
				if (num <= K && (num % 12 == 11))
					isPrime[num] = true;
			}
		}
	}

	for (ll i = 5; i <= lim; i++)
		if (isPrime[i])
			for (ll j = i * i; j <= K; j += i)
				isPrime[j] = false;

	//List of primes
	vector<int> primes;
	primes.reserve(1.26*K/log(K)); //avoid resizing by reserving an upper bound of pi(x)
	for (ll i = 2; i <= K; i++)
		if (isPrime[i])
			primes.push_back(i);

	queue<pair<int, pair<int, int>>> q;
	q.push(make_pair(1, make_pair(0, 0)));
	vector<int> nextUnvisited(K+1, 0), prevUnvisited(K+1, 0);
	for(int i = 1; i <= K; i++) {
		nextUnvisited[i] = i+1;
		prevUnvisited[i] = i-1;
	}

	vector<vector<ll>> ppowers(primes.size(), vector<ll>());
	for(ll i = 0; i < primes.size(); i++) {
		ppowers[i].push_back(1);
		while(ppowers[i].back() <= K) ppowers[i].push_back(primes[i]*ppowers[i].back());
	}

	nextUnvisited[0] = 2;
	prevUnvisited[2] = 0;
	nextUnvisited[1] = -1;
	prevUnvisited[1] = -1;

	vector<ll> divisorsSum(K+1, 0);
	divisorsSum[1] = 1;

	//BFS numbers while calculating sum of divisors
	//Better complexity than sieve of erathostenes but high overhead
	//Should have better performance for N >= 10^10
	while(nextUnvisited[0] <= K) {
		ll currentNum = q.front().first;
		ll k = q.front().second.first;
		ll t = q.front().second.second;
		q.pop();

		for(ll i = k; i < primes.size(); i++) {
			ll cur = (i == k ? t : 0);
			ll p = primes[i];
			ll nextNum = currentNum * p;
			if (nextNum > K) break;

			q.push(make_pair(nextNum, make_pair(i, (i == k) ? t + 1 : 1)));
			nextUnvisited[prevUnvisited[nextNum]] = nextUnvisited[nextNum];
			prevUnvisited[nextUnvisited[nextNum]] = prevUnvisited[nextNum];
			nextUnvisited[nextNum] = prevUnvisited[nextNum] = -1;
			divisorsSum[nextNum] = divisorsSum[currentNum] + divisorsSum[currentNum/ppowers[i][cur]]*(ppowers[i][cur+1]);
		}
	}

	// Print first N abundant numbers
	for(ll i = 1; N; i++) {
		if (divisorsSum[i] > 2*i) {
			printf("%d\n", i);
			N--;
		}
	}

	return 0;
}
