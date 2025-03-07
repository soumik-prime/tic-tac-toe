// Auther: Md. Samiul Islam Soumik
// Date:   2025.03.06
// Time:   23:04:06
#include<bits/stdc++.h>
#include <cstdlib> // For system("clear")
#include<unistd.h> // For usleep(<duration>)
using namespace std;
/**
 *    author:  Md. Samiul Islam Soumik
 *    created: 2025.03.06 23:10:00
 *    Purpose: A class representing a player in the game.
 *    Members:
 *        name      - The name of the player.
 *        id        - The unique identifier for the player.
 *        computer  - A boolean indicating whether the player is controlled by AI.
 */
class Player{
private:
    bool computer = false;  // Indicates if the player is AI-controlled
public:
    string name;  // Player's name
    int id;       // Unique player identifier
    // Constructor to initialize a player with a given ID.
    Player(int id){
        this->id = id;
    }
    // Marks this player as a computer-controlled player.
    void markAsComputer(){
        computer = true;
    }
    // Checks if the player is controlled by Computer.
    bool isComputer(){
        return computer;
    }
};
void startTwoPlayerGame();
void startGameWithComputer();
void displayGameBoard();
void gameBoardState(vector<vector<int>> &board);
bool moveAvailable(vector<vector<int>> &board, int move);
void promptPlayerMove(vector<vector<int>> &board, Player player, int difficultyLevel);
int noviceLevelMove(vector<vector<int>> &board);
void displayPlayerInfo(Player player1, Player player2);
int checkForWinner(vector<vector<int>> &board);
bool checkForDraw(vector<vector<int>> &board);
int expertLevelMove(vector<vector<int>> &board, Player computer);
/**
 *    author:  Md. Samiul Islam Soumik
 *    created: 2025.03.06 23:15:00
 *    Purpose: Main function to start the game and handle user input for selecting game modes.
 */
int main(){
    // Clear the screen for fresh start
    system("clear");
    // Distplay the mode selection options
    cout << "Choose the mode you want to play:" << "\n";
    cout << "1. Play with friend" << "\n";
    cout << "2. Play with Computer" << "\n";
    int gameMode;   // Variable to store the selected mode
    while(true){    // Loop for ensuring valid input selection
        try{
            // Prompt the user to make a selection
            cout << "Your Choice: ";
            cin >> gameMode;
            // Flush the output buffer to ensure prompt displayed immediately
            cout.flush();
            // Sleep briefly to make the game experience smoother
            usleep(300000);
            // Check the input stream fail (non-integer input)
            if(cin.fail()){
                throw invalid_argument("Please enter either 1 or 2 based on your preference.");
            }
            // Check if the player selected a vaild game mode
            if(gameMode == 1){
                startTwoPlayerGame();    // Start two player game mode
                break;    // exit loop after valid input
            }
            else if(gameMode == 2){
                startGameWithComputer();    // Start game with computer mode
                break;    // exit loop after valid input
            }else{
                // if the input is neither 1 nor 2, show error massage
                cout << "Please enter either 1 or 2 based on your preference." << "\n";
            }
        }
        catch(const invalid_argument &e){
            // Handle invalid input and show error massage
            cout << e.what() << "\n";
            cin.clear();    // Clear the error state of input stream
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    // Ignore any remaining invalid input
        }
    }
    // Thank you note at end of the match
    string thankYouNote = "Thank you for playing...";
    cout << "\n";
    for(auto ch : thankYouNote){
        cout.flush();
        usleep(300000);
        cout << ch;
    }
    cout.flush();
    usleep(500000);
    return 0;   // End of Program
}
/**
 *    author:  Md. Samiul Islam Soumik
 *    created: 2025.03.06 23:56:04
 *    Purpose: Start two player game by collecting the name of both players
 *    Parameters: none
 *    Returns: none
 */
