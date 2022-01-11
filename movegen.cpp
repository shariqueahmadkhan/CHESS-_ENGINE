#include<bits/stdc++.h>
using namespace std;
  

class movegen: public board{
    protected:
    vector<int> kingMov= {-1,1,-10,10,9,11,-9,-11};         //stores the value for which the king can move on the board.
    vector<int> queenMov= {1,-1,10,-10,-9, -11, 9 , 11};    //stores the value for which the Queen can move on the board.
    vector<int> bishopMov= {-9, -11, 9 , 11};               //stores the value for which the Bishop can move on the board.
    vector<int> rookMov = { 10,-10, 1,-1};                  //stores the value for which the Rook can move on the board.
    vector<int> knightMov = {8,-8,12,-12,19,-19,21,-21};    //stores the value for which the Knight can move on the board.

    vector<int> movelist;                                       // stores the indexes from and to for all available moves. 
    public:
    
    bool SqAttacked(int sq);
    void PawnMov();
    void KingMov();
    void KnightMov();
    void RookMov();
    void BishopMov();
    void QueenMov();
    void CastleMov();
    void PrintMoveList();
    void createmove(int fc,int fr, int tc, int tr, int pp, int ep,int castle);
    void GenerateAllMoves();
};
void movegen::GenerateAllMoves(){
    PawnMov();
    KingMov();
    KnightMov();
    RookMov();
    BishopMov();
    QueenMov();
    CastleMov();
}

void movegen::createmove(int fc,int fr, int tc, int tr, int pp, int ep,int cs){
            int move=0;
            move = move^fc;
            move = move^(fr<<3);
            move = move^(tc)<<6;
            move = move^(tr<<9);
            move = move^(pp<<12);
            move = move^(ep<<16);
            move = move^(cs<<17);
            movelist.push_back(move);
}
bool movegen::SqAttacked(int sq){
    //King
    for(int i=0;i<8;i++){
        int tsq=sq+kingMov[i];
        int f=tsq%10;
        int r=tsq/10;
        if(f>=0 && f<=7 && r>=0 && r<=7){
            if(side==0){
                if(Brd[r][f]==bK){
                    return true;
                }
            }else{
                if(Brd[r][f]==wK){
                    return true;
                }
            }
        }
    }
    // Queen
    for(int i=0;i<8;i++){
        int tsq=sq+queenMov[i];
        int f=tsq%10;
        int r=tsq/10;
        while(f>=0 && f<=7 && r>=0 && r<=7){
            if(side==0){
                if(Brd[r][f]==bQ){
                    return true;
                }
            }else{
                if(Brd[r][f]==wQ){
                    return true;
                }
            }
            if(Brd[r][f]!=EMPTY){
                break;
            }
            tsq=tsq+queenMov[i];
            f=tsq%10;
            r=tsq/10;
        }
    }
    // Rook
    for(int i=0;i<4;i++){
        int tsq=sq+rookMov[i];
        int f=tsq%10;
        int r=tsq/10;
        while(f>=0 && f<=7 && r>=0 && r<=7){
            if(side==0){
                if(Brd[r][f]==bR){
                    return true;
                }
            }else{
                if(Brd[r][f]==wR){
                    return true;
                }
            }
            if(Brd[r][f]!=EMPTY){
                break;
            }
            tsq=tsq+rookMov[i];
            f=tsq%10;
            r=tsq/10;
        }
    }
    // Bishop
    for(int i=0;i<4;i++){
        int tsq=sq+bishopMov[i];
        int f=tsq%10;
        int r=tsq/10;
        while(f>=0 && f<=7 && r>=0 && r<=7){
            if(side==0){
                if(Brd[r][f]==bB){
                    return true;
                }
            }else{
                if(Brd[r][f]==wB){
                    return true;
                }
            }
            if(Brd[r][f]!=EMPTY){
                break;
            }
            tsq=tsq+bishopMov[i];
            f=tsq%10;
            r=tsq/10;
        }
    }
    // knight
    for(int i=0;i<8;i++){
        int tsq=sq+knightMov[i];
        int f=tsq%10;
        int r=tsq/10;
        if(f>=0 && f<=7 && r>=0 && r<=7){
            if(side==0){
                if(Brd[r][f]==bN){
                    return true;
                }
            }else{
                if(Brd[r][f]==wN){
                    return true;
                }
            }
        }
    }
    //Pawn
    if(side==0){
        int tsq=sq+9;
        int f=tsq%10;
        int r=tsq/10;
        if(f>=0 && f<=7 && r>=0 && r<=7){
            if(Brd[r][f]==bP){
                return true;
            }
        }
        tsq=sq+11;
        f=tsq%10;
        r=tsq/10;
        if(f>=0 && f<=7 && r>=0 && r<=7){
            if(Brd[r][f]==bP){
                return true;
            }
        }
    }
    else{
        int tsq=sq-9;
        int f=tsq%10;
        int r=tsq/10;
        if(f>=0 && f<=7 && r>=0 && r<=7){
            if(Brd[r][f]==wP){
                return true;
            }
        }
        tsq=sq-11;
        f=tsq%10;
        r=tsq/10;
        if(f>=0 && f<=7 && r>=0 && r<=7){
            if(Brd[r][f]==wP){
                return true;
            }
        }
    }
    return false;
}

