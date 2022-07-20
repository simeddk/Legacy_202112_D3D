struct VertexInput
{
    float4 Position : Position;
};

struct VertexOutput
{
    float4 Position : SV_Position;
};


VertexOutput VS(VertexInput input)
{
    VertexOutput output;

    output.Position = input.Position;

    return output;
}

float4 PS(VertexOutput input) : SV_Target
{
    return float4(0, 1, 0, 1);
}

RasterizerState WireFrame
{
    FillMode = Wireframe;
};

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