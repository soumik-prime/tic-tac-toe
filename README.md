# Tic-Tac-Toe Game

This is a simple Tic-Tac-Toe game implemented in C++. It supports both **two-player mode** and **player vs. system mode** with selectable difficulty levels and move orders. The game is played on a 3x3 grid, and players alternate turns to place their mark ('X' or 'O') on the grid, aiming to be the first to get three marks in a row (horizontally, vertically, or diagonally).

## Features

- **Two-Player Mode**: Allows two players to play locally.
- **Player vs System Mode**: The player can play against the system, with different difficulty levels.
- **Difficulty Levels**:
  - **Novice**: The system makes random moves.
  - **Expert**: The system uses a more intelligent algorithm to block and win.
  - **Unbeatable**: The system uses a perfect strategy (Minimax algorithm) to never lose.
- **Move Order Selection**: Choose to go first, second, or let the game decide randomly.
- **Game State Display**: The current state of the game board is displayed after each move.
- **Input Validation**: Ensures only valid moves are made.

## Installation

1. **Clone the repository**:
    ```bash
    git clone https://github.com/soumik-prime/tic-tac-toe.git
    ```

2. **Navigate into the project folder**:
    ```bash
    cd tic-tac-toe
    ```

3. **Compile the code**:
    ```bash
    g++ -o tic-tac-toe main.cpp
    ```

4. **Run the game**:
    ```bash
    ./tic-tac-toe
    ```

## Usage

1. Upon starting the game, choose your preferred mode:
   - **1**: Play with a friend (Two-Player Mode)
   - **2**: Play with the system (Player vs System Mode)

2. If you choose to play against the system:
   - Select the difficulty level:
     - **1**: Novice
     - **2**: Expert
     - **3**: Unbeatable
   - Choose your move order:
     - **1**: First move
     - **2**: Second move
     - **3**: Random move

3. During the game, the board will be displayed, and you'll be prompted to make your move by choosing a number (1-9), corresponding to an empty spot on the grid.

4. The game ends when a player wins or when the game ends in a draw.

## Code Structure

- **Player Class**: Represents a player (either human or system). Stores player information like name, ID, and whether they are system-controlled.
- **Game Logic**: The core logic to manage the game, check for winners, and handle moves.
- **Game Board**: A 3x3 grid to represent the game state. The board is displayed after every move.
