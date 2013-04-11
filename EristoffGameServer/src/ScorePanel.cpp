//
//  scorePanel.cpp
//  EristoffGameServer
//
//  Created by Kris Meeusen on 01/10/12.
//
//

#include "ScorePanel.h"
#include "GameController.h"
#include <sstream>
#include <iostream>
#include "cinder/ImageIo.h"
#include <boost/lexical_cast.hpp>
#include "SettingManager.h"
#include "StringUtil.h"

using namespace ci;
using namespace ci::app;
using namespace std;



void ScorePanel::setup()
{
    mFont = Font(ci::app::loadAsset("fonts/Railway.ttf"), 24 );
	
    mFontPlayerNumber = Font(ci::app::loadAsset("fonts/Railway.ttf"), 22 );
    mFontPlayerName = Font(ci::app::loadAsset("fonts/Railway.ttf"), 44 );
	mTextureFont = gl::TextureFont::create( mFontPlayerName );
	
	
	mFontPlayerScore = Font(ci::app::loadAsset("fonts/Railway.ttf"), 58 );
	
	mFontOutroScore= Font(ci::app::loadAsset("fonts/Railway.ttf"), 20 );
	mFontOutroScorePlayerName= Font(ci::app::loadAsset("fonts/Railway.ttf"), 24 );
	
	mTextureFont = gl::TextureFont::create(mFont);
    
    mScoreBackgroundLeft = loadImage(loadAsset("scorebackgroundLeft.png"));
    mScoreBackgroundRight= loadImage(loadAsset("scorebackgroundRight.png"));
	mScorePanelOutro = loadImage(loadAsset("gameover-scoreboard2.png"));
	
	pos.set(0,0,0);
	
}
void ScorePanel::update()
{
}


void ScorePanel::drawOutroScore(){
	
	glPushMatrix();
	glTranslatef(SettingManager::Instance()->meshOffset.x + SettingManager::Instance()->scorepanelOutroPos.x,SettingManager::Instance()->meshOffset.y + SettingManager::Instance()->scorepanelOutroPos.y,0);
	glScalef(SettingManager::Instance()->scorepanelOutroScale * SettingManager::Instance()->meshScaleX,SettingManager::Instance()->scorepanelOutroScale* SettingManager::Instance()->meshScaleY,1);
	
	gl::draw(mScorePanelOutro,Vec2f(-mScorePanelOutro.getWidth()/2,-mScorePanelOutro.getHeight()/2));
	
	if(mScorePanelOutroNamesTexture) gl::draw(mScorePanelOutroNamesTexture,Vec2f(-251.82,-96.42) );
	if(mScorePanelOutroScoreTexture) gl::draw(mScorePanelOutroScoreTexture,Vec2f(-27.61,-96.42));
	
	if(mScorePanelOutroPlayer1NameTexture) gl::draw(mScorePanelOutroPlayer1NameTexture,Vec2f(-147 - mScorePanelOutroPlayer1NameTexture.getWidth()/2.0 ,-175));
	if(mScorePanelOutroPlayer2NameTexture) gl::draw(mScorePanelOutroPlayer2NameTexture,Vec2f(75 - mScorePanelOutroPlayer2NameTexture.getWidth()/2,-175));
	
	if(mScorePanelOutroPlayer1ScoreTexture) gl::draw(mScorePanelOutroPlayer1ScoreTexture,Vec2f(-147 - mScorePanelOutroPlayer1ScoreTexture.getWidth()/2.0,-145-6) + pos.xy());
	if(mScorePanelOutroPlayer2ScoreTexture) gl::draw(mScorePanelOutroPlayer2ScoreTexture,Vec2f(75 - mScorePanelOutroPlayer2ScoreTexture.getWidth()/2.0 ,-145-6)  );
	
	
	glPopMatrix();
	
}


