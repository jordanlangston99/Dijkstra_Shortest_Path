README

FOUNDATION OF THE PROGRAM

This program uses adjacency lists to represent network graphs to allow users to determine things such as shortest path directions between two nodes on a graph, the distance of said path, and whether or not a path exists from one node to another. 

Once the program is called with appropriate arguments, the user is able to give the following commands:

“find <source> <destination> <flag>”
“write path <source> <destination>”
“stop”

In these commands, source and destination represent the nodes in which the user in interested in and are represented by their unique node number. The flag is an optional command the user can set to ‘1’ when they wish to see the min-heap operations printed as the program evaluates a shortest path between given nodes.

Command “find <source> <destination> <flag>” evaluates the shortest path distances between nodes of the graph by loading the source node into an adjacency list and performing a breadth first search on the graph. If the destination node is set to a node number that does not exist, the program will evaluate all possible paths of the graph.

Command “write path <source> <destination>” will print the shortest possible path from source node to destination node by printing the node numbers in the order they would be traversed.

Command “stop” halts the program.

COMPILATION AND GRAPH FORMAT

The Makefile will compile these files into an executable called “dijkstra”
The executable program takes two inputs and looks like this when called:

./dijkstra <graph text file name> <direction>

These two arguments tell the program where to find the network file representing the graph in a text file, which in this case needs to be formatted as follows:

The first line in the file contains two positive integers ’n’ and ‘m’ where n is the number of vertices and m is the number of edges in the graph.

Each of the next m lines should have four space separated fields of the form:

<edge_ID> <vertex_u> <vertex_w> <weight> 

where <edge ID> is an integer in the interval [1,m] denoting the identifier of an edge, <vertex u> and
<vertex v> are two integers in the interval [1,n] denoting the vertices that are the endpoints of the edge,
and <weight> is a non-negative foating point number denoting the edge weight, of distance between two nodes.

If the graph is directed, i.e., parameter <direction> is directed, then each line in the file represents a
directed edge from vertex u to vertex v, with weight “weight”. If the graph is undirected, i.e., parameter <direction> is undirected, each line in the file represents an edge connecting vertex u and vertex v, with weight “weight”.

G must be represented in this way as the program stores the graph as adjacency lists.
