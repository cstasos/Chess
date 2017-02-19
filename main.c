/*
 * Author: Syleopoulos Anastasios
 *   File: chess.c
 *   Type: Game for two players
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/***************** DEFINE ****************/
#define Min_Size 0
#define Max_Size 7

#define wR 1
#define wH 2
#define wB 3
#define wQ 4
#define wK 5
#define wP 6
#define bR 7
#define bH 8
#define bB 9
#define bQ 10
#define bK 11
#define bP 12

#define blank -1

#define a 0
#define b 1
#define c 2
#define d 3
#define e 4
#define f 5
#define g 6
#define h 7

#define player1 0
#define player2 1

/******************** Global ********************/
int Chess_table[Max_Size+1][Max_Size+1];
int Abort[4*Max_Size];


/**************************** FUNCTIONS *****************************/

char *Get_Fname(int pawn){
	if(pawn == wR){
		return("White Rook");
	}else if(pawn == wH){
		return("White Horse");
	}else if(pawn == wB){
		return("White Bishop");
	}else if(pawn == wQ){
		return("White Queen");
	}else if(pawn == wK){
		return("White Kink");
	}else if(pawn == wP){
		return("White Pawm");
	}else if(pawn == bR){
		return("Black Rook");
	}else if(pawn == bH	){
		return("Black Horse");
	}else if(pawn == bB){
		return("Black Bishop");
	}else if(pawn == bQ){
		return("Black Queen");
	}else if(pawn == bK){
		return("Black Kink");
	}else if(pawn == bP){
		return("Black Pawm");
	}else{
		return(" ");
	}
	return("");
}

char *Get_name(int pawn){
	if(pawn == wR){
		return("wR");
	}else if(pawn == wH	){
		return("wH");
	}else if(pawn == wB){
		return("wB");
	}else if(pawn == wQ){
		return("wQ");
	}else if(pawn == wK){
		return("wK");
	}else if(pawn == wP){
		return("wP");
	}else if(pawn == bR){
		return("bR");
	}else if(pawn == bH	){
		return("bH");
	}else if(pawn == bB){
		return("bB");
	}else if(pawn == bQ){
		return("bQ");
	}else if(pawn == bK){
		return("bK");
	}else if(pawn == bP){
		return("bP");	
	}else{
		return("  ");
	}
}

int Get_line(char l){
	if(l == 'a'){
		return a;
	}else if(l == 'b'){
		return b;
	}else if(l == 'c'){
		return c;
	}else if(l == 'd'){
		return d;
	}else if(l == 'e'){
		return e;
	}else if(l == 'f'){
		return f;
	}else if(l == 'g'){
		return g;
	}else if(l == 'h'){
		return h;
	}else{
		return blank;
	}
}

char Get_Cline(int l){
	if(l == a){
		return 'a';
	}else if(l == b){
		return 'b';
	}else if(l == c){
		return 'c';
	}else if(l == d){
		return 'd';
	}else if(l == e){
		return 'e';
	}else if(l == f){
		return 'f';
	}else if(l == g){
		return 'g';
	}else if(l == h){
		return 'h';
	}else{
		return ' ';
	}
}

bool IsSame_Player(int p, int cb){
	if( ((p>=wR && p<=wP) && (cb>=wR && cb<=wP)) 
	 || ((p>=bR && p<=bP) && (cb>=bR && cb<=bP))){
		return true;
	}
		
	return false;
}

bool IsEmpty(int cb){
	if(cb == blank)
		return true;
	
	return false;	
}

void Make_Move(int x, int y, int new_x, int new_y){
	int i,j,swap;
	i=0;
	printf("The %s moved to %c%d!\n",Get_Fname(Chess_table[x][y]),Get_Cline(new_y),new_x+1);
	if(!IsEmpty(Chess_table[new_x][new_y])){
		while(Abort[i]!=blank){
			i++;
		}
		Abort[i] = Chess_table[new_x][new_y];
		printf("The %s was destroyed!",Get_Fname(Abort[i]));
		
		/************* BUBBLE SORT ******************/
		for(i=0;i<(4*Max_Size-1);i++){
			for(j=0;j<4*Max_Size-i-1;j++){
				if(Abort[j]>Abort[j+1] && Abort[j+1]!=blank){
					swap = Abort[j];
					Abort[j] = Abort[j+1];
					Abort[j+1] = swap;
				}
			}
		}	
	}
	Chess_table[new_x][new_y] = Chess_table[x][y];
	Chess_table[x][y] = blank;
}

