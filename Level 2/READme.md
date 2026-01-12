# 🟢 Grid Algorithm

Legend:
- `X` = land / alive / usable
- `.` = water / dead / blocked
- `*` = visited / counted (Flood Fill)
- Numbers = DP values (BSQ)
- `1` / `0` = alive / dead (Game of Life)

Original Map:

. X . . .
X X X . .
. X . X .
. . . X X
X . . X .

---

# Side-by-side visualization

Position →  0     1     2     3     4

Flood Fill      DP (BSQ)       Simulation (Game of Life)
------------   ----------      ------------------------
. * . . .      1  1  1  1  1      0  1  0  0  0
* * * . .      1  2  2  2  2      1  1  1  0  0
. * . X .      1  2  3  3  3      1  1  1  1  1
. . . X X      1  2  3  4  4      0  1  1  1  1
X . . X .      1  2  3  4  5      0  1  0  1  0

---

# Quick Notes

- **Flood Fill:** paint bucket → start at one X → mark all connected → count size  
- **DP (BSQ):** stacking blocks → each cell = 1 + min(top, left, top-left) → largest square size  
- **Simulation (Game of Life):** everyone acts at once → check neighbors → update new grid simultaneously  

Memory Tips for Exams:
- Flood fill → *spread outward from start*  
- DP → *build on previous results*  
- Simulation → *apply rules to every cell at once*


