/*
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
    int r;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int v[3] = {estate, province, duchy};
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	printf("---------TESTING COUNCIL ROOM---------\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	r = cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 4);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 4);
	asserttrue(testG.handCount[thisPlayer],G.handCount[thisPlayer] +4);
	asserttrue(testG.deckCount[thisPlayer],G.deckCount[thisPlayer] -4);
	printf("checking that the function returned okay\n");
	asserttrue(r,0);
	//other players draw a card
	int otherPlayer = 1;
	printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer] + 1);
	printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer] - 1);
	asserttrue(testG.handCount[otherPlayer],G.handCount[otherPlayer] + 1);
	asserttrue(testG.deckCount[otherPlayer],G.deckCount[otherPlayer] - 1);
	printf("numbuys = %d, numbuys expected = %d\n", testG.numBuys, G.numBuys + 2);
	asserttrue(testG.numBuys,G.numBuys+2);
	
	printf("SUCCESSFUL COMPLETION OF COUNCIL ROOM TESTING\n\n");
	return 0;
	
	
}
	
