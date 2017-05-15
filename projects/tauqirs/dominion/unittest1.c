/*Test of endTurn()
unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 
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
	printf("Entering: TEST1 w/ 2 players\n");
	initializeGame(numPlayer, k, seed, &G);
	printf("handcount of player 1 %d, expected %d\n", G.handCount[0], 5);
	printf("handcount of player 2 %d, expected %d\n", G.handCount[1], 0);
	asserttrue(G.handCount[0],5);
	asserttrue(G.handCount[1],0);
	r = endTurn(&G);
	asserttrue(r,0);

	printf("after function call:\n");
	printf("whoseturn: %d, expected: %d\n", whoseTurn(&G), 1);
	asserttrue(whoseTurn(&G), 1);
	printf("handcount of player 1 %d, expected %d\n", G.handCount[0], 0);
	printf("handcount of player 2 %d, expected %d\n", G.handCount[1], 5);
	asserttrue(G.handCount[0],0);
	asserttrue(G.handCount[1],5);
	
	printf("TEST1 SUCCEEDED of 2players\n");

	printf("Entering: TEST2 w/ 4 players, 4 calls\n");
	memset(&G, 23, sizeof(struct gameState));
	initializeGame(4, k, seed, &G);
	
	for (i= 0; i < MAX_PLAYERS; i ++){
		asserttrue(G.handCount[i],5);
		asserttrue(whoseTurn(&G),i);
		endTurn(&G);
		asserttrue(G.handCount[i],0);
		
		printf("checking that turn has changed\n");
		if (i == 3){
			asserttrue(whoseTurn(&G), 0);}
		else {
			asserttrue(whoseTurn(&G), i+1);
		}
	}
		
	printf("TEST2 SUCCEEDED for 4 players\n\n");
			return 0;
			
	}
