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

struct first
{
	int array[57];	
};

struct first firstarr[51];

struct follow{
	int array[58];
};

struct follow followarr[51];

void calculateFirst(char * filename){
	int p = 0;
	for(p=0;p<51;p++){
		int j = 0;
		for(j=0;j<57;j++){
			firstarr[p].array[j] = -1;
		}
	}
	// int cnt1 = 0;
	// int cnt2 = 100;
	int q = 0;
	// while(cnt1 != cnt2)
	for(q=0;q<100;q++)
	{
		// cnt2--;
		// printf("%d\n", cnt1);
		// cnt2 = cnt1;
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
				// printf("%s %d\n", pch, getTokenId("ID"));
				RHS[n] = getTokenId(pch);
				pch = strtok(NULL," ");
				n++;
			}
			// printf("iteration num %d rule num %d %s \n", q, i, grammar[i]);
			// printf("%s %d\n", idtotkstr(LHS),n);
			if (RHS[0] < 100 && RHS[0] > 0)
			{
				// printf(" yo\n");
				if (firstarr[LHS-101].array[RHS[0]] != 1)
				{
					cnt1++;
				}
				firstarr[LHS-101].array[RHS[0]] = 1;
				continue;
			}
			if (n == 1 && RHS[0] == 0)
			{
				// printf("yo %d %d\n",LHS-101,RHS[0]);///////////////////////
				if (firstarr[LHS-101].array[RHS[0]] != 1)
				{
					cnt1++;
				}
				firstarr[LHS-101].array[RHS[0]] = 1;
				// printf("%d\n", firstarr[LHS-101].array[RHS[0]]);
				continue;
			}
			int k;
			int flag = 1;
			// int zupata = 0;
			// printf("%d\n", RHS[0]);
			for(k=0;k<n && flag == 1;k++){
				if (RHS[k] > 100)
				{
					// printf("yo\n");
					if (firstarr[RHS[k]-101].array[0] == 1)
					{
						flag = 1;
					}
					else
					{
						flag = 0;
					}
					int l = 1;
					for(l=1;l<57;l++){
						if (firstarr[RHS[k]-101].array[l] == 1)
						{
							if (firstarr[LHS-101].array[l] != 1)
							{
								cnt1++;
							}
							firstarr[LHS-101].array[l] = 1;
							// cnt1++;
						}
					}
				}
				else
				{
					if (firstarr[LHS-101].array[RHS[k]] != 1)
					{
						cnt1++;
					}
					firstarr[LHS-101].array[RHS[k]] = 1;
					// zupata = 1;
					// cnt1++;
					break;
				}
			}
			if (k == n && flag == 1)
			{
				if (firstarr[LHS-101].array[0] != 1)
				{
					cnt1++;
				}
				firstarr[LHS-101].array[0] = 1;
			}
		}
	}
	FILE * fp = fopen(filename,"w");
	int j;
	for(j=0;j<51;j++){
		fprintf(fp,"%s ", idtotkstr(j+101));
		int k = 0;
		for(k=0;k<57;k++){
			if (firstarr[j].array[k] == 1)
			{
				fprintf(fp,"%s ", idtotkstr(k));
			}
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}

void calculatefollow(char * filename){
	int i;
	for(i=0;i<51;i++){
		// followarr[i].flag = 0;
		// followarr[i].counter = 0;
		int j = 0;
		for(j=0;j<58;j++){
			followarr[i].array[j] = -1;
		}
	}
	int cnt1 = 0;
	int cnt2 = 100;
	int q = 0;
	followarr[38].array[57] = 1;
	// while(cnt1 != cnt2)
	for(q=0;q<100;q++)
	{
		// cnt2--;
		// printf("%d\n", cnt1);
		cnt2 = cnt1;
		int i = 0;
		for(i=0;i<94;i++){
			// printf("%s\n", grammar[i]);////////////////////////////////////////

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
				// printf("%s %d\n", pch, getTokenId("ID"));
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
							followarr[RHS[j]-101].array[RHS[k]] = 1;
							break;
						}
						else
						{
							int r = 0;
							for(r=1;r<57;r++){
								if (followarr[RHS[j]-101].array[r] != 1)
								{
									followarr[RHS[j]-101].array[r] = firstarr[RHS[k]-101].array[r];
								}
								// followarr[RHS[j]-101].array[r] = firstarr[RHS[k]-101].array[r];
							}
							if ( firstarr[RHS[k]-101].array[0] == 1 )
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
						for(w=0;w<58;w++){
							if (followarr[RHS[j]-101].array[w] != 1)
							{
								followarr[RHS[j]-101].array[w] = followarr[LHS-101].array[w];
							}
							// followarr[RHS[j]-101].array[w] = followarr[LHS-101].array[w];
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
				for(w=0;w<58;w++){
					if (followarr[RHS[j]-101].array[w] != 1)
					{
						followarr[RHS[j]-101].array[w] = followarr[LHS-101].array[w];
					}
					// followarr[RHS[j]-101].array[w] = followarr[LHS-101].array[w];
				}
			}
			// printf("iteration num %d rule num %d %s \n", q, i, grammar[i]);
			// printf("%s %d\n", idtotkstr(LHS),n);
			
		}
	}
	FILE * fp1 = fopen(filename,"w");
	int j= 0;
	for(j=0;j<51;j++){
		fprintf(fp1,"%s ", idtotkstr(j+101));
		int k = 0;
		for(k=0;k<58;k++){
			if (followarr[j].array[k] == 1)
			{
				fprintf(fp1,"%s ", idtotkstr(k));
			}
		}
		fprintf(fp1,"\n");
	}
	fclose(fp1);
}
