//
//  MutableTexture2D.cpp
//  Sample
//
//  Created by tsuyoshi on 2013/11/04.
//  Copyright 2013 Tsuyoshi All rights reserved.
//

#include "MutableTexture2D.h"
#include "ImageFilter.h"

USING_NS_S2;
USING_NS_CC;

MutableTexture2D *MutableTexture2D::createWithImage(cocos2d::CCImage *image) {
    MutableTexture2D *ret = new MutableTexture2D();
    if (ret && ret->initWithImage(image)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return NULL;
}

MutableTexture2D::MutableTexture2D() : _data(NULL), _image(NULL) {
}

bool MutableTexture2D::initWithImage(CCImage *image) {
    if (CCTexture2D::initWithImage(image)) {
        if (getPixelFormat() == kCCTexture2DPixelFormat_RGBA8888) {
            CCLOG("pixels bits:%d", image->getBitsPerComponent());
            unsigned int dataLength = image->getWidth() * image->getHeight() * image->getBitsPerComponent() * 4;
            _data = malloc(dataLength);
            if (_data) {
                _image = image;
                _image->retain();
                return true;
            }
        }
    }
    CC_SAFE_FREE(_data);
    return false;
}

MutableTexture2D::~MutableTexture2D() {
    CC_SAFE_FREE(_data);
    CC_SAFE_RELEASE(_image);
}

void MutableTexture2D::restore() {
    if (_data == NULL) {
        return;
    }
	memcpy(_data, _image->getData(), _image->getWidth() * _image->getHeight() * _image->getBitsPerComponent() * 4);
	apply();
}

void MutableTexture2D::apply() {
	if(_data == NULL) {
        return;
    }
	
	glBindTexture(GL_TEXTURE_2D, getName());
	switch(getPixelFormat()) {
		case kTexture2DPixelFormat_RGBA8888:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, getPixelsWide(), getPixelsHigh(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);
			break;
		default:
            assert(false);
            break;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void MutableTexture2D::blur(int radius) {
	if(_data == NULL) {
        return;
    }
	
    GaussianFilter(_image->getData(),
                   _data,
                   getPixelFormat(),
                   _image->getWidth(),
                   _image->getHeight(),
                   radius);
	apply();
}

