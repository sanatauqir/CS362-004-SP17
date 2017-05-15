/*
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
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

int main() {
    int j, r;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int v[3] = {estate, province, duchy};
			
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	printf("---------TESTING SMITHY---------\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	r = cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("checking that the function returned okay\n");
	asserttrue(r,0);
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 3);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);
	asserttrue(testG.handCount[thisPlayer],G.handCount[thisPlayer] +3);
	asserttrue(testG.deckCount[thisPlayer],G.deckCount[thisPlayer] -3);
	
	//no state change for other players
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
		printf("victory supply count = $d, expected = %d\n", testG.supplyCount[v[j]], G.supplyCount[v[j]]);
		asserttrue(testG.supplyCount[v[j]],G.supplyCount[v[j]]);
	}
	printf("SUCCESSFUL COMPLETION OF SMITHY TESTING\n\n");
	return 0;
	
	
}
	
