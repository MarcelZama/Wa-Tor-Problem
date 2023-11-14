#include <iostream>
#include <cstdlib> // Include the necessary header for srand and rand
#include <ctime>   // Include the necessary header for time
#include <stdlib.h>     //for using the function sleep
#include <chrono>
#include <thread>

//Creator : Marcel Zama C00260146
//Date : 13/11/2023
// Title : Wa-Tor simulation working sequencially


// To Do: Add if(x=size -1) x= arr[0] coroce daca ajiunge la sfirsit de harta sa se uite la inceput de harta
//        Add skip after one fish / shark 
using namespace std;

enum CellType { Ocean, Fish, Shark };

int getrandom()
{
    // Get a random number
    int RandIndex = rand() % 10;

    // Print the random number
    cout << RandIndex << endl;

    return RandIndex;
}

int main()
{
    struct Cell {
        CellType cellType;
        int sharkEnergy;
        int fishBirth;
    };

    // Seed the random number generator once in the program
    srand(static_cast<unsigned>(time(NULL)));

    const int size = 10;
    Cell table[size][size];

    for (int x = 0; x < size; x++) //Initiate all cells to Ocean
    {
        for (int y = 0; y < size; y++)
        {
            table[x][y].cellType = CellType::Ocean;
        }
    }

    // Initiate a random index in the array as a fish.
    table[getrandom()][getrandom()].cellType = CellType::Fish;
    // Initiate a random index in the array as a shark.
    table[getrandom()][getrandom()].cellType = CellType::Shark;

    //// Print the initial state of the table
    std::cout << "Initial State:\n";
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            //std::cout << "[" << table[x][y].cellType << "]" <<"\t";
            if (table[x][y].cellType == 0)
            {
                std::cout << "[" << "Ocean" << "]" << "\t";
            }
            else if (table[x][y].cellType == 1)
            {
                std::cout << "[" << "Fish" << "]" << "\t";
            }
            else if (table[x][y].cellType == 2)
            {
                std::cout << "[" << "Shark" << "]" << "\t";
            }
        }
        std::cout << std::endl;
    }


    this_thread::sleep_for(chrono::milliseconds(5500)); //PAUSE
    // Simulate the movement of fish and sharks
    int i = 0;
    while (i == 0)
    {
        for (int x = 0; x < size; x++)
        {
            for (int y = 0; y < size; y++)
            {
                if (table[x][y].cellType = CellType::Fish) // Fishes
                {
                    if ((table[x][y].cellType == CellType::Fish) && (table[x][y].fishBirth < 2))// if the fish does not have enough points // might need to be changed!!!
                    {
                        if ((x > 0) && (table[x - 1][y].cellType = CellType::Ocean))
                        {
                            table[x - 1][y].cellType = CellType::Fish;
                            table[x - 1][y].fishBirth += 1;
                            table[x][y].cellType = CellType::Ocean;
                        }
                        else if ((x < size - 1) && (table[x + 1][y].cellType = CellType::Ocean))
                        {
                            table[x + 1][y].cellType = CellType::Fish;
                            table[x + 1][y].fishBirth += 1;
                            table[x][y].cellType = CellType::Ocean;
                        }
                        else if ((y < size - 1) && (table[x][y + 1].cellType = CellType::Ocean))
                        {
                            table[x][y + 1].cellType = CellType::Fish;
                            table[x][y + 1].fishBirth += 1;
                            table[x][y].cellType = CellType::Ocean;
                        }
                        else if ((y > 0) && (table[x][y - 1].cellType = CellType::Ocean))
                        {
                            table[x][y - 1].cellType = CellType::Fish;
                            table[x][y - 1].fishBirth += 1;
                            table[x][y].cellType = CellType::Ocean;
                        }
                    }
                    else if ((table[x][y].cellType == CellType::Fish) && (table[x][y].fishBirth = 2))//if the fish has enough points
                    {
                        if ((x > 0) && (table[x - 1][y].cellType = CellType::Ocean))
                        {
                            table[x - 1][y].cellType = CellType::Fish;
                            table[x][y].fishBirth = 0;
                        }
                        else if ((x < size - 1) && (table[x + 1][y].cellType = CellType::Ocean))
                        {
                            table[x + 1][y].cellType = CellType::Fish;
                            table[x][y].fishBirth = 0;
                        }
                        else if ((y < size - 1) && (table[x][y + 1].cellType = CellType::Ocean))
                        {
                            table[x][y + 1].cellType = CellType::Fish;
                            table[x][y].fishBirth = 0;
                        }
                        else if ((y > 0) && (table[x][y - 1].cellType = CellType::Ocean))
                        {
                            table[x][y - 1].cellType = CellType::Fish;
                            table[x][y].fishBirth = 0;
                        }
                    }
                }
                else if (table[x][y].cellType = CellType::Shark) //Sharkies
                {
                    if ((table[x][y].cellType == CellType::Shark) && (table[x][y].sharkEnergy < 3))//if shark sees a fish it goes hunting //might need to be changed !!!!
                    {
                        if ((x > 0) && (table[x - 1][y].cellType = CellType::Fish))//left
                        {
                            table[x - 1][y].cellType = CellType::Shark;
                            table[x][y].cellType = CellType::Ocean;
                        }
                        else if ((x < size - 1) && (table[x + 1][y].cellType = CellType::Fish))//right
                        {
                            table[x + 1][y].cellType = CellType::Shark;
                            table[x][y].cellType = CellType::Ocean;
                        }
                        else if ((y < size - 1) && (table[x][y + 1].cellType = CellType::Fish))//below
                        {
                            table[x][y + 1].cellType = CellType::Shark;
                            table[x][y].cellType = CellType::Ocean;
                        }
                        else if ((y > 0) && (table[x][y - 1].cellType = CellType::Fish))//above
                        {
                            table[x][y - 1].cellType = CellType::Shark;
                            table[x][y].sharkEnergy += 1;
                            table[x][y].cellType = CellType::Ocean;
                        }
                    }
                    else if ((table[x][y].cellType == CellType::Shark) && (table[x][y].sharkEnergy == 3))//if shark has enough energy makes a kid
                    {
                        if ((x > 0) && (table[x - 1][y].cellType = CellType::Ocean))
                        {
                            table[x - 1][y].cellType = CellType::Shark;
                        }
                        else if ((x < size - 1) && (table[x + 1][y].cellType = CellType::Ocean))
                        {
                            table[x + 1][y].cellType = CellType::Shark;
                        }
                        else if ((y < size - 1) && (table[x][y + 1].cellType = CellType::Ocean))
                        {
                            table[x][y + 1].cellType = CellType::Shark;
                        }
                        else if ((y > 0) && (table[x][y - 1].cellType = CellType::Ocean))
                        {
                            table[x][y - 1].cellType = CellType::Shark;
                        }
                    }
                }
            }
        }

    Print the final state of the table
    std::cout << "\nFinal State:\n";
    for (int x = 0; x < size; x++)
    {
       for (int y = 0; y < size; y++)
       {
           //std::cout << "[" << table[x][y].cellType << "]" <<"\t";
           if (table[x][y].cellType == 0)
           {
               std::cout << "[" << "Ocean" << "]" << "\t";
           }
           else if (table[x][y].cellType == 1)
           {
               std::cout << "[" << "Fish" << "]" << "\t";
           }
           else if (table[x][y].cellType == 2)
           {
               std::cout << "[" << "Shark" << "]" << "\t";
           }
       }
       std::cout << std::endl;
    }
    this_thread::sleep_for(chrono::milliseconds(10000));
    system("CLS");
    }
    return 0;
}
