/*NIM/Nama : 13513023 / Alexander Sukono
Nama file : P08135130231.c
Topik : List Linier
Tanggal : 30 Oktober 2014
Deskripsi : Body ADT List Linier Berkait
*/

#include "multilist.h"
#include <stdio.h>
#include <string.h>



void CreateList (ListUsers *LU)
{
	FirstU(*LU) = Nil;
}


bool IsListEmpty(ListUsers LU)
{
	return (FirstU(LU) == Nil);
}

bool IsListSEmpty(ListUsers LU, AdrUsers PU)
{
    PU = FirstU(LU);
	return (FirstS(PU) == Nil);
}

AdrUsers AlokasiU (char X[20])
{
    AdrUsers PU;

    PU = (AdrUsers) malloc (sizeof(EUsers));
    if(PU != Nil)
    {
        strcpy(InfoU(PU), X);
        FirstS(PU) = Nil;
        NextU(PU) = Nil;
    }
    else

        PU = Nil;

    return PU;
}

AdrScores AlokasiS (TANGGAL T, JAM J, int X)
{
	AdrScores PS;

    PS = (AdrScores) malloc (sizeof(Scores));
    if(PS != Nil)
    {
        InfoS(PS) = X;
		InfoD(PS).YY = T.YY;
		InfoD(PS).MM = T.MM;
		InfoD(PS).DD = T.DD;
		InfoH(PS).HH = J.HH;
		InfoH(PS).MM = J.MM;
		InfoH(PS).SS = J.SS;
        NextS(PS) = Nil;
    }
    else
        PS = Nil;

	return PS;
}

void DealokasiU (AdrUsers *PU)
{
    free(*PU);
}

void DealokasiS (AdrScores *PS)
{
    free(*PS);
}

void ListUsersLengkap (ListUsers LU)
{
	AdrUsers PU;
	AdrScores PS;


	if(!IsListEmpty(LU))
	{
	    PU = FirstU(LU);
		while(PU != Nil)
		{
			printf("------- %s --------\n", InfoU(PU));
			PS = FirstS(PU);
			while(PS != Nil)
			{
				printf("%d ", InfoS(PS));
				PS = NextS(PS);
			}
			PU = NextU(PU);
			printf("\n\n");
		}
	}
	else
		printf("No user registered\n");
}

AdrUsers Search (ListUsers LU, char X[20])
{
	AdrUsers PU;

	PU = FirstU(LU);
	while ((PU != Nil)&&(InfoU(PU) != X))
		PU = NextU(PU);
	return PU;
}

void InsertFirstU (ListUsers *LU, AdrUsers PU)
{
	NextU(PU) = FirstU(*LU);
    FirstU(*LU) = PU;
}

void InsertFirstS (ListUsers *LU, AdrUsers PU, AdrScores PS)
{
	PU = FirstU(*LU);
    NextS(PS) = FirstS(PU);
    FirstS(PU) = PS;
}

void InsertSAfter (ListUsers *LU,AdrScores PS, AdrScores Prec)
{
    NextS(PS) = NextS(Prec);
    NextS(Prec) = PS;
}

void InsertSLast (ListUsers *LU, AdrUsers PU,AdrScores PS)
{
    AdrScores Last;

    if(IsListSEmpty(*LU,PU))
        InsertFirstS(LU,PU,PS);
    else
    {
        PU = FirstU(*LU);
        Last = FirstS(PU);
        while(NextS(Last) != Nil)
            Last = NextS(Last);
        InsertSAfter(LU,PS,Last);
    }
}

void InsVSLast (ListUsers *LU, AdrUsers PU, TANGGAL T, JAM J, int X)
{
    AdrScores PS;

    PS = AlokasiS(T,J,X);
    if(PS != Nil)
        InsertSLast(LU,PU,PS);
}

void InsVSAfter (ListUsers *LU, AdrUsers PU, AdrScores Last, TANGGAL T,JAM J,int X)
{
   AdrScores PS, P;

   PS = AlokasiS(T,J,X);
   if(PS != Nil)
   {
		P = FirstS(PU);
		while (P != Last) {
			P = NextS(P);
		}
		InsertSAfter(LU, PS, P);
	}
}

void InsVUFirst (ListUsers *LU, char X[20])
{
    AdrUsers PU;

    PU = AlokasiU(X);
    if(PU != Nil)
        InsertFirstU(LU,PU);
}

