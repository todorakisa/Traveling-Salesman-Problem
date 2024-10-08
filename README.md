# TSP Solver Project Documentation

**Author**: Todor Tonev Dimitrov

## Project Structure
The project documentation is divided into five main sections:
1. **Introduction**
2. **Key Definitions, Concepts, and Algorithms**
3. **Results and Testing**
4. **Conclusion**
5. **References**

## Introduction
This repository contains a project aimed at solving the Traveling Salesman Problem (TSP). The Traveling Salesman Problem is one of the most well-known and studied algorithms in combinatorial optimization. It is easy to define but difficult to solve. A salesman must visit a list of cities, and given the distances between each pair of cities, the objective is to find the shortest path that visits every city. Due to the problem's nature, it cannot be solved in a reasonable time frame and is classified as NP-hard. Although no linear-time algorithm has been devised, several heuristic algorithms provide near-optimal solutions.

**GitHub Repository**: [TSP Solver Project](https://github.com/todorakisa/TSP-Project-SDP)

### Purpose and Objectives
The goal of this project is to implement several algorithms to solve the TSP and compare their performance across problems of various sizes. The results will evaluate the efficiency of each algorithm.

## Key Definitions, Concepts, and Algorithms

The algorithms chosen for testing are:

### 1. Brute Force
This is one of the first algorithms that comes to mind when solving the TSP. It is simple but extremely slow. It evaluates all possible solutions to the problem and selects the shortest path. However, for graphs with more than 10 cities, the time required to solve the problem grows exponentially.

**Pseudocode:**
```
get an initial tour; call it T
best_tour ⇦ T
best_score ⇦ score(T)
while there are more permutations of T do the following:
    generate a new permutation of T
    if score(T) < best_score then
        best_tour ⇦ T
        best_score ⇦ score(T)
print best_tour and best_score
```

### 2. Nearest Neighbor
This algorithm has a greedy nature. It starts from an initial point and iteratively selects the nearest city, adding it to the solution. While this method results in a path about 20% longer than the optimal one, it is much faster than Brute Force.

### 3. Improved Nearest Neighbor
This algorithm is similar to Nearest Neighbor but starts from the city that is closest to all others. While the speed is comparable to Nearest Neighbor, it sometimes provides better results.

### 4. ACS (Ant Colony System)
This algorithm is more complex and falls under the category of genetic algorithms or reinforcement learning. It mimics the behavior of ants finding the shortest path to their nest using pheromones. The algorithm generates an adjacency matrix for the graph, containing all edges, their pheromones, and their lengths. The number of generations and ants per generation is determined, and each ant explores the graph starting from a random point.

The algorithm requires both global and local rules for updating pheromones. After each generation, the best ant (the one with the shortest path) reinforces the pheromones along its path. To avoid all ants selecting the same path, the local rule reduces pheromones when an ant passes through an edge.

## Results and Testing
Several key observations can be made from the results:
- The Brute Force algorithm is impractical for graphs with more than 10 vertices.
- The ACS algorithm finds good paths but is much slower compared to Nearest Neighbor and Improved Nearest Neighbor due to its complexity.
- While Nearest Neighbor and Improved Nearest Neighbor do not always find the shortest paths, they are relatively fast for large problems.

For testing, the resources from section 3 of "References" were used.

## Conclusion

### Summary of Achievements
Four algorithms were implemented to solve the TSP, and they were tested on problems of varying sizes. A small user interface was also developed.

### Future Improvements
Implement more Algorithms.
Optimizing the ACS algorithm for solving the TSP is a potential future development. Parallelization and multi-threading could significantly improve the algorithm's performance on larger problems. Additionally, the initial number of ants in the ACS algorithm could be optimized based on problem size. Too few ants may not find a short path, while too many result in unnecessary computations.

## References
- [Swarm Intelligence in Ant Colonies](http://staff.washington.edu/paymana/swarm/dorigo97-itec.pdf)
- [Ant Colony Optimization: A Review](http://people.idsia.ch/~luca/acs-bio97.pdf)
- [World TSP Challenge](http://www.math.uwaterloo.ca/tsp/world/countries.html)
