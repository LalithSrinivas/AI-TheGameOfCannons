//
//  game.cpp
//  code
//
//  Created by Chinmai Sai Nagendra kokku on 9/9/19.
//  Copyright © 2019 Chinmai Sai Nagendra kokku. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include "game.h"

//Constructor
Game::Game(int player, int rows, int cols, double timeRemaining){
    this->player = player;
    this->rows = rows;
    this->cols = cols;
    this->timeRemaining = timeRemaining;
    this->board = new int*[rows];
    for (int i=0; i<rows; i++){
        this->board[i] = new int[cols];
    }
    this->mySoldierRows = new int[(int)(cols*3/2)];
    this->mySoldierCols = new int[(int)(cols*3/2)];
    this->oppSoldierRows = new int[(int)(cols*3/2)];
    this->oppSoldierCols = new int[(int)(cols*3/2)];

    /*  white soldier = 1
        white town hall = 2
        black soldier = 3
        black town hall = 4
        empty = -1  */
    for (int i=0; i<cols; i++){
        if (i%2==0){
            this->board[0][i] = 3;
            this->board[1][i] = 3;
            this->board[2][i] = 3;
            this->board[rows-1][i] = 2;
            for (int j=3; j<rows-1; j++){
                this->board[j][i] = -1;
            }
        }else{
            this->board[0][i] = 4;
            this->board[rows-1][i] = 1;
            this->board[rows-2][i] = 1;
            this->board[rows-3][i] = 1;
            for (int j=1; j<rows-3; j++) {
                this->board[j][i] = -1;
            }
        }
    }
    
    if (player==1){
        int num1 = (int)(cols/2);
        for (int i=0; i<3; i++){
            for (int j=0; j<num1; j++){
                mySoldierRows[i*num1+j] = rows-1-i;
            }
        }
        
        for (int i=0; i<num1; i++){
            mySoldierCols[i] = (2*i)+1;
            mySoldierCols[num1+i] = (2*i)+1;
            mySoldierCols[(2*num1)+i] = (2*i)+1;
        }
        
        for (int i=0; i<3; i++){
            for (int j=0; j<num1; j++){
                oppSoldierRows[i*num1+j] = i;
            }
        }
        
        for (int i=0; i<num1; i++){
            oppSoldierCols[i] = (2*i);
            oppSoldierCols[num1+i] = (2*i);
            oppSoldierCols[(2*num1)+i] = (2*i);
        }

    }else{
        int num1 = (int)(cols/2);
        for (int i=0; i<3; i++){
            for (int j=0; j<num1; j++){
                mySoldierRows[i*num1+j] = i;
            }
        }
        
        for (int i=0; i<num1; i++){
            mySoldierCols[i] = (2*i);
            mySoldierCols[num1+i] = (2*i);
            mySoldierCols[(2*num1)+i] = (2*i);
        }
        for (int i=0; i<3; i++){
            for (int j=0; j<num1; j++){
                oppSoldierRows[i*num1+j] = rows-1-i;
            }
        }
        
        for (int i=0; i<num1; i++){
            oppSoldierCols[i] = (2*i)+1;
            oppSoldierCols[num1+i] = (2*i)+1;
            oppSoldierCols[(2*num1)+i] = (2*i)+1;
        }

    }
    
    /*int num1 = (int)(cols*3/2);
    for (int i=0; i<num1; i++) {
        cout << "(" << mySoldierRows[i] << ", " << mySoldierCols[i] << ")"<<endl;
    }
    cout << "opponents";
    for (int i=0; i<num1; i++) {
        cout << "(" << oppSoldierRows[i] << ", " << oppSoldierCols[i] << ")"<<endl;
    }*/
}

bool Game::enemyAdjacent(int rowNum, int colNum){
    int enemy;
    if (player == 1) enemy = 3; else enemy = 1;
    if (player == 2){
        if (isInBoard(rowNum+1, colNum-1)){
            if (board[rowNum+1][colNum-1]==enemy) return true;
        }
        if (isInBoard(rowNum+1, colNum)){
            if (board[rowNum+1][colNum]==enemy) return true;
        }
        if (isInBoard(rowNum+1, colNum+1)){
            if (board[rowNum+1][colNum+1]==enemy) return true;
        }
    }
    if (isInBoard(rowNum, colNum-1)){
        if (board[rowNum][colNum-1]==enemy) return true;
    }
    if (isInBoard(rowNum, colNum+1)){
        if (board[rowNum][colNum+1]==enemy) return true;
    }
    if (player == 1){
        if (isInBoard(rowNum-1, colNum-1)){
            if (board[rowNum-1][colNum-1]==enemy) return true;
        }
        if (isInBoard(rowNum-1, colNum)){
            if (board[rowNum-1][colNum]==enemy) return true;
        }
        if (isInBoard(rowNum-1, colNum+1)){
            if (board[rowNum-1][colNum+1]==enemy) return true;
        }
    }
    
    return false;
}

