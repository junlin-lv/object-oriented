#include<iostream>
#include<string>
using namespace std;

class Grid {
public:
	string grid[9][9];
	int Box_SIZE;
	int GRID_SIZE;
	
	//获取行
	string* getRow(int row) {
		return grid[row-1];
	}
	//获取列
	string* getColumn(int col) {
		string *Col=new string[9];
		for (int row = 0; row < 9; row++) {
			Col[row] = grid[row][col-1];
		}
		return Col;
	}
	//获取小九宫格
	string* getBox(int row,int col) {
		string *box=new string[9];
		int startRow = (row-1) / 3 * 3;
		int startCol = (col-1) / 3 * 3;
		int count = 0;
		for (int row = startRow; row < startRow+3; row++) {
			for (int col = startCol; col < startCol + 3; col++) {
				box[count] = grid[row][col];
				count++;
			}
		}
		return box;
	}
};

class Sudoku :public Grid {
public:
	//解析字符串
	void parse(string input) {
		for (int i = 0; i < 81; i++) {
			int row = i / 9;
			int col = i % 9;
			grid[row][col] = string(1, input[i]);
		}
	}
	//判断能否填入
	bool issafe(int row, int col, char num) {
		string* str_row = getRow(row);
		string* str_col = getColumn(col);
		string* str_box = getBox(row, col);
		for (int i = 0; i < 9; i++) {
			if (str_row[i] == string(1,num)) return false;
			if (str_col[i] == string(1, num)) return false;
			if (str_box[i] == string(1, num)) return false;
		}
		return true;
	}

	//获取候选值
	string** getInference(void) {
		string** candidate = new string * [9];
		for (int i = 0; i < 9; i++) {
			candidate[i] = new string[9];
		}

		for (int row = 1; row < 10; row++) {
			for (int col = 1; col < 10; col++) {			
				for (char s = '1'; s <= '9'; s++) {
					if (grid[row-1][col-1] != "0") {
						candidate[row-1][col-1]+=grid[row-1][col-1];
						break;
					}
					if (issafe(row, col, s))
						candidate[row-1][col-1] += s;
				}
			}
		}
		return candidate;
		}
};

int main() {
	string input = "017903600000080000900000507072010430000402070064370250701000065000030000005601720";
	
	Sudoku sudo;
	sudo.parse(input);

	//数独可视化
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			cout << sudo.grid[row][col] << "|";
		}
		cout << endl << "—————————"<<endl;
	}

	string** candidate;
	candidate = sudo.getInference();

	cout << endl << "Candidate:" << endl;
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			cout << "(" << row+1 << "," << col+1 << ")" << ":";
			cout << candidate[row][col]<<"  ";
		}
		cout << endl;
	}
}