# Tic-Tac-Toe Game

A simple 2-player Tic-Tac-Toe game built in C++. The game can be played by two players on the same machine, taking turns to mark their moves on a 3x3 grid. The game ends when one player wins or if there are no more available moves, resulting in a draw.

## Features
- Play with two players.
- User-friendly interface to show the current game board.
- Check for a winner or draw after every move.
- Input validation to prevent invalid moves.

## Game Rules
- Players take turns marking a spot on the 3x3 grid with 'O' or 'X'.
- The first player to align 3 of their symbols in a row (horizontally, vertically, or diagonally) wins.
- The game ends in a draw if all spots are filled without a winner.

## How to Play
1. Clone the repository:
    ```bash
    git clone https://github.com/soumik-prime/tic-tac-toe.git
    cd tic-tac-toe
    ```

2. Compile the code using g++:
    ```bash
    g++ -o tic-tac-toe main.cpp
    ```

3. Run the game:
    ```bash
    ./tic-tac-toe
    ```

4. Enter your names and follow the on-screen instructions to play the game!

## Code Explanation
- **User Class**: Stores player information such as the name and the move identifier (1 or 2).
- **Board Representation**: A 3x3 grid is used to represent the game board, with '1' for player 1 ('O') and '2' for player 2 ('X').
- **Gameplay Loop**: Players alternate turns to input a move (between 1 and 9) until a winner is found or a draw occurs.
- **Winner Check**: The game checks for winners after each move by verifying rows, columns, and diagonals.