bool Check_move(int x, int y, int new_x, int new_y){
	int pawn = Chess_table[x][y];
	int tempx, tempy;
	int sgnx, sgny;
	bool move = false;
	sgnx = sgny = 1;
	
	if( (new_x < Min_Size || new_x > Max_Size) 
	 || (new_y < Min_Size || new_y > Max_Size)){
		printf("\nWarning! Invalid movement: Out of border!\n");
		return false;
	}
	if(IsSame_Player(pawn, Chess_table[new_x][new_y])){
		printf("\nWarning! Invalid movement: It's a owned pawn!\n");
		return false;
	}
	/********************* PAWN ****************************/
	if(pawn == wP){
		//printf("\nwP\n");
		/********************** White PAWN! *****************/
		if((new_x == x+1 && new_y == y) && IsEmpty(Chess_table[new_x][new_y])){
			move = true;
		}else if((new_x == x+1) && ((new_y == y+1) || (new_y == y-1))){
			if(!IsEmpty(Chess_table[new_x][new_y])){
				move = true;
			}else{
				return false;
			}
		}else{
			return false;
		}
	}else if(pawn == bP){
		//printf("\nbP\n");
		/******************* Black PAWN! **********************/
		if((new_x == x-1 && new_y == y) && IsEmpty(Chess_table[new_x][new_y])){
			move = true;
		}else if((new_x == x-1) && ((new_y == y+1) || (new_y == y-1))){
			if(!IsEmpty(Chess_table[new_x][new_y])){
				move = true;
			}else{
				return false;
			}
		}
	}else if(pawn == wH || pawn == bH){
		//printf("\nHorse!\n");
		/******************** HORSE! ****************/
		if((new_x == x-2 && new_y == y-1) || (new_x == x-2 && new_y == y+1)
		|| (new_x == x-1 && new_y == y+2) || (new_x == x+1 && new_y == y+2)
		|| (new_x == x+2 && new_y == y+1) || (new_x == x+2 && new_y == y-1)
		|| (new_x == x-1 && new_y == y-2) || (new_x == x+1 && new_y == y-2)){
			move = true;
		}else{
			return false;
		}
	}else if(pawn == wR || pawn == bR){
		//printf("\nRook!\n");
		/********************* ROOK! **********************/
		if(new_x == x){
			if(y>new_y){
				sgny=-1;
			}
			tempy=y+sgny;
			if(new_y == tempy){
				move = true;
			}else{
				while(abs(tempy-new_y) > 0){
					if(!IsEmpty(Chess_table[new_x][tempy])){
						return false;
					}else{
						move = true;
					}
					tempy+=sgny;
				}
			}
		}else if(new_y == y){
			if(x>new_x){
				sgnx=-1;
			}
			tempx=x+sgnx;
			if(new_x == tempx){
				move = true;
			}else{
				while(abs(tempx-new_x) > 0){
					if(!IsEmpty(Chess_table[tempx][new_y])){
						return false;
					}else{
						move = true;
					}
					tempx+=sgnx;
				}
			}
		}else{
			return false;
		}
	}else if(pawn == wB || pawn == bB){
		//printf("\nBishop!\n");
		/******************* BISHOP! *********************/
		if(abs(new_x-x) == abs(new_y-y)){
			if(x > new_x)
				sgnx = -1;
			if(y > new_y)
				sgny = -1;
			tempx = x+sgnx;
			tempy = y+sgny;
			if(tempx == new_x && tempy == new_y){
				move = true;
			}else{
				while(abs(new_x-tempx) > 0){
					if(!IsEmpty(Chess_table[tempx][tempy])){
						return false;
					}else{
						move = true;
					}
					tempx+=sgnx;
					tempy+=sgny;
				}
			}
		}else{
			return false;
		}
	}else if(pawn == wQ || pawn == bQ){
		//printf("\nQueen!\n");
		/****************** QUEEN! ****************/
		if(new_x == x){
			if(y>new_y){
				sgny=-1;
			}
			tempy=y+sgny;
			if(new_y == tempy){
				move = true;
			}else{
				while(abs(tempy-new_y) > 0){
					if(!IsEmpty(Chess_table[new_x][tempy])){
						return false;
					}else{
						move = true;
					}
					tempy+=sgny;
				}
			}
		}else if(new_y == y){
			if(x>new_x){
				sgnx=-1;
			}
			tempx=x+sgnx;
			if(new_x == tempx){
				move = true;
			}else{
				while(abs(tempx-new_x) > 0){
					if(!IsEmpty(Chess_table[tempx][new_y])){
						return false;
					}else{
						move = true;
					}
					tempx+=sgnx;
				}
			}
		}else if(abs(new_x-x) == abs(new_y-y)){
			if(x > new_x)
				sgnx = -1;
			if(y > new_y)
				sgny = -1;
			tempx = x+sgnx;
			tempy = y+sgny;
			if(tempx == new_x && tempy == new_y){
				move = true;
			}else{
				while(abs(new_x-tempx) > 0){
					if(!IsEmpty(Chess_table[tempx][tempy])){
						return false;
					}else{
						move = true;
					}
					tempx+=sgnx;
					tempy+=sgny;
				}
			}
		}else{
			return false;
		}		
	}else if(pawn == wK || pawn == bK){
		//printf("\nKing!\n");
		/********************* KING! *******************/
		if((new_x == x-1 && new_y == y-1) || (new_x == x-1 && new_y == y)
		|| (new_x == x-1 && new_y == y+1) || (new_x == x+1 && new_y == y+1)
		|| (new_x == x+1 && new_y == y) || (new_x == x+1 && new_y == y-1)
		|| (new_x == x && new_y == y+1) || (new_x == x && new_y == y-1)){
			move = true;
		}else{
			return false;
		}
	}
	
	return move;
}

