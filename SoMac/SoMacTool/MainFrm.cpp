
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "SoMacTool.h"

#include "MainFrm.h"
#include "GameView.h"
#include "HierachyView.h"
#include "ComponentView.h"
#include "ButtonView.h"
#include "DebugView.h"

#include "PathMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Layer.h"

#include "GameObject.h"
#include "Transform.h"
#include "ResMgr.h"
#include "MeshRenderer.h"
#include "Animator.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WORK_SPACE_X 1900
#define WORK_SPACE_Y 1070

#define GAME_VIEW_X 1200
#define GAME_VIEW_Y 675

#define BUTTON_VIEW_X GAME_VIEW_X
#define BUTTON_VIEW_Y 30

#define DEBUG_VIEW_X GAME_VIEW_X
#define DEBUG_VIEW_Y WORK_SPACE_Y - GAME_VIEW_Y - BUTTON_VIEW_Y

#define HIERACHY_VIEW_X 300
#define HIERACHY_VIEW_Y WORK_SPACE_Y

#define COMPONENT_VIEW_X WORK_SPACE_X - GAME_VIEW_X - HIERACHY_VIEW_X
#define COMPONENT_VIEW_Y WORK_SPACE_Y


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_GAMEOBJECT_EMPTY, &CMainFrame::OnGameObjectEmpty)
	ON_COMMAND(ID_GAMEOBJECT_RECT, &CMainFrame::OnGameObjectRect)
	ON_COMMAND(ID_GAMEOBJECT_STDANIM, &CMainFrame::OnGameObjectStdAnim)
	ON_COMMAND(ID_SCENE_SAVE, &CMainFrame::OnSceneSave)
	ON_COMMAND(ID_SCENE_LOAD, &CMainFrame::OnSceneLoad)
END_MESSAGE_MAP()

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::Update()
{
	CComponentView* pComView = (CComponentView*)GetComponentView();
	pComView->Update();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_MainSplitter.SetBorderSize(CPoint(0, 0), CPoint(1, 1));
	m_SubSplitter.SetBorderSize(CPoint(0, 0), CPoint(1, 1));

	// FrameWnd 3�� ����
	m_MainSplitter.CreateStatic(this, 1, 3);
	m_MainSplitter.SetColumnInfo(0, GAME_VIEW_X-4, GAME_VIEW_X-4);

	// Frame Wnd 0, 0 ��Ҹ� 3������ ����
	m_SubSplitter.CreateStatic(&m_MainSplitter, 3, 1, WS_CHILD | WS_VISIBLE, m_MainSplitter.IdFromRowCol(0, 0));

	// ������ ������ View �� �����Ѵ�.
	m_MainSplitter.CreateView(0, 1, RUNTIME_CLASS(CHierachyView), CSize(HIERACHY_VIEW_X, HIERACHY_VIEW_Y), NULL);
	m_MainSplitter.CreateView(0, 2, RUNTIME_CLASS(CComponentView), CSize(COMPONENT_VIEW_X, COMPONENT_VIEW_Y), NULL);

	m_SubSplitter.CreateView(0, 0, RUNTIME_CLASS(CButtonView), CSize(BUTTON_VIEW_X, BUTTON_VIEW_Y), NULL);
	m_SubSplitter.CreateView(1, 0, RUNTIME_CLASS(CGameView), CSize(GAME_VIEW_X, GAME_VIEW_Y), NULL);
	m_SubSplitter.CreateView(2, 0, RUNTIME_CLASS(CDebugView), CSize(DEBUG_VIEW_X, DEBUG_VIEW_Y), NULL);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame �޽��� ó����

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// �� â���� ��Ŀ���� �̵��մϴ�.
}

void CMainFrame::OnGameObjectEmpty()
{
	// ����ִ� ���� ������Ʈ�� �����. 
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->FindLayer(LAYER_DEFAULT);
	CGameObject* pObj = new CGameObject();
	pObj->SetTag(L"Empty GameObject");
	CTransform* pTrans = (CTransform*)pObj->AddComponent<CTransform>(new CTransform);
	pTrans->SetLocalPosition(Vec3(0.f, 0.f, 10.f));
	pTrans->SetLocalScale(Vec3(150.f, 150.f, 1.f));
	pLayer->AddGameObject(pObj);
	CComponentView* pComView = (CComponentView*)GetComponentView();
	pComView->SetGameObject(pObj);
}

void CMainFrame::OnGameObjectRect()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer * pLayer = pCurScene->FindLayer(LAYER_DEFAULT);
	CGameObject* pObj = CGameObject::CreateGameObject(L"Rect GameObject");
	CTransform* pTrans = pObj->GetTransform();
	pTrans->SetLocalPosition(Vec3(0.f, 0.f, 10.f));
	pTrans->SetLocalScale(Vec3(150.f, 150.f, 1.f));
	CMeshRenderer* pMeshRenderer = pObj->GetMeshRender();
	pMeshRenderer->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pMeshRenderer->SetMaterial((CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"Default"));
	pLayer->AddGameObject(pObj);
	CComponentView* pComView = (CComponentView*)GetComponentView();
	pComView->SetGameObject(pObj);
}

void CMainFrame::OnGameObjectStdAnim()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer * pLayer = pCurScene->FindLayer(LAYER_DEFAULT);
	CGameObject* pObj = CGameObject::CreateGameObject(L"Std GameObject");
	CTransform* pTrans = pObj->GetTransform();
	pTrans->SetLocalPosition(Vec3(0.f, 0.f, 10.f));
	pTrans->SetLocalScale(Vec3(150.f, 150.f, 1.f));
	CMeshRenderer* pMeshRenderer = pObj->GetMeshRender();
	pMeshRenderer->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pMeshRenderer->SetMaterial((CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"StandardMaterial"));
	pObj->AddComponent<CAnimator>(new CAnimator);
	pLayer->AddGameObject(pObj);
	CComponentView* pComView = (CComponentView*)GetComponentView();
	pComView->SetGameObject(pObj);
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// �׷��� ������ �⺻ ó���մϴ�.
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



void CMainFrame::OnSceneSave()
{
	wchar_t szFilter[] = L"Scene (*.scene) | *.scene; |";
	CFileDialog dlg(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, szFilter);
	CString strInitPath = CPathMgr::GetResourcePath();
	strInitPath += L"Scene";
	dlg.m_ofn.lpstrInitialDir = strInitPath;

	CString strPathName;
	if (IDOK == dlg.DoModal())
	{
		strPathName = dlg.GetPathName();
		wchar_t* pExt = CPathMgr::GetExtension(strPathName.GetBuffer());

		if (0 == wcslen(pExt))
			strPathName += L".scene";

	//	CSaveLoadMgr::GetInst()->SaveScene(strPathName.GetBuffer());
	}

}


void CMainFrame::OnSceneLoad()
{
	// TODO: Add your command handler code here
}
