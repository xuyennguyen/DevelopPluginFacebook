/*
 * MyFacebookManager.h
 *
 *  Created on: Feb 13, 2014
 *      Author: Xuyen
 */

#ifndef FACEBOOKMANAGER_H_
#define FACEBOOKMANAGER_H_

#include "ProtocolSocial.h"

class MyShareResult : public cocos2d::plugin::ResultListener
{
public:
	void setListener( ResultListener *listener);
	virtual void onShareResult(cocos2d::plugin::ResultCode ret, const char* msg);
	virtual void onScoreResult(cocos2d::plugin::ResultCode ret, const char* msg);

private:
	ResultListener *m_pLister;
};

class FacebookManager
{
public:
	static FacebookManager* sharedSocialManager();
    static void purgeManager();
	void unloadSocialPlugin();
    void loadSocialPlugin();
    void shareByMode(cocos2d::plugin::TShareInfo info);
    void onResumeActivity();
    void setListener( cocos2d::plugin::ResultListener  *listener);

private:
    FacebookManager();
    virtual ~FacebookManager();

    static FacebookManager* s_pManager;

    cocos2d::plugin::ProtocolSocial* s_pFacebook;
    MyShareResult* s_pRetListener;

};

#endif /* MYFACEBOOKMANAGER_H_ */
