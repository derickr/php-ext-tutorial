#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include "geo_array.h"

#define deg2rad(deg) ((deg) * M_PI / 180.0)
#define rad2deg(rad) ((rad) * 180.0 / M_PI)

void rdp_simplify(geo_array *points, double epsilon, int start, int end);
int polar_to_cartesian(double radius, double angle, double *x, double *y);
int cartesian_to_polar(double x, double y, double *radius, double *angle);

#endif /* __ALGORITHMS_H__ */

