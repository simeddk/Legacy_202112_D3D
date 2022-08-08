#include "00_Global.fx"

float3 LightDirection = float3(-1, -1, +1);
Texture2D DiffuseMap;

struct VertexInput
{
    float4 Position : Position;
    float2 Uv : Uv;
    float3 Normal : Normal;
};

struct VertexOutput
{
    float4 Position : SV_Position;
    float2 Uv : Uv;
    float3 Normal : Normal;
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
	float4 diffuseColor = DiffuseMap.Sample(LinearSampler, input.Uv);

    float3 normal = normalize(input.Normal);
    float lambert = dot(-LightDirection, normal);

    return diffuseColor * lambert;
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