#pragma once

#include <list>

using namespace std;

struct Device
{
	int			nIndex;				// 索引编号
	CString 	csDeviceId;			// 设备标识
	CString 	csDeviceName;		// 设备名称
	CString		csAffiliatedParts;	// 所属部件
	CString		csUseDepartment;	// 使用部门
	CString 	csDeviceModel;		// 规格型号
	CString		csAppearanceDate;	// 出厂日期
	CString		csAppearanceNumber;	// 出厂编号
	CString		csDeviceType;		// 设备类型
	CString		csImportance;		// 重要程度
	CString 	csOperator;			// 操作人员
	CString		csEnableData;		// 启用日期
	CString 	csDeviceStatue;		// 设备状况
	CString 	csInstallLocation;	// 安装地点
	CString		csCheckItem;		// 点检项目
	CString		csCheckCycle;		// 点检周期
	CString		csCheckMethod;		// 点检方法
	CString		csCheckPoint;		// 点检点数
	CString		csCheckTool;		// 点检工具
	CString		csWorkOrderType;	// 工单种类
	CString		csStandardNumber;	// 标准编号
	CString		csApporver;			// 审批人
	CString		csAuditor;			// 审核人
	CString		strEditor;			// 编制人
	CString		csRemarks;			// 备注信息
};