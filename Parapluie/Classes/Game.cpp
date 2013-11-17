#include "Game.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

#define COCOS2D_DEBUG 1

using namespace cocos2d;

CCScene* Game::scene(AppDelegate *appDelegate)
{
    /// Création de la scene.
    CCScene *scene = CCScene::create();
    
    /// Création de l'unique calque de la scene.
    Game *layer = Game::create();
	layer->setAppDelegate(appDelegate);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* labelName = CCLabelTTF::create("GameScene", "Arial", 30 * ((int)winSize.height/720.0f));
	labelName->setPosition(ccp(winSize.width*0.9f, winSize.height*0.05f));
	layer->addChild(labelName);

    /// Ajout du calque à la scene.
    scene->addChild(layer);

    /// Retourne la scene.
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
	/// Appel de la classe parent.
    if ( !CCLayer::init() )
    {
        return false;
    }
	_accelerationPerSecY = 0.0f;
	_shoot = false;
	_projectionsIndex = 0;
	_enemisIndex = 0;
	_startTimeInMillis = 0.0f;
	_nextEnemisSpawn = 0.0f;
	_life = 5;
	_vitesseEnemi = 5.0;
	_labelPoints = NULL;
	_points = 0;
	_explosionsIndex = 0;

    /// On active l'accelerometre, le click et l'appel à update.
    this->setAccelerometerEnabled(true);
	this->scheduleUpdate();
	this->setKeypadEnabled(true);

    /// On récupère la taille de l'écran.
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	/// On garde ne mémoire le ratio.
	_scaleSprite = winSize.height/720.0f;

	CCSprite *background = CCSprite::create("background.png");
	background->setPosition(ccp(winSize.width * 0.5f,winSize.height * 0.5f));
	background->setScale(_scaleSprite);
	this->addChild(background);
 
	_spriteRyu = CCSprite::create("ryuShoot1.png");
	_spriteRyu->setPosition(ccp(winSize.width * 0.05f, winSize.height * 0.5f));
	_spriteRyu->setScale(_scaleSprite);
	this->addChild(_spriteRyu);

	char str[20] = {0};
	
	/// Animation de base.
	_animationBase = CCAnimation::create();
	_animationBase->retain();

	for (int i = 1; i < 5; i++)
	{
		sprintf(str, "ryuStand%d.png", i);
		_animationBase->addSpriteFrameWithFileName(str);  
	}

	_animationBase->setDelayPerUnit(.1f);
	_animationBase->setRestoreOriginalFrame(true);

	/// Animation de tir;
	_animationShoot = CCAnimation::create();
	_animationShoot->retain();
 
	for (int i = 1; i < 5; i++)
	{
		sprintf(str, "ryuShoot%d.png", i);
		_animationShoot->addSpriteFrameWithFileName(str);  
	}

	_animationShoot->setDelayPerUnit(.1f);

	/// Animation du projectile.
	_animationProj = CCAnimation::create();
	_animationProj->retain();

	_animationProj->addSpriteFrameWithFileName("proj1.png"); 
	_animationProj->addSpriteFrameWithFileName("proj2.png");  

	_animationProj->setDelayPerUnit(.1f);
	_animationProj->setRestoreOriginalFrame(true);

	/// Animation du explosion.
	_animationExplosion = CCAnimation::create();
	_animationExplosion->retain();

	for (int i = 1; i < 6; i++)
	{
		sprintf(str, "explosion%d.png", i);
		_animationExplosion->addSpriteFrameWithFileName(str);  
	}
	_animationExplosion->addSpriteFrameWithFileName("emptyPix.png");

	_animationExplosion->setDelayPerUnit(.1f);

	/// On remplit les pool.
    _enemis = new CCArray();
    for(int i = 0; i < 10; ++i) 
	{
		CCSprite *enemi = CCSprite::create("chaliezu.png");
		enemi->setScale(_scaleSprite);
        enemi->setVisible(false);
        this->addChild(enemi);
        _enemis->addObject(enemi);
    }
    
	_projections = new CCArray();
    for(int i = 0; i < 10; ++i) 
	{
        CCSprite *proj = CCSprite::create("proj1.png");
		proj->setScale(_scaleSprite);
        proj->setVisible(false);
        this->addChild(proj);
		_projections->addObject(proj);
    }
    
	_explosions = new CCArray();
    for(int i = 0; i < 10; ++i) 
	{
        CCSprite *explo = CCSprite::create("explosion1.png");
		explo->setScale(_scaleSprite);
        explo->setVisible(false);
        this->addChild(explo);
		_explosions->addObject(explo);
    }

	/// On dessine les vies
	_lifeSprites = new CCArray();
	int posX = 5;
	float posY = winSize.height - 5;

	for(unsigned i = 0 ; i < _life ; ++i)
	{
		CCSprite *lifeSprite = CCSprite::create("life.png");
		float width = lifeSprite->getContentSize().width * _scaleSprite;
		float height = lifeSprite->getContentSize().height * _scaleSprite;
		lifeSprite->setScale(_scaleSprite);
		lifeSprite->setPosition(ccp(posX + width / 2, posY - height / 2));
		this->addChild(lifeSprite, 1);
		_lifeSprites->addObject(lifeSprite);
		posX = posX + width;
	}

	/// On ajoute le label pour les points.
	_labelPoints = CCLabelTTF::create();
	_labelPoints->setPosition(ccp(winSize.width * 0.9f, ((CCSprite *)_lifeSprites->objectAtIndex(0))->getPositionY()));
	this->addChild(_labelPoints);

	/// On lance l'animation de base
	_spriteRyu->runAction(CCRepeatForever::create(CCAnimate::create(_animationBase)));
    
	/// On préload le son et on joue le background.
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic(".wav", true); 
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("hadouken.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("explosion.wav");

    this->setTouchEnabled(true);

	return true;
}

void Game::setAppDelegate(AppDelegate *appDelegate)
{
	_appDelegate = appDelegate;
}

void Game::keyBackClicked()
{
	endScene();
}

void Game::didAccelerate(CCAcceleration* pAccelerationValue)
{    
    /// On récupère la taille de l'écran.
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	#define FILTER_FACTOR 0.1f /// Marge de manoeuvre.
	#define EQUILIBRAGE_X 0.6f /// -> Valeur de l'accelerometre pour avoir le perso au milieu.
    #define MAX_DPL_PAR_SEC (winSize.height*0.5f) /// Vitesse du déplacement
    #define RATIO_DIFF_X 0.2f

    // Cocos2DX inverts X and Y accelerometer depending on device orientation
    // in landscape mode right x=-y and y=x !!! (Strange and confusing choice)
    float rollingX = (pAccelerationValue->y * FILTER_FACTOR);
    _accelerationPerSecY = MAX_DPL_PAR_SEC * ( ( pAccelerationValue->y - rollingX ) + EQUILIBRAGE_X ) / RATIO_DIFF_X;
}

void Game::update(float dt) 
{    
	#if ! CC_TARGET_PLATFORM && CC_TARGET_WIN32
		windowsKeyTest();
	#endif

	///---------------- Update Player Position ------------------///
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float maxY = winSize.height * 0.85f /*- _spriteRyu->getContentSize().height/2*/;
    float minY = _spriteRyu->getContentSize().height/2;
    float newY = _spriteRyu->getPosition().y + _accelerationPerSecY * dt;
    newY = MIN(MAX(newY, minY), maxY);
    _spriteRyu->setPosition(ccp(_spriteRyu->getPosition().x, newY));
	///---------------- Update Player Position ------------------///
	
	///------------------- Collisions test ----------------------///
    CCObject* enemy;
	CCSprite* enemySprite;
    CCObject* projection;
	CCSprite* projectionSprite;
    CCARRAY_FOREACH(_enemis, enemy)
	{
		enemySprite = ((CCSprite *) enemy);
        if (!enemySprite->isVisible() )
            continue;
		/// On teste la collision avec les projections.
        CCARRAY_FOREACH(_projections, projection)
		{
			projectionSprite = ((CCSprite *) projection);
            if (!projectionSprite->isVisible())
                continue;
			if(projectionSprite->getPositionX() > winSize.width)
			{
				projectionSprite->setVisible(false);
			}
			else if (projectionSprite->boundingBox().intersectsRect(enemySprite->boundingBox()) ) 
			{
				///------------------- Creating explosion ----------------------///
				CCSprite *explo = (CCSprite *)_explosions->objectAtIndex(_explosionsIndex);
				explo->setVisible(true);
				if (++_explosionsIndex >= _explosions->count())
					_explosionsIndex = 0;
				explo->setPosition(enemySprite->getPosition());
				explo->runAction(CCAnimate::create(_animationExplosion));
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explosion.wav"); 
				///------------------- Creating explosion ----------------------///
                projectionSprite->setVisible(false);
                enemySprite->setVisible(false);
				_points += 500;
				enemySprite->stopAllActions();
                continue;
            }
        }
		/// On teste la collision avec le joueur.
		if (_spriteRyu->boundingBox().intersectsRect(enemySprite->boundingBox()) ) 
		{
            enemySprite->setVisible(false);
			removeLife();
			_spriteRyu->runAction(CCSequence::create(CCFadeOut::create(0.0f),
													 CCDelayTime::create(0.05f),
													 CCFadeIn::create(0.0f),
													 CCDelayTime::create(0.05f),
													 CCFadeOut::create(0.0f),
													 CCDelayTime::create(0.05f),
													 CCFadeIn::create(0.0f),
													 NULL));
        }
    }
	///------------------- Collisions test ----------------------///
	
	///------------------- Creating enemie ----------------------///
	_startTimeInMillis += dt;
	if(_vitesseEnemi > 1.0)
	{
		_vitesseEnemi -= dt / 10;
	}
	if(_startTimeInMillis > _nextEnemisSpawn)
	{
        float vitesseApparition = _vitesseEnemi / 5.0f;
		_nextEnemisSpawn = AppDelegate::randomValueBetween(1.0f * vitesseApparition, 2.0f * vitesseApparition) + _startTimeInMillis;
        
		CCSprite *enemy = (CCSprite *)_enemis->objectAtIndex(_enemisIndex);
        
		float randY = AppDelegate::randomValueBetween(enemy->getContentSize().height / 2 ,winSize.height * 0.85);
        
		if (++_enemisIndex >= _enemis->count())
            _enemisIndex = 0;
        
		float positionX = winSize.width + enemy->getContentSize().width;
		enemy->stopAllActions();
		enemy->setPosition(ccp(positionX, randY));
        enemy->setVisible(true);
        enemy->runAction(CCSequence::create(CCMoveBy::create(_vitesseEnemi, ccp(-(positionX + enemy->getContentSize().width), 0)),
											NULL));        
    }
	///------------------- Creating enemie ----------------------///
	
	///------------------- Points gestion -----------------------///
	_points += dt * 100;
	char text[20] = {0};
	CCPoint positionPoints = _labelPoints->getPosition();
	this->removeChild(_labelPoints);
	sprintf(text, "%d pts", (int)_points);
	_labelPoints = CCLabelTTF::create(text, "Arial", 30 * _scaleSprite);
	_labelPoints->setPosition(positionPoints);
	this->addChild(_labelPoints);
	///------------------- Points gestion -----------------------///
}

void Game::windowsKeyTest()
{

}

void Game::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
	if(!_shoot)
	{
		_shoot = true;
		/// On arrete l'action de base.
		_spriteRyu->stopAllActions();
		
		/// Animation de tir.
		_spriteRyu->runAction(CCSequence::create(CCFadeIn::create(0),
												 CCAnimate::create(_animationShoot),
												 CCCallFunc::create(this, callfunc_selector(Game::endShoot)),
												 NULL));
		// cpp with cocos2d-x
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hadouken.wav");   
	}
}

