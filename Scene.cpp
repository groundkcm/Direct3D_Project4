//-----------------------------------------------------------------------------
// File: CScene.cpp
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "Scene.h"
#include <random>
#include <array>
#define OBJECTNUM 54

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::BuildDefaultLightsAndMaterials()
{
	m_nLights = 5;
	m_pLights = new LIGHT[m_nLights];
	::ZeroMemory(m_pLights, sizeof(LIGHT) * m_nLights);

	m_xmf4GlobalAmbient = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);

	m_pLights[0].m_bEnable = true;
	m_pLights[0].m_nType = POINT_LIGHT;
	m_pLights[0].m_fRange = 1000.0f;
	m_pLights[0].m_xmf4Ambient = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	m_pLights[0].m_xmf4Diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);	
	m_pLights[0].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
	m_pLights[0].m_xmf3Position = XMFLOAT3(30.0f, 30.0f, 30.0f);
	m_pLights[0].m_xmf3Direction = XMFLOAT3(0.0f, 15.0f, 500.0f);
	m_pLights[0].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights[1].m_bEnable = true;
	m_pLights[1].m_nType = SPOT_LIGHT;
	m_pLights[1].m_fRange = 500.0f;
	m_pLights[1].m_xmf4Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_pLights[1].m_xmf4Diffuse = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
	m_pLights[1].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights[1].m_xmf3Position = XMFLOAT3(-50.0f, 20.0f, -5.0f);
	m_pLights[1].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_pLights[1].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights[1].m_fFalloff = 8.0f;
	m_pLights[1].m_fPhi = (float)cos(XMConvertToRadians(40.0f));
	m_pLights[1].m_fTheta = (float)cos(XMConvertToRadians(20.0f));
	m_pLights[2].m_bEnable = true;
	m_pLights[2].m_nType = DIRECTIONAL_LIGHT;
	m_pLights[2].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights[2].m_xmf4Diffuse = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights[2].m_xmf4Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.0f);
	m_pLights[2].m_xmf3Direction = XMFLOAT3(0.0f, -0.5f, 0.0f);
	m_pLights[3].m_bEnable = true;
	m_pLights[3].m_nType = SPOT_LIGHT;
	m_pLights[3].m_fRange = 600.0f;
	m_pLights[3].m_xmf4Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights[3].m_xmf4Diffuse = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights[3].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights[3].m_xmf3Position = XMFLOAT3(50.0f, 30.0f, 30.0f);
	m_pLights[3].m_xmf3Direction = XMFLOAT3(0.0f, 1.0f, 1.0f);
	m_pLights[3].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights[3].m_fFalloff = 8.0f;
	m_pLights[3].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights[3].m_fTheta = (float)cos(XMConvertToRadians(30.0f));
	m_pLights[4].m_bEnable = true;
	m_pLights[4].m_nType = POINT_LIGHT;
	m_pLights[4].m_fRange = 800.0f;
	m_pLights[4].m_xmf4Ambient = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	m_pLights[4].m_xmf4Diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	m_pLights[4].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
	m_pLights[4].m_xmf3Position = XMFLOAT3(30.0f, 30.0f, 30.0f);
	m_pLights[4].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_pLights[4].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.001f, 0.0001f);
}

random_device rd;
default_random_engine dre{ rd() }; 
uniform_int_distribution<int> uid(1, 3);

