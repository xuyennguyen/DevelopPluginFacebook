#include "FacebookManager.h"
#include "PluginManager.h"
#include "cocos2d.h"
#include <string.h>

using namespace cocos2d::plugin;
using namespace cocos2d;


FacebookManager* FacebookManager::s_pManager = NULL;
FacebookManager::FacebookManager()
: s_pRetListener(NULL)
, s_pFacebook(NULL)
{

}

FacebookManager::~FacebookManager()
{
	unloadSocialPlugin();
	if (s_pRetListener)
	{
		delete s_pRetListener;
		s_pRetListener = NULL;
	}
}

FacebookManager* FacebookManager::sharedSocialManager()
{
	if (s_pManager == NULL) {
		s_pManager = new FacebookManager();
	}
	return s_pManager;
}

void FacebookManager::purgeManager()
{
	if (s_pManager)
	{
		delete s_pManager;
		s_pManager = NULL;
	}
	PluginManager::end();
}

void FacebookManager::loadSocialPlugin()
{
	CCLog("goi den ham loadsocialPlugin 1");
	if (s_pRetListener == NULL)
	{
		s_pRetListener = new MyShareResult();
	}

		// init Facebook plugin
	if (s_pFacebook == NULL){
		CCLog("Goi den onShareResult 1");
		s_pFacebook = dynamic_cast<ProtocolSocial*>(PluginManager::getInstance()->loadPlugin("SocialFacebook"));
	}
	if ( s_pFacebook == NULL )
	{
		CCLog("s_pFacebook is null");
	}
	else {
		CCLog("s_pFacebook not null");
	}
		{
			TSocialDeveloperInfo pFacebookInfo;
			 pFacebookInfo["FacebookSecret"] = "5f9ea40176c5f9fdf2b9ee7f78f68288";
			 pFacebookInfo["FacebookKey"] = "1482671565281830";
			 pFacebookInfo["NameSpace"] = "socialleaderboard";
			if (pFacebookInfo.empty())
			{
				char msg[256] = { 0 };
				sprintf(msg, "Developer info is empty. PLZ fill your twitter info in %s(nearby line %d)", __FILE__, __LINE__);
				CCMessageBox(msg, "Facebook Warning");
			}
			CCLog("sau khi load xong plugin 2");
			s_pFacebook->setDebugMode(true);
			s_pFacebook->configDeveloperInfo(pFacebookInfo);
			s_pFacebook->setResultListener(s_pRetListener);
		}
}

void FacebookManager::unloadSocialPlugin()
{
	if (s_pFacebook)
	{
		PluginManager::getInstance()->unloadPlugin("SocialFacebook");
		s_pFacebook = NULL;
	}
}

void FacebookManager::shareByMode(TShareInfo info)
{
	if (s_pRetListener == NULL)
	{
	s_pRetListener = new MyShareResult();
	}

	ProtocolSocial* pShare = NULL;
	pShare = s_pFacebook;
	if (pShare) {
		pShare->share(info);

	}

}
void MyShareResult::onShareResult(ResultCode ret, const char* msg)
{
	CCLog("Goi den onShareResult");
	char shareStatus[1024] = { 0 };
	sprintf(shareStatus, "Share %s", (ret == kResultSuccess)? "Successed" : "Failed");
	int value =  0;
    if ( ret ==  kResultSuccess){
    	value = 0 ; // thanh cong
    }
    else if ( ret == kResultFail){
    	value = 1;
    }
    else if ( ret == kResultCancel){
    	value = 2;
    }
    else if ( ret== kResultTimeOut ){
    	value = 3;
    }
    else if ( ret == kResultNetWork){
    	value = 4;
    }
    CCUserDefault::sharedUserDefault()->setIntegerForKey("mCode",value);
    CCUserDefault::sharedUserDefault()->flush();

    m_pLister->onShareResult(ret, msg );
}
void FacebookManager::setListener(ResultListener *listener){
	this->s_pRetListener->setListener(listener);
}
void MyShareResult::setListener( ResultListener *listener){
	m_pLister = listener;
}

void MyShareResult::onScoreResult(cocos2d::plugin::ResultCode ret, const char* msg){
}

