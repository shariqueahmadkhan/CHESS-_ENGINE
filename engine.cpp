#include<bits/stdc++.h>
#include "board.cpp"
#include "movegen.cpp"
#include "makemove.cpp"


string DefaultFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
using namespace std;
int main(){
    makemove m;
    m.ParseFEN(DefaultFen);
    m.PrintBoard();
    int n=0;

    while(n!=3){
        if(m.Check_FM()){
            cout<<"\nGame Drawn";
            break;
        }
        if(m.IsCheckMate()){
            cout<<"\nGame Over";
            break;
        }
        string fen;
        string mov;
        cout<<"\n1. fen\n2. move\n3. exit\nEnter choice:";
        cin>>n;
        switch(n){
            case 1: cout<<"Enter FEN: ";
                    getchar();
                    getline(cin, fen,'\n');
                    m.ParseFEN(fen);break;
            case 2: cout<<"Enter move: ";
                    cin>>mov;
                    m.validMove(mov);break;
            case 3: break;
            default: cout<<"Invalid choice";
        }
        cin.clear();
    }
}