bool Check_pick(int pl, int x, int y){
	if(pl == player1 && Chess_table[x][y] >= wR && Chess_table[x][y] <= wP){
		return true;
	}else if(pl == player2 && Chess_table[x][y] >= bR && Chess_table[x][y] <= bP){
		return true;
	}else 
		return false;
}

bool Check_it(int pl, int x, int y, int new_x, int new_y){
	bool ref = false;
	ref = Check_pick(pl,x,y);
	if(ref){
		ref = Check_move(x,y,new_x,new_y);
	}
	
	return(ref);
}

void Player_Turn(int pl, int *xy){
	int x,y,new_x, new_y;
	char c1,c2;
	char *line = NULL;
	bool check_flag = false;
	char temp[2];
	int ref=0;
	int N=6;
	
	
	if(pl == player1){
		printf("\nPlayer 1 pick white pawn to move!");
	}else{
		printf("\nPlayer 2 pick black pawn to move!");
	}
	do{
		do{
			line = (char *) malloc((N+1)*sizeof(char));
			printf("\nPick a pawn to move. <ex. g3 to e5>: ");
			//getline(&line, &N, stdin);
			fgets(line, 100, stdin);
			ref = sscanf(line, "%c%d %c%c %c%d", &c1, &x, &temp[0], &temp[1], &c2, &new_x);
			sprintf(line, "%c%d %c%c %c%d", c1, x, temp[0], temp[1], c2, new_x);
			if(ref!=6){
				printf("Warning! Invalid input!");
				free(line);
			}else{
				break;
			}
		}while(1);
		
		y = Get_line(c1);
		new_y = Get_line(c2);
		x-=1;
		new_x-=1;
		check_flag = Check_it(pl,x,y,new_x,new_y);
		if(!check_flag){
			printf("\nWarning! The '%s' is invalid move!\n",line);
			free(line);
		}
	}while(!check_flag);

	xy[0]=x; xy[1]=y; xy[2]=new_x; xy[3]=new_y;
	
	return;
}

