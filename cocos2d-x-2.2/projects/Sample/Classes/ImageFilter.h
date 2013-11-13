//
//  ImageFilter.h
//  Sample
//
//  Created by tsuyoshi on 2013/11/04.
//  Copyright 2013 Tsuyoshi All rights reserved.
//

#ifndef __s2_image_filter__
#define __s2_image_filter__

NS_S2_BEGIN

void GaussianFilter(void *src, void *dest,  cocos2d::CCTexture2DPixelFormat format, int width, int height, int in_radius);

NS_S2_END

#endif /* __s2_gaussian_filter__ */
