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
    if (!graph || !str) return (NULL);

    for (vertex_t *v = graph->vertices; v; v = v->next)
        if (strcmp(v->content, str) == 0) return (NULL);

    vertex_t *new_vertex = malloc(sizeof(*new_vertex));
    if (!new_vertex || !(new_vertex->content = strdup(str))) {
        free(new_vertex);
        return (NULL);
    }

    new_vertex->index = graph->nb_vertices++;
    new_vertex->nb_edges = 0;
    new_vertex->edges = NULL;
    new_vertex->next = graph->vertices;
    graph->vertices = new_vertex;

    return (new_vertex);
}
