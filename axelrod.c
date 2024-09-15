#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//Define the maximum number of games.
#define MAX_GAMES 1000
//Define number of strategies
#define STRATEGY_NUMBER 5

//Array and global variable definition
int playerscore = 0;
int opposcore = 0;
char * strategies[STRATEGY_NUMBER - 1];

enum actions
{
    ACTIONS_COOPERATE = 0,
    ACTIONS_DEFECT = 1,
};

enum strategy
{
    STRATEGY_COOPERATE,
    STRATEGY_DEFECT,
    STRATEGY_RANDOM,
};

//Function prototypes
void simulate_games(int playerstrategy, int oppostrategy, int playerstrat[], int oppostrat[]);
int calculate_score(int playerstrat[], int oppostrat[]);

int main (int argc, char * argv[])
{
//Set up nuclear version of the game
if (argv[1] == NULL)
{
    printf("Usage: ./axelrod normal for normal mode, ./axelrod nuclear for nuclear mode\n");
    return 1;
}
if (strcmp(argv[1], "NUCLEAR") == 0)
{
    //Initialise arrays for strategies
    int playerstrat[MAX_GAMES];
    int oppostrat[MAX_GAMES];

    //Set up random number generation
    srand(time(NULL));

    //Greet player
    printf("Welcome to the NUCLEAR version of the AXELROD TOURNAMENT!\n");
    printf("This programme simulates multiple games of the Prisoner's Dilemma in nuclear conditions.\n");
    printf("You will face %i games. The aim is to survive without being bombed.\n", MAX_GAMES);
    printf("If one player ever defects, while the other cooperates, the cooperating player immediately loses.\n");
    printf("If both players defect, both players immediately lose.\n");
    printf("Firstly select which strategy YOU want to adopt by typing in its number.\n");
    printf("1:COOPERATE\n2:DEFECT\n3:RANDOM\n4:TIT FOR TAT\n5:TIT FOR DOUBLE TAT\n");

    //Prompt for strategy
    int playerstrategy = get_int("Strategy: ");
    if(isdigit(playerstrategy) != 0 || playerstrategy < 1 || playerstrategy > 5)
    {
        printf("Error: please type in the number of the strategy \n");
        return 1;
    }

    //Prompt for opponent strategy
    printf("Now select which strategy the OPPONENT will adopt by typing in its number.\n");
    printf("1:COOPERATE\n2:DEFECT\n3:RANDOM\n4:TIT FOR TAT\n5:TIT FOR DOUBLE TAT\n");
    int oppostrategy = get_int("Strategy: ");
    if(isdigit(oppostrategy) != 0 || oppostrategy < 1 || oppostrategy > 5)
    {
        printf("Error: please type in the number of the strategy \n");
        return 2;
    }

    //Populate arrays of strategies
    simulate_games(playerstrategy, oppostrategy, playerstrat, oppostrat);

    //TODO: iterate over games and see if any player lost
    for (int i = 0; i < MAX_GAMES; i++)
    {
        if (playerstrat[i] == ACTIONS_DEFECT && oppostrat[i] == ACTIONS_COOPERATE)
        {
            printf("The enemy got bombed. You win.\n");
            return 0;
        }
        if (oppostrat[i] == ACTIONS_DEFECT && playerstrat[i] == ACTIONS_COOPERATE)
        {
            printf("You got bombed. You lose.\n");
            return 0;
        }
        if (oppostrat[i] == ACTIONS_DEFECT && playerstrat[i] == ACTIONS_DEFECT)
        {
            printf("You both got bombed. You both lose.\n");
            return 0;
        }

    }
    printf("Neither player got bombed. You win.\n");

}
    //Set up normal version of the game.
else if (strcmp(argv[1], "NORMAL"))
{
    //Initialise arrays for strategies
    int playerstrat[MAX_GAMES];
    int oppostrat[MAX_GAMES];

    //Set up random number generation
    srand(time(NULL));

    //Greet player
    printf("Welcome to the AXELROD TOURNAMENT\n");
    printf("This programme simulates multiple games of the Prisoner's Dilemma.\n");
    printf("You will face %i games.\n", MAX_GAMES);
    printf("Firstly select which strategy YOU want to adopt by typing in its number.\n");
    printf("1:COOPERATE\n2:DEFECT\n3:RANDOM\n4:TIT FOR TAT\n5:TIT FOR DOUBLE TAT\n");

    //Prompt for strategy
    int playerstrategy = get_int("Strategy: ");
    if(isdigit(playerstrategy) != 0 || playerstrategy < 1 || playerstrategy > 5)
    {
        printf("Error: please type in the number of the strategy \n");
        return 1;
    }

    //Prompt for opponent strategy
    printf("Now select which strategy the OPPONENT will adopt by typing in its number.\n");
    printf("1:COOPERATE\n2:DEFECT\n3:RANDOM\n4:TIT FOR TAT\n5:TIT FOR DOUBLE TAT\n");
    int oppostrategy = get_int("Strategy: ");
    if(isdigit(oppostrategy) != 0 || oppostrategy < 1 || oppostrategy > 5)
    {
        printf("Error: please type in the number of the strategy \n");
        return 2;
    }

    //Populate arrays of strategies
    simulate_games(playerstrategy, oppostrategy, playerstrat, oppostrat);

    //Calculate the score
    int score = calculate_score(playerstrat, oppostrat);
    printf("You scored: %i\n", playerscore);
    printf("Your opponent scored: %i\n", opposcore);
    if (score < 0)
    {
        printf("You lose. Try a different strategy!\n");
    }
    if (score == 0)
    {
        printf("Tie! Jest dobrze jest git, dobry przekaz leci.\n");
    }
    if (score > 0)
    {
        printf("You win. Try a different strategy!\n");
    }
}
else
{
    printf("Error. Invalid mode selected.\n");
    return 1;
}

}

