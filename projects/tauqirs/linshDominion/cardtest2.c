	/*
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int asserttrue(int x, int y){
	if (x == y){
		printf("TEST PASSED\n");
		return 0;}
	else{
		printf("TEST FAILED\n");
		return 0;}
}

int assertgreater(int x, int y){
	if (x > y){
		printf("TEST PASSED\n");
		return 0;}
	else{
		printf("TEST FAILED\n");
		return 0;}
}


int main() {
    int i, j, r;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int v[3] = {estate, province, duchy};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	printf("---------TESTING ADVENTURER---------\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	r = cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2);
	
	printf("hand count increase:");
	asserttrue(testG.handCount[thisPlayer],G.handCount[thisPlayer] +2);	
	printf("deck count increase:");
	asserttrue(testG.deckCount[thisPlayer],G.deckCount[thisPlayer] -2);
	int treasure =0;
	//testing that there are at least 2 treasure cards in this players hand
	for (i=0; i < testG.handCount[thisPlayer]; i++){
		int x = testG.hand[thisPlayer][i];
		if (x == copper || x==silver || x==gold )
			treasure++;
	}
	assertgreater(treasure, 1);
	printf("checking that the function returned okay\n");
	asserttrue(r,0);
	
	//no state change for other players
	printf("TESTING NO STATE CHANGE FOR OTHER PLAYERS\n");
	int otherPlayer = 1;
	printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
	printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
	asserttrue(testG.handCount[otherPlayer],G.handCount[otherPlayer]);
	asserttrue(testG.deckCount[otherPlayer],G.deckCount[otherPlayer]);
	//no state change to victory and kingdom cards
	
	printf("TESTING NO CHANGE IN KINGDOM CARDS\n");
	for (j=0;j<10; j++){
		printf("supply count = %d, expected = %d\n", testG.supplyCount[k[j]], G.supplyCount[k[j]]);
		asserttrue(testG.supplyCount[k[j]],G.supplyCount[k[j]]);
	}
	printf("TESTING NO CHANGE IN VICTORY CARDS\n");
	for (j=0; j <= 3; j++){
		printf("victory supply count = %d, expected = %d\n", testG.supplyCount[v[j]], G.supplyCount[v[j]]);
		asserttrue(testG.supplyCount[v[j]],G.supplyCount[v[j]]);
	}
	printf("TESTING FOR DISCARDED DRAWN CARDS\n");
	printf("hand count = %d, expected = %d\n", testG.handCount[0], G.handCount[0]);
	asserttrue(testG.handCount[0], G.handCount[0]);
	
	printf("testing that gold cards are counted\n");
	/*Re-factoring for gold cards being counted*/
	memcpy(&testG, &G, sizeof(struct gameState));
	r = cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	for (j=0; j <5;j++){
		if (j < 3){
			G.hand[thisPlayer][j] = copper;
		}
		if (j==4){
			G.hand[thisPlayer][j] = adventurer;
		}
		else{
			G.hand[thisPlayer][j] = gold;
		}
	}
	for (i=0; i < testG.handCount[thisPlayer]; i++){
		int x = testG.hand[thisPlayer][i];
		if (x == copper || x==silver || x==gold )
			treasure++;
	}
	printf("treasure in hand= %d, expected = %d\n", treasure, 4);
	asserttrue(treasure, 4);
	
	printf("SUCCESSFUL COMPLETION OF ADVENTURER TESTING\n\n");
	return 0;
	
	
}
	
