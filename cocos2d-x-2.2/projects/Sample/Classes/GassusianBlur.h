//
//  GassusianBlur.h
//  Sample
//
//  Created by tsuyoshi on 2013/11/14.
//
//

#ifndef __Sample__GassusianBlur__
#define __Sample__GassusianBlur__

NS_S2_BEGIN

class GaussianBlur : public cocos2d::CCActionInterval {
public:
    //create with effect radius
    static GaussianBlur* create(float duration, int toRadius, int fromRadius);
    
    
    virtual void startWithTarget(cocos2d::CCNode *node);
    virtual void update(float t);
    virtual void stop(void);
    
protected:
    bool init(float duration, int toRadius, int fromRadius);
    void _reset();
    
    int _fromRadius;
    int _toRadius;
    int _prevRadius;
    cocos2d::CCTexture2D *_mutableTexture;
    cocos2d::CCTexture2D *_originalTexture;
};

NS_S2_END


#endif /* defined(__Sample__GassusianBlur__) */
