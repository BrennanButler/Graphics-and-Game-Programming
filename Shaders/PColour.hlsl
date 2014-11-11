
struct pixelTypes
{
	float4 pos : POSITION;
	float4 color : COLOR;
};

float4 ColourPixelShader(pixelTypes input) : SV_POSITION
{
	return input.color;
}