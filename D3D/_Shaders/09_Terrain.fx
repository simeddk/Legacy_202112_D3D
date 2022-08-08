#include "00_Global.fx"

float3 LightDirection = float3(-1, -1, +1);
Texture2D BaseMap;

uint Albedo = 0;

struct VertexInput
{
    float4 Position : Position;
    float3 Normal : Normal;
    float2 Uv : Uv;
};

struct VertexOutput
{
    float4 Position : SV_Position;
    float3 Normal : Normal;
    float2 Uv : Uv;
};


VertexOutput VS(VertexInput input)
{
    VertexOutput output;

    output.Position = WorldPosition(input.Position);
    output.Position = ViewProjection(output.Position);

    output.Normal = WorldNormal(input.Normal);
    output.Uv = input.Uv;

    return output;
}

float4 PS(VertexOutput input) : SV_Target
{
    //return float4(0, 1, 0, 1);
	float4 baseColor = BaseMap.Sample(LinearSampler, input.Uv);

    float3 normal = normalize(input.Normal);
    float lambert = dot(-LightDirection, normal);

    if (Albedo == 1)
        return baseColor;

    return baseColor * lambert;
}

technique11 T0
{
	P_VP(P0, VS, PS)
	P_RS_VP(P1, FillMode_WireFrame, VS, PS)
}