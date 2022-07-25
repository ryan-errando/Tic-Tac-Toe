#include<stdio.h>

/*
need to do :
-empty the board (makes every box filled with ' ') 											DONE
-fil the board layout (print a layout of 3x3 tic tac toe)									DONE	

layout :
| c | c | c |
|---|---|---|
| c | c | c |
|---|---|---|
| c | c | c |

-check the free spaces (contains integer with value = 9, decremented while spaces != ' ')	DONE
-make function to input coordinates (p1 & p2 input will be based on coordinate) 			DONE			
-detect the winner																			DONE
-print out the winner 																		DONE					
*/

//struct
struct user_data{
	char name[100];
	int win;
	float win_rate;
};

struct marks{
	char p1;
	char p2;
};



// prototype
void main_menu(); // input nama
void rules(); // untuk keluarin rules
void empty(); // untuk kosongin papan
void board_layout(); // keluarin papan
int spaces(); // ngecek sisa kotak
void p1_move(); // input
void p2_move(); // input
char line_check(); // ngecek baris
void winner_result(char); // output siapa yang menang
void result(); // hasil akhir
void win_percentage(); // hitung win rate
void file_1();
void file_2();

//global variable
unsigned int round = 0; // berapa kali main
char board[3][3]; // array untuk papan
struct marks mark = {'X', 'O'}; // untuk marking
struct user_data player[2]; // untuk nyimmpan data statistik player
FILE* out = fopen("tic tac toe result","w"); // output file berbentuk txt
FILE* add = fopen("tic tac toe result","a"); //  add output baru ke file yang sama

// main function
int main(){
	
	//local variable
	char winner, user;
	
	rules();
	main_menu();
	file_1();
	
	// main program
	do{
		winner = ' ';
		user = ' ';
		
		empty();
		
		while(winner == ' ' && spaces() != 0)
		{			
			// player 1 move
			board_layout();
			p1_move();
			winner = line_check();
			if(winner != ' ' || spaces() == 0){
				break;
			}
			
			// player 2 move
			board_layout();
			p2_move();
			winner = line_check();
			if(winner != ' ' || spaces() == 0){
				break;
			}
		}
		
		board_layout();
		winner_result(winner);
		
		printf("\nDo you want to play again ? (y/n) : ");
		getchar();
		scanf("%c", &user);
		(user >= 'a' && user<= 'z') ? user -= 'a'-'A' : user = user;
		
	}while(user == 'Y');
	
	// output berenti
	win_percentage();
	result();
	puts("================================================================================================================");
	puts("THANKS FOR PLAYING !");
	file_2();
	
	return 0;
}

// tampilan main menu
void main_menu(){
	printf("Player 1 (X), please enter your name : ");
	scanf("%[^\n]s", &player[0].name);
	getchar();
	printf("Player 2 (O), please enter your name : ");
	scanf("%[^\n]s", &player[1].name);
	getchar();
	puts("================================================================================================================");
	printf("!! %s VS %s !!\n",player[0].name, player[1].name);
}

// rules
void rules(){
	puts("!! TIC TAC TOE !!");
	puts("================================================================================================================");
	puts("!! RULES !!");
	puts("1. The game is played on a grid that's 3 squares by 3 squares.");
	puts("2. You are X, your friend is O. Players take turns putting their marks in empty squares");
	puts("3. The first player to get 3 of his/her marks in a row (up, down, across, or diagonally) is the winner.");
	puts("4. When all 9 squares are full, the game is over. If no player has 3 marks in a row, the game ends in a tie.");
	puts("");
	puts("!! HOW TO INPUT !!");
	puts("");
	puts("\t\t| 1 1 | 1 2 | 1 3|");
	puts("\t\t|-----|-----|----|");
	puts("\t\t| 2 1 | 2 2 | 2 3|");
	puts("\t\t|-----|-----|----|");
	puts("\t\t| 3 1 | 3 2 | 3 3|");
	puts("");
	puts("Your input will be based on the table above which is seperated by a space");
	puts("================================================================================================================");
}

// kosongkan papan
void empty(){
	for(int i=0 ; i<3 ; i++)
	{
		for(int j =0 ; j<3 ; j++)
		{
			board[i][j] = ' ';
		}
	}
}

