#include <iostream>
#include <cstdio>

#include "GameBoard.hpp"

GameBoard::~GameBoard(){
	for(int i=0; i< players.size(); i++)
		delete players[i];
}

void GameBoard::initializeGameBoard(int no_players){
	for(int i=0; i< no_players; i++)
		players.push_back(new Player());

		printGameStatistics();
}

void GameBoard::printGameStatistics(){
	for(int i=0; i< players.size(); i++){
		cout<< "PLAYER #"<< i<< endl;
		players[i]->printGameStatistics();
		cout<< endl;
	}
}

int GameBoard::checkWinningCondition(){
	int flag= 0, winner= 0;
	for(int i=0; i< players.size(); i++){
		if(players[i]->give_no_provinces()== 0)
			continue;
		else{
			flag++;
			winner= i;
		}
	}
	if(flag== 1) return winner;
	else return -1;
}

void GameBoard::gameplay(){
	int winner= -1;

	while(1){ //Rounds until winner is found
		cout<< "STARTING PHASE"<< endl;

		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;
			cout<< "PLAYER'S #"<< i<< " TURN"<< endl;
			players[i]->startingPhase();
		}

		cout<< "EQUIPMENT PHASE"<< endl;
		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;
			cout<< "PLAYER'S #"<< i<< " TURN"<< endl;
			players[i]->equipPhase();
		}

		cout<< "BATTLE PHASE"<< endl;
		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;
			cout<< "PLAYER'S #"<< i<< " TURN"<< endl;
				cout<< "Defense or Battle? [Type D/B]: ";
			int c= getchar();
			while(c!= 'D' || c!= "B"){
				cout<< "\nWrong character! Please type D or B: ";
				c= getchar();
			}
			putchar(c);
				if(c== 'D')
				players[i]->battlePhase(NULL);
			else{
				cout<< "\nWhich Player do you want to battle?"<< endl<<
					"Number of Players in the game: "<< players.size()<< endl<<
					"Type a number from 0 to "<< players.size()-1<< ": ";
					c= getchar();
				while(c>= players.size()-1 && c<= 0){
					cout<< "\nWrong number! Please type a number from 0 to "<< players.size()-1<< ":";
					c= getchar();
				}
				putchar(c);
				players[i]->battlePhase(&players[c]);
			} 
				
		}

		cout<< "ECONOMY PHASE"<< endl;
		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;
			cout<< "PLAYER'S #"<< i<< " TURN"<< endl;
			players[i]->economyPhase();
		}
			cout<< "FINAL PHASE"<< endl;
		for(int i=0; i< players.size(); i++){
				if(players[i]->give_no_provinces()== 0)
				continue;
			cout<< "PLAYER'S #"<< i<< " TURN"<< endl;
			players[i]->finalPhase();
		}
			winner= checkWinningCondition();
			if(winner> 0){
		cout<< "PLAYER #"<< winner<< " IS THE WINNER!"<< endl;
			break;
		}
	}
}