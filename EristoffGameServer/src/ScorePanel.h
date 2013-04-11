//
//  scorePanel.h
//  EristoffGameServer
//
//  Created by Kris Meeusen on 01/10/12.
//
//

#ifndef EristoffGameServer_scorePanel_h
#define EristoffGameServer_scorePanel_h

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Font.h"
#include "cinder/Text.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/Font.h"
#include "cinder/Text.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"


#include "Player.h"


class ScorePanel{
    
    
    ci::gl::Texture	scoreText1;
    ci::gl::Texture	scoreText2;
	
	ci::gl::TextureFontRef	mTextureFont;
	
	
    ci::Font	mFont;
    ci::Font	mFontPlayerNumber;
    ci::Font	mFontPlayerName;
    ci::Font	mFontPlayerScore;
    ci::Font	mFontOutroScore;
    ci::Font	mFontOutroScorePlayerName;
    
	
    ci::gl::Texture mScoreBackgroundLeft;
    ci::gl::Texture mScoreBackgroundRight;
	
	ci::gl::Texture mScorePanelOutro;
    
	//text outro
	ci::gl::Texture mScorePanelOutroNamesTexture;
    ci::gl::Texture mScorePanelOutroScoreTexture;
	// player1
	ci::gl::Texture mScorePanelOutroPlayer1NameTexture;
	ci::gl::Texture mScorePanelOutroPlayer1ScoreTexture;
	// player2
	ci::gl::Texture mScorePanelOutroPlayer2NameTexture;
	ci::gl::Texture mScorePanelOutroPlayer2ScoreTexture;
	
	
	
	void drawPlayer(ci::Vec3f position,float scale,Player* player,ci::gl::Texture& texture,ci::gl::Texture& textureBackground,bool alignLeft);
	void generateTextLeft(Player* player,int index,ci::gl::Texture& texture);
	void generateTextRight(Player* player,int index,ci::gl::Texture& texture);
	
	
public:
    void setup();
    void update();
    void drawScorePanels();
    void drawOutroScore();
    
	void generateFinalScoreBoardText();
	
	ci::Vec3f pos;
	
};

#endif