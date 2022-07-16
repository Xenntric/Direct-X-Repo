#include "Sphere.h"
#include "BindableTemplate.h"
#include <string>

Sphere::Sphere(Renderer& render, float x, float y, float z,  float radius, int sliceCount, int stackCount)
	:
	x(x),
	y(y),
	z(z),
	radius(radius),
	r(),
	droll(),
	dpitch(),
	dyaw(),
	dphi(),
	dtheta(),
	dchi(),
	chi(),
	theta(),
	phi(),
	sliceCount(sliceCount),
	stackCount(stackCount),
	phiStep((pi / stackCount)),
	thetaStep((2.0f * pi / sliceCount))
{

	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		} pos;
	};

	std::vector<Vertex> vertices = {};
	// south pole
	vertices.push_back(Vertex{ 0.0f, -radius, 0.0 });

	for (int i = 1; i <= stackCount - 1; i++) 
	{
		phi = i * phiStep;
		std::string phistep = "phi: " + std::to_string(phi) + "\n";
		//OutputDebugString(phistep.c_str());
		
		for (int j = 0; j <= sliceCount; j++) 
		{

			theta = j * thetaStep;
			std::string thetastep = "theta: " + std::to_string(theta) +"\n";
			//OutputDebugString(thetastep.c_str());

			Vec3 pos = Vec3((radius * sinf(phi) * cosf(theta)),
					(radius * cosf(phi)),
					(radius * sinf(phi) * sinf(theta)));

			/*Vec3 currentRadius = Vec3(
				-radius * sin(phi) * sin(theta), 
				0, 
				radius * sin(phi) * cos(theta));
			currentRadius.Normalize();

			Vec3 posNorm = pos;
			posNorm.Normalize();

			Vec2 UV = Vec2(theta / (pi * 2), phi / pi);*/

			// Vertex( x,radius,z,?,?,y,?,?,?,?,?,)
		
			vertices.emplace_back(Vertex{	pos.x, 
											pos.y, 
											pos.z});

			std::string debug =  "{" +	std::to_string(pos.x) + ", " +
										std::to_string(pos.y) + ", " +
										std::to_string(pos.z) + "}\n" ;

			//OutputDebugString(debug.c_str());

		}
	}
	vertices.push_back(Vertex{ 0.0f, radius, 0.0 });


	AddBind(std::make_unique<VertexBuffer>(render, vertices));

	auto pvs = std::make_unique<VertexShader>(render, L"VertexShader.cso");
	auto pvsbc = pvs->GetBytecode();
	AddBind(std::move(pvs));

	AddBind(std::make_unique<PixelShader>(render, L"PixelShader.cso"));

	std::vector<unsigned short> indices = {};

	for (unsigned short i = 1; i <= sliceCount; i++)
	{
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i);
	}

	int baseIndex = 1;
	int ringVertexCount = sliceCount + 1;

	for (int i = 0; i < stackCount - 2; i++) {
		for (int j = 0; j < sliceCount; j++) {
			indices.push_back(baseIndex +	i		* ringVertexCount + j);
			indices.push_back(baseIndex +	i		* ringVertexCount + j + 1);
			indices.push_back(baseIndex + (	i + 1)	* ringVertexCount + j);
			indices.push_back(baseIndex + (	i + 1)	* ringVertexCount + j);
			indices.push_back(baseIndex +	i		* ringVertexCount + j + 1);
			indices.push_back(baseIndex + (	i + 1)	* ringVertexCount + j + 1);
		}
	}

	int southPoleIndex = vertices.size() - 1;
	baseIndex = southPoleIndex - ringVertexCount;
	for (int i = 0; i < sliceCount; i++) {
		indices.push_back(southPoleIndex);
		indices.push_back(baseIndex + i);
		indices.push_back(baseIndex + i + 1);
	}
	
	AddIndexBuffer(std::make_unique<IndexBuffer>(render, indices));


	/*struct ConstantBuffer2
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} face_colors[6];
	};
	const ConstantBuffer2 cb2 =
	{
		{
			{ 1.0f,0.0f,1.0f },
			{ 1.0f,0.0f,0.0f },
			{ 0.0f,1.0f,0.0f },
			{ 0.0f,0.0f,1.0f },
			{ 1.0f,1.0f,0.0f },
			{ 0.0f,1.0f,1.0f },
		}
	};
	AddBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2>>(render, cb2));*/

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	AddBind(std::make_unique<InputLayout>(render, ied, pvsbc));

	AddBind(std::make_unique<Topology>(render, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformBuffer>(render, *this));
}

void Sphere::Update(float dt) noexcept
{
	/*roll += droll * dt;
	pitch += dpitch * dt;
	yaw += dyaw * dt;
	theta += dtheta * dt;
	phi += dphi * dt;
	chi += dchi * dt;*/
}

DirectX::XMMATRIX Sphere::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
		DirectX::XMMatrixTranslation(x, y, z);
}

void Sphere::setTransformXYZ(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}
Vec3 Sphere::getTransformXYZ()
{
	return Vec3(x,y,z);
}