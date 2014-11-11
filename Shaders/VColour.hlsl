// Colour vertex shader

cbuffer matrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

// typedefs

//input types
struct vertexTypes
{
	float4 pos : POSITION;
	float4 color : COLOR;
};

//input types
struct pixelTypes
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

pixelTypes VertexColourShader(vertexTypes input)
{
	pixelTypes output;

	input.pos.w = 1.0f;

	output.pos = mul(input.pos, worldMatrix);
	output.pos = mul(input.pos, viewMatrix);
	output.pos = mul(input.pos, projectionMatrix);

	output.color = input.colour;

	return output;
}