#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK_SIZE 52
#define HAND_SIZE 7
#define SIMULATIONS 1000000

// 1. Define suits
enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };

// 2. Define card struct
struct Card {
    enum Suit suit;
    short pips; // 1 = Ace, 2-10 = Number cards, 11=Jack, 12=Queen, 13=King
};

// 3. Initialize deck
void initDeck(struct Card deck[]) 
{
    int index = 0;
    // Loop through each suit
    for (int s = 0; s < 4; s++) 
    {
        // For each suit, assign pips from 1 to 13
        for (short p = 1; p <= 13; p++) 
        {
            deck[index].suit = s;
            deck[index].pips = p;
            index++;
        }
    }
}

// 4. Shuffle deck
void shuffleDeck(struct Card deck[]) 
{
    for (int i = DECK_SIZE - 1; i > 0; i--) 
    {
        int j = rand() % (i + 1);
        struct Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp; // Swap cards
    }
}

// 5. Count occurrences of pips in a hand
void countPips(struct Card hand[], int counts[14]) 
{
    // Initialize counts to zero
    for (int i = 0; i < 14; i++) 
        counts[i] = 0;
    // Count pips in the hand
    for (int i = 0; i < HAND_SIZE; i++) 
    {
        counts[hand[i].pips]++;
    }
}

// 6. Evaluate hand type
enum HandType { NO_PAIR, ONE_PAIR, TWO_PAIR, THREE_KIND, FULL_HOUSE, FOUR_KIND };
// Evaluate the hand and return the type
enum HandType evaluateHand(struct Card hand[]) 
{
    int counts[14];
    countPips(hand, counts);

    int pairs = 0, threes = 0, fours = 0;
// Count pairs, threes, and fours
    for (int i = 1; i <= 13; i++) {
        if (counts[i] == 2) pairs++;
        else if (counts[i] == 3) threes++;
        else if (counts[i] == 4) fours++;
    }
// Determine hand type based on counts
    if (fours == 1) return FOUR_KIND;
    if (threes == 1 && pairs >= 1) return FULL_HOUSE;
    if (threes == 1) return THREE_KIND;
    if (pairs == 2) return TWO_PAIR;
    if (pairs == 1) return ONE_PAIR;
    return NO_PAIR;
}

int main() 
{
    // Seed the random number generator
    srand(time(NULL));

    struct Card deck[DECK_SIZE];
    int results[6] = {0}; // Counts for each hand type

    struct Card hand[HAND_SIZE];
    // Initialize the deck
    for (long sim = 0; sim < SIMULATIONS; sim++) {
        initDeck(deck);
        shuffleDeck(deck);

        // Deal 7 cards
        for (int i = 0; i < HAND_SIZE; i++) {
            hand[i] = deck[i];
        }
    // Evaluate the hand
        enum HandType ht = evaluateHand(hand);
        results[ht]++;
    }
    // Print results
    printf("After %d simulations:\n", SIMULATIONS);
    printf("No Pair:       %.6f\n", (double)results[NO_PAIR]/SIMULATIONS);
    printf("One Pair:      %.6f\n", (double)results[ONE_PAIR]/SIMULATIONS);
    printf("Two Pair:      %.6f\n", (double)results[TWO_PAIR]/SIMULATIONS);
    printf("Three of Kind: %.6f\n", (double)results[THREE_KIND]/SIMULATIONS);
    printf("Full House:    %.6f\n", (double)results[FULL_HOUSE]/SIMULATIONS);
    printf("Four of Kind:  %.6f\n", (double)results[FOUR_KIND]/SIMULATIONS);

    return 0;
}
// Compile with: gcc 7-Card.c -o 7-Card -lm