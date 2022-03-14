#include "CCameraSpline.h"
#include "Global.h"
#include "Components/SplineComponent.h"

ACCameraSpline::ACCameraSpline()
{
	CHelpers::CreateComponent(this, &Spline, "Spline");
	CHelpers::GetAsset<UCurveFloat>(&Curve, "CurveFloat'/Game/Curves/Curve_Unnormal.Curve_Unnormal'");
}

