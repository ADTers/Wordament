#include "Wordament.h"
#include "mesinkarj.h"

#define red   "\033[0;31m"        /* 0 -> normal ;  31 -> red */
#define cyan  "\033[1;36m"        /* 1 -> bold ;  36 -> cyan */
#define green "\033[1;32m"        /* 4 -> underline ;  32 -> green */
#define blue  "\033[9;34m"        /* 9 -> strike ;  34 -> blue */
#define black  "\033[0;30m"
#define brown  "\033[0;33m"
#define magenta  "\033[1;35m"
#define gray  "\033[0;37m"
#define normal "\033[0m"

void LoadDict(Map *M) {
	int i;
	char S[17];
	
	CreateEmptyHash(*M);
	
	STARTKATAD();
	while (!EndKataD) {
		for (i=0;i<CKataD.LengthD;i++);

		memcpy(S, CKataD.TabKataD, i);
		S[i] = '\0';
		
		Insert(S,*M);
		ADVKATAD();
	}
}

void CreateBoard (Board *B) {
	(*B).KolEff = 0;
	(*B).BarEff = 0;
}

void PilihBoard(boolean *select, int *kode) {
    int kodeboard;

        printf("=====================================================================\n"); 
        printf("Pilih Board: ");
	scanf("%d", &kodeboard);
	while(kodeboard < 0 || kodeboard > 9) {
        printf("Kode Board Yang Anda Masukkan Salah, Silahkan Coba Lagi\n");
        printf("=====================================================================\n");
        printf("Pilih Board: ");
        scanf("%d", &kodeboard);
        system("clear");
	}
	switch(kodeboard) {
        case 0 :
            *y = "boards/0.txt";
	    *x = "scores/List Users & Highscores 1.txt";
            *select = true;
            break;
        case 1 :
            *y = "boards/1.txt";
	    *x = "scores/List Users & Highscores 2.txt";
            *select = true;
            break;
        case 2 :
            *y = "boards/2.txt";
	    *x = "scores/List Users & Highscores 3.txt";
            *select = true;
            break;
        case 3 :
            *y = "boards/3.txt";
	    *x = "scores/List Users & Highscores 4.txt";
            *select = true;
            break;
        case 4 :
            *y = "boards/4.txt";
	    *x = "scores/List Users & Highscores 5.txt";
            *select = true;
            break;
        case 5 :
            *y = "boards/5.txt";
	    *x = "scores/List Users & Highscores 6.txt";
            *select = true;
            break;
        case 6 :
            *y = "boards/6.txt";
	    *x = "scores/List Users & Highscores 7.txt";
            *select = true;
            break;
        case 7 :
            *y = "boards/7.txt";
	    *x = "scores/List Users & Highscores 8.txt";
            *select = true;
            break;
        case 8 :
            *y = "boards/8.txt";
	    *x = "scores/List Users & Highscores 9.txt";
            *select = true;
            break;
        case 9 :
            *y = "boards/9.txt";
	    *x = "scores/List Users & Highscores 10.txt";
            *select = true;
            break;
	}
	*kode = kodeboard;
}

void InitKursor (Board *B) {
    int i, j;
    for (i=1; i<=4; i++) {
        for (j=1; j<=4; j++) {
            (*B).IsiBoard[i][j].Kursor = false;
        }
    }
    (*B).IsiBoard[1][1].Kursor = true;
}

void InitSelect (Board *B, Stack *S) {
    infotype dump;
    int i, j;
    for (i=1; i<=4; i++) {
        for (j=1; j<=4; j++) {
            (*B).IsiBoard[i][j].Selected = false;
        }
    }
    while (!IsEmpty(*S)) {
        Pop(S, &dump);
    }
}

void ProsesKursor (Board *B, int *x, int *y, boolean *ToggleSelect, char input, boolean *error) {
    switch (input) {
    case 'm': break;
    case 's':
        *ToggleSelect = !(*ToggleSelect);
        break;
    case 'r':
        if (!*ToggleSelect) {
        *B = RotateCW(*B);
        int i, j;
        for (i=1; i<=4; i++) {
            for (j=1; j<4; j++) {
                if ((*B).IsiBoard[i][j].Kursor)
                    break;
            }
            if ((*B).IsiBoard[i][j].Kursor)
                break;
        }
        *x = i;
        *y = j;
        }
        else
            *error = true;
        break;
    case 'w':
        if (*x == 1)
            *error = true;
        else {
            (*B).IsiBoard[*x][*y].Kursor = false;
            *x = *x - 1;
            (*B).IsiBoard[*x][*y].Kursor = true;
        }
        break;
    case 'a':
        if (*y == 1)
            *error = true;
        else {
            (*B).IsiBoard[*x][*y].Kursor = false;
            *y = *y - 1;
            (*B).IsiBoard[*x][*y].Kursor = true;
        }
        break;
    case 'x':
        if (*x == 4)
            *error = true;
        else {
            (*B).IsiBoard[*x][*y].Kursor = false;
            *x = *x + 1;
            (*B).IsiBoard[*x][*y].Kursor = true;
        }
        break;
    case 'd':
        if (*y == 4)
            *error = true;
        else {
            (*B).IsiBoard[*x][*y].Kursor = false;
            *y = *y + 1;
            (*B).IsiBoard[*x][*y].Kursor = true;
        }
        break;
    case 'q':
        if (*x == 1 || *y == 1)
            *error = true;
        else {
            (*B).IsiBoard[*x][*y].Kursor = false;
            *x = *x - 1;
            *y = *y - 1;
            (*B).IsiBoard[*x][*y].Kursor = true;
        }
        break;
    case 'e':
        if (*x == 1 || *y == 4)
            *error = true;
        else {
            (*B).IsiBoard[*x][*y].Kursor = false;
            *x = *x - 1;
            *y = *y + 1;
            (*B).IsiBoard[*x][*y].Kursor = true;
        }
        break;
    case 'z':
        if (*x == 4 || *y == 1)
            *error = true;
        else {
            (*B).IsiBoard[*x][*y].Kursor = false;
            *x = *x + 1;
            *y = *y - 1;
            (*B).IsiBoard[*x][*y].Kursor = true;
        }
        break;
    case 'c':
        if (*x == 4 || *y == 4)
            *error = true;
        else {
            (*B).IsiBoard[*x][*y].Kursor = false;
            *x = *x + 1;
            *y = *y + 1;
            (*B).IsiBoard[*x][*y].Kursor = true;
        }
        break;
    default:
        *error = true;
        break;
    }
}