void Game::makeProjectile()
{
	CCSprite *projectile = (CCSprite *)_projections->objectAtIndex(_projectionsIndex);
        
	if (++_projectionsIndex >= _projections->count())
        _projectionsIndex = 0;

	projectile->stopAllActions();
	projectile->runAction(CCRepeatForever::create(CCAnimate::create(_animationProj)));
	projectile->setPosition(ccp(_spriteRyu->getPositionX(), _spriteRyu->getPositionY()));
    projectile->setVisible(true);
	projectile->runAction(CCSequence::create(CCMoveTo::create(1.5f, ccp(CCDirector::sharedDirector()->getWinSize().width + projectile->getContentSize().width, _spriteRyu->getPositionY())),
											 NULL));        
}

void Game::removeLife()
{
	--_life;
	CCSprite *lifeSprite = (CCSprite*)_lifeSprites->objectAtIndex(_life); 
	CCPoint position = lifeSprite->getPosition();
	this->removeChild(lifeSprite);
	lifeSprite->release();

	CCSprite *nolifeSprite = CCSprite::create("nolife.png");
	nolifeSprite->setScale(_scaleSprite);
	nolifeSprite->setPosition(position);
	this->addChild(nolifeSprite, 1);
	_lifeSprites->insertObject(nolifeSprite, _life);
	
	if(_life == 0)
	{
		endScene();
	}
}

void Game::endShoot()
{
	/// On remet l'action de base.
	_spriteRyu->stopAllActions();
	_spriteRyu->runAction(CCRepeatForever::create(CCAnimate::create(_animationBase)));

	_shoot = false;

	this->makeProjectile();
}

void Game::endScene()
{
	this->unscheduleUpdate();
	if(_appDelegate != NULL)
		_appDelegate->changeScene(1);
}