void startTwoPlayerGame(){
    // Clear the console screen for prepare for the game
    system("clear");
    // Declare Player object for Player 1 and Player 2 and Initialize their id
    Player player1(1), player2(2);    // Game start with player who's is id 1
    while(true){
        // Prompt Player 1 to enter their name and store it
        cout << "Enter Player 1 name: ";
        cin >> player1.name;
        // Prompt Player 2 to enter their name and store it
        cout << "Enter Player 2 name: ";
        cin >> player2.name;
        // Flush the output buffer to ensure prompt displayed immediately
        cout.flush();
        // Sleep briefly to make the game experience smoother
        usleep(300000);
        if(player1.name != player2.name){
            break;
        }else{
            // Clear the console for clearness
            system("clear");
            // Prompt user to use different name for players
            cout << "If you don't have friend play with computer or use different names for two player!" << "\n";
        }
    }
    // Prompt Player that the game is starting
    cout << "Game is Starting";
    for(int i = 0; i < 3; i++){
        cout << ".";
        // Flush the output buffer to ensure prompt displayed immediately
        cout.flush();
        // Sleep briefly to make the game experience smoother
        usleep(300000);
    }
    // Initializing 3x3 game board
    vector<vector<int>> board(3, vector<int>(3, 0));
    // Initializing Player who's going make first move
    Player currentPlayer = player1;
    // Star the two player game
    while(true){
        int winnerId = checkForWinner(board);
        bool isDraw = checkForDraw(board);
        // Clear the console screen for prepare for the game
        system("clear");
        displayPlayerInfo(player1, player2);
        displayGameBoard();
        gameBoardState(board);
        // Check if there is a winner
        if(winnerId != -1){
            // Prompt Player the winner of the game
            cout << (winnerId == 1 ? player1.name : player2.name) << " win!" << "\n";
            break;
        }
        else if(isDraw){
            cout << "The match is Draw!" << "\n";
            break;
        }
        if(winnerId == -1 || !isDraw) promptPlayerMove(board, currentPlayer, -1);
        currentPlayer = currentPlayer.id == player1.id ? player2 : player1;
    }
}
/**
 *    author:  Md. Samiul Islam Soumik
 *    created: 2025.03.07 00:07:59
 *    Purpose: Start playing with computer by collecting play name and difficulty level and move order
 *    Parameters: none
 *    Returns: none
 */
