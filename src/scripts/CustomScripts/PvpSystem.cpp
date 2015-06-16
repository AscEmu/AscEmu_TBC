#include "StdAfx.h"
#include "Setup.h"

class SCRIPT_DECL PvPCreatureGossip : public GossipScript
{
public:
    void GossipHello(Object* pObject, Player* pPlayer, bool AutoSend)
    {
		GossipMenu *Menu;
		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, pPlayer);

		if( pPlayer->m_arenaTeams[ARENA_TEAM_TYPE_2V2]->HasMember( pPlayer->GetLowGUID() ) ||
			pPlayer->m_arenaTeams[ARENA_TEAM_TYPE_3V3]->HasMember( pPlayer->GetLowGUID() ) ||
			pPlayer->m_arenaTeams[ARENA_TEAM_TYPE_5V5]->HasMember( pPlayer->GetLowGUID() ) )			
			Menu->AddItem( 0, "Give me arena title i deserve!", 2);

		if (AutoSend)
			Menu->SendTo(pPlayer);
	};

	void GossipSelectOption(Object* pObject, Player* pPlayer, uint32 Id, uint32 IntId, const char * EnteredCode)
    {
		if( IntId == 0 )
		{
			if( pPlayer->m_arenaTeams[ARENA_TEAM_TYPE_2V2]->GetMemberByGuid(  pPlayer->GetLowGUID() )->PersonalRating >= 1650 ||
				pPlayer->m_arenaTeams[ARENA_TEAM_TYPE_3V3]->GetMemberByGuid(  pPlayer->GetLowGUID() )->PersonalRating >= 1650 ||
				pPlayer->m_arenaTeams[ARENA_TEAM_TYPE_5V5]->GetMemberByGuid(  pPlayer->GetLowGUID() )->PersonalRating >= 1650 )	
			{
				uint32 _2v2 = 0;
				uint32 _3v3 = 0;
				uint32 _5v5 = 0;

				if( pPlayer->m_arenaTeams[ARENA_TEAM_TYPE_2V2]->HasMember(  pPlayer->GetLowGUID() ) )
					 _2v2 = pPlayer->m_arenaTeams[ARENA_TEAM_TYPE_2V2]->GetMemberByGuid( pPlayer->GetLowGUID() )->PersonalRating;
				
				if( pPlayer->m_arenaTeams[ARENA_TEAM_TYPE_3V3]->HasMember(  pPlayer->GetLowGUID() ) )
					 _3v3 = pPlayer->m_arenaTeams[ARENA_TEAM_TYPE_3V3]->GetMemberByGuid( pPlayer->GetLowGUID() )->PersonalRating;

				if( pPlayer->m_arenaTeams[ARENA_TEAM_TYPE_5V5]->HasMember(  pPlayer->GetLowGUID() ) )
					 _5v5 = pPlayer->m_arenaTeams[ARENA_TEAM_TYPE_5V5]->GetMemberByGuid( pPlayer->GetLowGUID() )->PersonalRating;

				if( pPlayer->HasKnownTitle( PVPTITLE_CHALLENGER ) )
				{
					pPlayer->BroadcastMessage( "You already have titles for your raiting!" );
					return;
				}
				else
				{
					pPlayer->SetKnownTitle( PVPTITLE_CHALLENGER, true );
					pPlayer->BroadcastMessage( "You have earned a title 'Challenger' for having personal arena rating bigger than 1650." );
				};

				if( ( _2v2 >= 1800 || _3v3 >= 1800 || _5v5 >= 1800 )  )
				{
					if( pPlayer->HasKnownTitle( PVPTITLE_RIVAL ) )
					{
						pPlayer->BroadcastMessage( "You already have titles for your raiting!" );
						return;
					}
					else
					{
						pPlayer->SetKnownTitle( PVPTITLE_RIVAL, true );
						pPlayer->BroadcastMessage( "You have earned a title 'Rival' for having personal arena rating bigger than 1800." );
				
					};
				};

				if( ( _2v2 >= 2000 || _3v3 >= 2000 || _5v5 >= 2000 )  )
				{
					if( pPlayer->HasKnownTitle( PVPTITLE_DUELIST ) )
					{
						pPlayer->BroadcastMessage( "You already have titles for your raiting!" );
						return;
					}
					else
					{
						pPlayer->SetKnownTitle( PVPTITLE_DUELIST, true );
						pPlayer->BroadcastMessage( "You have earned a title 'Duelist' for having personal arena rating bigger than 2000." );
				
					};
				};
			}
			else
			{
				pPlayer->BroadcastMessage( "You must have personal arena rating bigger than 1650 to earn a title!" );
			};
		};
	};
};

