/*Test of isGameOver()

unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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
	int i, r;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	
	memset(&G, 23, sizeof(struct gameState));
	
	printf("UNITTEST4 TEST OF ISGAMEOVER\n");

	printf("----TEST1 where conditions for gameOver are false----\n");
	initializeGame(numPlayer, k, seed, &G);
	for (i=0; i < 5; i++){
		G.supplyCount[province] = 1;
		G.supplyCount[copper] = 8;
		G.supplyCount[silver] = 4;
		G.supplyCount[estate] = 0;
		G.supplyCount[smithy] = 0;
	}
	r = isGameOver(&G);
	printf("game over returns: %d, expected: %d\n", r, 0);
	asserttrue(r, 0);
	
	printf("----TEST2 where conditions province cards empty----\n");
	memset(&G, 23, sizeof(struct gameState));
	initializeGame(numPlayer, k, seed, &G);
	G.supplyCount[province] = 0;
	r = isGameOver(&G);
	printf("game over returns: %d, expected: %d\n", r, 1);
	asserttrue(r, 1);
	
	printf("----TEST3 where 3 empty supply piles----\n");
	memset(&G, 23, sizeof(struct gameState));
	initializeGame(numPlayer, k, seed, &G);
	G.supplyCount[smithy] = 0;
	G.supplyCount[silver] = 0;
	G.supplyCount[estate] = 0;
	r = isGameOver(&G);
	printf("game over returns: %d, expected: %d\n", r, 1);
	asserttrue(r, 1);

	printf("ISGAMEOVER TEST SUCCEEDED\n\n");
		
		return 0;
	}