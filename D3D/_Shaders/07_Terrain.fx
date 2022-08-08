#include "00_Global.fx"

struct VertexInput
{
    float4 Position : Position;
};

struct VertexOutput
{
    float4 Position : SV_Position;
};


//-----------------------------------------------------------------------------
//Albedo
//-----------------------------------------------------------------------------
VertexOutput VS(VertexInput input)
{
    VertexOutput output;

    output.Position = WorldPosition(input.Position);
    output.Position = ViewProjection(output.Position);

    return output;
}

float4 PS(VertexOutput input) : SV_Target
{
    return float4(1, 0, 0, 1);
}

//-----------------------------------------------------------------------------
//HeightColor
//-----------------------------------------------------------------------------
struct VertexOutput_HeightColor
{
    float4 Position : SV_Position;
    float4 Color : Color;
    float3 wPosition : Position1;
};

float4 GetHeightColor(float y)
{
    if (y > 20.0f)
        return float4(1, 1, 1, 1);

    if (y > 10.0f)
        return float4(0, 0, 1, 1);

    if (y > 5.0f)
        return float4(0, 1, 0, 1);

    return float4(0.3f, 0.3f, 0.3f, 1);
}

VertexOutput_HeightColor VS_HeightColor(VertexInput input)
{
    VertexOutput_HeightColor output;

    output.Position = WorldPosition(input.Position);
    //output.Color = GetHeightColor(output.Position.y);
    output.wPosition = output.Position.xyz;
    output.Position = ViewProjection(output.Position);

    return output;
}

float4 PS_HeightColor(VertexOutput_HeightColor input) : SV_Target
{
    //return input.Color;
    return GetHeightColor(input.wPosition.y);
}
 
//-----------------------------------------------------------------------------
//Lambert
//-----------------------------------------------------------------------------
struct VertexInput_Lambert
{
    float4 Position : Position;
    float3 Normal : Normal;
};

struct VertexOutput_Lambert
{
    float4 Position : SV_Position;
    float4 Color : Color;
    float3 wPosition : Position1;
    float3 Normal : Normal;
};

VertexOutput_Lambert VS_Lambert(VertexInput_Lambert input)
{
    VertexOutput_Lambert output;

    output.Position = WorldPosition(input.Position);
    output.wPosition = output.Position.xyz;
    output.Position = ViewProjection(output.Position);

    output.Normal = WorldNormal(input.Normal);

    return output;
}

float3 LightDirection = float3(-1, -1, +1);
float4 PS_Lambert(VertexOutput_Lambert input) : SV_Target
{
    float4 diffuse = GetHeightColor(input.wPosition.y);

    float3 normal = normalize(input.Normal);
    float lambert = dot(-LightDirection, normal);

    return diffuse * lambert;
}

float4 PS_HalfLambert(VertexOutput_Lambert input) : SV_Target
{
    float4 diffuse = GetHeightColor(input.wPosition.y);

    float3 normal = normalize(input.Normal);
    float lambert = dot(-LightDirection, normal) * 0.5f + 0.5f;

    return diffuse * lambert;
}

technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }

    pass P1
    {
        SetRasterizerState(WireFrame);
		
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }

    pass P2
    {
        SetVertexShader(CompileShader(vs_5_0, VS_HeightColor()));
        SetPixelShader(CompileShader(ps_5_0, PS_HeightColor()));
    }

    pass P3
    {
        SetVertexShader(CompileShader(vs_5_0, VS_Lambert()));
        SetPixelShader(CompileShader(ps_5_0, PS_Lambert()));
    }

    pass P4
    {
        SetVertexShader(CompileShader(vs_5_0, VS_Lambert()));
        SetPixelShader(CompileShader(ps_5_0, PS_HalfLambert()));
    }
}