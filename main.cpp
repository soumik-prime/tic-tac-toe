// Author: Md. Samiul Islam Soumik
// Date:   2025.03.03
// Time:   20:46:06

#include <bits/stdc++.h>
#include <cstdlib> // For system("clear")
#include<unistd.h>
using namespace std;

// Class to store user information
class user
{
public:
    string name; // Stores player's name
    int id;      // Unique ID to identify moves (1 = first user, 2 = second user)
};

// Function to set unique usernames for both players
void setUser(user &first, user &second)
{
    while (true)
    {
        cout << "First User Name: ";
        cin >> first.name; // Get first user's name
        cout << "Second User Name: ";
        cin >> second.name; // Get second user's name

        // Clear screen for better user experience
        system("clear");

        if (first.name != second.name)
            break; // Ensure usernames are unique

        // Display message if both players enter the same name
        cout << "Why are you trying to play alone?" << endl
             << "Don't you have any friends?" << endl
             << endl;
    }
}

// Function to display player names before the game starts
void header(user first, user second)
{
    cout << "User 1: " << first.name << (first.id == 1 ? ("(o)") : ("(x)")) << "\t";
    cout << "User 2: " << second.name << (second.id == 1 ? ("(o)") : ("(x)")) << endl;
}

// Function to display the board's input format before the game starts
void modelArena()
{
    cout << "Play your part according to the following model: " << endl
         << endl;
    cout << "\t" << " 1 | 2 | 3 " << endl;
    cout << "\t" << "-----------" << endl;
    cout << "\t" << " 4 | 5 | 6 " << endl;
    cout << "\t" << "-----------" << endl;
    cout << "\t" << " 7 | 8 | 9 " << endl;
    cout << endl;
}

// Function to display the main Tic-Tac-Toe board
void mainArena(vector<vector<int>> v)
{
    cout << endl;
    for (int i = 0; i < 9; i++)
    {
        int quotient = i / 3;
        int remainder = i % 3;
        char ch = ' ';

        // Assign player symbols based on the board state
        if (v[quotient][remainder] == 1)
            ch = 'o';
        else if (v[quotient][remainder] == 2)
            ch = 'x';

        cout << " " << ch << " ";
        if (remainder != 2)
            cout << "|";
        else
            cout << endl;

        if (remainder == 2 && i != 8)
            cout << "-----------" << endl;
    }
    cout << endl;
}

// Function to take user input and update the board
void takeInput(user currentMove, vector<vector<int>> &v)
{
    while (true)
    {
        int temp;
        cout << currentMove.name << "'s turn: ";

        // Input validation with error handling
        try
        {
            cin >> temp;

            // Check if input is a valid integer
            if (cin.fail())
            {
                throw invalid_argument("Invalid input! Please enter an integer.");
            }

            // Validate the move (should be between 1 and 9)
            if (temp < 1 || temp > 9)
            {
                cout << "Invalid Move! Please enter a number between 1 and 9." << endl;
                continue;
            }

            temp--; // Convert to 0-based index
            int quotient = temp / 3;
            int remainder = temp % 3;

            // Check if the selected cell is empty
            if (v[quotient][remainder] == 0)
            {
                v[quotient][remainder] = currentMove.id; // Mark the move
                    cout.flush();
                    usleep(300000);
                break;
            }

            cout << temp + 1 << " is already taken! Try again!" << endl;
        }
        catch (const invalid_argument &e)
        {
            cout << e.what() << endl;

            // Clear error state and ignore invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Function to check if any move is available
bool moveAvailibility(vector<vector<int>> v)
{
    int count = 0;
    for (auto row : v)
    {
        for (auto cell : row)
            if (cell != 0)
                count++; // Count occupied cells
    }
    return count != 9; // Returns true if moves are still available
}

// Function to check if there's a winner
int checkWinner(vector<vector<int>> &board)
{
    // Check rows for a win
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
    }

    // Check columns for a win
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }

    // Check main diagonal for a win
    if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];

    // Check anti-diagonal for a win
    if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];

    return 0; // No winner
}

