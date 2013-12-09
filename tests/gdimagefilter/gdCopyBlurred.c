#include <stdio.h>
#include <stdlib.h>

#include "gd.h"
#include "gdtest.h"

#define WIDTH 300
#define HEIGHT 200
#define LX (WIDTH/2)
#define LY (HEIGHT/2)

#define CLOSE_ENOUGH (-1)
#define PIXEL_CLOSE_ENOUGH 1


void
save(gdImagePtr im, const char *filename) {
    FILE *out;

    out = fopen(filename, "wb");
    gdImagePng(im, out);
    fclose(out);
}/* save*/


/* Test gdImageScale() with bicubic interpolation on a simple
 * all-white image. */

gdImagePtr mkwhite(int x, int y)
{
    gdImagePtr im;

	im = gdImageCreateTrueColor(x, y);
	gdImageFilledRectangle(im, 0, 0, x-1, y-1,
                           gdImageColorExactAlpha(im, 255, 255, 255, 0));

    gdTestAssert(im != NULL);

    gdImageSetInterpolationMethod(im, GD_BICUBIC);    // FP interp'n

    return im;
}/* mkwhite*/


/* Fill with almost-black. */
void mkblack(gdImagePtr ptr)
{
    gdImageFilledRectangle(ptr, 0, 0, ptr->sx - 1, ptr->sy - 1,
                           gdImageColorExactAlpha(ptr, 2, 2, 2, 0));
}/* mkblack*/


gdImagePtr mkcross() {
    gdImagePtr im;
    int fg, n;
    const int HT = 3;

    im = mkwhite(WIDTH, HEIGHT);
    fg = gdImageColorAllocate(im, 0, 0, 0);

    for (n = -HT; n < HT; n++) {
        gdImageLine(im, LX-n, 0, LX-n, HEIGHT-1, fg);
        gdImageLine(im, 0, LY-n, WIDTH-1, LY-n, fg);
    }/* for */

    return im;
}/* mkcross*/



void blurblank(gdImagePtr im, int radius, double sigma) {
    gdImagePtr result;

    result = gdImageCopyGaussianBlurred(im, radius, sigma);
    gdTestAssert(!!result);
    if (!result) return;

    gdTestAssert(gdMaxPixelDiff(im, result) <= CLOSE_ENOUGH);

    gdImageDestroy(result);
}/* blurblank*/


void do_test()
{
	gdImagePtr im, imref, tmp;
    gdImagePtr same, same2;

	im = mkwhite(WIDTH, HEIGHT);
    imref = mkwhite(WIDTH, HEIGHT);

    /* Blur a plain white image to various radii and ensure they're
     * still similar enough. */
    blurblank(im, 1, 0.0);
    blurblank(im, 2, 0.0);
    blurblank(im, 4, 0.0);
    blurblank(im, 8, 0.0);
    blurblank(im, 16, 0.0);

    /* Ditto a black image. */
    mkblack(im);
    gdTestAssert(gdMaxPixelDiff(im, imref) >= 240); /* Leaves a little wiggle room */

    blurblank(im, 1, 0.0);
    blurblank(im, 2, 0.0);
    blurblank(im, 4, 0.0);
    blurblank(im, 8, 0.0);
    blurblank(im, 16, 0.0);
}/* do_test*/

/* Ensure that RGB values are equal, then return r (which is therefore
 * the whiteness.) */
int getwhite(gdImagePtr im, int x, int y)
{
    int px, r, g, b;

    px = gdImageGetPixel(im, x, y);
    r = gdImageRed(im, px);
    g = gdImageGreen(im, px);
    b = gdImageBlue(im, px);

    gdTestAssert(r == g && r == b);

    return r;
}/* getrgb*/

int whitecmp(gdImagePtr im1, gdImagePtr im2, int x, int y) {
    int w1, w2;

    w1 = getwhite(im1, x, y);
    w2 = getwhite(im2, x, y);

    return abs(w1 - w2);
}/* whitediff*/

void do_crosstest()
{
    gdImagePtr im = mkcross();
    gdImagePtr blurred;
    const int RADIUS = 16; 

    gdTestAssert(!!im);

    save(im, "cross.png");

    blurred = gdImageCopyGaussianBlurred(im, RADIUS, 0.0);
    save(blurred, "blurredcross.png");

    /* These spots shouldn't be affected. */
    gdTestAssert(whitecmp(im, blurred, 5, 5) < PIXEL_CLOSE_ENOUGH);
    gdTestAssert(whitecmp(im, blurred, WIDTH-5, 5) < PIXEL_CLOSE_ENOUGH);
    gdTestAssert(whitecmp(im, blurred, 5, HEIGHT-5) < PIXEL_CLOSE_ENOUGH);
    gdTestAssert(whitecmp(im, blurred, WIDTH-5, HEIGHT-5) < PIXEL_CLOSE_ENOUGH);

    /* Ditto these, right in the corners */
    gdTestAssert(whitecmp(im, blurred, 0, 0) < PIXEL_CLOSE_ENOUGH);
    gdTestAssert(whitecmp(im, blurred, WIDTH-1, 0) < PIXEL_CLOSE_ENOUGH);
    gdTestAssert(whitecmp(im, blurred, 0, HEIGHT-1) < PIXEL_CLOSE_ENOUGH);
    gdTestAssert(whitecmp(im, blurred, WIDTH-1, HEIGHT-1) < PIXEL_CLOSE_ENOUGH);


}/* do_crosstest*/


int main(int argc, char **argv)
{

    do_test();
    do_crosstest();

    return gdNumFailures();
}