void Select (Board *B, int x, int y, boolean ToggleSelect, Stack *S, int *score, ListSet *LS, Queue *Q, boolean *used, ListSugg *LSG, ListSugg *LSGTemp, Map *M, addressSugg PSU) {
    infotype z, dump;
    if (ToggleSelect && !(*B).IsiBoard[x][y].Selected) {
        (*B).IsiBoard[x][y].Selected = true;
        z.c = (*B).IsiBoard[x][y].ArrayIsi[2];
        z.i = x;
        z.j = y;
        Push(S, z);
    }
    else if (ToggleSelect && (*B).IsiBoard[x][y].Selected) {
        Pop(S, &dump);
        while (x != dump.i || y != dump.j) {
            (*B).IsiBoard[dump.i][dump.j].Selected = false;
            Pop(S, &dump);
        }
        Push(S, dump);
    }
    else if (!ToggleSelect) {
        if (!IsEmpty(*S)) {
            Pop(S, &dump);
            if (IsEmpty(*S))
                InitSelect(B, S);
            else {
                Push(S, dump);
                CalcScore(score, S, LS, Q, used, LSG, LSGTemp, M, PSU);
                InitSelect(B, S);
            }
        }
    }
}
void AmbilBoard (Board *B) {
	int i, j;

	STARTJ();
    (*B).KolEff = 4;
    (*B).BarEff = 4;
    for (i=1; i<=4; i++) {
        j = 1;
        while (j<=(*B).KolEff) {
            if (CC != BLANK) {
                (*B).IsiBoard[i][j].ArrayIsi[1] = ' ';
                (*B).IsiBoard[i][j].ArrayIsi[2] = CC;
                (*B).IsiBoard[i][j].Neff = 2;
                j = j+1;
                ADVJ();
            }
            else {
                ADVJ();
            }
        }
    }
}

void TulisBoard (Board B) {
	int i, j, b;

	for (i=1; i<=4; i++) {
		for (j=1; j<=4; j++) {
			for (b=1; b<=B.IsiBoard[i][j].Neff; b++) {
				if (B.IsiBoard[i][j].Kursor)
                    B.IsiBoard[i][j].ArrayIsi[1] = '>';
				else if (B.IsiBoard[i][j].Selected)
                    B.IsiBoard[i][j].ArrayIsi[1] = '*';
                printf("%c", B.IsiBoard[i][j].ArrayIsi[b]);
				}
			}
			printf(" ");
		printf("\n");
	}
}

Board RotateCW (Board B) {
    int i, j, b;
    Board R;

    i=1;
    for (j=1; j<=4; j++) {
        for (b=1; b<=B.IsiBoard[i][j].Neff; b++) {
            R.IsiBoard[j][4].ArrayIsi[b] = B.IsiBoard[i][j].ArrayIsi[b];
            R.IsiBoard[j][4].Neff = B.IsiBoard[i][j].Neff;
            R.IsiBoard[j][4].Kursor = B.IsiBoard[i][j].Kursor;
            R.IsiBoard[j][4].Selected = B.IsiBoard[i][j].Selected;
        }
    }
    i=4;
    for (j=1; j<=4; j++) {
        for (b=1; b<=B.IsiBoard[i][j].Neff; b++) {
            R.IsiBoard[j][1].ArrayIsi[b] = B.IsiBoard[i][j].ArrayIsi[b];
            R.IsiBoard[j][1].Neff = B.IsiBoard[i][j].Neff;
            R.IsiBoard[j][1].Kursor = B.IsiBoard[i][j].Kursor;
            R.IsiBoard[j][1].Selected = B.IsiBoard[i][j].Selected;
        }
    }
    for (b=1; b<=B.IsiBoard[2][4].Neff; b++) {
            R.IsiBoard[4][3].ArrayIsi[b] = B.IsiBoard[2][4].ArrayIsi[b];
            R.IsiBoard[4][3].Neff = B.IsiBoard[2][4].Neff;
            R.IsiBoard[4][3].Kursor = B.IsiBoard[2][4].Kursor;
            R.IsiBoard[4][3].Selected = B.IsiBoard[2][4].Selected;
        }
    for (b=1; b<=B.IsiBoard[3][4].Neff; b++) {
            R.IsiBoard[4][2].ArrayIsi[b] = B.IsiBoard[3][4].ArrayIsi[b];
            R.IsiBoard[4][2].Neff = B.IsiBoard[3][4].Neff;
            R.IsiBoard[4][2].Kursor = B.IsiBoard[3][4].Kursor;
            R.IsiBoard[4][2].Selected = B.IsiBoard[3][4].Selected;
        }
    for (b=1; b<=B.IsiBoard[3][1].Neff; b++) {
            R.IsiBoard[1][2].ArrayIsi[b] = B.IsiBoard[3][1].ArrayIsi[b];
            R.IsiBoard[1][2].Neff = B.IsiBoard[3][1].Neff;
            R.IsiBoard[1][2].Kursor = B.IsiBoard[3][1].Kursor;
            R.IsiBoard[1][2].Selected = B.IsiBoard[3][1].Selected;
        }
    for (b=1; b<=B.IsiBoard[2][1].Neff; b++) {
            R.IsiBoard[1][3].ArrayIsi[b] = B.IsiBoard[2][1].ArrayIsi[b];
            R.IsiBoard[1][3].Neff = B.IsiBoard[2][1].Neff;
            R.IsiBoard[1][3].Kursor = B.IsiBoard[2][1].Kursor;
            R.IsiBoard[1][3].Selected = B.IsiBoard[2][1].Selected;
        }
    for (b=1; b<=B.IsiBoard[2][2].Neff; b++) {
            R.IsiBoard[2][3].ArrayIsi[b] = B.IsiBoard[2][2].ArrayIsi[b];
            R.IsiBoard[2][3].Neff = B.IsiBoard[2][2].Neff;
            R.IsiBoard[2][3].Kursor = B.IsiBoard[2][2].Kursor;
            R.IsiBoard[2][3].Selected = B.IsiBoard[2][2].Selected;
        }
    for (b=1; b<=B.IsiBoard[2][3].Neff; b++) {
            R.IsiBoard[3][3].ArrayIsi[b] = B.IsiBoard[2][3].ArrayIsi[b];
            R.IsiBoard[3][3].Neff = B.IsiBoard[2][3].Neff;
            R.IsiBoard[3][3].Kursor = B.IsiBoard[2][3].Kursor;
            R.IsiBoard[3][3].Selected = B.IsiBoard[2][3].Selected;
        }
    for (b=1; b<=B.IsiBoard[3][3].Neff; b++) {
            R.IsiBoard[3][2].ArrayIsi[b] = B.IsiBoard[3][3].ArrayIsi[b];
            R.IsiBoard[3][2].Neff = B.IsiBoard[3][3].Neff;
            R.IsiBoard[3][2].Kursor = B.IsiBoard[3][3].Kursor;
            R.IsiBoard[3][2].Selected = B.IsiBoard[3][3].Selected;
        }
    for (b=1; b<=B.IsiBoard[3][2].Neff; b++) {
            R.IsiBoard[2][2].ArrayIsi[b] = B.IsiBoard[3][2].ArrayIsi[b];
            R.IsiBoard[2][2].Neff = B.IsiBoard[3][2].Neff;
            R.IsiBoard[2][2].Kursor = B.IsiBoard[3][2].Kursor;
            R.IsiBoard[2][2].Selected = B.IsiBoard[3][2].Selected;
        }
    return R;
}

