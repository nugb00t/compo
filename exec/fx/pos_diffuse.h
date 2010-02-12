// Uniforms
uniform extern float4x4 TRANSFORM;

// Structure
struct OutputVS {
	float4 posH		: POSITION0;
	float4 color	: COLOR0;
};

// Vertex shader
OutputVS TransformVS(float3 posL : POSITION0, float4 c : COLOR0) {
	// Zero out our output
	OutputVS outVS = (OutputVS)0;

	// Transform to homogeneous clip space
	outVS.posH = mul(float4(posL, 1.0f), TRANSFORM);

	// Just pass the vertex color into the pixel shader.
    outVS.color = c;

	// Done--return the output.
	return outVS;
}

// Pixel shader
float4 TransformPS(OutputVS outVS) : COLOR {
	return outVS.color;
}

// Techniques
technique TransformTech {
	pass P0 {
		// Specify the vertex and pixel shader associated with this pass
		vertexShader = compile vs_3_0 TransformVS();
		pixelShader  = compile ps_3_0 TransformPS();
	}
}
