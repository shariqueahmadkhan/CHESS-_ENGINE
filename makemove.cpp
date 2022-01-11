#include<bits/stdc++.h>
using namespace std;

class makemove:public movegen{
    public:
    vector<int> CastleData ={ 
    13, 15, 15, 15, 12, 15, 15, 14,0,0,
    15, 15, 15, 15, 15, 15, 15, 15,0,0,
    15, 15, 15, 15, 15, 15, 15, 15,0,0,
    15, 15, 15, 15, 15, 15, 15, 15,0,0,
    15, 15, 15, 15, 15, 15, 15, 15,0,0,
    15, 15, 15, 15, 15, 15, 15, 15,0,0,
    15, 15, 15, 15, 15, 15, 15, 15,0,0,
     7, 15, 15, 15,  3, 15, 15, 11,0,0};
    string PrevFen="";
    bool execmove(int move);
    void validMove(string mov);
    void TakeMove(int move);
    void generateFen();
    bool IsCheckMate();
};
bool makemove::IsCheckMate(){
    GenerateAllMoves();
    for(int i=0;i<movelist.size();i++){
        if(execmove(movelist[i])){
            ParseFEN(PrevFen);
            return false;
        }
    }
    movelist.clear();
    return true;
}
void makemove::validMove(string mov){
    char prompce;
    int move=0, tempPce=EMPTY;
    int sidedir[]={1,-1};
    move=(move^(mov[0]-'a'));
    move=((move)^((mov[1]-'1')<<3));
    move=((move)^((mov[2]-'a')<<6));
    move=((move)^((mov[3]-'1')<<9));
    if((Brd[mov[1]-'1'][mov[0]-'a'] == wP && (mov[3]-'1' == 7)) 
    || Brd[mov[1]-'1'][mov[0]-'a'] == bP && (mov[3]-'1' == 1)){
        cout<<"\nEnter Promoted Piece: ";
        cin>>prompce;
        switch(prompce){
            case 'n':   tempPce = 8;
                        break;
            case 'b':   tempPce = 9;
                        break;
            case 'r':   tempPce = 10;
                        break;
            case 'q':   tempPce = 11;
                        break;
            case 'N':   tempPce = 2;
                        break;
            case 'B':   tempPce = 3;
                        break;
            case 'R':   tempPce = 4;
                        break;
            case 'Q':   tempPce = 5;
                        break;
            default:  cout<<"\nInvalid Piece Type";
                        return;
        }

    }
    move=((move)^(tempPce<<12));
    int tempmove;
    for(int i=0;i<movelist.size();i++){
        tempmove=movelist[i] & 0xffff;
        if(tempmove==move){
            if(!execmove(movelist[i]))
                cout<<"\nInvalid Move, King is attacked!!";
            PrintBoard();    
            movelist.clear();
            return;
        }
    }
    movelist.clear();
    cout<<"\nInvalid Move\n";
    PrintBoard();
    return;
}
bool makemove::execmove(int move){
    generateFen();
    int ff =((move) & 7);
    int fr = ((move>>3)&7); 
    int tf = ((move>>6)&7);
    int tr = ((move>>9)&7);
    int pr = ((move>>12)&15);
    int ep = ((move>>16)&1);
    int cast = ((move>>17)&1);
    int sidedir[] = {1,-1};
    int pce = Brd[fr][ff];
    FiftyMoves++;
    TotalMoves++;
    if(cast==1){
        ClearPiece(fr,ff);
        AddPiece(pce,tr,tf);
        if((tr*10+tf)==2){
            ClearPiece(0,0);
            AddPiece(wR,0,3);
        }else if((tr*10+tf)==6){
            ClearPiece(0,7);
            AddPiece(wR,0,5);
        }else if((tr*10+tf)==72){
            ClearPiece(7,0);
            AddPiece(bR,7,3);
        }else if((tr*10+tf)==76){
            ClearPiece(7,7);
            AddPiece(bR,7,5);
        }
    }
    else if(pr!= 0){
        if(Brd[tr][tf]!= EMPTY){
            ClearPiece(tr,tf);
        }
        ClearPiece(fr,ff);
        AddPiece(pr,tr,tf);
        FiftyMoves = 0;
    }
    else if(ep==1){
        ClearPiece((EnPassant - sidedir[side]*10)/10,EnPassant%10);
        ClearPiece(fr,ff);
        AddPiece(pce,tr,tf);
        FiftyMoves=0;
    }
    else{
        if(Brd[tr][tf]!= EMPTY){
            ClearPiece(tr,tf);
            FiftyMoves = 0;
        }
        if(Brd[fr][ff] == wP || Brd[fr][ff] == bP){
            FiftyMoves = 0;
        }
        ClearPiece(fr,ff);
        AddPiece(pce,tr,tf);
    }
    CastlePerm= CastlePerm & CastleData[(fr*10+ff)];
    CastlePerm= CastlePerm & CastleData[(tr*10+tf)];
    EnPassant = OFFBOARD;
    if((pce == wP && tr== fr + 2 && fr == 1) || (pce == bP && tr == fr - 2 && fr == 6)){
        EnPassant = (tr - sidedir[side])*10 + tf;
        FiftyMoves = 0;
    }
    
    if(SqAttacked(PList[(side*6)+6][0])){
        ParseFEN(PrevFen);
        return false;
    }
    side^=1;
    return true;
}

