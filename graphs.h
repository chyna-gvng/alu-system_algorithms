#ifndef GRAPHS_H
#define GRAPHS_H


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/**
 * enum edge_type_e - enumerates the different types of
 * connection between two vertices
 * @UNIDIRECTIONAL: the connection is made only in one way
 * @BIDIRECTIONAL: the connection is made in two ways
 */

typedef enum edge_type_e
{
	UNIDIRECTIONAL = 0,
	BIDIRECTIONAL
} edge_type_t;



/* Define the structure temporarily for usage in the edge_t */
typedef struct vertex_s vertex_t;



/**
 * struct edge_s - Edge structure in a graph's adjacency list
 * this structure is used to represent an edge in a graph, where each edge
 * connects a vertex to another vertex (destination);
 * each vertex in the graph maintains a linked list of 'edge_t' structures,
 * representing all the vertices (destinations) it is connected to directly
 * via an edge
 * @dest: a pointer to the destination vertex this edge connects to
 * @next: a pointer to the next edge in the linked list of edges for the vertex
 */

typedef struct edge_s
{
	vertex_t *dest;
	struct edge_s *next;
} edge_t;



/**
 * struct vertex_s - Node structure in the linked list of vertices
 * in the adjacency list
 * @index: the index of the vertex in the adjacency list.
 * @content: the custom data stored in the vertex (here, a string)
 * @nb_edges: the number of connections with other vertices in the graph
 * @edges: a pointer to the head node of the linked list of edges
 * @next: a pointer to the next vertex in the adjacency linked list;
 *        this pointer points to another vertex in the graph, but it
 *        doesn't stand for an edge between the two vertices
 */

struct vertex_s
{
	size_t index;
	char *content;
	size_t nb_edges;
	edge_t *edges;
	struct vertex_s *next;
};



/**
 * struct graph_s - Graph structure
 * this structure serves as a representation for a graph data structure
 * using an adjacency list approach;
 * the graph is composed of vertices connected by edges;
 * the structure maintains the count of vertices and a pointer
 * to the list of adjacency lists for each vertex
 * @nb_vertices: the number of vertices in the graph;
 *               this is the count of distinct nodes present in the graph
 * @vertices: a pointer to the head node of our adjacency linked list;
 *            this pointer points to an array or linked list of vertices,
 *            where each vertex has its own adjacency list representing
 *            edges to neighboring vertices
 */

typedef struct graph_s
{
	size_t nb_vertices;
	vertex_t *vertices;
} graph_t;



/**
 * struct GraphQueueNode - Node structure for a queue in graph traversal
 * this structure represents a single node in a queue used for graph traversal;
 * each node holds a vertex from the graph, the depth of that vertex in the
 * traversal, and a pointer to the next node in the queue
 * @vertex: a pointer to the vertex associated with this node
 * @depth: the depth of the vertex in the traversal from the starting point
 * @next: a pointer to the next node in the queue
 */

typedef struct GraphQueueNode
{
    	vertex_t *vertex;
    	size_t depth;
    	struct GraphQueueNode *next;
} GraphQueueNode;



/**
 * struct GraphQueue - Queue structure for managing nodes in graph traversal
 * this structure represents a queue used for breadth-first traversal of a graph;
 * it keeps track of the front and rear of the queue (head and tail), as well as
 * the total number of nodes currently in the queue;
 * this queue is used to manage the order in which vertices are visited
 * during the traversal
 * @head: a pointer to the first node in the queue
 * @tail: a pointer to the last node in the queue
 * @size: the number of nodes currently in the queue
 */

typedef struct GraphQueue
{
    	GraphQueueNode *head;
    	GraphQueueNode *tail;
    	size_t size;
} GraphQueue;

/* function needed for testing */
void graph_display(const graph_t *graph);


/* task 0 */
graph_t *graph_create(void);

/* task 1 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str);

/* task 2 */
edge_t *graph_add_single_edge(vertex_t *src_vertex, vertex_t *dest_vertex);
int graph_add_edge(graph_t *graph, const char *src,
		   const char *dest, edge_type_t type);

/* task 3 */
void graph_delete(graph_t *graph);

/* task 4 */
size_t traverseVerticesRecursively(vertex_t *vertex, char *visited_flags,
				   size_t current_depth, void (*vertex_action)
				   (const vertex_t *v, size_t depth));
size_t depth_first_traverse(const graph_t *graph, void (*action)
			    (const vertex_t *v, size_t depth));

/* task 5 */
void freeQueue(GraphQueue *queue);
int pushToQueue(GraphQueue *queue, vertex_t *vertex, size_t depth);
int popFromQueue(GraphQueue *queue, vertex_t **vertex, size_t *depth);
void processEdges(GraphQueue *queue, const vertex_t *vertex,
		  size_t currentDepth, size_t *visited);
size_t breadth_first_traverse(const graph_t *graph, void (*action)
			      (const vertex_t *v, size_t depth));



#endif /* GRAPHS_H */
