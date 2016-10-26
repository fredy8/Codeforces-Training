#include <cstdio>
#include <cstdlib>
#include <vector>

int main(int argc, char **argv) {
	if (argc < 2) {
		puts("Missing argument");
		return 1;
	}

	int N = atoi(argv[1]);
	int K = std::max(100000, int(N*4.05));

	if (N <= 0) {
		puts("Invalid argument");
		return 1;
	}

	std::vector<int> sums(K, 0), abundant(K, 0);

    for (int i = 1; i < K; ++i)
		for (int j = 1; j * i < K; j++)
			sums[i * j] += i;

    for (int i = 12; N; ++i)
		if (sums[i] > (i << 1)) {
			N--;
			printf("%d\n", i);
		}

	return 0;
}
