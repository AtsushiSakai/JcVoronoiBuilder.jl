//
//  c voronoi code interface c code
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <float.h>

#define JC_VORONOI_IMPLEMENTATION
#define JCV_REAL_TYPE double
#define JCV_FABS fabs
#define JCV_ATAN2 atan2
#define NDEBUG //For ignore assertion check

#include "jc_voronoi.h"

/**
 * @brief voronoi point calculation function with jc_voronoi.h
 *
 * @param x :x position lists of input points
 * @param y :y position lists of input points
 * @param(return) rx :x position lists of voronoi points
 * @param(return) ry :y position lists of voronoi points
 * @param np: input points number 
 * @param nxmax : maximum voronoi points number 
 *
 * @return voronoi points number
 */
int calc_voronoi_points(double *x, double *y,
        double *rx, double*ry, int64_t np, int64_t nxmax){
    /* printf("hello, np is %d\n", np); */

    double maxx = -DBL_MAX;
    double maxy = -DBL_MAX;
    double minx = DBL_MAX;
    double miny = DBL_MAX;

    jcv_point* points = (jcv_point*)malloc( sizeof(jcv_point)*np );
    for( uint64_t i = 0; i < np; ++i ){
        points[i].x = x[i];
        points[i].y = y[i];

        if(x[i] >= maxx){maxx = x[i];}
        else if(x[i]<=minx){minx = x[i];}
        if(y[i] >= maxy){maxy = y[i];}
        else if(y[i]<=miny){miny = y[i];}
    }

    jcv_diagram diagram;
    memset(&diagram, 0, sizeof(jcv_diagram));
    jcv_diagram_generate(np, points, 0, 0, &diagram );
    const jcv_edge* edge = jcv_diagram_get_edges( &diagram );
    uint64_t count = 0;
    while( edge ){
        //outbound
        if(edge->pos[0].x <= minx ||
           edge->pos[0].x >= maxx ||
           edge->pos[0].y <= miny ||
           edge->pos[0].y >= maxy
                ){
            edge = edge->next;
            continue;
        }

        rx[count] = edge->pos[0].x;
        ry[count] = edge->pos[0].y;
        count++;
        edge = edge->next;
        if(count >= nxmax){
            printf("Error(calc_voronoi_points):return list is overflow!!\n");
            break;
        }
    }

    jcv_diagram_free(&diagram);

    return count;
}