void CalcScore (int *x, Stack *S, ListSet *LS, Queue *Q, boolean *used, ListSugg *LSG, ListSugg *LSGTemp, Map *M, addressSugg PSU)
{
    addressSugg PSUT;
    addressset PSE, PSET, precSE;
    boolean suggfound;
    Stack inverse;
	Set Set;
	CreateEmptySet(&Set);
    CreateEmpty(&inverse);
    infotype dump;
    char word[17], dummy;
    int i, j, sum;
    i = 1; sum = 0;
    while (!IsEmpty(*S)) {
        Pop(S, &dump);
        Push(&inverse, dump);
    }
    while (!IsEmpty(inverse)) {
        Pop(&inverse, &dump);
        word[i] = dump.c;
		InsertSet(&Set, word[i]);		
        switch (word[i]) {
        case 'E':
            sum += 1;
            break;
        case 'C':
            sum += 3;
            break;
        case 'D':
            sum += 3;
            break;
        case 'L':
            sum += 3;
            break;
        case 'G':
            sum += 4;
            break;
        case 'H':
            sum += 4;
            break;
        case 'M':
            sum += 4;
            break;
        case 'P':
            sum += 4;
            break;
        case 'U':
            sum += 4;
            break;
        case 'B':
            sum += 5;
            break;
        case 'F':
            sum += 5;
            break;
        case 'Y':
            sum += 5;
            break;
        case 'K':
            sum += 6;
            break;
        case 'V':
            sum += 6;
            break;
        case 'W':
            sum += 6;
            break;
        case 'Z':
            sum += 8;
            break;
        case 'X':
            sum += 9;
            break;
        case 'J':
            sum += 10;
            break;
        case 'Q':
            sum += 10;
            break;
        case 'A':
            sum += 2;
            break;
        case 'I':
            sum += 2;
            break;
        case 'N':
            sum += 2;
            break;
        case 'O':
            sum += 2;
            break;
        case 'R':
            sum += 2;
            break;
        case 'S':
            sum += 2;
            break;
        case 'T':
            sum += 2;
            break;
        default:
            break;
        }
        i++;
    }
    i--;
    sum = sum * i;
    if (i >= 10)
        sum += 100;
	
	for (j=0;j<i;j++) {
		word[j] = word[j+1];
	}
	word[j] = '\0';
	
	if (IsMember(word,*M)) {
		
		if (!FSearchSet(*LS,SearchSet(*LS,Set))) {
			*x = *x + sum;
			InsertWord(LS,Set);
			AddQ(Q, Set, sum);
		}
		else
			*used = true;
			
		PSUT = FirstSU(*LSGTemp);
		PSE = FirstSE(PSU);
		suggfound = false;
		while (PSE != Nil) {
			if (strcmp(InfoSE(PSE), word) == 0) {
				suggfound = true;
				InsVSEFirst(LSGTemp, PSUT, word);
				precSE = Nil;
				PSET = FirstSE(PSU);
				int counter;
				counter = 0;
				while (PSET != Nil) {	
					if (strcmp(InfoSE(PSET), word) == 0) {
						if (counter > 0) {
							NextSE(precSE) = NextSE(PSE);
							break;
						}
						else {
							FirstSE(PSU) = NextSE(FirstSE(PSU));
							break;
						}
					}
					else {
						precSE = PSET;
						PSET = NextSE(PSET);
						counter = counter + 1;
					}
				}
				break;
			}
			else
				PSE = NextSE(PSE);
		}
		if (!suggfound) {
			PSUT = FirstSU(*LSGTemp);
			PSET = AlokasiSE(word);
			NextSE(PSET) = FirstSE(PSUT);
			FirstSE(PSUT) = PSET;
		}	
	}
	else
		*used = true;	
}


void randgreet (Kata s)
{
    int x;

    x = rand() % 4;
    switch (x)
    {
        case 0 :
            printf("                            Hello %s\n", s.TabKata);
            break;
        case 1 :
            printf("                            Greeting %s\n", s.TabKata);
            break;
        case 2 :
            printf("                            Welcome! %s\n", s.TabKata);
            break;
        case 3 :
            printf("                            Good day %s\n", s.TabKata);
            break;
    }
}

