
#include <SFML/Graphics.hpp>
#include <omp.h>
#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <cstdlib>  // For std::rand
#include <ctime>    // For std::time
#include <chrono>   // to measure time

#define stringify( name ) #name
using namespace std;

//Creator : Marcel Zama C00260146
//Date : 27/11/2023
//Title : Wa-Tor simulation working Parallel
//GitHub repository: https://github.com/MarcelZama/Wa-Tor-Problem/tree/main

// Define constants
const int NumShark = 10000;    // Initial number of sharks
const int NumFish = 15000;     // Initial number of fishes

const int FishBreed = 2;    // Fish breeding age
const int FishEnergyValue = 2; // Amount of energy fish gives to a shark when eaten

const int SharkBreed = 8;   // Shark breeding age // number of cells shark needs to move before it multiplies.
const int Starve = 6;       // Shark starvation time // number of times the shark is accesed before it dies // initiated to 6

const int GridSize = 1000;    // Size of the grid (GridSize x GridSize)
const int Threads =1;      // Number of OpenMP threads

// Define cell types
enum class CellType
{
    Ocean,
    Fish,
    Shark
};

// Define cell structure
struct Cell
{
    CellType type;
    int breedCounter;
    int starveCounter;
};

// Create a 2D grid
std::vector<std::vector<Cell>> grid(GridSize, std::vector<Cell>(GridSize, { CellType::Ocean, 0, 0 }));

// Function to initialize the grid with fish and sharks
void initializeGrid(std::vector<std::vector<Cell>>& grid)
{
    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    ///////Fishes

    // Place fish on the grid
    for (int i = 0; i < NumFish; ++i)
    {
        int x = std::rand() % GridSize;
        int y = std::rand() % GridSize;

        // Find an empty cell "Ocean" to place a fish
        while (grid[x][y].type != CellType::Ocean)
        {
            x = std::rand() % GridSize;
            y = std::rand() % GridSize;
        }

        // Place a fish in the empty cell with breed and starve counters initialized to 0
        grid[x][y] = { CellType::Fish, FishBreed,  Starve };
    }

    ///////Sharks

    // Place sharks on the grid
    for (int i = 0; i < NumShark; ++i)
    {
        int x = std::rand() % GridSize;
        int y = std::rand() % GridSize;

        // Find an empty cell "Ocean" to place a shark
        while (grid[x][y].type != CellType::Ocean)
        {
            x = std::rand() % GridSize;
            y = std::rand() % GridSize;
        }

        // Place a shark in the empty cell with breed and starve counters initialized to 0
        grid[x][y] = { CellType::Shark, SharkBreed, Starve };
    }
}

// Function to swap two cells in the grid
void swap(Cell& cell1, Cell& cell2)
{
    std::swap(cell1.type, cell2.type);
    std::swap(cell1.breedCounter, cell2.breedCounter);
    std::swap(cell1.starveCounter, cell2.starveCounter);
}

//FISH
// At each chronon, a fish moves randomly to one of the adjacent unoccupied squares.If there are no free squares, no movement takes place.
// 
//Once a fish has survived a certain number of chronons it may reproduce.
//This is done as it moves to a neighbouring square, leaving behind a new
//fish in its old position.Its reproduction time is also reset to zero.