void startGameWithComputer(){
    // Declare Player object for Player and Computer and Initialize their id
    Player player(1), computer(2);  // Game start with player who's is id 1
    // Clear the console screen for prepare for the game
    system("clear");
    while(true){
        // Prompt Player to enter their name and store it
        cout << "Enter Player Name: ";
        cin >> player.name;
        // Flush the output buffer to ensure prompt displayed immediately
        cout.flush();
        // Sleep briefly to make the game experience smoother
        usleep(300000);
        // Check if player input their name 'computer', if true then take input again
        string playerName = player.name;
        transform(playerName.begin(), playerName.end(), playerName.begin(), ::toupper);
        if(playerName == "COMPUTER"){
            cout << "Illegal Player Name! Try another" << "\n";
        }
        else{
            // Clear the console screen for clearness
            system("Clear");
            break;
        }
    }
    // Initialize computer object property name as "Computer" and make it as computer
    computer.name = "Computer";
    computer.markAsComputer();
    // Display difficulty selection options
    cout << "Choose Difficulty Level: " << "\n";
    cout << "1. Novice" << "\n";
    cout << "2. Expert" << "\n";
    cout << "3. Unbeatable" << "\n";
    int difficultyLevel;
    while (true) {  // Loop for ensuring vaild difficulty level selection
        // Prompt the user to make a selection
        cout << "Your Choice: ";
        cin >> difficultyLevel;
        // Check if player select vaild difficulty level
        if (cin.fail() || difficultyLevel < 1 || difficultyLevel > 3) {
            // If player select an invalid difficulty level throw error
            cout << "Please enter 1, 2, or 3 based on your preference.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            // If player select a valid difficulty level stop the loop
            break;
        }
    }
    // Flush the output buffer to ensure prompt displayed immediately
    cout.flush();
    // Sleep briefly to make the game experience smoother
    usleep(300000);
    // Clear the console screen for clearness
    system("Clear");
    // Display move order options
    cout << "Choose your move order:\n";
    cout << "1. First Move\n";
    cout << "2. Second Move\n";
    cout << "3. Random Move\n";
    int moveOrder;
    while (true) {  // Loop for ensuring vaild difficulty level selection
        // Prompt the user to make a selection
        cout << "Your Choice: ";
        cin >> moveOrder;
        // Check if player select vaild option
        if (cin.fail() || moveOrder < 1 || moveOrder > 3){
            // If player select an invalid option throw error
            cout << "Please enter 1, 2, or 3 based on your preference.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else{
            // If player select a valid difficulty level stop the loop
            break;
        }
    }
    // Setting player id based on move order
    if(moveOrder == 2 || (moveOrder == 3 && rand()%2 == 0)){
        swap(player.id, computer.id);
    }
    // Flush the output buffer to ensure prompt displayed immediately
    cout.flush();
    // Sleep briefly to make the game experience smoother
    usleep(300000);
    // Prompt Player that the game is starting
    cout << "Game is Starting";
    for(int i = 0; i < 3; i++){
        cout << ".";
        // Flush the output buffer to ensure prompt displayed immediately
        cout.flush();
        // Sleep briefly to make the game experience smoother
        usleep(300000);
    }
    // Initializing 3x3 game board
    vector<vector<int>> board(3, vector<int>(3, 0));
    // Initializing Player who's going make first move
    Player currentPlayer = player.id == 1 ? player : computer;
    // Star the two player game
    while(true){
        int winnerId = checkForWinner(board);
        bool isDraw = checkForDraw(board);
        // Clear the console screen for prepare for the game
        system("clear");
        displayPlayerInfo(player, computer);
        displayGameBoard();
        gameBoardState(board);
        // Check if there is a winner
        if(winnerId != -1){
            // Prompt Player the winner of the game
            if(winnerId == player.id){
                cout << "You win!" << "\n";
            }
            else{
                cout << "You lose!" << "\n";
            }
            break;
        }
        else if(isDraw){
            cout << "The match is Draw!" << "\n";
            break;
        }
        if(winnerId == -1 || !isDraw) promptPlayerMove(board, currentPlayer, difficultyLevel);
        currentPlayer = currentPlayer.id == player.id ? computer : player;
    }
}
/**
 *    author:  Md. Samiul Islam Soumik
 *    created: 2025.03.07 01:04:39
 *    Purpose: to display the current game board, where each cell is represented by a number (1-9), which players can choose from to make their moves
 *    Parameters: none
 *    Returns: none
 */
void displayGameBoard(){
    // Display game board tample
    cout << "  " << " 1 | 2 | 3 " << "\n";
    cout << "  " << "-----------" << "\n";
    cout << "  " << " 4 | 5 | 6 " << "\n";
    cout << "  " << "-----------" << "\n";
    cout << "  " << " 7 | 8 | 9 " << "\n";
    cout << "\n";
    cout << "Select your move by entering" << "\n" << "a number between 1 and 9:" << "\n";
}
/**
 *    author:  Md. Samiul Islam Soumik
 *    created: 2025.03.07 01:19:04
 *    Purpose: Displays the real-time state of the game board.
 *    Parameters: 
 *        board - A 2D vector representing the game board (3x3 grid) where each cell is either 0 (empty), 1 (player 1's move), or 2 (player 2's move).
 *    Returns: void
 */
void gameBoardState(vector<vector<int>> &board) {
    cout << "\n";
    for(int i = 0; i < 9; i++) {
        int rowIndex = i / 3, colIndex = i % 3;
        string cellValue = "   ";  // Default empty cell
        if(board[rowIndex][colIndex] == 1) cellValue = " x ";  // Player 1's move
        else if(board[rowIndex][colIndex] == 2) cellValue = " o ";  // Player 2's move
        if(colIndex == 0) cout << "  ";
        cout << cellValue;
        if (colIndex != 2) {
            cout << "|";  // Print a separator between cells
        } else {
            cout << "\n";
            if(i != 8) cout << "  " << "-----------" << "\n";  // Print separator between rows
        }
    }
    cout << "\n";
}
/**
 *    author:  Md. Samiul Islam Soumik
 *    created: 2025.03.07 02:13:39
 *    Purpose: Check if the given move is available.
 *    Parameters: 
 *        board - A 2D vector representing the game board (3x3 grid) where each cell is either 0 (empty), 1 (player 1's move), or 2 (player 2's move).
 *        move - An integer representing the position (1-9) on the board, where 1 corresponds to the top-left cell, 9 corresponds to the bottom-right cell.
 *    Returns: true if the move is available (the cell is empty), false otherwise.
 */
