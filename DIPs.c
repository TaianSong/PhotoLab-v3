
#include "DIPs.h"

/* make the picture color black & white */
IMAGE *BlackNWhite(IMAGE *image)
{
    assert(image);
    int x, y, tmp;
    for (y = 0; y < ImageHeight(image); y++)
    {
        for (x = 0; x < ImageWidth(image); x++)
        {
            tmp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y))/3;
            SetPixelR(image, x, y, tmp);
            SetPixelG(image, x, y, tmp);
            SetPixelB(image, x, y, tmp);
        }
    }
    return image;
}


/* Sharpen function */
IMAGE *Sharpen(IMAGE *image)
{
    assert(image);
    int x, y;
    IMAGE *tmpimage = NULL;
    tmpimage = CreateImage(ImageWidth(image),ImageHeight(image));

    /* sum of the intensity differences with neighbors */
    int tmpR = 0;
    int tmpG = 0;
    int tmpB = 0;

    for (y = 0; y < ImageHeight(image); y++)
    {
        for (x = 0; x < ImageWidth(image); x++)
        {
            SetPixelR(tmpimage, x, y, GetPixelR(image ,x ,y));
            SetPixelG(tmpimage, x, y, GetPixelG(image ,x ,y));
            SetPixelB(tmpimage, x, y, GetPixelB(image ,x ,y));
        }
    }
    for (y = 1; y < ImageHeight(image) - 1 ; y++)
    {
        for (x = 1; x < ImageWidth(image) - 1 ; x++)
        {
            tmpR = 9 * GetPixelR(image ,x ,y) - GetPixelR(image ,x + 1 ,y) - GetPixelR(image ,x - 1 ,y) - GetPixelR(image ,x ,y + 1 ) - GetPixelR(image ,x ,y - 1 ) - GetPixelR(image ,x - 1 ,y - 1) - GetPixelR(image ,x - 1 ,y + 1 ) - GetPixelR(image ,x + 1,y - 1) -GetPixelR(image ,x + 1 ,y + 1);
            tmpG = 9 * GetPixelG(image ,x ,y) - GetPixelG(image ,x + 1 ,y) - GetPixelG(image ,x - 1 ,y) - GetPixelG(image ,x ,y + 1 ) - GetPixelG(image ,x ,y - 1 ) - GetPixelG(image ,x - 1 ,y - 1) - GetPixelG(image ,x - 1 ,y + 1 ) - GetPixelG(image ,x + 1,y - 1) -GetPixelG(image ,x + 1 ,y + 1);
            tmpB = 9 * GetPixelB(image ,x ,y) - GetPixelB(image ,x + 1 ,y) - GetPixelB(image ,x - 1 ,y) - GetPixelB(image ,x ,y + 1 ) - GetPixelB(image ,x ,y - 1 ) - GetPixelB(image ,x - 1 ,y - 1) - GetPixelB(image ,x - 1 ,y + 1 ) - GetPixelB(image ,x + 1,y - 1) -GetPixelB(image ,x + 1 ,y + 1);

            SetPixelR(tmpimage, x, y, (tmpR > 255) ? 255: (tmpR < 0) ? 0: tmpR);
            SetPixelG(tmpimage, x, y, (tmpG > 255) ? 255: (tmpG < 0) ? 0: tmpG);
            SetPixelB(tmpimage, x, y, (tmpB > 255) ? 255: (tmpB < 0) ? 0: tmpB);

        }
    }
    for (y = 0; y < ImageHeight(image); y++)
    {
        for (x = 0; x < ImageWidth(image); x++)
        {
            SetPixelR(image, x, y, GetPixelR(tmpimage ,x ,y));
            SetPixelG(image, x, y, GetPixelG(tmpimage ,x ,y));
            SetPixelB(image, x, y, GetPixelB(tmpimage ,x ,y));
        }
    }
    DeleteImage(tmpimage);
    return image;
}


/*Hue function*/
IMAGE *Hue(IMAGE *image, int degree)
{
    int x, y;
    double a, b, r;
    double d = degree * PI / 180.0;
    double tmp_r, tmp_g, tmp_b;

    a = (2 * cos(d) + 1.0) / 3.0;
    b = (1.0 - cos(d)) / 3.0 - sin(d) / sqrt(3.0);
    r = (1.0 - cos(d)) / 3.0 + sin(d) / sqrt(3.0);

    for (x = 0; x < ImageWidth(image); x++)
    {   for (y = 0; y < ImageHeight(image); y++)
        {   tmp_r = GetPixelR(image ,x ,y) * a + GetPixelG(image ,x ,y) * b + GetPixelB(image ,x ,y) * r;
            tmp_g = GetPixelR(image ,x ,y) * r + GetPixelG(image ,x ,y) * a + GetPixelB(image ,x ,y) * b;
            tmp_b = GetPixelR(image ,x ,y) * b + GetPixelG(image ,x ,y) * r + GetPixelB(image ,x ,y) * a;

            SetPixelR(image, x, y, (tmp_r > 255)?255:(tmp_r < 0)?0:tmp_r);
            SetPixelG(image, x, y, (tmp_r > 255)?255:(tmp_g < 0)?0:tmp_g);
            SetPixelB(image, x, y, (tmp_r > 255)?255:(tmp_b < 0)?0:tmp_b);
        }
    }
    return image;
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
