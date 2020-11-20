#include "Advanced.h"


#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* Add noise to an image */
IMAGE *Noise (IMAGE *image, int n)
{
    int x, y, i;
    int num;  /*number of noise added*/
    num = ( n*ImageHeight(image)*ImageWidth(image) )/100;
    srand(time(NULL));

    for ( i = 0; i < num; i++ ) {
        x = ((double) rand() / RAND_MAX) * (ImageWidth(image) - 1);
        y = ((double) rand() / RAND_MAX) * (ImageHeight(image) - 1);
        SetPixelR(image, x, y, 255);
        SetPixelG(image, x, y, 255);
        SetPixelB(image, x, y, 255);
    }
    return (image);
}

/* make the image posterized */
IMAGE *Posterize (IMAGE *image, int rbits, int gbits, int bbits)
{
    int x, y, i;
    for(x=0; x<ImageWidth(image); x++)
    {
        for (y = 0; y < ImageHeight(image); y++)
        {
            unsigned char one = 1;
            for (i = 0; i < rbits - 1; i++)
            {
                SetPixelR(image, x, y, GetPixelR(image, x, y) | one);
                one <<= 1;
            }
            one = ~one;
            SetPixelR(image, x, y, GetPixelR(image, x, y) & one);
            one  = 1;
            for (i = 0; i < rbits - 1; i++)
            {
                SetPixelG(image, x, y, GetPixelG(image, x, y) | one);
                one <<= 1;
            }
            one = ~one;
            SetPixelG(image, x, y, GetPixelG(image, x, y) & one);
            one  = 1;
            for (i = 0; i < rbits - 1; i++)
            {
                SetPixelB(image, x, y, GetPixelB(image, x, y) | one);
                one <<= 1;
            }
            one = ~one;
            SetPixelB(image, x, y, GetPixelB(image, x, y) & one);
            one  = 1;
        }
    }

    return image;
}

/* add motion blur to the image */
IMAGE *MotionBlur(IMAGE *Image, int BlurAmount)
{
    int x,y,m;
    int temp_r , temp_g , temp_b;
    int H = ImageHeight(Image);
    int W = ImageWidth(Image);
    unsigned char R[W][H], G[W][H], B[W][H];
    for (x = 0; x < W; x++)
    {   for(y = 0; y < H; y++)
        {
            R[x][y] = GetPixelR(Image,x,y);
            G[x][y] = GetPixelG(Image,x,y);
            B[x][y] = GetPixelB(Image,x,y);
        }
    }
    for (x = 0; x < W; x++)
    {
        for (y = H - 1; y >= 0 ; y--)
        {
            int count = 0;
            temp_r = temp_g = temp_b = 0.0;
            for (m = 1; m<=BlurAmount ; m++)
            {
                //if ((x-m) >= 0)
                if((y-m) >= 0)
                {
                    temp_r += R[x][y-m];
                    temp_b += B[x][y-m];
                    temp_g += G[x][y-m];
                    count++;
                }
            }
            count = (count==0)?1:count;
            R[x][y] = temp_r / 2.0 / count + R[x][y] / 2.0;
            B[x][y] = temp_b / 2.0 / count + B[x][y] / 2.0;
            G[x][y] = temp_g / 2.0 / count + G[x][y] / 2.0;
            SetPixelR(Image,x,y,R[x][y]);
            SetPixelB(Image,x,y,B[x][y]);
            SetPixelG(Image,x,y,G[x][y]);
        }
    }
    return Image;
}
/* Enlarge the image */
IMAGE *Enlarge(IMAGE *image, int percentage) {
    assert(image);
    int i, j, m, n;
    double p = percentage / 100.00;
    int h = ImageHeight(image) * p;
    int w = ImageWidth(image) * p;
    int H = floor(h);
    int W = floor(w);
    IMAGE *size = NULL;
    size = CreateImage(W,H);
    while(percentage<100||percentage>200){
        printf("The number you enter is not between 100 - 200 !\n");
        printf("Please input again:");
        scanf("%d", &percentage);
    }
    if (percentage>100) {
        for (i = 0; i < W; i++) {
            for (j = 0; j < H; j++) {
                m = floor(i / p);
                n = floor(j / p);
                SetPixelR(size, i, j, GetPixelR(image, m, n));
                SetPixelG(size, i, j, GetPixelG(image, m, n));
                SetPixelB(size, i, j, GetPixelB(image, m, n));
            }
        }
        DeleteImage(image);
        return size;
    }
    else{
        DeleteImage(size);
        return image;
    }
}



/* Square the image*/
IMAGE *Square(IMAGE *image, int x_offset, int y_offset, int square_size)
{
    assert(image);
    int x, y;

    IMAGE *tmpImage = NULL;
    tmpImage = CreateImage(ImageWidth(image),ImageHeight(image));

    for (x = 0; x < ImageWidth(image) ; x++)
    {
        for (y = 0; y < ImageHeight(image) ; y++)
        {
            SetPixelR(tmpImage, x, y, GetPixelR(image, x, y));
            SetPixelG(tmpImage, x, y, GetPixelG(image, x, y));
            SetPixelB(tmpImage, x, y, GetPixelB(image, x, y));
        }
    }
    DeleteImage(image);
    image = CreateImage(square_size,square_size);
    for (x = 0; x <square_size ; x++)
    {
        for (y = 0; y < square_size; y++)
        {
            SetPixelR(image, x, y, GetPixelR(tmpImage, x + x_offset, y + y_offset));
            SetPixelG(image, x, y, GetPixelG(tmpImage, x + x_offset, y + y_offset));
            SetPixelB(image, x, y, GetPixelB(tmpImage, x + x_offset, y + y_offset));
        }
    }
    DeleteImage(tmpImage);
    return image;
}

IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast)
{
    assert(image);
    int x, y;
    double factor;
    int tmpR, tmpG, tmpB;

    factor = (double) (259 * (contrast + 255)) / (double) (255 * (259 - contrast));
    for (x = 0; x < ImageWidth(image); x++) {
        for (y = 0; y < ImageHeight(image); y++) {

            tmpR = (int)(factor * (GetPixelR(image, x, y)+brightness - 128) + 128);
            tmpG = (int)(factor * (GetPixelG(image, x, y)+brightness - 128) + 128);
            tmpB = (int)(factor * (GetPixelB(image, x, y)+brightness - 128) + 128);

            SetPixelR(image, x, y, (tmpR > 255)?255:(tmpR < 0)?0:tmpR);
            SetPixelG(image, x, y, (tmpG > 255)?255:(tmpG < 0)?0:tmpG);
            SetPixelB(image, x, y, (tmpB > 255)?255:(tmpB < 0)?0:tmpB);
        }
    }
    return image;
}


/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
