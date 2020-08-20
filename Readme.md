# Trees Libraries
## Several tress made in C++ for the data structures course
Uses templates for the node information.

Print mode using dot descriptive language (only runs in Linux with graphviz installed)
```bash
sudo apt-get install graphviz
```

This repository contains:
### Binary Search Tree
Binary Search Tree with add and remove methods without balancing (see AVL Tree).

Includes two tests, one of these receives add ('a') commands.

### AVL Tree
Adelson-Velskii and Landis tree. Which means it balances itself.

Includes two tests, one of these receives add ('a') and delete ('d') commands. There is a test called "prueba.in" which can be used as an input to this test.

The Erase() function is not optimized and might fail in specific cases.

### 3D Tree
k-Dimension Tree where k=3 which handles (x, y, z) points.

It can add n points and then search the Nearest Neighbour (NN).

Includes one thest which reads points in the format that has in2.txt

### Generic Tree
n-Child Tree.

Includes several functions to test similarity, equality between two trees, etc.

Includes a test that test most of these functionalities, please check comments on this test.
