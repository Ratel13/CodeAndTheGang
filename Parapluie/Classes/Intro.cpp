#include "Intro.h"
#include "AppDelegate.h"

using namespace cocos2d;

CCScene* Intro::scene(AppDelegate *appDelegate)
{
    /// Cr�ation de la scene.
    CCScene *scene = CCScene::create();
    
    /// Cr�ation de l'unique calque de la scene.
    Intro *layer = Intro::create();
	layer->setAppDelegate(appDelegate);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* labelName = CCLabelTTF::create("IntoScene", "Arial", 30 * ((int)winSize.height/720.0f));
	labelName->setPosition(ccp(winSize.width*0.9f, winSize.height*0.05f));
	layer->addChild(labelName);

    /// Ajout du calque � la scene.
    scene->addChild(layer);

    /// Retourne la scene.
    return scene;
}

// on "init" you need to initialize your instance
bool Intro::init()
{
	/// Appel de la classe parent.
    if ( !CCLayer::init() )
    {
        return false;
    }

    /// On d�sactive l'accelerometre et la click pour cette scene.
    this->setAccelerometerEnabled(false);
    this->setTouchEnabled(false);

    /// On r�cup�re la taille de l'�cran.
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    /// On charge le logo et le nom.
    _logo = CCSprite::create("logoIntroScene.png");
    _name = CCSprite::create("nameIntroScene.png");

    /// On les place sur l'�cran.
	_logo->setScale(winSize.width * 0.5f / _logo->getContentSize().width);
    _logo->setPosition(ccp(-500, -500));
	_name->setScale(winSize.width / _name->getContentSize().width);
    _name->setPosition(ccp(-500, -500));

	/// On ajoute les images au layer et on les masque.
	this->addChild(_logo, 0);
	this->addChild(_name, 0);

	/// On cr�� et on ajoute les s�quences d'animations pour les deux images.	
	_logo->runAction(CCSequence::create(CCFadeOut::create(0.0f),
										CCMoveTo::create(0,ccp(winSize.width * 0.5f, winSize.height * 0.63f)),
										CCDelayTime::create(0.5f),
										CCFadeIn::create(2.0f),
										NULL));
	_name->runAction(CCSequence::create(CCFadeOut::create(0.0f),
										CCMoveTo::create(0,ccp(winSize.width * 0.5f, winSize.height * 0.25f)),
										CCDelayTime::create(2.5f),
										CCFadeIn::create(2.0f),
										CCDelayTime::create(1.0f),
										CCCallFunc::create(this, callfunc_selector(Intro::endScene)),
									    NULL));

    return true;
}

void Intro::setAppDelegate(AppDelegate *appDelegate)
{
	_appDelegate = appDelegate;
}

void Intro::endScene()
{
	if(_appDelegate != NULL)
		_appDelegate->changeScene(1);
}
