#include "EasyFunctions.h"

void
EAS::PrintMessage(const char *text, ...)
{
#ifdef ENABLE_DEBUG_TEXT
		va_list arg;
		va_start(arg, text);

		printf("[EAS] ");
		vprintf(text, arg);
		putc('\n', stdout);

		va_end(arg);
#endif
}

void 
EAS::WaypointCreate(Creature *pCreature, float x, float y, 
					float z, float o, uint32 waittime, uint32 flags, uint32 modelId)
{
	PrintMessage("Function call: WaypointCreate()");
	if(pCreature == NULL)
		return;

	if(!pCreature->m_custom_waypoint_map)
	{
		pCreature->m_custom_waypoint_map = new WayPointMap;
		pCreature->GetAIInterface()->SetWaypointMap(pCreature->m_custom_waypoint_map);
	}

	if(!modelId)
		modelId = pCreature->GetUInt32Value(UNIT_FIELD_DISPLAYID);

	WayPoint * pWaypoint = new WayPoint;
	pWaypoint->id = pCreature->m_custom_waypoint_map->size() + 1;
	pWaypoint->x = x;
	pWaypoint->y = y;
	pWaypoint->z = z;
	pWaypoint->o = o;
	pWaypoint->flags = flags;
	pWaypoint->backwardskinid = modelId;
	pWaypoint->forwardskinid = modelId;
	pWaypoint->backwardemoteid = pWaypoint->forwardemoteid = 0;
	pWaypoint->backwardemoteoneshot = pWaypoint->forwardemoteoneshot = false;
	pWaypoint->waittime = waittime;

	pCreature->m_custom_waypoint_map->push_back(pWaypoint);
}

void 
EAS::WaypointCreate(Creature *pCreature, EASWaypoint * pWPData)
{
    WaypointCreate(pCreature, pWPData->x, pWPData->y, pWPData->z, pWPData->o, pWPData->waitTime, pWPData->flags, pWPData->modelId);
}

void 
EAS::MoveToPlayer(Player *plr, Creature *creat)
{
	PrintMessage("Function call: MoveToPlayer()");
	if(plr == NULL || creat == NULL)
		return;
      
	creat->GetAIInterface()->MoveTo(plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ(), plr->GetOrientation());
}

void 
EAS::CreateCustomWaypointMap(Creature *creat)
{

	PrintMessage("Function call: CreateCustomWaypointMap()");
	if(creat == NULL)
		return;

	if(creat->m_custom_waypoint_map)
	{
		WayPointMap::iterator itr = creat->m_custom_waypoint_map->begin();
		for(; itr != creat->m_custom_waypoint_map->end(); ++itr)
			delete (*itr);

		delete creat->m_custom_waypoint_map;
	} 
    
	creat->m_custom_waypoint_map = new WayPointMap;
	creat->GetAIInterface()->SetWaypointMap(creat->m_custom_waypoint_map);
}

void 
EAS::DeleteWaypoints(Creature *creat)
{
	PrintMessage("Function call: DeleteWaypoints()");
	if(creat == NULL || creat->m_custom_waypoint_map == NULL)
		return;

	WayPointMap::iterator i = creat->m_custom_waypoint_map->begin();
	for(;i != creat->m_custom_waypoint_map->end(); ++i)
	{
		if((*i) != NULL)
			delete (*i);
	}

	creat->m_custom_waypoint_map->clear();
}

void 
EAS::DeleteSpawned(Creature *creat)
{
	PrintMessage("Function call: DeleteSpawned()");
	if(creat == NULL)
		return;

	creat->Despawn(0, 0);
	creat->SafeDelete();
}

void
EAS::GameobjectDelete(GameObject *pC, uint32 duration)
{
	PrintMessage("Function call: GameobjectDelete()");

	TimedEvent *te = TimedEvent::Allocate(pC, new CallbackP0<GameObject>(pC, &GameObject::ExpireAndDelete), 0, duration, 1);  
	pC->event_AddEvent(te);
}

Creature*
EAS::SpawnCreature(Player *pThis, uint32 entry, float posX, float posY, float posZ, float posO, uint32 duration)
{	
	PrintMessage("Function call: SpawnCreature()");
	if(pThis == NULL)
		return NULL;
      
	Creature* pCreature = pThis->GetMapMgr()->GetInterface()->SpawnCreature(entry, posX, posY, posZ, posO, true, false, 0, 0);
	if(duration > 0 && pThis != NULL)
		pCreature->Despawn(duration, 0);

	return pCreature;
}

GameObject*
EAS::SpawnGameobject(Player *plr, uint32 entry_id, float x, float y, float z, float o, float scale)
{
	PrintMessage("Function call: SpawnGameobject()");

	GameObjectInfo *goi = GameObjectNameStorage.LookupEntry(entry_id);
	if(goi == NULL)
		return NULL;

	GameObject *pC = plr->GetMapMgr()->CreateGameObject(entry_id);
	pC->m_spawn=0;
	pC->CreateFromProto(entry_id, plr->GetMapId(), x, y, z, o);
	pC->SetFloatValue(OBJECT_FIELD_SCALE_X, scale);
	pC->SetMapId(plr->GetMapId());
	pC->SetInstanceID(plr->GetInstanceID());
	pC->PushToWorld(plr->GetMapMgr());

	return pC;
}


bool 
EAS::AddItem(uint32 entry, Player *plr, uint32 count)
{
	PrintMessage("Function call: AddItem(%u)", entry);
	if(plr == NULL)
		return false;

	SlotResult slotresult = plr->GetItemInterface()->FindFreeInventorySlot(NULL);
	if(!slotresult.Result)
	{
		plr->GetItemInterface()->BuildInventoryChangeError(NULL, NULL, INV_ERR_INVENTORY_FULL);
		return false;
	}

	Item *pItem = objmgr.CreateItem(entry, plr);
	Item *stack = plr->GetItemInterface()->FindItemLessMax(entry, count, false);

	if(stack == NULL)
	{
		plr->GetItemInterface()->AddItemToFreeSlot(pItem);
		plr->GetSession()->SendItemPushResult(pItem, false, true, true, true, slotresult.ContainerSlot, slotresult.Slot, 1);
		return true;
	}

	stack->SetCount(stack->GetUInt32Value(ITEM_FIELD_STACK_COUNT) + count);
	stack->m_isDirty = true;
      
	plr->GetSession()->SendItemPushResult(stack, false, true, true, false, plr->GetItemInterface()->GetBagSlotByGuid(stack->GetGUID()), 0xFFFFFFFF, 1);
       
	return true;
}