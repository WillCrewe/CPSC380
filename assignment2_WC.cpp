#include <iostream>
#include <thread>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int board[9][9];

//Probably a way overcomplicated way of reading the csv to a 2d array
void input_reader()
{
  string myText;
  // Read from the text file
  ifstream MyReadFile("Testfile5.txt");
  // Use a while loop together with the getline() function to read the file line by line
  int count = 0;
  while (getline (MyReadFile, myText)) {
    //cout << myText << endl;
    string line;
    for(int i = 0; i < myText.length(); i++)
    {
      if(myText[i] != ',')
      {
        //cout << myText[i] << endl;
        line += myText[i];
        //cout << line << endl;
      }
    }
    for(int j = 0; j < line.length(); j++)
    {
      //SUBTRACT 48 to convert from string to int
      board[count][j] = int(line.at(j) - 48);
    }
    count++;
  }
  MyReadFile.close();
}

int findMissing(int c, bool isCol)
{
  bool one = true;
  bool two = true;
  bool three = true;
  bool four = true;
  bool five = true;
  bool six = true;
  bool seven = true;
  bool eight = true;
  bool nine = true;
  for(int i = 0; i < 9; i++)
  {
  if(isCol)
  {
    if(board[i][c] == 1)
    {
      one = false;
    } else if (board[i][c] == 2) {
      two = false;
    } else if (board[i][c] == 3) {
      three = false;
    } else if (board[i][c] == 4) {
      four = false;
    } else if (board[i][c] == 5) {
      five = false;
    } else if (board[i][c] == 6) {
      six = false;
    } else if (board[i][c] == 7) {
      seven = false;
    } else if (board[i][c] == 8) {
      eight = false;
    } else if (board[i][c] == 9) {
      nine = false;
    }
  } else {
    if(board[c][i] == 1)
    {
      one = false;
    } else if (board[c][i] == 2) {
      two = false;
    } else if (board[c][i] == 3) {
      three = false;
    } else if (board[c][i] == 4) {
      four = false;
    } else if (board[c][i] == 5) {
      five = false;
    } else if (board[c][i] == 6) {
      six = false;
    } else if (board[c][i] == 7) {
      seven = false;
    } else if (board[c][i] == 8) {
      eight = false;
    } else if (board[c][i] == 9) {
      nine = false;
    }
  }

  }
  if(one)
  {
    return 1;
  }
  if(two)
  {
    return 2;
  }
  if(three)
  {
    return 3;
  }
  if(four)
  {
    return 4;
  }
  if(five)
  {
    return 5;
  }
  if(six)
  {
    return 6;
  }
  if(seven)
  {
    return 7;
  }
  if(eight)
  {
    return 8;
  }
  if(nine)
  {
    return 9;
  }
}

void errorFoundRow(int row, int collumn, int orgCol, int orgVal, int hint)
{
  for (int i = 0; i < 9; ++i)
  {
    for (int j = 0; j < 9; ++j)
    {
      if(i == row && (j == collumn || j == orgCol))
      {
        cout << "* ";
      } else {
        cout << board[i][j] << ' ';
      }
    }
    cout << std::endl;
  }
  cout << "* = ERROR FOUND, VALUES SHOULD BE EITHER: " << hint << " OR " << orgVal << endl;
}

void errorFoundCollumn(int row, int collumn, int orgCol, int orgVal, int hint)
{
  for (int i = 0; i < 9; ++i)
  {
    for (int j = 0; j < 9; ++j)
    {
      if((i == row || i == orgCol) && j == collumn)
      {
        cout << "* ";
      } else {
        cout << board[i][j] << ' ';
      }
    }
    cout << std::endl;
  }
  cout << "* = ERROR FOUND, VALUES SHOULD BE EITHER: " << hint << " OR " << orgVal << "\n" << endl;
}


void Square(int x, int y, int a, int b) //Checks Each Square
{
  int errRow = 0;
  int errCollumn = 0;
  int orgVal = 0;
  int orgCol = 0;
  int orgRow = 0;
  bool errFound = false;

  for (int i = x; i <= y; i++)
  {
    string square;
    for(int j = a; j <= b; j++)
    {
      square += to_string(board[i][j]);
      for(int k = 0; k < square.length() - 1; k++)
      {
        int value = int(square[k] - 48);
        if(board[i][j] == value)
        {
          orgCol = k;
          orgVal = value;
          errRow = i;
          errCollumn = j;
          errFound = true;
        }
      }
    }
  }
  if(errFound)
  {
    int hint = findMissing(errCollumn, true);
    errorFoundRow(errRow, errCollumn, orgCol, orgVal, hint);
  }
}

void SquareRun()
{
  Square(0,2,0,2);
  Square(0,2,3,5);
  Square(0,2,6,8);
  Square(3,5,0,2);
  Square(6,8,0,2);
  Square(3,5,3,5);
  Square(3,5,7,8);
  Square(6,8,3,5);
  Square(6,8,6,8);

}


void Row() //Checks Row of board
{
  int errRow = 0;
  int errCollumn = 0;
  int orgVal = 0;
  int orgCol = 0;
  bool errFound = false;
  for (int i = 0; i < 9; i++)
  {
    string row;
    for (int j = 0; j < 9; j++)
    {
      //Checking for duplicates
      //If duplicate found, return index
      row += to_string(board[i][j]);
      for(int k = 0; k < row.length()-1; k++)
      {
        int value = int(row[k] - 48);
        if(board[i][j] == value)
        {
          orgCol = k;
          orgVal = value;
          errRow = i;
          errCollumn = j;
          errFound = true;
        }
      }
    }
  }
  if(errFound)
  {
    int hint = findMissing(errCollumn, true);
    errorFoundRow(errRow, errCollumn, orgCol, orgVal, hint);
  }
}

void Collumn() //Checks Collumn of board
{
  int errRow = 0;
  int errCollumn = 0;
  int orgVal = 0;
  int orgRow = 0;
  bool errFound = false;
  for (int i = 0; i < 9; i++)
  {
    string col;
    for (int j = 0; j < 9; j++)
    {
      //Checking for duplicates
      //If duplicate found, return index
      col += to_string(board[j][i]);
      //cout << col << endl;
      for(int k = 0; k < col.length()-1; k++)
      {
        int value = int(col[k] - 48);
        if(board[j][i] == value)
        {
          orgRow = k;
          orgVal = value;
          errRow = i;
          errCollumn = j;
          errFound = true;
        }
      }
    }
  }
  if(errFound)
  {
    int hint = findMissing(errCollumn, false);
    errorFoundCollumn(errRow, errCollumn, orgRow, orgVal, hint);
  }
}

int main() {
  input_reader();
  thread row_thread(Row);
  thread col_thread(Collumn);
  thread square_thread(SquareRun);

  row_thread.join();
  col_thread.join();
  square_thread.join();
}
