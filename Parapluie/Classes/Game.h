#ifndef __Game_H__
#define __Game_H__

#include "cocos2d.h"

USING_NS_CC;

class AppDelegate;

class Game : public cocos2d::CCLayer
{
private:
	/// On garde en mémoire l'appDelegate qui permet de jouer avec les scenes.
	AppDelegate *_appDelegate;
	/// Scale pour les sprites.
	float _scaleSprite;
	/// Sprite de ryu.
	CCSprite *_spriteRyu;
	///  Animation lors du shoot
	CCAnimation *_animationShoot;
	CCAnimate *_actionShoot;
	/// Animation de base de ryu
	CCAnimation *_animationBase;
	CCAnimate *_actionBase;
	/// Data accelerometre
	float _accelerationPerSecY;
	/// true is shooting
	bool _shoot;
	/// Projections
	CCArray* _projections;
	int _projectionsIndex;
	/// Enemis
	CCArray* _enemis;
	int _enemisIndex;
	double _vitesseEnemi;
	/// Gestion spawn
	float _startTimeInMillis;
    float _nextEnemisSpawn;
	/// Animation du projectile.
	CCAnimation *_animationProj;
	CCAnimate *_actionProj;
	/// Gestion vie.
	int _life;
	CCArray* _lifeSprites;

	CCLabelTTF *labelName;
    
    // scheduled Update
    void update(float dt);
	void makeProjectile();
	void removeLife();

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	void setAppDelegate(AppDelegate *appDelegate);

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene(AppDelegate *appDelegate);

    // implement the "static node()" method manually
    CREATE_FUNC(Game);
	
	/// Accéléromètre.
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);

	virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	void endShoot();
	void windowsKeyTest();
	void keyBackClicked();
    
    /// Méthode appelé à la fin de la séquence.
    void endScene();
};

#endif // __Game_H__