void makemove::generateFen(){
    PrevFen="";
    int j=0;
    for(int m=7;m>=0;m--){
        j=0;
        for(int n=0;n<8;n++){
            switch(Brd[m][n]){
                case wP: if(j!=0)
                        PrevFen+=to_string(j);
                        PrevFen+="P";j=0;break;
                case wN: if(j!=0)
                        PrevFen+=to_string(j);
                        PrevFen+="N";j=0;break;
                case wB: if(j!=0)
                        PrevFen+=to_string(j);
                        PrevFen+="B";j=0;break;
                case wR: if(j!=0)
                        PrevFen+=to_string(j);
                        PrevFen+="R";j=0;break;
                case wQ: if(j!=0)
                        PrevFen+=to_string(j);
                        PrevFen+="Q";j=0;break;
                case wK: if(j!=0)
                        PrevFen+=to_string(j);
                        PrevFen+="K";j=0;break;
                case bP: if(j!=0)
                        PrevFen+=to_string(j);
                        PrevFen+="p";j=0;break;
                case bN: if(j!=0)
                        PrevFen+=to_string(j);
                        PrevFen+="n";j=0;break; 
                case bB: if(j!=0)
                        PrevFen+=to_string(j);
                        PrevFen+="b";j=0;break;
                case bR: if(j!=0)
                        PrevFen+=to_string(j);
                        PrevFen+="r";j=0;break;
                case bQ: if(j!=0)
                        PrevFen+=to_string(j);
                        PrevFen+="q";j=0;break;
                case bK: if(j!=0)
                        PrevFen+=to_string(j);
                        PrevFen+="k";j=0;break;
                default: j++;
            }
        }
        if(j!=0)
        PrevFen+=to_string(j);
        if(m!=0)
        PrevFen+="/";
    }
    PrevFen+=" ";
    if(side==0){
        PrevFen+="w";
    }
    else{
        PrevFen+="b";
    }
    PrevFen+=" ";
    if((CastlePerm & 1) == 1)
    PrevFen+="K";
    if((CastlePerm & 2) == 2)
    PrevFen+="Q";
    if((CastlePerm & 4) == 4)
    PrevFen+="k";
    if((CastlePerm & 8) == 8)
    PrevFen+="q";
    if((CastlePerm & 15) == 0)
    PrevFen+="-";
    PrevFen+=" ";
    if(EnPassant!=OFFBOARD){
        PrevFen+=files[EnPassant%10];
        PrevFen+=ranks[EnPassant/10];
    }
    else{
        PrevFen+="-";
    }
    PrevFen+=" ";
    PrevFen+=to_string(FiftyMoves);
    PrevFen+=" ";
    PrevFen+=to_string(TotalMoves);
}