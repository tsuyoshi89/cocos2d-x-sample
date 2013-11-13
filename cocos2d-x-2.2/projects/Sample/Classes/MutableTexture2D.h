//
//  MutableTexture_2d.h
//  Sample
//
//  Created by tsuyoshi on 2013/11/04.
//  Copyright 2013 Tsuyoshi All rights reserved.
//

#ifndef __mutable_texture_2d__
#define __mutable_texture_2d__

NS_S2_BEGIN

class MutableTexture2D : public cocos2d::CCTexture2D {
public:
    static MutableTexture2D *createWithImage(cocos2d::CCImage *image);
    
    virtual ~MutableTexture2D();
    
    CC_SYNTHESIZE_READONLY(void *, originalData_, OriginalTexData);
    CC_SYNTHESIZE(void *, data_, TexData);

    void apply();
    
    void restore();//back to original data;

    void blur(int radius);
    
    
private:
    MutableTexture2D();
    bool initWithImage(cocos2d::CCImage *image);

    void *_data;
    cocos2d::CCImage *_image;
};

NS_S2_END

#endif /* __mutable_texture_2d__ */
