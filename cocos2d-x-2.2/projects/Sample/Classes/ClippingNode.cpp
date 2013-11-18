//
//  s2_clipped_node.cpp
//  Sample
//
//  Created by tsuyoshi on 2013/10/29.
//
//

#include "ClippingNode.h"


USING_NS_S2;
USING_NS_CC;

static cocos2d::CCRect convertToWorldSpace(cocos2d::CCNode *node, const cocos2d::CCRect &r) {
    CCPoint leftBottom = r.origin;
    CCPoint rightTop = leftBottom + r.size;
    
    leftBottom = node->convertToWorldSpace(leftBottom);
    rightTop = node->convertToWorldSpace(rightTop);
    
    return CCRectMake(leftBottom.x, leftBottom.y, rightTop.x - leftBottom.x, rightTop.y - leftBottom.y);
}


ClippingNode *ClippingNode::create() {
    ClippingNode *ret = new ClippingNode();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_RELEASE(ret);
    return NULL;
}

void ClippingNode::visit() {
    CCRect bounds = CCRectMake(0, 0, this->getContentSize().width, this->getContentSize().height);
    bounds = ::convertToWorldSpace(this, bounds);

    //kmGLPushMatrix();
    glEnable(GL_SCISSOR_TEST);
    CCEGLView::sharedOpenGLView()->setScissorInPoints(bounds.getMinX(), bounds.getMinY(), bounds.size.width, bounds.size.height);
    super::visit();
    glDisable(GL_SCISSOR_TEST);
    //kmGLPopMatrix();
}
