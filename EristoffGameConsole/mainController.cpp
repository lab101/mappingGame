//
//  mainController.cpp
//  eristoffGameConsole
//
//  Created by Kris Meeusen on 20/09/12.
//
//

#include "mainController.h"
#include "npTimer.h"

#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <boost/algorithm/string.hpp>




using namespace ci;


void mainController::setup(){
    
    pointsStartYPosition = -170;

    background.setSize(1024, 768,NP_ALIGN_TOPLEFT);
    background.setUVauto(1024, 0, 2048, 768* 2);
    background.setPos(0, 0);
    background.isDirty = true;
    background.resetData();
    addChild(background);
    
    
    btnStart.setSize(400, 100,NP_ALIGN_CENTER);
    btnStart.setUVauto(0, 0, 2048, 768* 2);
    btnStart.setPos(1024/2, 280);
    btnStart.alpha = 1;
    btnStart.isDirty = true;
    btnStart.resetData();
    addChild(btnStart);
    
//    btnCalibrate.setSize(400, 100,NP_ALIGN_CENTER);
//    btnCalibrate.setUVauto(0, 100, 2048, 768* 2);
//    btnCalibrate.setPos(1024/2, 400);
//    btnCalibrate.alpha = 0;
//    btnCalibrate.isDirty = true;
//    btnCalibrate.resetData();
//    addChild(btnCalibrate);
    
    btnShoot.setSize(270, 270,NP_ALIGN_CENTER);
    btnShoot.setUVauto(27, 290, 2048, 768* 2);
    btnShoot.alpha = 0;
    btnShoot.isDirty = true;
    addChild(btnShoot);
    
    
    btnLeftRight.setSize(370, 69,NP_ALIGN_CENTER);
    btnLeftRight.setUVauto(40, 1169, 2048, 768* 2);
    btnLeftRight.setPos(1024.0/2.0, 200);
    btnLeftRight.isDirty = true;
    addChild(btnLeftRight);
    
    
    
    // points
    
    points10.setSize(150,134,NP_ALIGN_TOPLEFT);
    points10.setUVauto(450, 0, 2048, 768* 2);
    points10.setPos(125, pointsStartYPosition);
    points10.isDirty = true;
    points10.resetData();
    addChild(points10);
    
    points25.setSize(150,134,NP_ALIGN_TOPLEFT);
    points25.setUVauto(450 + 150, 0, 2048, 768* 2);
    points25.setPos(125 + 138, pointsStartYPosition);
    points25.isDirty = true;
    points25.resetData();
    addChild(points25);
    
    points50.setSize(150,134,NP_ALIGN_TOPLEFT);
    points50.setUVauto(450 + 300, 0, 2048, 768* 2);
    points50.setPos(125 + (138*2), pointsStartYPosition);
    points50.isDirty = true;
    points50.resetData();
    addChild(points50);
    
    bottle.setSize(150,280,NP_ALIGN_TOPLEFT);
    bottle.setUVauto(680, 290, 2048, 768* 2);
    bottle.setPos(-5,-10);
    bottle.alpha = 0;
    bottle.isDirty = true;
    addChild(bottle);

    scorePanel.setSize(350,500,NP_ALIGN_CENTER);
    scorePanel.setUVauto(20, 600, 2048, 768* 2);
    scorePanel.alpha = 1;
    scorePanel.isDirty = true;
    
    addChild(scorePanel);

    
    scorePanelStartPosition.set(1024/2,768-110);
    scoreLabelStartPosition.set(1024/2, 768-74);
    nameLabelStartPosition.set(1024/2, 768-162);

    
        
    currentState = INTRO;
    setIntro();
    
    calibrationPos.set(-0.4,0,0);
    timeoutTimer = -1;
    


    // setup osc connections
    for(int i=0;i < SettingManager::Instance()->servers.size();++i){
        senders.push_back(ci::osc::Sender());
        senders.back().setup(SettingManager::Instance()->servers[i], UDP_PORT);
    }
    
    listener.setup(UDP_PORT);
    
    
     // setup gyroscope
     motionManager = [[CMMotionManager alloc] init];
     motionManager.gyroUpdateInterval = 1.0/60.0;
    
     if (motionManager.gyroAvailable) {     
         [motionManager startDeviceMotionUpdates];
     } else {
     NSLog(@"No gyroscope on device.");
         [motionManager release];
     }
    
    
    // setup GL
    ImageDataLoader IDloader;
    // Loading interface texture
    GLubyte* imagedata = IDloader.loadFile(@"interface.png");
    glGenTextures(1, &interfaceTextureId);
    glBindTexture(GL_TEXTURE_2D, interfaceTextureId);
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA , 2048,1536, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagedata);

    nameLabel->setup("Arial-BoldMT",37,NP_ALIGN_CENTER);
    nameLabel->setColor(ci::Color(205/255.0,205/255.0,205/255.0));
    
    scoreLabel->setup("Arial-BoldMT",100,NP_ALIGN_CENTER);
    
    
    scorePanel.setPos(scorePanelStartPosition.x,scorePanelStartPosition.y + 400);
    scoreLabel->setPos(scoreLabelStartPosition.x,scoreLabelStartPosition.y  + 400);
    nameLabel->setPos(nameLabelStartPosition.x,nameLabelStartPosition.y + 400);

    
