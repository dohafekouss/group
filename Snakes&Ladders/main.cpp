#include<iostream>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
using namespace std;

void line();
void visual(char board[100],int player1,int player2);
int play(char board[100], int player, char playername[50]) {
    int dice=(rand()) % 6 + 1;
    string enter;
    cout<<"\n"<<playername<<", press any key to continue.";
    cin >>enter;
    line();
    cout<<"\n\nYou rolled: "<<dice<<"\n";
    player += dice;
    if (int(board[player-1])>0&&player<100){
        cout << "\nGreat!! You got a ladder going up "<<int(board[player-1]);
        player += board[player-1];
        cout << "\nYour new position is " <<player<<".";
        //cout<<endl;
    } else if (int(board[player-1])<0&&player<100){
        //line();
        cout << "\nOops!! Snake found going down "<<int(board[player-1]);
        player += board[player-1];
        cout <<"\nYour new position is " << player<<".";
        cout<<endl;
    } else if (int(board[player-1])==0&&player<100){
        //line();
        cout << "Your new position is " << player<<".";
        cout<<endl;

    }
    cout << "\n";
    cout<<endl;
    return player;
}
int main() {
    char board[100] = {
            0,  0,  0, 0,  0,  40,  0,  0, 0,  0,
            0,  0,  0,  0,  0,  0,0,  0,  24, 0,
            0,  0,  0,  0,  0,  0,  0, 0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
            0,  0,  0,0,  0,  0,  -38,  0,  0,  0,
            0,19, 0, 0,  0,  0,  41,  0,  0,  0,
            0,  -22,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,0,  0,0,  -21,  0,  0,0,  0
    };

    int player1 = 1, player2 = 1;
    char player1name[50], player2name[50];
    line();
    cout << "\n\n\t\tSNAKES AND LADDERS\n\n";
    line();
    cout << "\nEnter Name of player 1: ";
    cin>>player1name;
    cout << "\nEnter Name of player 2: ";
    cin>>player2name;
    line();
    cout<<endl;
    while (player1 < 100 && player2 < 100) {
        player1= play(board, player1, player1name);
        if (player1>99){
            player1=100;
            cout<<"Congratulations!! "<<player1name<<" is the winner!!"<<"\n"<<endl;
            visual(board,player1,player2);

            cout<<"\n"<<player1name<<"'s Position: "<<player1;
            cout<<"\n"<<player2name<<"'s Position: "<<player2;
            break;
        }
        visual(board,player1,player2);

        cout<<"\n"<<player1name<<"'s Position: "<<player1;
        cout<<"\n"<<player2name<<"'s Position: "<<player2;

        player2= play(board, player2, player2name);
        if (player2>99){
            player2=100;
            cout<<"Congratulations!! "<<player2name<<" is the winner!!"<<"\n"<<endl;
            visual(board,player1,player2);
            cout<<"\n"<<player1name<<"'s Position: "<<player1;
            cout<<"\n"<<player2name<<"'s Position: "<<player2;
            break;
        }
        visual(board,player1,player2);

        cout<<"\n"<<player1name<<"'s Position: "<<player1;
        cout<<"\n"<<player2name<<"'s Position: "<<player2;
    }
}
void line(){
    int n=50;
    char ch='-';
    for (int i = 0; i < n; i++)
        cout << ch;
}
void visual(char board[100],int player1, int player2){
    int count =1;
    for (int i=1;i<=100;i++){
        int a = int(board[i]);
        a = count;
        count++;
        if (a==player1||a==player2){
            cout<<'X';
        }
        cout<<a<<"\t";

        if (a%10==0){
            cout<<"\n";
        }
        if (board[i]<0){
            cout<<'S';
        }
        if(board[i]>0){
            cout<<'L';
        }
    }
}
