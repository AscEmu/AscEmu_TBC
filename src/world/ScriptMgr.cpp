/*
 * AscEmu MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2008 <http://www.AscEmu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "StdAfx.h"
#ifndef WIN32
    #include <dlfcn.h>
    #include <unistd.h>
    #include <dirent.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <cstdlib>
    #include <cstring>
#endif

#include <git_version.h>
#define SCRIPTLIB_HIPART(x) ((x >> 16))
#define SCRIPTLIB_LOPART(x) ((x & 0x0000ffff))
#define SCRIPTLIB_VERSION_MINOR (BUILD_REVISION % 1000)
#define SCRIPTLIB_VERSION_MAJOR (BUILD_REVISION / 1000)

initialiseSingleton(ScriptMgr);
initialiseSingleton(HookInterface);

ScriptMgr::ScriptMgr()
{
	DefaultGossipScript = new GossipScript();
}

ScriptMgr::~ScriptMgr()
{

}

struct ScriptingEngine_dl
{
    AscEmu::DynLib* dl;
    exp_script_register InitializeCall;
    uint32 Type;

    ScriptingEngine_dl()
    {
        dl = NULL;
        InitializeCall = NULL;
        Type = 0;
    }
};

struct ScriptingEngine
{
#ifdef WIN32
	HMODULE Handle;
#else
	void* Handle;
#endif
	exp_script_register InitializeCall;
	uint32 Type;
};

void ScriptMgr::LoadScripts()
{
    if (HookInterface::getSingletonPtr() == NULL)
        new HookInterface;

    Log.Success("Server", "Loading External Script Libraries...");

    std::string Path;
    std::string FileMask;
    Path = PREFIX;
    Path += '/';
#ifdef WIN32
    /*Path = Config.MainConfig.GetStringDefault("Script", "BinaryLocation", "script_bin");
    Path += "\\";*/
    FileMask = ".dll";
#else
#ifndef __APPLE__
    FileMask = ".so";
#else
    FileMask = ".dylib";
#endif
#endif

    AscEmu::FindFilesResult findres;
    std::vector< ScriptingEngine_dl > Engines;

    AscEmu::FindFiles(Path.c_str(), FileMask.c_str(), findres);
    uint32 count = 0;

    while (findres.HasNext())
    {
        std::stringstream loadmessage;
        std::string fname = Path + findres.GetNext();
        AscEmu::DynLib* dl = new AscEmu::DynLib(fname.c_str());

        loadmessage << dl->GetName() << " : ";

        if (!dl->Load())
        {
            Log.Error("ScriptMgr", "Cannot open library.");
            delete dl;
            continue;

        }
        else
        {
            exp_get_version vcall = reinterpret_cast<exp_get_version>(dl->GetAddressForSymbol("_exp_get_version"));
            exp_script_register rcall = reinterpret_cast<exp_script_register>(dl->GetAddressForSymbol("_exp_script_register"));
            exp_get_script_type scall = reinterpret_cast<exp_get_script_type>(dl->GetAddressForSymbol("_exp_get_script_type"));

            if ((vcall == NULL) || (rcall == NULL) || (scall == NULL))
            {
                Log.Error("ScriptMgr", "Cannot find version functions.");
                delete dl;
                continue;
            }
            else
            {
                const char *version = vcall();
                uint32 stype = scall();

                if (strcmp(version, BUILD_HASH_STR) != 0)
                {
                    Log.Error("ScriptMgr", "ERROR: Version mismatch.");
                    delete dl;
                    continue;

                }
                else
                {
                    loadmessage << std::string(BUILD_HASH_STR) << " : ";

                    if ((stype & SCRIPT_TYPE_SCRIPT_ENGINE) != 0)
                    {
                        ScriptingEngine_dl se;

                        se.dl = dl;
                        se.InitializeCall = rcall;
                        se.Type = stype;

                        Engines.push_back(se);

                        loadmessage << "delayed load";

                    }
                    else
                    {
                        rcall(this);
                        dynamiclibs.push_back(dl);

                        loadmessage << "loaded";
                    }
                    //LOG_BASIC(loadmessage.str().c_str());
                    count++;
                }
            }
        }
    }

    if (count == 0)
    {
        //LOG_ERROR("No external scripts found! Server will continue to function with limited functionality.");
    }
    else
    {
        Log.Success("Server", "Loaded %u external libraries.", count);
        Log.Success("Server", "Loading optional scripting engine(s)...");

        for (std::vector< ScriptingEngine_dl >::iterator itr = Engines.begin(); itr != Engines.end(); ++itr)
        {
            itr->InitializeCall(this);
            dynamiclibs.push_back(itr->dl);
        }

        Log.Success("Server", "Done loading scripting engine(s)...");
    }
}