// Function to update the fish population in the grid
void updateFish(std::vector<std::vector<Cell>>& grid)
{
    // Parallelize the loop using OpenMP
    #pragma omp parallel for
    // Iterate through each cell in the grid
    for (int x = 0; x < GridSize; ++x)
    {
        for (int y = 0; y < GridSize; ++y)
        {
            // Check if the cell contains a fish
            if (grid[x][y].type == CellType::Fish)
            {
                // If the breed timer reaches zero, spawn a new fish in a neighboring empty cell
                if (grid[x][y].breedCounter == 0)
                {
                    for (int attempt = 0; attempt < 5; ++attempt) // try 5 times to find an empty cell
                    {
                        int x2 = x + std::rand() % 3 - 1; // Random movement in x direction
                        int y2 = y + std::rand() % 3 - 1; // Random movement in y direction

                        if (x2 == -1)
                        {
                            x2 = GridSize - 1;
                        }
                        else if (x2 == GridSize)
                        {
                            x2 = 0;
                        }

                        if (y2 == -1)
                        {
                            y2 = GridSize - 1;
                        }
                        else if (y2 == GridSize)
                        {
                            y2 = 0;
                        }

                        // Check if the neighboring cell is within bounds and empty
                        if (x2 >= 0 && x2 < GridSize && y2 >= 0 && y2 < GridSize && grid[x2][y2].type == CellType::Ocean)
                        {
                            // Spawn a new fish
                            grid[x2][y2].type = CellType::Fish;
                            grid[x2][y2].breedCounter = FishBreed;
                            grid[x][y].breedCounter = FishBreed;
                            break;
                        }
                    }
                }

                // Move the fish to a neighboring empty cell
                for (int attempt = 0; attempt < 5; ++attempt) // try 5 times to find an empty cell
                {
                    int x2 = x + std::rand() % 3 - 1; // Random movement in x direction
                    int y2 = y + std::rand() % 3 - 1; // Random movement in y direction

                    if (x2 == -1)
                    {
                        x2 = GridSize - 1;
                    }
                    else if (x2 == GridSize)
                    {
                        x2 = 0;
                    }

                    if (y2 == -1)
                    {
                        y2 = GridSize - 1;
                    }
                    else if (y2 == GridSize)
                    {
                        y2 = 0;
                    }

                    // Check if the neighboring cell is within bounds and empty
                    if (x2 >= 0 && x2 < GridSize && y2 >= 0 && y2 < GridSize && grid[x2][y2].type == CellType::Ocean)
                    {
                        --grid[x][y].breedCounter;
                        // Move the fish
                        std::swap(grid[x][y], grid[x2][y2]);
                        grid[x2][y2].breedCounter = grid[x][y].breedCounter;  // Inherit breed timer
                        grid[x][y].type = CellType::Ocean;  // Set the original cell to empty
                        grid[x][y].breedCounter = 0;  // Reset the original breed timer
                        //grid[x2][y2].starveCounter = FishBreed;  // Reset move timer for the moved fish
                        break;
                    }
                }
            }
        }
    }
}

//SHARKS
//  At each chronon, a shark moves randomly to an adjacent square occupied by a fish. If there is none, the shark moves to a random adjacent
//unoccupied square.If there are no free squares, no movement takes place.
// 
//At each chronon, each shark is deprived of a unit of energy.
// 
//Upon reaching zero energy, a shark dies.
// 
//If a shark moves to a square occupied by a fish, it eats the fish and earns
//a certain amount of energy
// 
//Once a shark has survived a certain number of chronons it may reproduce
//in exactly the same way as the fish.

