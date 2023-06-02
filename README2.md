##  Assignment

The figure below shows a grid-world where the green cell is the destination cell and the red cells are pitfalls. The world is surrounded by walls.



![figure-grid-world-1](https://user-images.githubusercontent.com/8132627/59187521-ed4a1300-8b75-11e9-9cd3-4fcf8ed585ec.png)



A robot in this world can move in one of the four relative directions (Up, Down, Left, and Right). However, due to some disturbance, when the robot tries to move in any given direction, there is a chance that it actually moves to a different direction. In particular, when the robot tries to move in a direction, there is a probability of 0.1 that it actually moves in the direction that is at the left of the given direction and probability of 0.1 that it actually moves in the direction that is at the right of the given direction. The figure below shows the probability of the direction taken when the robot tries to move Left.



![figure-movements-1](https://user-images.githubusercontent.com/8132627/59187533-f1763080-8b75-11e9-8544-244f72b780da.png)



For example, taking the direction Left moves the robot to the left cell 80% of the time, to the cell above 10% of the time, and to the cell below 10% of the time. If the robot hits a wall, it will stay to the current cell (it will not move). 



This assignment requires to write an algorithm that computes the optimal policy and gives an action (either up, down, left, or right) for each cell of **any grid** like the one above such that the robot, starting from that cell, will eventually reach the green cell with **probability 0.0** of getting into a pitfall, when a solution exists.

Edit the file `main.cpp` and create additional source files if needed.
You can show on screen your solution running the python script `show.py` in the build folder. This script requires [PyGame](pygame.org) installed.

**NOTE:** you should develop code in C++


## How to turn in your solution
1. [Create the new branch](https://help.github.com/articles/creating-and-deleting-branches-within-your-repository) `solution` in the GitHub repository.
1. Complete the assignment within the branch `solution`.
1. [Push](https://help.github.com/articles/pushing-to-a-remote)/sync your changes up to GitHub.
1. [Open a pull request](https://help.github.com/articles/creating-a-pull-request) with `master` as _base_ branch and `solution` as _compare_ branch.

Whenever you need any clarification, [file an issue](../../issues) and we will respond as soon as possible.

## Deadline
Since the date you have accepted the assignment, you will have **7 days** to turn in your solution.
