//
//  HitItemPool.cpp
//  EristoffGameServer
//
//  Created by Kris Temmerman on 12/10/12.
//
//

#include "HitItemPool.h"
void HitItemPool::setup()
{
    
    
    
    /// LOAD COIN
    string coinPath = getAssetPath( "models/COIN.dae" ).string();
    cinder::Matrix44f mat;
    mat.setToIdentity();

    mat.scale (0.01);
    loader.preMatrix =mat;
    loader.load(coinPath);
    coinMesh = loader.getMeshByName("COIN");
    
    coin10Mat= new npMaterial();
    coin10Mat->setColorTexture("models/coin10.png");
    
    coin25Mat= new npMaterial();
    coin25Mat->setColorTexture("models/coin25.png");
    
    coin50Mat= new npMaterial();
    coin50Mat->setColorTexture("models/coin50.png");
    
    
    
    
    
    ///LOAD WOLF
    string wolfPath = getAssetPath( "models/WOLF growl.dae" ).string();
    mat.setToIdentity();
     mat.scale (0.06);
    loader.preMatrix =mat;
        loader.load(wolfPath);
   
    wolfMesh =loader.getMeshByName("WolfREDUCED");
     
  
   
	wolfMat= new npMaterial();
    wolfMat->setColorTexture("models/wolf.jpg");

    
   }
HitItem * HitItemPool::getHitItem(PrizeType type )
{
    ///POINTS10=10, POINTS25=25,POINTS50=50,BAD=4,BOTTLE=30
   
   if(type == POINTS10 || type == POINTS25|| type == POINTS50  )
    {
        HitItem *coin = getCoin(type);
        
        if (type ==POINTS10) coin->visualMesh->material =  coin10Mat;
        if (type ==POINTS25) coin->visualMesh->material =  coin25Mat;
        if (type ==POINTS50) coin->visualMesh->material =  coin50Mat;
        if (type ==BAD) coin->visualMesh->material =  wolfMat;
        return coin;
    
    }
    else if(type==BAD )
    {
        HitItem *wolf = getWolf(type);
        
        wolf->visualMesh->material =  wolfMat;
        return wolf;
    
    }
  
    return NULL;
}
HitItem *  HitItemPool::getWolf(PrizeType type )
{
    for ( int i =0; i<wolven.size();i++)
    {
        if (!wolven[i]->used)
        {
            wolven[i]->used =true;
            return wolven[i];
        }
        
    }
    HitItemWolf *wolfH = new HitItemWolf();
    wolfH->visualMesh= wolfMesh->clone();
   wolfH->used =true;
    
    
    
  
    wolven.push_back(wolfH);
    return (HitItem *)wolfH;


}
HitItem * HitItemPool::getCoin(PrizeType type )
{
 

    for ( int i =0; i<coins.size();i++)
    {
        if (!coins[i]->used)
        {
            coins[i]->used =true;
            return coins[i];
        }
    
    }

    HitItemCoin *coinH = new HitItemCoin();
    coinH->visualMesh= coinMesh->clone();
    coinH->used =true;
    

   
   
    coins.push_back(coinH);
    return (HitItem *)coinH;
}