struct PSInput
{
    float4 pos : SV_POSITION;
};

cbuffer myBuffer
{
    float4x4 object;
}

struct ObjectData
{
    float4x4 model;
};
StructuredBuffer<ObjectData> myDynamicBuffer;


void main(in float3 position : ATTRIB0, out PSInput PSIn)
{
    ObjectData d = myDynamicBuffer[0];

    PSIn.pos = mul(d.model, float4(position, 1.0));
}