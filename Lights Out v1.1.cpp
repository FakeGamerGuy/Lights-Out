#include <iostream>
#include <string>
using namespace std;

int main()
{
    bool winGame = false;
    bool quitGame = false;
    bool gameBoard[25];
    for(int i=0; i<25; i++) // Initializes a blank game board
    {
        gameBoard[i]=false;
    }
    int lightsLeft = 0;
    int buttonArray = 0;
    string buttonPress = "3C";
    string passphrase = "@@@@@";
    string userInput = "1248F"; // these values do not actually equal 1, 2, 4... etc in decimal or hex
    
    cout << "Lights Out(TM)\n";
    cout << "by Tiger Electronics, 1995\n\n";
    cout << "Enter 5 character passphrase:" << endl;
    cout << "(Example, ABCDE): ";
    cin >> userInput;

    /*
    We need the 5 least significant bits to generate a game board, which is 32 in decimal.
    If we mod each character by 32 we get 0-31 which is exactly what we want.
    gameBoard[0]=((userInput[0]%32)&1) to get the first bit of the first user input character.
    gameBoard[1]=((userInput[0]%32)&2)
    ...
    gameBoard[4]=((userInput[0]%32)&16)
    gameBoard[5]=((userInput[1]%33)&1)
    */
    
    for(int i=0; i<25;)
    {
        for(int j=0; j<5; j++)
        {
            gameBoard[i++]=((userInput[j]%32)&1);
            gameBoard[i++]=((userInput[j]%32)&2);
            gameBoard[i++]=((userInput[j]%32)&4);
            gameBoard[i++]=((userInput[j]%32)&8);
            gameBoard[i++]=((userInput[j]%32)&16);
        }
    }

    cout << endl;

    // End game setup, start main game loop

    do
    {
        // Draw the game board
        cout << "  A  B  C  D  E" << endl;
        for(int i=0; i<5; i++)
        {
            cout << i+1;
            for(int j=0; j<5; j++)
            {
                if(gameBoard[(i*5+j)])
                {
                    cout << " ▓▓";
                }
                else
                {
                    cout << " ░░";
                }
            }
            cout << endl << endl;
        }
        
        cout << "Pick a button to press\n";
        cout << "(H for help, Q to quit): ";
        cin >> buttonPress;

        buttonPress[0]=toupper(buttonPress[0]);
        buttonPress[1]=toupper(buttonPress[1]);

        switch(buttonPress[0])
        {
            case 'Q':
                quitGame=true;
                cout << "\nIf you want to continue, use the passcode:\n";
                
                // Creating the passphrase to resume the game
                // Bool values are treated like a single binary value to create an ASCII character
                // then added to the default value of @, which is a blank row, then the values immediate
                // above it are all letters and simple special characters.
                for(int i=0; i<5; i++)
                {
                    passphrase[i] += gameBoard[(i*5)+0]*1 + gameBoard[(i*5)+1]*2 + gameBoard[(i*5)+2]*4 + gameBoard[(i*5)+3]*8 + gameBoard[(i*5)+4]*16;
                    cout << passphrase[i];
                }
                cout << endl;
                break;
            case 'H':
                cout << "\nThe objective of Lights out is to turn off all the lights.\n";
                cout << "on the game board. When you press a button, it turns ON if it was OFF,\n";
                cout << "and OFF if it was ON, and so will the buttons above, below, and to the sides\n";
                cout << "in a cross-shape. In the example below, pressing the middle button on the left\n";
                cout << "game board results in the center light turning on, and the lights around it turning off.\n\n";
                cout << "  A  B  C  D  E \t A  B  C  D  E\n";
                cout << "1 ░░ ░░ ░░ ░░ ░░\t1 ░░ ░░ ░░ ░░ ░░\n\n";
                cout << "2 ░░ ░░ ▓▓ ░░ ░░\t2 ░░ ░░ ░░ ░░ ░░\n\n";
                cout << "3 ░░ ▓▓ ░░ ▓▓ ░░\t3 ░░ ░░ ▓▓ ░░ ░░\n\n";
                cout << "4 ░░ ░░ ▓▓ ░░ ░░\t4 ░░ ░░ ░░ ░░ ░░\n\n";
                cout << "5 ░░ ░░ ░░ ░░ ░░\t5 ░░ ░░ ░░ ░░ ░░\n\n";
                break;
            default:
                buttonPress[0]-=48; // 0-9 in ASCII is 48-57
                // Convert row+column input to 0-24
                // A = 65 in ASCII
                // Input = 3C to push button 12
                // ((row-1)*5) + column
                
                buttonArray = ((buttonPress[0]-1)*5)+(buttonPress[1]-65);
                gameBoard[buttonArray]=!gameBoard[buttonArray];   // Invert the pressed button
                if((buttonArray-5)>=0)                                   // Invert the button above
                {
                    gameBoard[(buttonArray-5)]=!gameBoard[(buttonArray-5)];
                }
                if((buttonArray+5)<25)                                   // Invert the button below
                {
                    gameBoard[(buttonArray+5)]=!gameBoard[(buttonArray+5)];
                }
                if((buttonArray%5)>0)                                    // Invert the button to the left
                {
                    gameBoard[(buttonArray-1)]=!gameBoard[(buttonArray-1)];
                }
                if((buttonArray%5)<4)                                    // Invert the button to the right
                {
                    gameBoard[(buttonArray+1)]=!gameBoard[(buttonArray+1)];
                }
                cout << endl;
        }

        // Check to see if the player won
        lightsLeft=0;
        for(int i=0; i<25; i++)
        {
            lightsLeft+=gameBoard[i];
        }
        if(lightsLeft==0)
        {
            winGame=true;
        }
    } while(!quitGame && !winGame);
    
    if(winGame)
    {
        // Draw the game board
        cout << "  A  B  C  D  E" << endl;
        for(int i=0; i<5; i++)
        {
            cout << i+1;
            for(int j=0; j<5; j++)
            {
                if(gameBoard[(i*5+j)])
                {
                    cout << " ▓▓";
                }
                else
                {
                    cout << " ░░";
                }
            }
            cout << endl << endl;
        }
        cout << "Congratulations, you won!";
    }

    cout << endl;

    return 0;
}