#pragma once


#include "IRaycaster.h"

#include "VoxelRenderer/Application/Presentation/BlitEffect.h"


namespace vr
{

/**@brief Bit shifts for specific position in child mask in OctreeNode.*/
typedef uint8 ChildFlag;



/**@brief GPU raycaster using compute shaders.*/
class ShellMeshRenderer : public IRaycaster
{
protected:

	IRenderer*				m_renderer;
	ResourceManager*		m_resourceManager;

	ResourcePtr< BufferObject >		m_cameraBuffer;

	ResourcePtr< VertexShader >		m_vertexShader;
	ResourcePtr< PixelShader >		m_pixelShader;

	ResourcePtr< ShaderInputLayout >	m_layout;

	ResourcePtr< BlendingState >		m_blendingState;
	ResourcePtr< RasterizerState >		m_rasterizerState;
	ResourcePtr< DepthStencilState >	m_depthStencilState;

	ResourcePtr< RenderTargetObject >	m_shellMeshTarget;

	BlitEffectUPtr		m_blitEffect;

	uint16				m_width;
	uint16				m_height;

public:
	explicit			ShellMeshRenderer();


	virtual void			RenderShellMeshes	( const std::vector< ShellMeshPtr >& shellMeshes, CameraActor* camera )					override;
	virtual void			Render				( OctreePtr octree, RenderTargetObject* svoRenderTarget, CameraActor* camera )			override;
	virtual void			Init				( IRenderer* renderer, ResourceManager* resourceManager )								override;
	virtual void			ProcessInput		( const sw::input::MouseState& mouse, const sw::input::KeyboardState& keyboard )		override;


private:

	void					UpdateCamera			( CameraActor* camera );
	void					ReallocateRenderTarget	( uint16 newWidth, uint16 newHeight );

};


}	// vr