void MainMenu (int *x)
{
	system("clear");
        printf("%s=====================================================================\n", cyan);
	printf(" _       ______  ____  ____  ___    __  __________   ________   ____ \n");
	printf("| |     / / __ \\/ __ \\/ __ \\/   |  /  |/  / ____/ | / /_  __/  / __ \\ \n");
	printf("| | /| / / / / / /_/ / / / / /| | / /|_/ / __/ /  |/ / / /    / / / /\n");
	printf("| |/ |/ / /_/ / _ _ / /_/ / ___ |/ /  / / /___/ /|  / / /    / /_/ / \n");
	printf("|__/|__/\\____/_/ |_/_____/_/  |_/_/  /_/_____/_/ |_/ /_/     \\____/  \n\n");
	printf("=====================================================================%s\n\n",normal);
        printf("%s                                                               .---.    \n",green);
        printf("                                                              /  .  \\  \n");
        printf("                                                             |\\_/|   |  \n");
        printf("                                                             |   |  /|  \n");
        printf("  .----------------------------------------------------------------' |  \n");
        printf(" /  .-.                                                              |  \n");
        printf("|  /   \\                      %s1. Register%s                            |  \n", cyan,green);
        printf("| |\\_.  |                     %s2. Login%s                               |  \n", cyan,green);
        printf("|\\|  | /|                     %s3. How to play%s                         |  \n", cyan,green);
        printf("| `---' |                     %s4. About%s                               |  \n", cyan,green);
        printf("|       |                     %s5. Quit%s                                | *\n", cyan,green);
        printf("|       |                                                           /   \n");
        printf("|       |----------------------------------------------------------'    \n");
        printf("\\       |                                                               \n");
        printf(" \\     /                                                               \n");
        printf("  `---'                                                                 \n");
        printf("    \n");
		printf("%s=====================================================================\n", cyan);

        do
        {
            printf("Enter Option : ");
            scanf("%d", x);
            if(*x > 5 || *x <= 0)
                printf("Wrong option, type again\n");
            printf("=====================================================================\n");
        } while(*x > 5 || *x <= 0);
}

void PrepMenu(int *y, Kata s)
{
	system("clear");
	printf("%s=====================================================================\n", cyan);
	printf(" _       ______  ____  ____  ___    __  __________   ________   ____ \n");
	printf("| |     / / __ \\/ __ \\/ __ \\/   |  /  |/  / ____/ | / /_  __/  / __ \\ \n");
	printf("| | /| / / / / / /_/ / / / / /| | / /|_/ / __/ /  |/ / / /    / / / /\n");
	printf("| |/ |/ / /_/ / _ _ / /_/ / ___ |/ /  / / /___/ /|  / / /    / /_/ / \n");
	printf("|__/|__/\\____/_/ |_/_____/_/  |_/_/  /_/_____/_/ |_/ /_/     \\____/  \n\n");
	printf("=====================================================================\n\n");
        randgreet(s);
        printf("            %s                                                   .---.    \n",green);
        printf("                                                              /  .  \\  \n");
        printf("                                                             |\\_/|   |  \n");
        printf("                                                             |   |  /|  \n");
        printf("  .----------------------------------------------------------------' |  \n");
        printf(" /  .-.                                                              |  \n");
        printf("|  /   \\                    %s1. Play Game%s                             |  \n", cyan,green);
        printf("| |\\_.  |                   %s2. Select Board%s                          |  \n", cyan,green);
        printf("|\\|  | /|                   %s3. View My Highscore%s                     |  \n", cyan,green);
        printf("| `---' |                   %s4. View All Highscore%s                    |  \n", cyan,green);
        printf("|       |                   %s5. View Board Statistic%s                  | *\n", cyan,green);
        printf("|       |                   %s6. Logout%s                                | *\n", cyan,green);
        printf("|       |                                                           /   \n");
        printf("|       |----------------------------------------------------------'    \n");
        printf("\\       |                                                               \n");
        printf(" \\     /                                                               \n");
        printf("  `---'                                                                 \n");
        printf("    \n");
		printf("%s=====================================================================\n",cyan);

    printf("Enter Option : ");

    do
    {
		scanf("%d", y);
		if(*y > 6 || *y <= 0)
			printf("Wrong option, type again\n");
    } while(*y > 6 || *y <= 0);
}

void About()
{
    char a;
   system("clear");
	printf("%s=====================================================================\n", cyan);
	printf(" _       ______  ____  ____  ___    __  __________   ________   ____ \n");
	printf("| |     / / __ \\/ __ \\/ __ \\/   |  /  |/  / ____/ | / /_  __/  / __ \\ \n");
	printf("| | /| / / / / / /_/ / / / / /| | / /|_/ / __/ /  |/ / / /    / / / /\n");
	printf("| |/ |/ / /_/ / _ _ / /_/ / ___ |/ /  / / /___/ /|  / / /    / /_/ / \n");
	printf("|__/|__/\\____/_/ |_/_____/_/  |_/_/  /_/_____/_/ |_/ /_/     \\____/  \n\n");
	printf("=====================================================================\n\n");
    printf("                    This game brought to you by : \n");
    printf("              ___________________   ___________________        \n");
    printf("          .-/|  1                \\ /                2  |\\-.    \n");
    printf("          ||||                    :                    ||||    \n");
    printf("          ||||                    :    WORDAMENT - 0   ||||    \n");
    printf("          ||||                    :                    ||||    \n");
    printf("          ||||      TEAM          :  Alexander Sukono  ||||    \n");
    printf("          ||||         FFF        :  Calvin Aditya J.  ||||    \n");
    printf("          ||||                    :  Freddy Isman      ||||    \n");
    printf("          ||||                    :  Hans Christian G. ||||    \n");
    printf("          ||||                    :  Jonathan Benedict ||||    \n");
    printf("          ||||                    :  Juan Anton        ||||    \n");
    printf("          ||||                    :                    ||||    \n");
    printf("          ||||                    :    FFF@fmail.com   ||||    \n");
    printf("          ||||___________________ : ___________________||||    \n");
    printf("          ||/===================\\:/====================\\||    \n");
    printf("          `---------------------~___~--------------------''    \n");
    printf("\n\n\n");
    printf("                      %sPress any key to continue%s\n",magenta,normal);
    getch();
    getch();
}

