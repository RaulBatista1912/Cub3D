## 🧑‍💻 Author

**Isaiah** — [42 Lausanne Student] : https://github.com/isaiahrbs

**Raul** — [42 Lausanne Student] : https://github.com/RaulBatista1912

---

```markdown
# 🧱 cub3D

`cub3D` is a 3D graphical project developed at 42 School, inspired by early FPS games like *Wolfenstein 3D*. It renders a 3D view from a 2D map using **raycasting**, implemented entirely in C using the **MiniLibX** graphical library.

This project is part of the 42 cursus and was designed to help students understand basic graphical rendering, memory management, and mathematical concepts behind 3D engines.

---

## 🕹 Features

- 3D rendering from a 2D map
- Player movement (WASD)
- Rotation (left/right arrows)
- Wall textures
- Basic minimap (optional)
- Sprite rendering (bonus)

---

## 🔧 Installation & Usage

### Requirements
- Linux (tested on Linux Mint)
- gcc compiler
- `make`
- MiniLibX (included)

### Install MiniLibX (if not using the 42 intranet version)
```bash
git clone https://github.com/42Paris/minilibx-linux.git
cd minilibx-linux
make
```

### Run the Program
```bash
./Cub3D maps/fish.cub
```

---

## 🗺 Map Format (`.cub`)

A `.cub` file is a plain-text file that defines:
- Resolution (optional on Linux)
- Texture paths (N, S, E, W walls)
- Floor and ceiling colors (RGB)
- 2D Map layout using:
  - `1`: wall
  - `0`: empty space
  - `N`, `S`, `E`, `W`: player start direction

Example:
```
NO ./textures/wall_n.xpm
SO ./textures/wall_s.xpm
WE ./textures/wall_w.xpm
EA ./textures/wall_e.xpm
F 220,100,0
C 225,30,0

1111111111
1000000001
1000010001
1000N00001
1111111111
```

---

## 🧠 Raycasting Explained

Raycasting is a technique that simulates a 3D perspective using a 2D map. It’s not real 3D — rather, it’s an illusion that casts rays from the player’s position and finds where those rays hit walls.

### Step-by-Step Overview:

1. **Player View**: The player stands in a 2D map and can rotate. Their view is a field of rays — one per vertical column of the screen.

2. **Casting Rays**: For every column of pixels:
   - A ray is cast at a specific angle.
   - The ray moves step by step through the map grid (using DDA: Digital Differential Analyzer).
   - It stops when it hits a wall (`'1'`).

3. **Distance Calculation**:
   - The distance to the wall is calculated (corrected for the fish-eye effect).
   - The closer the wall, the taller the column on screen.

4. **Drawing Walls**:
   - Based on the distance, a vertical slice of the wall is drawn with the correct texture.
   - The wall height is scaled based on how far it is.

5. **Repeat** for all columns across the screen → gives a pseudo-3D effect!

---

## 🎯 Goals of the Project

- Learn basic **graphics programming** with MiniLibX
- Understand **raycasting mathematics** and geometry
- Work with **textures**, **map parsing**, and **game loop**
- Improve **C programming** and **memory management**

---

## 📸 Screenshots

![image](https://github.com/user-attachments/assets/0dbe0772-4372-46f1-9917-175de302c9d3)

---

## 🏆 Bonus Ideas

- 🧠 Minimap
- 👾 FPS Counter

---



---
```
