#include "Menu.h"
#include "AppDelegate.h"

using namespace cocos2d;

CCScene* Menu::scene(AppDelegate *appDelegate)
{
    /// Création de la scene.
    CCScene *scene = CCScene::create();
    
    /// Création de l'unique calque de la scene.
    Menu *layer = Menu::create();
	layer->setAppDelegate(appDelegate);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* labelName = CCLabelTTF::create("MenuScene", "Arial", 30 * ((int)winSize.height/720.0f));
	labelName->setPosition(ccp(winSize.width*0.9f, winSize.height*0.05f));
	layer->addChild(labelName);

    /// Ajout du calque à la scene.
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

    /// On désactive l'accelerometre et pn active le click pour cette scene.
    this->setAccelerometerEnabled(false);
    this->setTouchEnabled(true);

    /// On récupère la taille de l'écran.
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	_playItem = CCMenuItemFont::create("Jouer",
									   this,
									   menu_selector(Menu::menuCallback));
	_playItem->setFontSize(30 * ((int)winSize.height/720.0f));
	_playItem->setFontName("Arial");

	_closeItem = CCMenuItemFont::create("Quitter",
										this,
										menu_selector(Menu::menuCallback) );
	_closeItem->setFontSize(30 * ((int)winSize.height/720.0f));
	_closeItem->setFontName("Arial");
	
	CCMenu* playMenu = CCMenu::create(_playItem, NULL);
	playMenu->setPosition(winSize.width * 0.5f, winSize.height * 0.66f);
	CCMenu* closeMenu = CCMenu::create(_closeItem, NULL);
	closeMenu->setPosition(winSize.width * 0.5f, winSize.height * 0.33f);
	this->addChild(playMenu, 1);
	this->addChild(closeMenu, 1);

    return true;
}

void Menu::setAppDelegate(AppDelegate *appDelegate)
{
	_appDelegate = appDelegate;
}

void Menu::menuCallback(CCObject* sender)
{
	if(_playItem == (CCMenuItemFont*)sender)
		endScene(1);
	else
		endScene();
}

void Menu::endScene(int raise)
{
	if(_appDelegate != NULL)
		_appDelegate->changeScene(raise);
}
