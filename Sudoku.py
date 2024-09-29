class Grid():
    grid = [["0" for i in range(9)] for i in range(9)]
    Box_SIZE = 3
    GRID_SIZE = 9

    # 获取行
    def getRow(self, row):
        return self.grid[row - 1]

    # 获取列
    def getColumn(self, col):
        Col = ['' for i in range(9)]
        for row in range(9):
            Col[row] = self.grid[row][col - 1]
        return Col

    # 获取小九宫格
    def getBox(self, row, col):
        box = ['' for i in range(9)]
        startRow = (row - 1) // 3 * 3
        startCol = (col - 1) // 3 * 3
        count = 0
        for row in range(startRow, startRow + 3):
            for col in range(startCol, startCol + 3):
                box[count] = self.grid[row][col]
                count += 1
        return box


class Sudoku(Grid):
    # 解析字符串
    def parse(self, input):
        for i in range(0, 81):
            row = i // 9
            col = i % 9
            self.grid[row][col] = input[i]

    # 判断能否填入
    def issafe(self, row, col, num):
        strRow = self.getRow(row)
        strCol = self.getColumn(col)
        strBox = self.getBox(row, col)
        for i in range(9):
            if strRow[i] == num:
                return False
            if strCol[i] == num:
                return False
            if strBox[i] == num:
                return False
        return True

    # 获取候选值
    def getInference(self):
        candidate = [["" for i in range(9)] for i in range(9)]
        for row in range(1, 10):
            for col in range(1, 10):
                for c in "123456789":
                    if self.grid[row - 1][col - 1] != "0":
                        candidate[row - 1][col - 1] = self.grid[row - 1][col - 1]
                        break
                    if self.issafe(row, col, c):
                        candidate[row - 1][col - 1] += c
        return candidate


input = "017903600000080000900000507072010430000402070064370250701000065000030000005601720"
sudo = Sudoku()
sudo.parse(input)
# 数独可视化
for row in range(0, 9):
    for col in range(0, 9):
        print(sudo.grid[row][col], end="|")
    print('')
print('')

candidate = sudo.getInference()
print("Candidate:")

# 结果输出
for row in range(9):
    for col in range(9):
        print(f"({row + 1},{col + 1}):", end='')
        print(candidate[row][col], end=" ")
    print('')
