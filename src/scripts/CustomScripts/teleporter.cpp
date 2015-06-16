#include "StdAfx.h"
#include "Setup.h"

#ifdef WIN32
#pragma warning(disable:4305)		// warning C4305: 'argument' : truncation from 'double' to 'float'
#endif

class SCRIPT_DECL TeleNPC : public GossipScript
{
public:
	void Destroy()
	{
		delete this;
    }

    void GossipHello(Object* pObject, Player * Plr, bool AutoS)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, Plr);

        if (Plr->CombatStatus.IsInCombat() == true) {
        Plr->BroadcastMessage( "You are in combat!" );
        return;}

        if (Plr->GetItemInterface()->GetItemCount(98768, true) >= 1 )  //VIP 
            Menu->AddItem(3, "VIP Mall!", 950, 0);

        if ( Plr->GetTeam() == 1 )
            Menu->AddItem(3, "Alliance Cities", 1, 0);
        else
            Menu->AddItem(3, "Horde Cities", 2, 0);

        Menu->AddItem(3, "Eastern Kingdom Locations", 3, 0);
        Menu->AddItem(3, "Kalimdor Locations", 4, 0);
        Menu->AddItem(3, "Outland Locations", 5, 0);
        Menu->AddItem(3, "Azeroth Instances", 6, 0);
        Menu->AddItem(3, "Outland Instances", 7, 0);
        Menu->AddItem(1, "Shattrath(mall)", 420, 0);
		Menu->AddItem(4, "Remove Resurrection Sickness", 998, 0);
		Menu->AddItem(3, "Dueling Areas", 3, 0);

        if(AutoS)
            Menu->SendTo(Plr);
    }

    void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
    {
        GossipMenu * Menu;
        switch(IntId)
        {
        case 999: 
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);

Menu->AddItem(3, "Eastern Kingdom Locations", 3, 0);
Menu->AddItem(3, "Kalimdor Locations", 4, 0);
Menu->AddItem(3, "Outland Locations", 5, 0);
Menu->AddItem(3, "Azeroth Instances", 6, 0);
Menu->AddItem(3, "Outland Instances", 7, 0);
Menu->AddItem(1, "Shattrath(mall)", 420, 0);
Menu->AddItem(4, "Remove Resurrection Sickness", 10, 0);
Menu->SendTo(Plr);


break; case 1: 
objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
Menu->AddItem(1, "Stormwind", 300, 0);
Menu->AddItem(1, "Ironforge", 301, 0);
Menu->AddItem(1, "Darnassus", 302, 0);
Menu->AddItem(1, "Exodar", 303, 0);
Menu->AddItem(1, "Shattrath(mall)", 420, 0);
Menu->AddItem(0, "[Back]", 999, 0);
Menu->SendTo(Plr);


break; case 2: 
objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
Menu->AddItem(1, "Orgrimmar", 304, 0);
Menu->AddItem(1, "Thunder Bluff", 305, 0);
Menu->AddItem(1, "Undercity", 306, 0);
Menu->AddItem(1, "Silvermoon", 307, 0);
Menu->AddItem(0, "[Back]", 999, 0);
Menu->SendTo(Plr);


break; case 3: 
objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
Menu->AddItem(1, "Alterac Mountains", 308, 0);
Menu->AddItem(1, "Arathi Highlands", 309, 0);
Menu->AddItem(1, "Badlands", 310, 0);
Menu->AddItem(1, "Burning Steppes", 311, 0);
Menu->AddItem(1, "Deadwind Pass", 312, 0);
Menu->AddItem(1, "Dun Morogh", 313, 0);
Menu->AddItem(1, "Duskwood", 314, 0);
Menu->AddItem(1, "Eastern Plaguelands", 315, 0);
Menu->AddItem(1, "Elwynn Forest", 316, 0);
Menu->AddItem(1, "Eversong Woods", 317, 0);
Menu->AddItem(1, "Ghostlands", 318, 0);
Menu->AddItem(1, "Hillsbrad Foothills", 319, 0);
Menu->AddItem(1, "Hinterlands", 320, 0);
Menu->AddItem(1, "Loch Modan", 321, 0);
Menu->AddItem(0, "--> Page 2 -->", 10, 0);
Menu->AddItem(0, "[Back]", 999, 0);
Menu->SendTo(Plr);


break; case 4: 
objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
Menu->AddItem(1, "Ashenvale", 331, 0);
Menu->AddItem(1, "Azshara", 332, 0);
Menu->AddItem(1, "Azuremyst Isle", 333, 0);
Menu->AddItem(1, "Bloodmyst Isle", 334, 0);
Menu->AddItem(1, "Darkshore", 335, 0);
Menu->AddItem(1, "Durotar", 336, 0);
Menu->AddItem(1, "Desolace", 337, 0);
Menu->AddItem(1, "Dustwallow Marsh", 338, 0);
Menu->AddItem(1, "Felwood", 339, 0);
Menu->AddItem(1, "Feralas", 340, 0);
Menu->AddItem(1, "Moonglade", 341, 0);
Menu->AddItem(1, "Mulgore", 342, 0);
Menu->AddItem(1, "Silithus", 343, 0);
Menu->AddItem(1, "Stonetalon Mountains", 344, 0);
Menu->AddItem(0, "--> Page 2 -->", 11, 0);
Menu->AddItem(0, "[Back]", 999, 0);
Menu->SendTo(Plr);


break; case 5: 
objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
Menu->AddItem(1, "Blade's Edge Mountains", 351, 0);
Menu->AddItem(1, "Hellfire Peninsula", 352, 0);
Menu->AddItem(1, "Nagrand", 353, 0);
Menu->AddItem(1, "Netherstorm", 354, 0);
Menu->AddItem(1, "Shadowmoon Valley", 355, 0);
Menu->AddItem(1, "Terokkar Forest", 356, 0);
Menu->AddItem(1, "Zangarmarsh", 357, 0);
Menu->AddItem(0, "[Back]", 999, 0);
Menu->SendTo(Plr);


break; case 6: 
objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
Menu->AddItem(1, "Ahn'Qiraj", 358, 0);
Menu->AddItem(1, "Blackfathom Depths", 359, 0);
Menu->AddItem(1, "Blackrock Depths", 360, 0);
Menu->AddItem(1, "Blackrock Spire", 361, 0);
Menu->AddItem(1, "Blackwing Lair", 362, 0);
Menu->AddItem(1, "Caverns of Time", 363, 0);
Menu->AddItem(1, "Deadmines", 364, 0);
Menu->AddItem(1, "Dire Maul", 365, 0);
Menu->AddItem(1, "Gnomeregan", 366, 0);
Menu->AddItem(1, "Maraudon", 367, 0);
Menu->AddItem(1, "Molten Core", 368, 0);
Menu->AddItem(1, "Onyxia's Lair", 369, 0);
Menu->AddItem(1, "Ragefire Chasm", 370, 0);
Menu->AddItem(0, "--> Page 2 -->", 12, 0);
Menu->AddItem(0, "[Back]", 999, 0);
Menu->SendTo(Plr);


break; case 7: 
objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
Menu->AddItem(0, "Outland Raids", 13, 0);
Menu->AddItem(1, "Auchenai Crypts", 383, 0);
Menu->AddItem(1, "Coilfang Reservoir", 385, 0);
Menu->AddItem(1, "Hellfire Ramparts", 387, 0);
Menu->AddItem(1, "Mana Tombs", 388, 0);
Menu->AddItem(1, "Pheonix Hall", 389, 0);
Menu->AddItem(1, "Sethekk Halls", 390, 0);
Menu->AddItem(1, "Shadow Labyrinth", 391, 0);
Menu->AddItem(1, "The Blood Furnace", 423, 0);
Menu->AddItem(1, "The Botanica", 392, 0);
Menu->AddItem(1, "The Mechanar", 393, 0);
Menu->AddItem(1, "The Shattered Halls", 425, 0);
Menu->AddItem(1, "The Slave Pens", 426, 0);
Menu->AddItem(1, "The Steamvault", 427, 0);
Menu->AddItem(1, "The Underbog", 428, 0);
Menu->AddItem(0, "[Back]", 999, 0);
Menu->SendTo(Plr);


break; case 8: 
objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
Menu->AddItem(1, "WinterSpring", 403, 0);
Menu->SendTo(Plr);


break; case 9: 
objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
Menu->AddItem(1, "Azjol'Nerub", 406, 0);
Menu->AddItem(1, "Drak'Tharon", 407, 0);
Menu->AddItem(1, "Gun'Drak", 408, 0);
Menu->AddItem(1, "Icecrown Citadel", 409, 0);
Menu->AddItem(1, "Naxxaramas", 410, 0);
Menu->AddItem(1, "Obsidian Sanctum", 411, 0);
Menu->AddItem(1, "The Nexus/Occulus/Eye of Eternity", 412, 0);
Menu->AddItem(1, "Halls of Stone/Halls of Lightning", 413, 0);
Menu->AddItem(1, "Utgarde Keep", 414, 0);
Menu->AddItem(1, "Utgarde Pinnacle", 415, 0);
Menu->AddItem(1, "Vault of Archevon", 416, 0);
Menu->AddItem(1, "Violet Hold", 417, 0);
Menu->AddItem(0, "[Back]", 999, 0);
Menu->SendTo(Plr);


break; case 10: 
objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
Menu->AddItem(1, "Searing Gorge", 322, 0);
Menu->AddItem(1, "Silverpine Forest", 323, 0);
Menu->AddItem(1, "Stranglethorn Vale", 324, 0);
Menu->AddItem(1, "Swamp of Sorrows", 325, 0);
Menu->AddItem(1, "The Blasted Lands", 326, 0);
Menu->AddItem(1, "Trisfal Glades", 327, 0);
Menu->AddItem(1, "Western Plaguelands", 328, 0);
Menu->AddItem(1, "Westfall", 329, 0);
Menu->AddItem(1, "Wetlands", 330, 0);
Menu->AddItem(0, "<-- Page 1 <--", 3, 0);
Menu->AddItem(0, "[Back]", 999, 0);
Menu->SendTo(Plr);


break; case 11: 
objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
Menu->AddItem(1, "Tanaris", 345, 0);
Menu->AddItem(1, "Teldrassil", 346, 0);
Menu->AddItem(1, "The Barrens", 347, 0);
Menu->AddItem(1, "Thousand Needles", 348, 0);
Menu->AddItem(1, "Un Goro Crater", 349, 0);
Menu->AddItem(1, "Winterspring", 350, 0);
Menu->AddItem(0, "<-- Page 1 <--", 4, 0);
Menu->AddItem(0, "[Back]", 999, 0);
Menu->SendTo(Plr);


break; case 12: 
objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
Menu->AddItem(1, "Razorfen Downs", 371, 0);
Menu->AddItem(1, "Razorfen Kraul", 372, 0);
Menu->AddItem(1, "Scarlet Monestary", 373, 0);
Menu->AddItem(1, "Scholomance", 374, 0);
Menu->AddItem(1, "Shadowfang Keep", 375, 0);
Menu->AddItem(1, "Stratholme", 376, 0);
Menu->AddItem(1, "Sunken Temple", 377, 0);
Menu->AddItem(1, "Uldaman", 378, 0);
Menu->AddItem(1, "Wailing Caverns", 379, 0);
Menu->AddItem(1, "Zul'Aman", 380, 0);
Menu->AddItem(1, "Zul'Farrak", 381, 0);
Menu->AddItem(1, "Zul'Gurub", 382, 0);
Menu->AddItem(0, "<-- Page 1 <--", 6, 0);
Menu->AddItem(0, "[Back]", 999, 0);
Menu->SendTo(Plr);


break; case 13: 
objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
Menu->AddItem(1, "Magtheridon's Lair", 421, 0);
Menu->AddItem(1, "Sepentshrine Cavern", 422, 0);
Menu->AddItem(1, "Gruul's Lair", 386, 0);
Menu->AddItem(1, "The Eye", 424, 0);
Menu->AddItem(1, "Black Temple", 384, 0);
Menu->AddItem(0, "[Back]", 999, 0);
Menu->SendTo(Plr);


break; case 998: 
if(Plr->HasAura(15007) == true) {
Plr->RemoveAura(15007);
Plr->BroadcastMessage("You have been cured of Resurrection Sickness!"); }
else{
Plr->BroadcastMessage("You do not currently have Resurrection Sickness!");
Plr->Gossip_Complete();}



break; case 950:
Plr->EventTeleport(169, -247.572571 , 2916.743896, 98.119423);
Plr->Gossip_Complete();


break; case 300:  // Stormwind
Plr->EventTeleport(0, -8928, 540, 95);
Plr->Gossip_Complete();


break; case 301:  // Ironforge
Plr->EventTeleport(0, -4981, -881, 502);
Plr->Gossip_Complete();
 

break; case 302:  // Darnassus
Plr->EventTeleport(1, 9978, 2033, 1328.5);
Plr->Gossip_Complete();


break; case 303:  // Exodar
Plr->EventTeleport(530, -4014, -11895, -1.5);
Plr->Gossip_Complete();


break; case 304:  // Orgrimmar
Plr->EventTeleport(1, 1502, -4415, 22);
Plr->Gossip_Complete();


break; case 305:  // Thunder Bluff
Plr->EventTeleport(1, -1283, 158, 130);
Plr->Gossip_Complete();


break; case 306:  // Undercity
Plr->EventTeleport(0, 1752, 239, 61.5);
Plr->Gossip_Complete();


break; case 307:  // Silvermoon
Plr->EventTeleport(530, 9392, -7277, 14.5);
Plr->Gossip_Complete();


break; case 308:  // Alterac Mountains
Plr->EventTeleport(0, 237, -652, 119);
Plr->Gossip_Complete();


break; case 309:  // Arathi Highlands
Plr->EventTeleport(0, -1550, -2495, 55);
Plr->Gossip_Complete();


break; case 310:  // Badlands
Plr->EventTeleport(0, -6775, -3286, 242);
Plr->Gossip_Complete();


break; case 311:  // Burning Steppes
Plr->EventTeleport(0, -7975, -1786, 133.5);
Plr->Gossip_Complete();


break; case 312:  // Deadwind Pass
Plr->EventTeleport(0, -10447, -1872, 105);
Plr->Gossip_Complete();


break; case 313:  // Dun Morogh
Plr->EventTeleport(0, -5709, -1339, 395);
Plr->Gossip_Complete();


break; case 314:  // Duskwood
Plr->EventTeleport(0, -10914, -528, 54);
Plr->Gossip_Complete();


break; case 315:  // Eastern Plaguelands
Plr->EventTeleport(0, 1739, -3623, 120);
Plr->Gossip_Complete();


break; case 316:  // Elwynn Forest
Plr->EventTeleport(0, -9591, -463, 58);
Plr->Gossip_Complete();


break; case 317:  // Eversong Woods
Plr->EventTeleport(530, 8250, -7214, 140);
Plr->Gossip_Complete();


break; case 318:  // Ghostlands
Plr->EventTeleport(530, 6396, -6848, 101);
Plr->Gossip_Complete();


break; case 319:  // Hillsbrad Foothills
Plr->EventTeleport(0, -440, -582, 54);
Plr->Gossip_Complete();


break; case 320:  // Hinterlands
Plr->EventTeleport(0, 235, -3298, 110);
Plr->Gossip_Complete();


break; case 321:  // Loch Modan
Plr->EventTeleport(0, -5853, -3251, 303);
Plr->Gossip_Complete();


break; case 322:  // Searing Gorge
Plr->EventTeleport(0, -6645, -1918, 245);
Plr->Gossip_Complete();


break; case 323:  // Silverpine Forest
Plr->EventTeleport(0, 628, 1291, 87);
Plr->Gossip_Complete();


break; case 324:  // Stranglethorn Vale
Plr->EventTeleport(0, -14246, 301, 28);
Plr->Gossip_Complete();


break; case 325:  // Swamp of Sorrows
Plr->EventTeleport(0, -10476, -2408, 74);
Plr->Gossip_Complete();


break; case 326:  // The Blasted Lands
Plr->EventTeleport(0, -11189, -3023, 8);
Plr->Gossip_Complete();


break; case 327:  // Tirisfal Glades
Plr->EventTeleport(0, 1599, 569, 38);
Plr->Gossip_Complete();


break; case 328:  // Western Plaguelands
Plr->EventTeleport(0, 1676, -1366, 70);
Plr->Gossip_Complete();


break; case 329:  // Westfall
Plr->EventTeleport(0, -10922, 998, 36);
Plr->Gossip_Complete();


break; case 330:  // Wetlands
Plr->EventTeleport(0, -3604, -2711, 20);
Plr->Gossip_Complete();


break; case 331:  // Ashenvale
Plr->EventTeleport(1, 2319, -1672, 124);
Plr->Gossip_Complete();


break; case 332:  // Azshara
Plr->EventTeleport(1, 3336, -4599, 93);
Plr->Gossip_Complete();


break; case 333:  // Azuremyst Isle
Plr->EventTeleport(530, -4540, -11933, 28);
Plr->Gossip_Complete();


break; case 334:  // Bloodmyst Isle
Plr->EventTeleport(530, -2721, -12206, 10);
Plr->Gossip_Complete();


break; case 335:  // Darkshore
Plr->EventTeleport(1, 5084, 242, 29);
Plr->Gossip_Complete();


break; case 336:  // Desolace
Plr->EventTeleport(1, 301, -4184, 28);
Plr->Gossip_Complete();


break; case 337:  // Durotar
Plr->EventTeleport(1, -548, 1276, 90);
Plr->Gossip_Complete();


break; case 338:  // Dustwallow Marsh
Plr->EventTeleport(1, -3345, -3078, 33);
Plr->Gossip_Complete();


break; case 339:  // Felwood
Plr->EventTeleport(1, 5537, -585, 359);
Plr->Gossip_Complete();


break; case 340:  // Feralas
Plr->EventTeleport(1, -4811, 1037, 105);
Plr->Gossip_Complete();


break; case 341:  // Moonglade
Plr->EventTeleport(1, 7931, -2616, 493);
Plr->Gossip_Complete();


break; case 342:  // Mulgore
Plr->EventTeleport(1, -2372, -893, -9);
Plr->Gossip_Complete();


break; case 343:  // Silithus
Plr->EventTeleport(1, -6839, 763, 43);
Plr->Gossip_Complete();


break; case 344:  // Stonetalon Mountains
Plr->EventTeleport(1, 588, 330, 48);
Plr->Gossip_Complete();


break; case 345:  // Tanaris
Plr->EventTeleport(1, -7149, -3746, 9);
Plr->Gossip_Complete();


break; case 346:  // Teldrassil
Plr->EventTeleport(1, 9947, 649, 1310);
Plr->Gossip_Complete();


break; case 347:  // The Barrens
Plr->EventTeleport(1, 567, -2573, 96);
Plr->Gossip_Complete();


break; case 348:  // Thousand Needles
Plr->EventTeleport(1, -4969, -1723, -61);
Plr->Gossip_Complete();


break; case 349:  // Un Goro Crater
Plr->EventTeleport(1, -7932, -2139, -230);
Plr->Gossip_Complete();


break; case 350:  // Winterspring
Plr->EventTeleport(1, 6719, -4646, 722);
Plr->Gossip_Complete();


break; case 351:  // Blade's Edge Mountains
Plr->EventTeleport(530, 2924, 5982, 1);
Plr->Gossip_Complete();


break; case 352:  // Hellfire Peninsula
Plr->EventTeleport(530, -312.657562, 3030.401855, -15.506211);
Plr->Gossip_Complete();


break; case 353:  // Nagrand
Plr->EventTeleport(530, -1525, 6571, 21);
Plr->Gossip_Complete();


break; case 354:  // Netherstorm
Plr->EventTeleport(530, 3052, 3670, 143);
Plr->Gossip_Complete();


break; case 355:  // Shadowmoon Valley
Plr->EventTeleport(530, -3693, 2344, 77);
Plr->Gossip_Complete();


break; case 356:  // Terokkar Forest
Plr->EventTeleport(530, -1975, 4516, 13);
Plr->Gossip_Complete();


break; case 357:  // Zangarmarsh
Plr->EventTeleport(530, -205, 5545, 24);
Plr->Gossip_Complete();


break; case 358:  // Ahn'Qiraj
Plr->EventTeleport(1, -8187, 1539, 5);
Plr->Gossip_Complete();


break; case 359:  // Blackfathom Depths
Plr->EventTeleport(1, 4225.5, 736.2, -26.1);
Plr->Gossip_Complete();


break; case 360:  // Blackrock Depths
Plr->EventTeleport(0, -7187, -914, 166);
Plr->Gossip_Complete();


break; case 361:  // Blackrock Spire
Plr->EventTeleport(0, -7532, -1221, 286);
Plr->Gossip_Complete();


break; case 362:  // Blackwing Lair
Plr->EventTeleport(229, 137, -474, 117);
Plr->Gossip_Complete();


break; case 363:  // Caverns of Time
Plr->EventTeleport(1, -8568, -4260, -213);
Plr->Gossip_Complete();


break; case 364:  // Deadmines
Plr->EventTeleport(0, -11207.7, 1668, 24.6);
Plr->Gossip_Complete();


break; case 365:  // Dire Maul
Plr->EventTeleport(1, -3524, 1124, 162);
Plr->Gossip_Complete();


break; case 366:  // Gnomeregan
Plr->EventTeleport(0, -5164, 918,258);
Plr->Gossip_Complete();


break; case 367:  // Maraudon
Plr->EventTeleport(1, -1458, 2606, 76);
Plr->Gossip_Complete();


break; case 368:  // Molten Core
Plr->EventTeleport(230, 1123, -455, -101);
Plr->Gossip_Complete();


break; case 369:  // Onyxia's Lair
Plr->EventTeleport(1, -4709, -3729, 55);
Plr->Gossip_Complete();


break; case 370:  // Ragefire Chasm
Plr->EventTeleport(1, 1805, -4404, -18);
Plr->Gossip_Complete();


break; case 371:  // Razorfen Downs
Plr->EventTeleport(1, -4661, -2511, 81);
Plr->Gossip_Complete();


break; case 372:  // Razorfen Kraul
Plr->EventTeleport(1, -4473, -1690, 82);
Plr->Gossip_Complete();


break; case 373:  // Scarlet Monestary
Plr->EventTeleport(0, 2841, -692, 140);
Plr->Gossip_Complete();


break; case 374:  // Scholomance
Plr->EventTeleport(0, 1265, -2560, 95);
Plr->Gossip_Complete();


break; case 375:  // Shadowfang Keep
Plr->EventTeleport(0, -241, 1545, 77);
Plr->Gossip_Complete();


break; case 376:  // Stratholme
Plr->EventTeleport(0, 3345, -3380, 145);
Plr->Gossip_Complete();


break; case 377:  // Sunken Temple
Plr->EventTeleport(0, -10457, -3828, 19);
Plr->Gossip_Complete();


break; case 378:  // Uldaman
Plr->EventTeleport(0, -6076.05, -2957.7, 207);
Plr->Gossip_Complete();


break; case 379:  // Wailing Caverns
Plr->EventTeleport(1, -737, -2219, 17);
Plr->Gossip_Complete();


break; case 380:  // Zul'Aman
Plr->EventTeleport(530, 6850, -7950, 171);
Plr->Gossip_Complete();


break; case 381:  // Zul'Farrak
Plr->EventTeleport(1, -6821, -2890, 9);
Plr->Gossip_Complete();


break; case 382:  // Zul'Gurub
Plr->EventTeleport(0, -11916, -1204, 93);
Plr->Gossip_Complete();


break; case 383:  // Auchenai Crypts
Plr->EventTeleport(530, -3359.8, 5221, -101);
Plr->Gossip_Complete();


break; case 384:  // Black Temple
Plr->EventTeleport(530, -3614, 310, 40);
Plr->Gossip_Complete();


break; case 385:  // Coilfang Reservoir
Plr->EventTeleport(530, 740.1, 6868, -68);
Plr->Gossip_Complete();


break; case 386:  // Gruul's Lair
Plr->EventTeleport(530, 3529, 5096, 3);
Plr->Gossip_Complete();


break; case 387:  // Hellfire Ramparts
Plr->EventTeleport(530, -172, 3020, -3.2);
Plr->Gossip_Complete();


break; case 388:  // Mana Tombs
Plr->EventTeleport(530, -3081.4, 4945.6, -101);
Plr->Gossip_Complete();


break; case 389:  // Pheonix Hall
Plr->EventTeleport(530, 3084, 1385, 185);
Plr->Gossip_Complete();


break; case 390:  // Sethekk Halls
Plr->EventTeleport(530, -3364, 4675, 101);
Plr->Gossip_Complete();


break; case 391:  // Shadow Labyrinth
Plr->EventTeleport(530, -3640, 4941, -101);
Plr->Gossip_Complete();


break; case 392:  // The Botanica
Plr->EventTeleport(530, 3404, 1488, 183);
Plr->Gossip_Complete();


break; case 393:  // The Mechanar
Plr->EventTeleport(530, 2870, 1557, 252);
Plr->Gossip_Complete();


break; case 394:  // Borean Tundra
Plr->EventTeleport(571, 3008, 5290, 60);
Plr->Gossip_Complete();


break; case 395:  // Dragonblight
Plr->EventTeleport(571, 3118, 107, 72);
Plr->Gossip_Complete();


break; case 396:  // Grizzly Hills
Plr->EventTeleport(571, 3681, -3472, 243);
Plr->Gossip_Complete();


break; case 397:  // Howling Fjord
Plr->EventTeleport(571, 1267, -4062, 143);
Plr->Gossip_Complete();


break; case 398:  // Icecrown
Plr->EventTeleport(571, 7514, 2091, 623);
Plr->Gossip_Complete();


break; case 399:  // Sholazar Basin
Plr->EventTeleport(571, 5501, 4879, 198);
Plr->Gossip_Complete();


break; case 400:  // Storm Peaks
Plr->EventTeleport(571, 7514, -1037, 467);
Plr->Gossip_Complete();


break; case 401:  // Wintergrasp
Plr->EventTeleport(571, 4611, 2848, 3397);
Plr->Gossip_Complete();


break; case 402:  // Zul'Drak
Plr->EventTeleport(571, 5441, -2304, 298);
Plr->Gossip_Complete();


break; case 403:  // Dalaran
Plr->EventTeleport(571, 5797, 629, 648);
Plr->Gossip_Complete();


break; case 404:  // Crystalsong Forest
Plr->EventTeleport(571, 5402, 72, 151);
Plr->Gossip_Complete();


break; case 405:  // DK Start Zone
Plr->EventTeleport(609, 2353, -5666, 427);
Plr->Gossip_Complete();


break; case 406:  // Azjol'Nerub
Plr->EventTeleport(571, 3721, 2155, 37);
Plr->Gossip_Complete();


break; case 407:  // Drak'Tharon
Plr->EventTeleport(571, 4897, 2046, 249);
Plr->Gossip_Complete();


break; case 408:  // Gun'Drak
Plr->EventTeleport(571, 6925, 4447, 451);
Plr->Gossip_Complete();


break; case 409:  // Icecrown Citadel
Plr->EventTeleport(571, 6151, 2244, 508);
Plr->Gossip_Complete();


break; case 410:  // Naxxaramas
Plr->EventTeleport(571, 3668, -1049, 131);
Plr->Gossip_Complete();


break; case 411:  // Obsidian Sanctum
Plr->EventTeleport(571, 3561, 275, 115);
Plr->Gossip_Complete();


break; case 412:  // The Nexus/Occulus/Eye of Eternity
Plr->EventTeleport(571, 3783, 6942, 105);
Plr->Gossip_Complete();


break; case 413:  // Halls of Stone/Halls of Lightning
Plr->EventTeleport(571, 8937, 1266, 1026);
Plr->Gossip_Complete();


break; case 414:  // Utgarde Keep
Plr->EventTeleport(571, 1228, -4943, 36);
Plr->Gossip_Complete();


break; case 415:  // Utgarde Pinnacle
Plr->EventTeleport(571, 1274, -4857, 216);
Plr->Gossip_Complete();


break; case 416:  // Vault of Archevon
Plr->EventTeleport(571, 5440, 2840, 421);
Plr->Gossip_Complete();


break; case 417:  // Violet Hold
Plr->EventTeleport(571, 5708, 521, 650);
Plr->Gossip_Complete();


break; case 418:  // Alliance Mall
Plr->EventTeleport(530, 53.706242, -1503.903809, 12.486);
Plr->Gossip_Complete();


break; case 419:  // Horde Mall
Plr->EventTeleport(530, 53.706242, -1503.903809, 12.486);
Plr->Gossip_Complete();


break; case 420:  // shattrath
Plr->EventTeleport(530, -1887.510010, 5359.379883, -12.427300);
Plr->Gossip_Complete();


break; case 421:  // Magtheridon's Lair
Plr->EventTeleport(530, -313, 3088, -116);
Plr->Gossip_Complete();


break; case 422:  // Serpentshrine Cavern
Plr->EventTeleport(530, 830, 6865, -63);
Plr->Gossip_Complete();


break; case 423:  // The Blood Furnace
Plr->EventTeleport(530, -303, 3164, 32);
Plr->Gossip_Complete();


break; case 424:  // The Eye
Plr->EventTeleport(530, 3087, 1373, 185);
Plr->Gossip_Complete();


break; case 425:  // The Shattered Halls
Plr->EventTeleport(530, -311, 3083, -3);
Plr->Gossip_Complete();


break; case 426:  // The Slave Pens
Plr->EventTeleport(530, 719, 6999, -73);
Plr->Gossip_Complete();


break; case 427:  // The Steamvault
Plr->EventTeleport(530, 816, 6934, -80);
Plr->Gossip_Complete();


break; case 428:  // The Underbog
Plr->EventTeleport(530, 777, 6763, -72);
Plr->Gossip_Complete();
          break;
}}};

void SetupTeleNPC(ScriptMgr * mgr)
{
	GossipScript * teleporter = (GossipScript*) new TeleNPC();
    mgr->register_gossip_script(35001,  teleporter); 
}