boolean IsAlNumS (Kata s)
{
    bool found;
    int i;

    found = false; i = 0;

    while(s.TabKata[i] != '\0' && !(found))
    {
        if(!(isalnum(s.TabKata[i])))
            found = true;
        i++;
    }
    return !(found);
}

void InitUser (ListUsers *LU, ID *id)
{
    int i;
    char user[20];
    AdrUsers PU;
    char temp[50];
    TANGGAL T;
	JAM J;

    i = 0;
	T.YY = 0;	J.HH = 0;
	T.MM = 0;	J.MM = 0;
	T.DD = 0;	J.SS = 0;
	
    PU = FirstU(*LU);
    strncpy((*id).user.TabKata,CKata.TabKata,CKata.Length);
    (*id).user.Length = CKata.Length;
    strcpy(user,CKata.TabKata);
    user[CKata.Length] = '\0';
    InsVUFirst(LU,user);


    while(i <= 9)
    {
        ADVKATA();
        strncpy(temp,CKata.TabKata,CKata.Length);
        temp[CKata.Length] = '\0';
        if(strcmp(temp,"---") != 0)
        {
            CKata.TabKata[CKata.Length] = '\0';
            (*id).tgl[i].YY = atoi(CKata.TabKata);
            ADVKATA();

            CKata.TabKata[CKata.Length] = '\0';
            (*id).tgl[i].MM = atoi(CKata.TabKata);
            ADVKATA();

            CKata.TabKata[CKata.Length] = '\0';
            (*id).tgl[i].DD = atoi(CKata.TabKata);
            ADVKATA();

            CKata.TabKata[CKata.Length] = '\0';
            (*id).jam[i].HH = atoi(CKata.TabKata);
            ADVKATA();

            CKata.TabKata[CKata.Length] = '\0';
            (*id).jam[i].MM = atoi(CKata.TabKata);
            ADVKATA();

            CKata.TabKata[CKata.Length] = '\0';
            (*id).jam[i].SS = atoi(CKata.TabKata);
            ADVKATA();

            CKata.TabKata[CKata.Length] = '\0';
            strncpy(temp,CKata.TabKata,CKata.Length);
            temp[CKata.Length] = '\0';
            (*id).score[i] = temp;

            if(strcmp((*id).score[i],"---") == 0)
                InsVSLast(LU,PU,T,J,0);
            else
                InsVSLast(LU,PU,(*id).tgl[i],(*id).jam[i],(atoi((*id).score[i])));
            i++;
        }
        else
        {
            InsVSLast(LU,PU,T,J,0);
            (*id).tgl[i].YY = 0;
            (*id).tgl[i].MM = 0;
            (*id).tgl[i].DD = 0;
            (*id).jam[i].HH = 0;
            (*id).jam[i].MM = 0;
            (*id).jam[i].SS = 0;
            i++;
        }
    }
    ADVKATA();
}

void InitUserTime (ID *id, int i)
{
    char temp[50];

        ADVKATA();
        strncpy(temp,CKata.TabKata,CKata.Length);
        temp[CKata.Length] = '\0';
        if(strcmp(temp,"---") != 0)
        {
            CKata.TabKata[CKata.Length] = '\0';
            (*id).tgl[i].YY = atoi(CKata.TabKata);
            ADVKATA();

            CKata.TabKata[CKata.Length] = '\0';
            (*id).tgl[i].MM = atoi(CKata.TabKata);
            ADVKATA();

            CKata.TabKata[CKata.Length] = '\0';
            (*id).tgl[i].DD = atoi(CKata.TabKata);
            ADVKATA();

            CKata.TabKata[CKata.Length] = '\0';
            (*id).jam[i].HH = atoi(CKata.TabKata);
            ADVKATA();

            CKata.TabKata[CKata.Length] = '\0';
            (*id).jam[i].MM = atoi(CKata.TabKata);
            ADVKATA();

            CKata.TabKata[CKata.Length] = '\0';
            (*id).jam[i].SS = atoi(CKata.TabKata);
            ADVKATA();

            i++;
        }
        else
        {
            (*id).tgl[i].YY = 0;
            (*id).tgl[i].MM = 0;
            (*id).tgl[i].DD = 0;
            (*id).jam[i].HH = 0;
            (*id).jam[i].MM = 0;
            (*id).jam[i].SS = 0;
            i++;
        }
}

void InitUserTime1 (ID *id)
{
    char temp[50];
    int i;

    i = 0;
    while(i<=9)
    {
        ADVKATA();
        strncpy(temp,CKata.TabKata,CKata.Length);
        temp[CKata.Length] = '\0';
        if(strcmp(temp,"---") != 0)
        {
            ADVKATA();
            ADVKATA();
            ADVKATA();
            ADVKATA();
            ADVKATA();
            ADVKATA();
        }
        i++;
    }
    ADVKATA();
}


void CheckUser (Kata username, ID *id, boolean *found)
{

    *found = false;
    strncpy((*id).user.TabKata,CKata.TabKata,CKata.Length);
    (*id).user.Length = CKata.Length;
    (*id).user.TabKata[CKata.Length] = '\0';

    if(IsKataSama((*id).user,username))
        *found = true;

    InitUserTime1(id);
}