bool moveAvailable(vector<vector<int>> &board, int move){
    int rowIndex = (move - 1) / 3;  // Adjust move to 0-indexed
    int colIndex = (move - 1) % 3;  // Adjust move to 0-indexed
    return board[rowIndex][colIndex] == 0;  // Return true if the cell is empty
}
/**
 *    author:  Md. Samiul Islam Soumik
 *    created: 2025.03.07 08:44:32
 *    Purpose: To take a move from the player or computer and store it in the game board.
 *    Parameters: 
 *        board - A 2D vector representing the game board (3x3 grid), where each cell is either:
 *                0 (empty), 1 (player 1's move), or 2 (player 2's move). 
 *        player - A Player object representing the current player taking the turn.
 *        difficultyLevel - An integer that determines Game difficulty level when playing against the computer.
 *                         - (-1): Two-player game (Ignore, human vs human)
 *                         - 1: Easy (random moves)
 *                         - 2: Medium (some strategy)
 *                         - 3: Hard (optimal moves)
 *    Returns: none
 */

void promptPlayerMove(vector<vector<int>> &board, Player player, int difficultyLevel = -1){
    int move;
    if(!player.isComputer()){
        while(true){
            cout << player.name << "'s turn: ";
            cin >> move;
            // Flush the output buffer to ensure prompt display immediately
            cout.flush();
            // Sleep briefly make game experience smoother
            usleep(300000);
            // Check if the move is integer
            if (cin.fail()) { 
                // if selected move is not an integer show error massage
                cin.clear();  // Reset cin state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Please enter a legal move (1-9)!\n";
                continue;
            }
            // Check if selected move is valid(range 1-9) and is available
            if(move < 1 || move > 9){
                cout << "Please enter a legal move (1-9)!" << "\n";
            }
            else if(!moveAvailable(board, move)){
                cout << "Please ensure the move is available!" << "\n";
            }
            else{
                // if selected move is valid exit the loop
                break;
            }
        }
    }
    else{
        cout << player.name << "'s turn:";
        if(difficultyLevel == 1) move = noviceLevelMove(board);
        else if(difficultyLevel == 2) move = expertLevelMove(board, player);
        // Flush the output buffer to ensure prompt display immediately
        cout.flush();
        // Sleep briefly make game experience smoother
        usleep(500000);
        for(int i = 0; i < 3; i++){
            cout << ".";
            // Flush the output buffer to ensure prompt display immediately
            cout.flush();
            // Sleep briefly make game experience smoother
            usleep(300000);
        }
    }

    int rowIndex = (move - 1) / 3;  // Adjust move to 0-indexed
    int colIndex = (move - 1) % 3;  // Adjust move to 0-indexed
    board[rowIndex][colIndex] = player.id;
}
/**
 *    author:  Md. Samiul Islam Soumik
 *    created: 2025.03.07 10:25:05
 *    Purpose: Displaying Player information on the top of the game board
 *    Parameters: 
 *        player1 - An object that contain player 1 information
 *        player2 - An object that contain player 2 information
 *    Returns: none
 */
void displayPlayerInfo(Player player1, Player player2){
    // Setting player 1 who's id is 1
    if(player1.id == 2) swap(player1, player2);
    // Display players name and their move mark
    cout << "Player 1: " << player1.name << "(x)" << "\n";
    cout << "Player 2: " << player2.name << "(o)" << "\n\n";
}
/**
 *    author:  Md. Samiul Islam Soumik
 *    created: 2025.03.07 11:27:54
 *    Purpose: Checking if there is an winner
 *    Parameters: 
 *        board - A 2D vector representing the game board (3x3 grid), where each cell is either 0 (empty), 1 (player 1's move), or 2 (player 2's move).
 *    Returns: An interger representing the winner id, if there is no winner the integer is -1
 */
