#include <stdio.h>

#include "gd.h"
#include "gdtest.h"

void png(gdImagePtr im, const char *filename)
{    
    FILE *fh;
    fh = fopen(filename, "w");
    gdImagePng(im, fh);
    fclose(fh);
}/* png*/

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





void do_test(int x, int y, int nx, int ny)
{
	gdImagePtr im, tmp;
    gdImagePtr samex, samey, same, same2;

	im = mkwhite(x, y);
    same = gdImageScale(im, x, y);
//gdImageFilledRectangle(same, 0, 0, x-1, y-1,
//                           gdImageColorExactAlpha(im, 2, 2, 2, 0));
//    png(same, "same.png");
//    png(im, "im.png");

    /* Trivial resize should be a straight copy. */
    gdTestAssert(im != same);
    gdTestAssert(gdTestImageCompareToImage(__FILE__, __LINE__,
                                           "Trivial resize yields different image.",
                                           im, same));
    gdImageDestroy(same);

    /* Scale only horizontally */
    tmp = gdImageScale(im, x, ny);
    samex = gdImageScale(tmp, x, y);
printf("diff: %u\n", gdMaxPixelDiff(im, samex));
png(samex, "samex.png");
png(im, "im.png");
    gdTestAssert(0 != gdMaxPixelDiff(im, samex));



}

int main(int argc, char **argv)
{

    do_test(300, 300, 600, 600);
//    do_test(3200, 2133, 640, 427);

    return gdNumFailures();
#if 0
	gdImagePtr im;
	char path[2048];
	const char *file_exp = "gdimageline/gdImageAALine_thickness_exp.png";

	im = gdImageCreateTrueColor(100, 100);
	gdImageFilledRectangle(im, 0, 0, 99, 99,
			       gdImageColorExactAlpha(im, 255, 255, 255, 0));

	gdImageSetThickness(im, 5);
	gdImageSetAntiAliased(im, gdImageColorExactAlpha(im, 0, 0, 0, 0));
	gdImageLine(im, 0,0, 99, 99, gdAntiAliased);

	sprintf(path, "%s/%s", GDTEST_TOP_DIR, file_exp);

	if (!gdAssertImageEqualsToFile(path, im)) {
		printf("comparing rotated image to %s failed.\n", path);
		gdImageDestroy(im);
		return 1;
	}

	gdImageDestroy(im);
#endif
}
