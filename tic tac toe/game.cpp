#include<bits/stdc++.h>
using namespace std;

#define COMPUTER 1 
#define HUMAN 2

#define SIDE 3

#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

//showBoard
void showBoard(char board[SIDE][SIDE])
{
    cout<<"   "<<board[0][0]<<" | "<<board[0][1]<<" | "<<board[0][2]<<endl;
    cout<<" -------------\n";
    cout<<"   "<<board[1][0]<<" | "<<board[1][1]<<" | "<<board[1][2]<<endl;
    cout<<" -------------\n";
    cout<<"   "<<board[2][0]<<" | "<<board[2][1]<<" | "<<board[2][2]<<endl;
    cout<<" -------------\n";
    
}

//check rowCrossed
bool rowCrossed(char board[SIDE][SIDE])
{
    for(int i=0;i<SIDE;i++)
    {
        if(board[i][0]==board[i][1] &&board[i][1]==board[i][2] && board[i][0]!='*')
            return true;
        
    
    }
    return false;
    
}

//check coloumnCrossed
bool coloumnCrossed(char board[SIDE][SIDE])
{
    for(int i=0;i<SIDE;i++)
    {
        if(board[0][i]==board[1][i] &&board[1][i]==board[2][i] && board[0][i]!='*')
            return true;
        
    
    }
    return false;
    
}

//check diagonalCrossed
bool diagonalCrossed(char board[SIDE][SIDE])
{          
        //left to right
        if(board[0][0]==board[1][1] &&board[1][1]==board[2][2] && board[0][0]!='*')
            return true;
        //right to left
        if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2]!='*')
           return true;
    
    
    return false;
    
}

//gameOver
bool gameOver(char board[SIDE][SIDE])
{
    
    return rowCrossed(board) || coloumnCrossed(board) || diagonalCrossed(board);
}

//showInstructions
void showInstructions()
{
    cout<<endl<<"Choose a cell numbered from 1 to 9 as below and play "<<endl;
    cout<<"\t\t\t 1 | 2 | 3 \n";
    cout<<"\t\t\t-----------\n";
     cout<<"\t\t\t 4 | 5 | 6 \n";
    cout<<"\t\t\t-----------\n";
     cout<<"\t\t\t 7 | 8 | 9 \n";
    cout<<"\t\t\t-----------\n";
    
}

//initialise board
void initialise(char board[SIDE][SIDE])
{
    //intially board is empty i.e. '*'
    for(int i=0;i<SIDE;i++)
    {
        for(int j=0;j<SIDE;j++)
        board[i][j]='*';
    }
    
}
//declaration of winner
void declareWinner(int whoseTurn)
{
    if(whoseTurn==COMPUTER)
        cout<<"COMPUTER has won"<<endl;
    else
        cout<<"HUMAN has won"<<endl;
}

//implement minimax
int minimax(char board[SIDE][SIDE],int depth,bool isAI)
{
    int score=0;
    int bestscore=0;
    if(gameOver(board)==true)
    {
        if(isAI==true)
            return -10;
        if(isAI==false)
            return +10;
    }
    else
    {
        
        if(depth<9)
        {
            if(isAI==true)
            {
                bestscore=-999;
                for(int i=0;i<SIDE;i++)
                {
                    for(int j=0;j<SIDE;j++)
                    {
                        if(board[i][j]=='*')
                        {
                            board[i][j]=COMPUTERMOVE;
                            score=minimax(board,depth+1,false);
                            board[i][j]='*';
                            if(score>bestscore)
                            {
                                bestscore=score;
                            }
                        }
                    }
                }
                return bestscore;
            }
            else
            {
                bestscore=999;
                for(int i=0;i<SIDE;i++)
                {
                    for(int j=0;j<SIDE;j++)
                    {
                        if(board[i][j]=='*')
                        {
                            board[i][j]=HUMANMOVE;
                            score=minimax(board,depth+1,true);
                            board[i][j]='*';
                            if(score<bestscore)
                            {
                                bestscore=score;
                            }
                        }
                    }
                }
                return bestscore;
            }
        }
    
       else
       {
           return 0;
        }
    }    
}


//bestMove
int bestMove(char board[SIDE][SIDE],int moveIndex)
{
    int x=-1,y=-1;
    int score=0,bestscore=-999;
    for(int i=0;i<SIDE;i++)
    {
        for(int j=0;j<SIDE;j++)
        {
            if(board[i][j]=='*')
            {
                board[i][j]=COMPUTERMOVE;
                score=minimax(board,moveIndex+1,false);
                board[i][j]='*';
                
                if(score>bestscore)
                {
                    bestscore=score;
                    x=i;
                    y=j;
                }
            }
        }
    }
    return x*3+y;
    
}

//main Tic-Tac-Toe play fn:
void playTicTacToe(int whoseTurn)
{
    char board[SIDE][SIDE];
    int moveIndex=0,x=0,y=0;
    
    initialise(board);
    showInstructions();
    
    while(gameOver(board)==false && moveIndex!=SIDE*SIDE)
    {
        int n;
        if(whoseTurn==COMPUTER)
        {
            n=bestMove(board,moveIndex);
            x=n/SIDE;
            y=n%SIDE;
            
            board[x][y]=COMPUTERMOVE;
            cout<<"COMPUTER has put a "<<COMPUTERMOVE<<" in cell "<<n+1<<endl;
            
            showBoard(board);
            moveIndex++;
            whoseTurn=HUMAN;
        }
        else if(whoseTurn==HUMAN)
        {
            cout<<"You can insert in the following positions: ";
            for(int i=0;i<SIDE;i++)
            {
                for(int j=0;j<SIDE;j++)
                {
                    if(board[i][j]=='*')
                        cout<<(i*3+j)+1<<" "; //for example (1,1)=5th position
                }
            }
            cout<<"\n\n Enter the position = ";
            cin>>n;
            
            n--;  //bcz 0 based indexing
            
            x=n/SIDE;
            y=n%SIDE;
            
            if(board[x][y]=='*' && n<9 && n>=0)
            {
                board[x][y]=HUMANMOVE;
                cout<<"HUMAN has put a "<<HUMANMOVE<<" in cell "<<n+1<<endl;
                
                showBoard(board);
                moveIndex++;
                
                whoseTurn=COMPUTER;
                
            }
            else if(board[x][y]!='*' && n<9 && n>=0)
            {
                cout<<"\nPosition is occupied, select any one place from the available places\n"<<endl;
            }
            else if(n<0 || n>8)
            {
                cout<<"invalid position"<<endl;
            }
        }
        
    }
    if(gameOver(board)==false && moveIndex==SIDE*SIDE)
        cout<<"It's a draw"<<endl;
    else
    {
        if(whoseTurn==COMPUTER)
            whoseTurn=HUMAN;
        else if(whoseTurn==HUMAN)
            whoseTurn=COMPUTER;
        
        declareWinner(whoseTurn);    
    }
    
}

int main ()
{
  cout << "\t\t\t............................\t\t\t" << endl;
  cout << endl << "\t\t\t\t Tic-Tac-Toe\t\t\t\t" << endl;
  cout << endl << "\t\t\t............................\t\t\t" << endl;
  
  char conti='y';
  do{
       char choice;
       cout<<"Do you want start first ?(y/n): ";
       cin>>choice;
       
       if(choice=='y')
          playTicTacToe(HUMAN);
        else if(choice=='n')
           playTicTacToe(COMPUTER);
        else
            cout<<"invalid choice"<<endl;
            
        cout<<"Do you want to quit(y/n): "<<endl;
        cin>>conti;
           
      
  }while(conti=='n');
  
  return 0;
}





