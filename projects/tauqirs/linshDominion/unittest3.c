/*Test of fullDeckCount()

unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
	printf("UNITTEST3 of FULLDECKCOUNT\n");

	initializeGame(numPlayer, k, seed, &G);
	for (i=0; i < 5; i++){
		if (i < 2){
			G.deck[0][i] = duchy;
			G.hand[0][i] = province;
			G.discard[0][i] = estate;
		}
		else{
			G.deck[0][i] = silver;
			G.hand[0][i] = copper;
			G.discard[0][i] = copper;
		}
	}
	
	r = fullDeckCount(0, copper, &G);
	printf("copper count actual: %d, expected: %d\n", r, 6);
	asserttrue(r, 6);
	
	r = fullDeckCount(0, silver, &G);
	printf("silver count actual: %d, expected: %d\n", r, 3);
	asserttrue(r, 3);
	
	r = fullDeckCount(0, duchy, &G);
	printf("duchy count actual: %d, expected: %d\n", r, 2);
	asserttrue(r, 2);
	
	r = fullDeckCount(0, estate, &G);
	printf("estate count actual: %d, expected: %d\n", r, 2);
	asserttrue(r, 2);
	
	printf("FULLCOUNT TEST SUCCEEDED\n\n");
	
	return 0;
	
}