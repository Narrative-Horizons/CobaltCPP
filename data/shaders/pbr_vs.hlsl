struct MaterialData
{
    uint albedoIndex;
    uint normalIndex;
    uint ORMIndex;
    uint emissiveIndex;
};
StructuredBuffer<MaterialData> mData;

struct ObjectData
{
    float4x4 model;
};
StructuredBuffer<ObjectData> oData;

cbuffer DrawConstantBuffer
{
    float4x4 viewProjection;
}

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

void main(in float3 iPosition : ATTRIB0,
            in float2 iUV : ATTRIB1,
            in float3 iNormal : ATTRIB2,
            in float3 iTangent : ATTRIB3,
            in float3 iBitangent : ATTRIB4,
            in uint instanceID : ATTRIB5,

            out float4 oPosition : SV_Position,
            out VSOut vsOutput)
{
    ObjectData data = oData[instanceID];
    MaterialData material = mData[instanceID];

    float3 positionWorld = mul(data.model, float4(iPosition, 1.0f)).xyz;
    oPosition = mul(viewProjection, float4(positionWorld, 1.0));

    vsOutput.positionModel = iPosition;
    vsOutput.normalWorld = mul(data.model, float4(iNormal, 0.0f)).xyz;

    vsOutput.albedo = material.albedoIndex;
    vsOutput.normal = material.normalIndex;
    vsOutput.ORM = material.ORMIndex;
    vsOutput.emissive = material.emissiveIndex;
    vsOutput.instanceID = instanceID;
}