#include "00_Global.fx"

float3 LightDirection = float3(-1, -1, +1);
TextureCube CubeMap;

struct VertexInput
{
    float4 Position : Position;
};

struct VertexOutput
{
    float4 Position : SV_Position;
    float3 oPosition : Position1;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;

    output.oPosition = input.Position.xyz;

    output.Position = WorldPosition(input.Position);
    output.Position = ViewProjection(output.Position);

    return output;
}

float4 PS(VertexOutput input) : SV_Target
{
	float4 diffuseColor = CubeMap.Sample(LinearSampler, input.oPosition);

    return diffuseColor;
}

float4 PS_Wireframe(VertexOutput input) : SV_Target
{
    return float4(0, 1, 0, 1);
}

technique11 T0
{
	P_VP(P0, VS, PS)
	P_RS_VP(P1, FillMode_WireFrame, VS, PS_Wireframe)
}