
#ifndef __FIXEDPOINT_H
#define __FIXEDPOINT_H

/* This should be 32-bits. */
typedef int Fixed;

/* Integer to fixed point */
#define itofx(x) ((x) << 8)

/* Float to fixed point */
#define ftofx(x) (long)((x) * 256)

/*  Double to fixed point */
#define dtofx(x) (long)((x) * 256)

/* Fixed point to integer */
#define fxtoi(x) ((x) >> 8)

/* Fixed point to float */
# define fxtof(x) ((float)(x) / 256)

/* Fixed point to double */
#define fxtod(x) ((double)(x) / 256)

/* Multiply a fixed by a fixed */
#define mulfx(x,y) (((x) * (y)) >> 8)

/* Divide a fixed by a fixed */
#define divfx(x,y) (((x) << 8) / (y))


#endif