void movegen::PawnMov(){
    int move = 0;
    int pawnside = side*6 + 1;
    int oppside[] = {1,0};
    int sidemove[] = {1,-1};
    for(int i = 0; i<PieceNum[pawnside]; i++){
        int sq = PList[pawnside][i];
        int rank = sq/10;
        int column = sq%10;
        if(Brd[rank+ sidemove[side]][column] == EMPTY){
            //promotion
            if(rank == ((side+1)%2)*5 + 1){
                 for(int i = 1;i<=4;i++){
                     createmove(column,rank,column,rank+sidemove[side],pawnside+i,0,0);
                 }
            }
            //normal move
            else createmove(column,rank,column,rank+sidemove[side],0,0,0);
            //pawn Start
            if(rank == side*5 + 1 && Brd[rank+sidemove[side]*2][column] == EMPTY){
                createmove(column,rank,column,rank+sidemove[side]*2,0,0,0);
            }
        }
        int rd = rank + sidemove[side];
        int cdl = column + sidemove[side];
        int cdr = column - sidemove[side];
        //enPassant
        if(EnPassant != OFFBOARD && (EnPassant == sidemove[side]*9 + sq || EnPassant == sidemove[side]*11 + sq)){
            createmove(column,rank,(EnPassant%10),(EnPassant/10),0,1,0);
        }
        // capture moves
        //left side
        if(cdl>-1 && cdl<8 && Brd[rd][cdl] > oppside[side]*6 && Brd[rd][cdl] < oppside[side]*6+7){
            if(rank == ((side+1)%2)*5 + 1){
                 for(int i = 1;i<=4;i++){
                     createmove(column,rank,cdl,rd,pawnside+i,0,0);
                 }
            }
            else createmove(column,rank,cdl,rd,0,0,0);
        }
        //right side
        if(cdr>-1 && cdr<8 && Brd[rd][cdr] > oppside[side]*6 && Brd[rd][cdr] < oppside[side]*6+7){
            if(rank == ((side+1)%2)*5 + 1){
                 for(int i = 1;i<=4;i++){
                     createmove(column,rank,cdr,rd,pawnside+i,0,0);
                 }
            }
            else createmove(column,rank,cdr,rd,0,0,0);
        }
    }
}

void movegen::KingMov(){
    int sq = PList[side*6 + 6][0];
    int rank = sq/10;
    int file = sq %10;
    int oppside[] = {1,0};
    for(int i = 0;i<8;i++){
        int tsq = sq + kingMov[i];
        int trank = tsq/10;
        int tfile = tsq%10;  
        if(trank>-1 && trank<8 && tfile>-1 && tfile<8 
                && (Brd[trank][tfile]== EMPTY 
                || (Brd[trank][tfile] > oppside[side]*6 
                && Brd[trank][tfile] < oppside[side]*6 +7)) 
                && !SqAttacked(tsq)){
            createmove(file,rank,tfile,trank,0,0,0);
        }
    }
}