// Function to update the shark population in the grid
void updateShark(std::vector<std::vector<Cell>>& grid)
{
    // Parallelize the loop using OpenMP
    #pragma omp parallel for

    // Iterate through each cell in the grid
    for (int x = 0; x < GridSize; ++x)
    {
        for (int y = 0; y < GridSize; ++y)
        {
            // Check if the cell contains a shark
            if (grid[x][y].type == CellType::Shark)
            {
                int somethingdone = 0;
                //#########################################################
                //# Die 
                //#########################################################
                // If the move timer reaches zero, the shark dies
                if (grid[x][y].starveCounter == 0)
                {
                    grid[x][y].type = CellType::Ocean;
                    somethingdone = 1;
                }

                //#########################################################
                //# Shark Eats Fish 
                //#########################################################
                // Move the shark to a neighboring fish cell and reset the move timer
                for (int attempt = 0; attempt < 5; ++attempt) // try 5 times to find a fish cell
                {
                    int x2 = x + std::rand() % 3 - 1; // Random movement in x direction
                    int y2 = y + std::rand() % 3 - 1; // Random movement in y direction

                    if (x2 == -1)
                    {
                        x2 = GridSize - 1;
                    }
                    else if (x2 == GridSize)
                    {
                        x2 = 0;
                    }

                    if (y2 == -1)
                    {
                        y2 = GridSize - 1;
                    }
                    else if (y2 == GridSize)
                    {
                        y2 = 0;
                    }

                    // Check if the neighboring cell is within bounds and contains a fish
                    if (x2 >= 0 && x2 < GridSize && y2 >= 0 && y2 < GridSize && grid[x2][y2].type == CellType::Fish)
                    {
                        //std::cout << "I execute 7777777777777777777" << std::endl;
                        // Move the shark and reset the move timer
                        --grid[x][y].breedCounter;
                        --grid[x][y].starveCounter;
                        std::swap(grid[x][y], grid[x2][y2]);
                        //grid[x2][y2].starveCounter = Starve;

                        grid[x2][y2].starveCounter += FishEnergyValue;
                        grid[x][y].type = CellType::Ocean;

                        somethingdone = 1;

                        break;
                    }
                }

                //#########################################################
                //# Move 
                //#########################################################
                // Move the shark to a neighboring cell
                for (int attempt = 0; attempt < 5; ++attempt) // try 5 times to find an empty cell
                {
                    int x2 = x + std::rand() % 3 - 1; // Random movement in x direction
                    int y2 = y + std::rand() % 3 - 1; // Random movement in y direction

                    if (x2 == -1)
                    {
                        x2 = GridSize - 1;
                    }
                    else if (x2 == GridSize)
                    {
                        x2 = 0;
                    }

                    if (y2 == -1)
                    {
                        y2 = GridSize - 1;
                    }
                    else if (y2 == GridSize)
                    {
                        y2 = 0;
                    }

                    // Check if the neighboring cell is within bounds and empty
                    if (x2 >= 0 && x2 < GridSize && y2 >= 0 && y2 < GridSize && grid[x2][y2].type == CellType::Ocean)
                    {
                        --grid[x][y].breedCounter;
                        --grid[x][y].starveCounter;
                        // Move the shark and reset the move timer
                        std::swap(grid[x][y], grid[x2][y2]);

                        somethingdone = 1;

                        break;
                    }
                }

                //#########################################################
                //# Multiply 
                //#########################################################
                // If the breed timer reaches zero, spawn a new shark in a neighboring empty cell
                if (grid[x][y].breedCounter == 0)
                {
                    for (int attempt = 0; attempt < 5; ++attempt) // try 5 times to find an empty cell
                    {
                        int x2 = x + std::rand() % 3 - 1; // Random movement in x direction
                        int y2 = y + std::rand() % 3 - 1; // Random movement in y direction

                        if (x2 == -1)
                        {
                            x2 = GridSize - 1;
                        }
                        else if (x2 == GridSize)
                        {
                            x2 = 0;
                        }

                        if (y2 == -1)
                        {
                            y2 = GridSize - 1;
                        }
                        else if (y2 == GridSize)
                        {
                            y2 = 0;
                        }

                        // Check if the neighboring cell is within bounds and empty
                        if (x2 >= 0 && x2 < GridSize && y2 >= 0 && y2 < GridSize && grid[x2][y2].type == CellType::Ocean)
                        {
                            //// Spawn a new shark
                            //grid[x2][y2].type = CellType::Shark;
                            //grid[x2][y2].breedCounter = SharkBreed;
                            //grid[x2][y2].starveCounter = Starve;

                            std::swap(grid[x][y], grid[x2][y2]);
                            grid[x][y].type = CellType::Shark;
                            grid[x][y].breedCounter = SharkBreed;
                            //grid[x][y].starveCounter = Starve;
                            grid[x][y].starveCounter += FishEnergyValue;

                            break;
                        }
                    }
                }

                // If the move timer reaches zero, the shark dies
                if (grid[x][y].starveCounter <= 0)
                {
                    grid[x][y].type = CellType::Ocean;
                }
                // Decrease the breed timer and move timer
            }
        }
    }
}

//Count number of Sharks
int sharkCount(std::vector<std::vector<Cell>>& grid)
{
    int sharkies = 0;
    // Iterate through each cell in the grid
    for (int x = 0; x < GridSize; ++x)
    {
        for (int y = 0; y < GridSize; ++y)
        {
            // Check if the cell contains a shark
            if (grid[x][y].type == CellType::Shark)
            {
                sharkies++;
            }
        }
    }
    return sharkies;
}

//Count number of Fishes
int fishCount(std::vector<std::vector<Cell>>& grid)
{
    int fishes = 0;
    // Iterate through each cell in the grid
    for (int x = 0; x < GridSize; ++x)
    {
        for (int y = 0; y < GridSize; ++y)
        {
            // Check if the cell contains a fish
            if (grid[x][y].type == CellType::Fish)
            {
                fishes++;
            }
        }
    }
    return fishes;
}


// Function to update the entire grid based on Wa-Tor simulation rules
//double updateGrid(std::vector<std::vector<Cell>>& grid)
//{
//    // Start the clock
//    auto start = std::chrono::high_resolution_clock::now();
//
//    updateFish(grid);
//
//    updateShark(grid);
//
//
//    // Stop the clock
//    auto stop = std::chrono::high_resolution_clock::now();
//
//    // Calculate the duration
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//    auto duration2 = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
//
//    // Print the running time in microseconds
//    std::cout << "Running time: " << duration.count() << " microseconds" << " or " << duration2.count() << " seconds." << std::endl;
//    return duration.count();
//
//}

