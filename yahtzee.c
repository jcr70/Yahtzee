#include <stdio.h>
#include <stdlib.h>

#define FULL_HOUSE 25
#define	SMALL_STRAIGHT 30
#define LARGE_STRAIGHT 40
#define YAHTZEE 50
#define DICE 6

int dice[DICE];
int score = 0;

struct upperSection {
	int ones;
	int twos;
	int threes;
	int fours;
	int fives;
	int sixes;

}upper;

struct lowerSection {
	int threeOfAKind;
	int fourOfAKind;
	int fullHouse;		//This variable is just a boolean, it's a const 25 points
	int smallStraight;	//This variable is just a boolean, it's a const 30 points
	int largeStraight;	//This variable is just a boolean, it's a const 40 points
	int yahtzee;		//This variable is just a boolean, it's a const 50 points (5 of a kind)
	int chance;			//Total of all 5 dice, useful when it doesn't fit into other categories
}lower;

int cmpfunc (const void *a, const void *b) {
	return ( *(int*)a - *(int*)b );
}

int generateDice() {

	
	FILE *f;
	f = fopen("/dev/dice", "r");
	int c = (fgetc(f) - '0') + 1;
	return c;
	
	/*
	int r = rand() % DICE;		//Random Number between 0-5
	r += 1;						//Increment by 1 to get number between 1-6
	return r;
	*/

}

int isThreeOfAKind() {
	int i;

	qsort(dice, 6, sizeof(int), cmpfunc);

	for(i = 0; i < DICE; i++) {
		if( (dice[i] == dice[i+1]) &&  (dice[i+1]== dice[i+2]) ) {
			return 1;
		}
	}


	return 0;
}

int isFourOfAKind() {
	int i;

	qsort(dice, 6, sizeof(int), cmpfunc);

	for(i = 0; i < DICE; i++) {
		if( (dice[i] == dice[i+1]) &&  (dice[i+1]== dice[i+2]) && (dice[i+2] == dice[i+3]) ) {
			return 1;
		}
	}


	return 0;
}

int isFullHouse() {
	int i, k;
	qsort(dice, 6, sizeof(int), cmpfunc);

	for(i = 0; i < DICE; i++) {
		if( (dice[i] == dice[i+1]) && (dice[i+1] == dice[i+2]) ) {
			int cantBeThis = dice[i];

			for(k = 0; k < DICE; k++) {
				if ( (dice[k] == dice[k+1]) && dice[k] != cantBeThis ) {
					return 1;
				}
			}

		} 
	}

	return 0;

}

void addInZeros() {
	if(upper.ones == NULL) {
		upper.ones = 0;
	}

	if(upper.twos == NULL) {
		upper.twos = 0;
	}

	if(upper.threes == NULL) {
		upper.threes = 0;
	}

	if(upper.fours == NULL) {
		upper.fours = 0;
	}

	if(upper.fives == NULL) {
		upper.fives = 0;
	}

	if(upper.sixes == NULL) {
		upper.sixes = 0;
	}

	if(lower.threeOfAKind == NULL) {
		lower.threeOfAKind = 0;
	}

	if(lower.fourOfAKind == NULL) {
		lower.fourOfAKind = 0;
	}

	if(lower.fullHouse == NULL) {
		lower.fullHouse = 0;
	}

	if(lower.smallStraight == NULL) {
		lower.smallStraight = 0;
	}

	if(lower.largeStraight == NULL) {
		lower.largeStraight = 0;
	}

	if(lower.yahtzee == NULL) {
		lower.yahtzee = 0;
	}

	if(lower.chance == NULL) {
		lower.chance = 0;
	}
}

int computeScore(int categorySelection) {
	int i;
	int sum = 0;
	for(i = 0; i < DICE; i++) {
		if(dice[i] == categorySelection) {
			sum += categorySelection;
		}
	}

	return sum;

}

int isSmallStraight() {		//Any 4 numbers in a row
	int i;
	int counter = 1;

	qsort(dice, 6, sizeof(int), cmpfunc);

	for(i = 0; i < DICE-1; i++) {
		if( (dice[i+1])-(dice[i]) == 1 ) {
			counter++;

			if(counter >= 4) {
				return 1;
			} else {
				continue;
			}

		} else if(dice[i+1] == dice[i]) {
			continue;
			
		} else if(dice[i+1] - dice[i] != 1) {
			counter = 1;
			continue;
		}
	}

	if(counter >= 4) {
		return 1;
	} else {
		return 0;
	}

}

int isLargeStraight() {		//Any 5 numbers in a row
	int i;
	int counter = 1;

	qsort(dice, 6, sizeof(int), cmpfunc);

	for(i = 0; i < DICE-1; i++) {
		if( (dice[i+1])-(dice[i]) == 1 ) {
			counter++;

			if(counter >= 5) {
				return 1;
			} else {
				continue;
			}

		} else if(dice[i+1] == dice[i]) {
			continue;
			
		} else if(dice[i+1] - dice[i] != 1) {
			counter = 1;
			continue;
		}
	}

	if(counter >= 5) {
		return 1;
	} else {
		return 0;
	}

}