void ScorePanel::drawScorePanels()
{
	//    if(GameController::Instance()->currentGameState == WAITING){
	//		mTextureFont->drawString("WAITING FOR PLAYERS",Vec2f(10,50));
	//	}
	//
	//
	//    if(GameController::Instance()->currentGameState == OUTRO){
	//		mTextureFont->drawString("GAMEOVER",Vec2f(100,200));
	//	}
    
    
	//	if(GameController::Instance()->currentGameState == GAME)
	//	{
	//        int remainingTime = GameController::Instance()->getRemainingTime();
	//		mTextureFont->drawString(boost::lexical_cast<std::string>(remainingTime),Vec2f(getWindowWidth() - 300,150));
	//	}
    
    // draw players
    int i=0;
    
	
    for(std::map<std::string,Player>::iterator it = GameController::players.begin();it != GameController::players.end();++it){
        
		
		if((*it).second.playerNumber == 1){
			
			generateTextLeft(&(*it).second,0 ,scoreText1);
			drawPlayer(SettingManager::Instance()->scorepanel1Pos + SettingManager::Instance()->meshOffset,SettingManager::Instance()->scorepanel1Scale * SettingManager::Instance()->meshScaleX,&(*it).second,scoreText1,mScoreBackgroundLeft,true);
		}else{
			generateTextRight(&(*it).second, 1,scoreText2);
			drawPlayer(SettingManager::Instance()->scorepanel2Pos + SettingManager::Instance()->meshOffset,SettingManager::Instance()->scorepanel2Scale * SettingManager::Instance()->meshScaleX,&(*it).second,scoreText2,mScoreBackgroundRight,false);
		}
		
		++i;
		
	}
}


void ScorePanel::drawPlayer(Vec3f position,float scale,Player* player,ci::gl::Texture& texture,ci::gl::Texture& textureBackground,bool alignLeft){
	glPushMatrix();
	glTranslatef(position.x,position.y,0);
	
	glScalef(scale,scale,1);
    
    
	//   glEnable( GL_BLEND );
	//  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    glColor4f(1,1,1,0.9);
    
    gl::enableAlphaBlending();
	
	gl::draw(textureBackground);
	
	glColor4f(1,1,1,1);
	
    gl::draw(texture,Vec2f(60 + (alignLeft ? 0 : (200-texture.getWidth())),80));
	
	//glDisable( GL_BLEND );
    
	glColor3f(1,1,1);
 	glPopMatrix();
}

void ScorePanel::generateTextLeft(Player* player,int index,ci::gl::Texture& texture){
	
	//mTextureFont->drawString(player->getName() + " test" + boost::lexical_cast<std::string>(player->getScore()),Vec2f(10,150));
	
	TextLayout simple;
	simple.setColor(Color(1,1,1));
	
	simple.setFont(  mFontPlayerNumber );
	simple.addLine("PLAYER " + toString(index+1) );
	
	simple.setFont( mFontPlayerName );
	simple.addLine( trimToLength(player->getFirstName(),9 ));
	
	simple.setFont(  mFontPlayerScore );
	simple.addLine(toString(player->getScore() ) );
	
	texture = gl::Texture( simple.render( true, true ) );
}


void ScorePanel::generateTextRight(Player* player,int index,ci::gl::Texture& texture){
	
	//mTextureFont->drawString(player->getName() + " test" + boost::lexical_cast<std::string>(player->getScore()),Vec2f(10,150));
	
	TextLayout simple;
	simple.setColor(Color(1,1,1));
	
	simple.setFont(  mFontPlayerNumber );
	simple.addRightLine("PLAYER " + toString(index+1) );
	
	simple.setFont(  mFontPlayerName );
	simple.addRightLine(trimToLength(player->getFirstName(),7) );
	
	simple.setFont(  mFontPlayerScore );
	simple.addRightLine(toString(player->getScore() ) );
	
	texture = gl::Texture( simple.render( true, true ) );
}


