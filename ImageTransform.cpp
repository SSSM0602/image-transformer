#include <iostream>
#include <cmath>
#include <cstdlib>

#include "uiuc/PNG.h"
#include "uiuc/HSLAPixel.h"
#include "ImageTransform.h"

/* ******************
(Begin multi-line comment...)

Write your name and email address in the comment space here:

Name:
Email:

(...end multi-line comment.)
******************** */

using uiuc::PNG;
using uiuc::HSLAPixel;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a reference to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly. No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 * 
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {
  for (unsigned int y = 0; y < image.height(); y++) {
        for (unsigned int x = 0; x < image.width(); x++) {
            // Calculate the Euclidean distance from the center
            int dx = x - centerX;
            int dy = y - centerY;
            double distance = std::sqrt(dx * dx + dy * dy);

            // Calculate the luminance adjustment
            double adjustment = std::min(0.8, 0.005 * distance);

            // Adjust the pixel luminance
            HSLAPixel & pixel = image.getPixel(x, y);
            pixel.l = pixel.l * (1.0 - adjustment);
        }
    }
  return image;
  
}
 

/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {
  // Define the hue values for Illini colors
    const double orangeHue = 11;
    const double blueHue = 216;

    // Iterate through each pixel in the image
    for (unsigned int y = 0; y < image.height(); y++) {
        for (unsigned int x = 0; x < image.width(); x++) {
            HSLAPixel & pixel = image.getPixel(x, y);

            // Calculate the distance to Illini orange and blue
            double distToOrange = std::min(std::abs(pixel.h - orangeHue), 360 - std::abs(pixel.h - orangeHue));
            double distToBlue = std::min(std::abs(pixel.h - blueHue), 360 - std::abs(pixel.h - blueHue));

            // Set the hue to the closest Illini color
            if (distToOrange < distToBlue) {
                pixel.h = orangeHue;
            } else {
                pixel.h = blueHue;
            }
        }
    }

  return image;
}
 

/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs, which is the base image.
* @param secondImage The second of the two PNGs, which acts as the stencil.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {
  // Ensure both images are of the same dimensions
    if (firstImage.width() != secondImage.width() || firstImage.height() != secondImage.height()) {
        // Handle the error (throw exception, return an unmodified image, etc.)
        return firstImage;
    }

    // Iterate through each pixel of both images
    for (unsigned int y = 0; y < secondImage.height(); y++) {
        for (unsigned int x = 0; x < secondImage.width(); x++) {
            HSLAPixel & basePixel = firstImage.getPixel(x, y);
            HSLAPixel & stencilPixel = secondImage.getPixel(x, y);

            // Check if the luminance of the stencil pixel is 1
            if (stencilPixel.l == 1.0) {
                // Increase the luminance of the base image pixel by 0.2, capped at 1.0
                basePixel.l = std::min(1.0, basePixel.l + 0.2);
            }
        }
    }
  return firstImage;
}