void CScene::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);

	CMaterial::PrepareShaders(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);

	BuildDefaultLightsAndMaterials();

	m_nGameObjects = OBJECTNUM;
	m_ppGameObjects = new CGameObject*[m_nGameObjects];

	CCarObject* pcarObject = NULL;
	CGameObject * pPlaneModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/B_Plane.bin");

	pcarObject = new CCarObject();
	pcarObject->SetChild(pPlaneModel, true);
	pcarObject->OnInitialize();
	pcarObject->SetPosition(+0.0f, 0.0f, 40.0f);
	pcarObject->SetScale(50.0f, 100.0f, 150.0f);
	pcarObject->Rotate(0.0f, 90.0f, 0.0f);
	m_ppGameObjects[0] = pcarObject;

	CGameObject* pCubeModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/Cube.bin");

	for (int i{ 1 }; i < 5; ++i) {
		pcarObject = new CCarObject();
		pcarObject->SetChild(pCubeModel, true);
		pcarObject->OnInitialize();
		pcarObject->SetScale(10.0f, 10.0f, 600.0f);
		if (i == 1) {
			pcarObject->Rotate(0.0f, 0.0f, 0.0f);
			pcarObject->SetPosition(-250.0f, 0.0f, -150.0f);
		}
		else if (i == 2) {
			pcarObject->Rotate(0.0f, 0.0f, 0.0f);
			pcarObject->SetPosition(250.0f, 0.0f, -150.0f);
		}
		else if (i == 3) {
			pcarObject->Rotate(0.0f, 0.0f, 0.0f);
			pcarObject->SetPosition(-250.0f, 0.0f, 450.0f);
		}
		else {
			pcarObject->Rotate(0.0f, 0.0f, 0.0f);
			pcarObject->SetPosition(250.0f, 0.0f, 450.0f);
		}
		m_ppGameObjects[i] = pcarObject;
	}

	CGameObject* pYellowCubeModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/YellowCube.bin");

	pcarObject = new CCarObject();
	pcarObject->SetChild(pYellowCubeModel, true);
	pcarObject->OnInitialize();
	pcarObject->SetScale(7.0f, 2.0f, 1200.0f);
	pcarObject->Rotate(0.0f, 0.0f, 0.0f);
	pcarObject->SetPosition(0.0f, 0.0f, 150.0f);
	m_ppGameObjects[5] = pcarObject;

	CGameObject* pWhiteCubeModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/WhiteCube.bin");

	for (int i{ 6 }; i < 30; ++i) {
		pcarObject = new CCarObject();
		pcarObject->SetChild(pWhiteCubeModel, true);
		pcarObject->OnInitialize();
		pcarObject->SetScale(7.0f, 2.0f, 100.0f);
		pcarObject->Rotate(0.0f, -180.0f, 0.0f);
		if (i % 4 == 2)
			pcarObject->SetPosition(-160.0f, 0.0f, -400.0f + (i - 6) * 55.0f);
		else if (i % 4 == 3)
			pcarObject->SetPosition(-80.0f, 0.0f, -400.0f + (i - 7) * 55.0f);
		else if (i % 4 == 0)
			pcarObject->SetPosition(80.0f, 0.0f, -400.0f + (i - 8) * 55.0f);
		else
			pcarObject->SetPosition(160.0f, 0.0f, -400.0f + (i - 9) * 55.0f);
		m_ppGameObjects[i] = pcarObject;
	}

	CGameObject* pTreeModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/Tree.bin");

	for (int i{ 30 }; i < 42; ++i) {
		pcarObject = new CCarObject();
		pcarObject->SetChild(pTreeModel, true);
		pcarObject->OnInitialize();
		pcarObject->SetScale(10.0f, 10.0f, 10.0f);
		pcarObject->Rotate(0.0f, -180.0f, 0.0f);
		if (!(i % 2))
			pcarObject->SetPosition(-260.0f, -10.0f, 750.0f - (i - 30) * 110.0f);
		else
			pcarObject->SetPosition(260.0f, -10.0f, 750.0f - (i - 31) * 110.0f);
		m_ppGameObjects[i] = pcarObject;
	}

	CGameObject* pAmbulanceModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/Ambulance.bin");
	CGameObject* pPoliceCarModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/PoliceCar.bin");
	CGameObject* pOldCarModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/SportCar.bin");
	CGameObject* pForkModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/Fork.bin");

	pcarObject = new CCarObject();
	pcarObject->SetChild(pAmbulanceModel, true);
	pcarObject->OnInitialize();
	pcarObject->SetPosition(40.0f, 0.0f, -100.0f);
	pcarObject->SetScale(15.0f, 15.0f, 15.0f);
	pcarObject->Rotate(0.0f, -180.0f, 0.0f);
	m_ppGameObjects[42] = pcarObject;

	pcarObject = new CCarObject();
	pcarObject->SetChild(pAmbulanceModel, true);
	pcarObject->OnInitialize();
	pcarObject->SetPosition(40.0f, 0.0f, 500.0f);
	pcarObject->SetScale(15.0f, 15.0f, 15.0f);
	pcarObject->Rotate(0.0f, -180.0f, 0.0f);
	m_ppGameObjects[43] = pcarObject;

	pcarObject = new CCarObject();
	pcarObject->SetChild(pPoliceCarModel, true);
	pcarObject->OnInitialize();
	pcarObject->SetPosition(120.0f, 0.0f, 100.0f);
	pcarObject->SetScale(15.0f, 15.0f, 15.0f);
	pcarObject->Rotate(0.0f, -180.0f, 0.0f);
	m_ppGameObjects[44] = pcarObject;

	pcarObject = new CCarObject();
	pcarObject->SetChild(pPoliceCarModel, true);
	pcarObject->OnInitialize();
	pcarObject->SetPosition(40.0f, 0.0f, 0.0f);
	pcarObject->SetScale(15.0f, 15.0f, 15.0f);
	pcarObject->Rotate(0.0f, -180.0f, 0.0f);
	m_ppGameObjects[45] = pcarObject;

	pcarObject = new CCarObject();
	pcarObject->SetChild(pOldCarModel, true);
	pcarObject->OnInitialize();
	pcarObject->SetPosition(200.0f, 0.0f, 600.0f);
	pcarObject->SetScale(15.0f, 15.0f, 15.0f);
	pcarObject->Rotate(0.0f, -180.0f, 0.0f);
	m_ppGameObjects[46] = pcarObject;

	pcarObject = new CCarObject();
	pcarObject->SetChild(pOldCarModel, true);
	pcarObject->OnInitialize();
	pcarObject->SetPosition(200.0f, 0.0f, -200.0f);
	pcarObject->SetScale(15.0f, 15.0f, 15.0f);
	pcarObject->Rotate(0.0f, -180.0f, 0.0f);
	m_ppGameObjects[47] = pcarObject;

	pcarObject = new CCarObject();
	pcarObject->SetChild(pForkModel, true);
	pcarObject->OnInitialize();
	pcarObject->SetPosition(120.0f, 0.0f, -300.0f);
	pcarObject->SetScale(15.0f, 15.0f, 15.0f);
	pcarObject->Rotate(0.0f, -180.0f, 0.0f);
	m_ppGameObjects[48] = pcarObject;

	//-------------------------------------- 순방향

	pcarObject = new CCarObject();
	pcarObject->SetChild(pAmbulanceModel, true);
	pcarObject->OnInitialize();
	pcarObject->SetPosition(-120.0f, 0.0f, 500.0f);
	pcarObject->SetScale(15.0f, 15.0f, 15.0f);
	m_ppGameObjects[49] = pcarObject;


	pcarObject = new CCarObject();
	pcarObject->SetChild(pPoliceCarModel, true);
	pcarObject->OnInitialize();
	pcarObject->SetPosition(-40.0f, 0.0f, 300.0f);
	pcarObject->SetScale(15.0f, 15.0f, 15.0f);
	m_ppGameObjects[50] = pcarObject;

	pcarObject = new CCarObject();
	pcarObject->SetChild(pPoliceCarModel, true);
	pcarObject->OnInitialize();
	pcarObject->SetPosition(-40.0f, 0.0f, 0.0f);
	pcarObject->SetScale(15.0f, 15.0f, 15.0f);
	m_ppGameObjects[51] = pcarObject;

	pcarObject = new CCarObject();
	pcarObject->SetChild(pOldCarModel, true);
	pcarObject->OnInitialize();
	pcarObject->SetPosition(-200.0f, 0.0f, 600.0f);
	pcarObject->SetScale(15.0f, 15.0f, 15.0f);
	m_ppGameObjects[52] = pcarObject;

	pcarObject = new CCarObject();
	pcarObject->SetChild(pOldCarModel, true);
	pcarObject->OnInitialize();
	pcarObject->SetPosition(-200.0f, 0.0f, -200.0f);
	pcarObject->SetScale(15.0f, 15.0f, 15.0f);
	m_ppGameObjects[53] = pcarObject;



	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CScene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();

	if (m_ppGameObjects)
	{
		for (int i = 0; i < m_nGameObjects; i++) if (m_ppGameObjects[i]) m_ppGameObjects[i]->Release();
		delete[] m_ppGameObjects;
	}

	ReleaseShaderVariables();

	if (m_pLights) delete[] m_pLights;
}

