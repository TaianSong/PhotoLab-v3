#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_

#include "Constants.h"
#include "Image.h"

/* add noise to an image */
IMAGE *Noise (IMAGE *image, int n );

/* posterize the image */
IMAGE *Posterize (IMAGE *image, int rbits, int gbits, int bbits);

/* motion blur */
IMAGE *MotionBlur (IMAGE *image, int blur_amount);

/* Enlarge the image */
IMAGE *Enlarge(IMAGE *image, int enlarge_percentage);

/* Square the image*/
IMAGE *Square(IMAGE *image, int x_offset, int y_offset, int square_size);

/* BrightnessAndContrast the image*/
IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast);

#endif /* ADVANCED_H_INCLUDED_ */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
