#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class EXAMPLE_API CEditorDetailPanel : public IDetailCustomization
{
public:
	CEditorDetailPanel();
	~CEditorDetailPanel();

public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	FReply OnClicked();

private:
	TArray<TWeakObjectPtr<UObject>> Objects;
};
