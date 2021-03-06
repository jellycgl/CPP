#pragma once
#include <map>
#include <list>
#include <string>
#include "Device.h"

using namespace std;

typedef map<CString, list<Device*>>				MAPFILETODEIVCE;
typedef map<CString, list<Device*>>::iterator	MAPFILETODEIVCEITER;

class CDeviceManager
{
/*/////////////////////////////////////////////////////////////////////////
				    单        例        相        关
/////////////////////////////////////////////////////////////////////////*/
public:
	static CDeviceManager * Instance();

private:
	CDeviceManager();
	CDeviceManager(const CDeviceManager &);
	CDeviceManager & operator = (const CDeviceManager &);

private:
	static CDeviceManager * pDeviceManager;

/*/////////////////////////////////////////////////////////////////////////
					数        据        管        理
/////////////////////////////////////////////////////////////////////////*/
public:
	// 初始化数据
	void Initialize();

	// 销毁数据
	void Uninitialize();

	// 添加一个Device
	bool AddOneDevice(const CString & csFile, Device * pDev);

	// 删除一个Device
	bool DeleteOneDevice(const CString & csFile, Device * pDev);

	// 更新一个Device
	bool UpdateOnDevice(const CString & csFile, Device * pDev);

	// 判断是否为相同Device
	bool IsSameDevice(Device * pDev1, Device * pDev2);

	// 保存Device信息
	void SaveAllDevice();

	// 从内存立读取Device信息
	void GetDeviceByFile(const CString & csFile, list<Device*> & lsDevs);

	// 从文件中读取Device信息
	void GetDeviceFromFile(const CString & csFile);

	// 序列化Device信息
	CString SerializeDevice(list<Device*> & lsDevs);

	// 反序列化Device信息
	Device * UnSerializeDevice(const CString & strContent);

private:
	MAPFILETODEIVCE m_mapFileToDevice;
};