bool IsGame_Over(){
	int i;
	for(i=0;i<4*Max_Size;i++){
		if(Abort[i] == wK || Abort[i] == bK){
			return true;
		}
	}
	return false;
}

void Game_Over(int pl){
	pl+=1;
	pl = pl%2;
	printf("\n\n******************** WINNER *******************\n");
	if(pl == player1){
		printf("*The white pawns are the winners!!! Well done!*\n");
	}else{
		printf("*The black pawns are the winners!!! Well done!*\n");
	}
	printf("***********************************************\n\n");
}

void Print_Chess(){
	int i, j;
	
	printf("\n\n____________________  Chess Table ____________________\n\n");
	printf(" L\\R |  a  |  b  |  c  |  d  |  e  |  f  |  g  |  h  |\n");
	printf("~~~~~|~~~~~|~~~~~|~~~~~|~~~~~|~~~~~|~~~~~|~~~~~|~~~~~|\n");
		
	for(i=Min_Size;i<=Max_Size;i++){
		printf("  %d  |",i+1);
		for(j=Min_Size;j<=Max_Size;j++){
			printf("  %s |",Get_name(Chess_table[i][j]));
		}
		printf("\n~~~~~|~~~~~|~~~~~|~~~~~|~~~~~|~~~~~|~~~~~|~~~~~|~~~~~|\n");
	}
	printf(" L\\R |  a  |  b  |  c  |  d  |  e  |  f  |  g  |  h  |\n");
	
	printf("\n\n___Aborted Pawn___\n");
	if(Abort[0] == blank){
		printf("No Pawn is out.\n");
		return;
	}
	
	i=0;
	if(Abort[i] <= wP){
		printf("White Pawn: ");
		while(Abort[i] <= wP && Abort[i] != blank){
			if(Abort[i] <= wP){
				printf("%s  ",Get_name(Abort[i]));
			}
			i++;
		}
		printf("\n");
	}
	if(Abort[i] > wP){
		printf("Black Pawn: ");
		while(Abort[i] != blank){
			printf("%s  ",Get_name(Abort[i]));
			i++;
		}
		printf("\n");
	}
	
}

void init(){
	int i, j;
	
	for(i=Min_Size;i<=Max_Size;i++)
		for(j=Min_Size;j<=Max_Size;j++){
			Chess_table[i][j] = blank;
		}
	for(i=0;i<4*Max_Size;i++)
		Abort[i]=blank;

	
	Chess_table[0][a] = wR;   Chess_table[7][a] = bR;
	Chess_table[0][b] = wH;   Chess_table[7][b] = bH;
	Chess_table[0][c] = wB;   Chess_table[7][c] = bB;
	Chess_table[0][d] = wQ;   Chess_table[7][d] = bQ;
	Chess_table[0][e] = wK;   Chess_table[7][e] = bK;
	Chess_table[0][f] = wB;   Chess_table[7][f] = bB;
	Chess_table[0][g] = wH;   Chess_table[7][g] = bH;
	Chess_table[0][h] = wR;   Chess_table[7][h] = bR;
	
	for(i=Min_Size;i<=Max_Size;i++){
		Chess_table[1][i] = wP; Chess_table[6][i] = bP;
	}
}

/****************** MAIN *******************************/

int main(int argc, char *argv[]){
	int player = player1;
	int x,y,xy[4];
	int new_x,new_y;
	
	init();
	Print_Chess();
	printf("Game is ready to start!\n");
	do{
		player = player%2;
		Player_Turn(player, xy);
		x=xy[0]; y=xy[1]; new_x=xy[2]; new_y=xy[3];
		Make_Move(x,y,new_x,new_y);		
		Print_Chess();
		player++;
	}while(!IsGame_Over());
	
	Game_Over(player);
	return(0);
}