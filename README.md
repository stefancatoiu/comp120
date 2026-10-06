# comp120

The following repository is dedicated for the COMP120 - Fall 2026 course.

project1.c is the main project file. It is a playable version of tic-tac-toe that takes user and computer input, handling invalid inputs and deviations from the game's rules. The game mainly handles arrays, if/else if statements and loops. For this version, the computer chooses a random square each time, so a human is more likely to win. I made a small addition for the program to wait 2 seconds after the "Computer is thinking..." statement to add a bit more realism.

project1_2.c is an improved version I made for fun. Using A.I. as a tool for thinking (i.e. not copy pasting code, but rather learning the order of algorithms and how to use new types of functions) I designed a tic-tac-toe version where the computer makes more calculated moves. The computer chooses the next square based on a score system, where winning moves result in a higher best score (also called a minimax function). Then I added depth, meaning the computer would rather win earlier, and if not possible, lose as late as possible. Depth also improves the game by allowing the computer to think a few moves in advance. Against human gameplay (me), the computer is very much unbeatable.

test_project.c is the code for testing the ability of the computer. Manually going over thousands of games is tedious and unpractical, thus I  simulated 10000 games against random input, and the computer won over 80% of the times.
