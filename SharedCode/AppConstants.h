#pragma once

#define MESG_CLIENT_NEW_PLAYER "c/new"
#define MESG_CLIENT_UPDATE_PLAYER "c/update"

#define MESG_SERVER_NEW_GAME "s/newGame"
#define MESG_SERVER_START_GAME "s/startGame"
#define MESG_SERVER_GAMEOVER "s/gameover"
#define MESG_SERVER_PLAYER_ACCEPTED "s/accepted"
#define MESG_SERVER_CLIENT_UPDATE "s/clientUpdate"

#define MESG_SERVER_SLAVE_UPDATE "s/slaveUpdate"
#define MESG_SERVER_SLAVE_SCORES "s/slaveScores"


#define UDP_PORT 3000
#define prizeTypeColorDivideFactor 50.0

#define NR_OF_WINDOWS 12

enum PrizeType { POINTS10=10, POINTS25=25,POINTS50=50,BAD=5,BOTTLE=30 };
