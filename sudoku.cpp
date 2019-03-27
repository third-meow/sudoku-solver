#include<bits/stdc++.h>
using namespace std;

#define oneThruNine {1, 2, 3, 4, 5, 6, 7, 8, 9};

vector<vector<int>> unsolved;
vector<vector<int>> start;
vector<vector<vector<int>>> done;

vector<int> getSquareCoOrds(int x, int y) {
	return {(x - (x % 3)),
					(y - (y % 3))};
}


vector<int> getNeighbours(int x, int y) {
	vector<int> neighbours;
	for(int i = 0; i < 9; ++i) {
		for(int j = 0; j < 9; ++j) {
			if (done[i][j].size() == 1) {
				if (i == x || j == y) {
					neighbours.push_back(done[i][j][0]);
				}
			}
		}
	}

	vector<int> sq = getSquareCoOrds(x, y);
	for(int i = sq[0]; i < (sq[0] + 3); ++i) {
		for(int j = sq[1]; j < (sq[1] + 3); ++j) {
			if (done[i][j].size() == 1) {
				neighbours.push_back(done[i][j][0]);
			}
		}
	}

	vector<int> result;
	for(int i = 0; i <= 9; ++i) {
		if (find(neighbours.begin(), neighbours.end(), i) != neighbours.end()) {
			result.push_back(i);
		}
	}

	return result;
}


bool takeStep() {
	cout << endl << "*";
	if (unsolved.size() < 1) {
		//no unsolved number slots 
		return true;
	}

	for(int o = 0; o < unsolved.size(); ++o) {
		cout << "-";
		int x = unsolved[o][0];
		int y = unsolved[o][1];
		vector<int> neighbours = getNeighbours(x, y);

		for(auto n : neighbours) {
			auto pos = find(done[x][y].begin(), done[x][y].end(), n);
			if (pos != done[x][y].end()) {
				//remove 
				done[x][y].erase(pos);
			}
		}
	}
	return false;
}

void cleanUnsolved() {
	for(int o = 0; o < unsolved.size(); ++o) {
		int i, j;
		i = unsolved[o][0];
		j = unsolved[o][1];
		if (done[i][j].size() == 1) {
			start[i][j] = done[i][j][0];
			unsolved.erase(unsolved.begin() + o);
			--o;
		}
	}

}


int main(int argc, char *argv[]) {
	start = vector<vector<int>>(9, vector<int>(9);
	done = vector<vector<vector<int>>>(9, vector<vector<int>>(9));

	// -------------------------------- READ IT
	for(int i = 0; i < 9; ++i) {
		for(int j = 0; j < 9; ++j) {
			cin >> start[i][j];
			if (start[i][j] != 0) {
				done[i][j].push_back(start[i][j]);
			} else {
				done[i][j] = oneThruNine;
				// record position of unsolved position
				unsolved.push_back({i, j});
			}
		}
	}

	// -------------------------------- SOLVE IT
	while(!takeStep()) {
		cleanUnsolved();
	}

	// -------------------------------- PRINT IT
	for(auto r : start) {
		cout << endl;
		for(auto e : r) {
			cout << e << " ";
		}
	}

	return 0;
}

