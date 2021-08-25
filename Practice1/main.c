#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

struct point
{
  int x, y;
};

typedef struct point point;

void
read (point * p)
{
  scanf ("%d", &(p->x));
  scanf ("%d", &(p->y));
}

void
print (point p)
{
  printf ("%4d%4d", p.x, p.y);
}

int
x_distance (point p1, point p2)
{
  return abs (p2.x - p1.x) + 1;
}

int
y_distance (point p1, point p2)
{
  return abs (p2.y - p1.y) + 1;
}

bool
are_equal (point p1, point p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}

// Caso 0: 
void
perfect_line (point p1, point p2, point * table)
{
  int dx = p2.x > p1.x ? 1 : -1;
  int dy = p2.y > p1.y ? 1 : -1;

  int i = 0;
  table[i++] = p1;
  while (!are_equal (p1, p2))
    {
      p1.x += dx;
      p1.y += dy;
      table[i++] = p1;
    }
}

void
x_line (point p1, point p2, point * table)
{
  int dx = x_distance (p1, p2);
  int dy = y_distance (p1, p2);

  int points_per_row = dx / dy;
  int points_extras = dx % dy;

  int sx = p2.x > p1.x ? 1 : -1;
  int sy = p2.y > p1.y ? 1 : -1;

  int n_points = 0;
  for (;;)
    {
      int p_extra = points_extras > 0 ? 1 : 0;
      for (int i = 0; i < points_per_row + p_extra; i++)
	{
	  table[n_points++] = p1;
	  if (are_equal (p1, p2))
	    return;
	  p1.x += sx;
	}
      points_extras--;
      p1.y += sy;
    }
}

void
y_line (point p1, point p2, point * table)
{
  int dx = x_distance (p1, p2);
  int dy = y_distance (p1, p2);

  int points_per_row = dy / dx;
  int points_extras = dy % dx;

  int sx = p2.x > p1.x ? 1 : -1;
  int sy = p2.y > p1.y ? 1 : -1;

  int n_points = 0;
  for (;;)
    {
      int p_extra = points_extras > 0 ? 1 : 0;
      for (int i = 0; i < points_per_row + p_extra; i++)
	{
	  table[n_points++] = p1;
	  if (are_equal (p1, p2))
	    return;
	  p1.y += sy;
	}
      points_extras--;
      p1.x += sx;
    }
}

void
print_table (point * t, int size)
{
  printf("   x   y\n");    
  for (int i = 0; i < size; i++)
    {
      print (t[i]);
      printf ("\n");
    }
}

void
to_image (point * t, int size)
{
  point p1 = t[0];
  point p2 = t[size - 1];

  FILE *f = fopen ("line.ppm", "w");
  fprintf (f, "P3\n");
  fprintf (f, "101 101\n");
  fprintf (f, "1\n");

  bool has_point[101][101];

  for (int i = 0; i < 101; i++)
    for (int j = 0; j < 101; j++)
      has_point[i][j] = false;

  for (int i = 0; i < size; i++)
    has_point[100 - t[i].y][t[i].x] = true;

  for (int i = 0; i < 101; i++)
    {
      for (int j = 0; j < 101; j++)
	fprintf (f, "%d %d %d ", has_point[i][j], has_point[i][j],
		 has_point[i][j]);
      fprintf (f, "\n");
    }
  fclose (f);
}


int
main ()
{
  point p1, p2;
  read (&p1);
  read (&p2);
  int total_points_to_color = fmax (x_distance (p1, p2), y_distance (p1, p2));
  point *table = malloc (total_points_to_color * sizeof (point));

  int dx = x_distance (p1, p2);
  int dy = y_distance (p1, p2);

  if (dx == dy)
    perfect_line (p1, p2, table);
  else if (dx > dy)
    x_line (p1, p2, table);
  else
    y_line (p1, p2, table);

  print_table (table, total_points_to_color);
  to_image (table, total_points_to_color);
  return 0;
}
