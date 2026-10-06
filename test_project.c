#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// prototypes
void init_board(char board[9]);
void display_board(char board[9]);
bool is_winner(char board[9], char player);
char other_player(char player);
int get_human_move(char board[9]);
int get_computer_move(char board[9]);
void take_turn(char board[9], char player);
char play_game(char board[9]);
int minimax(char board[9], char player, int depth);


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


// TEMPORARY TEST VERSION
// O randomly chooses an available square.
int get_human_move(char board[9]) {
    int human_input;

    do {
        human_input = rand() % 9;
    } while (board[human_input] != ' ');

    return human_input;
}


int minimax(char board[9], char player, int depth) {

    if (is_winner(board, 'O')) {
        return -10 + depth;
    }
    else if (is_winner(board, 'X')) {
        return 10 - depth;
    }

    int check_full = 0;

    for (int i = 0; i <= 8; i++) {
        if (board[i] == 'X' || board[i] == 'O') {
            check_full++;
        }
    }

    if (check_full == 9) {
        return 0;
    }

    int score;
    int best_score;

    if (player == 'X') {
        best_score = -1000;
    }
    else {
        best_score = 1000;
    }

    for (int i = 0; i <= 8; i++) {

        if (board[i] == ' ') {

            board[i] = player;

            score = minimax(board, other_player(player), depth + 1);

            // Undo hypothetical move
            board[i] = ' ';

            if (player == 'X') {
                if (score > best_score) {
                    best_score = score;
                }
            }
            else {
                if (score < best_score) {
                    best_score = score;
                }
            }
        }
    }

    return best_score;
}


int get_computer_move(char board[9]) {

    int computer_input;
    int best_score = -1000;
    int score;

    for (int i = 0; i <= 8; i++) {

        if (board[i] == ' ') {

            board[i] = 'X';

            score = minimax(board, 'O', 1);

            // Undo hypothetical move
            board[i] = ' ';

            if (score > best_score) {
                best_score = score;
                computer_input = i;
            }
        }
    }

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

    if (player == 'O') {
        return 'X';
    }

    return 'O';
}


void take_turn(char board[9], char player) {

    int choice;

    if (player == 'O') {
        choice = get_human_move(board);
    }
    else {
        choice = get_computer_move(board);
    }

    board[choice] = player;
}


char play_game(char board[9]) {

    init_board(board);

    char player = 'O';

    for (int i = 1; i <= 9; i++) {

        take_turn(board, player);

        if (is_winner(board, player)) {
            return player;
        }

        player = other_player(player);
    }

    return 'D';
}


int main(void) {

    srand((unsigned int)time(NULL));

    char board[9];

    int o_wins = 0;
    int x_wins = 0;
    int draws = 0;

    // Run exactly 10000 games
    for (int i = 0; i < 10000; i++) {

        char result = play_game(board);

        if (result == 'D') {
            draws++;
        }
        else if (result == 'X') {
            x_wins++;
        }
        else {
            o_wins++;
        }
    }

    int games_played = o_wins + x_wins + draws;

    printf("\n========== 10000 GAME TEST ==========\n");

    printf("Games played: %d\n", games_played);

    printf("O wins: %d (%.1f%%)\n",
           o_wins,
           (double)o_wins / games_played * 100.0);

    printf("X wins: %d (%.1f%%)\n",
           x_wins,
           (double)x_wins / games_played * 100.0);

    printf("Draws: %d (%.1f%%)\n",
           draws,
           (double)draws / games_played * 100.0);

    return 0;
}