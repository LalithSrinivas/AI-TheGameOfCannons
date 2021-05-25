//
//  game.h
//  code
//
//  Created by Chinmai Sai Nagendra kokku on 9/9/19.
//  Copyright © 2019 Chinmai Sai Nagendra kokku. All rights reserved.
//

#ifndef game_h
#define game_h
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>

using namespace std;
class gameMove{
    
public:
    int curr_row, curr_col, dest_row, dest_col;
    bool cannon_move;
    gameMove(){
        this->curr_row = -1;
        this->curr_col = -1;
        this->dest_row = -1;
        this->dest_col = -1;
        this->cannon_move = false;
    }
    //Constructor
    gameMove(int curr_row, int curr_col, int dest_row, int dest_col, bool cannon_move){
        this->curr_row = curr_row;
        this->curr_col = curr_col;
        this->dest_row = dest_row;
        this->dest_col = dest_col;
        this->cannon_move = cannon_move;
    }
    bool compareMove(gameMove aMove){
        if(curr_col == aMove.curr_col)
            if(curr_row == aMove.curr_row)
                if(dest_col == aMove.dest_col)
                    if(dest_row == aMove.dest_row)
                        if(cannon_move == aMove.cannon_move)
                            return true;
        return false;
    }
    void make(gameMove aMove){
        curr_row = aMove.curr_row;
        curr_col = aMove.curr_col;
        dest_row = aMove.dest_row;
        dest_col = aMove.dest_col;
        cannon_move = aMove.cannon_move;
    }
    gameMove getNegation(gameMove aMove){
        gameMove temp(-1, -1, -1, -1, false);
        if (aMove.cannon_move){
            temp = gameMove(aMove.curr_row, aMove.curr_col, aMove.dest_row, aMove.dest_col, aMove.cannon_move);
        }else{
            temp = gameMove(aMove.dest_row, aMove.dest_col, aMove.curr_row, aMove.curr_col, aMove.cannon_move);
        }
        return temp;
    }
    bool isNegation(gameMove aMove){
        if(cannon_move == aMove.cannon_move){
            if (cannon_move && (curr_col == aMove.curr_col) && (curr_row == aMove.curr_row) && (dest_row==aMove.dest_row) && (dest_col== aMove.dest_col)){
                return true;
            }
            if(curr_col == aMove.dest_col){
                if(curr_row == aMove.dest_row){
                    if(dest_col == aMove.curr_col){
                        if(dest_row == aMove.curr_row){
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
    
    void printMove(int rows){
        cout << "S " << curr_col << " " << (rows - 1 - curr_row) << " ";
        if (cannon_move) cout << "B ";
        else cout << "M ";
        cout << dest_col << " " << (rows - 1 -dest_row) << endl;
    }
    
};

class ScoreAndMoves{
public:
    float score;
    vector<gameMove> *Posmoves;
    
    ScoreAndMoves(){
        score = 0;
        Posmoves = new vector<gameMove>[7];
        /*Posmoves[0] -> cannon townhall capture
         Posmoves[1] -> cannon soldier capture
         Posmoves[2] -> soldier townhall capture
         Posmoves[3] -> soldier soldier capture
         Posmoves[4] -> cannon move
         Posmoves[5] -> soldier move
         Posmoves[6] -> empty cannon blasts
         */
    }
};

class ScoreAndMove{
public:
    float score;
    gameMove gamemove;
    
    ScoreAndMove(){
        score = 0;
        gamemove = gameMove();
    }
};

class ScoreAndMovesCollection{
public:
    float cumScore;
    vector<ScoreAndMove> *moves;
    
    ScoreAndMovesCollection(){
        cumScore = 0;
        moves = new vector<ScoreAndMove>[6];
        /*Posmoves[0] -> cannon townhall capture
         Posmoves[1] -> cannon soldier capture
         Posmoves[2] -> soldier townhall capture
         Posmoves[3] -> soldier soldier capture
         Posmoves[4] -> cannon move
         Posmoves[5] -> soldier move
         */
    }
};


class Game{
    int rows, cols, player;
    int **board;
    int *mySoldierRows;
    int *mySoldierCols;
    int *oppSoldierRows;
    int *oppSoldierCols;
    
public:
    double timeRemaining;
    //Constructor
    Game(int player, int rows, int cols, double timeRemaining);
    
    ScoreAndMoves getValidMoves();
    vector<ScoreAndMove> getValidMovesRedefined();
    
    void executeMove(gameMove moveInfo);
        
    bool enemyAdjacent(int rowNum, int colNum);
    
    gameMove minimax(int depth, double time_span, gameMove prevMove);
    
    ScoreAndMove minVal(float alpha, float beta, int depth);
    
    ScoreAndMove maxVal(float alpha, float beta, int depth, gameMove prevMove);
    
    int diffTownHalls(int myTownHalls, int enemyTownHalls){
        if (cols == 8){
            if (myTownHalls == 4 && enemyTownHalls==2){
                return 100;
            }else if (myTownHalls == 3 && enemyTownHalls == 2){
                return 80;
            }else if (myTownHalls==4 && enemyTownHalls==3){
                return 7;
            }else if (myTownHalls==4 && enemyTownHalls==4){
                return 5;
            }else if (myTownHalls==3 && enemyTownHalls==3){
                return 5;
            }else if (myTownHalls==3 && enemyTownHalls==4){
                return 3;
            }else if (myTownHalls==2 && enemyTownHalls==3){
                return -80;
            }else if (myTownHalls==2 && enemyTownHalls==4){
                return -100;
            }
        }else{
            if (myTownHalls == 5 && enemyTownHalls==3){
                return 100;
            }else if (myTownHalls == 4 && enemyTownHalls == 3){
                return 80;
            }else if (myTownHalls== 5 && enemyTownHalls== 4){
                return 7;
            }else if (myTownHalls== 5 && enemyTownHalls== 5){
                return 5;
            }else if (myTownHalls==4 && enemyTownHalls==4){
                return 5;
            }else if (myTownHalls==4 && enemyTownHalls==5){
                return 3;
            }else if (myTownHalls==3 && enemyTownHalls==4){
                return -80;
            }else if (myTownHalls==3 && enemyTownHalls==5){
                return -100;
            }
        }
        return  0;
    }
    float numOppCannons(){
        float count=0;
        int num1 = cols/2;
//        std::ofstream out("out1.txt");
//        std::streambuf *coutbuf = std::cout.rdbuf();
//        std::cout.rdbuf(out.rdbuf());
//        cout << "started" << endl;
//        printBoard();
        for(int i=0; i< 3*num1; i++){
            if(oppSoldierRows[i] != -1 && board[oppSoldierRows[i]][oppSoldierCols[i]] != -1){
                int x = oppSoldierRows[i];
                int y = oppSoldierCols[i];
                if(isInBoard(x+1, y+1) && isInBoard(x-1, y-1)){
//                    cout << x << " " << y << endl;
                    if((board[x+1][y+1] == board[x-1][y-1]) && (board[x+1][y+1] == board[x][y])){
                        count+=1;
                    }
                }if(isInBoard(x+1, y) && isInBoard(x-1, y)){
//                    cout << x << " " << y << endl;
                    if((board[x+1][y] == board[x-1][y]) && (board[x+1][y] == board[x][y])){
                        count+=1;
                    }
                }if(isInBoard(x+1, y-1) && isInBoard(x-1, y+1)){
//                    cout << x << " " << y << endl;
                    if((board[x+1][y-1] == board[x-1][y+1]) && (board[x+1][y-1] == board[x][y])){
                        count+=1;
                    }
                }if(isInBoard(x, y+1) && isInBoard(x, y-1)){
//                    cout << x << " " << y << endl;
                    if((board[x][y-1] == board[x][y+1]) && (board[x][y-1] == board[x][y])){
//                        if (cols==10){
//                            count+=0.25;
//                        }else{
                            count+=1;
//                        }
                    }
                }
            }
        }
//        std::cout.rdbuf(coutbuf);
        return count;
    };
    
    float numMyCannons(){
        float count=0;
        int num1 = cols/2;
//        std::ofstream out("out.txt");
//        std::streambuf *coutbuf = std::cout.rdbuf();
//        std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
//        printBoard();
        for(int i=0; i< 3*num1; i++){
//            cout << "hello " << mySoldierRows[i] << " " << mySoldierCols[i] << endl;
            if(mySoldierRows[i] != -1 && board[mySoldierRows[i]][mySoldierCols[i]] != -1){
                int x = mySoldierRows[i];
                int y = mySoldierCols[i];
                if(isInBoard(x+1, y+1) && isInBoard(x-1, y-1)){
//                    cout << x << " " << y << endl;
                    if((board[x+1][y+1] == board[x-1][y-1]) && (board[x+1][y+1] == board[x][y])){
                    count += 1;
                    }
                }if(isInBoard(x+1, y) && isInBoard(x-1, y)){
//                    cout << x << " " << y << endl;
                    if((board[x+1][y] == board[x-1][y]) && (board[x+1][y] == board[x][y])){
                    count+=1;
                    }
                }if(isInBoard(x+1, y-1) && isInBoard(x-1, y+1)){
//                    cout << x << " " << y << endl;
                    if((board[x+1][y-1] == board[x-1][y+1]) && (board[x+1][y-1] == board[x][y])){
                    count+=1;
                    }
                }if(isInBoard(x, y+1) && isInBoard(x, y-1)){
//                    cout << x << " " << y << endl;
                    if((board[x][y-1] == board[x][y+1]) && (board[x][y-1] == board[x][y])){
//                        if (cols==10){
//                            count+=0.25;
//                        }else{
                            count+=1;
//                        }
                    }
                }

            }
        }
//        std::cout.rdbuf(coutbuf); //save old buf
        return count;
    };
    
    float getMyScore(){
        int myTownHalls = 0; int enemyTownHalls = 0;
        float score = 0;
        int num1 = (int)(cols/2);
//        bool myF[num1]; bool oppF[num1];
        int myFort, enemyFort;
        if (player==1){
            myFort = 2; enemyFort = 4;
        }else{
            myFort = 4; enemyFort = 2;
        }
        for (int i=0; i<num1; i++){
            if (player == 1){
                if (board[rows-1][(2*i)] == myFort){
                    myTownHalls++;
                }
                if (board[0][(2*i)+1] == enemyFort){
                    enemyTownHalls++;
                }
            }else{
                if (board[0][(2*i)+1] == myFort){
                    myTownHalls++;
                }
                if (board[rows-1][(2*i)] == enemyFort){
                    enemyTownHalls++;
                }
            }
//            myF[i] = false; oppF[i] = false;
        }
        
        int deltaTownHalls = diffTownHalls(myTownHalls, enemyTownHalls);
        
        score += (10000*deltaTownHalls);
        
        int mySoldiers=0; int oppSoldiers = 0;
        for (int i=0; i<(3*num1); i++){
            if (player == 1 && mySoldierRows[i]!=-1 && myTownHalls == 4){
                bool addOrNot = false;
                if (mySoldierCols[i] - 1 >= 0){
                    addOrNot = addOrNot || (board[0][mySoldierCols[i]-1] == enemyFort);
                }
//                if (addOrNot && !oppF[(int)((mySoldierCols[i]-1)/2) + 1]){
//                    score += 1.5*(rows - 1 - mySoldierRows[i]);
//                    oppF[(int)((mySoldierCols[i]-1)/2) + 1] = true;
//                }else
                if (mySoldierCols[i] + 1 < cols){
                    addOrNot = addOrNot || (board[0][mySoldierCols[i]+1]==enemyFort);
                }
                addOrNot = addOrNot || (board[0][mySoldierCols[i]] == enemyFort);
                if (addOrNot){
                    if(cols != 10 || rows != 10)
                        score += 1.5*(rows - 1 - mySoldierRows[i]);
                    else
                        score += 1.5*(rows - 1 - mySoldierRows[i]);
                }
            }
            if (player == 2 && mySoldierRows[i]!=-1 && myTownHalls == 4){
                bool addOrNot = false;
                if (mySoldierCols[i] - 1 >= 0){
                    addOrNot = addOrNot || (board[rows-1][mySoldierCols[i]-1] == enemyFort);
                }
                if (mySoldierCols[i] + 1 < cols){
                    addOrNot = addOrNot || (board[rows-1][mySoldierCols[i]+1]==enemyFort);
                }
                addOrNot = addOrNot || (board[rows-1][mySoldierCols[i]] == enemyFort);
                if (addOrNot){
                    if(cols != 10 || rows != 10)
                        score += 1.5*mySoldierRows[i];
                    else
                        score += 1.5*mySoldierRows[i];
                }
            }
            if (mySoldierRows[i]!=-1 && mySoldierCols[i]!=-1){
                mySoldiers++;
            }
            if (oppSoldierRows[i]!=-1 && oppSoldierCols[i]!=-1){
                oppSoldiers++;
            }
        }
        if(cols != 10 || rows != 10)
            score += 3*numMyCannons();
        else
            score += 3*numMyCannons();
//        if (oppSoldiers <= 2 && mySoldiers > 3){
//            score += 2*(mySoldiers);
//            score += 3*oppSoldiers;
//        }else{
        if(cols != 10 || rows != 10)
            score += 1.5*(mySoldiers);
        else
            score += 1.5*(mySoldiers);
//            score -=  0.5*oppSoldiers;
//        }
        return score;
        
    }
    
    
    float getOppScore(){
        int myTownHalls = 0; int enemyTownHalls = 0;
        float score = 0;
        int num1 = (int)(cols/2);
        int myFort, enemyFort;
        if (player==1){
            myFort = 2; enemyFort = 4;
        }else{
            myFort = 4; enemyFort = 2;
        }
        for (int i=0; i<num1; i++){
            if (player == 1){
                if (board[rows-1][(2*i)] == myFort){
                    myTownHalls++;
                }
                if (board[0][(2*i)+1] == enemyFort){
                    enemyTownHalls++;
                }
            }else{
                if (board[0][(2*i)+1] == myFort){
                    myTownHalls++;
                }
                if (board[rows-1][(2*i)] == enemyFort){
                    enemyTownHalls++;
                }
            }
        }
        
        int deltaTownHalls = diffTownHalls(enemyTownHalls, myTownHalls);
        
        score += (10000*deltaTownHalls);
        
        int mySoldiers=0; int oppSoldiers = 0;
        for (int i=0; i<(3*num1); i++){
            if (player == 2 && oppSoldierRows[i]!=-1 && enemyTownHalls == 4){
                bool addOrNot = false;
                if (oppSoldierCols[i] - 1 >= 0){
                    addOrNot = addOrNot || (board[0][oppSoldierCols[i]-1] == myFort);
                }
                if (oppSoldierCols[i] + 1 < cols){
                    addOrNot = addOrNot || (board[0][oppSoldierCols[i]+1]==myFort);
                }
                addOrNot = addOrNot || (board[0][oppSoldierCols[i]] == myFort);
                if (addOrNot){
                    if(cols != 10 || rows != 10)
                        score += 1.5*(rows - 1 - oppSoldierRows[i]);
                    else
                        score += 1.5*(rows - 1 - oppSoldierRows[i]);
                }
            }
            if (player == 1 && oppSoldierRows[i]!=-1 && enemyTownHalls == 4){
                bool addOrNot = false;
                if (oppSoldierCols[i] - 1 >= 0){
                    addOrNot = addOrNot || (board[rows-1][oppSoldierCols[i]-1] == myFort);
                }
                if (oppSoldierCols[i] + 1 < cols){
                    addOrNot = addOrNot || (board[rows-1][oppSoldierCols[i]+1]==myFort);
                }
                addOrNot = addOrNot || (board[rows-1][oppSoldierCols[i]] == myFort);
                if (addOrNot){
                    if(cols != 10 || rows != 10)
                        score += 1.5*oppSoldierRows[i];
                    else
                        score += 1.5*oppSoldierRows[i];
                }
            }
            
            if (mySoldierRows[i]!=-1 && mySoldierCols[i]!=-1){
                mySoldiers++;
            }
            if (oppSoldierRows[i]!=-1 && oppSoldierCols[i]!=-1){
                oppSoldiers--;
            }
        }
        if(cols != 10 || rows != 10)
            score += 3*numOppCannons();
        else
            score += 3*numOppCannons();
//        if (mySoldiers<=2 && oppSoldiers>3){
//            score += 2*(oppSoldiers);
//            score += 3*oppSoldiers;
//        }else{
//            score -= 0.5*(mySoldiers);
        if(cols != 10 || rows != 10)
            score += 1.5*(oppSoldiers);
        else
            score += 1.5*(oppSoldiers);
//            }
        return score;
        
    }
    
    void copyBoard(int** toBoard, int** fromBoard, int rows, int cols){
        for (int i=0; i<rows; i++){
            for (int j=0; j<cols; j++){
                toBoard[i][j] = fromBoard[i][j];
            }
        }
    }
    
    void copySol(int* toSol, int* fromSol, int cols){
        int num1 = (int)(cols*3/2);
        for (int i=0; i<num1; i++){
            toSol[i] = fromSol[i];
        }
    }

    
    bool isTerminalState(int myTownHalls, int enemyTownHalls){
        myTownHalls = 0; enemyTownHalls = 0;
        int num1 = (int)(cols/2);
        int myFort, enemyFort;
        if (player==1){
            myFort = 2; enemyFort = 4;
        }else{
            myFort = 4; enemyFort = 2;
        }
        for (int i=0; i<num1; i++){
            if (player == 1){
                if (board[rows-1][(2*i)] == myFort){
                    myTownHalls++;
                }
                if (board[0][(2*i)+1] == enemyFort){
                    enemyTownHalls++;
                }
            }else{
                if (board[0][(2*i)+1] == myFort){
                    myTownHalls++;
                }
                if (board[rows-1][(2*i)] == enemyFort){
                    enemyTownHalls++;
                }
            }
        }
        
        return ((myTownHalls == 2) || (enemyTownHalls == 2));
        
    }
    
    bool isInBoard(int x, int y){
        return (x>=0 && x<rows && y>=0 && y<cols);
    }

    int getrows(){
        return rows;
    }
    void printBoard(){
        for (int i=0; i<rows; i++){
            for (int j=0; j<cols; j++){
                cout << this->board[rows-1-i][j] << " ";
            }
            cout << endl;
        }
    }
    
    void printSoldiers(){
        int num1 = (int)(cols*3/2);
        for (int i=0; i<num1; i++){
            cout << mySoldierRows[i] << " " << mySoldierCols[i] << endl;
        }
    }
};


#endif /* game_h */
