#include <math.h>
#include "algorithms.h"
#include "geo_array.h"

static double rdp_find_perpendicular_distable(double pX, double pY, double p1X, double p1Y, double p2X, double p2Y)
{
	double slope, intercept, result;

	if (p1X == p2X) {
		return fabs(pX - p1X);
	} else {
		slope = (p2Y - p1Y) / (p2X - p1X);
		intercept = p1Y - (slope * p1X);
		result = fabs(slope * pX - pY + intercept) / sqrt(pow(slope, 2) + 1);
		return result;
	}
}

void rdp_simplify(geo_array *points, double epsilon, int start, int end)
{
	double firstX = points->x[start], firstY = points->y[start];
	double lastX = points->x[end], lastY = points->y[end];
	int    index = -1, i;
	double dist  = 0.0, current_dist;

	if (end - start < 2) {
		return;
	}

	for (i = start + 1; i < end; i++) {
		if (!points->status[i]) {
			continue;
		}

		current_dist = rdp_find_perpendicular_distable(points->x[i], points->y[i], firstX, firstY, lastX, lastY);

		if (current_dist > dist) {
			dist = current_dist;
			index = i;
		}
	}

	if (dist > epsilon) {
		rdp_simplify(points, epsilon, start, index);
		rdp_simplify(points, epsilon, index, end);

		return;
	} else {
		for (i = start + 1; i < end; i++) {
			points->status[i] = 0;
		}
		return;
	}
}

int polar_to_cartesian(double radius, double angle, double *x, double *y)
{
	/* PHP:
	$x = $radius * cos(deg2rad(angle));
	$y = $radius * sin(deg2rad(angle));
	*/
	*x = radius * cos(deg2rad(angle));
	*y = radius * sin(deg2rad(angle));
}

int cartesian_to_polar(double x, double y, double *radius, double *angle)
{
	/* PHP:
	$radius = sqrt($x * $x + $y * $y);
	$angle  = rad2deg(atan2($y, $x));
	*/
	*radius = sqrt(x * x + y * y);
	*angle  = rad2deg(atan2(y, x));
}
