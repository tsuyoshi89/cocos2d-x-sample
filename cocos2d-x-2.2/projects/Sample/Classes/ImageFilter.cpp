//
//  ImageFilter.cpp
//  Sample
//
//  Created by tsuyoshi on 2013/11/04.
//  Copyright 2013 Tsuyoshi All rights reserved.
//

#include "ccMacros.h"
#include "ImageFilter.h"

USING_NS_S2;
USING_NS_CC;

void s2::GaussianFilter(void *src, void *dest,  CCTexture2DPixelFormat format, int width, int height, int in_radius) {
    
	const int startPointX = 0;
    const int startPointY = 0;
    const int endPointX = startPointX + width;
    const int endPointY = startPointY + height;
	
    const int radius = MIN(MAX(0, in_radius), 248);
    const int diameter = 1 + radius * 2;
    float kernelf[diameter];

#if 1 /* gaussian */
    {
        float sigma = radius / 3.0f;
        float base = 1.0f / (2 * sigma * sigma);
        //Gaussian filter
        for (int k = 0; k < radius; k++) {
            float g = expf(-(radius - k) * (radius - k) * base);
            kernelf[k] = kernelf[diameter - k - 1] = g;
        }
        kernelf[radius] = 1;
    }
#elif defined(S2_BLUR_POT)
    {
        for (int k = 0; k < radius; k++) {
            int g = (k + 1) * (k + 1);
            kernelf[k] = kernelf[diameter - k - 1] = g;
        }
        kernelf[radius] = (radius + 1) * (radius + 1);
    }
#elif defined(S2_BLUR_LINER)
    {
        //Gaussian filter
        for (int i = 0; i < radius; i++) {
            int g = (i + 1);
            kernelf[i] = kernelf[diameter - i - 1] = g;
        }
        kernelf[radius] = (radius + 1);
    }
#endif
    
    //normailzation
    const int sum = 1024 * 8;
    int factors[diameter];
    {
        float sumf = 0;
        for (int k = 0; k < diameter; k++) {
            sumf += kernelf[k];
        }
        float factor = sum / sumf;
        for (int k = 0; k < diameter; k++) {
            //factors[k] = (int)roundf(kernelf[k] * factor);
            factors[k] = (int)floorf(kernelf[k] * factor);
        }
    }
    
	if (format == kTexture2DPixelFormat_RGBA8888) {
		const ccColor4B *srcData = (ccColor4B *)src;
		ccColor4B *destData = (ccColor4B *)dest;
		ccColor4B *temp = (ccColor4B *)malloc(width * height * sizeof(*destData));
        int cb, cg, cr, ca;
		
		//Horizontal blur
		for (int y = startPointY; y < endPointY; y++) {
            const int sy = y * width;
			for (int x = startPointX; x < endPointX; x++) {
                cb = cg = cr = ca = sum / 2;
				int rx = x - radius;
                const ccColor4B *pixel;
				for (int k = 0; k < diameter; k++){
					if ((rx + k) < 0) {
						pixel = &srcData[sy];
                    } else if ((rx + k) < width) {
                        pixel = &srcData[sy + rx + k];
                    } else {
                        pixel = &srcData[sy + width - 1];
                    }
					cr += pixel->r * factors[k];
					cg += pixel->g * factors[k];
					cb += pixel->b * factors[k];
					ca += pixel->a * factors[k];
				}
                ccColor4B *outPixel = &temp[sy + x];
				outPixel->r = cr / sum;
				outPixel->g = cg / sum;
				outPixel->b = cb / sum;
				outPixel->a = ca / sum;
			}
		}
        
		//Vertical blur
        for (int x = startPointX; x < endPointX; x++) {
            for (int y = startPointY; y < endPointY; y++) {
                cb = cg = cr = ca = sum / 2;
                int ry = y - radius;
                const ccColor4B *pixel;
				for (int k = 0; k < diameter; k++) {
					if ((ry + k) < startPointY) {
                        pixel = &temp[startPointY * width + x];
                    } else if ((ry + k) < endPointY) {
						pixel = &temp[(ry + k) * width + x];
                    } else {
						pixel = &temp[(endPointY - 1) * width + x];
                    }
					cr += pixel->r * factors[k];
					cg += pixel->g * factors[k];
					cb += pixel->b * factors[k];
					ca += pixel->a * factors[k];
				}
				ccColor4B *outPixel = &destData[y * width + x];
				outPixel->r = cr / sum;
				outPixel->g = cg / sum;
				outPixel->b = cb / sum;
				outPixel->a = ca / sum;
			}
        }
		
		CC_SAFE_FREE(temp);
	} else {
        CCLOG("pixel format  don't supported. %d", format);
    }
}