void Game::executeMove(gameMove moveInfo){
    //cout << "move as of executeMove: " << moveInfo.cannon_move << endl;
    if(!(moveInfo.cannon_move)){
        int temp = board[moveInfo.curr_row][moveInfo.curr_col];
        int capture = board[moveInfo.dest_row][moveInfo.dest_col];
        board[moveInfo.curr_row][moveInfo.curr_col] = -1;
        board[moveInfo.dest_row][moveInfo.dest_col] = temp;
        int num1 = (int)(cols*3/2);
        if(temp == 3){
            if(player != 1){
                for(int i=0; i< num1; i++){
                    if(mySoldierRows[i] == moveInfo.curr_row && mySoldierCols[i] == moveInfo.curr_col){
                        mySoldierRows[i] = moveInfo.dest_row;
                        mySoldierCols[i] = moveInfo.dest_col;
                        break;
                    }
                }
                if(capture == 1){
                    for(int i=0; i< num1; i++){
                        if(oppSoldierRows[i] == moveInfo.dest_row && oppSoldierCols[i] == moveInfo.dest_col){
                            oppSoldierRows[i] = -1;
                            oppSoldierCols[i] = -1;
                            break;
                        }
                    }
                }
            }
            else{
                for(int i=0; i< num1; i++){
                    if(oppSoldierRows[i] == moveInfo.curr_row && oppSoldierCols[i] == moveInfo.curr_col){
                        oppSoldierRows[i] = moveInfo.dest_row;
                        oppSoldierCols[i] = moveInfo.dest_col;
                        break;
                    }
                }
                if(capture == 1){
                    for(int i=0; i< num1; i++){
                        if(mySoldierRows[i] == moveInfo.dest_row && mySoldierCols[i] == moveInfo.dest_col){
                            mySoldierRows[i] = -1;
                            mySoldierCols[i] = -1;
                            break;
                        }
                    }
                }
            }
        }
        else if(temp == 1){
            if(player == 1){
                for(int i=0; i< num1; i++){
                    if(mySoldierRows[i] == moveInfo.curr_row && mySoldierCols[i] == moveInfo.curr_col){
                        mySoldierRows[i] = moveInfo.dest_row;
                        mySoldierCols[i] = moveInfo.dest_col;
                        break;
                    }
                }
                if(capture == 3){
                    for(int i=0; i< num1; i++){
                        if(oppSoldierRows[i] == moveInfo.dest_row && oppSoldierCols[i] == moveInfo.dest_col){
                            oppSoldierRows[i] = -1;
                            oppSoldierCols[i] = -1;
                            break;
                        }
                    }
                }
            }
            else{
                for(int i=0; i< num1; i++){
                    if(oppSoldierRows[i] == moveInfo.curr_row && oppSoldierCols[i] == moveInfo.curr_col){
                        oppSoldierRows[i] = moveInfo.dest_row;
                        oppSoldierCols[i] = moveInfo.dest_col;
                        break;
                    }
                }
                if(capture == 3){
                    for(int i=0; i< num1; i++){
                        if(mySoldierRows[i] == moveInfo.dest_row && mySoldierCols[i] == moveInfo.dest_col){
                            mySoldierRows[i] = -1;
                            mySoldierCols[i] = -1;
                            break;
                        }
                    }
                }
            }
        }
    }

    else {
        //cout << "correctly read cannon blast:" << endl;
        int temp = board[moveInfo.dest_row][moveInfo.dest_col];
        board[moveInfo.dest_row][moveInfo.dest_col] = -1;
        int num1 = (int)(cols*3/2);
        if(temp == 3){
            if(player!=1){
                for(int i=0; i< num1; i++){
                    if(mySoldierRows[i] == moveInfo.dest_row && mySoldierCols[i] == moveInfo.dest_col){
                        mySoldierRows[i] = -1;
                        mySoldierCols[i] = -1;
                        break;
                    }
                    //if(i==num1-1)
                        //cout << "no one died" << endl;
                }
            }
            else{
                for(int i=0; i< num1; i++){
                    if(oppSoldierRows[i] == moveInfo.dest_row && oppSoldierCols[i] == moveInfo.dest_col){
                        oppSoldierRows[i] = -1;
                        oppSoldierCols[i] = -1;
                        break;
                    }
                    //if(i==num1-1)
                        //cout << "no one died" << endl;
                }
            }
        }
        else if(temp == 1){
            if(player==1){
                for(int i=0; i< num1; i++){
                    if(mySoldierRows[i] == moveInfo.dest_row && mySoldierCols[i] == moveInfo.dest_col){
                        mySoldierRows[i] = -1;
                        mySoldierCols[i] = -1;
                        break;
                    }
                }
            }
            else{
                for(int i=0; i< num1; i++){
                    if(oppSoldierRows[i] == moveInfo.dest_row && oppSoldierCols[i] == moveInfo.dest_col){
                        oppSoldierRows[i] = -1;
                        oppSoldierCols[i] = -1;
                        break;
                    }
                }
            }
        }
    }
    /*int num1 = (int)(cols*3/2);
    for (int i=0; i<num1; i++) {
        if(mySoldierCols[i] != -1)
            cout << "(" << mySoldierCols[i] << ", " << rows - 1 - mySoldierRows[i] << ")"<<endl;
        else
            cout << "(" << mySoldierCols[i] << ", " << mySoldierRows[i] << ")"<<endl;
    }
    cout << "opponents" << endl;
    for (int i=0; i<num1; i++) {
        if(oppSoldierCols[i] != -1)
           cout << "(" << oppSoldierCols[i] << ", " << rows - 1 - oppSoldierRows[i] << ")"<<endl;
        else
           cout << "(" << oppSoldierCols[i] << ", " << oppSoldierRows[i] << ")"<<endl;
    }*/

}

ScoreAndMoves Game::getValidMoves(){
    ScoreAndMoves allMoves = ScoreAndMoves();
    int soldiers = (int)(cols*3/2);
    for (int i=0; i<soldiers; i++){
        gameMove temp = gameMove(-1, -1, -1, -1, false);
        if (mySoldierRows[i]!=-1 && mySoldierCols[i]!=-1){
            if (player==2){
            //Searching for non-cannon moves
                //forward non-capture moves
                if (isInBoard(mySoldierRows[i]+1, mySoldierCols[i]-1)){
                    if (board[mySoldierRows[i]+1][mySoldierCols[i]-1]==1){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+1, mySoldierCols[i]-1, false);
                        allMoves.Posmoves[3].push_back(temp);
//                        allMoves.score = allMoves.score + x;
                    }
                    else if (board[mySoldierRows[i]+1][mySoldierCols[i]-1]==2){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+1, mySoldierCols[i]-1, false);
                        allMoves.Posmoves[2].push_back(temp);
//                        allMoves.score = allMoves.score + (10*x);
                    }
                    else if (board[mySoldierRows[i]+1][mySoldierCols[i]-1]==-1){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+1, mySoldierCols[i]-1, false);
                        allMoves.Posmoves[5].push_back(temp);
//                        allMoves.score = allMoves.score + 1;
                    }
                }
                
                if (isInBoard(mySoldierRows[i]+1, mySoldierCols[i])){
                    if (board[mySoldierRows[i]+1][mySoldierCols[i]]==1){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+1, mySoldierCols[i], false);
                        allMoves.Posmoves[3].push_back(temp);
//                        allMoves.score = allMoves.score + x;
                    }
                    else if (board[mySoldierRows[i]+1][mySoldierCols[i]]==2){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+1, mySoldierCols[i], false);
                        allMoves.Posmoves[2].push_back(temp);
//                        allMoves.score = allMoves.score + (10*x);
                    }
                    else if (board[mySoldierRows[i]+1][mySoldierCols[i]]==-1){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+1, mySoldierCols[i], false);
                        allMoves.Posmoves[5].push_back(temp);
