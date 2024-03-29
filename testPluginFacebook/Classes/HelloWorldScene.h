#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ProtocolSocial.h"
using namespace cocos2d;
using namespace cocos2d::plugin;

class HelloWorld : public CCLayer, public ResultListener
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
	virtual void onShareResult(ResultCode ret, const char* msg);
	virtual void onScoreResult(ResultCode ret, const char* msg);


    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

};

#endif // __HELLOWORLD_SCENE_H__