void InsVSFirst (ListUsers *LU,AdrUsers PU, TANGGAL T, JAM J, int X)
{
    AdrScores PS;

    PS = AlokasiS(T,J,X);
    if(PS != Nil)
        InsertFirstS(LU,PU,PS);
}

void DeleteFirstU (ListUsers *LU, AdrUsers *PU)
{
    *PU = FirstU(*LU);
    FirstU(*LU) = NextU(FirstU(*LU));
}

void DeleteLastS(ListUsers *LU, AdrUsers PU, AdrScores *PS)
{
	AdrScores Last;

	Last = FirstS(PU);
	while (NextS(Last)!=Nil)
		Last = NextS(Last);
	*PS = Last;
	DealokasiS (&Last);
}

void DeleteFirstS (ListUsers *LU,AdrUsers PU, AdrScores *PS)
{
    PU = FirstU(*LU);
	*PS = FirstS(PU);
    FirstS(PU) = NextS(FirstS(PU));
}

void CopyList (ListUsers *L1, ListUsers *L2)
{
    FirstU(*L2) = FirstU(*L1);
}

void CopyListS (ListUsers *LU,AdrUsers *L1, AdrUsers *L2)
{
    *L2 = FirstU(*LU);
    *L1 = FirstU(*LU);
    FirstS(*L2) = FirstS(*L1);
}

void InversListU (ListUsers *LU)
{
	AdrUsers PU;
	ListUsers LI;

	CreateList(&LI);
	while (!IsListEmpty(*LU)){
		DeleteFirstU(LU,&PU);
		InsertFirstU(&LI,PU);
	}
	CopyList(&LI,LU);
}

int NbElmtS(AdrUsers PU)
{
	AdrScores PS;
	int i;

	PS = FirstS(PU);
	i = 1;
	while (NextS(PS)!=Nil)
	{
		PS = NextS(PS);
		i = i+1;
	}
	return i;
}

void InsSortScoreU (ListUsers *LU,TANGGAL T,JAM J,int X,Kata user)
{
	AdrUsers PU;
	AdrScores PS,PD,Last;
	int i;

	i = 1;
	PU = FirstU(*LU);
	while (strcmp(user.TabKata, InfoU(PU)) != 0) {
		PU = NextU(PU);
	}
	PS = AlokasiS(T,J,X);
	PD = FirstS(PU);
if (PS!=Nil)
{
	if (X>InfoS(PD)) {
		NextS(PS) = FirstS(PU);
		FirstS(PU) = PS;
	}
	else
	{
	while(X<=InfoS(PD) && i<=10)
	{
		if (X==InfoS(PD))
		{
			if (T.YY<InfoD(PD).YY)
			{
				InsertSAfter (LU,PS,PD);
				break;
			}
			else if (T.YY==InfoD(PD).YY)
			{
				if (T.MM<InfoD(PD).MM)
				{
					InsertSAfter (LU,PS,PD);
					break;
				}
				else if (T.MM==InfoD(PD).MM)
				{
					if (T.DD<InfoD(PD).DD)
					{
						InsertSAfter (LU,PS,PD);
						break;
					}
					else if (T.DD==InfoD(PD).DD)
					{
						if (J.HH<InfoH(PD).HH)
						{
							InsertSAfter (LU,PS,PD);
							break;
						}
						else if (J.HH==InfoH(PD).HH)
						{
							if (J.MM<InfoH(PD).MM)
							{
								InsertSAfter (LU,PS,PD);
								break;
							}
							else if (J.MM==InfoH(PD).MM)
							{
								if (J.SS<=InfoH(PD).SS)
								{
									InsertSAfter (LU,PS,PD);
									break;
								}
							}
						}
					}
				}
			}
		}
		i = i+1;
		if (X<=InfoS(NextS(PD)))
			PD = NextS(PD);
		else
		{
			InsertSAfter (LU,PS,PD);
			break;
		}
	}
	}
	if (NbElmtS(PU)>10)
	{
		DeleteLastS(LU, PU, &Last);
	}
}
}

