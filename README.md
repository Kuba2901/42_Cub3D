# Cub3D

A **ray-casting 3D engine** inspired by early FPS games like *Wolfenstein 3D*.
This project is part of **42’s curriculum** and follows the concepts from **Lode’s Computer Graphics Tutorial**, rebuilt in C using the **MiniLibX** graphics library.

---

## Overview

Cub3D renders a pseudo-3D environment from a 2D map using **DDA (Digital Differential Analyzer)** ray-casting.
The program displays walls, textures, sprite effects (optional), and allows first-person movement through a maze-like world.

The goal of the project is to implement the core principles of early game graphics:

* Ray casting
* Wall projection
* Texture mapping
* Player movement and rotation
* Handling key events and window rendering
* Efficient pixel-buffer manipulation
* Proper parsing and error handling

---

## Features

* **Raycasting engine** based on DDA
* **Texture mapping** for walls (NO/SO/EA/WE)
* **Floor & ceiling colors**
* **Movement system**

  * Forward/backward movement
  * Strafing
  * Smooth rotation
* **Collision detection**
* **Config file parsing** (`.cub`)
* **Image buffer rendering** using MiniLibX
* **Simple game loop** with controlled frame updates
* **Crosshair & minimal HUD (optional depending on implementation)**

## The `.cub` File Format

A valid `.cub` configuration contains:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
1000N1
111111
```

**Allowed identifiers:**

* `NO SO WE EA` → wall textures
* `F` / `C` → RGB floor / ceiling colors
* Map must be closed by walls and contain one player start position (`N`, `S`, `E`, `W`)

---

## Raycasting (DDA) Summary

Cub3D uses the algorithm described by Lode:

1. Cast one ray per vertical screen stripe
2. Determine the ray direction from camera plane + player direction
3. Perform DDA:
   * Step through the grid square by square
   * Find the first wall intersection
4. Compute perpendicular wall distance
5. Project a vertical wall slice onto the screen
6. Apply texture mapping
7. Repeat for all screen columns

This produces a fast, deterministic pseudo-3D environment.

---

## Controls

| Key   | Action                |
| ----- | --------------------- |
| W / S | Move forward/backward |
| A / D | Strafe left/right     |
| ← / → | Rotate camera         |
| ESC   | Quit                  |

---

## Compilation

```
make bonus      # build cub3d with bonus settings
make clean      # object files
make fclean     # full cleanup
```

Run with:

```
./cub3d assets/maps/bonus.cub
```

---

## Requirements

* **C compiler (clang or gcc)**
* **MiniLibX** (provided by 42)
* Works on **Linux** and **macOS** (subject to MLX version)

---

## Key Concepts Implemented

* DDA ray-grid intersection
* Vector math (dir, plane, rayDir, deltaDist, sideDist)
* Wall distance correction (fish-eye prevention)
* Scaled texture sampling
* Double-buffered rendering
* Parsing and validation of custom file format
* Pixel-based rendering via MiniLibX

---

## Notes

This project is based heavily on the ideas presented in **Lode Vandevenne’s Raycasting Tutorial**, adapted and extended to meet the constraints of the **42 Cub3D** project.
