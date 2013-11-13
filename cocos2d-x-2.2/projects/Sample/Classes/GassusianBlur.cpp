//
//  GassusianBlur.cpp
//  Sample
//
//  Created by tsuyoshi on 2013/11/14.
//
//

#include "GassusianBlur.h"
#include "MutableTexture2D.h"

USING_NS_S2;
USING_NS_CC;

#pragma mark - GaussianBlur
GaussianBlur* GaussianBlur::create(float duration, int toRadius, int fromRadius) {
    GaussianBlur *pRet = new GaussianBlur();
    if (pRet && pRet->init(duration, toRadius, fromRadius)) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool GaussianBlur::init(float duration, int toRadius, int fromRadius) {
    if (CCActionInterval::initWithDuration(duration)) {
        _toRadius = toRadius;
        _fromRadius = fromRadius;
        _mutableTexture = NULL;
        _originalTexture = NULL;
        return true;
    }
    return false;
}

void GaussianBlur::update(float time) {
    if (!_mutableTexture) {
        return;
    }
    const int radius = (int) ((_toRadius - _fromRadius) * time  + _fromRadius + 0.5);
    if (_prevRadius != radius) {
        ((MutableTexture2D *)_mutableTexture)->blur(radius);
        _prevRadius = radius;
    }
}

static cocos2d::CCRenderTexture *createRenderTexture(cocos2d::CCTexture2D *texture, float scale) {
    const CCSize drawSize = CCSizeMake(texture->getContentSize().width * scale, texture->getContentSize().height * scale);
    CCRenderTexture *renderTexture = CCRenderTexture::create(drawSize.width, drawSize.height);
    renderTexture->begin();
#if 1
    texture->drawInRect(CCRectMake(0, 0, drawSize.width, drawSize.height));
#else
    CCPoint pos = sola2d::getMid(renderTexture->getSprite()->getTexture()->getContentSize());
    pSprite->setPosition(pos);
    pSprite->visit();
#endif
    renderTexture->end();
    renderTexture->getSprite()->getTexture()->setAntiAliasTexParameters();
    //renderTexture->setScale(1 / ratio);
    return renderTexture;
}


void GaussianBlur::startWithTarget(CCNode *pTarget) {
    CCSprite *sprite = dynamic_cast<CCSprite *>(pTarget);
    assert(sprite);
    CCActionInterval::startWithTarget(pTarget);
    if (_mutableTexture == NULL) {
        CCRenderTexture *renderTexture =  createRenderTexture(sprite->getTexture(), 1.0);
        CCImage *image = renderTexture->newCCImage();
        image->autorelease();
        MutableTexture2D *texture = MutableTexture2D::createWithImage(image);
        if (texture) {
            _mutableTexture = texture;
            _originalTexture = sprite->getTexture();
            _originalTexture->setAntiAliasTexParameters();
            _mutableTexture->setAntiAliasTexParameters();
            _originalTexture->retain();
            sprite->setTexture(_mutableTexture);
            _mutableTexture->retain();
        } else {
            CC_SAFE_DELETE(texture);
        }
    }
    _prevRadius = -1;
}

void GaussianBlur::stop(void) {
    // Action is done, reset clip position
    CCSprite *sprite = dynamic_cast<CCSprite *>(getTarget());
    assert(sprite);
    assert(_originalTexture);
    sprite->setTexture(_originalTexture);
    CCActionInterval::stop();
    
    CC_SAFE_RELEASE(_originalTexture);
    CC_SAFE_RELEASE(_mutableTexture);
}