// 1. Play with Friend
void playWithFriend()
{
    system("clear");
    user first, second;          // Creating player objects
    first.id = 1, second.id = 2; // Assigning unique IDs

    vector<vector<int>> v(3, vector<int>(3)); // Initializing empty 3x3 board

    setUser(first, second); // Collecting unique usernames

    user currentMove = first; // First player starts the game

    while (true)
    {
        modelArena();          // Displaying model board
        header(first, second); // Displaying player names
        mainArena(v);          // Displaying current board state

        int temp = checkWinner(v); // Check for a winner
        if (temp != 0)
        {
            cout << (temp == 1 ? first.name : second.name) << " wins!" << endl
                 << endl;
            cout << "Thanks for Playing!" << endl
                 << endl;
            break;
        }

        if (!moveAvailibility(v))
        {
            // Check for a draw
            cout << "Out of Moves!" << endl;
            cout << "-----Draw-----" << endl
                 << endl;
            cout << "Thanks for Playing!" << endl
                 << endl;
            break;
        }

        takeInput(currentMove, v);                                   // Taking player input and updating the board
        currentMove = (currentMove.id == first.id) ? second : first; // Swapping turns

        // Clear screen to refresh the board
        system("clear");
    }
}

void takeInputNovice(user currentMove, vector<vector<int>> &v)
{
    if (currentMove.id == 2)
    {
        cout << currentMove.name << "'s turn: ";
        for(int i = 0; i < 5; i++){
            cout << '.';
            cout.flush();
            usleep(500000);
        }
        while (true)
        {
            int temp;
            temp = rand()%9;
            int quotient = temp / 3;
            int remainder = temp % 3;

            // Check if the selected cell is empty
            if (v[quotient][remainder] == 0)
            {
                v[quotient][remainder] = currentMove.id; // Mark the move
                break;
            }
        }
    }
    else
    {
        while (true)
        {
            cout << currentMove.name << "'s turn: ";
            int temp;
            // Input validation with error handling
            try
            {
                cin >> temp;

                // Check if input is a valid integer
                if (cin.fail())
                {
                    throw invalid_argument("Invalid input! Please enter an integer.");
                }

                // Validate the move (should be between 1 and 9)
                if (temp < 1 || temp > 9)
                {
                    cout << "Invalid Move! Please enter a number between 1 and 9." << endl;
                    continue;
                }

                temp--; // Convert to 0-based index
                int quotient = temp / 3;
                int remainder = temp % 3;

                // Check if the selected cell is empty
                if (v[quotient][remainder] == 0)
                {
                    v[quotient][remainder] = currentMove.id; // Mark the move
                    cout.flush();
                    usleep(300000);
                    break;
                }

                cout << temp + 1 << " is already taken! Try again!" << endl;
            }
            catch (const invalid_argument &e)
            {
                cout << e.what() << endl;

                // Clear error state and ignore invalid input
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    
}

// Difficulty Novice
void noviceLevel()
{
    system("clear");
    user first, second;          // Creating player objects
    first.id = 1, second.id = 2; // Assigning unique IDs

    vector<vector<int>> v(3, vector<int>(3)); // Initializing empty 3x3 board
    cout << "Enter User Name: ";
    cin >> first.name;
    second.name = "Computer";
    if (rand() % 2)
        swap(first, second);

    user currentMove = first; // First player starts the game

    while (true)
    {
        modelArena();          // Displaying model board
        header(first, second); // Displaying player names
        mainArena(v);          // Displaying current board state

        int temp = checkWinner(v); // Check for a winner
        if (temp != 0)
        {
            string str = (temp == first.id ? first.name : second.name);
            if(str != "Computer") cout << str << " wins!" << endl << endl;
            else cout << "You lost!" << endl << endl;
            cout << "Thanks for Playing!" << endl
                 << endl;
            break;
        }

        if (!moveAvailibility(v))
        {
            // Check for a draw
            cout << "Out of Moves!" << endl;
            cout << "-----Draw-----" << endl
                 << endl;
            cout << "Thanks for Playing!" << endl
                 << endl;
            break;
        }

        takeInputNovice(currentMove, v);                             // Taking player input and updating the board
        currentMove = (currentMove.id == first.id) ? second : first; // Swapping turns

        // Clear screen to refresh the board
        system("clear");
    }
}

// 2. Play with Computer
void playWithComputer()
{
    system("Clear");
    cout << "Choose Difficulty: " << endl;
    cout << "1. Novice" << endl;
    cout << "2. Expert" << endl;
    cout << "3. Impossible" << endl;
    int difficulty;
    cout << "Your Choice: ";
    cin >> difficulty;
    if (difficulty == 1)
        noviceLevel();
}

// Main function to run the Tic-Tac-Toe game
int main()
{
    // Clearing the console screen at the beginning
    system("clear");
    cout << "Mode:" << endl;
    cout << "1. Play with Friend" << endl;
    cout << "2. Play with Computer" << endl;
    cout << "Your Choice: ";
    int mode;
    cin >> mode;
    if (mode == 1)
        playWithFriend();
    else
        playWithComputer();
}