ID3D12RootSignature *CScene::CreateGraphicsRootSignature(ID3D12Device *pd3dDevice)
{
	ID3D12RootSignature *pd3dGraphicsRootSignature = NULL;

	D3D12_ROOT_PARAMETER pd3dRootParameters[3];

	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[0].Descriptor.ShaderRegister = 1; //Camera
	pd3dRootParameters[0].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[1].Constants.Num32BitValues = 32;
	pd3dRootParameters[1].Constants.ShaderRegister = 2; //GameObject
	pd3dRootParameters[1].Constants.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[2].Descriptor.ShaderRegister = 4; //Lights
	pd3dRootParameters[2].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = 0;
	d3dRootSignatureDesc.pStaticSamplers = NULL;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;

	ID3DBlob *pd3dSignatureBlob = NULL;
	ID3DBlob *pd3dErrorBlob = NULL;
	D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pd3dSignatureBlob, &pd3dErrorBlob);
	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(), pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void **)&pd3dGraphicsRootSignature);
	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();

	return(pd3dGraphicsRootSignature);
}

void CScene::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(LIGHTS) + 255) & ~255); //256의 배수
	m_pd3dcbLights = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbLights->Map(0, NULL, (void **)&m_pcbMappedLights);
}

void CScene::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	::memcpy(m_pcbMappedLights->m_pLights, m_pLights, sizeof(LIGHT) * m_nLights);
	::memcpy(&m_pcbMappedLights->m_xmf4GlobalAmbient, &m_xmf4GlobalAmbient, sizeof(XMFLOAT4));
	::memcpy(&m_pcbMappedLights->m_nLights, &m_nLights, sizeof(int));
}

