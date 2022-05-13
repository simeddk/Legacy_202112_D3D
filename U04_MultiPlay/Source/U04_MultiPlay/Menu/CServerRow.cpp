#include "CServerRow.h"
#include "Components/Button.h"
#include "CMainMenu.h"

void UCServerRow::SetUp(class UCMainMenu* InParent, uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;

	RowButton->OnClicked.AddDynamic(this, &UCServerRow::OnClicked);
}

void UCServerRow::OnClicked()
{
	if (!!Parent)
		Parent->SelectIndex(Index);
}