int isYahtzee() {
	int holder = dice[0];
	int i;

	for(i = 0; i < DICE; i++) {
		if (holder != dice[i]) {
			return 0;
		}

	}

	return 1;
}


void printScore() {
	printf("Your score: %i\n", score);
	printf("Ones: %i", upper.ones);
	printf("\t\t\t\tFours: %i\n", upper.fours);
	printf("Twos: %i", upper.twos);
	printf("\t\t\t\tFives: %i\n", upper.fives);
	printf("Threes: %i", upper.threes);
	printf("\t\t\tSixes: %i\n", upper.sixes);

	printf("\n");

	printf("Three of a Kind: %i", lower.threeOfAKind);
	printf("\t\tSmall Straight: %i\n", lower.smallStraight);
	printf("Four of a Kind: %i", lower.fourOfAKind);
	printf("\t\tLarge Straight: %i\n", lower.largeStraight);
	printf("Full House: %i", lower.fullHouse);
	printf("\t\t\tYahtzee: %i\n", lower.yahtzee);
	printf("Chance: %i\n", lower.chance);


}

int main() {


	
	char toReroll[DICE];
	int sectionSelection;
	int categorySelection;
	int counter= 1;

	int upperUsed1 = 0;
	int upperUsed2 = 0;
	int upperUsed3 = 0;
	int upperUsed4 = 0;
	int upperUsed5 = 0;
	int upperUsed6 = 0;

	int lowerUsed1 = 0;
	int lowerUsed2 = 0;
	int lowerUsed3 = 0;
	int lowerUsed4 = 0;
	int lowerUsed5 = 0;
	int lowerUsed6 = 0;
	int lowerUsed7 = 0;

	srand(time(NULL));
	int i;

	while (counter < 13) {	//Must go 13 times to fill all categories
		printf("\: %i\n", counter);

		int rolls=1;		//Variable to hold how many re-rolls a user gets

		for(i = 0; i < DICE; i++) {
			dice[i] = generateDice();		//Generates dice
		}

		printf("Your Roll: ");

		for(i = 0; i < DICE; i++){ 
			printf("%i ", dice[i]);			//Prints dice
		}

		printf("\n");



		while(rolls < 3 ) {					//Loop to re-roll dice if necessary
			printf("Which dice to reroll?\n");
			scanf("%s", &toReroll);

			if(toReroll[0] == '0') {	//Do not reroll any more dice if user enters '0'
				break;
			} else {
				for(i = 0; i < DICE; i++) {
					//printf("%c\n", toReroll[i]);
					if(toReroll[i] == NULL) {
						break;
					}
					int num = toReroll[i] - '0';	//Converts from char to int
					num -= 1;
					dice[num] = generateDice();
				
					
				}

				int x;
					
				for(x = 0; x < DICE; x++){ 
					printf("%i ", dice[x]);			//Prints dice
				}
				printf("\n");


			}



			rolls++;

		}

		printf("Place dice into:\n");
		printf("1) Upper Section\n");
		printf("2) Lower Section\n");

		printf("Selection? ");
		scanf("%i", &sectionSelection);
		printf("\n");

		if(sectionSelection == 1) {		//Place into Upper Section

			while(1) {
				printf("Place dice into:\n");
				printf("1) Ones\n");
				printf("2) Twos\n");
				printf("3) Threes\n");
				printf("4) Fours\n");
				printf("5) Fives\n");
				printf("6) Sixes\n");
				scanf("%i", &categorySelection);
				printf("\n");


				if(categorySelection == 1) {
					if(upperUsed1) {
						printf("Already used. Please pick again\n\n");
						continue;
					}
					upper.ones = computeScore(categorySelection);
					score+= upper.ones;
					upperUsed1 = 1;
					break;
				} else if (categorySelection == 2) {
					if(upperUsed2) {
						printf("Already used. Please pick again\n\n");
						continue;
					}
					upper.twos = computeScore(categorySelection);
					score+= upper.twos;
					upperUsed2 = 1;
					break;
				} else if (categorySelection == 3) {
					if(upperUsed3) {
						printf("Already used. Please pick again\n\n");
						continue;
					}
					upper.threes = computeScore(categorySelection);
					score+= upper.threes;
					upperUsed3 = 1;
					break;
				} else if (categorySelection == 4) {
					if(upperUsed4) {
						printf("Already used. Please pick again\n\n");
						continue;
					}
					upper.fours = computeScore(categorySelection);
					score+= upper.fours;
					upperUsed4 = 1;
					break;
				} else if (categorySelection == 5) {
					if(upperUsed5) {
						printf("Already used. Please pick again\n\n");
						continue;
					}
					upper.fives = computeScore(categorySelection);
					score+= upper.fives;
					upperUsed5 = 1;
					break;
				} else if (categorySelection == 6) {
					if(upperUsed6) {
						printf("Already used. Please pick again\n\n");
						continue;
					}
					upper.sixes = computeScore(categorySelection);
					score+= upper.sixes;
					upperUsed6 = 1;
					break;
				}
			}


			printScore();
			printf("\n\n");

		} else {	//Place into Lower Section

			while(1) {
				char takeZero;
				printf("Place dice into:\n");
				printf("1) Three of a Kind\n");
				printf("2) Four of a Kind\n");
				printf("3) Full House\n");
				printf("4) Small Straight\n");
				printf("5) Large Straight\n");
				printf("6) Yahtzee\n");
				printf("7) Chance\n");
				scanf("%i", &categorySelection);
				printf("\n");

				if(categorySelection == 1) {
					if(lowerUsed1) {
						printf("Already used. Please pick again\n\n");
						continue;
					}

					if(!isThreeOfAKind()){
						printf("You do not have three of a kind. Would you like to take a 0 for this category? [y/n]\n\n");
						scanf("%c", &takeZero);
						if(takeZero == 'y') {
							lower.threeOfAKind = 0;
						} else{
							continue;
						}
					} else{
						int sum = 0;
						for(i = 0; i < DICE; i++) {
							sum += dice[i];
						}

						lower.threeOfAKind = sum;
						score+= lower.threeOfAKind;
						lowerUsed1 = 1;
					}
					
				} else if (categorySelection == 2) {
					if(lowerUsed2) {
						printf("Already used. Please pick again\n\n");
						continue;
					}

					if(!isFourOfAKind()){
						printf("You do not have four of a kind. Would you like to take a 0 for this category? [y/n]\n\n");
						scanf("%c", &takeZero);
						if(takeZero == 'y') {
							lower.fourOfAKind = 0;
						} else {
							continue;
						}
					} else{
						int sum = 0;
						for(i = 0; i < DICE; i++) {
							sum += dice[i];
						}

						lower.fourOfAKind = sum;
						score+= lower.fourOfAKind;
						lowerUsed2 = 1;
					}
					
				} else if (categorySelection == 3) {
					if(lowerUsed3) {
						printf("Already used. Please pick again\n\n");
						continue;
					}
					if(!isFullHouse()) {
						printf("You do not have a full house. Would you like to take a 0 for this category? [y/n]\n\n");
						scanf("%c", &takeZero);
						if(takeZero == 'y') {
							lower.fullHouse = 0;
						} else {
							continue;
						}
					} else {
						lower.fullHouse = FULL_HOUSE;
						score += FULL_HOUSE;
						lowerUsed3 = 1;
					}
				} else if (categorySelection == 4) {
					if(lowerUsed4) {
						printf("Already used. Please pick again\n\n");
						continue;
					}
					if(!isSmallStraight()) {
						printf("You do not have small straight. Would you like to take a 0 for this category? [y/n]\n\n");
						scanf("%c", &takeZero);
						if(takeZero == 'y') {
							lower.smallStraight = 0;
						} else {
							continue;
						}
					} else {
						lower.smallStraight = SMALL_STRAIGHT;
						score += SMALL_STRAIGHT;
						lowerUsed4 = 1;
					}
				} else if (categorySelection == 5) {
					if(lowerUsed5) {
						printf("Already used. Please pick again\n\n");
						continue;
					}
					if(!isLargeStraight()) {
						printf("You do not have large straight. Would you like to take a 0 for this category? [y/n]\n\n");
						scanf("%c", &takeZero);
						if(takeZero == 'y') {
							lower.largeStraight = 0;
						} else {
							continue;
						}
					} else {
						lower.largeStraight = LARGE_STRAIGHT;
						score += LARGE_STRAIGHT;
						lowerUsed5 = 1;
					}
				} else if (categorySelection == 6) {
					if(lowerUsed6) {
						printf("Already used. Please pick again\n\n");
						continue;
					}
					if(!isYahtzee()){
						printf("You do not have yahtzee. Would you like to take a 0 for this category? [y/n]\n\n");
						scanf("%c", &takeZero);
						if(takeZero == 'y') {
							lower.threeOfAKind = 0;
						} else {
							continue;
						}
					} else {
						lower.yahtzee = YAHTZEE;
						score += YAHTZEE;
						lowerUsed6 = 1;
					}
				} else if(categorySelection == 7) {
					if(lowerUsed7) {
						printf("Already used. Please pick again\n\n");
						continue;
					}
					int i;
					int tempScore = 0;
					for (i = 0; i < DICE; i++) {
						tempScore += dice[i];
					}

					lower.chance = tempScore;
					score += tempScore;
					lowerUsed7 = 1;
				}


				printScore();
				printf("\n");
				break;
			} //End while
		} //End else


		counter++;
	} //End while

	if( (upper.ones + upper.twos + upper.threes + upper.fours + upper.fives + upper.sixes) > 63) {
		printf("35 Bonus points because your upper section totalled more than 63\n");
		score+= 35;
	}
	addInZeros();
	printf("Final Score\n");
	printf("------------------------------------------\n");
	printScore();
	printf("------------------------------------------\n");
	 


	return 0;
}