void ViewMyHighScores(ListUsers LU, Kata user)
{
	AdrUsers PU;
	int i;

	PU = FirstU(LU);
	
	while (strcmp(InfoU(PU),user.TabKata)!=0)
		PU = NextU(PU);
printf("=====================================================================\n");
	printf("nama 	: %s\n",InfoU(PU));
	printf("tanggal : %d:%d:%d\n",InfoD(FirstS(PU)).YY,InfoD(FirstS(PU)).MM,InfoD(FirstS(PU)).DD);
	printf("waktu 	: %d:%d:%d\n",InfoH(FirstS(PU)).HH,InfoH(FirstS(PU)).MM,InfoH(FirstS(PU)).SS);
	printf("score	: %d\n",InfoS(FirstS(PU)));
printf("=====================================================================\n");
}


int IndexMin(ArrayScores AS)
{
	int min, i;
	
	min = 1;
	for (i=1; i<=10; i++) {
		if (AS[i].score<AS[min].score)
				{
					min = i;
				}
				else if (AS[i].score==AS[min].score)
				{
					if (AS[i].date.YY<AS[min].date.YY)
					{
						min = i;
					}
					else if (AS[i].date.YY==AS[min].date.YY)
					{
						if (AS[i].date.MM<AS[min].date.MM)
						{
							min = i;
						}
						else if (AS[i].date.MM==AS[min].date.MM)
						{
							if (AS[i].date.DD<AS[min].date.DD)
							{
								min = i;
							}
							else if (AS[i].date.DD==AS[min].date.DD)
							{
								if (AS[i].hour.HH<AS[min].hour.HH)
								{
									min = i;
								}
								else if (AS[i].hour.HH==AS[min].hour.HH)
								{
									if (AS[i].hour.MM<AS[min].hour.MM)
									{
										min = i;
									}
									else if (AS[i].hour.MM==AS[min].hour.MM)
									{
										if (AS[i].hour.SS<AS[min].hour.SS)
										{
											min = i;
										}
									}
								}
							}
						}
					}
				}
	}
	
	return min;
}

int IndexMax(ArrayScores AS)
{
	int max, i;
	
	max = 1;
	for (i=1; i<=10; i++) {
		if (AS[i].score>AS[max].score)
				{
					max = i;
				}
				else if (AS[i].score==AS[max].score)
				{
					if (AS[i].date.YY>AS[max].date.YY)
					{
						max = i;
					}
					else if (AS[i].date.YY==AS[max].date.YY)
					{
						if (AS[i].date.MM>AS[max].date.MM)
						{
							max = i;
						}
						else if (AS[i].date.MM==AS[max].date.MM)
						{
							if (AS[i].date.DD>AS[max].date.DD)
							{
								max = i;
							}
							else if (AS[i].date.DD==AS[max].date.DD)
							{
								if (AS[i].hour.HH>AS[max].hour.HH)
								{
									max = i;
								}
								else if (AS[i].hour.HH==AS[max].hour.HH)
								{
									if (AS[i].hour.MM>AS[max].hour.MM)
									{
										max = i;
									}
									else if (AS[i].hour.MM==AS[max].hour.MM)
									{
										if (AS[i].hour.SS>AS[max].hour.SS)
										{
											max = i;
										}
									}
								}
							}
						}
					}
				}
	}
	
	return max;
}

