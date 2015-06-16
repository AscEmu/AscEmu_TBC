#include "StdAfx.h"
#include "Setup.h"

#define CREATE_QUESTSCRIPT(cl) (QuestScript*)new cl

void OnEnterWorld(Player * pPlayer)
{
        if( pPlayer && pPlayer->GetSession() )
        {
                if( pPlayer->GetSession()->CanUseCommand('z') )
                {
                        char Message[512];
                        sprintf( Message, "%s[ADMIN]r%s%s has logged on!", MSG_COLOR_LIGHTBLUE, MSG_COLOR_GREEN, pPlayer->GetName() );
                        sWorld.SendWorldText( Message );
                }
                else if( pPlayer->GetSession()->CanUseCommand('a') )
                {
                        char Message[512];
                        sprintf( Message, "%s[GM]r%s%s has logged on!", MSG_COLOR_LIGHTBLUE, MSG_COLOR_GREEN, pPlayer->GetName() );
                        sWorld.SendWorldText( Message );
                };
        };

    if( pPlayer->GetMapId() == 169 && pPlayer->IsPvPFlagged() )
            pPlayer->SetPvPFlag();
        
        pPlayer->ResetKillStreak()
;};

class ChampionOfNaruu : public QuestScript
{       
public:
        void OnQuestComplete(Player* mTarget, QuestLogEntry *qLogEntry) 
        {
                if( !mTarget->HasKnownTitle( PVPTITLE_CHAMPION_OF_THE_NAARU ) )
                {
                        mTarget->SetKnownTitle( PVPTITLE_CHAMPION_OF_THE_NAARU, true  );
                        mTarget->BroadcastMessage( "You have earned title 'Champion of Naruu'! Congratulations!" );
                }
        };
};

class HandOfAdal : public QuestScript
{       
public:
        void OnQuestComplete(Player* mTarget, QuestLogEntry *qLogEntry) 
        {
                if( !mTarget->HasKnownTitle( PVPTITLE_HAND_OF_ADAL ) )
                {
                        mTarget->SetKnownTitle( PVPTITLE_HAND_OF_ADAL, true  );
                        mTarget->BroadcastMessage( "You have earned title 'Hand of A'dal'! Congratulations!" );
                };
        };
};

class ShatteredSun : public QuestScript
{       
public:
        void OnQuestComplete(Player* mTarget, QuestLogEntry *qLogEntry) 
        {
                if( !mTarget->HasKnownTitle( PVPTITLE_OF_THE_SHATTERED_SUN ) )
                {
                        mTarget->SetKnownTitle( PVPTITLE_OF_THE_SHATTERED_SUN, true  );
                        mTarget->BroadcastMessage( "You have earned title 'Of The Shattered Sun' Congratulations!" );
                };
        };
};

void SetupGMAnnounce(ScriptMgr* mgr)
{
        mgr->register_hook( SERVER_HOOK_EVENT_ON_ENTER_WORLD_2, (void *)&OnEnterWorld);
        mgr->register_quest_script( 10888, CREATE_QUESTSCRIPT( ChampionOfNaruu ) );
        mgr->register_quest_script( 10445, CREATE_QUESTSCRIPT( HandOfAdal ) );
		mgr->register_quest_script( 11549, CREATE_QUESTSCRIPT( ShatteredSun ) );
};