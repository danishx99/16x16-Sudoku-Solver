#include <iostream>
#include <fstream> 
#include <unordered_set>
#include <map>
#define N 9

using namespace std; 

char grid[N][N];
char allowed[16]= {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G'};
int reoccur = 0;
unordered_set<char> notes[N][N] = {};

void getFromFile()
{
  
    for(int x  = 0; x < N; x++)
    {
        for(int y = 0; y < N; y++)
        {
        	char character;
			cin >> character;
            grid[x][y] = character;

        }
    }

}


bool allowedCol(int col, char num)
{
    //Check if a number is already present in a col
    for(int row = 0; row < N; row++)
        if(grid[row][col] == num)
            return true;
    return false; 
}

bool allowedRow(int row, char num)
{
    //Check if a number is already present in a row
    for(int col = 0; col < N; col++)
        if(grid[row][col] == num)
            return true;
    return false; 
}

bool allowedBox(int boxRow, int boxCol, char num)
{
    //Check if a number is already present in a box
    for(int row = 0; row < 4; row++)
        for(int col = 0; col < 4; col++)
            if(grid[row+boxRow][col+boxCol] == num)
                return true;
    return false; 
}

bool isEmpty(int &row, int &col)
{
    for(row = 0; row < N; row++)
        for(col = 0; col < N; col++)
            if(grid[row][col] == '0')
                return true; 
    return false; 
}

bool checkValid(int row, int col, char num)
{
    return !allowedBox(row - row%4, col - col%4, num) && !allowedCol(col, num) && !allowedRow(row, num);
}

void buildNotes()
{
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == '0') {
                for (int num = 0; num < 16; num++) {
                    if (checkValid(row, col, allowed[num]))
                    {
                        notes[row][col].insert(allowed[num]);
                    }
                }
            }
        }
    }
}

void dispBoard()
{

for (int i = 0; i < N; i++){
	for (int j =0 ; j < N; j++){
		
		cout << grid[i][j] << " ";
	}
	cout << endl;
}

}

bool solveSudoku()
{
    //dispBoard();
    //cout << "\n" << endl;
    reoccur+=1;
    //cout << reoccur << endl;
    int row, col; 
    if(!isEmpty(row,col))
        return true;
  	for (char num: notes[row][col]) {
    if (checkValid(row, col, num))
    {
        grid[row][col] = num;
        if (solveSudoku())
            return true;
        grid[row][col] = '0';
    }
}
    return false; 
}

bool unique()
{
    for (int row = 0; row < N; row++) {
        map<char, int> found;
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == '0') {
                for (char num : notes[row][col]) {
                    found[num]++;
                }
            }
        }
        for (auto i : found) {
            if (i.second == 1) { // found unique number in this column
                for (int col = 0; col < N; col++) {
                    if (grid[row][col] == '0') {
                        if (notes[row][col].find(i.first) != notes[row][col].end()) {
                            grid[row][col] = i.first;
                            // remove it from each cell in that col
                            for (int r = 0; r < N; r++) {
                                if (grid[r][col] == '0')
                                    notes[r][col].erase(i.first);
                            }
                            return true;
                        }
                    }
                }

            }
        }
    }

    for (int col = 0; col < N; col++) {
        map<char, int> found;
        for (int row = 0; row < N; row++) {
            if (grid[row][col] == '0') {
                for (char num : notes[row][col]) {
                    found[num]++;
                }
            }
        }
        for (auto i : found) {
            if (i.second == 1) { // found unique number in this row
                for (int row = 0; row < N; row++) {
                    if (grid[row][col] == '0') {
                        if (notes[row][col].find(i.first) != notes[row][col].end()) {
                            grid[row][col] = i.first;
                            // remove it from each cell in that row
                            for (int c = 0; c < N; c++) {
                                if (grid[row][c] == '0')
                                    notes[row][c].erase(i.first);
                            }
                            return true;
                        }
                    }
                }

            }
        }
    }
    return false;
}

bool singles()
{
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == '0') {
                if (notes[row][col].size() == 1) {
                    char num = *notes[row][col].begin();
                    grid[row][col] = num;
                    // remove it from each cell in that col
                    for (int r = 0; r < N; r++) {
                        if (grid[r][col] == '0')
                            notes[r][col].erase(num);
                    }
                    // remove it from each cell in that row
                    for (int c = 0; c < N; c++) {
                        if (grid[row][c] == '0')
                            notes[row][c].erase(num);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    //cout << "Here Is The Sudoku Problem:" << endl; 
	getFromFile();
	//dispBoard();
	buildNotes();
		while (unique()) {
    	while(singles())
       ;
}
		
	if(solveSudoku()){
        cout << "Solved" << endl;
        dispBoard();
    }
    else{

        cout << "No Solution" << endl; 
    } 
        
}

   

