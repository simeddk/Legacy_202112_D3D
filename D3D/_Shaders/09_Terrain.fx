matrix World, View, Projection;
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

RasterizerState WireFrame
{
    FillMode = Wireframe;
};

SamplerState LinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;

    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    output.Normal = mul(input.Normal, (float3x3) World);

    output.Uv = input.Uv;

    return output;
}

float4 PS(VertexOutput input) : SV_Target
{
    return float4(0, 1, 0, 1);
	float4 baseColor = BaseMap.Sample(LinearSampler, input.Uv);

    float3 normal = normalize(input.Normal);
    float lambert = dot(-LightDirection, normal);

    if (Albedo == 1)
        return baseColor;

    return baseColor * lambert;
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
}