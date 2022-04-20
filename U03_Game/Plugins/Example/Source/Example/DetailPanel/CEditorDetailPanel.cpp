#include "CEditorDetailPanel.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Objects/CHasButton.h"

CEditorDetailPanel::CEditorDetailPanel()
{
}

CEditorDetailPanel::~CEditorDetailPanel()
{
}

TSharedRef<IDetailCustomization> CEditorDetailPanel::MakeInstance()
{
	return MakeShareable(new CEditorDetailPanel());
}

void CEditorDetailPanel::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& category = DetailBuilder.EditCategory("Change Color");

	category.AddCustomRow(FText::FromString("Color"))
		.ValueContent()
		.VAlign(VAlign_Center)
		.MaxDesiredWidth(250)
		[
			SNew(SButton).VAlign(VAlign_Center)
			.OnClicked(this, &CEditorDetailPanel::OnClicked)
			.Content()
			[
				SNew(STextBlock).Text(FText::FromString("Random Color"))
			]
		];

	DetailBuilder.GetObjectsBeingCustomized(Objects);
}

FReply CEditorDetailPanel::OnClicked()
{
	for (TWeakObjectPtr<UObject>& object : Objects)
	{
		GLog->Log(object->GetName());

		ACHasButton* hasButton = Cast<ACHasButton>(object);
		
		if (!!hasButton)
			hasButton->ApplyColor(FLinearColor::MakeRandomColor());
	}

	return FReply::Handled();
}
