#include "pathfinding.h"

/**
 * point_push - program that adds a point to the front of the queue
 * with given x and y coordinates
 * @queue: the double pointer to the queue where the point will be added
 * @x: the x-coordinate of the point to add
 * @y: the y-coordinate of the point to add
 * Return: 1 on success, 0 on failure
 */

int point_push(queue_t **queue, int x, int y)
{
	point_t *p;

	p = malloc(sizeof(*p));
	if (!p)
		return (0);
	p->x = x;
	p->y = y;
	queue_push_front(*queue, p);

	return (1);
}

/**
 * backtracker - recursive program that implements backtracking
 * to find a path in a grid
 * this function explores the grid from the current position (x, y)
 * towards the target position
 * @queue: a pointer to the queue where valid path points are stored
 * @saw: a pointer to an array keeping track of visited cells
 * @map: the 2D array representing the grid (1 = obstacle, 0 = free)
 * @rows: the number of rows in the grid
 * @cols: the number of columns in the grid
 * @x: the current x-coordinate
 * @y: the current y-coordinate
 * @target: a pointer to the target position
 * Return: 1 if the target is reached, 0 otherwise
 */

int backtracker(queue_t **queue, int *saw, char **map, int rows,
		int cols, int x, int y, point_t const *target)
{
	int arr[][2] = {RIGHT, BOTTOM, LEFT, TOP}, i;

	if (x < 0 || x >= cols || y < 0 || y >= rows ||
	    map[y][x] == '1' || *(saw + y * cols + x) == 1)
		return (0);

	printf("Checking coordinates [%d, %d]\n", x, y);

	if (x == target->x && y == target->y)
		return (point_push(queue, x, y));

	*(saw + y * cols + x) = 1;

	for (i = 0; i < 4; ++i)
		if (backtracker(queue, saw, map, rows, cols,
				x + arr[i][0], y + arr[i][1], target))
			return (point_push(queue, x, y));
	return (0);
}

/**
 * backtracking_array - program that initializes and manages a backtracking
 * search to find a path in a grid from start to target
 * @map: the 2D array representing the grid
 * @rows: the number of rows in the grid
 * @cols: the number of columns in the grid
 * @start: a pointer to the start position
 * @target: a pointer to the target position
 * Return: a pointer to the queue holding the path,
 *         or NULL if no path is found or on error
 */

queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target)
{
	int *saw;
	queue_t *queue;
	int ret;

	if (!map || !*map || !start || !target || rows < 1 || cols < 1)
		return (NULL);

	saw = calloc(rows * cols, sizeof(*saw));

	if (!saw)
		return (NULL);

	queue = queue_create();

	if (!queue)
	{
		free(saw);
		return (NULL);
	}
	ret = backtracker(&queue, saw, map, rows, cols,
			  start->x, start->y, target);
	if (!ret)
	{
		queue_delete(queue);
		queue = NULL;
	}
	free(saw);

	return (queue);
}
