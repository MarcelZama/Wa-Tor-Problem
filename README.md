# Wator: A Simulation of Predator-Prey Dynamics

Wator is a well-known ecological simulation model that depicts the interactions between two species: predators (sharks) and prey (fish). It is a cellular automaton devised by A.K. Dewdney, originally featured in his "Computer Recreations" column in *Scientific American*. The name "Wator" is a play on words, combining "water" with "toroid," indicating the toroidal (wrap-around) structure of the simulation grid.

## Key Components and Rules

### Grid and Environment
- **Grid**: The simulation takes place on a two-dimensional grid, where each cell can either be empty, contain a fish, or contain a shark.
- **Toroidal Structure**: The grid edges are connected, meaning that moving off one edge brings an entity to the opposite edge, creating a continuous loop.

### Entities

#### Fish
- **Movement**: Fish move to an adjacent empty cell.
- **Reproduction**: After a certain number of time steps (breeding age), a fish can reproduce, creating a new fish in an adjacent empty cell.
- **Lifespan**: Fish have an indefinite lifespan, but they are vulnerable to sharks.

#### Sharks
- **Movement**: Sharks move to an adjacent cell, preferring those containing fish (to eat). If no fish are nearby, they move to an empty cell.
- **Feeding**: Sharks must eat fish to survive. If a shark does not eat within a certain number of time steps, it dies.
- **Reproduction**: After a certain number of time steps (breeding age), a shark can reproduce, creating a new shark in an adjacent empty cell.
- **Lifespan**: Sharks have a lifespan determined by their ability to find and consume fish.

## Simulation Steps

1. **Initialization**: The grid is initialized with a random distribution of sharks, fish, and empty cells.
2. **Time Step**: Each time step, the simulation updates:
   - **Fish Movement and Reproduction**: Each fish moves and potentially reproduces.
   - **Shark Movement, Feeding, and Reproduction**: Each shark moves, attempts to eat fish, and potentially reproduces.
3. **Check Conditions**: Sharks that have not eaten within the required time steps die. Fish and sharks that reproduce generate offspring in adjacent cells.
4. **Repeat**: The simulation repeats these steps for a predefined number of iterations or until a steady state is reached.

## Getting Started

### Prerequisites
- Install SFML for graphics rendering.

### Installing
1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/wator-simulation.git
2. Navigate to the project directory:
   cd wator-simulation
3. Build the project:
   make
4.Running the Simulation
   ./Parallel

![image](https://github.com/MarcelZama/Wa-Tor-Problem/assets/92083030/d6af9815-3457-4ca7-b728-51a73fd69806)
![image](https://github.com/MarcelZama/Wa-Tor-Problem/assets/92083030/19b376a5-3353-453f-a978-0bbddaf7cd3d)

Authors
Marcel Zama

License
This project is licensed under the MIT License - see the LICENSE.md file for details.