//                        allMoves.score = allMoves.score + 1;
                }
                }

                if (isInBoard(mySoldierRows[i]+1, mySoldierCols[i]+1)){
                    if (board[mySoldierRows[i]+1][mySoldierCols[i]+1]==1){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+1, mySoldierCols[i]+1, false);
                        allMoves.Posmoves[3].push_back(temp);
//                        allMoves.score = allMoves.score + x;
                    }
                    else if (board[mySoldierRows[i]+1][mySoldierCols[i]+1]==2){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+1, mySoldierCols[i]+1, false);
                        allMoves.Posmoves[2].push_back(temp);
//                        allMoves.score = allMoves.score + (10*x);
                    }
                else if (board[mySoldierRows[i]+1][mySoldierCols[i]+1]==-1){
                    temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+1, mySoldierCols[i]+1, false);
                    allMoves.Posmoves[5].push_back(temp);
//                    allMoves.score = allMoves.score + 1;
                }
                }
                
                //capture side-ways moves
                if (isInBoard(mySoldierRows[i], mySoldierCols[i]-1)){
                    if (board[mySoldierRows[i]][mySoldierCols[i]-1]==1){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]-1, false);
                        allMoves.Posmoves[3].push_back(temp);
//                        allMoves.score = allMoves.score + x;
                    }else if (board[mySoldierRows[i]][mySoldierCols[i]-1]==2){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]-1, false);
                        allMoves.Posmoves[2].push_back(temp);
//                        allMoves.score = allMoves.score + (10*x);
                    }
                }

                if (isInBoard(mySoldierRows[i], mySoldierCols[i]+1)){
                    if (board[mySoldierRows[i]][mySoldierCols[i]+1]==1){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]+1, false);
                        allMoves.Posmoves[3].push_back(temp);
//                        allMoves.score = allMoves.score + x;
                    }else if (board[mySoldierRows[i]][mySoldierCols[i]+1]==2){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]+1, false);
                        allMoves.Posmoves[2].push_back(temp);
