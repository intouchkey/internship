#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dos.h> // for sleep function

// setting up personal tabs and enter
#define tab "\t\t\t\t"
#define enter "\n\n\n\n\n\n\n\n\n"

//Welcome function
void welcome()
{
	printf("%s%sWELCOME TO HANGMAN GAME!!!\n\n",enter, tab);
	printf("%sby: INTOUCH YUTINATORN\n\n", tab);
	printf("%sTo play the game...\n%s", tab, tab);
}

//A function for user to select category
int select_category()
{
	int input;

	while (1)
	{
		printf("%s%sPlease select the category you wanted to play:\n\n", enter, tab);
		printf("%s1. Fruit\n\n", tab);
		printf("%s2. Mobile phone brands\n\n", tab);
		printf("%s3. Music\n\n", tab);
		printf("%sEnter number: ", tab);
		input = getch();
		//If user enters 1 or 2, proceeds
		if ((input == 49) || (input == 50) || (input == 51))
			break;
		printf("\n%sInvalid input, please enter again..", tab);
		Sleep(1000);
		system("cls");
	}

	return input;
}

//A function for calculating total points and game over
void calculate_points(int length, int correct_answer, int incorrect_guess, float time_taken)
{
	system("cls");
	printf("%s%sNumber of correct guesses: %d / %d", enter, tab, correct_answer, length);
	printf("\n\n%sNumber of incorrect guesses: %d", tab, incorrect_guess);
	printf("\n\n%sTime taken: %.2f seconds", tab, time_taken);

	float score = (correct_answer / (float)length) * 1000;
	score -= (incorrect_guess / (float)length) * 1000;
	
	if (time_taken < 180 && correct_answer == length)
	{
		score += 500 - ((time_taken / 180) * 500);
	}

	if (score < 0)
		score = 0;

	printf("\n\n%sTotal score (Maximum score: 1500 points): %.2f points\n%sThank you so much for playing...\n\n%s", tab, score, tab, tab);

	system("pause");
	exit(0);
}

//Function used during the guessing of words
void game_interface(char word[1000], char hint[1000])
{
	// array1 is used to keep the words inputted
	char array1[100];
	//times = Number of times guessing words
	int times = 0;
	//Start timing
	clock_t start = clock();

	while (1)
	{
		system("cls");
		char input[1000];
		int check, check2, check3, incorrect_guess = 0;
		// check, check2 and check3 are used as conditions when true (used in nested loop)
		// incorrect_guess is just the number of guesses that are incorrect

		printf("%s%sHint: %s\n\n\n%sWord: ", enter, tab, hint, tab);

		//Length is the size of word
		int length = strlen(word);
		length = length - 1;

		//This is for printing out lines and words
		for (int i = 0; i < length; i++)
		{
			check = 0;

			for (int j = 0; j <= times; j++)
			{
				if (word[i] == tolower(array1[j]))
				{
					printf("%c ", word[i]);
					check = 1;
				}
			}

			if (check == 0)
				printf("_ ");
		}

		//This is for printing out the words that are guessed incorrectly in the past
		printf("\n\n\n%sWords guessed incorrectly: ", tab);
		for (int j = 0; j < times; j++)
		{
			check3 = 0;
			for (int i = 0; i <= length; i++)
			{
				if (word[i] == tolower(array1[j]))
					check3 = 1;
			}
			if (check3 == 0)
			{
				printf("%c ", array1[j]);
				incorrect_guess++;
			}
		}
		// Remaining guesses for the user to guess
		printf("\n%sRemaining guess: %d", tab, 10 - incorrect_guess);

		// Check for number of correct words that are guessed
		int correct_answer = 0;
		for (int i = 0; i <= length; i++)
		{
			check3 = 0;
			for (int j = 0; j < times; j++)
			{
				if (word[i] == tolower(array1[j]))
					check3 = 1;
			}
			if (check3 == 1)
				correct_answer++;
		}

		// Proceed to the function calculate points if all words are correct or user guessed incorrectly more than 10 times
		if (correct_answer == length || incorrect_guess == 10)
		{
			clock_t end = clock();
			calculate_points(length, correct_answer, incorrect_guess, (float)(end - start) / CLOCKS_PER_SEC);
		}

		// This is for inputting word
		// This function will keep asking if the word is not a character or the word is duplicated (already inputted before)
		printf("\n\n\n%sGuess the word: ", tab);
		while (1)
		{
			check2 = 0;
			scanf("%s", input);
			getchar();

			// Check whether the word is duplicated
			if (strlen(input) == 1)
			{
				for (int j = 0; j <= times; j++)
				{
					if (input[0] == array1[j])
					{
						check2 = 1;
					}
				}
			}

			if (strlen(input) == 1 && check2 == 0)
				break;
			printf("%sGuess the word again: ", tab);
		}

		// Adding word to the array
		array1[times] = input[0];

		times++;
	}
	system("pause");
}

//A function for opening the file accordingly and choosing a word randomly
void game(int choice)
{
	FILE *inFile;
	char line[1000], hint[1000];

	// Opens file according to user's choice
	if (choice == 49)
	{
		inFile = fopen("fruit.txt", "r");
		if (inFile == NULL)
		{
			printf("%sMissing database file!\n", tab);
			exit(0);
		}
	}
	else if (choice == 50)
	{
		inFile = fopen("brand.txt", "r");
		if (inFile == NULL)
		{
			printf("%sMissing database file!\n", tab);
			exit(0);
		}
	}
	else
	{
		inFile = fopen("music.txt", "r");
		if (inFile == NULL)
		{
			printf("%sMissing database file!\n", tab);
			exit(0);
		}
	}

	//Randomize word
	srand(time(NULL));
	int random = rand() % 6;

	//Read input from the file
	while (fgets(line, 1000, inFile) != NULL)
	{
		fgets(hint, 1000, inFile);
		if (random == 0)
		{
			game_interface(line, hint);
			break;
		}
		random -= 1;
	}

	fclose(inFile);
}

//Main function that calls other functions
void main()
{
	welcome();
	system("pause");
	system("cls");
	
	game(select_category());
}