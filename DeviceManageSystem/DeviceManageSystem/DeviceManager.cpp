#include "stdafx.h"
#include "DeviceManager.h"

#include <map>
#include <atlconv.h>
#include <shlwapi.h>

static CCriticalSection g_cs;

class DMLock
{
public:
	DMLock()
	{
		g_cs.Lock();
	}
	~DMLock()
	{
		g_cs.Unlock();
	}
};

CDeviceManager * CDeviceManager::pDeviceManager = NULL;

CDeviceManager::CDeviceManager()
{

}

CDeviceManager * CDeviceManager::Instance()
{
	if ( NULL == pDeviceManager )
	{
		DMLock dmLock;
		if ( NULL == pDeviceManager )
		{
			pDeviceManager = new CDeviceManager();
		}
	}

	return pDeviceManager;
}

void CDeviceManager::Initialize()
{
	CString path;
	GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);

	CFileFind ff;
	CString csFolder;
	csFolder.Format("%s\\Data\\*.dvi", path);
	BOOL res = ff.FindFile(csFolder);
	while (res)
	{
		res = ff.FindNextFile();
		if (!ff.IsDirectory() && !ff.IsDots())
		{
			CString strFullPath;
			strFullPath.Format("%s\\Data\\%s", path, ff.GetFileName());
			GetDeviceFromFile(strFullPath);
		}
	}
	ff.Close();
}

void CDeviceManager::Uninitialize()
{
	Device* pDevice = NULL;
	MAPFILETODEIVCEITER iterBegin = m_mapFileToDevice.begin();
	MAPFILETODEIVCEITER iterEnd = m_mapFileToDevice.end();
	for (; iterBegin != iterEnd; ++iterBegin)
	{
		list<Device*> & lsDevices = iterBegin->second;
		if (0 == lsDevices.size())
		{
			continue;
		}

		list<Device*>::iterator iterB = lsDevices.begin();
		list<Device*>::iterator iterE = lsDevices.end();
		for (; iterB != iterE;++iterB)
		{
			pDevice = *iterB;
			if (NULL == pDevice)
			{
				continue;
			}
			delete pDevice;
			pDevice = NULL;
		}
	}
	m_mapFileToDevice.clear();
}

bool CDeviceManager::AddOneDevice(const CString & csFile, Device * pDev)
{
	if (NULL == pDev)
	{
		return false;
	}

	MAPFILETODEIVCEITER iterFind = m_mapFileToDevice.find(csFile);
	if (iterFind != m_mapFileToDevice.end())
	{
		list<Device*> & lsDevices = iterFind->second;
		lsDevices.push_back(pDev);
	} 
	else
	{
		list<Device*> lsDevs;
		lsDevs.push_back(pDev);
		m_mapFileToDevice[csFile] = lsDevs;
	}

	return true;
}

bool CDeviceManager::DeleteOneDevice(const CString & csFile, Device * pDevice)
{
	if (csFile.IsEmpty() || NULL == pDevice)
	{
		return false;
	}

	MAPFILETODEIVCEITER iterFind = m_mapFileToDevice.find(csFile);
	if (iterFind == m_mapFileToDevice.end())
	{
		return false;
	}

	list<Device*> & lsDevs = iterFind->second;
	if (0 == lsDevs.size())
	{
		return false;
	}

	Device * pDev = NULL;
	list<Device*>::iterator iterBegin = lsDevs.begin();
	list<Device*>::iterator iterEnd = lsDevs.end();
	for (; iterBegin != iterEnd; ++iterBegin)
	{
		pDev = *iterBegin;
		if (NULL == pDev)
		{
			continue;
		}
		if (IsSameDevice(pDev, pDevice))
		{
			delete pDev;
			pDev = NULL;
			lsDevs.erase(iterBegin);
			return true;
		}
	}

	return false;
}

bool CDeviceManager::UpdateOnDevice(const CString & csFile, Device * pDevice)
{
	if (csFile.IsEmpty() || NULL == pDevice)
	{
		return false;
	}

	MAPFILETODEIVCEITER iterFind = m_mapFileToDevice.find(csFile);
	if (iterFind == m_mapFileToDevice.end())
	{
		return false;
	}

	list<Device*> & lsDevs = iterFind->second;
	if (0 == lsDevs.size())
	{
		return false;
	}

	Device * pDev = NULL;
	list<Device*>::iterator iterBegin = lsDevs.begin();
	list<Device*>::iterator iterEnd = lsDevs.end();
	for (; iterBegin != iterEnd; ++iterBegin)
	{
		pDev = *iterBegin;
		if (NULL == pDev)
		{
			continue;
		}
		if (IsSameDevice(pDev, pDevice))
		{
			*pDev = *pDevice;
			return true;
		}
	}

	return false;
}