//                        allMoves.score = allMoves.score + (10*x);
                    }
                }
                
                //non-capture backwards move
                if (enemyAdjacent(mySoldierRows[i], mySoldierCols[i])){
                    if (isInBoard(mySoldierRows[i]-2, mySoldierCols[i]-2)){
                        if (board[mySoldierRows[i]-2][mySoldierCols[i]-2]==-1 && (board[mySoldierRows[i]-1][mySoldierCols[i]-1]==-1 || board[mySoldierRows[i]-1][mySoldierCols[i]-1]==3)){
                            temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-2, mySoldierCols[i]-2, false);
                            allMoves.Posmoves[5].push_back(temp);
//                            allMoves.score = allMoves.score + 1;
                        }else if (board[mySoldierRows[i]-2][mySoldierCols[i]-2]==1 && (board[mySoldierRows[i]-1][mySoldierCols[i]-1]==-1 || board[mySoldierRows[i]-1][mySoldierCols[i]-1]==3)){
                            temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-2, mySoldierCols[i]-2, false);
                            allMoves.Posmoves[3].push_back(temp);
                            //                            allMoves.score = allMoves.score + 1;
                        }
                    }

                    if (isInBoard(mySoldierRows[i]-2, mySoldierCols[i])){
                        if (board[mySoldierRows[i]-2][mySoldierCols[i]]==-1 && (board[mySoldierRows[i]-1][mySoldierCols[i]]==-1 || board[mySoldierRows[i]-1][mySoldierCols[i]]==3)){
                            temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-2, mySoldierCols[i], false);
                            allMoves.Posmoves[5].push_back(temp);
//                            allMoves.score = allMoves.score + 1;
                        }else if (board[mySoldierRows[i]-2][mySoldierCols[i]]==1 && (board[mySoldierRows[i]-1][mySoldierCols[i]]==-1 || board[mySoldierRows[i]-1][mySoldierCols[i]]==3)){
                            temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-2, mySoldierCols[i], false);
                            allMoves.Posmoves[3].push_back(temp);
                            //                            allMoves.score = allMoves.score + 1;
                        }
                    }

                    if (isInBoard(mySoldierRows[i]-2, mySoldierCols[i]+2)){
                        if (board[mySoldierRows[i]-2][mySoldierCols[i]+2]==-1 && (board[mySoldierRows[i]-1][mySoldierCols[i]+1]==-1 || board[mySoldierRows[i]-1][mySoldierCols[i]+1]==3)){
                            temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-2, mySoldierCols[i]+2, false);
                            allMoves.Posmoves[5].push_back(temp);
//                            allMoves.score = allMoves.score + 1;
                        }else if (board[mySoldierRows[i]-2][mySoldierCols[i]+2]==1 && (board[mySoldierRows[i]-1][mySoldierCols[i]+1]==-1 || board[mySoldierRows[i]-1][mySoldierCols[i]+1]==3)){
                            temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-2, mySoldierCols[i]+2, false);
                            allMoves.Posmoves[3].push_back(temp);
                            //                            allMoves.score = allMoves.score + 1;
                        }
                    }
                }
                
                //Cannon moves
                //'x'
                // x
                // x
                if (isInBoard(mySoldierRows[i]-2, mySoldierCols[i])){
                    if (board[mySoldierRows[i]-1][mySoldierCols[i]]==3 && board[mySoldierRows[i]-2][mySoldierCols[i]]==3){
                        allMoves.score = allMoves.score + 1;
                        //capture-moves by cannon
                        if (isInBoard(mySoldierRows[i]+3, mySoldierCols[i])){
                            if (board[mySoldierRows[i]+3][mySoldierCols[i]]==1 && board[mySoldierRows[i]+1][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i], true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]+3][mySoldierCols[i]]==2 && board[mySoldierRows[i]+1][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i], true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]+3][mySoldierCols[i]]==-1 && board[mySoldierRows[i]+1][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i], true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        if (isInBoard(mySoldierRows[i]+2, mySoldierCols[i])){
                            if (board[mySoldierRows[i]+2][mySoldierCols[i]]==1 && board[mySoldierRows[i]+1][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i], true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]+2][mySoldierCols[i]]==2 && board[mySoldierRows[i]+1][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i], true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]+2][mySoldierCols[i]]==-1 && board[mySoldierRows[i]+1][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i], true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }

                        if (isInBoard(mySoldierRows[i]-5, mySoldierCols[i])){
                            if (board[mySoldierRows[i]-5][mySoldierCols[i]]==1 && board[mySoldierRows[i]-3][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i], mySoldierRows[i]-5, mySoldierCols[i], true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]-5][mySoldierCols[i]]==2 && board[mySoldierRows[i]-3][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i], mySoldierRows[i]-5, mySoldierCols[i], true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]-5][mySoldierCols[i]]==-1 && board[mySoldierRows[i]-3][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i], mySoldierRows[i]-5, mySoldierCols[i], true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        if (isInBoard(mySoldierRows[i]-4, mySoldierCols[i])){
                            if (board[mySoldierRows[i]-4][mySoldierCols[i]]==1&& board[mySoldierRows[i]-3][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i], mySoldierRows[i]-4, mySoldierCols[i], true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if ( board[mySoldierRows[i]-4][mySoldierCols[i]]==2 && board[mySoldierRows[i]-3][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i], mySoldierRows[i]-4, mySoldierCols[i], true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]-4][mySoldierCols[i]]==-1 && board[mySoldierRows[i]-3][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i], mySoldierRows[i]-4, mySoldierCols[i], true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }

                        //non-capture moves
                        if (isInBoard(mySoldierRows[i]+1, mySoldierCols[i])){
                            if (board[mySoldierRows[i]+1][mySoldierCols[i]] == -1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i], mySoldierRows[i]+1, mySoldierCols[i], false);
                                allMoves.Posmoves[4].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        if (isInBoard(mySoldierRows[i]-3, mySoldierCols[i])){
                            if (board[mySoldierRows[i]-3][mySoldierCols[i]] == -1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-3, mySoldierCols[i], false);
                                allMoves.Posmoves[4].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                    }
                }
                
                
                //   'x'
                //  x
                //x
                if (isInBoard(mySoldierRows[i]-2, mySoldierCols[i]-2)){
                    if (board[mySoldierRows[i]-1][mySoldierCols[i]-1]==3 && board[mySoldierRows[i]-2][mySoldierCols[i]-2]==3){
                        //capture-moves by cannon
                        allMoves.score = allMoves.score + 1;
                        if (isInBoard(mySoldierRows[i]+3, mySoldierCols[i]+3)){
                            if (board[mySoldierRows[i]+3][mySoldierCols[i]+3]==1 && board[mySoldierRows[i]+1][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i]+3, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]+3][mySoldierCols[i]+3]==2 && board[mySoldierRows[i]+1][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i]+3, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]+3][mySoldierCols[i]+3]==-1 && board[mySoldierRows[i]+1][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i]+3, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        if (isInBoard(mySoldierRows[i]+2, mySoldierCols[i]+2)){
                            if (board[mySoldierRows[i]+2][mySoldierCols[i]+2]==1 && board[mySoldierRows[i]+1][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i]+2, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]+2][mySoldierCols[i]+2]==2 && board[mySoldierRows[i]+1][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i]+2, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]+2][mySoldierCols[i]+2]==-1 && board[mySoldierRows[i]+1][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i]+2, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        if (isInBoard(mySoldierRows[i]-5, mySoldierCols[i]-5)){
                            if (board[mySoldierRows[i]-5][mySoldierCols[i]-5]==1 && board[mySoldierRows[i]-3][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]-2, mySoldierRows[i]-5, mySoldierCols[i]-5, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]-5][mySoldierCols[i]-5]==2 && board[mySoldierRows[i]-3][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]-2, mySoldierRows[i]-5, mySoldierCols[i]-5, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]-5][mySoldierCols[i]-5]==-1 && board[mySoldierRows[i]-3][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]-2, mySoldierRows[i]-5, mySoldierCols[i]-5, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        if (isInBoard(mySoldierRows[i]-4, mySoldierCols[i]-4)){
                            if (board[mySoldierRows[i]-4][mySoldierCols[i]-4]==1 && board[mySoldierRows[i]-3][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]-2, mySoldierRows[i]-4, mySoldierCols[i]-4, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]-4][mySoldierCols[i]-4]==2 && board[mySoldierRows[i]-3][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]-2, mySoldierRows[i]-4, mySoldierCols[i]-4, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]-4][mySoldierCols[i]-4]==-1 && board[mySoldierRows[i]-3][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]-2, mySoldierRows[i]-4, mySoldierCols[i]-4, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        //non-capture moves
                        if (isInBoard(mySoldierRows[i]+1, mySoldierCols[i]+1)){
                            if (board[mySoldierRows[i]+1][mySoldierCols[i]+1] == -1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]-2, mySoldierRows[i]+1, mySoldierCols[i]+1, false);
                                allMoves.Posmoves[4].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }

                        if (isInBoard(mySoldierRows[i]-3, mySoldierCols[i]-3)){
                            if (board[mySoldierRows[i]-3][mySoldierCols[i]-3] == -1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-3, mySoldierCols[i]-3, false);
                                allMoves.Posmoves[4].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                    }
                }
                
                
                //'x'
                //   x
                //     x
                if (isInBoard(mySoldierRows[i]-2, mySoldierCols[i]+2)){
                    if (board[mySoldierRows[i]-1][mySoldierCols[i]+1]==3 && board[mySoldierRows[i]-2][mySoldierCols[i]+2]==3){
                        //capture-moves by cannon
                        allMoves.score = allMoves.score + 1;
                        if (isInBoard(mySoldierRows[i]+3, mySoldierCols[i]-3)){
                            if (board[mySoldierRows[i]+3][mySoldierCols[i]-3]==1 && board[mySoldierRows[i]+1][mySoldierCols[i]-1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i]-3, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]+3][mySoldierCols[i]-3]==2 && board[mySoldierRows[i]+1][mySoldierCols[i]-1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i]-3, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]+3][mySoldierCols[i]-3]==-1 && board[mySoldierRows[i]+1][mySoldierCols[i]-1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i]-3, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        if (isInBoard(mySoldierRows[i]+2, mySoldierCols[i]-2)){
                            if (board[mySoldierRows[i]+2][mySoldierCols[i]-2]==1 && board[mySoldierRows[i]+1][mySoldierCols[i]-1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i]-2, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]+2][mySoldierCols[i]-2]==2 && board[mySoldierRows[i]+1][mySoldierCols[i]-1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i]-2, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]+2][mySoldierCols[i]-2]==-1 && board[mySoldierRows[i]+1][mySoldierCols[i]-1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i]-2, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        if (isInBoard(mySoldierRows[i]-5, mySoldierCols[i]+5)){
                            if (board[mySoldierRows[i]-5][mySoldierCols[i]+5]==1 && board[mySoldierRows[i]-3][mySoldierCols[i]+3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]+2, mySoldierRows[i]-5, mySoldierCols[i]+5, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]-5][mySoldierCols[i]+5]==2 && board[mySoldierRows[i]-3][mySoldierCols[i]+3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]+2, mySoldierRows[i]-5, mySoldierCols[i]+5, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]-5][mySoldierCols[i]+5]==-1 && board[mySoldierRows[i]-3][mySoldierCols[i]+3]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-5, mySoldierCols[i]+5, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        if (isInBoard(mySoldierRows[i]-4, mySoldierCols[i]+4)){
                            if (board[mySoldierRows[i]-4][mySoldierCols[i]+4]==1 && board[mySoldierRows[i]-3][mySoldierCols[i]+3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]+2, mySoldierRows[i]-4, mySoldierCols[i]+4, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]-4][mySoldierCols[i]+4]==2 && board[mySoldierRows[i]-3][mySoldierCols[i]+3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]+2, mySoldierRows[i]-4, mySoldierCols[i]+4, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]-4][mySoldierCols[i]+4]==-1 && board[mySoldierRows[i]-3][mySoldierCols[i]+3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]+2, mySoldierRows[i]-4, mySoldierCols[i]+4, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        //non-capture moves
                        if (isInBoard(mySoldierRows[i]+1, mySoldierCols[i]-1)){
                            if (board[mySoldierRows[i]+1][mySoldierCols[i]-1] == -1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]+2, mySoldierRows[i]+1, mySoldierCols[i]-1, false);
                                allMoves.Posmoves[4].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }

                        if (isInBoard(mySoldierRows[i]-3, mySoldierCols[i]+3)){
                            if (board[mySoldierRows[i]-3][mySoldierCols[i]+3] == -1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-3, mySoldierCols[i]+3, false);
                                allMoves.Posmoves[4].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                    }
                }
                
                //xx'x'
                if (isInBoard(mySoldierRows[i], mySoldierCols[i]-2)){
                    if (board[mySoldierRows[i]][mySoldierCols[i]-1]==3 && board[mySoldierRows[i]][mySoldierCols[i]-2]==3){
                        //capture-moves by cannon
                        allMoves.score = allMoves.score + 1;
                        if (isInBoard(mySoldierRows[i], mySoldierCols[i]+3)){
                            if (board[mySoldierRows[i]][mySoldierCols[i]+3]==1 && board[mySoldierRows[i]][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]+3, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]][mySoldierCols[i]+3]==2 && board[mySoldierRows[i]][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]+3, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]][mySoldierCols[i]+3]==-1 && board[mySoldierRows[i]][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]+3, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        if (isInBoard(mySoldierRows[i], mySoldierCols[i]+2)){
                            if (board[mySoldierRows[i]][mySoldierCols[i]+2]==1 && board[mySoldierRows[i]][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]+2, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]][mySoldierCols[i]+2]==2 && board[mySoldierRows[i]][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]+2, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]][mySoldierCols[i]+2]==-1 && board[mySoldierRows[i]][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]+2, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        if (isInBoard(mySoldierRows[i], mySoldierCols[i]-5)){
                            if (board[mySoldierRows[i]][mySoldierCols[i]-5]==1 && board[mySoldierRows[i]][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i]-2, mySoldierRows[i], mySoldierCols[i]-5, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]][mySoldierCols[i]-5]==2 && board[mySoldierRows[i]][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i]-2, mySoldierRows[i], mySoldierCols[i]-5, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]][mySoldierCols[i]-5]==-1 && board[mySoldierRows[i]][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i]-2, mySoldierRows[i], mySoldierCols[i]-5, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        if (isInBoard(mySoldierRows[i], mySoldierCols[i]-4)){
                            if (board[mySoldierRows[i]][mySoldierCols[i]-4]==1 && board[mySoldierRows[i]][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i]-2, mySoldierRows[i], mySoldierCols[i]-4, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]][mySoldierCols[i]-4]==2 && board[mySoldierRows[i]][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i]-2, mySoldierRows[i], mySoldierCols[i]-4, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]][mySoldierCols[i]-4]==-1 && board[mySoldierRows[i]][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i]-2, mySoldierRows[i], mySoldierCols[i]-4, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        //non-capture moves
                        if (isInBoard(mySoldierRows[i], mySoldierCols[i]+1)){
                            if (board[mySoldierRows[i]][mySoldierCols[i]+1] == -1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i]-2, mySoldierRows[i], mySoldierCols[i]+1, false);
                                allMoves.Posmoves[4].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        if (isInBoard(mySoldierRows[i], mySoldierCols[i]-3)){
                            if (board[mySoldierRows[i]][mySoldierCols[i]-3] == -1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]-3, false);
                                allMoves.Posmoves[4].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                    }
                }

            }
            else{
                //Searching for non-cannon moves
                //forward non-capture moves
                if (isInBoard(mySoldierRows[i]-1, mySoldierCols[i]-1)){
                    if (board[mySoldierRows[i]-1][mySoldierCols[i]-1]==3){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-1, mySoldierCols[i]-1, false);
                        allMoves.Posmoves[3].push_back(temp);
//                        allMoves.score = allMoves.score + x;
                    }else if (board[mySoldierRows[i]-1][mySoldierCols[i]-1]==4){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-1, mySoldierCols[i]-1, false);
                        allMoves.Posmoves[2].push_back(temp);
//                        allMoves.score = allMoves.score + (10*x);
                    }
                    else if (board[mySoldierRows[i]-1][mySoldierCols[i]-1]==-1){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-1, mySoldierCols[i]-1, false);
                        allMoves.Posmoves[5].push_back(temp);
