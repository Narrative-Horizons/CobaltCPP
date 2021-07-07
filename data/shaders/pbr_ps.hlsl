Texture2DArray<float4> textures[1024];
SamplerState textureSampler;

struct VSOut
{
    float3 positionModel : POSITIONMODEL;
    float3 normalWorld : NORMAL;

    uint albedo;
    uint normal;
    uint ORM;
    uint emissive;

    uint instanceID;
};

void main(in float4 iPosition : SV_Position, in VSOut vsOutput, out float4 color : SV_Target)
{
    color = float4(1, 0, 1, 1);
}