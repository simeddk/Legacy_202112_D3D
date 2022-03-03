#include "CEnemy_AI.h"
#include "Global.h"
#include "Components/CpatrolComponent.h"

ACEnemy_AI::ACEnemy_AI()
{
	CHelpers::CreateActorComponent<UCPatrolComponent>(this, &Patrol, "Patrol");
}