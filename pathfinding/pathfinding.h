#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "graphs.h"
#include "queues.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define RIGHT {1, 0}
#define BOTTOM {0, 1}
#define LEFT {-1, 0}
#define TOP {0, -1}

/**
 * struct point_s - Structure storing coordinates
 * @x: X coordinate
 * @y: Y coordinate
 */

typedef struct point_s
{
	int x;
	int y;
} point_t;

/* ---------------------------------------------------------------------------- */

/* 2-dijkstra_graph.c */

/**
 * struct dijkstra_vertex_s - Vertex structure in the context of Dijkstra's algorithm
 * This structure is used to store the state and track the path of each vertex during the
 * execution of Dijkstra's algorithm for finding the shortest path in a graph
 * @vertex: a pointer to the vertex itself, storing or referencing the actual graph vertex
 * @cml_weight: the cumulative weight from the source vertex to this vertex;
 *              it represents the total cost to reach this vertex from the source in the
 *              path found so far
 * @path_via: a pointer to another vertex structure indicating the previous vertex in the
 *            optimal path from the source;
 *            this helps in reconstructing the shortest path once the algorithm completes
 */

typedef struct dijkstra_vertex_s
{
    vertex_t *vertex;      /* Pointer to the actual graph vertex */
    size_t cml_weight;     /* Cumulative weight from source to this vertex */
    vertex_t *path_via;    /* Pointer to the previous vertex in the shortest path */
} dijkstra_vertex_t;


/* ---------------------------------------------------------------------------- */

/* task 0 */
queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target);
int point_push(queue_t **queue, int x, int y);
int backtracker(queue_t **queue, int *saw, char **map, int rows,
		int cols, int x, int y, point_t const *target);

/* task 1 */
queue_node_t *graph_fill(queue_t *new_node, int *saw, const vertex_t *current,
			 char *target);
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			    vertex_t const *target);

/* task 2 */
queue_t *constructPathFromQueue(dijkstra_vertex_t *d_queue, size_t target_i);
int weightComparator(const void *param1, const void *param2);
void evaluateVertexEdges(dijkstra_vertex_t *d_queue, size_t nb_vertices,
			 size_t dq_head_i);
int runDijkstraAlgorithm(dijkstra_vertex_t *d_queue, size_t nb_vertices,
			 const vertex_t *start, const vertex_t *target,
			 size_t dq_head_i, size_t *target_i);
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
			vertex_t const *target);

#endif /* PATHFINDING_H */
