#include "bdwordprocess.h"
#include <QDebug>
#include <QAxObject>

BDWordProcess::BDWordProcess(QObject *parent) : QObject(parent)
{
    mWinWordName = "WINWORD.exe";
    mPID = 0;
}
///
/// \brief BDWordProcess::checkWordExist
/// \return
/// 检查winword进程是否正在运行
///
bool BDWordProcess::checkWordExist()
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    PROCESSENTRY32* processInfo=new PROCESSENTRY32;
    // 必须设置PROCESSENTRY32的dwSize成员的值 ;
    processInfo->dwSize=sizeof(PROCESSENTRY32);
    //这里我们将快照句柄和PROCESSENTRY32结构传给Process32Next()。
    //执行之后，PROCESSENTRY32 结构将获得进程的信息。我们循环遍历，直到函数返回FALSE。
    qDebug()<<(QStringLiteral("****************开始列举进程****************"));
    while(Process32Next(hSnapShot,processInfo)!=FALSE)
    {
        int size=WideCharToMultiByte(CP_ACP,0,processInfo->szExeFile,-1,NULL,0,NULL,NULL);
        char *ch=new char[size+1];
        if(WideCharToMultiByte(CP_ACP,0,processInfo->szExeFile,-1,ch,size,NULL,NULL))
        {
            if(QString(ch).toLower() == (mWinWordName.toLower()))//使用这段代码的时候只需要改变"cmd.exe".将其改成你要结束的进程名就可以了。
            {
                qDebug()<<Q_FUNC_INFO<<mWinWordName<<" file Path "<<GetProcessPath(processInfo->th32ProcessID);
                mPID = processInfo->th32ProcessID;
                return true;
            }
        }
    }
    CloseHandle(hSnapShot);
    delete processInfo;
    typedef HANDLE (_stdcall *WTSOPENSERVER)(
                LPTSTR pServerName //NetBios指定的终端服务名，如果我们查看本地终端所有进程信息我们可以通过在控制台命令行下用nbtstat –an来获取本机NetBios名。
                );
    return false;

}

bool BDWordProcess::killWordExe()
{
    HANDLE hProcess;
    // 现在我们用函数 TerminateProcess()终止进程：
    hProcess = OpenProcess(PROCESS_ALL_ACCESS,TRUE,mPID);
    if(hProcess == NULL)
    {
        qDebug("Unable to get handle of process: ");
        qDebug()<<"Error is: "<<GetLastError();
        return false;
    }
    TerminateProcess(hProcess,0);
    return CloseHandle(hProcess);
}

bool BDWordProcess::isInstalledExcel()
{
    QAxObject *axObj = new QAxObject;
    bool installed = axObj->setControl("Excel.Application");
    if(installed){
        qDebug()<<"installed OK";
    }else{
        qDebug()<<"not installed";
    }
    axObj->deleteLater();
    axObj = NULL;
    return installed;
}
QString BDWordProcess::GetProcessPath( DWORD idProcess )
{
    // 获取进程路径
    WCHAR name[1024];
    ZeroMemory(name,1024);
    // 打开进程句柄
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, idProcess );
    if( NULL != hProcess )
    {
        DWORD cbNeeded;
        HMODULE hMod;
        // 获取路径
        if(::EnumProcessModules(hProcess,&hMod,sizeof(hMod),&cbNeeded))
            DWORD dw = ::GetModuleFileNameExW(hProcess, hMod, name, 1024 );

        CloseHandle( hProcess );
        }
    return QString::fromWCharArray(name);
}
