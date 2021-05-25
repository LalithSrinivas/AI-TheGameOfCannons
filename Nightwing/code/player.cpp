#include <climits>
#include <stdio.h>
#include <vector>
#include "game.h"

//int count1;

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

gameMove Game::minimax(int depth, double time_span, gameMove prevMove){
    gameMove temp = gameMove(-1, -1, -1, -1, false);
    //ScoreAndMoves successors = ScoreAndMoves();
    //successors = getValidMoves();
//    count1 = 0;
    float alpha;
    alpha = (float)INT_MIN;
    float beta = (float)INT_MAX;
    ScoreAndMove temp1 = ScoreAndMove();
    int check = depth;
    if (time_span > 100){
        check = (int)(timeRemaining/time_span);
        check = min(check, depth);
    }
    temp1 = maxVal(alpha, beta, check, prevMove);
    temp = temp1.gamemove;
//    cout << count1 << endl;
    //temp = maxVal(alpha, beta, depth);
    return temp;
}

ScoreAndMove Game::maxVal(float alpha, float beta, int depth, gameMove prevMove){
//    count1++;
    ScoreAndMove ans = ScoreAndMove();
    ans.score = (float)INT_MIN;
    int myTownHalls = 0;
    int enemyTownHalls = 0;
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
    if (depth ==0){
        ans.score = getMyScore() - getOppScore();
        ans.gamemove = gameMove();
        return  ans;
    }else if ((myTownHalls == num1-2) || (enemyTownHalls == num1-2)){
        ans.score = getMyScore() - getOppScore();
        ans.gamemove = gameMove();
        return ans;
    }else{
        //cout << myTownHalls << " " << enemyTownHalls << endl;
        ScoreAndMoves successors = ScoreAndMoves();
        successors = getValidMoves();
        vector<gameMove> temp;
        int total = 0;
        for (int i=0; i<7; i++){
            total += (int)successors.Posmoves[i].size();
        }
        if (total == 0){
            ans.score = getMyScore() - getOppScore();
            ans.gamemove = gameMove();
            return ans;
        }
        if (enemyTownHalls == num1-1){
            int len = (int)successors.Posmoves[0].size();
            if (len!=0){
                int opponent;
                if (player==1) opponent=2; else opponent=1;
                gameMove tempMove = successors.Posmoves[0][0];
                Game opponent_game = Game(opponent, rows, cols, timeRemaining);
                copyBoard(opponent_game.board, board, rows, cols);
                copySol(opponent_game.mySoldierRows, oppSoldierRows, cols);
                copySol(opponent_game.mySoldierCols, oppSoldierCols, cols);
                copySol(opponent_game.oppSoldierRows, mySoldierRows, cols);
                copySol(opponent_game.oppSoldierCols, mySoldierCols, cols);
                opponent_game.executeMove(tempMove);
                ans.score = opponent_game.getOppScore() - opponent_game.getMyScore() + 100;
                ans.gamemove = tempMove;
                return ans;
            }
            len = (int)successors.Posmoves[2].size();
            if (len!=0){
                int opponent;
                if (player==1) opponent=2; else opponent=1;
                gameMove tempMove = successors.Posmoves[2][0];
                Game opponent_game = Game(opponent, rows, cols, timeRemaining);
                copyBoard(opponent_game.board, board, rows, cols);
                copySol(opponent_game.mySoldierRows, oppSoldierRows, cols);
                copySol(opponent_game.mySoldierCols, oppSoldierCols, cols);
                copySol(opponent_game.oppSoldierRows, mySoldierRows, cols);
                copySol(opponent_game.oppSoldierCols, mySoldierCols, cols);
                opponent_game.executeMove(tempMove);
                ans.score = opponent_game.getOppScore() - opponent_game.getMyScore() + 100;
                ans.gamemove = tempMove;
                return ans;
            }
        }
        for (int i=0; i<7; i++){
            if (i==1){
                temp = successors.Posmoves[2];
            }else if (i==2){
                temp = successors.Posmoves[1];
            }else{
                temp = successors.Posmoves[i];
            }
            int len = (int)temp.size();
            for (int j=0; j<len; j++){
                gameMove tempMove = temp[j];
                if(tempMove.compareMove(prevMove))
                    continue;
                int opponent;
                if (player==1) opponent=2; else opponent=1;
                Game opponent_game = Game(opponent, rows, cols, timeRemaining);
                copyBoard(opponent_game.board, board, rows, cols);
                copySol(opponent_game.mySoldierRows, oppSoldierRows, cols);
                copySol(opponent_game.mySoldierCols, oppSoldierCols, cols);
                copySol(opponent_game.oppSoldierRows, mySoldierRows, cols);
                copySol(opponent_game.oppSoldierCols, mySoldierCols, cols);
                opponent_game.executeMove(tempMove);
                ScoreAndMove oppMove = ScoreAndMove();
                oppMove = opponent_game.minVal(alpha, beta, depth-1);
                if (oppMove.score > ans.score){
                    ans.score = oppMove.score;
                    ans.gamemove = tempMove;
                }
                if (alpha < oppMove.score){
                    alpha = oppMove.score;
                }
                if (alpha >= beta){
                    //cout << "pruned" << endl;
//                        cout << alpha << " " << beta << endl;
                    return ans;
                }
            }
            }
    }
    return ans;
}


