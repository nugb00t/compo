uniform extern texture TEX_DIFFUSE;

sampler TEX_DIFFUSE_SAMPLER = sampler_state {
    Texture = <TEX_DIFFUSE>;
};

struct VertexOut {
	float4 posH		: POSITION0;
    float2 tex		: TEXCOORD0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VertexOut TransformVS(float3 posL : POSITION0, float2 tex : TEXCOORD0) {
	VertexOut vertex = (VertexOut)0;

	// Just pass the vertex color into the pixel shader.
	vertex.posH = float4(posL, 1.0f);
    vertex.tex = tex;

	return vertex;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Pixel shader
float4 TransformPS(VertexOut vertex) : COLOR {
	float4 color = tex2D(TEX_DIFFUSE_SAMPLER, vertex.tex);
	return color;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Techniques
technique TransformTech {
	pass P0 {
		vertexShader = compile vs_3_0 TransformVS();
		pixelShader  = compile ps_3_0 TransformPS();

		ZWriteEnable = False;
		AlphaBlendEnable = True;
		SrcBlend = One;
		DestBlend = Zero;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