//                        allMoves.score = allMoves.score +1;
                    }
                }
                
                if (isInBoard(mySoldierRows[i]-1, mySoldierCols[i])){
                    if (board[mySoldierRows[i]-1][mySoldierCols[i]]==3){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-1, mySoldierCols[i], false);
                        allMoves.Posmoves[3].push_back(temp);
//                        allMoves.score = allMoves.score + x;
                    }else if (board[mySoldierRows[i]-1][mySoldierCols[i]]==4){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-1, mySoldierCols[i], false);
                        allMoves.Posmoves[2].push_back(temp);
//                        allMoves.score = allMoves.score + (10*x);
                    }
                else if (board[mySoldierRows[i]-1][mySoldierCols[i]]==-1){
                    temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-1, mySoldierCols[i], false);
                    allMoves.Posmoves[5].push_back(temp);
//                    allMoves.score = allMoves.score +1;
                }
                }
                
                if (isInBoard(mySoldierRows[i]-1, mySoldierCols[i]+1)){
                    if (board[mySoldierRows[i]-1][mySoldierCols[i]+1]==3){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-1, mySoldierCols[i]+1, false);
                        allMoves.Posmoves[3].push_back(temp);
//                        allMoves.score = allMoves.score + x;
                    }else if (board[mySoldierRows[i]-1][mySoldierCols[i]+1]==4){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-1, mySoldierCols[i]+1, false);
                        allMoves.Posmoves[2].push_back(temp);
