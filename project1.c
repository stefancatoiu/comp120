#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //small addition to simulate the "Computer thinking" part

void init_board(char board[9]) {
    for (int square_index = 0; square_index < 9; square_index++) {
        board[square_index] = ' ';
    }
}

void display_board(char board[9]) {
    char c[9];
    
    for (int square_index = 0; square_index < 9; square_index++) {
        c[square_index] = board[square_index];

        if (c[square_index] == ' ') {
            c[square_index] = '0' + square_index;
        }
    }

    printf("\n");
    printf(" %c | %c | %c\n", c[0], c[1], c[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", c[3], c[4], c[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", c[6], c[7], c[8]);
    printf("\n");
}

int get_human_move(char board[9]) {
    int human_input;
    bool valid_input = false;

    while (valid_input == false) {
        printf("Your turn (0). Enter a square number (0-8): ");
        
        if (scanf("%d", &human_input) != 1) {
            printf("INVALID INPUT: TRY AGAIN!\n");
            while (getchar() != '\n');
            continue;
        }

        if (human_input >= 0 && human_input <= 8 && board[human_input] == ' ') {
            valid_input = true;
        } else if (human_input >= 0 && human_input <= 8 && board[human_input] != ' ') {
            valid_input = false;
            printf("SQUARE IS ALREADY TAKEN: TRY AGAIN!\n");
        } else if (human_input < 0 || human_input > 8) {
            valid_input = false;
            printf("INVALID SQUARE: TRY AGAIN!\n");
        }
    }

    return human_input;
}

int get_computer_move(char board[9]) {
    int computer_input;

    do {
        computer_input = rand() % 9;
    }
    while (board[computer_input] != ' ');

    printf("Computer (X) is thinking...\n");
    sleep(2);
    printf("Computer (X) chose square %d. Your move next!\n", computer_input);

    return computer_input;
}

bool is_winner(char board[9], char player) {
    
    if (board[0] == player && board[1] == player && board[2] == player) {
        return true;
    }
    else if (board[3] == player && board[4] == player && board[5] == player) {
        return true;
    }
    else if (board[6] == player && board[7] == player && board[8] == player) {
        return true;
    }
    else if (board[0] == player && board[3] == player && board[6] == player) {
        return true;
    }
    else if (board[1] == player && board[4] == player && board[7] == player) {
        return true;
    }
    else if (board[2] == player && board[5] == player && board[8] == player) {
        return true;
    }
    else if (board[0] == player && board[4] == player && board[8] == player) {
        return true;
    }
    else if (board[2] == player && board[4] == player && board[6] == player) {
        return true;
    }

    return false;
}

char other_player(char player) {
    if (player == 'O'){
        return 'X';
    }

    return 'O';
}

void take_turn(char board[9], char player){
    int choice;
    
    if (player == 'O') {
        choice = get_human_move(board);
    }
    else if (player == 'X') {
        choice = get_computer_move(board);
    }

    board[choice] = player;
}

void play_game(char board[9], char player) {
    init_board(board);
    display_board(board);
    player = 'O';

    for (int i = 1; i <= 9; i++) {
        take_turn(board, player);
        display_board(board);

        if (is_winner(board, player)) {
            sleep(1);
            printf("Player %c won the game!!!\n", player);
            return;
        }

        player = other_player(player);
    }

    sleep(1);
    printf("Draw!\n");
}

bool play_again(void) {
    char yes_or_no;

    do {
        printf("Do you want to play again (y/n): ");
        scanf(" %c", &yes_or_no);
        if (yes_or_no != 'y' && yes_or_no != 'n') {
            printf("INVALID INPUT: TRY AGAIN!\n");
        }
    } while (yes_or_no != 'y' && yes_or_no != 'n');

    return yes_or_no == 'y';
}

int main() {
    srand((unsigned int)time(NULL));
    char board[9];
    char player = 'O';

    printf("\n\n=====================================\n");
    printf("        TIC-TAC-TOE vs COMPUTER\n");
    printf("=====================================\n\n");
    printf("You are O and you go first. Computer is X.\n");

    do {
        play_game(board, player);
    } while (play_again());
    
    printf("\n\n");

    return 0;
}