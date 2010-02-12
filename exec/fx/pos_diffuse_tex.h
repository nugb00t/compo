uniform extern float4x4 TRANSFORM;
uniform extern texture TEX_DIFFUSE;

sampler TEX_DIFFUSE_SAMPLER = sampler_state {
    Texture = <TEX_DIFFUSE>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
};

struct VertexOut {
	float4 posH		: POSITION0;
	float4 color	: COLOR0;
    float2 tex		: TEXCOORD0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VertexOut TransformVS(float3 posL : POSITION0, float4 color : COLOR0, float2 tex : TEXCOORD0) {
	VertexOut vertex = (VertexOut)0;

	// Transform to homogeneous clip space
	vertex.posH = mul(float4(posL, 1.0f), TRANSFORM);

	// Just pass the vertex color into the pixel shader.
    vertex.color = color;
    vertex.tex = tex;

	return vertex;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Pixel shader
float4 TransformPS(VertexOut vertex) : COLOR {
	float4 color = tex2D(TEX_DIFFUSE_SAMPLER, vertex.tex);
	color.xyz *= vertex.color.xyz;
	return color;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Techniques
technique TransformTech {
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend = srcalpha;
		DestBlend = invsrcColor;

		vertexShader = compile vs_3_0 TransformVS();
		pixelShader  = compile ps_3_0 TransformPS();
	}
}
