struct PSInput
{
    float4 pos : SV_POSITION;
    float2 UV : TEX_COORD;
};

cbuffer myBuffer
{
    float4x4 object;
}

void main(in float3 position : ATTRIB0, in float2 iUV : ATTRIB1, out PSInput PSIn)
{
    PSIn.pos = mul(object, float4(position, 1.0));
    PSIn.UV = iUV;
}