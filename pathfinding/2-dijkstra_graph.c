#include "pathfinding.h"

/**
 * constructPathFromQueue - program that constructs a path
 * from the result of Dijkstra's algorithm
 * the function extracts and creates a queue representing
 * the shortest path to the target vertex
 * @d_queue: the array containing vertex states from Dijkstra's
 *           execution
 * @target_i: the index of the target vertex within the queue
 * Return: a queue representing the path from the start vertex
 *         to the target vertex
 */

queue_t *constructPathFromQueue(dijkstra_vertex_t *d_queue, size_t target_i)
{
	queue_t *path = NULL;
	vertex_t *via = NULL;
	char *via_name = NULL;
	long int i;

	if (!d_queue)
		return (NULL);

	path = queue_create();

	if (!path)
		return (NULL);

	via_name = strdup(d_queue[target_i].vertex->content);
	queue_push_front(path, (void *)via_name);
	via = d_queue[target_i].path_via;

	for (i = target_i; i >= 0; i--)
	{
		if (d_queue[i].vertex == via)
		{
			via_name = strdup(d_queue[i].vertex->content);
			queue_push_front(path, (void *)via_name);
			via = d_queue[i].path_via;
		}
	}

	if (via != NULL)
	{
		while (path->front)
			free(dequeue(path));
		queue_delete(path);
		path = NULL;
	}
	return (path);
}

/**
 * weightComparator - program that compares two vertices based on
 * their cumulative weight
 * this function is used for sorting vertices during Dijkstra's algorithm
 * @param1: the first vertex to compare
 * @param2: the second vertex to compare
 * Return: an integer less than, equal to, or greater than zero if the
 *         first argument is considered to be respectively less than,
 *         equal to, or greater than the second
 */

int weightComparator(const void *param1, const void *param2)
{
	dijkstra_vertex_t *D_vert1 = NULL, *D_vert2 = NULL;

	if (!param1 && !param2)
		return (0);
	if (param1 && !param2)
		return (1);
	if (!param1 && param2)
		return (-1);

	D_vert1 = (dijkstra_vertex_t *)param1;
	D_vert2 = (dijkstra_vertex_t *)param2;

	if (D_vert1->cml_weight > D_vert2->cml_weight)
		return (1);
	else if (D_vert1->cml_weight < D_vert2->cml_weight)
		return (-1);
	else if (param1 > param2)
		return (1);
	else if (param1 < param2)
		return (-1);

	return (0);
}

/**
 * evaluateVertexEdges - program that evaluates and updates
 * the shortest paths to vertices connected to the current vertex
 * @d_queue: the array of vertices with their current state in
 *           Dijkstra's algorithm
 * @nb_vertices: the total number of vertices
 * @dq_head_i: the index of the current vertex being evaluated
 * Return: nothing (void)
 */

void evaluateVertexEdges(dijkstra_vertex_t *d_queue, size_t nb_vertices,
			 size_t dq_head_i)
{
	dijkstra_vertex_t dq_head;
	edge_t *temp_e = NULL;
	size_t i;

	if (!d_queue)
		return;

	dq_head = d_queue[dq_head_i];

	for (temp_e = dq_head.vertex->edges; temp_e; temp_e = temp_e->next)
	{
		if (dq_head.path_via && strcmp(temp_e->dest->content, dq_head.path_via->content) == 0)
			continue;

		for (i = dq_head_i; i < nb_vertices; i++)
		{
			if (strcmp(temp_e->dest->content, d_queue[i].vertex->content) == 0)
			{
				if (dq_head.cml_weight + temp_e->weight < d_queue[i].cml_weight)
				{
					d_queue[i].cml_weight = dq_head.cml_weight + temp_e->weight;
					d_queue[i].path_via = dq_head.vertex;
				}
			}
		}
	}

	dq_head_i++;

	qsort((void *)(d_queue + dq_head_i),
	      nb_vertices - dq_head_i,
	      sizeof(dijkstra_vertex_t), weightComparator);
}

/**
 * runDijkstraAlgorithm - program that implements Dijkstra's algorithm
 * for pathfinding between a start and a target vertex
 * this function evaluates shortest paths from the start vertex
 * to all others and identifies the path to a target vertex
 * @d_queue: the array of vertex states initialized for Dijkstra's algorithm
 * @nb_vertices: the total number of vertices in the graph
 * @start: a pointer to the start vertex
 * @target: a pointer to the target vertex
 * @dq_head_i: the index of the current vertex being evaluated
 * @target_i: a pointer to store the index of the target vertex once found
 * Return: 0 for success, 1 for failure
 */

int runDijkstraAlgorithm(dijkstra_vertex_t *d_queue, size_t nb_vertices,
			 const vertex_t *start, const vertex_t *target,
			 size_t dq_head_i, size_t *target_i)
{
	dijkstra_vertex_t dq_head;

	if (!d_queue || !start || !target || !target_i)
		return (1);

	dq_head = d_queue[dq_head_i];

	printf("Checking %s, distance from %s is %lu\n",
	       dq_head.vertex->content, start->content, dq_head.cml_weight);

	evaluateVertexEdges(d_queue, nb_vertices, dq_head_i);

	if (strcmp(target->content, dq_head.vertex->content) == 0)
	{
		*target_i = dq_head_i;
		return (0);
	}

	if (dq_head_i == nb_vertices - 1)
		return (1);

	if (d_queue[dq_head_i + 1].cml_weight == ULONG_MAX ||
	    d_queue[dq_head_i + 1].path_via == NULL)
		return (1);

	return (runDijkstraAlgorithm(d_queue, nb_vertices, start, target,
				     dq_head_i + 1, target_i));
}

/**
 * dijkstra_graph - program that sets up and executes Dijkstra's algorithm on a graph
 * this function initializes a queue for the Dijkstra process, sorts vertices,
 * and calculates the shortest path from a start to a target vertex
 * @graph: a pointer to the graph containing the vertices
 * @start: a pointer to the starting vertex for the pathfinding
 * @target: a pointer to the target vertex for the pathfinding
 * Return: a queue representing the shortest path from start to target,
 *         or NULL if the path cannot be established or memory allocation fails
 */

queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
			vertex_t const *target)
{
	dijkstra_vertex_t *dijkstra_queue = NULL;
	vertex_t *temp_v = NULL;
	size_t i, target_i;
	queue_t *path = NULL;

	if (!graph || !graph->nb_vertices || !graph->vertices ||
	    !start || !target)
		return (NULL);

	dijkstra_queue = malloc(sizeof(dijkstra_vertex_t) * graph->nb_vertices);

	if (!dijkstra_queue)
		return (NULL);

	for (i = 0, temp_v = graph->vertices; i < graph->nb_vertices;
	     i++, temp_v = temp_v->next)
	{
		dijkstra_queue[i].vertex = temp_v;

		if (strcmp(start->content, temp_v->content) == 0)
			dijkstra_queue[i].cml_weight = 0;
		else
			dijkstra_queue[i].cml_weight = ULONG_MAX;

		dijkstra_queue[i].path_via = NULL;
	}

	qsort((void *)dijkstra_queue, graph->nb_vertices,
	      sizeof(dijkstra_vertex_t), weightComparator);

	if (runDijkstraAlgorithm(dijkstra_queue, graph->nb_vertices,
			  start, target, 0, &target_i) != 0)
	{
		free(dijkstra_queue);
		return (NULL);
	}

	path = constructPathFromQueue(dijkstra_queue, target_i);
	free(dijkstra_queue);

	return (path);
}