//    btnFire.setupByResource("btnFire.png",100,100,ALIGN_BOTTOMRIGHT);
//   spriteRender.setup();
//    spriteRender.add(&btnFire);
    
    isRightHanded = true;
    
}




void mainController::set10Points(){
    points10.setPos(points10.x, -170);
    npTween  moveTween;
    moveTween.init( &points10,NP_EASE_OUT_BACK,400,0);
    moveTween.addProperty( &points10.y, -25);
    npTweener::addTween(moveTween);
    
    npTween  moveTweenBack;
    moveTweenBack.init( &points10,NP_EASE_OUT_BACK,400,2000);
    moveTweenBack.addProperty( &points10.y, pointsStartYPosition,-25);
    
    npTweener::addTween(moveTweenBack,false);
}

void mainController::set25Points(){
    points25.setPos(points25.x, -170);
    npTween  moveTween;
    moveTween.init( &points25,NP_EASE_OUT_BACK,400,0);
    moveTween.addProperty( &points25.y, -25);
    npTweener::addTween(moveTween);
    
    npTween  moveTweenBack;
    moveTweenBack.init( &points25,NP_EASE_OUT_BACK,400,2000);
    moveTweenBack.addProperty( &points25.y, pointsStartYPosition,-25);
    
    npTweener::addTween(moveTweenBack,false);
    
}

void mainController::set50Points(){
    points50.setPos(points50.x, -170);
    npTween  moveTween;
    moveTween.init( &points50,NP_EASE_OUT_BACK,400,0);
    moveTween.addProperty( &points50.y, -25);
    npTweener::addTween(moveTween);
    
    npTween  moveTweenBack;
    moveTweenBack.init( &points50,NP_EASE_OUT_BACK,400,2000);
    moveTweenBack.addProperty( &points50.y, pointsStartYPosition,-25);
    
    npTweener::addTween(moveTweenBack,false);
    
}
void mainController::setBottle(){
    npTween fadeIn;
    fadeIn.init( &bottle,NP_EASE_OUT_SINE,800,0);
    fadeIn.addProperty( &bottle.alpha, 1);
    npTweener::addTween(fadeIn);

}

void mainController::setIntro(){
    
    scorePanelYPosition = 400;
    // will be overwritten by server if connected otherwise this is used to timeout
    totalGameTime = 90 * 1000;

    scoreLabel->setText("0");
    
    npTween  moveTween1;
    moveTween1.init( &scorePanel,NP_EASE_OUT_BACK,400,0);
    moveTween1.addProperty( &scorePanel.y, scorePanelStartPosition.y + 400);
    npTweener::addTween(moveTween1);
    
    npTween  moveTween2;
    moveTween2.init( scoreLabel,NP_EASE_OUT_BACK,400,0);
    moveTween2.addProperty( &scoreLabel->y, scoreLabelStartPosition.y+ 400);
    npTweener::addTween(moveTween2);
    
    npTween  moveTween3;
    moveTween3.init( nameLabel,NP_EASE_OUT_BACK,400,0);
    moveTween3.addProperty( &nameLabel->y, nameLabelStartPosition.y + 400);
    npTweener::addTween(moveTween3);

    
    
    btnStart.alpha = 1;
    btnStart.isDirty = true;
    
    btnLeftRight.alpha = 1;
    btnLeftRight.isDirty = true;
    
    bottle.alpha = 0;
    bottle.isDirty = true;
    

    txtName.hidden = false;
    txtFirstName.hidden = false;
    
    isRightHanded = true;

}