void OnKillEnemy(Player * pPlayer, Player * pKilled)
{
	if( pPlayer == NULL )
		return;
		
	if( pKilled != NULL )
	{
		pPlayer->UpdateKillStreak();
		pKilled->ResetKillStreak();
		
		switch( pPlayer->GetKillsStreak() )
		{
        case 10:
            {
                pPlayer->SetKnownTitle( PVPTITLE_GLADIATOR, true  );
		        pPlayer->BroadcastMessage( "You have earned new title for 10 kill streak!" );
            }break;
        case 15:
            {
                pPlayer->SetKnownTitle( PVPTITLE_MERCILESS_GLADIATOR, true  );
		        pPlayer->BroadcastMessage( "You have earned new title for 15 kill streak!" );
            }break;
        case 20:
            {
                pPlayer->SetKnownTitle( PVPTITLE_VENGEFUL_GLADIATOR, true  );
		        pPlayer->BroadcastMessage( "You have earned new title for 20 kill streak!" );
            }break;
		};
		
	};

	uint32 kills = pPlayer->m_killsLifetime;
	if( kills >= 250 && ( !pPlayer->HasKnownTitle( TITLE_SCOUT ) && !pPlayer->HasKnownTitle( TITLE_PRIVATE ) ) )
	{
		pPlayer->SetKnownTitle( pPlayer->GetTeam() ? Title_SCOUT : TITLE_PRIVATE, true  );
		pPlayer->BroadcastMessage( "You have earned new title , please relog for the title to be added you will only need to relog once for this ." );
	};
	
	if( kills >= 500 && !pPlayer->HasKnownTitle( PVPTITLE_GRUNT ) && !pPlayer->HasKnownTitle( PVPTITLE_CORPORAL ) )
	{
		pPlayer->SetKnownTitle( pPlayer->GetTeam() ? PVPTITLE_GRUNT : PVPTITLE_CORPORAL, true  );
		pPlayer->BroadcastMessage( "You have earned new title!" );
	};

	if( kills >= 1000 && !pPlayer->HasKnownTitle( PVPTITLE_HSERGEANT ) && !pPlayer->HasKnownTitle( PVPTITLE_SERGEANT ) )
	{
		pPlayer->SetKnownTitle( pPlayer->GetTeam() ? PVPTITLE_SERGEANT : PVPTITLE_HSERGEANT, true  );
		pPlayer->BroadcastMessage( "You have earned new title!" );
	};

	if( kills >= 2000 && !pPlayer->HasKnownTitle( PVPTITLE_SENIOR_SERGEANT ) && !pPlayer->HasKnownTitle( PVPTITLE_MASTER_SERGEANT ) )
	{
		pPlayer->SetKnownTitle( pPlayer->GetTeam() ? PVPTITLE_SENIOR_SERGEANT : PVPTITLE_MASTER_SERGEANT, true  );
		pPlayer->BroadcastMessage( "You have earned new title!" );
	};

	if( kills >= 4000 && !pPlayer->HasKnownTitle( PVPTITLE_FIRST_SERGEANT ) && !pPlayer->HasKnownTitle( PVPTITLE_SERGEANT_MAJOR ) )
	{
		pPlayer->SetKnownTitle( pPlayer->GetTeam() ? PVPTITLE_FIRST_SERGEANT : PVPTITLE_SERGEANT_MAJOR , true  );
		pPlayer->BroadcastMessage( "You have earned new title!" );
	};

	if( kills >= 7500 && !pPlayer->HasKnownTitle( PVPTITLE_KNIGHT ) && !pPlayer->HasKnownTitle( PVPTITLE_STONE_GUARD ) )
	{
		pPlayer->SetKnownTitle( pPlayer->GetTeam() ? PVPTITLE_STONE_GUARD : PVPTITLE_KNIGHT, true  );
		pPlayer->BroadcastMessage( "You have earned new title!" );
	};

	if( kills >= 9000 && !pPlayer->HasKnownTitle( PVPTITLE_KNIGHT_LIEUTENANT ) && !pPlayer->HasKnownTitle( PVPTITLE_BLOOD_GUARD ) )
	{
		pPlayer->SetKnownTitle( pPlayer->GetTeam() ? PVPTITLE_BLOOD_GUARD : PVPTITLE_KNIGHT_LIEUTENANT, true  );
		pPlayer->BroadcastMessage( "You have earned new title!" );
	};

	if( kills >= 15000 && !pPlayer->HasKnownTitle( PVPTITLE_KNIGHT_CAPTAIN ) && !pPlayer->HasKnownTitle( PVPTITLE_LEGIONNAIRE ) )
	{
		pPlayer->SetKnownTitle( pPlayer->GetTeam() ? PVPTITLE_LEGIONNAIRE : PVPTITLE_KNIGHT_CAPTAIN, true  );
		pPlayer->BroadcastMessage( "You have earned new title!" );
	};

	if( kills >= 30000 && !pPlayer->HasKnownTitle( PVPTITLE_KNIGHT_CHAMPION ) && !pPlayer->HasKnownTitle( PVPTITLE_CENTURION ) )
	{
		pPlayer->SetKnownTitle( pPlayer->GetTeam() ? PVPTITLE_CENTURION : PVPTITLE_KNIGHT_CHAMPION, true  );
		pPlayer->BroadcastMessage( "You have earned new title!" );
	};

	if( kills >= 40000 && !pPlayer->HasKnownTitle( PVPTITLE_LIEUTENANT_COMMANDER ) && !pPlayer->HasKnownTitle( PVPTITLE_CHAMPION ) )
	{
		pPlayer->SetKnownTitle( pPlayer->GetTeam() ? PVPTITLE_CHAMPION : PVPTITLE_LIEUTENANT_COMMANDER, true  );
		pPlayer->BroadcastMessage( "You have earned new title!" );
	};

	if( kills >= 50000 && !pPlayer->HasKnownTitle( PVPTITLE_COMMANDER ) && !pPlayer->HasKnownTitle( PVPTITLE_LIEUTENANT_GENERAL ) )
	{
		pPlayer->SetKnownTitle( pPlayer->GetTeam() ? PVPTITLE_LIEUTENANT_GENERAL : PVPTITLE_COMMANDER, true  );
		pPlayer->BroadcastMessage( "You have earned new title!" );
	};

	if( kills >= 60000 && !pPlayer->HasKnownTitle( PVPTITLE_MARSHAL ) && !pPlayer->HasKnownTitle( PVPTITLE_GENERAL ) )
	{
		pPlayer->SetKnownTitle( pPlayer->GetTeam() ? PVPTITLE_GENERAL : PVPTITLE_MARSHAL, true  );
		pPlayer->BroadcastMessage( "You have earned new title!" );
	};

	if( kills >= 70000 && !pPlayer->HasKnownTitle( PVPTITLE_FIELD_MARSHAL ) && !pPlayer->HasKnownTitle( PVPTITLE_WARLORD ) )
	{
		pPlayer->SetKnownTitle( pPlayer->GetTeam() ? PVPTITLE_WARLORD : PVPTITLE_FIELD_MARSHAL, true  );
		pPlayer->BroadcastMessage( "You have earned new title!" );
	};

	if( kills >= 80000 && !pPlayer->HasKnownTitle( PVPTITLE_GRAND_MARSHAL ) && !pPlayer->HasKnownTitle( PVPTITLE_WARLORD ) )
	{
		pPlayer->SetKnownTitle( pPlayer->GetTeam() ? PVPTITLE_HIGH_WARLORD : PVPTITLE_GRAND_MARSHAL, true  );
		pPlayer->BroadcastMessage( "You have earned new title!" );
	};

	if( kills >= 1000000 && !pPlayer->HasKnownTitle( PVPTITLE_CONQUEROR ) )
	{
		pPlayer->SetKnownTitle( PVPTITLE_CONQUEROR, true  );
		pPlayer->BroadcastMessage( "You have earned title Conqueror for having 10000 honorable kills! Congratulations!" );
	};
};

void OnDeath(Player * pPlayer)
{
    if( !pPlayer )
        return;

    pPlayer->ResetKillStreak();
};

void SetupPvPSystem(ScriptMgr* mgr)
{
	GossipScript* Gossip = (GossipScript*) new PvPCreatureGossip();
	mgr->register_gossip_script( 98741, Gossip);

	mgr->register_hook(SERVER_HOOK_EVENT_ON_HONORABLE_KILL, (void *)&OnKillEnemy);
    mgr->register_hook(SERVER_HOOK_EVENT_ON_DEATH, (void *)&OnDeath);
};