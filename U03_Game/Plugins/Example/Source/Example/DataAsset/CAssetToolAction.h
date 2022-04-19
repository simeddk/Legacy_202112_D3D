#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "AssetTypeCategories.h"

class EXAMPLE_API CAssetToolAction : public FAssetTypeActions_Base
{
public:
	CAssetToolAction(EAssetTypeCategories::Type InCategory);
	~CAssetToolAction();

public:
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;

private:
	EAssetTypeCategories::Type Category;
};
