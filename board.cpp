#include<bits/stdc++.h>
#define OFFBOARD 100
using namespace std;
enum {WHITE=0,BLACK=1};
enum {EMPTY=0,wP=1,wN=2,wB=3,wR=4,wQ=5,wK=6,bP=7,bN=8,bB=9,bR=10,bQ=11,bK=12};
enum {A=0,B=1,C=2,D=3,E=4,F=5,G=6,H=7};
string files= "abcdefgh";
string ranks= "12345678";
int PceVal[13] = { 0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000};
class board{
    protected:
    //data members
    int Brd[8][8]; //stores piece type in each block
    int PList[13][10]; //stores index of board for each piece type
    int CastlePerm; //Store WKCA=1, WQCA=2, BKCA=4, BQCA=8 according to available castling 
    int EnPassant; //Stores index of block Where enPassant move is available
    int side ;  //side to move 
    int Material[2]; //stores total piece value for each side
    int PieceNum[13]; //stores no of piece of each type 
    int FiftyMoves;
    int TotalMoves;
    public:
    //Function members
    void SetBoard();
    void ParseFEN(string fen);
    void AddPiece(int pce, int rank, int file);
    void ClearPiece(int rank,int file);
    void UpdateMaterial();
    void PrintBoard();
    bool Check_FM();

};
bool board::Check_FM(){
    if(FiftyMoves==50){
        return true;
    }
    return false;
}
void board::SetBoard(){
    for(int i=0;i<13;i++){
        PieceNum[i]=0;
        PList[i][0]=OFFBOARD;
    }
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            Brd[i][j]=0;
        }
    }
    CastlePerm=0; 
    EnPassant=OFFBOARD; 
    side=OFFBOARD;  
    Material[0]=0;
    Material[1]=0;
    FiftyMoves=0;
    TotalMoves=0;
}
void board::ParseFEN(string fen){
    int rank= 7,file = 0, i;

    SetBoard();
    for(i = 0; fen[i] != ' '; i++){
        switch(fen[i]){
            case 'p':   AddPiece(bP, rank, file); 
                        break;
            case 'n':   AddPiece(bN, rank, file); 
                        break;
            case 'b':   AddPiece(bB, rank, file); 
                        break;
            case 'r':   AddPiece(bR, rank, file); 
                        break;
            case 'q':   AddPiece(bQ, rank, file); 
                        break;
            case 'k':   AddPiece(bK, rank, file); 
                        break;
            case 'P':   AddPiece(wP, rank, file); 
                        break;
            case 'N':   AddPiece(wN, rank, file); 
                        break;
            case 'B':   AddPiece(wB, rank, file); 
                        break;
            case 'R':   AddPiece(wR, rank, file); 
                        break;
            case 'Q':   AddPiece(wQ, rank, file); 
                        break;
            case 'K':   AddPiece(wK, rank, file); 
                        break;
            case '/':   rank = rank - 1;
                        file = 0;
                        continue;
        }
        if(fen[i] >= '1' && fen[i] <= '8'){
            file += fen[i] - '0';
        }
        else file++;
    }
    if(fen[++i] == 'w') side = WHITE;
    else side = BLACK;
    
    i+=2;
    if(fen[i]!= '-'){
        for(; fen[i] != ' '; i++){
            switch(fen[i]){
                case 'K':   CastlePerm^=1;
                            break;
                case 'Q':   CastlePerm^=2;
                            break;
                case 'k':   CastlePerm^=4;
                            break;
                case 'q':   CastlePerm^=8;
                            break;
                default: cout<<"\ninvalid FEN\n";
            }
        }
    }
    else{
        i++;
    }
    
    if(fen[++i]!= '-'){
        EnPassant = (fen[i] - 'a');
        EnPassant += ((fen[++i] - '1')*10);  
    }
    
    i+=2;
    FiftyMoves = fen[i]-'0';
    if(fen[i+1]!=' ') FiftyMoves = FiftyMoves*10+ fen[++i] - '0';

    i+=2;
    
    TotalMoves = fen[i]-'0';
    if(fen[i+1]!='\0') TotalMoves = TotalMoves*10+ fen[++i] - '0';
    if(fen[i+1]!='\0') TotalMoves = TotalMoves*10+ fen[++i] - '0';
    

}

void board::AddPiece(int pce, int rank, int file){
    int sq = rank*10 + file;
    Brd[rank][file] = pce;
    PList[pce][PieceNum[pce]] = sq;
    PList[pce][++PieceNum[pce]] = OFFBOARD;
    if(pce>=0 && pce<=6){
        Material[0] += PceVal[pce];
    }
    else  Material[1] += PceVal[pce];
}
void board::ClearPiece(int rank, int file){
    int pce = Brd[rank][file];
    int sq = rank *10 + file;
    for(int i = 0; i<PieceNum[pce] ; i++){
        if(PList[pce][i] == sq){
            Brd[rank][file] = EMPTY;
            PList[pce][i] = PList[pce][PieceNum[pce]-1];
            PList[pce][PieceNum[pce]-1] = OFFBOARD;
            PieceNum[pce]--;
            if(pce>=0 && pce<=6){
                Material[0] -= PceVal[pce];
            }
            else  Material[1] -= PceVal[pce];
            return;
        }
    }
}

void board::PrintBoard(){
    int temp=0;
    cout<<"\n";
    for(int i=7;i>=0;i--){
        for(int j=0;j<8;j++){
            if(j==0){ 
                cout<<i+1<<"\t";
            }
            temp=Brd[i][j];
            switch(temp){
                case EMPTY: cout<<".\t";break;
                case wP: cout<<"P\t";break;
                case wN: cout<<"N\t";break;
                case wB: cout<<"B\t";break;
                case wR: cout<<"R\t";break;
                case wQ: cout<<"Q\t";break;
                case wK: cout<<"K\t";break;
                case bP: cout<<"p\t";break;
                case bN: cout<<"n\t";break;
                case bB: cout<<"b\t";break;
                case bR: cout<<"r\t";break;
                case bQ: cout<<"q\t";break;
                case bK: cout<<"k\t";break;
            }
        }
        cout<<"\n\n";
    }
    cout<<"\tA\tB\tC\tD\tE\tF\tG\tH\n";
    cout<<"\n\nside:"<< side <<endl;
    cout<<"\nenpassant:";
    if(EnPassant != OFFBOARD){
      cout<<files[EnPassant%10]<<EnPassant/10+1;
    }
    cout<<"\nCastle Available:"<<    
        ((CastlePerm & 1) ? 'K' : '-')<<
        ((CastlePerm & 2) ? 'Q' : '-')<<
        ((CastlePerm & 4)? 'k' : '-')<<
        ((CastlePerm & 8) ? 'q' : '-');
    cout<<"\nTotal Moves:"<<TotalMoves;
    cout<<"\nFifty Moves:"<<FiftyMoves;
}

