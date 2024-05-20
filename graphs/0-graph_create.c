#include "graphs.h"

/**
 * graph_create - program that creates an empty graph_t structure
 * Return: a pointer to the newly created graph_t structure on success,
 *         or NULL if memory allocation fails
 */

graph_t *graph_create(void)
{
	graph_t *graph = (graph_t *)malloc(sizeof(graph_t));

	if (graph)
	{
		graph->nb_vertices = 0;
		graph->vertices = NULL;
	}

	return (graph);
}
