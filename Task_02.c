#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// this a function protypes or we are saying function name
void displayWelcome();
int selectDifficulty();
int generateSecretNumber(int difficulty);
void playGame(int secret, int maxAttempts);
int playAgain();

int main() {
    int score = 0, gamesPlayed = 0;
    
    displayWelcome();
    
    do {
        int difficulty = selectDifficulty();
        int maxAttempts;
        int range;
        
        // Range of limits also we can edit the limit as per requirement.
        switch(difficulty) {
            case 1: // easy
                range = 50;
                maxAttempts = 10;
                break;
            case 2: // medium
                range = 100;
                maxAttempts = 7;
                break;
            case 3: // hard
                range = 200;
                maxAttempts = 5;
                break;
            default:
                range = 100;
                maxAttempts = 7;
        }
        
        int secret = generateSecretNumber(range);
        printf("\n🎯 I'm thinking of a number between 1 and %d\n", range);
        printf("💡 You have %d attempts\n\n", maxAttempts);
        
        playGame(secret, maxAttempts);
        gamesPlayed++;
        
    } while(playAgain());
    
    printf("\n🎮 Thanks for playing! You played %d games.\n", gamesPlayed);
    return 0;
}

void displayWelcome() {
    printf("=====================================\n");
    printf("        NUMBER GUESSING GAME\n");
    printf("=====================================\n");
    printf("Welcome! Try to guess the secret number!\n\n");
}

int selectDifficulty() {
    int choice;
    printf("Select difficulty:\n");
    printf("1. Easy (1-50, 10 attempts)\n");
    printf("2. Medium (1-100, 7 attempts)\n");
    printf("3. Hard (1-200, 5 attempts)\n");
    printf("Enter choice (1-3): ");
    
    while(scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
        printf("Please enter 1, 2, or 3: ");
        while(getchar() != '\n'); // Clear input buffer
    }
    return choice;
}

int generateSecretNumber(int range) {
    srand(time(0));
    return rand() % range + 1;
}

void playGame(int secret, int maxAttempts) {
    int guess, attempts = 0;
    int won = 0;
    
    while(attempts < maxAttempts && !won) {
        printf("Attempt %d/%d → Enter your guess: ", attempts + 1, maxAttempts);
        
        if(scanf("%d", &guess) != 1) {
            printf("❌ Please enter a valid number!\n");
            while(getchar() != '\n'); // Clear invalid input
            continue;
        }
        
        attempts++;
        
        if(guess == secret) {
            won = 1;
            printf("\n🎉 CONGRATULATIONS! You guessed it!\n");
            printf("⭐ You found the number %d in %d attempts!\n\n", secret, attempts);
        } else if(guess < secret) {
            printf("📉 Too low!");
            if(secret - guess <= 5) printf(" But very close!");
            printf("\n");
        } else {
            printf("📈 Too high!");
            if(guess - secret <= 5) printf(" But very close!");
            printf("\n");
        }
        
        // intersting hint that we help th players
        if(attempts == maxAttempts - 2 && !won) {
            if(secret % 2 == 0) {
                printf("💡 Hint: The number is even!\n");
            } else {
                printf("💡 Hint: The number is odd!\n");
            }
        }
    }
    
    if(!won) {
        printf("\n😢 Game over! The secret number was %d\n\n", secret);
    }
}

int playAgain() {
    char choice;
    printf("Would you like to play again? (y/n): ");
    scanf(" %c", &choice);
    return (tolower(choice) == 'y');
}