ScoreAndMove Game::minVal(float alpha, float beta, int depth){
//    count1++;
    ScoreAndMove ans = ScoreAndMove();
    gameMove prevMove = gameMove(-1, -1, -1, -1, false);
    ans.score = (float)INT_MAX;
    int myTownHalls = 0;
    int enemyTownHalls = 0;
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
    if (depth == 0){
        ans.score = getOppScore() - getMyScore();
        ans.gamemove = gameMove();
        return ans;
    }else if ((myTownHalls == num1-2) || (enemyTownHalls == num1-2)){
        ans.score = getOppScore() - getMyScore();
        ans.gamemove = gameMove();
        return ans;
    }else{
        ScoreAndMoves successors = ScoreAndMoves();
        successors = getValidMoves();
        vector<gameMove> temp;
        int total = 0;
        for (int i=0; i<7; i++){
            total += (int)successors.Posmoves[i].size();
        }
        if (total == 0){
            ans.score = getOppScore() - getMyScore();
            ans.gamemove = gameMove();
            return ans;
        }
        if (enemyTownHalls == num1-1){
            int len = (int)successors.Posmoves[0].size();
            if (len!=0){
                int opponent;
                if (player==1) opponent=2; else opponent=1;
                gameMove tempMove = successors.Posmoves[0][0];
                executeMove(tempMove);
                ans.score = getOppScore() - getMyScore() - 100;
                ans.gamemove = tempMove;
                return ans;
            }
            len = (int)successors.Posmoves[2].size();
            if (len!=0){
                int opponent;
                if (player==1) opponent=2; else opponent=1;
                gameMove tempMove = successors.Posmoves[2][0];
                executeMove(tempMove);
                ans.score = getOppScore() - getMyScore() - 100;
                ans.gamemove = tempMove;
                return ans;
            }
        }
        for (int i=0; i<7; i++){
            if (i==1){
                temp = successors.Posmoves[2];
            }else if (i==2){
                temp = successors.Posmoves[1];
            }else{
                temp = successors.Posmoves[i];
            }
            int len = (int)temp.size();
            for (int j=0; j<len; j++){
                gameMove tempMove = temp[j];
                int opponent;
                if (player==1) opponent=2; else opponent=1;
                Game opponent_game = Game(opponent, rows, cols, timeRemaining);
                copyBoard(opponent_game.board, board, rows, cols);
                copySol(opponent_game.mySoldierRows, oppSoldierRows, cols);
                copySol(opponent_game.mySoldierCols, oppSoldierCols, cols);
                copySol(opponent_game.oppSoldierRows, mySoldierRows, cols);
                copySol(opponent_game.oppSoldierCols, mySoldierCols, cols);
                opponent_game.executeMove(tempMove);
                ScoreAndMove oppMove = ScoreAndMove();
                oppMove = opponent_game.maxVal(alpha, beta, depth-1, prevMove);
                if (oppMove.score < ans.score){
                    ans.score = oppMove.score;
                    ans.gamemove = oppMove.gamemove;
                }
                if (beta > oppMove.score){
                    beta = oppMove.score;
                }
                if (alpha >= beta){
                    //cout << "pruned" << endl;
//                    cout << alpha << " " << beta << endl;
                    return ans;
                }
            }
        }
    }
    return ans;
}
