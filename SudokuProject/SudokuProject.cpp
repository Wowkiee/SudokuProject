// SudokuProject.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#pragma warning(disable : 4996)

int IO::Input(char *s) {
	int len = strlen(s);
	// s == ""
	if (len == 0) return -1;
	// 
	for (int i = 0; i < len; ++i) {
		if ('0' > s[i] || s[i] > '9') return -1;
	}
	// lead 0
	if (len != 1 && s[0] == '0') return -1;
	// get res
	int res = 0;
	for (int i = 0; i < len; ++i) {
		res = res * 10 + s[i] - '0';
	}
	return res;
}

int n, cnt, myColor, myColorIndex;
int digit[81], result[9][9];
bool col[9][9], row[9][9], block[9][9];

void init() {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			digit[i * 9 + j] = i + 1;
			if (i + 1 == myColor && myColorIndex == -1) myColorIndex = i * 9 + j;
		}
	}
	result[0][0] = myColor;
	col[myColor][0] = row[myColor][0] = block[myColor][0] = true;
}
void Output() {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (!result[i][j]) result[i][j] = 9;
			putchar(result[i][j] + '0');
			char ch = " \n"[j+1==9];
			putchar(ch);
		}
	}
	putchar('\n');
}
void dfs(int Ind) {
	if (cnt >= n) return;
	int val = digit[Ind];
	// Output
	if (val == 9) {
		Output();
		++cnt;
		return;
	}
	// 
	if (Ind == myColorIndex) {
		dfs(Ind + 1);
		return;
	}
	// 
	for (int b = 0; b < 9; ++b) if (block[val][b] == false) {
		int X = b / 3, Y = b % 3;
		for (int x = X * 3; x < (X + 1) * 3; ++x) if (row[val][x] == false) {
			for (int y = Y * 3; y < (Y + 1) * 3; ++y) if (col[val][y] == false && !result[x][y]) {
				block[val][b] = row[val][x] = col[val][y] = true;
				result[x][y] = val;
				dfs(Ind + 1);
				block[val][b] = row[val][x] = col[val][y] = false;
				result[x][y] = 0;
			}
		}
		break;
	}
}
void solve() {
	myColor = (3 + 6) % 9 + 1;
	myColorIndex = -1;
	init();
	dfs(0);
}

int main(int argc, char * argv[]) {
	freopen("sudoku.txt", "w", stdout);
	if (argc != 3) {
		puts("Input error");
	}
	else {
		IO io; n = io.Input(argv[2]);
		if (n == -1) {
			puts("Input error");
		}
		else {
			solve();
		}
	}
	return 0;
}