void ScriptMgr::UnloadScripts()
{
	if(HookInterface::getSingletonPtr())
		delete HookInterface::getSingletonPtr();

	for(CustomGossipScripts::iterator itr = _customgossipscripts.begin(); itr != _customgossipscripts.end(); ++itr)
		(*itr)->Destroy();
	_customgossipscripts.clear();
	delete this->DefaultGossipScript;
	this->DefaultGossipScript=NULL;

	LibraryHandleMap::iterator itr = _handles.begin();
	for(; itr != _handles.end(); ++itr)
	{
#ifdef WIN32
		FreeLibrary(((HMODULE)*itr));
#else
		dlclose(*itr);
#endif
	}
	_handles.clear();
}

void ScriptMgr::register_creature_script(uint32 entry, exp_create_creature_ai callback)
{
	_creatures.insert( CreatureCreateMap::value_type( entry, callback ) );
}

void ScriptMgr::register_gameobject_script(uint32 entry, exp_create_gameobject_ai callback)
{
	_gameobjects.insert( GameObjectCreateMap::value_type( entry, callback ) );
}

void ScriptMgr::register_dummy_aura(uint32 entry, exp_handle_dummy_aura callback)
{
	_auras.insert( HandleDummyAuraMap::value_type( entry, callback ) );
}

void ScriptMgr::register_dummy_spell(uint32 entry, exp_handle_dummy_spell callback)
{
	_spells.insert( HandleDummySpellMap::value_type( entry, callback ) );
}

void ScriptMgr::register_gossip_script(uint32 entry, GossipScript * gs)
{
	CreatureInfo * ci = CreatureNameStorage.LookupEntry(entry);
	if(ci)
		ci->gossip_script = gs;

	_customgossipscripts.insert(gs);
}

void ScriptMgr::register_go_gossip_script(uint32 entry, GossipScript * gs)
{
	GameObjectInfo * gi = GameObjectNameStorage.LookupEntry(entry);
	if(gi)
		gi->gossip_script = gs;

	_customgossipscripts.insert(gs);
}

void ScriptMgr::register_quest_script(uint32 entry, QuestScript * qs)
{
	Quest * q = QuestStorage.LookupEntry( entry );
	if( q != NULL )
		q->pQuestScript = qs;

	_questscripts.insert( qs );
}

CreatureAIScript* ScriptMgr::CreateAIScriptClassForEntry(Creature* pCreature)
{
	CreatureCreateMap::iterator itr = _creatures.find(pCreature->GetEntry());
	if(itr == _creatures.end())
		return NULL;

	exp_create_creature_ai function_ptr = itr->second;
	return (function_ptr)(pCreature);
}

GameObjectAIScript * ScriptMgr::CreateAIScriptClassForGameObject(uint32 uEntryId, GameObject* pGameObject)
{
	GameObjectCreateMap::iterator itr = _gameobjects.find(pGameObject->GetEntry());
	if(itr == _gameobjects.end())
		return NULL;

	exp_create_gameobject_ai function_ptr = itr->second;
	return (function_ptr)(pGameObject);
}

