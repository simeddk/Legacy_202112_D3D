#include "CUserWidget_Select.h"
#include "Global.h"
#include "Components/Widget.h"
#include "Components/GridPanel.h"
#include "Components/Border.h"
#include "Widgets/CUserWidget_SelectItem.h"


void UCUserWidget_Select::NativeConstruct()
{
	TArray<UWidget*> children = Grid->GetAllChildren();
	for (UWidget* child : children)
		Items.Add(child->GetName(), Cast<UCUserWidget_SelectItem>(child));

	Super::NativeConstruct();
}

void UCUserWidget_Select::Press(FString InName)
{
	
}

void UCUserWidget_Select::Hover(FString InName)
{
	UBorder* border = Cast<UBorder>(Items[InName]->GetWidgetFromName("BG_Border"));
	if (!!border)
		border->SetBrushColor(FLinearColor::Red);
}

void UCUserWidget_Select::Unhover(FString InName)
{
	UBorder* border = Cast<UBorder>(Items[InName]->GetWidgetFromName("BG_Border"));
	if (!!border)
		border->SetBrushColor(FLinearColor::White);
}

