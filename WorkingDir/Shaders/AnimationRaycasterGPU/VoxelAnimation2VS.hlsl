#include "BonesHelpers.hlsli"


#define MAX_BONES 200



// ================================ //
//
cbuffer CameraConstants : register( b0 )
{
	matrix			ViewMatrix;					///< View matrix.
	matrix			ProjectionMatrix;			///< Projection matrix.
	float3			CameraPosition;				///< Position of camera in world space.
}

// ================================ //
//
cbuffer MeshContants : register( b2 )
{
	float3			Translate;
	float			Scale;
	float			OffsetShell;
}


// ================================ //
//
struct InputVS
{
	float4			Position : POSITION;
	uint4			BlendIdx : BLENDINDICES;
	float4			BlendWeights : BLENDWEIGHT;
};

// ================================ //
//
struct OutputVS
{
	linear float4			Position : SV_POSITION;
	linear float3			WorldPosition : TEXCOORD0;
	linear float3			ModelPosition : TEXCOORD1;
	nointerpolation uint4	BlendIdx : BLENDINDICES;
	linear float4			BlendWeights : BLENDWEIGHT;
};


// ================================ //
//
OutputVS	main( InputVS input )
{
	OutputVS output = (OutputVS)0;

	float4 position = ComputeBonesPositionsTransform( input.Position, input.BlendIdx, input.BlendWeights );

	output.WorldPosition = position.xyz;
	output.Position = mul( position, ViewMatrix );
	output.Position = mul( output.Position, ProjectionMatrix );
	output.BlendIdx = input.BlendIdx;
	output.BlendWeights = input.BlendWeights;

	output.ModelPosition = input.Position.xyz;
	output.ModelPosition += Translate;
	output.ModelPosition = output.ModelPosition * Scale;

	return output;
}