bool ScriptMgr::CallScriptedDummySpell(uint32 uSpellId, uint32 i, Spell* pSpell)
{
	HandleDummySpellMap::iterator itr = _spells.find(uSpellId);
	if(itr == _spells.end())
		return false;

	exp_handle_dummy_spell function_ptr = itr->second;
	return (function_ptr)(i, pSpell);
}

bool ScriptMgr::CallScriptedDummyAura(uint32 uSpellId, uint32 i, Aura* pAura, bool apply)
{
	HandleDummyAuraMap::iterator itr = _auras.find(uSpellId);
	if(itr == _auras.end())
		return false;

	exp_handle_dummy_aura function_ptr = itr->second;
	return (function_ptr)(i, pAura, apply);
}

bool ScriptMgr::CallScriptedItem(Item * pItem, Player * pPlayer)
{
	if(pItem->GetProto() && pItem->GetProto()->gossip_script)
	{
		pItem->GetProto()->gossip_script->GossipHello(pItem,pPlayer,true);
		return true;
	}
	
	return false;
}

void ScriptMgr::register_item_gossip_script(uint32 entry, GossipScript * gs)
{
	ItemPrototype * proto = ItemPrototypeStorage.LookupEntry(entry);
	if(proto)
		proto->gossip_script = gs;

	_customgossipscripts.insert(gs);
}

/* CreatureAI Stuff */
CreatureAIScript::CreatureAIScript(Creature* creature) : _unit(creature)
{

}

