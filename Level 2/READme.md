# 🟢 Grid Algorithms: Visual Guide

### 📊 Side-by-Side Visualization

| **Original Map**|**Largest Isld(FF)**| **DP(BSQ)**|**Game of Life**|
| :----------- | :-------------- | :-------------- | :-------------- |
|             | * = visited     |                 | 0 = Dead; 1 = Alive |
|  Input map   |largest connected| largest square | change by neighbour following a specific rule|
| . X . . .    | . * . . .       | 1 1 1 1 1       | 0 1 0 0 0      |
| X X X . .    | * * * . .       | 1 2 2 2 2       | 1 1 1 0 0      |
| . X . X .    | . * . X .       | 1 2 3 3 3       | 1 1 1 1 1      |
| . . . X X    | . . . X X       | 1 2 3 4 4       | 0 1 1 1 1      |
| X . . X .    | X . . X .       | 1 2 3 4 5       | 0 1 0 1 0      |

---

### ⚙️ Core Logic & Formulas

**Flood Fill (Connectivity)[Largest Island]**  
- **Goal:** find largest connected area
- **Mechanism:** Spread outward from a seed point  
- **Memory Tip:** Use a visited indicator 

**Dynamic Programming (Optimization)[BSQ]**  
- **Goal:** Find the largest square of `1`s  
- **Formula:**  
dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])

**Simulation (State Change)[Game of Life]**
- **Goal:** Update the grid based on the previous state.
- **Formula:**  Every cell checks its 8 neighbors.
//Alive cell with <2 or >3 alive neighbors → dies
//Alive cell with 2 or 3 alive neighbors → lives
//Dead cell with exactly 3 alive neighbors → becomes alive 
- **Tip:**Never update in-place. Use a temporary grid to store new values, then swap
