//
//  mainController.h
//  eristoffGameConsole
//
//  Created by Kris Meeusen on 20/09/12.
//
//

#import "npDLRenderer.h"
#import "npBitmapSprite.h"
#import "npTweener.h"
#import "ImageDataLoader.h"
#import "OscSender.h"
#import "OscListener.h"
#import "AppConstants.h"
#import <CoreMotion/CoreMotion.h>
#import "cinder/Vector.h"
#import "SettingManager.h"
#import "npFontSprite.h"

#import "uiSpriteRender.h"

enum States
{
    INTRO,
    GAME,
    END,
};


#ifndef eristoffGameConsole_mainController_h
#define eristoffGameConsole_mainController_h

class mainController : public npDisplayObject{
    
    States currentState;
    vector<ci::osc::Sender> senders;
    ci::osc::Listener listener;
    
    ci::Vec3f rotation;
    ci::Vec3f calibrationPos;
    

    npBitmapSprite background;
    
    npBitmapSprite btnStart;
    npBitmapSprite btnCalibrate;
    
    npBitmapSprite btnShoot;
    
    // points
    npBitmapSprite points10;
    npBitmapSprite points25;
    npBitmapSprite points50;

    npBitmapSprite bottle;

    npBitmapSprite btnLeftRight;
    
    ci::Vec2f scorePanelStartPosition;
    ci::Vec2f nameLabelStartPosition;
    ci::Vec2f scoreLabelStartPosition;
    
    npBitmapSprite scorePanel;
        
    void setIntro();
    void setStart();
    void setGameOver();
    
    void calibrate();

    CMMotionManager* motionManager;
    GLuint interfaceTextureId;

    bool shoot;
    bool isRightHanded;
    int score;
    
    float timeoutTimer;
    float totalGameTime;
    
    float pointsStartYPosition;
    float scorePanelYPosition;
    
    void set10Points();
    void set25Points();
    void set50Points();
    void setBottle();
    
    void setPlayerNumber(int number);
    
public:
    void setup();
    void update();
    void draw();
    
    void checkToucheDown(vector<ci::Vec2f> touches);
    void checkToucheUp(vector<ci::Vec2f> touches);
    
    npFontSprite* scoreLabel;
    npFontSprite* nameLabel;
    
    UITextField* txtName;
    UITextField* txtFirstName;
    UILabel* debugLabel;

};

#endif