void CreatureAIScript::RegisterAIUpdateEvent(uint32 frequency)
{
	//sEventMgr.AddEvent(_unit, &Creature::CallScriptUpdate, EVENT_SCRIPT_UPDATE_EVENT, frequency, 0,0);
	sEventMgr.AddEvent(_unit, &Creature::CallScriptUpdate, EVENT_SCRIPT_UPDATE_EVENT, frequency, 0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
}

void CreatureAIScript::ModifyAIUpdateEvent(uint32 newfrequency)
{
	sEventMgr.ModifyEventTimeAndTimeLeft(_unit, EVENT_SCRIPT_UPDATE_EVENT, newfrequency);
}

void CreatureAIScript::RemoveAIUpdateEvent()
{
	sEventMgr.RemoveEvents(_unit, EVENT_SCRIPT_UPDATE_EVENT);
}

/* GameObjectAI Stuff */

GameObjectAIScript::GameObjectAIScript(GameObject* goinstance) : _gameobject(goinstance)
{

}

void GameObjectAIScript::ModifyAIUpdateEvent(uint32 newfrequency)
{
	sEventMgr.ModifyEventTimeAndTimeLeft(_gameobject, EVENT_SCRIPT_UPDATE_EVENT, newfrequency);
}
 
void GameObjectAIScript::RemoveAIUpdateEvent()
{
	sEventMgr.RemoveEvents(_gameobject, EVENT_SCRIPT_UPDATE_EVENT);
}

void GameObjectAIScript::RegisterAIUpdateEvent(uint32 frequency)
{
	sEventMgr.AddEvent(_gameobject, &GameObject::CallScriptUpdate, EVENT_SCRIPT_UPDATE_EVENT, frequency, 0,0);
}


/* InstanceAI Stuff */

InstanceScript::InstanceScript(MapMgr *instance) : _instance(instance)
{
}

/* QuestScript Stuff */

/* Gossip Stuff*/

GossipScript::GossipScript()
{
	
}

void GossipScript::GossipEnd(Object* pObject, Player* Plr)
{
	Plr->CleanupGossipMenu();
}

bool CanTrainAt(Player * plr, Trainer * trn);
void GossipScript::GossipHello(Object* pObject, Player* Plr, bool AutoSend)
{
	GossipMenu *Menu;
	uint32 TextID = 2;
	Creature * pCreature = (pObject->GetTypeId()==TYPEID_UNIT)?static_cast< Creature* >( pObject ):NULL;
	if(!pCreature)
		return;

	Trainer *pTrainer = pCreature->GetTrainer();
	uint32 Text = objmgr.GetGossipTextForNpc(pCreature->GetEntry());
	if(Text != 0)
	{
		GossipText * text = NpcTextStorage.LookupEntry(Text);
		if(text != 0)
			TextID = Text;
	}

	objmgr.CreateGossipMenuForPlayer(&Menu, pCreature->GetGUID(), TextID, Plr);
	
	uint32 flags = pCreature->GetUInt32Value(UNIT_NPC_FLAGS);

	if(flags & UNIT_NPC_FLAG_VENDOR)
		Menu->AddItem(1, Plr->GetSession()->LocalizedWorldSrv(1), 1);
	
	if((flags & UNIT_NPC_FLAG_TRAINER || flags & UNIT_NPC_FLAG_TRAINER_PROF || flags & UNIT_NPC_FLAG_TRAINER_CLASS) && pTrainer != 0)
	{
        std::string name = pCreature->GetCreatureInfo()->Name;
        std::string::size_type pos = name.find(" ");	  // only take first name
        if (pos != std::string::npos)
			name = name.substr(0, pos);

		if(CanTrainAt(Plr, pTrainer))
			Menu->SetTextID(pTrainer->Can_Train_Gossip_TextId);
		else
			Menu->SetTextID(pTrainer->Cannot_Train_GossipTextId);
        if(pTrainer->TrainerType != TRAINER_TYPE_PET)
		{
            std::string msg = std::string(Plr->GetSession()->LocalizedWorldSrv(2));
			if(pTrainer->RequiredClass)
			{
				switch(Plr->getClass())
				{
				case MAGE:
                    msg += std::string(Plr->GetSession()->LocalizedWorldSrv(3));
					break;
				case SHAMAN:
                    msg += std::string(Plr->GetSession()->LocalizedWorldSrv(4));
					break;
				case WARRIOR:
                    msg += std::string(Plr->GetSession()->LocalizedWorldSrv(5));
					break;
				case PALADIN:
                    msg += std::string(Plr->GetSession()->LocalizedWorldSrv(6));
					break;
				case WARLOCK:
                    msg += std::string(Plr->GetSession()->LocalizedWorldSrv(7));
					break;
				case HUNTER:
                    msg += std::string(Plr->GetSession()->LocalizedWorldSrv(8));
					break;
				case ROGUE:
                    msg += std::string(Plr->GetSession()->LocalizedWorldSrv(9));
					break;
				case DRUID:
                    msg += std::string(Plr->GetSession()->LocalizedWorldSrv(10));
					break;
				case PRIEST:
                    msg += std::string(Plr->GetSession()->LocalizedWorldSrv(11));
					break;
				}
                msg += " " + std::string(Plr->GetSession()->LocalizedWorldSrv(12)) + ", ";
				msg += name;
				msg += ".";

				Menu->AddItem(3, msg.c_str(), 2);

			}
			else
			{
                msg += std::string(Plr->GetSession()->LocalizedWorldSrv(12)) + ", ";
				msg += name;
				msg += ".";

				Menu->AddItem(3, msg.c_str(), 2);
			}
		}
		else
		{
			
			Menu->AddItem(3, Plr->GetSession()->LocalizedWorldSrv(13), 2);
		}
	}

	if(flags & UNIT_NPC_FLAG_TAXIVENDOR)
		Menu->AddItem(2, Plr->GetSession()->LocalizedWorldSrv(14), 3);

	if(flags & UNIT_NPC_FLAG_AUCTIONEER)
		Menu->AddItem(0, Plr->GetSession()->LocalizedWorldSrv(15), 4);

	if(flags & UNIT_NPC_FLAG_INNKEEPER)
		Menu->AddItem(5, Plr->GetSession()->LocalizedWorldSrv(16), 5);

	if(flags & UNIT_NPC_FLAG_BANKER)
		Menu->AddItem(0, Plr->GetSession()->LocalizedWorldSrv(17), 6);

	if(flags & UNIT_NPC_FLAG_SPIRITHEALER)
		Menu->AddItem(0, Plr->GetSession()->LocalizedWorldSrv(18), 7);

	if(flags & UNIT_NPC_FLAG_ARENACHARTER)
		Menu->AddItem(0, Plr->GetSession()->LocalizedWorldSrv(19), 8);

	if(flags & UNIT_NPC_FLAG_TABARDCHANGER)
		Menu->AddItem(0, Plr->GetSession()->LocalizedWorldSrv(20), 9);

	if(flags & UNIT_NPC_FLAG_BATTLEFIELDPERSON)
		Menu->AddItem(0, Plr->GetSession()->LocalizedWorldSrv(21), 10);

	if( pTrainer &&
		pTrainer->RequiredClass &&					  // class trainer
		pTrainer->RequiredClass == Plr->getClass() &&   // correct class
		pCreature->getLevel() > 10 &&				   // creature level
		pTrainer->TrainerType != TRAINER_TYPE_PET &&  // Pet Trainers do not respec hunter talents
		Plr->getLevel() > 10 )						  // player level
	{
		Menu->AddItem(0, Plr->GetSession()->LocalizedWorldSrv(22), 11);
	}
	
	if( pTrainer &&
		pTrainer->TrainerType == TRAINER_TYPE_PET &&	// pet trainer type
		Plr->getClass() == HUNTER &&					// hunter class
		Plr->GetSummon() != NULL )						// have pet
	{
		Menu->AddItem(0, Plr->GetSession()->LocalizedWorldSrv(23), 13);
	}

	if(AutoSend)
		Menu->SendTo(Plr);
}

void GossipScript::GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char * EnteredCode)
{
	Creature* pCreature = static_cast< Creature* >( pObject );
	if( pObject->GetTypeId() != TYPEID_UNIT )
		return;

	switch( IntId )
	{
	case 1:
		// vendor
		Plr->GetSession()->SendInventoryList(pCreature);
		break;
	case 2:
		// trainer
		Plr->GetSession()->SendTrainerList(pCreature);
		break;
	case 3:
		// taxi
		Plr->GetSession()->SendTaxiList(pCreature);
		break;
	case 4:
		// auction
		Plr->GetSession()->SendAuctionList(pCreature);
		break;
	case 5:
		// innkeeper
		Plr->GetSession()->SendInnkeeperBind(pCreature);
		break;
	case 6:
		// banker
		Plr->GetSession()->SendBankerList(pCreature);
		break;
	case 7:
		// spirit
		Plr->GetSession()->SendSpiritHealerRequest(pCreature);
		break;
	case 8:
		// petition
		Plr->GetSession()->SendCharterRequest(pCreature);
		break;
	case 9:
		// guild crest
		Plr->GetSession()->SendTabardHelp(pCreature);
		break;
	case 10:
		// battlefield
		Plr->GetSession()->SendBattlegroundList(pCreature, 0);
		break;
	case 11:
		// switch to talent reset message
		{
			GossipMenu *Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pCreature->GetGUID(), 5674, Plr);
			Menu->AddItem(0, Plr->GetSession()->LocalizedWorldSrv(24), 12);
			Menu->SendTo(Plr);
		}break;
	case 12:
		// talent reset
		{
			Plr->Gossip_Complete();
			Plr->SendTalentResetConfirm();
		}break;
	case 13:
		// switch to untrain message
		{
			GossipMenu *Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pCreature->GetGUID(), 7722, Plr);
			Menu->AddItem(0, Plr->GetSession()->LocalizedWorldSrv(25), 14);
			Menu->SendTo(Plr);
		}break;
	case 14:
		// untrain pet
		{
			Plr->Gossip_Complete();
			Plr->SendPetUntrainConfirm();
		}break;

	default:
		sLog.outError("Unknown IntId %u on entry %u", IntId, pCreature->GetEntry());
		break;
	}	
}

