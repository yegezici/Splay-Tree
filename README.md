# Splay Tree

We built a splay tree simulation in C. We created two versions of this tree: online and offline.
We will explain the program flow:
  In the online version:
    - The user enters an input, and the construction of the tree begins.
    - The user continues to enter inputs.
    - The tree is constructed like a classic binary search tree, but if the user enters the same input more than once, that node will be moved to the root (or "to the top").
    - If multiple nodes have been entered more than once, the most frequently entered one will be at the root.
    - If some nodes have been entered the same number of times, the properties of the binary search tree must be conserved.

  In the offline version these inputs are given in a text file and the program reads and constructs the tree automatically.
