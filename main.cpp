#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;
using vs = vector<string>;

vs board;
int zeroCt;
vii zeroPos;
vii pushed;
bool isFound;

bool isPossible(const int i, const int j, const int k) {
	for (auto ii = 0; ii < 9; ++ii) {
		if (i == ii) {
			continue;
		}

		if ('0' + k == board[ii][j]) {
			return false;
		}
	}

	for (auto jj = 0; jj < 9; ++jj) {
		if (j == jj) {
			continue;
		}

		if ('0' + k == board[i][jj]) {
			return false;
		}
	}

	const auto bi = 3 * (i / 3);
	const auto bj = 3 * (j / 3);
	for (auto y = bi; y < bi + 3; ++y) {
		for (auto x = bj; x < bj + 3; ++x) {
			if (y == i && x == j) {
				continue;
			}

			if ('0' + k == board[y][x]) {
				return false;
			}
		}
	}

	return true;
}

void solve(const int z) {
	if (isFound) {
		return;
	}

	if (pushed.size() == zeroCt) {
		for (const auto& row : board) {
			for (const auto& x : row) {
				cout << x;
			}
			cout << '\n';
		}

		isFound = true;
		return;
	}

	const auto& [y, x] = zeroPos[z];

	for (auto k = 1; k <= 9 && !isFound; ++k) {
		if (!isPossible(y, x, k)) {
			continue;
		}

		board[y][x] = '0' + k;
		pushed.push_back({ y, x });

		solve(z + 1);

		if (isFound) {
			break;
		}

		board[y][x] = '0';
		pushed.pop_back();
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	board = vs(9);
	for (auto&& s : board) {
		cin >> s;
	}

	zeroCt = 0;
	for (auto i = 0; i < 9; ++i) {
		for (auto j = 0; j < 9; ++j) {
			if ('0' == board[i][j]) {
				zeroPos.push_back({ i, j });
				++zeroCt;
			}
		}
	}

	isFound = false;
	solve(0);

	return 0;
}