bool CDeviceManager::IsSameDevice(Device * pDev1, Device * pDev2)
{
	if (NULL == pDev2 || NULL == pDev1)
	{
		return false;
	}

	return pDev1->csDeviceName == pDev2->csDeviceName;
}

void CDeviceManager::SaveAllDevice()
{
	Device * pDevice = NULL;
	MAPFILETODEIVCEITER iterB = m_mapFileToDevice.begin();
	MAPFILETODEIVCEITER iterE = m_mapFileToDevice.end();
	for (; iterB != iterE; ++iterB)
	{
		CString csFile = iterB->first;
		list<Device*> lsDevs = iterB->second;
		CString strDevInfo = SerializeDevice(lsDevs);
		CFile cf;
		if (!cf.Open(csFile, CFile::modeCreate | CFile::modeWrite))
		{
			continue;
		}
		
		int len = strDevInfo.GetLength();
		cf.Write(strDevInfo.GetBuffer(len), len);
		cf.Close();
		strDevInfo.ReleaseBuffer();
	}
}

void CDeviceManager::GetDeviceByFile(const CString & csFile, list<Device*> & lsDevs)
{
	MAPFILETODEIVCEITER iterFind = m_mapFileToDevice.find(csFile);
	if (iterFind != m_mapFileToDevice.end())
	{
		lsDevs = iterFind->second;
	}
}

void CDeviceManager::GetDeviceFromFile(const CString & csFile)
{
	CStdioFile myFile;
	list<Device *> lsDevices;
	CFileException fileException;
	if (myFile.Open(csFile, CFile::typeText | CFile::modeReadWrite), &fileException)
	{
		CString csTemp;
		while (myFile.ReadString(csTemp))
		{
			Device *pDevice = UnSerializeDevice(csTemp);
			if (NULL != pDevice)
			{
				lsDevices.push_back(pDevice);
			}
		}
	}
	else
	{
		TRACE("Can't open file %s,error=%u/n", csFile, fileException.m_cause);
	}
	myFile.Close();
	m_mapFileToDevice[csFile] = lsDevices;
}

CString CDeviceManager::SerializeDevice(list<Device*> & lsDevs)
{
	CString strResult = "";
	if (0 == lsDevs.size())
	{
		return strResult;
	}

	Device* pDevice = NULL;
	list<Device*>::iterator iterBegin = lsDevs.begin();
	list<Device*>::iterator iterEnd = lsDevs.end();
	for (; iterBegin != iterEnd; ++iterBegin)
	{
		pDevice = *iterBegin;
		if (NULL == pDevice)
		{
			continue;
		}

		//strResult.Append(pDevice->csDeviceId);
		//strResult.AppendChar(';');
		strResult.Append(pDevice->csDeviceName);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csAffiliatedParts);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csUseDepartment);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csDeviceModel);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csAppearanceDate);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csAppearanceNumber);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csImportance);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csOperator);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csEnableData);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csDeviceStatue);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csInstallLocation);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csCheckItem);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csCheckCycle);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csCheckMethod);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csCheckPoint);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csCheckTool);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csWorkOrderType);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csStandardNumber);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csApporver);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csAuditor);
		strResult.AppendChar(';');
		strResult.Append(pDevice->strEditor);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csRemarks);
		strResult.AppendChar(';');
		strResult.Append(pDevice->csDeviceType);
		strResult.Append(";");
		strResult.Append("\r\n");
	}
	return strResult;
}

Device * CDeviceManager::UnSerializeDevice(const CString & strContent)
{
	Device * pDev = new Device();

	CString strTemp = strContent;

	CString strInfo, strSub;
	int nPos = strContent.Find(';');
	pDev->csDeviceName = strContent.Left(nPos);
	strSub = strContent.Right(strContent.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csAffiliatedParts = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csUseDepartment = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csDeviceModel = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csAppearanceDate = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csAppearanceNumber = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csImportance = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csOperator = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csEnableData = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csDeviceStatue = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csInstallLocation = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csCheckItem = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csCheckCycle = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csCheckMethod = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csCheckPoint = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csCheckTool = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csWorkOrderType = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csStandardNumber = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csApporver = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csAuditor = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->strEditor = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csRemarks = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	nPos = strSub.Find(';');
	pDev->csDeviceType = strSub.Left(nPos);
	strSub = strSub.Right(strSub.GetLength() - nPos - 1);

	return pDev;
}
