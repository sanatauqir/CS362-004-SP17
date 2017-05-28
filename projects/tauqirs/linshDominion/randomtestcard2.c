#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int p,r,i;
	
    printf("Running Random Card Test for Adventure\n");
    for (i = 1; i < 2000; i++) {
		int seed = rand() * 1000;
		memset(&G, 23, sizeof(struct gameState)); 
		memset(&testG, 23, sizeof(struct gameState)); 
		r = initializeGame(2, k, seed, &G);
		p = floor(Random() * 2);
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		int position = floor(Random() * G.handCount[p]);
		G.hand[p][position] = village;
		memcpy(&testG, &G, sizeof(struct gameState));
		r = cardEffect(village, 0,0,0,&G, 0,0);
		if (r<0){
			printf("TEST %d of return value FAILED\n", i);
		}
		
		printf("hand count = %d, expected = %d\n", G.handCount[p], testG.handCount[p] + 1);
		printf("deck count = %d, expected = %d\n", G.deckCount[p], testG.deckCount[p] - 1);
		printf("numActions = %d, expected = %d\n", G.numActions, testG.numActions+2);
		if ((G.handCount[p] != testG.handCount[p]+1) && (G.handCount[p] != testG.handCount[p]-1)){
			printf ("TEST %d FAILED\n",i);
		}
		else
			printf ("TEST %d PASSED\n",i);
		printf("Testing for other players hand count\n");		
		if (p == 0){
			printf("hand count = %d, expected = %d\n", G.handCount[p+1], 0);	
			if (G.handCount[p+1] == 0){
				printf("TEST of other player PASSED\n");}
else
			printf ("TEST of other player FAILED \n");
		}	
		else if (p==1){
			printf("hand count = %d, expected = %d\n", G.handCount[p-1], 0);
			if (G.handCount[p-1] == 0){
				printf("TEST of other player PASSED\n");}	
else
			printf ("TEST of other player FAILED\n");
		}
			

	}
	return 0;
}