void ViewAllHighScores(ListUsers LU)
{

	AdrUsers PU;
	AdrScores PS;
	ArrayScores AS, temp;
	int i,j,n, idxmin;
	
	for (i=1; i<=10; i++) {
		strcpy(AS[i].username, "---");
		AS[i].score = 0;
		AS[i].date.YY = 0;
		AS[i].date.MM = 0;
		AS[i].date.DD = 0;
		AS[i].hour.HH = 0;
		AS[i].hour.MM = 0;
		AS[i].hour.SS = 0;
	}
	
	PU = FirstU(LU);
	i = 1;
	while (PU != Nil && i <= 10) {
		PS = FirstS(PU);
		while (InfoD(PS).YY != 0 && i <= 10) {
			strcpy(AS[i].username, InfoU(PU));
			AS[i].score = InfoS(PS);
			AS[i].date = InfoD(PS);
			AS[i].hour = InfoH(PS);
			i = i+1;
			PS = NextS(PS);
		}
		if(InfoS(PS) == 0) {
			PU = NextU(PU);
		}
	}
	
	while (PU != Nil) {
		while (InfoD(PS).YY != 0) {
			if (InfoS(PS)>AS[IndexMin(AS)].score)
			{
				strcpy(AS[IndexMin(AS)].username, InfoU(PU));
				AS[IndexMin(AS)].score = InfoS(PS);
				AS[IndexMin(AS)].date = InfoD(PS);
				AS[IndexMin(AS)].hour = InfoH(PS);
			}
				else if (InfoS(PS)==AS[IndexMin(AS)].score)
				{
					if (InfoD(PS).YY>AS[IndexMin(AS)].date.YY)
					{
						strcpy(AS[IndexMin(AS)].username, InfoU(PU));
						AS[IndexMin(AS)].score = InfoS(PS);
						AS[IndexMin(AS)].date = InfoD(PS);
						AS[IndexMin(AS)].hour = InfoH(PS);
					}
					else if (InfoD(PS).YY==AS[IndexMin(AS)].date.YY)
					{
						if (InfoD(PS).MM>AS[IndexMin(AS)].date.MM)
						{
							strcpy(AS[IndexMin(AS)].username, InfoU(PU));
							AS[IndexMin(AS)].score = InfoS(PS);
							AS[IndexMin(AS)].date = InfoD(PS);
							AS[IndexMin(AS)].hour = InfoH(PS);
						}
						else if (InfoD(PS).MM==AS[IndexMin(AS)].date.MM)
						{
							if (InfoD(PS).DD>AS[IndexMin(AS)].date.DD)
							{
								strcpy(AS[IndexMin(AS)].username, InfoU(PU));
								AS[IndexMin(AS)].score = InfoS(PS);
								AS[IndexMin(AS)].date = InfoD(PS);
								AS[IndexMin(AS)].hour = InfoH(PS);
							}
							else if (InfoD(PS).DD==AS[IndexMin(AS)].date.DD)
							{
								if (InfoH(PS).HH>AS[IndexMin(AS)].hour.HH)
								{
									strcpy(AS[IndexMin(AS)].username, InfoU(PU));
									AS[IndexMin(AS)].score = InfoS(PS);
									AS[IndexMin(AS)].date = InfoD(PS);
									AS[IndexMin(AS)].hour = InfoH(PS);
								}
								else if (InfoH(PS).HH==AS[IndexMin(AS)].hour.HH)
								{
									if (InfoH(PS).MM>AS[IndexMin(AS)].hour.MM)
									{
										strcpy(AS[IndexMin(AS)].username, InfoU(PU));
										AS[IndexMin(AS)].score = InfoS(PS);
										AS[IndexMin(AS)].date = InfoD(PS);
										AS[IndexMin(AS)].hour = InfoH(PS);
									}
									else if (InfoH(PS).MM==AS[IndexMin(AS)].hour.MM)
									{
										if (InfoH(PS).SS>AS[IndexMin(AS)].hour.SS)
										{
											strcpy(AS[IndexMin(AS)].username, InfoU(PU));
											AS[IndexMin(AS)].score = InfoS(PS);
											AS[IndexMin(AS)].date = InfoD(PS);
											AS[IndexMin(AS)].hour = InfoH(PS);
										}
									}
								}
							}
						}
					}
				}
			PS = NextS(PS);
		}
		PU = NextU(PU);
		if (PU != Nil) {
			PS = FirstS(PU);
		}
	}
	
	for (i=1; i<=10; i++) {
		strcpy(temp[i].username, AS[i].username);
		temp[i].score = AS[i].score;
		temp[i].date = AS[i].date;
		temp[i].hour = AS[i].hour;
	}
	
	for (i=1; i<=10; i++) {
		j = IndexMax(temp);
		strcpy(AS[i].username, temp[j].username);
		AS[i].score = temp[j].score;
		AS[i].date = temp[j].date;
		AS[i].hour = temp[j].hour;
		
		
		temp[j].score = 0;
		strcpy(temp[j].username, "---");
		temp[j].date.YY = 0;
		temp[j].date.MM = 0;
		temp[j].date.DD = 0;
		temp[j].hour.HH = 0;
		temp[j].hour.MM = 0;
		temp[j].hour.SS = 0;
	}
	printf("=====================================================================\n");
	printf("Nama           Score           Waktu           Tanggal\n");
	for(i=1;i<=10;i++)
	{
		printf("%s             %d           %d:%d:%d        %d-%d-%d\n",AS[i].username,AS[i].score,AS[i].hour.HH,AS[i].hour.MM,AS[i].hour.SS,AS[i].date.DD,AS[i].date.MM,AS[i].date.YY);
	}
	printf("=====================================================================\n");
}

