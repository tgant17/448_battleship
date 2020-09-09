#include "board.h"
#include <iostream>
#include <string>

Board::Board(){
    m_board = new char*[10];
    for (int i = 0; i < 10; i++){
        m_board[i] = new char[10];
    }
    //create m_board
    char rowLabel = '0';
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(j == 0){
                m_board[i][j] = rowLabel;
                rowLabel++;
            }
            else{
                m_board[i][j] = '-';
            }
            
        }
    }

    //create m_playerViewBoard
    char rowPlayerViewLabel = '0';
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(j == 0){
                m_playerViewBoard[i][j] = rowPlayerViewLabel;
                rowLabel++;
            }
            else{
                m_playerViewBoard[i][j] = '-';
            }
            
        }
    }
}

//print m_board
void Board::printBoard(){
    cout<< " "<<"\t";
    char colLabel = 'A';
    for(char i = colLabel; i <= 'I'; i++){
        cout<< i << "\t";
    }
    cout<<endl;
    cout<<endl;
    for (int i = 1; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cout<<m_board[i][j]<<"\t";    
        }
        cout<<endl;
    }
    cout<<endl;
}

//print m_playerViewBoard
void Board:: printPlayerViewBoard(){
    cout<< " "<<"\t";
    char colLabel = 'A';
    for(char i = colLabel; i <= 'I'; i++){
        cout<< i << "\t";
    }
    cout<<endl;
    cout<<endl;
    for (int i = 1; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cout<<m_playerViewBoard[i][j]<<"\t";    
        }
        cout<<endl;
    }
    cout<<endl;
}

//return a character of a location on m_board
char Board:: getLocation(int row, int col){
    return m_board[row][col];
}

//set a location of m_board to a character
void Board:: setLocation(int row, int col, char newChar){
    m_board[row][col] = newChar;
}

//convert character column into integer
int Board::convertCharToInt(char character){
    switch (character)
    {
    case 'A':
        return 1;
    case 'B':
        return 2;
    case 'C':
        return 3;
    case 'D':
        return 4;
    case 'E':
        return 5;
    case 'F':
        return 6;
    case 'G':
        return 7;
    case 'H':
        return 8;
    case 'I':
        return 9;
    default:
        return 0;
        break;
    }
}


//check if the ship is off the board
bool Board::isOffArray(int p, int shipStart, int shipEnd){
    if(p < 1 || p > 9 || shipStart < 1 || shipEnd > 9 ){
        return true;
    }
    return false;
}

//check if the ship size is valid
bool Board::isValidSize(int shipStart, int shipEnd){
    return (shipStart <= shipEnd);
}

//check if the position is occupied horizontally
bool Board::isOccupiedHorizontally(int p, int shipStart, int shipEnd){
    for(int i = shipStart; i <= shipEnd; i++){
        if(m_board[p][i] == 'S'){
            return true;
        }
    }
    return false;    
}

//check if the postion is occupied vertically
bool Board::isOccupiedVertically(int p, int shipStart, int shipEnd){
    for(int i = shipStart; i <= shipEnd; i++){
        if(m_board[i][p] == 'S'){
            return true;
        }
    }
    return false;    
}
//check if it is valid to set the Ship
bool Board::isValidShip(int p, int shipStart, int shipEnd){
    return (!isOffArray(p, shipStart, shipEnd) && isValidSize(shipStart, shipEnd));
}


//Set a ship horizontally on the board
bool Board::setShipHorizontally(int row, char colStart, char colEnd){
    int shipStart = convertCharToInt(colStart);
    int shipEnd = convertCharToInt(colEnd);
    if(isValidShip(row, shipStart, shipEnd) && !isOccupiedHorizontally(row, colStart, colEnd)){
        for(int i = shipStart; i <= shipEnd; i++){
            m_board[row][i] = 'S';
        }
        return true;
    }
    else{
        return false;
    }
    
}

//Set a ship vertically on the board
bool Board::setShipVertically(char col, int rowStart, int rowEnd){
    int intCol = convertCharToInt(col);
    if(isValidShip(intCol, rowStart, rowEnd) && !isOccupiedVertically(intCol, rowStart, rowEnd)){
        for(int i = rowStart; i <= rowEnd; i++){
            m_board[i][intCol] = 'S';
        }
        return true;
    }
    else{
        return false;
    }
}

//return true if player hit a board and updatge m_playerViewBoard
bool Board::Hit(Board otherPlayerBoard, int row, char col){
    int intCol = convertCharToInt(col);
    if(otherPlayerBoard.getLocation(row, intCol) == 'S'){
        otherPlayerBoard.setLocation(row, intCol, '-');
        m_playerViewBoard[row][intCol] = 'H';
        return true;
    }
    else{
        m_playerViewBoard[row][intCol] = 'M';
    }
    return false;
}

//destructor, deallocatte m_board and m_playerViewBoard
Board:: ~Board(){
    for(int i = 0; i < 10; i++){
    delete [] m_board[i];
  }
  delete[] m_board;

  for(int i = 0; i < 10; i++){
    delete [] m_playerViewBoard[i];
  }
  delete[] m_playerViewBoard;
}