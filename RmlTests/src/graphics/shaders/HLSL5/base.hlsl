#pragma pack_matrix(column_major)

#define MAX_NUM_STOPS 16

struct VSInput
{
    float2 position : POSITION;
    float4 color0 : COLOR0;
    float2 texCoord0 : TEXCOORD0;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float4 color0 : COLOR0;
    float2 texCoord0 : TEXCOORD0;
};

typedef VSOutput PSInput;

struct ExternalData
{
    float2 m_Translate;
    float2 m_Offset;
    float4x4 m_Transform;
};

ConstantBuffer<ExternalData> m_ExternalData : register(b0);

VSOutput vs_main(VSInput inputData)
{
    VSOutput outputData;
    outputData.color0 = inputData.color0;
    outputData.texCoord0 = inputData.texCoord0;
    
    float2 translatedPos = inputData.position + m_ExternalData.m_Translate.xy;
    float4 outPos = mul(float4(translatedPos, 0.0, 1.0), m_ExternalData.m_Transform);

    outputData.position = outPos;
    
    return outputData;
}

float4 ps_color_main(PSInput inputData) : SV_TARGET0
{
    return inputData.color0;
}

Texture2D<float> m_Texture : register(t0);
SamplerState m_Sampler : register(s0);

float4 ps_tex_main(PSInput inputData) : SV_TARGET0
{
    float4 texColor = m_Texture.SampleLevel(m_Sampler, inputData.texCoord0, 0.0f);
    return texColor * inputData.color0;
}
