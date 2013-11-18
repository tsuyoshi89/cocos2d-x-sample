//
//  ResizeAction.cpp
//  Sample
//
//  Created by tsuyoshi on 2013/11/18.
//
//

#include "ResizeAction.h"

USING_NS_S2;
USING_NS_CC;

ResizeAction* ResizeAction::create(float duration, const CCSize &to, const CCSize &from) {
    ResizeAction *pRet = new ResizeAction();
    if (pRet && pRet->init(duration, to, from)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool ResizeAction::init(float duration, const CCSize &to, const CCSize &from) {
    if (CCActionInterval::initWithDuration(duration)) {
        _to = to;
        _from = from;
        return true;
    }
    return false;
}

void ResizeAction::update(float time) {
    const float width = (_to.width - _from.width) * time + _from.width;
    const float height = (_to.height - _from.height) * time + _from.height;

    CCArray *children = getTarget()->getChildren();
    CCObject *obj;
    CCARRAY_FOREACH(children, obj) {
        CCNode *node = (CCNode *)obj;
        float x = node->getPositionX() / getTarget()->getContentSize().width;
        float y = node->getPositionY() / getTarget()->getContentSize().height;
        node->setPosition(ccp(x * width, y * height));
    }

    getTarget()->setContentSize(CCSizeMake(width, height));
}

void ResizeAction::startWithTarget(CCNode *pTarget) {
    CCActionInterval::startWithTarget(pTarget);
    

}

void ResizeAction::stop(void) {
    CCActionInterval::stop();
}

