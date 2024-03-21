#include "fileinit.h"
#include "radixsort.h"
#include "threadForCout.h"

using namespace std;

#ifdef UNICODE
#define tstring std::wstring
#define tprintf wprintf
#define Tcsdup wcsdup
#else
#define tstring std::string
#define tprintf printf
#define Tcsdup _strdup
#endif

// 删除字符串后面的换行符
static inline void removeTrailingNewline(std::string &s) {
    s.erase(s.find_last_not_of("\n\r") + 1);
}

bool executeCommand(const TCHAR* command, const TCHAR* workingDirectory) {
	// 初始化STARTUPINFO和PROCESS_INFORMATION结构
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	si.hStdOutput = NULL;

	TCHAR* commandCopy = Tcsdup(command);

	// 创建进程
	if (CreateProcess(NULL, commandCopy, NULL, NULL, FALSE, 0, NULL,
		workingDirectory, &si, &pi)) {
		// 等待进程结束 0.5秒后直接放弃等待
		WaitForSingleObject(pi.hProcess, 500);

		// 关闭进程和线程的句柄 但是程序依旧运行
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		XXPrint("Command executed successfully.\n");
		return true;
	}
	else {
		XXPrint("Failed to execute command.\n");
		return false;
	}
}

unsigned __stdcall Answer(void* a) {
  Socket* s = (Socket*) a;

  while (1) {
    std::string r = s->ReceiveLine();
    if (r.empty()) break;
    removeTrailingNewline(r);
    XXPrint("ReceiveLine:", r, "\n");

    if (myCmdDataJson.contains(r))
    {
		std::string strDir = myCmdDataJson[r]["dir"];
		std::string strCMD = myCmdDataJson[r]["cmd"];
		strCMD += ">nul";
        if(strDir.length() <= 0 || strCMD.length() <= 0)
            break;

#ifdef UNICODE
        XXPrint("匹配命令:\tDIR:", strDir,"\tCMD:", strCMD, "\n");
        wchar_t* wcDir = new wchar_t[strDir.size()];
        swprintf(wcDir, strDir.size() + 1, L"%S", strDir.c_str());

		wchar_t* wcCMD = new wchar_t[strCMD.size()];
		swprintf(wcCMD, strCMD.size() + 1, L"%S", strCMD.c_str());
		executeCommand(wcCMD, wcDir);
#else
		executeCommand(strCMD.c_str(), strDir.c_str());
#endif
        
    }
  }

  s->Close();
  delete s;

  return 0;
}

void threadFunction() {
  std::ifstream f("listen_cmd_server_cfg.json");
  if (!f) {
      XXPrint("无法打开文件 cmd.json\n");
      return ;
  }
  try {
    myCmdDataJson = json::parse(f);
  } catch (json::parse_error& e) {
      XXPrint("解析JSON数据时发生错误: " ,e.what(),'\n');
      return ;
  }
  
  XXPrint("listen ", myCmdDataJson["listenPort"]," for restart_server\n");
  try {
    SocketServer in(myCmdDataJson["listenPort"], 30);
    
    while (1) {
      Socket* s=in.Accept();

      unsigned ret;
      _beginthreadex(0,0,Answer,(void*) s,0,&ret);
    }
  } catch (const char* msg) {
      XXPrint("初始化失败 端口占用", msg, "\n 所以需要换个端口 \n");
  }
}

int main(int argc, char* argv[]) {
  init();
  ThreadPrintManager ctpm;

  std::thread t(threadFunction);
  t.join();

  return 0;
}