void SalinFile (ListUsers LU,Kata user)
{
    FILE *fw;
    AdrScores PS;
    AdrUsers PU;
    ID id;
    int i;
	
    *x = "scores/List Users & Highscores 1.txt";
    CreateList(&LU);
    STARTKATA();
    while(!EndKata)
        InitUser(&LU,&id);
    InversListU(&LU);
	
    fw = fopen("scores/List Users & Highscores 1.txt", "r+");

	
    PU = FirstU(LU);
    STARTKATA();
    while(PU != Nil)
    {
        fprintf(fw,"%s | ", InfoU(PU));
        i = 0;
        PS = FirstS(PU);
        while(PS != Nil && i<=9)
        {
            InitUserTime(&id,i);
            if(id.tgl[i].YY != 0)
            {
                fprintf(fw,"%d ", id.tgl[i].YY);
                fprintf(fw,"%d ", id.tgl[i].MM);
                fprintf(fw,"%d ", id.tgl[i].DD);
                fprintf(fw,"%d ", id.jam[i].HH);
                fprintf(fw,"%d ", id.jam[i].MM);
                fprintf(fw,"%d ", id.jam[i].SS);
            }
            i++;

            if(InfoS(PS) == 0)
                fprintf(fw,"--- | ");
            else
                fprintf(fw," %d | ",InfoS(PS));
            PS = NextS(PS);
        }
        fprintf(fw,"\n");
        PU = NextU(PU);
        ADVKATA();
    }
    fprintf(fw,"%s | ", user.TabKata);
    for(i=1;i<=10; i++)
        fprintf(fw,"--- | ");
    fprintf(fw,"\n");
	fprintf(fw,".");
    fclose(fw);
	

	 *x = "scores/List Users & Highscores 2.txt";
  	  CreateList(&LU);
  	  STARTKATA();
   	  while(!EndKata)
  	      InitUser(&LU,&id);
  	  InversListU(&LU);

    fw = fopen("scores/List Users & Highscores 2.txt", "r+");

    PU = FirstU(LU);
    STARTKATA();
    while(PU != Nil)
    {
        fprintf(fw,"%s | ", InfoU(PU));
        i = 0;
        PS = FirstS(PU);
        while(PS != Nil && i<=9)
        {
            InitUserTime(&id,i);
            if(id.tgl[i].YY != 0)
            {
                fprintf(fw,"%d ", id.tgl[i].YY);
                fprintf(fw,"%d ", id.tgl[i].MM);
                fprintf(fw,"%d ", id.tgl[i].DD);
                fprintf(fw,"%d ", id.jam[i].HH);
                fprintf(fw,"%d ", id.jam[i].MM);
                fprintf(fw,"%d ", id.jam[i].SS);
            }
            i++;

            if(InfoS(PS) == 0)
                fprintf(fw,"--- | ");
            else
                fprintf(fw," %d | ",InfoS(PS));
            PS = NextS(PS);
        }
        fprintf(fw,"\n");
       
        PU = NextU(PU);
        ADVKATA();
    }
    fprintf(fw,"%s | ", user.TabKata);
    for(i=1;i<=10; i++)
        fprintf(fw,"--- | ");
    fprintf(fw,"\n");
	fprintf(fw,".");
    fclose(fw);
	

	*x = "scores/List Users & Highscores 3.txt";
  	  CreateList(&LU);
  	  STARTKATA();
   	  while(!EndKata)
  	      InitUser(&LU,&id);
  	  InversListU(&LU);

    fw = fopen("scores/List Users & Highscores 3.txt", "r+");

    PU = FirstU(LU);
    STARTKATA();
    while(PU != Nil)
    {
        fprintf(fw,"%s | ", InfoU(PU));
        i = 0;
        PS = FirstS(PU);
        while(PS != Nil && i<=9)
        {
            InitUserTime(&id,i);
             
            if(id.tgl[i].YY != 0)
            {
                fprintf(fw,"%d ", id.tgl[i].YY);
                fprintf(fw,"%d ", id.tgl[i].MM);
                fprintf(fw,"%d ", id.tgl[i].DD);
                fprintf(fw,"%d ", id.jam[i].HH);
                fprintf(fw,"%d ", id.jam[i].MM);
                fprintf(fw,"%d ", id.jam[i].SS);
            }
            i++;

            if(InfoS(PS) == 0)
                fprintf(fw,"--- | ");
            else
                fprintf(fw," %d | ",InfoS(PS));
            PS = NextS(PS);
        }
        fprintf(fw,"\n");
        
        PU = NextU(PU);
        ADVKATA();
    }
    fprintf(fw,"%s | ", user.TabKata);
    for(i=1;i<=10; i++)
        fprintf(fw,"--- | ");
    fprintf(fw,"\n");
	fprintf(fw,".");
    fclose(fw);


	  *x = "scores/List Users & Highscores 4.txt";
  	  CreateList(&LU);
  	  STARTKATA();
   	  while(!EndKata)
  	      InitUser(&LU,&id);
  	  InversListU(&LU);

    fw = fopen("scores/List Users & Highscores 4.txt", "r+");

    PU = FirstU(LU);
    STARTKATA();
    while(PU != Nil)
    {
        fprintf(fw,"%s | ", InfoU(PU));
        i = 0;
        PS = FirstS(PU);
        while(PS != Nil && i<=9)
        {
            InitUserTime(&id,i);
             
            if(id.tgl[i].YY != 0)
            {
                fprintf(fw,"%d ", id.tgl[i].YY);
                fprintf(fw,"%d ", id.tgl[i].MM);
                fprintf(fw,"%d ", id.tgl[i].DD);
                fprintf(fw,"%d ", id.jam[i].HH);
                fprintf(fw,"%d ", id.jam[i].MM);
                fprintf(fw,"%d ", id.jam[i].SS);
            }
            i++;

            if(InfoS(PS) == 0)
                fprintf(fw,"--- | ");
            else
                fprintf(fw," %d | ",InfoS(PS));
            PS = NextS(PS);
        }
        fprintf(fw,"\n");
      
        PU = NextU(PU);
        ADVKATA();
    }
    fprintf(fw,"%s | ", user.TabKata);
    for(i=1;i<=10; i++)
        fprintf(fw,"--- | ");
    fprintf(fw,"\n");
	fprintf(fw,".");
    fclose(fw);


	  *x = "scores/List Users & Highscores 5.txt";
  	  CreateList(&LU);
  	  STARTKATA();
   	  while(!EndKata)
  	      InitUser(&LU,&id);
  	  InversListU(&LU);

    fw = fopen("scores/List Users & Highscores 5.txt", "r+");

    PU = FirstU(LU);
    STARTKATA();
    while(PU != Nil)
    {
        fprintf(fw,"%s | ", InfoU(PU));
        i = 0;
        PS = FirstS(PU);
        while(PS != Nil && i<=9)
        {
            InitUserTime(&id,i);
             
            if(id.tgl[i].YY != 0)
            {
                fprintf(fw,"%d ", id.tgl[i].YY);
                fprintf(fw,"%d ", id.tgl[i].MM);
                fprintf(fw,"%d ", id.tgl[i].DD);
                fprintf(fw,"%d ", id.jam[i].HH);
                fprintf(fw,"%d ", id.jam[i].MM);
                fprintf(fw,"%d ", id.jam[i].SS);
            }
            i++;

            if(InfoS(PS) == 0)
                fprintf(fw,"--- | ");
            else
                fprintf(fw," %d | ",InfoS(PS));
            PS = NextS(PS);
        }
        fprintf(fw,"\n");
       
        PU = NextU(PU);
        ADVKATA();
    }
    fprintf(fw,"%s | ", user.TabKata);
    for(i=1;i<=10; i++)
        fprintf(fw,"--- | ");
    fprintf(fw,"\n");
	fprintf(fw,".");
    fclose(fw);
	


	  *x = "scores/List Users & Highscores 6.txt";
  	  CreateList(&LU);
  	  STARTKATA();
   	  while(!EndKata)
  	      InitUser(&LU,&id);
  	  InversListU(&LU);

    fw = fopen("scores/List Users & Highscores 6.txt", "r+");

    PU = FirstU(LU);
    STARTKATA();
    while(PU != Nil)
    {
        fprintf(fw,"%s | ", InfoU(PU));
        i = 0;
        PS = FirstS(PU);
        while(PS != Nil && i<=9)
        {
            InitUserTime(&id,i);
             
            if(id.tgl[i].YY != 0)
            {
                fprintf(fw,"%d ", id.tgl[i].YY);
                fprintf(fw,"%d ", id.tgl[i].MM);
                fprintf(fw,"%d ", id.tgl[i].DD);
                fprintf(fw,"%d ", id.jam[i].HH);
                fprintf(fw,"%d ", id.jam[i].MM);
                fprintf(fw,"%d ", id.jam[i].SS);
            }
            i++;

            if(InfoS(PS) == 0)
                fprintf(fw,"--- | ");
            else
                fprintf(fw," %d | ",InfoS(PS));
            PS = NextS(PS);
        }
        fprintf(fw,"\n");
       
        PU = NextU(PU);
        ADVKATA();
    }
    fprintf(fw,"%s | ", user.TabKata);
    for(i=1;i<=10; i++)
        fprintf(fw,"--- | ");
    fprintf(fw,"\n");
	fprintf(fw,".");
    fclose(fw);
	

	  *x = "scores/List Users & Highscores 7.txt";
  	  CreateList(&LU);
  	  STARTKATA();
   	  while(!EndKata)
  	      InitUser(&LU,&id);
  	  InversListU(&LU);	
	
    fw = fopen("scores/List Users & Highscores 7.txt", "r+");

    PU = FirstU(LU);
    STARTKATA();
    while(PU != Nil)
    {
        fprintf(fw,"%s | ", InfoU(PU));
        i = 0;
        PS = FirstS(PU);
        while(PS != Nil && i<=9)
        {
            InitUserTime(&id,i);
             
            if(id.tgl[i].YY != 0)
            {
                fprintf(fw,"%d ", id.tgl[i].YY);
                fprintf(fw,"%d ", id.tgl[i].MM);
                fprintf(fw,"%d ", id.tgl[i].DD);
                fprintf(fw,"%d ", id.jam[i].HH);
                fprintf(fw,"%d ", id.jam[i].MM);
                fprintf(fw,"%d ", id.jam[i].SS);
            }
            i++;

            if(InfoS(PS) == 0)
                fprintf(fw,"--- | ");
            else
                fprintf(fw," %d | ",InfoS(PS));
            PS = NextS(PS);
        }
        fprintf(fw,"\n");
      
        PU = NextU(PU);
        ADVKATA();
    }
    fprintf(fw,"%s | ", user.TabKata);
    for(i=1;i<=10; i++)
        fprintf(fw,"--- | ");
    fprintf(fw,"\n");
	fprintf(fw,".");
    fclose(fw);
	


	  *x = "scores/List Users & Highscores 8.txt";
  	  CreateList(&LU);
  	  STARTKATA();
   	  while(!EndKata)
  	      InitUser(&LU,&id);
  	  InversListU(&LU);

    fw = fopen("scores/List Users & Highscores 8.txt", "r+");

    PU = FirstU(LU);
    STARTKATA();
    while(PU != Nil)
    {
        fprintf(fw,"%s | ", InfoU(PU));
        i = 0;
        PS = FirstS(PU);
        while(PS != Nil && i<=9)
        {
            InitUserTime(&id,i);
             
            if(id.tgl[i].YY != 0)
            {
                fprintf(fw,"%d ", id.tgl[i].YY);
                fprintf(fw,"%d ", id.tgl[i].MM);
                fprintf(fw,"%d ", id.tgl[i].DD);
                fprintf(fw,"%d ", id.jam[i].HH);
                fprintf(fw,"%d ", id.jam[i].MM);
                fprintf(fw,"%d ", id.jam[i].SS);
            }
            i++;

            if(InfoS(PS) == 0)
                fprintf(fw,"--- | ");
            else
                fprintf(fw," %d | ",InfoS(PS));
            PS = NextS(PS);
        }
        fprintf(fw,"\n");
       
        PU = NextU(PU);
        ADVKATA();
    }
    fprintf(fw,"%s | ", user.TabKata);
    for(i=1;i<=10; i++)
        fprintf(fw,"--- | ");
    fprintf(fw,"\n");
	fprintf(fw,".");
    fclose(fw);
	


	  *x = "scores/List Users & Highscores 9.txt";
  	  CreateList(&LU);
  	  STARTKATA();
   	  while(!EndKata)
  	      InitUser(&LU,&id);
  	  InversListU(&LU);

    fw = fopen("scores/List Users & Highscores 9.txt", "r+");

    PU = FirstU(LU);
    STARTKATA();
    while(PU != Nil)
    {
        fprintf(fw,"%s | ", InfoU(PU));
        i = 0;
        PS = FirstS(PU);
        while(PS != Nil && i<=9)
        {
            InitUserTime(&id,i);
             
            if(id.tgl[i].YY != 0)
            {
                fprintf(fw,"%d ", id.tgl[i].YY);
                fprintf(fw,"%d ", id.tgl[i].MM);
                fprintf(fw,"%d ", id.tgl[i].DD);
                fprintf(fw,"%d ", id.jam[i].HH);
                fprintf(fw,"%d ", id.jam[i].MM);
                fprintf(fw,"%d ", id.jam[i].SS);
            }
            i++;

            if(InfoS(PS) == 0)
                fprintf(fw,"--- | ");
            else
                fprintf(fw," %d | ",InfoS(PS));
            PS = NextS(PS);
        }
        fprintf(fw,"\n");
       
        PU = NextU(PU);
        ADVKATA();
    }
    fprintf(fw,"%s | ", user.TabKata);
    for(i=1;i<=10; i++)
        fprintf(fw,"--- | ");
    fprintf(fw,"\n");
	fprintf(fw,".");
    fclose(fw);
	


	  *x = "scores/List Users & Highscores 10.txt";
  	  CreateList(&LU);
  	  STARTKATA();
   	  while(!EndKata)
  	      InitUser(&LU,&id);
  	  InversListU(&LU);


    fw = fopen("scores/List Users & Highscores 10.txt", "r+");

    PU = FirstU(LU);
    STARTKATA();
    while(PU != Nil)
    {
        fprintf(fw,"%s | ", InfoU(PU));
        i = 0;
        PS = FirstS(PU);
        while(PS != Nil && i<=9)
        {
            InitUserTime(&id,i);
             
            if(id.tgl[i].YY != 0)
            {
                fprintf(fw,"%d ", id.tgl[i].YY);
                fprintf(fw,"%d ", id.tgl[i].MM);
                fprintf(fw,"%d ", id.tgl[i].DD);
                fprintf(fw,"%d ", id.jam[i].HH);
                fprintf(fw,"%d ", id.jam[i].MM);
                fprintf(fw,"%d ", id.jam[i].SS);
            }
            i++;

            if(InfoS(PS) == 0)
                fprintf(fw,"--- | ");
            else
                fprintf(fw," %d | ",InfoS(PS));
            PS = NextS(PS);
        }
        fprintf(fw,"\n");
     
        PU = NextU(PU);
        ADVKATA();
    }
    fprintf(fw,"%s | ", user.TabKata);
    for(i=1;i<=10; i++)
        fprintf(fw,"--- | ");
    fprintf(fw,"\n");
	fprintf(fw,".");
    fclose(fw);
}