void GossipScript::Destroy()
{
	delete this;
}

void ScriptMgr::register_hook(ServerHookEvents event, void * function_pointer)
{
	ASSERT(event < NUM_SERVER_HOOKS);
	_hooks[event].push_back(function_pointer);
}

/* Hook Implementations */
#define OUTER_LOOP_BEGIN(type, fptr_type) if(!sScriptMgr._hooks[type].size()) { \
	return; } \
	fptr_type call; \
	for(ServerHookList::iterator itr = sScriptMgr._hooks[type].begin(); itr != sScriptMgr._hooks[type].end(); ++itr) { \
	call = ((fptr_type)*itr);

#define OUTER_LOOP_END }

#define OUTER_LOOP_BEGIN_COND(type, fptr_type) if(!sScriptMgr._hooks[type].size()) { \
	return true; } \
	fptr_type call; \
	bool ret_val = true; \
	for(ServerHookList::iterator itr = sScriptMgr._hooks[type].begin(); itr != sScriptMgr._hooks[type].end(); ++itr) { \
		call = ((fptr_type)*itr);

#define OUTER_LOOP_END_COND } return ret_val;

bool HookInterface::OnNewCharacter(uint32 Race, uint32 Class, WorldSession * Session, const char * Name)
{
	OUTER_LOOP_BEGIN_COND(SERVER_HOOK_EVENT_ON_NEW_CHARACTER, tOnNewCharacter)
		ret_val = (call)(Race, Class, Session, Name);
	OUTER_LOOP_END_COND
}

void HookInterface::OnKillPlayer(Player * pPlayer, Player * pVictim)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_KILL_PLAYER, tOnKillPlayer)
		(call)(pPlayer, pVictim);
	OUTER_LOOP_END
}

