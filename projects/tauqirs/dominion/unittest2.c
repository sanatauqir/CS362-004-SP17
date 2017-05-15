/*Test of scoreFor()

unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int asserttrue(int x, int y){
	if (x == y){
		printf("TEST PASSED\n");
		return 0;}
	else{
		printf("TEST FAILED\n");
		return 0;}
}

int main(){
	//setup a game
	int i,r;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	
	memset(&G, 23, sizeof(struct gameState));
	
	//----TEST1----//
	//loop to artificially setup 2 player's hand/deck/discard piles and confirm the final scoreFor
	printf("UNITTEST2 of SCOREFOR\n");

	initializeGame(numPlayer, k, seed, &G);
	for (i=0; i < 5; i++){
		if (i < 2){
			G.deck[0][i] = curse;
			G.hand[0][i] = province;
			G.discard[0][i] = estate;
		}
		else{
			G.deck[0][i] = great_hall;
			G.hand[0][i] = copper;
			G.discard[0][i] = duchy;
		}
	}
	printf("hand count %d\n", numHandCards(&G));
	printf("deck count %d\n", G.deckCount[0]);
	printf("discard count %d\n", G.discardCount[0]);
	printf("in his hand %d, %d, %d, %d, %d\n",G.hand[0][0],G.hand[0][1],G.hand[0][2],G.hand[0][3],G.hand[0][4]);
	printf("in his deck %d, %d, %d, %d, %d\n",G.deck[0][0],G.deck[0][1],G.deck[0][2],G.deck[0][3],G.deck[0][4]);
	printf("in his discard %d, %d, %d, %d, %d\n",G.discard[0][0],G.discard[0][1],G.discard[0][2],G.discard[0][3],G.discard[0][4]);
	r = scoreFor(0, &G);
	printf("score actual: %d, expected: %d\n", r, 25);
	asserttrue(r, 25);
	
	printf("--TEST2 deck w/gardens test--\n");
	
	memset(&G, 23, sizeof(struct gameState));
	initializeGame(numPlayer, k, seed, &G);
	for (i=0; i < 5; i++){
		if (i < 1){
			G.hand[0][i] = gardens;
		}
		if (i > 1 && i < 4){
			G.hand[0][i] = province;
		}
		else{
			G.hand[0][i] = copper;
		}
	}
	for (i=0; i < 9; i++){
		if (i < 5){
			G.deck[0][i] = estate;
			G.discard[0][i] = copper;
		}
		else{
			G.deck[0][i] = silver;
			G.discard[0][i] = curse;
		}
	}
	r = scoreFor(0, &G);
	printf("score actual: %d, expected: %d\n", r, 14);
	asserttrue(r, 14);
	
	printf("SCOREFOR TEST SUCCEEDED\n");
		
		return 0;
	
}