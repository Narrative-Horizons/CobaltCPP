struct PSInput
{
    float4 pos : SV_POSITION;
};

void main(in float3 position : ATTRIB0, out PSInput PSIn)
{
    PSIn.pos = float4(position, 1.0);
}