void CScene::ReleaseShaderVariables()
{
	if (m_pd3dcbLights)
	{
		m_pd3dcbLights->Unmap(0, NULL);
		m_pd3dcbLights->Release();
	}
}

void CScene::ReleaseUploadBuffers()
{
	for (int i = 0; i < m_nGameObjects; i++) m_ppGameObjects[i]->ReleaseUploadBuffers();
}

bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	/*switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case '1': m_pPlayer->booster = true; break;
		}
		break;
	default:
		break;
	}*/
	return(false);
}

bool CScene::ProcessInput(UCHAR *pKeysBuffer)
{
	return(false);
}

void CScene::Collision()
{
	m_pPlayer->m_xmOOBB = BoundingOrientedBox(XMFLOAT3(m_pPlayer->GetPosition()), XMFLOAT3(25.0f, 10.0f, 35.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_pPlayer->m_pObjectCollided = NULL;

	for (int i = 42; i < m_nGameObjects; ++i) {
		m_ppGameObjects[i]->m_xmOOBB = BoundingOrientedBox(XMFLOAT3(m_ppGameObjects[i]->GetPosition()), XMFLOAT3(20.0f, 10.0f, 35.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
		m_ppGameObjects[i]->m_pObjectCollided = NULL;
	}

	for (int i = 42; i < m_nGameObjects; ++i) {
		if (m_ppGameObjects[i]->m_xmOOBB.Intersects(m_pPlayer->m_xmOOBB)) {
			if (m_pPlayer->GetPosition().x >= m_ppGameObjects[i]->GetPosition().x)
				m_ppGameObjects[i]->rcrash = true;
			else if (m_pPlayer->GetPosition().x < m_ppGameObjects[i]->GetPosition().x) 
				m_ppGameObjects[i]->lcrash = true;
		}
		for (int j = (i + 1); j < m_nGameObjects; j++)
		{
			if (m_ppGameObjects[i]->m_xmOOBB.Intersects(m_ppGameObjects[j]->m_xmOOBB))
			{
				m_ppGameObjects[i]->m_pObjectCollided = m_ppGameObjects[j];
				m_ppGameObjects[j]->m_pObjectCollided = m_ppGameObjects[i];
			}
		}
	}

	for (int i = 42; i < m_nGameObjects; ++i) {
		int choice{ uid(dre) };
		float lane{};
		switch (choice) {
		case 1:
			lane = 200.0f;
			break;
		case 2:
			lane = 120.0f;
			break;
		default:
			lane = 40.0f;
		}
		if (m_ppGameObjects[i]->lcrash || m_ppGameObjects[i]->rcrash) {
			if (m_ppGameObjects[i]->crashnum > 36) {
				m_ppGameObjects[i]->crashnum = 0;
				m_ppGameObjects[i]->lcrash = false;
				m_ppGameObjects[i]->rcrash = false;
				if (i < 49)
					m_ppGameObjects[i]->SetPosition(lane, 0.0f, 850.0f);
				else
					m_ppGameObjects[i]->SetPosition(-lane, 0.0f, 850.0f);
			}
			if (m_ppGameObjects[i]->rcrash) {
				//m_ppGameObjects[i]->Rotate(0.0f, 0.0f, 10.0f);
				m_ppGameObjects[i]->SetPosition(m_ppGameObjects[i]->GetPosition().x - 2.5f, m_ppGameObjects[i]->GetPosition().y + 2.0f, m_ppGameObjects[i]->GetPosition().z);
			}
			else if (m_ppGameObjects[i]->lcrash) {
				//m_ppGameObjects[i]->Rotate(0.0f, 0.0f, 10.0f);
				m_ppGameObjects[i]->SetPosition(m_ppGameObjects[i]->GetPosition().x + 2.5f, m_ppGameObjects[i]->GetPosition().y + 2.0f, m_ppGameObjects[i]->GetPosition().z);
			}
			++(m_ppGameObjects[i]->crashnum);
		}
		if (m_ppGameObjects[i]->m_pObjectCollided && (m_ppGameObjects[i]->GetPosition().z >= 700.0f)) {
			if (i < 49)
				m_ppGameObjects[i]->SetPosition(lane, 0.0f, 850.0f);
			else
				m_ppGameObjects[i]->SetPosition(-lane, 0.0f, 850.0f);
		}
	}
	
}

void CScene::AnimateObjects(float fTimeElapsed)
{
	m_fElapsedTime = fTimeElapsed;
	static XMFLOAT3 location{};
	for (int i = 0; i < m_nGameObjects; i++) {
		int choice{ uid(dre) };
		float lane{};
		switch (choice) {
		case 1:
			lane = 200.0f;
			break;
		case 2:
			lane = 120.0f;
			break;
		default:
			lane = 40.0f;
		}
		if (i >= 6 && m_pPlayer->start) {		// 랜덤위치 이동생성
			location = m_ppGameObjects[i]->GetPosition();
			if (location.z < -450.0f) {
				if (i < 42)
					m_ppGameObjects[i]->SetPosition(location.x, 0.0f, 850.0f);
				else if (i < 49)
					m_ppGameObjects[i]->SetPosition(lane, 0.0f, 850.0f);
				else 
					m_ppGameObjects[i]->SetPosition(-lane, 0.0f, 850.0f);
			}
			if (m_pPlayer->booster) {
				if (m_pPlayer->bossternum >= 150) {
					m_pPlayer->booster = false;
					m_pPlayer->bossternum = 0;
				}
				if (i < 42)
					m_ppGameObjects[i]->MoveForward(6.0f);
				else if (i < 49)
					m_ppGameObjects[i]->MoveForward(8.0f);
				else
					m_ppGameObjects[i]->MoveForward(-5.0f);
				m_pPlayer->bossternum += 1;
			}
			else {
				if (i < 42)
					m_ppGameObjects[i]->MoveForward(3.0f);
				else if (i < 49)
					m_ppGameObjects[i]->MoveForward(5.0f);
				else
					m_ppGameObjects[i]->MoveForward(-2.0f);
			}
			
		}
		m_ppGameObjects[i]->Animate(fTimeElapsed, NULL);
	}

	if (m_pLights)
	{
		m_pLights[1].m_xmf3Position = m_pPlayer->GetPosition();
		m_pLights[1].m_xmf3Direction = m_pPlayer->GetLookVector();
		m_pLights[4].m_xmf3Position = XMFLOAT3(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y + 30.0f, m_pPlayer->GetPosition().z + 50.0f);
		m_pLights[4].m_xmf3Direction = m_pPlayer->GetPosition();
	}

	Collision();
}

void CScene::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pCamera->UpdateShaderVariables(pd3dCommandList);

	UpdateShaderVariables(pd3dCommandList);

	D3D12_GPU_VIRTUAL_ADDRESS d3dcbLightsGpuVirtualAddress = m_pd3dcbLights->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(2, d3dcbLightsGpuVirtualAddress); //Lights

	for (int i = 0; i < m_nGameObjects; i++)
	{
		if (m_ppGameObjects[i])
		{
			m_ppGameObjects[i]->Animate(m_fElapsedTime, NULL);
			m_ppGameObjects[i]->UpdateTransform(NULL);
			m_ppGameObjects[i]->Render(pd3dCommandList, pCamera);
		}
	}
}

