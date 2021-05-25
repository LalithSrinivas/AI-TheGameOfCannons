//
//  main.cpp
//  code
//
//  Created by Chinmai Sai Nagendra kokku on 9/9/19.
//  Copyright © 2019 Chinmai Sai Nagendra kokku. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <chrono>
#include "game.h"
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    int* info; info = new int[4];
    cin >> info[0];
    if (info[0]==1) info[0] = 2;
    else info[0] = 1;
    cin >> info[1];
    cin >> info[2];
    cin >> info[3];
    double remTime = (double)(info[3]*1000);
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    Game cannon = Game(info[0], info[1], info[2], remTime);
    gameMove temp = gameMove(-1, -1, -1, -1, false);
    int MinMoves = 25; int MyMoves = 0; int depth = 6; int mul_factor = 7; int max_depth = 7; int min_depth = 2;
    if (info[2] == 10){
        MinMoves = 50;
        depth = 5;
        mul_factor = 20;
        max_depth = 6;
        min_depth = 4;
    }else if (info[1]==10){
        MinMoves = 45;
        depth = 5;
        mul_factor = 15;
        max_depth = 7;
    }
    double time_span = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    gameMove prevOppMove = gameMove(-1, -1, -1, -1, false);
    gameMove prevMyMove = gameMove(-1, -1, -1, -1, false);
    bool compareOpp = false;
    if (info[0]==1){
        char move;
        int curr_row, curr_col, dest_row, dest_col;
        //x = col, y = rows-1-row
        cin >> move;
        cin >> curr_col;
        cin >> curr_row;
        curr_row = info[1] - 1 - curr_row;
        cin >> move;
        cin >> dest_col;
        cin >> dest_row;
        t1 = std::chrono::high_resolution_clock::now();
        dest_row = info[1] - 1 - dest_row;
        if (move == 'M'){
            temp = gameMove(curr_row, curr_col, dest_row, dest_col, false);
            prevOppMove = gameMove(curr_row, curr_col, dest_row, dest_col, false);
        }else{
            temp = gameMove(curr_row, curr_col, dest_row, dest_col, true);
            prevOppMove = gameMove(curr_row, curr_col, dest_row, dest_col, true);
        }
        cannon.executeMove(temp);
        if (info[1]==8){
            gameMove comp = gameMove(0, 2, 3, 2, false);
            if (temp.compareMove(comp)){
                cout << "S 5 0 M 6 1" << endl;
                temp = gameMove(7, 5, 6, 6, false);
                cannon.executeMove(temp);
            }else{
                cout << "S 3 0 M 2 1" << endl;
                temp = gameMove(7, 3, 6, 2, false);
                cannon.executeMove(temp);
            }
            cin >> move;
            cin >> curr_col;
            cin >> curr_row;
            curr_row = info[1] - 1 - curr_row;
            cin >> move;
            cin >> dest_col;
            cin >> dest_row;
            t1 = std::chrono::high_resolution_clock::now();
            dest_row = info[1] - 1 - dest_row;
            if (move == 'M'){
                temp = gameMove(curr_row, curr_col, dest_row, dest_col, false);
                prevOppMove = gameMove(curr_row, curr_col, dest_row, dest_col, false);
            }else{
                temp = gameMove(curr_row, curr_col, dest_row, dest_col, true);
                prevOppMove = gameMove(curr_row, curr_col, dest_row, dest_col, true);
            }
            cannon.executeMove(temp);
        }
    }
    if (info[0]==2 && info[1]==8){
        cout << "S 2 7 M 1 6" << endl;
        temp = gameMove(0, 2, 1, 1, false);
        prevMyMove = gameMove(1, 1, 0, 2, false);
        cannon.executeMove(temp);
        char move;
        int curr_row, curr_col, dest_row, dest_col;
        //x = col, y = rows-1-row
        cin >> move;
        cin >> curr_col;
        cin >> curr_row;
        curr_row = info[1] - 1 - curr_row;
        cin >> move;
        cin >> dest_col;
        cin >> dest_row;
        t1 = std::chrono::high_resolution_clock::now();
        dest_row = info[1] - 1 - dest_row;
        if (move == 'M'){
            temp = gameMove(curr_row, curr_col, dest_row, dest_col, false);
            gameMove(curr_row, curr_col, dest_row, dest_col, false);
        }else{
            temp = gameMove(curr_row, curr_col, dest_row, dest_col, true);
            gameMove(curr_row, curr_col, dest_row, dest_col, true);
        }
        cannon.executeMove(temp);
    }
    int negationCount = 0;
    while (true) {
        gameMove misc = gameMove(-2, -2, -2, -2, false);
        if(compareOpp || negationCount >= 1){
            misc = (prevMyMove.getNegation(prevMyMove));
//            cout << "prev move: ";
//            prevMyMove.printMove(info[1]);
//            cout << "neg move: ";
//            misc.printMove(info[1]);
        }
        
        temp = cannon.minimax(depth, time_span, misc);
        if(temp.isNegation(prevMyMove))
            negationCount++;
        else
            negationCount = 0;
        prevMyMove.make(temp);
        if (temp.curr_row == -1){
            ScoreAndMoves moves = cannon.getValidMoves();
            bool success = false;
            while (!success){
                int random = (rand() % 7);
                int size = (int)moves.Posmoves[random].size();
                if (size!=0){
                    int random1 = (rand() % size);
                    temp = moves.Posmoves[random][random1];
                    success = true;
                }
            }
            temp.printMove(info[1]);
        }else{
            temp.printMove(info[1]);
        }
        t2 = std::chrono::high_resolution_clock::now();
//        cout << "depth: " << 8 << ", " << "time: " << (std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()) << endl;
        MyMoves++;
        cannon.timeRemaining = cannon.timeRemaining - (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count());
//        if (count%3 == 0){
            time_span = (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count());
//        }
//        cout << time_span << endl;
        if (time_span * (MinMoves - MyMoves) > cannon.timeRemaining){
            if (depth > min_depth){
                depth--;
            }
        }else if (time_span * (MinMoves - MyMoves) * mul_factor < cannon.timeRemaining ){
            if (depth < max_depth){
                depth++;
            }
        }
//        cout << (t2 - t1) << endl;
        cannon.executeMove(temp);
        char move;
        int curr_row, curr_col, dest_row, dest_col;
        //x = col, y = rows-1-row
        cin >> move;
        cin >> curr_col;
        cin >> curr_row;
        curr_row = info[1] - 1 - curr_row;
        cin >> move;
        cin >> dest_col;
        cin >> dest_row;
        t1 = std::chrono::high_resolution_clock::now();
        dest_row = info[1] - 1 - dest_row;
        if (move == 'M'){
            temp = gameMove(curr_row, curr_col, dest_row, dest_col, false);
            compareOpp = temp.isNegation(prevOppMove);
            prevOppMove = gameMove(curr_row, curr_col, dest_row, dest_col, false);
        }else{
            temp = gameMove(curr_row, curr_col, dest_row, dest_col, true);
            compareOpp = temp.isNegation(prevOppMove);
            prevOppMove = gameMove(curr_row, curr_col, dest_row, dest_col, true);
        }
//        cout << compareOpp << endl;
        cannon.executeMove(temp);
//        prevOppMove.printMove(info[1]);
    }
    return 0;
}
