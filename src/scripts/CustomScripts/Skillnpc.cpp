#include "StdAfx.h"
#include "Setup.h"

#ifdef WIN32
#pragma warning(disable:4305)// warning C4305: 'argument' : truncation from 'double' to 'float'
#endif


class SCRIPT_DECL SkillNPC : public GossipScript
{
public:
    void GossipHello(Object * pObject, Player* Plr, bool AutoSend);
    void GossipSelectOption(Object * pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code);
    void GossipEnd(Object * pObject, Player* Plr);
	void Destroy()
	{
		delete this;
	}
};
void SkillNPC::GossipHello(Object * pObject, Player* Plr, bool AutoSend)
	{
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);
		       
				if(!Plr->CombatStatus.IsInCombat())
					{
						Menu->AddItem(9, "Advance my weapon skills!", 1);
						Menu->AddItem(5, "Goodbye!", 5);
					}
					else
						Plr->BroadcastMessage("You are in combat!");
					
					    if(AutoSend)
							Menu->SendTo(Plr);
					};


void SkillNPC::GossipSelectOption(Object * pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
    {
	Creature * pCreature = (pObject->GetTypeId()==TYPEID_UNIT)?((Creature*)pObject):NULL;
	if(pCreature==NULL)
		return;

        switch(IntId)
        {
        case 0:
		GossipHello(pObject, Plr, true);
        break;

		case 5:
		{
		Plr->Gossip_Complete();//Ends Conversation
		}
		break;

		case 1:
		{
		if (Plr->_HasSkillLine(43))
			{Plr->_AdvanceSkillLine(43, 400);}//Swords

		if (Plr->_HasSkillLine(44))
			{Plr->_AdvanceSkillLine(44, 400);}//Axes

		if (Plr->_HasSkillLine(45))
			{Plr->_AdvanceSkillLine(45, 400);}//Bows

		if (Plr->_HasSkillLine(46))
			{Plr->_AdvanceSkillLine(46, 400);}//Guns

		if (Plr->_HasSkillLine(54))
			{Plr->_AdvanceSkillLine(54, 400);}//Maces

		if (Plr->_HasSkillLine(95))
			{Plr->_AdvanceSkillLine(95, 400);}//Defense

		if (Plr->_HasSkillLine(136))
			{Plr->_AdvanceSkillLine(136, 400);}//Staves

		if (Plr->_HasSkillLine(160))
			{Plr->_AdvanceSkillLine(160, 400);}//Two-Handed Swords

		if (Plr->_HasSkillLine(162))
			{Plr->_AdvanceSkillLine(162, 400);}//Unarmed

		if (Plr->_HasSkillLine(172))
			{Plr->_AdvanceSkillLine(172, 400);}//Two-Handed Axes

		if (Plr->_HasSkillLine(173))
			{Plr->_AdvanceSkillLine(173, 400);}//Daggers

		if (Plr->_HasSkillLine(176))
			{Plr->_AdvanceSkillLine(176, 400);}//Thrown

		if (Plr->_HasSkillLine(226))
			{Plr->_AdvanceSkillLine(226, 400);}//Crossbows

		if (Plr->_HasSkillLine(228))
			{Plr->_AdvanceSkillLine(228, 400);}//Wands

		if (Plr->_HasSkillLine(229))
			{Plr->_AdvanceSkillLine(229, 400);}//Polearms

		if (Plr->_HasSkillLine(473))
			{Plr->_AdvanceSkillLine(473, 400);}//Fist Weapons - I am not sure if this is a skill that is like the others, I thought fist weapons contributed towards unarmed.
			
		if (Plr->_HasSkillLine(633))
			{Plr->_AdvanceSkillLine(633, 400);}//Lockpicking - I know its not a weapon skill, but it's always a bitch to level.

			Plr->BroadcastMessage("You weapon skills have been advanced!");
			Plr->Gossip_Complete();
			}
 }
 }

void SkillNPC::GossipEnd(Object * pObject, Player* Plr)
{
    GossipScript::GossipEnd(pObject, Plr);
}

class SCRIPT_DECL BuffNPC : public GossipScript
{
public:
    void GossipHello(Object * pObject, Player* Plr, bool AutoSend)
    { 
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);
		       
        if(!Plr->CombatStatus.IsInCombat())
		{
	        Menu->AddItem(0, "Master Magic buff!", 1);
	        Menu->AddItem(0, "Master Melee buff!", 2);
            Menu->AddItem(0, "Master Ranged buff!", 3);
	    }
	    else
            Plr->BroadcastMessage("You are in combat!");
					
	    if(AutoSend)
	        Menu->SendTo(Plr);
    };

    void GossipSelectOption(Object * pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
    {
        switch( IntId )
        {
        case 1:
            Plr->CastSpell( Plr, 35912, true );
            break;
        case 2:
            Plr->CastSpell( Plr, 35874, true );
            break;
        case 3:
            Plr->CastSpell( Plr, 38734, true );
            break;
        };
    };

	void Destroy()
	{
		delete this;
	}
};

class SCRIPT_DECL MissingSkillNPC : public GossipScript{
public:
    void GossipHello(Object *pObject, Player *Plr, bool AutoSend);
    void GossipSelectOption(Object *pObject, Player *Plr, uint32 Id, uint32 IntId, const char *Code);
    void GossipEnd(Object *pObject, Player *Plr);
	void Destroy(){ delete this; }
};
void MissingSkillNPC::GossipEnd(Object * pObject, Player* Plr){ GossipScript::GossipEnd(pObject, Plr); }
void MissingSkillNPC::GossipHello(Object *pObject, Player *Plr, bool AutoSend){
	GossipMenu *Menu;
    objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);
				if (Plr->getClass() == 1) 
 { 
Menu->AddItem(0, "What spells can warriors learn?", 1);
 } 
				if (Plr->getClass() == 2)
 { 
Menu->AddItem(0, "What spells can paladins learn?", 2);
 }
				if (Plr->getClass() == 3)
 { 
Menu->AddItem(0, "What spells can hunters learn?", 3);
 }
				if (Plr->getClass() == 9)
 { 
Menu->AddItem(0, "What spells can warlocks learn?", 4);
 }
				if (Plr->getClass() == 11)
 { 
Menu->AddItem(0, "What spells can druids learn?", 5);
 }
				if (Plr->getClass() == 4) 
 { 
Menu->AddItem(0, "What spells can rogues learn?", 6);
 } 
				if (Plr->getClass() == 5) 
 { 
Menu->AddItem(0, "What spells can priests learn?", 7);
 } 
				if (Plr->getClass() == 7) 
 { 
Menu->AddItem(0, "What spells can shamans learn?", 8);
 } 
				if (Plr->getClass() == 8) 
 { 
Menu->AddItem(0, "What spells can mages learn?", 9);
 } 


Menu->AddItem(0, "Reset Talent Points", 98);

    Menu->SendTo(Plr);
}


