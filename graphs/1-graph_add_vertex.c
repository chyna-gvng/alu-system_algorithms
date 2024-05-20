#include "graphs.h"

/**
 * graph_add_vertex - program that adds a new vertex to an existing graph
 * @graph: a pointer to the graph to add the vertex to
 * @str: the string to store in the new vertex
 * Return: a pointer to the created vertex on success,
 *         or NULL if memory allocation fails or the vertex already exists
 */

vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *current_vertex;
	vertex_t *new_vertex;

	if (graph == NULL || str == NULL)
		return (NULL);

	for (current_vertex = graph->vertices; current_vertex != NULL;
	     current_vertex = current_vertex->next)
	{
		if (strcmp(current_vertex->content, str) == 0)
			return (NULL);
	}
	new_vertex = (vertex_t *)malloc(sizeof(vertex_t));

	if (new_vertex == NULL)
		return (NULL);

	new_vertex->content = strdup(str);

	if (new_vertex->content == NULL)
	{
		free(new_vertex);
		return (NULL);
	}
	new_vertex->index = graph->nb_vertices;
	new_vertex->nb_edges = 0;
	new_vertex->edges = NULL;
	new_vertex->next = NULL;

	if (graph->vertices == NULL)
	{
		graph->vertices = new_vertex;
	}
	else
	{
		vertex_t *current = graph->vertices;

		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_vertex;
	}
	graph->nb_vertices++;

	return (new_vertex);
}
