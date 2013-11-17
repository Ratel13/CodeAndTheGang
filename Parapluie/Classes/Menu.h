#ifndef __Menu_H__
#define __Menu_H__

#include "cocos2d.h"

USING_NS_CC;

class AppDelegate;

class Menu : public cocos2d::CCLayer
{
private:
	/// On garde en mémoire l'appDelegate qui permet de jouer avec les scenes.
	AppDelegate *_appDelegate;
	/// Menu
	CCMenuItemFont *_playItem;
	CCMenuItemFont *_closeItem;
    
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	void setAppDelegate(AppDelegate *appDelegate);

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene(AppDelegate *appDelegate);

    // implement the "static node()" method manually
    CREATE_FUNC(Menu);

	void menuCallback(CCObject* sender);
    
    /// Méthode appelé à la fin de la séquence.
    void endScene(int raise = -2);
};

#endif // __Menu_H__