// cetak papan
void board_layout(){
	printf("\n| %c | %c | %c |", board[0][0], board[0][1], board[0][2]);
	printf("\n|---|---|---|\n");
	printf("| %c | %c | %c |", board[1][0], board[1][1], board[1][2]);
	printf("\n|---|---|---|\n");
	printf("| %c | %c | %c |\n\n", board[2][0], board[2][1], board[2][2]);
}

// mengecek nilai dari board
int spaces(){
	
	int free = 9;
	
	for(int i=0 ; i<3 ; i++)
	{
		for(int j=0 ; j<3 ; j++)
		{
			if(board[i][j] != ' '){
				free--;
			}
		}	
	}
	return free;
}

// mengecek yg 1 garis
char line_check(){
	
	//col
	for(int i=0 ; i<3 ; i++)
	{
		if(board[0][i] == board[1][i] && board[0][i] == board[2][i])
		return board[0][i];
	}
	
	//row
	for(int i=0 ; i<3 ; i++)
	{
		if(board[i][0] == board[i][1] && board[i][0] == board[i][2])
		return board[i][0];
	}
	
	// diagonal 1
	if(board[0][0] == board[1][1] && board[0][0] == board[2][2]){
		return board[0][0];
	}
	
	//diagonal 2
	if(board[0][2] == board[1][1] && board[0][2] == board[2][0]){
		return board[0][2];		
	}
	return ' ';
}

// input user p1
void p1_move(){
	int x,y;
	do
	{
		printf("%s Input your coordinate (x y) = ", player[0].name);
		scanf("%d %d", &x, &y);
		x--;
		y--;
		
		if(board[x][y] != ' '){
			puts("It has been marked, try another coordinate");
		}else{
			board[x][y] = mark.p1;
			break;
		}
		
	}while(board[x][y] != 0);
}

// input user p2
void p2_move(){
	int x, y;
	do
	{
		printf("%s Input your coordinate (x y) = ", player[1].name);
		scanf("%d %d", &x, &y);
		x--;
		y--;
		
		if(board[x][y] != ' '){
			puts("It has been marked, try another coordinate");
		}else{
			board[x][y] = mark.p2;
			break;
		}
		
	}while(board[x][y] != ' ');	
}

// output winner
void winner_result(char winner){
	switch(winner){
		
		case 'X':
			round++;								//bakalan ditambah kalau salah 1 player menang
			player[0].win++;						//var utk win rate
			printf("! %s WIN !\n",player[0].name);	
			break;
		
		case 'O':
			round++;
			player[1].win++;
			printf("! %s WIN !\n",player[1].name);
			break;
		
		default: 
			puts("TIE");			
	}
}

// win rate
void win_percentage(){
	player[0].win_rate = (float)player[0].win/round*100;
	player[1].win_rate = (float)player[1].win/round*100;
}

// final result
void result(){
	puts("================================================================================================================");
	puts("!! FINAL RESULT !!");
	puts("================================================================================================================");
	printf("Name\t\t: %s\n", player[0].name);
	printf("Total win\t: %d\n", player[0].win);
	printf("Win rate\t: %.2f", player[0].win_rate);
	puts("%");
	puts("");
	printf("Name\t\t: %s\n", player[1].name);
	printf("Total win\t: %d\n", player[1].win);
	printf("Win rate\t: %.2f", player[1].win_rate);
	puts("%");
}

// FILE
void file_1(){
	fprintf(add,"================================================================================================================\n");
	fprintf(add,"PLAYER INFO\n");
	fprintf(add,"================================================================================================================\n");
	fprintf(out, "Player 1 name : %s\n", player[0].name);
	fprintf(out, "Player 2 name : %s\n", player[1].name);
}

// FILE ADD
void file_2(){
	fprintf(add,"================================================================================================================\n");
	fprintf(add,"STATISTIC\n");
	fprintf(add,"================================================================================================================\n");
	fprintf(add,"Name\t\t: %s\n", player[0].name);
	fprintf(add,"Total win\t: %d\n", player[0].win);
	fprintf(add,"Win rate\t: %.2f%%\n\n", player[0].win_rate);
	fprintf(add,"Name\t\t: %s\n", player[1].name);
	fprintf(add,"Total win\t: %d\n", player[1].win);
	fprintf(add,"Win rate\t: %.2f%%\n", player[1].win_rate);
}
