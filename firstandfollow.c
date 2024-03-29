/*
Batch No 11
Nishant Bansal	2014A7PS052P
Subham Kumar	2014A7PS121P
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parserDef.h"
#include "utility.h"

//'rows' rows corresponding to all non terminals in the grammar
//'columns' columns corresponding to all terminals in the grammar except $
int firstArray[rows][columns];

//'rows' rows corresponding to all non terminal in the grammar
//columns+1 columns corresponding to all terminals in the grammar
int followArray[rows][columns+1];

//calculateFirst takes input the file name uses the grammar defined in parser.c
//to create first dets in the file passed to it
void calculateFirst(char * filename){
	int p = 0;
	for(p=0;p<rows;p++){
		int j = 0;
		for(j=0;j<columns;j++){
			firstArray[p][j] = -1;
		}
	}
	int cnt1 = 0;
	int cnt2 = 100;
	while(cnt1 != cnt2)
	{
		cnt2 = cnt1;
		int i = 0;
		for(i=0;i<94;i++){
			char tempbuffer[90];
			memset(tempbuffer, 90, '\0');
			strcpy(tempbuffer,grammar[i]);
			char * pch;
			pch = strtok(tempbuffer," ");
			int LHS = getTokenId(pch);
			int RHS[100] = {-1};
			int n = 0;
			pch = strtok(NULL," ");
			while(pch != NULL){
				RHS[n] = getTokenId(pch);
				pch = strtok(NULL," ");
				n++;
			}
			if (RHS[0] < 100 && RHS[0] > 0)
			{
				if (firstArray[LHS-101][RHS[0]] != 1)
				{
					cnt1++;
				}
				firstArray[LHS-101][RHS[0]] = 1;
				continue;
			}
			if (n == 1 && RHS[0] == 0)
			{
				if (firstArray[LHS-101][RHS[0]] != 1)
				{
					cnt1++;
				}
				firstArray[LHS-101][RHS[0]] = 1;
				continue;
			}
			int k;
			int flag = 1;
			for(k=0;k<n && flag == 1;k++){
				if (RHS[k] > 100)
				{
					if (firstArray[RHS[k]-101][0] == 1)
					{
						flag = 1;
					}
					else
					{
						flag = 0;
					}
					int l = 1;
					for(l=1;l<columns;l++){
						if (firstArray[RHS[k]-101][l] == 1)
						{
							if (firstArray[LHS-101][l] != 1)
							{
								cnt1++;
							}
							firstArray[LHS-101][l] = 1;
						}
					}
				}
				else
				{
					if (firstArray[LHS-101][RHS[k]] != 1)
					{
						cnt1++;
					}
					firstArray[LHS-101][RHS[k]] = 1;
					break;
				}
			}
			if (k == n && flag == 1)
			{
				if (firstArray[LHS-101][0] != 1)
				{
					cnt1++;
				}
				firstArray[LHS-101][0] = 1;
			}
		}
	}
	FILE * fp = fopen(filename,"w");
	int j;
	for(j=0;j<rows;j++){
		fprintf(fp,"%s ", idtotkstr(j+101));
		int k = 0;
		for(k=0;k<columns;k++){
			if (firstArray[j][k] == 1)
			{
				fprintf(fp,"%s ", idtotkstr(k));
			}
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}

//calculateFollow takes input the filename and uses the grammar defined in parser.c
//to crate the follow sets in the file
void calculatefollow(char * filename){
	int i;
	for(i=0;i<rows;i++){
		int j = 0;
		for(j=0;j<columns+1;j++){
			followArray[i][j] = -1;
		}
	}
	int cnt1 = 0;
	int cnt2 = 100;
	followArray[38][57] = 1;
	//include $ in 'program' follow
	while(cnt1 != cnt2)
	{
		cnt2 = cnt1;
		int i = 0;
		for(i=0;i<94;i++){
			char tempbuffer[90];
			memset(tempbuffer, 90, '\0');
			strcpy(tempbuffer,grammar[i]);
			char * pch;
			pch = strtok(tempbuffer," ");
			int LHS = getTokenId(pch);
			int RHS[100] = {-1};
			int n = 0;
			pch = strtok(NULL," ");
			while(pch != NULL){
				RHS[n] = getTokenId(pch);
				pch = strtok(NULL," ");
				n++;
			}
			int j;
			for(j=0;j<n-1;j++){
				if (RHS[j] < 100)
				{
					continue;
				}
				else
				{
					int zupata = 0;
					int k = j+1;
					for(k;k<n;k++){
						if (RHS[k] < 100 && RHS[k] > 0)
						{
							if (followArray[RHS[j]-101][RHS[k]] != 1)
							{
								cnt1++;
							}
							followArray[RHS[j]-101][RHS[k]] = 1;
							break;
						}
						else
						{
							int r = 0;
							for(r=1;r<columns;r++){
								if (followArray[RHS[j]-101][r] != 1)
								{
									if (firstArray[RHS[k]-101][r] == 1)
									{
										cnt1++;
									}
									followArray[RHS[j]-101][r] = firstArray[RHS[k]-101][r];
								}
							}
							if ( firstArray[RHS[k]-101][0] == 1 )
							{
								zupata = 1;
								continue;
							}
							else
							{
								break;
							}
						}
					}
					if (k == n && zupata == 1 && RHS[n-1] > 100)
					{
						int w = 0;
						for(w=0;w<columns+1;w++){
							if (followArray[RHS[j]-101][w] != 1)
							{
								if (followArray[LHS-101][w] == 1)
								{
									cnt1++;
								}
								followArray[RHS[j]-101][w] = followArray[LHS-101][w];
							}
						}
					}
				}
			}
			if (RHS[n-1] < 100)
			{
				continue;
			}
			else
			{
				int w = 0;
				for(w=0;w<columns+1;w++){
					if (followArray[RHS[j]-101][w] != 1)
					{
						if (followArray[LHS-101][w] == 1)
						{
							cnt1++;
						}
						followArray[RHS[j]-101][w] = followArray[LHS-101][w];
					}
				}
			}
		}
	}
	FILE * fp1 = fopen(filename,"w");
	int j= 0;
	for(j=0;j<rows;j++){
		fprintf(fp1,"%s ", idtotkstr(j+101));
		int k = 0;
		for(k=0;k<columns+1;k++){
			if (followArray[j][k] == 1)
			{
				fprintf(fp1,"%s ", idtotkstr(k));
			}
		}
		fprintf(fp1,"\n");
	}
	fclose(fp1);
}
