#include "Menu.h"
#include "AppDelegate.h"

using namespace cocos2d;

CCScene* Menu::scene(AppDelegate *appDelegate)
{
    /// Cr�ation de la scene.
    CCScene *scene = CCScene::create();
    
    /// Cr�ation de l'unique calque de la scene.
    Menu *layer = Menu::create();
	layer->setAppDelegate(appDelegate);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* labelName = CCLabelTTF::create("MenuScene", "Arial", 24);
	labelName->setPosition(ccp(winSize.width*0.9f, winSize.height*0.05f));
	layer->addChild(labelName);

    /// Ajout du calque � la scene.
    scene->addChild(layer);

    /// Retourne la scene.
    return scene;
}

// on "init" you need to initialize your instance
bool Menu::init()
{
	/// Appel de la classe parent.
    if ( !CCLayer::init() )
    {
        return false;
    }
	_appDelegate = NULL;

    /// On d�sactive l'accelerometre et pn active le click pour cette scene.
    this->setAccelerometerEnabled(false);
    this->setTouchEnabled(true);

    /// On r�cup�re la taille de l'�cran.
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	this->runAction(CCSequence::create(CCDelayTime::create(1.0f),
									   CCCallFunc::create(this, callfunc_selector(Menu::endScene)),
									   NULL));

    return true;
}

void Menu::setAppDelegate(AppDelegate *appDelegate)
{
	_appDelegate = appDelegate;
}

void Menu::endScene()
{
	if(_appDelegate != NULL)
		_appDelegate->changeScene(1);
}