void SalinInto (ListUsers LU, int x)
{
	FILE *fw;
	AdrScores PS;
    AdrUsers PU;
    int i;
    
    switch (x)
    {
		case 0 :
			 fw = fopen("scores/List Users & Highscores 1.txt", "w");
		case 1 :
			 fw = fopen("scores/List Users & Highscores 2.txt", "w");
		case 2 :
			 fw = fopen("scores/List Users & Highscores 3.txt", "w");
		case 3 :
			 fw = fopen("scores/List Users & Highscores 4.txt", "w");
		case 4 :
			 fw = fopen("scores/List Users & Highscores 5.txt", "w");
		case 5 :
			 fw = fopen("scores/List Users & Highscores 6.txt", "w");
		case 6 :
			 fw = fopen("scores/List Users & Highscores 7.txt", "w");
		case 7 :
			 fw = fopen("scores/List Users & Highscores 8.txt", "w");
		case 8 :
			 fw = fopen("scores/List Users & Highscores 9.txt", "w");
		case 9 :
			 fw = fopen("scores/List Users & Highscores 10.txt", "w");
	}
		
    PU = FirstU(LU);
    while(PU != Nil) {
		fprintf(fw,"%s | ", InfoU(PU));
        i = 0;
        PS = FirstS(PU);
        while(PS != Nil && i<=9)
        {
            if(InfoD(PS).YY != 0)
            {
                fprintf(fw,"%d ", InfoD(PS).YY);
                fprintf(fw,"%d ", InfoD(PS).MM);
                fprintf(fw,"%d ", InfoD(PS).DD);
                fprintf(fw,"%d ", InfoH(PS).HH);
                fprintf(fw,"%d ", InfoH(PS).MM);
                fprintf(fw,"%d ", InfoH(PS).SS);
            }
            i++;

            if(InfoS(PS) == 0)
                fprintf(fw,"--- | ");
            else
                fprintf(fw," %d | ",InfoS(PS));
            PS = NextS(PS);
		}
		fprintf(fw,"\n");
        printf("\n");
        PU = NextU(PU);
	}
	fprintf(fw,".");
	fclose(fw);
}

void HowToPlay()
{
 	system("clear");
    	printf("=================NAVIGATION BUTTON==================\n");
	printf("Q : Move Cursor Up-Left Direction\n");
	printf("W : Move Cursor Up Direction\n");
	printf("E : Move Cursor Up-Right Direction\n");
	printf("A : Move Cursor Right Direction\n");
	printf("D : Move Cursor Left Direction\n");
	printf("Z : Move Cursor Down-Left Direction\n");
	printf("X : Move Cursor Down Direction\n");
	printf("C : Move Cursor Down-Right Direction\n\n");
	printf("=================PROCESSING BUTTON================\n");
	printf("R : Rotate the Board Clockwise\n");
	printf("S : Press it once to start selecting the character \n");
	printf("    with the cursor using navigation button.\n");
	printf("    Press it again to stop selecting the character\n");

	printf("M : Back to the Menu\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
    	printf("%sPress any key to continue%s",magenta,cyan);
	getch();
	getch();
}
