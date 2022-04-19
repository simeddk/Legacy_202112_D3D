#include "CAssetToolAction.h"
#include "CDataAsset.h"

CAssetToolAction::CAssetToolAction(EAssetTypeCategories::Type InCategory)
	: Category(InCategory)
{
}

CAssetToolAction::~CAssetToolAction()
{
}

FText CAssetToolAction::GetName() const
{
	return FText::FromString("Awesome Asset");
}

UClass* CAssetToolAction::GetSupportedClass() const
{
	return UCDataAsset::StaticClass();
}

FColor CAssetToolAction::GetTypeColor() const
{
	return FColor::Orange;
}

uint32 CAssetToolAction::GetCategories()
{
	return Category;
}