void ScorePanel::generateFinalScoreBoardText(){
	
	TextLayout layoutNames;
	TextLayout layoutScores;
	
	layoutNames.setLeadingOffset(10);
	layoutScores.setLeadingOffset(10);
	
	layoutNames.setColor(Color(1,1,1));
	layoutScores.setColor(Color(1,1,1));
	
	layoutNames.setFont(  mFontOutroScore );
	layoutScores.setFont(  mFontOutroScore );
	
	int count = 0;
	
	vector<std::string> playersInTop10;
	
	
	// draw top 10
	for(std::vector<Player>::iterator it = ScoreController::Instance()->getScores().begin();it != ScoreController::Instance()->getScores().end();++it){
		
		if( GameController::Instance()->isActivePlayer(it->getUniqueId())){
			layoutNames.setColor(Color(1,0.5,0.5));
			layoutScores.setColor(Color(1,0.5,0.5));
			playersInTop10.push_back(it->getUniqueId());
			
		}else{
			layoutNames.setColor(Color(1,1,1));
			layoutScores.setColor(Color(1,1,1));
		}
		
		if(++count == 11) break;
		
		std::string spacer = count < 10 ? "   " : " ";
		
		std::string origField = "#" + toString(count) + spacer + it->getName();
		std::string field = origField;
		int fieldChars = origField.size();
		float fieldWidth;
		int breakdown = 0;
		
		do{
			field = trimToLength(origField,fieldChars);
			fieldWidth = mTextureFont->measureString(field).x;
			fieldChars--;
			//std::cout << field << " : " << fieldChars << ":" << fieldWidth << std::endl;
			if(++breakdown == 1000) break;
			
		}while(fieldWidth > 270);
		
		layoutNames.addLine(field);
		layoutScores.addRightLine(toString(it->getScore())+ "ptn");
	}
	
	
	
	mScorePanelOutroNamesTexture = gl::Texture( layoutNames.render( true, true ) );
	
	
	// draw extra if needed
	//bool firstAdded = true;
	
    Player* player1 = 0;
    Player* player2 = 0;
	
	for(std::map<std::string,Player>::iterator it = GameController::players.begin();it != GameController::players.end();++it){
        
        // poor mans player sorting
        if(player1 ==0)
        {
            player1 = &it->second;
        }else{
            if(player1->getScore() < it->second.getScore()){
                player2 = player1;
                player1 = &it->second;
            }else{
                player2 = &it->second;
            }
            
        }
  	}
	
	if(player1 != 0){
		// player1
		
		TextLayout layoutPlayer1Name;
		TextLayout layoutPlayer1Score;
		
		layoutPlayer1Name.setColor(Color(248.0/255.0,201.0/255.0,65.0/255.0));
		layoutPlayer1Score.setColor(Color(248.0/255.0,201.0/255.0,65.0/255.0));
		
		layoutPlayer1Name.setFont(  mFontOutroScorePlayerName );
		layoutPlayer1Score.setFont(  mFontOutroScorePlayerName );
		
		layoutPlayer1Name.addCenteredLine ("#" + toString(player1->getRank()) + " " + trimToLength(player1->getFirstName(),9));
		layoutPlayer1Score.addCenteredLine (toString(player1->getScore()) + "ptn");
		
		mScorePanelOutroPlayer1NameTexture = gl::Texture( layoutPlayer1Name.render( true, true ) );
		mScorePanelOutroPlayer1ScoreTexture = gl::Texture( layoutPlayer1Score.render( true, true ) );
	}
	
	if(player2 != 0){
		// player1
		
		TextLayout layoutPlayer2Name;
		TextLayout layoutPlayer2Score;
		
		layoutPlayer2Name.setColor(Color(1,1,1));
		layoutPlayer2Score.setColor(Color(1,1,1));
		
		layoutPlayer2Name.setFont(  mFontOutroScorePlayerName );
		layoutPlayer2Score.setFont(  mFontOutroScorePlayerName );
		
		layoutPlayer2Name.addCenteredLine ("#" + toString(player2->getRank()) + " " + trimToLength(player2->getFirstName(),9));
		layoutPlayer2Score.addCenteredLine (toString(player2->getScore()) + "ptn");
		
		mScorePanelOutroPlayer2NameTexture = gl::Texture( layoutPlayer2Name.render( true, true ) );
		mScorePanelOutroPlayer2ScoreTexture = gl::Texture( layoutPlayer2Score.render( true, true ) );
	}
	
	
	
	
	mScorePanelOutroScoreTexture = gl::Texture( layoutScores.render( true, true ) );
	
}