void mainController::setGameOver(){
    
    btnCalibrate.alpha = 0;
    btnCalibrate.isDirty = true;
    
    btnShoot.isDirty = true;
    btnShoot.alpha = 0;
    
    timeoutTimer = -1;
    
}


void mainController::setStart(){
    
    //hide stuff
    btnStart.alpha = 0;
    btnStart.isDirty = true;
    
    btnCalibrate.alpha = 1;
    btnCalibrate.isDirty = true;
    
    btnShoot.alpha = 1;
    btnShoot.isDirty = true;
    
    
    btnLeftRight.alpha = 0;
    btnLeftRight.isDirty = true;
    
    if(isRightHanded){
        btnShoot.setPos(1024 - 182, 768 -178);
    }else{
        btnShoot.setPos(182, 768 -178);
    }
    
    txtName.hidden = true;
    txtFirstName.hidden = true;
    
    [txtName setText:@""];
    [txtFirstName setText:@""];

    

    // show stuff
    
    npTween  moveTween1;
    moveTween1.init( &scorePanel,NP_EASE_OUT_BACK,400,0);
    moveTween1.addProperty( &scorePanel.y, scorePanelStartPosition.y);
    npTweener::addTween(moveTween1);
    
    npTween  moveTween2;
    moveTween2.init( scoreLabel,NP_EASE_OUT_BACK,400,0);
    moveTween2.addProperty( &scoreLabel->y, scoreLabelStartPosition.y);
    npTweener::addTween(moveTween2);
    
    npTween  moveTween3;
    moveTween3.init( nameLabel,NP_EASE_OUT_BACK,400,0);
    moveTween3.addProperty( &nameLabel->y, nameLabelStartPosition.y);
    npTweener::addTween(moveTween3);
    


    
    
}




void mainController::checkToucheDown(vector<ci::Vec2f> touches){
//    set10Points();
//    set25Points();
//    set50Points();
//    setBottle();
    
    for (vector<Vec2f>::const_iterator it = touches.begin(); it != touches.end(); ++it) {
        
        if(btnShoot.checkTouch(*it,3)){
            btnShoot.setUVauto(27 + 270, 290, 2048, 768* 2);

            //btnShoot.setUVauto(30 + 255, 299, 2048, 768* 2);
          //  btnShoot.scale = 0.8;
          //  btnShoot.isDirty = true;
            shoot = true;
        }
    }
}


void mainController::checkToucheUp(vector<ci::Vec2f> touches){
  
    for (vector<Vec2f>::const_iterator it = touches.begin(); it != touches.end(); ++it) {
        
        if(btnShoot.checkTouch(*it,3)){
            btnShoot.setUVauto(27, 290, 2048, 768* 2);
            
            //btnShoot.scale = 1;

            btnShoot.isDirty = true;
        }
        
        if (btnLeftRight.checkTouch(*it)) {
            if(it->x < 1024/2.0){
                isRightHanded = false;
                btnLeftRight.setUVauto(40, 1169 + 69, 2048, 768* 2);
            }else{
                btnLeftRight.setUVauto(40, 1169 , 2048, 768* 2);

            }
        }

        
        // start button hit
        if (btnStart.checkTouch(*it)) {
            
            [txtFirstName resignFirstResponder];
            [txtName resignFirstResponder];
            
            string firstname = "";
            string lastname = "";
            string fullname = "";
           
            if([txtFirstName.text length] > 0 && [txtName.text length] > 0){
                firstname = [txtFirstName.text UTF8String];
                lastname = [txtName.text UTF8String];

            }else{
                return;
            }
            
            //remove ;
            boost::replace_all(firstname, ";", ":");
            boost::replace_all(lastname, ";", ":");
            
            // set to upper
            boost::to_upper(firstname);
            boost::to_upper(lastname);
            
            // set score panel 
            std::string displayText = firstname + " "+ lastname;
            if (displayText.size() > 9) {
               displayText = displayText.substr(0,9);
            }

            nameLabel->setText(displayText);
            
            
            boost::uuids::uuid uuid = boost::uuids::random_generator()();
            string uniqueIDString = boost::lexical_cast<std::string>(uuid);
            
            for(int i=0;i < SettingManager::Instance()->servers.size();++i){
                
                ci::osc::Message message;
                
                message.addStringArg(uniqueIDString);
                message.addStringArg(firstname);
                message.addStringArg(lastname);
                
                message.setAddress(MESG_CLIENT_NEW_PLAYER);
                message.setRemoteEndpoint(SettingManager::Instance()->servers[i], UDP_PORT);
                
                senders[i].sendMessage(message);
   //             calibrationPos.x = motionManager.deviceMotion.gravity.x;
     //           calibrationPos.y = motionManager.deviceMotion.gravity.y;
            
                                

//                calibrate();
            }
            
            
            
        }else if(btnCalibrate.checkTouch(*it)){
            cout << "calibrate" << endl;
            
#if !(TARGET_IPHONE_SIMULATOR)
            calibrate();
#endif
        }
    }
}