//                        allMoves.score = allMoves.score + (10*x);
                    }
                else if (board[mySoldierRows[i]-1][mySoldierCols[i]+1]==-1){
                    temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-1, mySoldierCols[i]+1, false);
                    allMoves.Posmoves[5].push_back(temp);
//                    allMoves.score = allMoves.score +1;
                }
                }
                
                //capture side-ways moves
                if (isInBoard(mySoldierRows[i], mySoldierCols[i]-1)){
                    if (board[mySoldierRows[i]][mySoldierCols[i]-1]==3){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]-1, false);
                        allMoves.Posmoves[3].push_back(temp);
//                        allMoves.score = allMoves.score + x;
                    }else if (board[mySoldierRows[i]][mySoldierCols[i]-1]==4){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]-1, false);
                        allMoves.Posmoves[2].push_back(temp);
//                        allMoves.score = allMoves.score + (10*x);
                    }
                }
                
                if (isInBoard(mySoldierRows[i], mySoldierCols[i]+1)){
                    if (board[mySoldierRows[i]][mySoldierCols[i]+1]==3){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]+1, false);
                        allMoves.Posmoves[3].push_back(temp);
//                        allMoves.score = allMoves.score + x;
                    }else if (board[mySoldierRows[i]][mySoldierCols[i]+1]==4){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]+1, false);
                        allMoves.Posmoves[2].push_back(temp);
//                        allMoves.score = allMoves.score + (10*x);
                    }
                }
                
                //non-capture backwards move
                if (enemyAdjacent(mySoldierRows[i], mySoldierCols[i])){
                if (isInBoard(mySoldierRows[i]+2, mySoldierCols[i]-2)){
                    if (board[mySoldierRows[i]+2][mySoldierCols[i]-2]==-1 && (board[mySoldierRows[i]+1][mySoldierCols[i]-1]==-1 || board[mySoldierRows[i]+1][mySoldierCols[i]-1]==1)){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i]-2, false);
                        allMoves.Posmoves[5].push_back(temp);
//                        allMoves.score = allMoves.score + 1;
                    }else if (board[mySoldierRows[i]+2][mySoldierCols[i]-2]==3 && (board[mySoldierRows[i]+1][mySoldierCols[i]-1]==-1 || board[mySoldierRows[i]+1][mySoldierCols[i]-1]==1)){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i]-2, false);
                        allMoves.Posmoves[3].push_back(temp);
                        //                        allMoves.score = allMoves.score + 1;
                    }
                }
                
                if (isInBoard(mySoldierRows[i]+2, mySoldierCols[i])){
                    if (board[mySoldierRows[i]+2][mySoldierCols[i]]==-1 && (board[mySoldierRows[i]+1][mySoldierCols[i]]==-1 || board[mySoldierRows[i]+1][mySoldierCols[i]]==1)){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i], false);
                        allMoves.Posmoves[5].push_back(temp);
//                        allMoves.score = allMoves.score + 1;
                    }else if (board[mySoldierRows[i]+2][mySoldierCols[i]]==3 && (board[mySoldierRows[i]+1][mySoldierCols[i]]==-1 || board[mySoldierRows[i]+1][mySoldierCols[i]]==1)){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i], false);
                        allMoves.Posmoves[3].push_back(temp);
                        //                        allMoves.score = allMoves.score + 1;
                    }
                }
                
                if (isInBoard(mySoldierRows[i]+2, mySoldierCols[i]+2)){
                    if (board[mySoldierRows[i]+2][mySoldierCols[i]+2]==-1 && (board[mySoldierRows[i]+1][mySoldierCols[i]+1]==-1 || board[mySoldierRows[i]+1][mySoldierCols[i]+1]==1)){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i]+2, false);
                        allMoves.Posmoves[5].push_back(temp);