void movegen::CastleMov(){
    int sq = PList[side*6 + 6][0];
    int rank = sq/10;
    int file = sq %10;
    int oppside[] = {1,0};
    if(side==WHITE && !SqAttacked(PList[wK][0])){
        if(((CastlePerm & 1 )== 1) && Brd[0][5] == EMPTY && Brd[0][6] == EMPTY && !SqAttacked(5) && !SqAttacked(6)){
            createmove(file,rank,6,0,0,0,1);
        }
        if(((CastlePerm & 2)==2) && Brd[0][1] == EMPTY && Brd[0][2] == EMPTY && Brd[0][3] == EMPTY && !SqAttacked(2) && !SqAttacked(3)){
            createmove(file,rank,2,0,0,0,1);
        }
    }else if(side == BLACK  && !SqAttacked(PList[bK][0])){
        if(((CastlePerm & 4 )== 4 ) && Brd[7][5] == EMPTY && Brd[7][6] == EMPTY && !SqAttacked(75) && !SqAttacked(76)){
            createmove(file,rank,6,7,0,0,1);
        }
        if(((CastlePerm & 8) == 8) && Brd[7][2] == EMPTY && Brd[7][3] == EMPTY && Brd[7][1] == EMPTY && !SqAttacked(72) && !SqAttacked(73)){
            createmove(file,rank,2,7,0,0,1);
        }
    }
}

void movegen::PrintMoveList(){
    for(int i = 0 ; i<movelist.size(); i++ ){
        int temp=movelist[i];
        cout<<"\nfrom: "<<files[(temp & 7)]<<((temp>>3)&7)+1
        <<"\nTo: "<<files[((temp>>6)&7)]<<((temp>>9)&7)+1
        <<"\nProm: "<<((temp>>12)&15)
        <<"\nEP: "<<((temp>>16)&1)
        <<"\ncast: "<<((temp>>17)&1)
        <<endl;
    }
}

void movegen::KnightMov(){
    int oppside[] = {1,0};
    for(int j=0;j<PieceNum[side*6+2];j++){
        for(int i=0; i<8;i++){
            int sq=PList[side*6+2][j];
            int tsq=sq+knightMov[i];
            int f=tsq%10;
            int r=tsq/10;
            if(f>=0 && f<=7 && r>=0 && r<=7){
                if(Brd[r][f]==EMPTY 
                || (Brd[r][f] > oppside[side]*6 
                && Brd[r][f] < oppside[side]*6 +7)){
                    createmove(sq%10,sq/10,f,r,0,0,0);
                } 
            }
        }
    }
}

void movegen::RookMov(){
    int tsq;
    int r;
    int f;
    int oppside[] = {1,0};
    for(int j=0;j<PieceNum[side*6+4];j++){
        for(int i=0; i<4;i++){
            int sq=PList[side*6+4][j]; 
            tsq=sq+rookMov[i];
            f=tsq%10;
            r=tsq/10;
            while(f>=0 && f<=7 && r>=0 && r<=7){
                if(Brd[r][f] == EMPTY)
                    createmove(sq%10,sq/10,f,r,0,0,0);
                else if(Brd[r][f] > oppside[side]*6 && Brd[r][f] < oppside[side]*6 +7){
                    createmove(sq%10,sq/10,f,r,0,0,0);
                    break;
                    }
                else break;
                
                tsq=tsq+rookMov[i];
                f=tsq%10;
                r=tsq/10;
            }
        }
    }
}

void movegen::BishopMov(){
    int oppside[] = {1,0};
    for(int j=0;j<PieceNum[side*6+3];j++){
        for(int i=0;i<4;i++){
            int sq=PList[side*6+3][j];
            int tsq=sq+bishopMov[i];
            int f=tsq%10;
            int r=tsq/10;
            while(f>=0 && f<=7 && r>=0 && r<=7){
                if(Brd[r][f]==EMPTY){
                    createmove(sq%10,sq/10,f,r,0,0,0);
                }
                else if(Brd[r][f] > oppside[side]*6 
                && Brd[r][f] < oppside[side]*6 +7){
                    createmove(sq%10,sq/10,f,r,0,0,0);
                    break;
                }
                else break;
                tsq=tsq+bishopMov[i];
                f=tsq%10;
                r=tsq/10;
            }
        }
    }
}

void movegen::QueenMov(){
    int oppside[] = {1,0};
    for(int j=0;j<PieceNum[side*6+5];j++){
        for(int i=0;i<8;i++){
            int sq=PList[side*6+5][j];
            int tsq=sq+queenMov[i];
            int f=tsq%10;
            int r=tsq/10;
            while(f>=0 && f<=7 && r>=0 && r<=7){
                if(Brd[r][f]==EMPTY){
                    createmove(sq%10,sq/10,f,r,0,0,0);
                }
                else if(Brd[r][f] > oppside[side]*6 
                && Brd[r][f] < oppside[side]*6 +7){
                    createmove(sq%10,sq/10,f,r,0,0,0);
                    break;
                }
                else break;
                tsq=tsq+queenMov[i];
                f=tsq%10;
                r=tsq/10;
            }
        }
    }
}