#ifndef BDWORDPROCESS_H
#define BDWORDPROCESS_H

#include <QObject>

#ifdef Q_OS_WIN32
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#endif
typedef struct tagProcessDetails
{
    int   dwSize;
    int   cntUsage;
    int   th32ProcessID;          // this process
    int   cntThreads;
    long    pcPriClassBase;         // Base priority of process's threads
    QString   szExeFile;    // Path
} ProcessDetails;

class BDWordProcess : public QObject
{
    Q_OBJECT
public:
    explicit BDWordProcess(QObject *parent = 0);
    bool  checkWordExist();
    bool  killWordExe();
    bool isInstalledExcel();
signals:

public slots:
private:
    QString GetProcessPath(DWORD idProcess);
    QString mWinWordName;
    int         mPID;
};

#endif // BDWORDPROCESS_H
