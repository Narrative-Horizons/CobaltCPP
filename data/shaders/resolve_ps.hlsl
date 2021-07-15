Texture2D tex;
SamplerState tex_sampler;

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 UV : TEX_COORD;
};

struct PSOutput
{
    float4 color : SV_TARGET;
};

void main(in PSInput PSIn, out PSOutput PSOut)
{
    PSOut.color = tex.Sample(tex_sampler, PSIn.UV);
}