int checkForWinner(vector<vector<int>> &board){
    // Checking rows for a win
    for(int i = 0; i < 3; i++){
        if(board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2]){
            return board[i][0];
        }
    }
    // Checking columns for a win
    for(int i = 0; i < 3; i++){
        if(board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i]){
            return board[0][i];
        }
    }
    // Checking main diagonal for a win
    if(board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2]){
        return board[0][0];
    }
    // Checking anti-diagonal for a win
    if(board[0][2] != 0 && board[0][2] == board[1][1] && board[2][0] == board[1][1]){
        return board[1][1];
    }
    // if there is no winner return -1
    return -1;
}
/**
 *    author:  Md. Samiul Islam Soumik
 *    created: 2025.03.07 11:42:58
 *    Purpose: Chech if there is any empty cell available for next move
 *    Parameters: 
 *        board - A 2D vector representing the game board (3x3 grid), where each cell is either 0 (empty), 1 (player 1's move), or 2 (player 2's move).
 *    Returns: An boolian value, true if there is no empty cell(draw), false if there is a cell for next move
 */
bool checkForDraw(vector<vector<int>> &board){
    for(auto row : board){
        for(auto cell : row){
            if(cell == 0){
                // if cell value is 0(empty), then it is not draw
                return false;
            }
        }
    }
    // if there is not any empty cell, it is draw
    return true;
}
/**
 *    author:  Md. Samiul Islam Soumik
 *    created: 2025.03.07 10:20:56
 *    Purpose: Generate move at novice level
 *    Parameters: 
 *        board - A 2D vector representing the game board (3x3 grid), where each cell is either 0 (empty), 1 (player 1's move), or 2 (player 2's move).
 *    Returns: An integer representing a randomly chosen move (1-9)
 */
int noviceLevelMove(vector<vector<int>> &board){
    while(true){
        // Generate random move between 1 to 9
        int move = rand()%9 + 1;
        // Check if move is available
        if(moveAvailable(board, move)){
            // if available return the value
            return move;
        }
    }
}
/**
 *    author:  Md. Samiul Islam Soumik
 *    created: 2025.03.07 13:05:01
 *    Purpose: Determines the best move for the computer in a Tic-Tac-Toe game.
 *             First, it checks if there is a move that will ensure a win for the computer.
 *             If no winning move is available, it checks if there is a move to block the opponent from winning.
 *             If neither of the above options is possible, it selects a random available move.
 *    Parameters:
 *        board - A 2D vector representing the game board (3x3 grid), where each cell is either 0 (empty), 1 (player 1's move), or 2 (player 2's move).
 *        computer - An object representing the computer player
 *    Returns:
 *        An integer (1-9) corresponding to a valid move on the board.
 */
int expertLevelMove(vector<vector<int>> &board, Player computer){
    // Try to find a winnig move for Computer
    for(int move = 1; move <= 9; move++){
        int rowIndex = (move - 1) / 3;  // Adjust move to 0-indexed
        int colIndex = (move - 1) % 3;  // Adjust move to 0-indexed
        if(board[rowIndex][colIndex] != 0) continue;
        vector<vector<int>> tempBoard(board);
        tempBoard[rowIndex][colIndex] = computer.id;
        if(checkForWinner(tempBoard) == computer.id){
            return move;
        }
    }
    // Try to block opponent's winning move
    for(int move = 1; move <= 9; move++){
        int rowIndex = (move - 1) / 3;  // Adjust move to 0-indexed
        int colIndex = (move - 1) % 3;  // Adjust move to 0-indexed
        if(board[rowIndex][colIndex] != 0) continue;
        vector<vector<int>> tempBoard(board);
        tempBoard[rowIndex][colIndex] = computer.id == 1 ? 2 : 1;
        if(checkForWinner(tempBoard) != -1 && checkForWinner(tempBoard) != computer.id){
            return move;
        }
    }
    // If no winning or blocking move is found, use random move
    return noviceLevelMove(board);
}
