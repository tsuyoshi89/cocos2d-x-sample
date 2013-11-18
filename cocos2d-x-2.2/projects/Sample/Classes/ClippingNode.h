//
//  s2_clipping_node.h
//  Sample
//
//  Created by tsuyoshi on 2013/10/29.
//
//

#ifndef __ss_clipping_node__
#define __s2_clipping_node__

NS_S2_BEGIN

class ClippingNode : public cocos2d::CCNode {
public:
    typedef cocos2d::CCNode super;
    
    static ClippingNode *create();
    
    virtual void visit();
};

NS_S2_END

#endif /* defined(__s2_clipping_node__) */
