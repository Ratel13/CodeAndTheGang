#include "AppDelegate.h"

#include "cocos2d.h"
#include "Intro.h"
#include "Menu.h"
#include "Game.h"

USING_NS_CC;

using namespace cocos2d;

AppDelegate::AppDelegate()
 : _indexScene(0)
{
	srand(time(NULL));
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // Création de la scène d'intro.
    _currentScene = Intro::scene(this);
	
    // run
    pDirector->runWithScene(_currentScene);
	
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::quitApplication()
{
	CCDirector::sharedDirector()->end();
}

void AppDelegate::changeScene(int indexRaise)
{
	_indexScene += indexRaise;

	CCScene *newScene = NULL;
	CCTransitionScene *transition = NULL;
	switch (_indexScene)
	{
	case 1:
		newScene = Menu::scene(this);
		transition = CCTransitionFade::create(0.5,newScene);
		break;
	case 2:
		newScene = Game::scene(this);
		transition = CCTransitionFade::create(0.5,newScene);
		break;
	default:
		quitApplication();
		break;
	}

	if(newScene)
	{
		CCDirector::sharedDirector()->replaceScene(transition);
		_currentScene = newScene;
	}
}

float AppDelegate::randomValueBetween(float low, float high) 
{
	return ((rand() / (float) RAND_MAX) * (high - low)) + low;
}