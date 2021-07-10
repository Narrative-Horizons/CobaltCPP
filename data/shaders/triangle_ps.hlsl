struct PSInput
{
    float4 pos : SV_POSITION;
};

struct PSOutput
{
    float4 color : SV_TARGET;
};

void main(in PSInput PSIn, out PSOutput PSOut)
{
    PSOut.color = float4(1, 0, 1, 1);
}