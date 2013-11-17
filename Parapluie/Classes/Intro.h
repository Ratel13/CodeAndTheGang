#ifndef __Intro_H__
#define __Intro_H__

#include "cocos2d.h"

USING_NS_CC;

class AppDelegate;

class Intro : public cocos2d::CCLayer
{
private:
	/// Logo afficher lors de la scene d'intro.
	cocos2d::CCSprite * _logo;
	/// Nom afficher lors de la scene d'intro.
	cocos2d::CCSprite * _name;
	/// On garde en mémoire l'appDelegate qui permet de jouer avec les scenes.
	AppDelegate *_appDelegate;
    
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	void setAppDelegate(AppDelegate *appDelegate);

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene(AppDelegate *appDelegate);

    // implement the "static node()" method manually
    CREATE_FUNC(Intro);
    
    /// Méthode appelé à la fin de la séquence.
    void endScene();
};

#endif // __Intro_H__