void mainController::calibrate(){
    calibrationPos.x = motionManager.deviceMotion.gravity.x;
    calibrationPos.y = motionManager.deviceMotion.gravity.y;
}


void mainController::setPlayerNumber(int number){
    scorePanel.setUVauto(20 + (350 * (number-1)), 600, 2048, 768* 2);

}

void mainController::update(){
    while (listener.hasWaitingMessages()) {
        cinder::osc::Message message;
		listener.getNextMessage(&message);
		
        string ip = message.getRemoteIp();
   //     debugLabel.text =  [NSString stringWithUTF8String:message.getAddress().c_str()];
        
        if (message.getAddress() == MESG_SERVER_START_GAME) {
            
            totalGameTime = message.getArgAsInt32(0) * 1000;
            setPlayerNumber(message.getArgAsInt32(1));
            
           // std::cout << totalGameTime<< std::endl;
            debugLabel.text = [NSString stringWithFormat:@"%f", totalGameTime];
            timeoutTimer= npTimer::getCurrentTime();

            
            //debugLabel.text =  [NSString stringWithUTF8String:totalGameTime.c_str()];
                               //] @"NEW GAME" + timeoutTimer;
            //setNewGame();
            
        }else if(message.getAddress() == MESG_SERVER_PLAYER_ACCEPTED) {
            setStart();
            debugLabel.text = @"MESG_SERVER_PLAYER_ACCEPTED";


        }else if(message.getAddress() == MESG_SERVER_GAMEOVER) {
            debugLabel.text = @"MESG_SERVER_GAMEOVER";
            
            setGameOver();
        }else if(message.getAddress() == MESG_SERVER_NEW_GAME) {
            debugLabel.text = @"MESG_SERVER_NEW_GAME";
            
            setIntro();
        }else if(message.getAddress() == MESG_SERVER_CLIENT_UPDATE) {
            //setGameOver();
            
            switch (message.getArgAsInt32(0)) {
                case POINTS10:
                    set10Points();
                    break;
                case POINTS25:
                    set25Points();
                    break;
                case POINTS50:
                    set50Points();
                    break;
                case BOTTLE:
                    setBottle();
                    break;
                    
                default:
                    break;
            }
            
            score = message.getArgAsInt32(1);
            scoreLabel->setText(boost::lexical_cast<std::string>(score));
                            
        }
    }
    //if(message.getAddress() == MESG_CLIENT_NEW_PLAYER){
    
    
    // check timeout
    if(timeoutTimer > 0 && (npTimer::getCurrentTime() - timeoutTimer) > (totalGameTime + 1000 ))
    {
        setGameOver();
        setIntro();
    }
    
    
#if !(TARGET_IPHONE_SIMULATOR)
    rotation.x = motionManager.deviceMotion.gravity.x;
    rotation.y = motionManager.deviceMotion.gravity.y;

    //debugLabel.text = [NSString stringWithFormat:@"%f/%f", rotation.x,rotation.y];

    
    // calculate roation from calibration position
    rotation.x -= calibrationPos.x;
    rotation.y -= calibrationPos.y;
    
    // make coordinate system from -1 to 1
    rotation.x *= 2;
    rotation.y *= 2;
#endif
    
    
    for(int i=0;i < SettingManager::Instance()->servers.size();++i){
        ci::osc::Message message;
        message.addFloatArg(rotation.x);
        message.addFloatArg(rotation.y);

        if(shoot){
            message.addIntArg(1);
        }
        
        
        message.setAddress(MESG_CLIENT_UPDATE_PLAYER);
        message.setRemoteEndpoint(SettingManager::Instance()->servers[i], UDP_PORT);
        
        senders[i].sendMessage(message);
    }
    
    shoot = false;

}

void mainController::draw(){
        
    glClearColor(1.0,0.0,0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable (GL_BLEND);
        
    
    glBindTexture(GL_TEXTURE_2D, interfaceTextureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}