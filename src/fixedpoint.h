
#ifndef __FIXEDPOINT_H
#define __FIXEDPOINT_H

#include <stdint.h>

/* This should be a 32-bit quantity.  It *looks* like most compilers
 * default to a 32-bit int. */
typedef int32_t gdFixed;

/* Integer to fixed point */
#define gd_itofx(x) ((x) << 8)

/* Float to fixed point */
#define gd_ftofx(x) (long)((x) * 256)

/*  Double to fixed point */
#define gd_dtofx(x) (long)((x) * 256)

/* Fixed point to integer */
#define gd_fxtoi(x) ((x) >> 8)

/* Fixed point to float */
# define gd_fxtof(x) ((float)(x) / 256)

/* Fixed point to double */
#define gd_fxtod(x) ((double)(x) / 256)

/* Multiply a fixed by a fixed */
#define gd_mulfx(x,y) (((x) * (y)) >> 8)

/* Divide a fixed by a fixed */
#define gd_divfx(x,y) (((x) << 8) / (y))

#endif




#if 0

/* Reimplementation as inline functions.  This turns out to have a
 * performance hit but I'm leaving the code here in case can do
 * something with it later.*/

/* Integer to fixed point */
static inline gdFixed gd_itofx(int x)                {return x << 8;}

/* Float to fixed point */
static inline gdFixed gd_ftofx(float x)              {return (gdFixed)(x * 256);}

/*  Double to fixed point */
static inline gdFixed gd_dtofx(double x)             {return (gdFixed)(x * 256);}

/* Fixed point to integer */
static inline int gd_fxtoi(gdFixed x)                {return (int)(x >> 8);}

/* Fixed point to float */
static inline float gd_fxtof(gdFixed x)              {return (float)x / 256;}

/* Fixed point to double */
static inline double gd_fxtod(gdFixed x)             {return (double)x / 256;}

/* Multiply a fixed by a fixed */
static inline gdFixed gd_mulfx(gdFixed x, gdFixed y) {return (x * y) >> 8;}

/* Divide a fixed by a fixed */
static inline gdFixed gd_divfx(gdFixed x, gdFixed y) {return (x << 8) / y;}

#endif
