#ifndef BEST_FIT_H

#define BEST_FIT_H

// This routine was released in 'snippet' form
// by John W. Ratcliff mailto:jratcliffscarab@gmail.com
// on March 22, 2006.
//
// This routine computes the 'best fit' plane equation to
// a set of input data points with an optional per vertex
// weighting component.
//
// The implementation for this was lifted directly from
// David Eberly's Magic Software implementation.

// computes the best fit plane to a collection of data points.
// returns the plane equation as A,B,C,D format. (Ax+By+Cz+D)
//
// Geometric Tools, Inc.
// http://www.geometrictools.com
// Copyright (c) 1998-2006.  All Rights Reserved

// A version that works with double precision floats.

bool getBestFitPlane(unsigned int vcount,     // number of input data points
                     const double *points,     // starting address of points array.
                     unsigned int vstride,    // stride between input points.
                     const double *weights,    // *optional point weighting values.
                     unsigned int wstride,    // weight stride for each vertex.
                     double *plane);

// A version that works with single precision floats.
bool getBestFitPlane(unsigned int vcount,     // number of input data points
					 const float *points,     // starting address of points array.
					 unsigned int vstride,    // stride between input points.
					 const float *weights,    // *optional point weighting values.
					 unsigned int wstride,    // weight stride for each vertex.
					 float *plane);


#endif