// Function to draw the grid using SFML
void drawGrid(sf::RenderWindow& window,int iterationin, int fishCount, int sharkCount, int durationin,int averagedurationin, std::vector<std::vector<Cell>>& grid)
{
    // Define cell size based on window dimensions and grid size
    float cellSize = static_cast<float>(window.getSize().x) / GridSize;

    // Iterate through each cell in the grid
    for (int i = 0; i < GridSize; ++i)
    {
        for (int j = 0; j < GridSize; ++j)
        {
            // Calculate the position and size of the cell
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(static_cast<float>(j) * cellSize, static_cast<float>(i) * cellSize);

            // Set cell color based on cell type
            switch (grid[i][j].type)
            {
            case CellType::Ocean:
                cell.setFillColor(sf::Color(80, 180, 233));//(sf::Color(212, 241, 249)); //water
                break;
            case CellType::Fish:
                cell.setFillColor(sf::Color(51, 136, 0)); //Slimy green
                break;
            case CellType::Shark:
                cell.setFillColor(sf::Color(1, 11, 19)); //Rich black
                break;
            }

            // Draw the cell
            window.draw(cell);
        }
    }

    int totalcellsin = fishCount + sharkCount;
    int gridsize = grid.size() * grid.size();

    // Display fish and shark counts
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return;
    }

    sf::Text iteration, fishText, sharkText, totalcells, duration, averageduration, threadss;
    iteration.setFont(font);
    fishText.setFont(font);
    sharkText.setFont(font);
    totalcells.setFont(font);
    threadss.setFont(font);

    duration.setFont(font);
    averageduration.setFont(font);

    iteration.setString("Iteration: " + std::to_string(iterationin));
    fishText.setString("Fish: " + std::to_string(fishCount));
    sharkText.setString("Sharks: " + std::to_string(sharkCount));
    totalcells.setString("Total Cells Ocuppied: " + std::to_string(totalcellsin) + " / " + std::to_string(gridsize));
    threadss.setString("Threads: " + std::to_string(Threads));

    duration.setString("Time: " + std::to_string(durationin) + " microseconds");
    averageduration.setString("Average Time: " + std::to_string(averagedurationin) + " microseconds");

    
    iteration.setFillColor(sf::Color(255, 0, 0));
    fishText.setFillColor(sf::Color(255, 0, 0));
    sharkText.setFillColor(sf::Color(255, 0, 0));
    totalcells.setFillColor(sf::Color(255, 0, 0));
    threadss.setFillColor(sf::Color(255, 0, 0));

    duration.setFillColor(sf::Color(255, 0, 0));
    averageduration.setFillColor(sf::Color(255, 0, 0));

    iteration.setCharacterSize(20);
    fishText.setCharacterSize(20);
    sharkText.setCharacterSize(20);
    totalcells.setCharacterSize(20);
    duration.setCharacterSize(20);
    averageduration.setCharacterSize(20);
    threadss.setCharacterSize(20);

    iteration.setPosition(10, 10);
    fishText.setPosition(10, 40);
    sharkText.setPosition(10, 70);
    totalcells.setPosition(10, 100);
    duration.setPosition(10, 130);
    averageduration.setPosition(10, 160);
    threadss.setPosition(700, 10);

    window.draw(iteration);
    window.draw(fishText);
    window.draw(sharkText);
    window.draw(totalcells);
    window.draw(duration);
    window.draw(averageduration);
    window.draw(threadss);
}

int main()
{
    // Initialize the grid
    initializeGrid(grid);

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Wa-Tor Simulation                                                                                        Made By : Marcel Zama C00260146");

    // Set the number of OpenMP threads
    omp_set_num_threads(Threads);

    int iteration = 0;
    int averagetime = 0;
    int currenttime = 0;
    int totalaverage = 0;
    int gate = 0;

    // Main loop
    while (window.isOpen())
    {
        iteration++;
       
        // Handle SFML events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update the grid
        auto start = std::chrono::high_resolution_clock::now();

        // Parallelize the fish and shark updates using OpenMP tasks
        #pragma omp parallel
        {
            #pragma omp single
            {
            #pragma omp task
                updateFish(grid);

            #pragma omp task
                updateShark(grid);
            }
        }

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        //cout << "Average time before : " << averagetime << " , current time: " << duration.count() << endl; // test that average time works
        
        // Calculate the average iteration time
        if (gate == 1)
        {
            averagetime = (averagetime + duration.count()) / 2;
            totalaverage += averagetime;
        }
        else
        {
            averagetime = duration.count();
            totalaverage += averagetime;
        }

        //cout << "Average time after : " << averagetime << " , current time: " << duration.count() << endl; // test that average time works

        gate = 1;
        // Draw the grid
        window.clear();
        drawGrid(window, iteration, fishCount(grid), sharkCount(grid), duration.count(), averagetime, grid);
        window.display();
        if ((iteration % 10) == 0) // to automatically stop after 10 iterations
        {
            totalaverage = totalaverage / (iteration + 1);
            cout << "TOTAL AVERAGE FROM 10 ITERATIONS !!! ---> " << totalaverage << endl;
            cout << "Press Enter to Continue" << endl;
            cin.ignore();
        }
    }

    return 0;
}