void HookInterface::OnFirstEnterWorld(Player * pPlayer)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_FIRST_ENTER_WORLD, tOnFirstEnterWorld)
		(call)(pPlayer);
	OUTER_LOOP_END
}

void HookInterface::OnCharacterCreate(Player * pPlayer)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_CHARACTER_CREATE, tOCharacterCreate)
		(call)(pPlayer);
	OUTER_LOOP_END
}

void HookInterface::OnEnterWorld(Player * pPlayer)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_ENTER_WORLD, tOnEnterWorld)
		(call)(pPlayer);
	OUTER_LOOP_END
}

void HookInterface::OnGuildCreate(Player * pLeader, Guild * pGuild)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_GUILD_CREATE, tOnGuildCreate)
		(call)(pLeader, pGuild);
	OUTER_LOOP_END
}

void HookInterface::OnGuildJoin(Player * pPlayer, Guild * pGuild)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_GUILD_JOIN, tOnGuildJoin)
		(call)(pPlayer, pGuild);
	OUTER_LOOP_END
}

void HookInterface::OnDeath(Player * pPlayer)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_DEATH, tOnDeath)
		(call)(pPlayer);
	OUTER_LOOP_END
}

bool HookInterface::OnRepop(Player * pPlayer)
{
	OUTER_LOOP_BEGIN_COND(SERVER_HOOK_EVENT_ON_REPOP, tOnRepop)
		ret_val = (call)(pPlayer);
	OUTER_LOOP_END_COND
}

void HookInterface::OnEmote(Player * pPlayer, uint32 Emote, Unit * pUnit)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_EMOTE, tOnEmote)
		(call)(pPlayer, Emote, pUnit);
	OUTER_LOOP_END
}

void HookInterface::OnEnterCombat(Player * pPlayer, Unit * pTarget)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_ENTER_COMBAT, tOnEnterCombat)
		(call)(pPlayer, pTarget);
	OUTER_LOOP_END
}

bool HookInterface::OnCastSpell(Player * pPlayer, SpellEntry* pSpell)
{
	OUTER_LOOP_BEGIN_COND(SERVER_HOOK_EVENT_ON_CAST_SPELL, tOnCastSpell)
		ret_val = (call)(pPlayer, pSpell);
	OUTER_LOOP_END_COND
}

