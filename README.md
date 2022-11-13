# Graphes

Minimum weight spanning tree with implementation of Kruskal and Prim algorithms.  
Question 30 and above are not implemented.

# Git clone

- https : `https://github.com/Sylcantor/Graphes.git`
- ssh : `git@github.com:Sylcantor/Graphes.git`

# Execution

- `cd src`  
- `make` : to compile  
- `./mst.out -h` : to print the help usage

Exemple of execution with prim algorithm :   

`./mst.out -i ../data/wgraphEl_toygraph -p`  

Exemple of execution with kruskal algorithm and output in a file :   

`./mst.out -i ../data/graphEL_as2000 -o ../data/result.txt -k`
