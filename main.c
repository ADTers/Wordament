#include "Wordament.h"
#include "mesinkar.h"
#include "mesinkarj.h"
#include "pqueue.h"
#include "multilist.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <time.h>

static struct termios old_termios, new_termios; 

/* restore new terminal i/o settings */
void resetTermios(){
	tcsetattr(0,TCSANOW,&old_termios);
} 

/* initialize new terminal i/o settings */
void initTermios(){
	tcgetattr(0,&old_termios); // store old terminal
	new_termios = old_termios; // assign to new setting
	new_termios.c_lflag &= ~ICANON; // disable buffer i/o
	new_termios.c_lflag &= ~ECHO; // disable echo mode
	tcsetattr(0,TCSANOW,&new_termios); // use new terminal setting
}

/* detect keyboard press */
int kbhit(){
	struct timeval tv = {0L,0L};
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0,&fds);
	return select(1,&fds,NULL,NULL,&tv);
}

/* read 1 character */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

char getch(void) 
{
  return getch_(0);
}

/* skeleton program for play */
void Play(double seconds){
	initTermios(); // initailize new terminal setting to make kbhit() and getch() work
	char cc;
	const double TIME_LIMIT = seconds * CLOCKS_PER_SEC;
	clock_t startTime = clock();
	while ((clock() - startTime) <= TIME_LIMIT){
		if (kbhit()){
		cc = getch();
		resetTermios(); // reset terminal setting to enable buffer i/o and echo (printf)
		printf("Pressed %c\n",cc); // process character
		initTermios(); // use new terminal setting again to make kbhit() and getch() work
		}
	}
	printf("\nTime Up\n");
	resetTermios(); // restore default terminal setting
}


// UNTUK MENGGANTI WARNA TEXT DI TERMINAL

#define red   "\033[0;31m"        /* 0 -> normal ;  31 -> red */
#define cyan  "\033[1;36m"        /* 1 -> bold ;  36 -> cyan */
#define green "\033[1;32m"        /* 4 -> underline ;  32 -> green */
#define blue  "\033[9;34m"        /* 9 -> strike ;  34 -> blue */
#define black  "\033[0;30m"
#define brown  "\033[0;33m"
#define magenta  "\033[1;35m"
#define gray  "\033[0;37m"
#define normal "\033[0m"


// KAMUS

Board B, R;
Stack S;
char *y[100];
boolean T, error,found,found1, selectT,SelectB, usersuggfound, used;
int baris, kolom, score,opt1,opt2, kode,i;
float averagescore,sumscore, countuser,countscore;
char input,a, dummygetch, tempsugg[20];
Kata username,username1;
ListUsers LU,LP;
AdrScores PS,PZ;
AdrUsers PU,PX;
addressQS P;
ID id;
ListSet LS;
addressSugg PSU, PSUT;
addressset PSE, PSET;
ListSugg LSG, LSGTemp;
Map M;
Queue QFinish;
QueueStatistic QS;
time_t rawtime;
struct tm *t;
TANGGAL D;
JAM J;


// ALGORITMA

