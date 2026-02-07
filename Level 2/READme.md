# 🟢 Grid Algorithms: Visual Guide

A quick-reference guide for common grid-based problems. Use this to distinguish between connectivity, optimization, and simulation logic.

---

### 🗺️ Legend
| Symbol | Meaning | Context |
| :--- | :--- | :--- |
| `X` / `.` | Land / Water | Original Map |
| `*` | Visited / Counted | **Flood Fill** (Connectivity) |
| `n` | Max Square Size | **DP / BSQ** (Optimization) |
| `1` / `0` | Alive / Dead | **Game of Life** (Simulation) |

---

### 📊 Side-by-Side Visualization

#### 1. Flood Fill (DFS/BFS)
*Identifies connected components. Once an `X` is found, "bleed" into neighbors.*
```text
  0 1 2 3 4
0 . * . . .
1 * * * . .
2 . * . X .

2. DP: Biggest Square (BSQ)Calculates the side length of the largest square ending at (i, j).Plaintext  0 1 2 3 4
```text
0 1 1 1 1 1
1 1 2 2 2 2
2 1 2 3 3 3

3. Simulation (Game of Life)State changes based on neighbor counts. Requires a buffer (don't update in-place).Plaintext  0 1 2 3 4
```text
0 0 1 0 0 0
1 1 1 1 0 0
2 0 1 0 1 0

#### Core Logic & Formulas:
Flood Fill (Connectivity)Goal: Count islands or fill areas.
Mechanism: Spread outward from a seed point.
Memory Tip: Uses a visited set or modifies the grid in-place to avoid infinite loops.

Dynamic Programming (Optimization)Goal: Find the Largest Square of 1s.
Formula: $$dp[i][j] = 1 + \min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
$$Memory Tip: You only need the current and previous row to optimize space.

Simulation (State Change)Goal: Predict the next generation.
Mechanism: Every cell checks its 8 neighbors simultaneously.
Memory Tip: Always use a copy of the grid; updating a cell immediately will "pollute" the calculation for its neighbors.


🎓 Exam Cheat SheetSpread Outward? 
→ Flood Fill / BFS.Build on Neighbors? 
→ DP (BSQ / Pathfinding).Tick-based Evolution? 
→ Simulation (Game of Life).