bool HookInterface::OnLogoutRequest(Player * pPlayer)
{
	OUTER_LOOP_BEGIN_COND(SERVER_HOOK_EVENT_ON_LOGOUT_REQUEST, tOnLogoutRequest)
		ret_val = (call)(pPlayer);
	OUTER_LOOP_END_COND
}

void HookInterface::OnLogout(Player * pPlayer)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_LOGOUT, tOnLogout)
		(call)(pPlayer);
	OUTER_LOOP_END
}

void HookInterface::OnQuestAccept(Player * pPlayer, Quest * pQuest, Object * pQuestGiver)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_QUEST_ACCEPT, tOnQuestAccept)
		(call)(pPlayer, pQuest, pQuestGiver);
	OUTER_LOOP_END
}

void HookInterface::OnZone(Player * pPlayer, uint32 Zone)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_ZONE, tOnZone)
		(call)(pPlayer, Zone);
	OUTER_LOOP_END
}

bool HookInterface::OnChat(Player * pPlayer, uint32 Type, uint32 Lang, const char * Message, const char * Misc)
{
	OUTER_LOOP_BEGIN_COND(SERVER_HOOK_EVENT_ON_CHAT, tOnChat)
		ret_val = (call)(pPlayer, Type, Lang, Message, Misc);
	OUTER_LOOP_END_COND
}

void HookInterface::OnLoot(Player * pPlayer, Unit * pTarget, uint32 Money, uint32 ItemId)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_LOOT, tOnLoot)
		(call)(pPlayer, pTarget, Money, ItemId);
	OUTER_LOOP_END
}

void HookInterface::OnObjectLoot(Player * pPlayer, Object * pTarget, uint32 Money, uint32 ItemId)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_OBJECTLOOT, tOnObjectLoot)
		(call)(pPlayer, pTarget, Money, ItemId);
	OUTER_LOOP_END
}

void HookInterface::OnEnterWorld2(Player * pPlayer)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_ENTER_WORLD_2, tOnEnterWorld)
		(call)(pPlayer);
	OUTER_LOOP_END
}

void HookInterface::OnQuestCancelled(Player * pPlayer, Quest * pQuest)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_QUEST_CANCELLED, tOnQuestCancel)
		(call)(pPlayer, pQuest);
	OUTER_LOOP_END
}

void HookInterface::OnQuestFinished(Player * pPlayer, Quest * pQuest, Object * pQuestGiver)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_QUEST_FINISHED, tOnQuestFinished)
		(call)(pPlayer, pQuest, pQuestGiver);
	OUTER_LOOP_END
}

void HookInterface::OnHonorableKill(Player * pPlayer, Player * pKilled)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_HONORABLE_KILL, tOnHonorableKill)
		(call)(pPlayer, pKilled);
	OUTER_LOOP_END
}

void HookInterface::OnArenaFinish(Player * pPlayer, ArenaTeam* pTeam, bool victory, bool rated)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_ARENA_FINISH, tOnArenaFinish)
		(call)(pPlayer, pTeam, victory, rated);
	OUTER_LOOP_END
}

void HookInterface::OnAreaTrigger(Player * pPlayer, uint32 areaTrigger)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_AREATRIGGER, tOnAreaTrigger)
		(call)(pPlayer, areaTrigger);
	OUTER_LOOP_END
}

void HookInterface::OnPostLevelUp(Player * pPlayer)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_POST_LEVELUP, tOnPostLevelUp)
		(call)(pPlayer);
	OUTER_LOOP_END
}

void HookInterface::OnPreUnitDie(Unit *Killer, Unit *Victim)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_PRE_DIE, tOnPreUnitDie)
		(call)(Killer, Victim);
	OUTER_LOOP_END
}

void HookInterface::OnAdvanceSkillLine(Player * pPlayer, uint32 SkillLine, uint32 Current)
{
	OUTER_LOOP_BEGIN(SERVER_HOOK_EVENT_ON_ADVANCE_SKILLLINE, tOnAdvanceSkillLine)
		(call)(pPlayer, SkillLine, Current);
	OUTER_LOOP_END
}