int main()
{
	LoadDict(&M);
    	system("clear");
    	printf("%s=====================================================================\n", cyan);
    	printf(" _       ______  ____  ____  ___    __  __________   ________   ____ \n");
    	printf("| |     / / __ \\/ __ \\/ __ \\/   |  /  |/  / ____/ | / /_  __/  / __ \\ \n");
    	printf("| | /| / / / / / /_/ / / / / /| | / /|_/ / __/ /  |/ / / /    / / / /\n");
    	printf("| |/ |/ / /_/ / _ _ / /_/ / ___ |/ /  / / /___/ /|  / / /    / /_/ / \n");
    	printf("|__/|__/\\____/_/ |_/_____/_/  |_/_/  /_/_____/_/ |_/ /_/     \\____/  \n\n");
    	printf("=====================================================================\n\n\n");
    	printf("                      %sPress any key to continue%s\n",magenta,normal);
    	getch();
   	while(opt1 != 5)  //OPT1 = 5 adalah QUIT
	{
        MainMenu(&opt1);       // MENAMPILKAN MAIN MENU
        switch(opt1)
        {
            case 1 : 	// REGISTER
                printf("%sEnter user name : ", cyan);

                do
                {
                    found = false;	// INISIALISASI YANG MENANDAKAN USER BELUM DITEMUKAN DI FILE EKSTERNAL
                    scanf("%s", username.TabKata);
                    username.Length = strlen(username.TabKata); 
                    if(strlen(username.TabKata) >= 20 || !(IsAlNumS(username))) // MENGECEK APAKAH LEBIH DARI 20 ATAU ALFANUMERIK
                        printf("Username must be alphanumeric / less or equal to 20 characters\n");
                    else
                    {
                        *x = "scores/List Users & Highscores 2.txt";
                        STARTKATA();
                        while(!EndKata && !found)
                            CheckUser(username,&id,&found);

                        if(found)
                            printf("Sorry, that username already exists\n");
                    }
                }while((strlen(username.TabKata) >= 20 || !(IsAlNumS(username))) || found);
		
                SalinFile(LU,username);
                printf("Congratulations! %s has been successfully registered\n",username.TabKata);
                printf("\n");
                printf("%sPress any key to continue%s\n", magenta,cyan);
                dummygetch = getch();
		dummygetch = getch();
                break;

            case 2 :	//LOGIN			
                CreateList(&LU);
                printf("\n");
                *x = "scores/List Users & Highscores 2.txt";
                STARTKATA();
                while(!(EndKata))
                    InitUser(&LU,&id);	// MEMASUKKAN DATA FILE EKSTERNAL KE DALAM LIST
                InversListU(&LU);
                ListUsersLengkap(LU);	// MENAMPILKAN LIST USER
                found1 = false;		// INISIALISASI YANG MENANDAKAN USERNAME TIDAK DITEMUKAN
                while(!found1)
                {
                    printf("=====================================================================\n");
                    printf("Enter username : ");
                    scanf("%s",username1.TabKata);
                    username1.Length = strlen(username1.TabKata);
                    STARTKATA();
                    while(!EndKata && !found1)
                        CheckUser(username1,&id,&found1);

                    if(!found1)
                        printf("%s not found. Try again\n",username1.TabKata);
                }

                SelectB = true;	// INISIALISASI AGAR SETELAH MEMILIH BOARD, MELIHAT SCORE TIDAK KELUAR KE MAIN MENU, MELAINKAN PREP MENU
                selectT = false;	// INISIALISASI YANG MENANDAKAN USER BELUM PILIH BOARD
                
                while(SelectB == true)
                {
		    if(selectT == false)
			kode = 1;

                    PrepMenu(&opt2, username1);	// PREPARATION MENU
                    switch(opt2)
                    {
                        case 1 :	// PLAY GAME
                            if(selectT == false) 
			    {
                                kode = 1;
                                *y = "boards/1.txt";
                            }
                            baris = 1;
                            kolom = 1;
                            T = false;
                            used = false;
                            score = 0;
                            CreateEmptyQ(&QFinish);
                            CreateEmpty(&S);
							CreateListSU(&LSG);
							CreateListSU(&LSGTemp);
							
							ReadSuggestion(&LSG, kode);
							strcpy(tempsugg, username1.TabKata);
							PSU = FirstSU(LSG);
							usersuggfound = false;
							while (PSU != Nil) {
								if (strcmp(InfoSU(PSU), tempsugg) == 0) {
									usersuggfound =  true;
									break;
								}
								else {
									PSU = NextSU(PSU);
								}
							}
							if (!usersuggfound) {
								InsVSUFirst(&LSG, tempsugg);
								PSU = FirstSU(LSG);
							}
							InsVSUFirst(&LSGTemp, tempsugg);
							PSE = FirstSE(PSU);
							if (PSE != Nil) 
								strcpy(tempsugg, InfoSE(PSE));
							else {
								tempsugg[0] = ' ';
								tempsugg[1] = '\0';
							}
							CreateListSet(&LS);
                            CreateBoard(&B);
                            AmbilBoard(&B);
                            InitKursor(&B);
                            InitSelect(&B, &S);
                            system("clear");
                            printf("Score = %d\n\n", score);
                            printf("Suggestion = %s\n\n", InfoSE(PSE));
                            TulisBoard(B);
                            printf("\n\n");
                            dummygetch = getch();
                            input = getch();
                            printf("\n");
                            while (input != 'm')
                            {
                                system("clear");
                                ProsesKursor(&B, &baris, &kolom, &T, input, &error);
                                Select(&B, baris, kolom, T, &S, &score, &LS, &QFinish, &used, &LSG, &LSGTemp, &M, PSU);
                                printf("Score = %d\n\n", score);
                                PSE = FirstSE(PSU);
                                printf("Suggestion = %s\n\n", InfoSE(PSE));
                                TulisBoard(B);
                                printf("\n");
                                if (used)
									printf("Invalid Word\n");
								else
									printf("\n");
                                if (error)
                                    printf("error\n");
                                else
                                    printf("\n");
                                input = getch();
                                printf("\n");
                                error = false;
                                used = false;
                            }
                            time(&rawtime);	//INISIALISASI WAKTU
			    t = localtime(&rawtime);
			    D.YY = (*t).tm_year+1900;
			    D.MM = (*t).tm_mon+1;
			    D.DD = (*t).tm_mday;
		            J.HH = (*t).tm_hour;
		  	    J.MM = (*t).tm_min;
			    J.SS = (*t).tm_sec;
                            InsSortScoreU (&LU,D,J,score,username1);	//INSERT SCORE KE LIST SCORE
                            SalinInto(LU, kode);	// MENYALIN KE FILE EKSTERNAL
                            SelectB = false;
                            system("clear");
                            addressQ PQ;
                            PQ = Head(QFinish);
                            while (PQ != Nil) 
			    {
			    	PrintSet(InfoQ(PQ));
				printf("\n");
				PQ = NextQ(PQ);
		       	    }
				printf("Total Score = %d\n", score);
							PSU = FirstSU(LSG);
							PSE = FirstSE(PSU);
							PSUT = FirstSU(LSGTemp);
							while (PSUT != Nil) {
								PSET = FirstSE(PSUT);
								while (PSET != Nil) {
									InsVSEFirst(&LSG, PSU, InfoSE(PSET));
									PSET = NextSE(PSET);
								}
								PSUT = NextSU(PSUT);
							}
							WriteSuggestion(LSG, kode);
							printf("Press any key to continue\n");
							dummygetch = getch();
			    getch();
                            break;

                        case 2 :	//SELECT BOARD
                            PilihBoard(&selectT, &kode);
		            CreateList(&LU);
			    STARTKATA();
                            while(!(EndKata))
                    	       InitUser(&LU,&id);	// MEMASUKKAN DATA FILE EKSTERNAL KE DALAM LIST
                	    InversListU(&LU);
                            SelectB = true;
                            break;

                        case 3 :	//VIEW MY HIGH SCORES
			    ViewMyHighScores(LU,username1);
			    printf("%sPress any key to continue%s\n", magenta,cyan);
			    dummygetch = getch();
			    dummygetch = getch();
                            SelectB = true;
  			    break;

                        case 4 :	//VIEW ALL HIGH SCORES	
			    ViewAllHighScores(LU);
	              	    printf("%sPress any key to continue%s\n", magenta,cyan);
			    dummygetch = getch();
			    dummygetch = getch();
                            SelectB = true;
                            break;

                        case 5 :	//VIEW BOARD STATISTICS	
 				CreateEmptyQS(&QS);
                            	countuser = 0;
				countscore = 0;
				sumscore = 0;
				PU = FirstU(LU);
				while (PU != Nil)
				{
					PS = FirstS(PU);
					if((InfoD(PS)).YY != 0)
					{
						countuser += 1;
					}	
					while(PS != Nil)
					{
						if((InfoD(PS)).YY != 0)
						{
							countscore += 1;
							sumscore += InfoS(PS);
						}	
						PS = NextS(PS);	
					}
					PU = NextU(PU); 	
				}
				//CreateList(&LU);
				averagescore = sumscore/countscore;
				printf("%.0f user/s have played in board %d\n",countuser,kode);
				if(countscore == 0)
					averagescore = 0;
				printf("The average score in board %d is %.2f\n",kode,averagescore);
				AddQS(&QS,kode,averagescore);
				for(i=0; i<=9;i++)
				{
					switch(i)
					{
						case 0 : *x = "scores/List Users & Highscores 1.txt"; break;
						case 1 : *x = "scores/List Users & Highscores 2.txt"; break;
						case 2 : *x = "scores/List Users & Highscores 3.txt"; break;
						case 3 : *x = "scores/List Users & Highscores 4.txt"; break;
						case 4 : *x = "scores/List Users & Highscores 5.txt"; break;
						case 5 : *x = "scores/List Users & Highscores 6.txt"; break;
						case 6 : *x = "scores/List Users & Highscores 7.txt"; break;
						case 7 : *x = "scores/List Users & Highscores 8.txt"; break;
						case 8 : *x = "scores/List Users & Highscores 9.txt"; break;
						case 9 : *x = "scores/List Users & Highscores 10.txt"; break;
					}
					if(i != kode)
					{
						CreateList(&LP);
						STARTKATA();
						while(!EndKata)
							InitUser(&LP,&id);
					
						InversListU(&LP);
						printf("%s\n", *x);
						ListUsersLengkap(LP);
						sumscore = 0;
						countscore = 0;
						PX = FirstU(LP);
						while (PX != Nil)
						{
							PZ = FirstS(PX);	
							while(PZ != Nil)
							{
								if((InfoD(PZ)).YY != 0)
								{
									countscore += 1;
									sumscore += InfoS(PZ);
								}	
								PZ = NextS(PZ);	
							}
							PX = NextU(PX); 	
						}
						if (countscore == 0)
							averagescore = 0;
						else
							averagescore = sumscore/countscore;
						AddQS(&QS, i, averagescore);
					}
							
				}
				PX = FirstU(LP);
				DealokasiU(&PX);
				PZ = FirstS(PX);
				DealokasiS(&PZ);
				P = Head(QS);
				printf("Difficulty Level of Boards : \n");
				for(i=1;i<=10;i++)
				{						
					printf("%d. Board no.%d with average user scores of %.2f\n",i,InfoQ(P),Prio(P));
					P = NextQ(P);
					if (P == Nil)
					{
						break;
					}
				}
			    printf("%sPress any key to continue%s\n", magenta,cyan);
           		    dummygetch = getch();
		  	    dummygetch = getch();
			    SelectB = true;
			    break;

                        case 6 :	// LOG OUT
                            SelectB = false;
                            break;
                    }
                if(SelectB == false)
                    break;
                }
		break;
            case 3 :	// HOW TO PLAY
		HowToPlay();
                break;
            case 4 :	// ABOUT
                About();
                break;
        }
	}
	printf("%s\n", normal); //MENGGANTI WARNA TEXT TERMINAL KE AWAL
	
	return 0;
}