//                        allMoves.score = allMoves.score + 1;
                    }else if (board[mySoldierRows[i]+2][mySoldierCols[i]+2]==3 && (board[mySoldierRows[i]+1][mySoldierCols[i]+1]==-1 || board[mySoldierRows[i]+1][mySoldierCols[i]+1]==1)){
                        temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i]+2, false);
                        allMoves.Posmoves[3].push_back(temp);
                        //                        allMoves.score = allMoves.score + 1;
                    }
                }
                }
                
                //Cannon moves
                //'x'
                // x
                // x
                if (isInBoard(mySoldierRows[i]-2, mySoldierCols[i])){
                    if (board[mySoldierRows[i]-1][mySoldierCols[i]]==1 && board[mySoldierRows[i]-2][mySoldierCols[i]]==1){
                        allMoves.score = allMoves.score + 1;
                        //capture-moves by cannon
                        if (isInBoard(mySoldierRows[i]+3, mySoldierCols[i])){
                            if (board[mySoldierRows[i]+3][mySoldierCols[i]]==3 && board[mySoldierRows[i]+1][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i], true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]+3][mySoldierCols[i]]==4 && board[mySoldierRows[i]+1][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i], true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]+3][mySoldierCols[i]]==-1 && board[mySoldierRows[i]+1][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i], true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        if (isInBoard(mySoldierRows[i]+2, mySoldierCols[i])){
                            if (board[mySoldierRows[i]+2][mySoldierCols[i]]==3 && board[mySoldierRows[i]+1][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i], true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]+2][mySoldierCols[i]]==4 && board[mySoldierRows[i]+1][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i], true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]+2][mySoldierCols[i]]==-1 && board[mySoldierRows[i]+1][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i], true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        if (isInBoard(mySoldierRows[i]-5, mySoldierCols[i])){
                            if (board[mySoldierRows[i]-5][mySoldierCols[i]]==3 && board[mySoldierRows[i]-3][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i], mySoldierRows[i]-5, mySoldierCols[i], true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]-5][mySoldierCols[i]]==4 && board[mySoldierRows[i]-3][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i], mySoldierRows[i]-5, mySoldierCols[i], true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]-5][mySoldierCols[i]]==-1 && board[mySoldierRows[i]-3][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i], mySoldierRows[i]-5, mySoldierCols[i], true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        if (isInBoard(mySoldierRows[i]-4, mySoldierCols[i])){
                            if (board[mySoldierRows[i]-4][mySoldierCols[i]]==3 && board[mySoldierRows[i]-3][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i], mySoldierRows[i]-4, mySoldierCols[i], true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]-4][mySoldierCols[i]]==4 && board[mySoldierRows[i]-3][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i], mySoldierRows[i]-4, mySoldierCols[i], true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]-4][mySoldierCols[i]]==-1 && board[mySoldierRows[i]-3][mySoldierCols[i]]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i], mySoldierRows[i]-4, mySoldierCols[i], true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        //non-capture moves
                        if (isInBoard(mySoldierRows[i]+1, mySoldierCols[i])){
                            if (board[mySoldierRows[i]+1][mySoldierCols[i]] == -1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i], mySoldierRows[i]+1, mySoldierCols[i], false);
                                allMoves.Posmoves[4].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        if (isInBoard(mySoldierRows[i]-3, mySoldierCols[i])){
                            if (board[mySoldierRows[i]-3][mySoldierCols[i]] == -1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-3, mySoldierCols[i], false);
                                allMoves.Posmoves[4].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                    }
                }
                
                
                //  'x'
                // x
                //x
                if (isInBoard(mySoldierRows[i]-2, mySoldierCols[i]-2)){
                    if (board[mySoldierRows[i]-1][mySoldierCols[i]-1]==1 && board[mySoldierRows[i]-2][mySoldierCols[i]-2]==1){
                        allMoves.score = allMoves.score + 1;
                        //capture-moves by cannon
                        if (isInBoard(mySoldierRows[i]+3, mySoldierCols[i]+3)){
                            if (board[mySoldierRows[i]+3][mySoldierCols[i]+3]==3 && board[mySoldierRows[i]+1][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i]+3, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]+3][mySoldierCols[i]+3]==4 && board[mySoldierRows[i]+1][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i]+3, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]+3][mySoldierCols[i]+3]==-1 && board[mySoldierRows[i]+1][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i]+3, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        if (isInBoard(mySoldierRows[i]+2, mySoldierCols[i]+2)){
                            if (board[mySoldierRows[i]+2][mySoldierCols[i]+2]==3 && board[mySoldierRows[i]+1][mySoldierCols[i]+1]== -1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i]+2, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]+2][mySoldierCols[i]+2]==4 && board[mySoldierRows[i]+1][mySoldierCols[i]+1]== -1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i]+2, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]+2][mySoldierCols[i]+2]==-1 && board[mySoldierRows[i]+1][mySoldierCols[i]+1]== -1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i]+2, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        if (isInBoard(mySoldierRows[i]-5, mySoldierCols[i]-5)){
                            if (board[mySoldierRows[i]-5][mySoldierCols[i]-5]==3 && board[mySoldierRows[i]-3][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]-2, mySoldierRows[i]-5, mySoldierCols[i]-5, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]-5][mySoldierCols[i]-5]==4 && board[mySoldierRows[i]-3][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]-2, mySoldierRows[i]-5, mySoldierCols[i]-5, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]-5][mySoldierCols[i]-5]==-1 && board[mySoldierRows[i]-3][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]-2, mySoldierRows[i]-5, mySoldierCols[i]-5, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        if (isInBoard(mySoldierRows[i]-4, mySoldierCols[i]-4)){
                            if (board[mySoldierRows[i]-4][mySoldierCols[i]-4]==3 && board[mySoldierRows[i]-3][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]-2, mySoldierRows[i]-4, mySoldierCols[i]-4, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]-4][mySoldierCols[i]-4]==4 && board[mySoldierRows[i]-3][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]-2, mySoldierRows[i]-4, mySoldierCols[i]-4, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]-4][mySoldierCols[i]-4]==-1 && board[mySoldierRows[i]-3][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]-2, mySoldierRows[i]-4, mySoldierCols[i]-4, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        //non-capture moves
                        if (isInBoard(mySoldierRows[i]+1, mySoldierCols[i]+1)){
                            if (board[mySoldierRows[i]+1][mySoldierCols[i]+1] == -1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]-2, mySoldierRows[i]+1, mySoldierCols[i]+1, false);
                                allMoves.Posmoves[4].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }

                        if (isInBoard(mySoldierRows[i]-3, mySoldierCols[i]-3)){
                            if (board[mySoldierRows[i]-3][mySoldierCols[i]-3] == -1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-3, mySoldierCols[i]-3, false);
                                allMoves.Posmoves[4].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                    }
                }
                
                
                //'x'
                //   x
                //    x
                if (isInBoard(mySoldierRows[i]-2, mySoldierCols[i]+2)){
                    if (board[mySoldierRows[i]-1][mySoldierCols[i]+1]==1 && board[mySoldierRows[i]-2][mySoldierCols[i]+2]==1){
                        allMoves.score = allMoves.score + 1;
                        //capture-moves by cannon
                        if (isInBoard(mySoldierRows[i]+3, mySoldierCols[i]-3)){
                            if (board[mySoldierRows[i]+3][mySoldierCols[i]-3]==3 && board[mySoldierRows[i]+1][mySoldierCols[i]-1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i]-3, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]+3][mySoldierCols[i]-3]==4 && board[mySoldierRows[i]+1][mySoldierCols[i]-1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i]-3, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]+3][mySoldierCols[i]-3]==-1 && board[mySoldierRows[i]+1][mySoldierCols[i]-1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+3, mySoldierCols[i]-3, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        if (isInBoard(mySoldierRows[i]+2, mySoldierCols[i]-2)){
                            if (board[mySoldierRows[i]+2][mySoldierCols[i]-2]==3 && board[mySoldierRows[i]+1][mySoldierCols[i]-1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i]-2, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]+2][mySoldierCols[i]-2]==4 && board[mySoldierRows[i]+1][mySoldierCols[i]-1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i]-2, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]+2][mySoldierCols[i]-2]==-1 && board[mySoldierRows[i]+1][mySoldierCols[i]-1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]+2, mySoldierCols[i]-2, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        if (isInBoard(mySoldierRows[i]-5, mySoldierCols[i]+5)){
                            if (board[mySoldierRows[i]-5][mySoldierCols[i]+5]==3 && board[mySoldierRows[i]-3][mySoldierCols[i]+3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]+2, mySoldierRows[i]-5, mySoldierCols[i]+5, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]-5][mySoldierCols[i]+5]==4 && board[mySoldierRows[i]-3][mySoldierCols[i]+3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]+2, mySoldierRows[i]-5, mySoldierCols[i]+5, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]-5][mySoldierCols[i]+5]==-1 && board[mySoldierRows[i]-3][mySoldierCols[i]+3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]+2, mySoldierRows[i]-5, mySoldierCols[i]+5, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        if (isInBoard(mySoldierRows[i]-4, mySoldierCols[i]+4)){
                            if (board[mySoldierRows[i]-4][mySoldierCols[i]+4]==3 && board[mySoldierRows[i]-3][mySoldierCols[i]+3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]+2, mySoldierRows[i]-4, mySoldierCols[i]+4, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]-4][mySoldierCols[i]+4]==4 && board[mySoldierRows[i]-3][mySoldierCols[i]+3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]+2, mySoldierRows[i]-4, mySoldierCols[i]+4, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]-4][mySoldierCols[i]+4]==-1 && board[mySoldierRows[i]-3][mySoldierCols[i]+3]==-1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]+2, mySoldierRows[i]-4, mySoldierCols[i]+4, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        //non-capture moves
                        if (isInBoard(mySoldierRows[i]+1, mySoldierCols[i]-1)){
                            if (board[mySoldierRows[i]+1][mySoldierCols[i]-1] == -1){
                                temp = gameMove(mySoldierRows[i]-2, mySoldierCols[i]+2, mySoldierRows[i]+1, mySoldierCols[i]-1, false);
                                allMoves.Posmoves[4].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }

                        if (isInBoard(mySoldierRows[i]-3, mySoldierCols[i]+3)){
                            if (board[mySoldierRows[i]-3][mySoldierCols[i]+3] == -1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i]-3, mySoldierCols[i]+3, false);
                                allMoves.Posmoves[4].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                    }
                }
                
                
                //xx'x'
                if (isInBoard(mySoldierRows[i], mySoldierCols[i]-2)){
                    if (board[mySoldierRows[i]][mySoldierCols[i]-1]==1 && board[mySoldierRows[i]][mySoldierCols[i]-2]==1){
                        allMoves.score = allMoves.score + 1;
                        //capture-moves by cannon
                        if (isInBoard(mySoldierRows[i], mySoldierCols[i]+3)){
                            if (board[mySoldierRows[i]][mySoldierCols[i]+3]==3 && board[mySoldierRows[i]][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]+3, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]][mySoldierCols[i]+3]==4 && board[mySoldierRows[i]][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]+3, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]][mySoldierCols[i]+3]==-1 && board[mySoldierRows[i]][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]+3, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        if (isInBoard(mySoldierRows[i], mySoldierCols[i]+2)){
                            if (board[mySoldierRows[i]][mySoldierCols[i]+2]==3 && board[mySoldierRows[i]][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]+2, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]][mySoldierCols[i]+2]==4 && board[mySoldierRows[i]][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]+2, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]][mySoldierCols[i]+2]==-1 && board[mySoldierRows[i]][mySoldierCols[i]+1]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]+2, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        if (isInBoard(mySoldierRows[i], mySoldierCols[i]-5)){
                            if (board[mySoldierRows[i]][mySoldierCols[i]-5]==3 && board[mySoldierRows[i]][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i]-2, mySoldierRows[i], mySoldierCols[i]-5, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]][mySoldierCols[i]-5]==4 && board[mySoldierRows[i]][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i]-2, mySoldierRows[i], mySoldierCols[i]-5, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (10*x);
                            }else if (board[mySoldierRows[i]][mySoldierCols[i]-5]==-1 && board[mySoldierRows[i]][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i]-2, mySoldierRows[i], mySoldierCols[i]-5, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        if (isInBoard(mySoldierRows[i], mySoldierCols[i]-4)){
                            if (board[mySoldierRows[i]][mySoldierCols[i]-4]==3 && board[mySoldierRows[i]][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i]-2, mySoldierRows[i], mySoldierCols[i]-4, true);
                                allMoves.Posmoves[1].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]][mySoldierCols[i]-4]==4 && board[mySoldierRows[i]][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i]-2, mySoldierRows[i], mySoldierCols[i]-4, true);
                                allMoves.Posmoves[0].push_back(temp);
//                                allMoves.score = allMoves.score + (2*x);
                            }else if (board[mySoldierRows[i]][mySoldierCols[i]-4]==-1 && board[mySoldierRows[i]][mySoldierCols[i]-3]==-1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i]-2, mySoldierRows[i], mySoldierCols[i]-4, true);
                                allMoves.Posmoves[6].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        //non-capture moves
                        if (isInBoard(mySoldierRows[i], mySoldierCols[i]+1)){
                            if (board[mySoldierRows[i]][mySoldierCols[i]+1] == -1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i]-2, mySoldierRows[i], mySoldierCols[i]+1, false);
                                allMoves.Posmoves[4].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                        
                        if (isInBoard(mySoldierRows[i], mySoldierCols[i]-3)){
                            if (board[mySoldierRows[i]][mySoldierCols[i]-3] == -1){
                                temp = gameMove(mySoldierRows[i], mySoldierCols[i], mySoldierRows[i], mySoldierCols[i]-3, false);
                                allMoves.Posmoves[4].push_back(temp);
//                                allMoves.score = allMoves.score + 1;
                            }
                        }
                    }
                }

            }
        }
    }
    return allMoves;
}