void MissingSkillNPC::GossipSelectOption(Object *pObject, Player *Plr, uint32 Id, uint32 IntId, const char *Code){
	Creature * pCreature = (pObject->GetTypeId()==TYPEID_UNIT) ? ((Creature*)pObject) : NULL;
	GossipMenu * Menu;
	switch(IntId){
	case 0:     // Return to start
				GossipHello(pObject, Plr, true);
            break;

case 1:
objmgr.CreateGossipMenuForPlayer(&Menu, pCreature->GetGUID(), 1, Plr);
Menu->AddItem(5, "Taunt", 10);
Menu->AddItem(5, "Intercept", 13);
Menu->AddItem(5, "Defensive Stance", 11);
Menu->AddItem(5, "Beserker Stance", 12);
Menu->AddItem(0, "[Back]", 99);
Menu->SendTo(Plr);
break;

case 2:
objmgr.CreateGossipMenuForPlayer(&Menu, pCreature->GetGUID(), 1, Plr);
Menu->AddItem(5, "Redemption", 22);
Menu->AddItem(5, "Summon Warhorse", 20);
Menu->AddItem(5, "Summon Charger", 21);
Menu->AddItem(0, "[Back]", 99);
Menu->SendTo(Plr);
break;

case 3:
objmgr.CreateGossipMenuForPlayer(&Menu, pCreature->GetGUID(), 1, Plr);
Menu->AddItem(5, "Pet spells", 30);
Menu->AddItem(0, "[Back]", 99);
Menu->SendTo(Plr);
break;

case 4:
objmgr.CreateGossipMenuForPlayer(&Menu, pCreature->GetGUID(), 1, Plr);
Menu->AddItem(5, "Pet Spells", 40);
Menu->AddItem(5, "Summon Felstead", 41);
Menu->AddItem(5, "Summon Dreadstead", 42);
Menu->AddItem(0, "[Back]", 99);
Menu->SendTo(Plr);
break;

case 5:
objmgr.CreateGossipMenuForPlayer(&Menu, pCreature->GetGUID(), 1, Plr);
Menu->AddItem(5, "Bear Form", 54);
Menu->AddItem(5, "Dire Bear Form", 51);
Menu->AddItem(5, "Aquatic Form", 56);
Menu->AddItem(5, "Normal Flight Form", 52);
Menu->AddItem(5, "Epic Flight Form", 53); 
Menu->AddItem(0, "[Back]", 99);
Menu->SendTo(Plr);
break;

case 6:
objmgr.CreateGossipMenuForPlayer(&Menu, pCreature->GetGUID(), 1, Plr);
Menu->AddItem(0, "[Back]", 99);
Menu->SendTo(Plr);
break;

case 7:
objmgr.CreateGossipMenuForPlayer(&Menu, pCreature->GetGUID(), 1, Plr);
Menu->AddItem(0, "[Back]", 99);
Menu->SendTo(Plr);
break;

case 8:
objmgr.CreateGossipMenuForPlayer(&Menu, pCreature->GetGUID(), 1, Plr);
Menu->AddItem(0, "[Back]", 99);
Menu->SendTo(Plr);
break;

        case 10:     // Warrior-Taunt
			if(Plr->getLevel() >= 10)
			{
				Plr->addSpell(355);
				Plr->BroadcastMessage("You have learned Taunt.");
			}else{
				Plr->BroadcastMessage("You must be level 10 to learn Taunt.");
				}
			break;

	case 11:     // Warrior-Defensive Stance
			if(Plr->getLevel() >= 10)
			{
				Plr->addSpell(71);
				Plr->BroadcastMessage("You have learned Defensive Stance.");
			}else{
				Plr->BroadcastMessage("You must be level 10 to learn Defensive Stance.");
				}
			break;

	case 12:     // Warrior-Beserker Stance
			if(Plr->getLevel() >= 30)
			{
				Plr->addSpell(2458);
				Plr->BroadcastMessage("You have learned Berseker Stance.");
			}else{
				Plr->BroadcastMessage("You must be level 30 to learn Berseker Stance.");
				}
			break;

	case 13:     // Warrior-Intercept
			if(Plr->getLevel() >= 10)
			{
				Plr->addSpell(25275);
				Plr->BroadcastMessage("You have learned Intercept.");
			}else{
				Plr->BroadcastMessage("You must be level 10 to learn Intercept.");
				}
			break;

        case 20:     // Paladin-Warhorse
			if(Plr->getLevel() >= 40)
			{
                		Plr->addSpell(13819);
            			Plr->BroadcastMessage("You have learned Summon Warhorse.");
			}else{ 
				Plr->BroadcastMessage("You must be level 40 to learn Summon Warhorse."); 
				}
			break;

	case 21:     // Paladin-Charger
			if(Plr->getLevel() >= 60)
			{
                		Plr->addSpell(34767);
            			Plr->BroadcastMessage("You have learned Summon Charger.");
			}else{ 
				Plr->BroadcastMessage("You must be level 60 to learn Summon Charger."); 
				}			
			break;

	case 22:     // Paladin-Redemption
			if(Plr->getLevel() >= 10)
			{
                		Plr->addSpell(20773);
            			Plr->BroadcastMessage("You have learned Redemption.");
			}else{ 
				Plr->BroadcastMessage("You must be level 10 to learn Redemption."); 
				}			
			break;
        
        case 30:     // Hunter-Pet Spells
	        	if(Plr->getLevel() >= 10)
	        	{
				Plr->addSpell(1515);
				Plr->addSpell(883);
				Plr->addSpell(5149);
				Plr->addSpell(982);
				Plr->addSpell(6991);
				Plr->BroadcastMessage("You have learned your Hunter Pet Spells.");
				Plr->Gossip_Complete();
			}else{
				Plr->BroadcastMessage("You are below level 10.");
				Plr->Gossip_Complete();
				}
            		break;

	case 40:     // Warlock-Pet Spells
	        	if(Plr->getLevel() >= 10)
	        	{
				Plr->addSpell(688);
				Plr->addSpell(697);
				Plr->addSpell(712);
				Plr->addSpell(691);
				Plr->BroadcastMessage("You have learned your Warlock Pet Spells.");
				Plr->Gossip_Complete();
			}else{
				Plr->BroadcastMessage("You are below level 10.");
				Plr->Gossip_Complete();
			}
			break;

	case 41:     // Warlock-Felsteed
	        	if(Plr->getLevel() >= 40)
	        	{
				Plr->addSpell(5784);
				Plr->BroadcastMessage("You have learned Summon Felsteed.");
				Plr->Gossip_Complete();
			}else{
				Plr->BroadcastMessage("You must be level 40 to learn Summon Felsteed.");
				Plr->Gossip_Complete();
			}
			break;

	case 42:     // Warlock-Dreadsteed
	        	if(Plr->getLevel() >= 60)
	        	{
				Plr->addSpell(23161);
				Plr->BroadcastMessage("You have learned Summon Dreadsteed.");
				Plr->Gossip_Complete();
			}else{
				Plr->BroadcastMessage("You must be level 60 to learn Summon Dreadsteed.");
				Plr->Gossip_Complete();
			}
            		break;

	case 51:     // Druid-Dire Bear Form
	        	if(Plr->getLevel() >= 30)
	        	{
				Plr->addSpell(9634);
				Plr->BroadcastMessage("You have learned Dire Bear Form.");
				Plr->Gossip_Complete();
			}else{
				Plr->BroadcastMessage("You must be level 30 to learn Dire Bear Form.");
				Plr->Gossip_Complete();
			}
            		break;

	case 52:     // Druid-Normal Flight Form
	        	if(Plr->getLevel() >= 68)
	        	{
				Plr->addSpell(33943);
				Plr->BroadcastMessage("You have learned Summon Normal Flight Form.");
				Plr->Gossip_Complete();
			}else{
				Plr->BroadcastMessage("You must be level 68 to learn Normal Flight Form.");
				Plr->Gossip_Complete();
			}
            		break;

	case 53:     // Druid-Epic Flight Form
	        	if(Plr->getLevel() >= 70)
	        	{
				Plr->addSpell(40120);
				Plr->BroadcastMessage("You have learned Summon Epic Flight Form.");
				Plr->Gossip_Complete();
			}else{
				Plr->BroadcastMessage("You must be level 60 to learn Epic Flight Form.");
				Plr->Gossip_Complete();
			}
					break;
	case 54:     // Druid-Bear form
	        	if(Plr->getLevel() >= 10)
	        	{
				Plr->addSpell(6795);
				Plr->BroadcastMessage("You have learned Bear Form.");
				Plr->Gossip_Complete();
			}else{
				Plr->BroadcastMessage("You must be level 10 to learn Bear Form.");
				Plr->Gossip_Complete();
			}
            		break;
	case 56:     // Druid-Aquatic Form
	        	if(Plr->getLevel() >= 20)
	        	{
				Plr->addSpell(6795);
				Plr->BroadcastMessage("You have learned Aquatic Form.");
				Plr->Gossip_Complete();
			}else{
				Plr->BroadcastMessage("You must be level 20 to learn Aquatic Form.");
				Plr->Gossip_Complete();
			}
            		break;

	case 98:     // Reset Talents  
			{
                                Plr->Reset_Talents();
				Plr->BroadcastMessage("You have reset your talent points.");
				Plr->Gossip_Complete();
			}
            		break;
	case 99:    //Main Menu
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);
				if (Plr->getClass() == 1) 
 { 
Menu->AddItem(0, "What spells can warriors learn?", 1);
 } 
				if (Plr->getClass() == 2)
 { 
Menu->AddItem(0, "What spells can paladins learn?", 2);
 }
				if (Plr->getClass() == 3)
 { 
Menu->AddItem(0, "What spells can hunters learn?", 3);
 }
				if (Plr->getClass() == 9)
 { 
Menu->AddItem(0, "What spells can warlocks learn?", 4);
 }
				if (Plr->getClass() == 11)
 { 
Menu->AddItem(0, "What spells can druids learn?", 5);
 }
				if (Plr->getClass() == 4) 
 { 
Menu->AddItem(0, "What spells can rogues learn?", 6);
 } 
				if (Plr->getClass() == 5) 
 { 
Menu->AddItem(0, "What spells can priests learn?", 7);
 } 
				if (Plr->getClass() == 7) 
 { 
Menu->AddItem(0, "What spells can shamans learn?", 8);
 } 
Menu->AddItem(0, "Reset Talent Points", 98);
Menu->SendTo(Plr);
break;

			
		}
	}


void SetupSkillNPC(ScriptMgr * mgr)
{
	GossipScript * gs = (GossipScript*) new SkillNPC();
    mgr->register_gossip_script( 98777, gs);

    GossipScript * bs = (GossipScript*) new BuffNPC();
    mgr->register_gossip_script( 99998, bs);

    mgr->register_gossip_script(98715, (GossipScript*) new MissingSkillNPC());
}
