//
//  ResizeAction.h
//  Sample
//
//  Created by tsuyoshi on 2013/11/18.
//
//

#ifndef __Sample__ResizeAction__
#define __Sample__ResizeAction__

NS_S2_BEGIN

class ResizeAction : public cocos2d::CCActionInterval {
public:
    static ResizeAction* create(float duration, const cocos2d::CCSize &to, const cocos2d::CCSize &from);
    virtual void startWithTarget(cocos2d::CCNode *node);
    virtual void update(float t);
    virtual void stop(void);
    
protected:
    bool init(float duration, const cocos2d::CCSize &to, const cocos2d::CCSize &from);
    
    cocos2d::CCSize _to;
    cocos2d::CCSize _from;
};

NS_S2_END

#endif /* defined(__Sample__ResizeAction__) */