void simulate_games(int playerstrategy, int oppostrategy, int playerstrat[], int oppostrat[])
{
    for (int i = 0; i < MAX_GAMES; i++)
    {
        if (playerstrategy == 1)
        {
            playerstrat[i] = ACTIONS_COOPERATE;
        }
        if (playerstrategy == 2)
        {
            playerstrat[i] = ACTIONS_DEFECT;
        }
        if (playerstrategy == 3)
        {
            playerstrat[i] = rand() %2;
        }
        if (playerstrategy == 4)
        {
            if (i == 0)
            {
                playerstrat[i] = ACTIONS_COOPERATE;
            }
            else
            {
                playerstrat[i] = oppostrat[i - 1];
            }
        }
        if (playerstrategy == 5)
        {
            if (i < 2)
            {
                playerstrat[i] = ACTIONS_COOPERATE;
            }
            else
            {
                playerstrat[i] = oppostrat[i - 2];
            }
        }

        if (oppostrategy == 1)
        {
            oppostrat[i] = ACTIONS_COOPERATE;
        }
        if (oppostrategy == 2)
        {
            oppostrat[i] = ACTIONS_DEFECT;
        }
        if (oppostrategy == 3)
        {
            oppostrat[i] = rand() %2;
        }
        if (oppostrategy == 4)
        {
            if (i == 0)
            {
                oppostrat[i] = ACTIONS_COOPERATE;
            }
            else
            {
                oppostrat[i] = playerstrat[i - 1];
            }
        }
        if (oppostrategy == 5)
        {
            if (i < 2)
            {
                oppostrat[i] = ACTIONS_COOPERATE;
            }
            else
            {
                oppostrat[i] = playerstrat[i - 2];
            }
        }
    }
}

int calculate_score(int playerstrat[], int oppostrat[])
{
    //Loop over all games
    for (int x = 0; x < MAX_GAMES; x++)
    {
        if (playerstrat[x] == ACTIONS_COOPERATE && oppostrat[x] == ACTIONS_COOPERATE)
        {
            playerscore += 3;
            opposcore += 3;
        }
        if (playerstrat[x] == ACTIONS_DEFECT && oppostrat[x] == ACTIONS_DEFECT)
        {
            playerscore += 1;
            opposcore += 1;
        }
        if (playerstrat[x] == ACTIONS_DEFECT && oppostrat[x] == ACTIONS_COOPERATE)
        {
            playerscore += 5;
        }
        if (playerstrat[x] == ACTIONS_COOPERATE && oppostrat[x] == ACTIONS_DEFECT)
        {
            opposcore +=5;
        }
    }
    return playerscore - opposcore;
}