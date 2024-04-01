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

// 写一个类实现threadFunction的功能 有读取文件，重新读取配置文件，监听,answer等等
class CThreadFunction {
public:
	CThreadFunction() {}

	~CThreadFunction() {
		if (pIn)
		{
			pIn->Close();
			delete pIn;
		}
	}

public:
	bool init() {
		if(!readConfig())
			return false;
		if (!ListenPort())
			return false;
		return true;
	}

	void listen() {
		while (1) {
			Socket* s = pIn->Accept();
			std::thread t(&CThreadFunction::answer, this, s);
			t.detach();
		}
	}
private:
	bool readConfig() {
		//初始化myCmdDataJson
		myCmdDataJson.clear();

		std::ifstream f("listen_cmd_server_cfg.json");
		if (!f) {
			XXPrint("无法打开文件 cmd.json\n");
			return false;
		}
		try {
			myCmdDataJson = json::parse(f);
		} catch (json::parse_error& e) {
			XXPrint("解析JSON数据时发生错误: " ,e.what(),'\n');
			return false;
		}

		XXPrint(" 读取配置文件 listen_cmd_server_cfg.json完毕\n");
		return true;
	}

	bool ListenPort() {
		try {
			XXPrint("lisening port: ", myCmdDataJson["listenPort"]);
			this->pIn = new SocketServer(myCmdDataJson["listenPort"], 30);
		}
		catch (const char* msg) {
			XXPrint("初始化失败 端口占用", msg, "\n 所以需要换个端口 \n");
			return false;
		}
		return true;
	}

	void answer(void* a) {
		Socket* s = (Socket*)a;
		while (1) {
			std::string r = s->ReceiveLine();
			if (r.empty()) break;
			removeTrailingNewline(r);
			XXPrint("ReceiveLine:", r, "\n");

			if (r == "reload")
			{
				this->readConfig();
				continue;
			}

			if (myCmdDataJson.contains(r))
			{
				std::string strDir = myCmdDataJson[r]["dir"];
				std::string strCMD = myCmdDataJson[r]["cmd"];
				strCMD += ">nul";
				if (strDir.length() <= 0 || strCMD.length() <= 0)
					break;

#ifdef UNICODE
				XXPrint("匹配命令:\tDIR:", strDir, "\tCMD:", strCMD, "\n");
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
	}

private:
	json myCmdDataJson = nullptr;
	SocketServer* pIn = nullptr;
};

int main(int argc, char* argv[]) {
  init();
  ThreadPrintManager ctpm;

  //std::thread t(threadFunction);
  // 多线程使用CThreadFunction 的listen
  CThreadFunction ctf;
  if (!ctf.init())
	  return 0;
  ctf.listen();
  std::cout<<"main thread end"<<std::endl;
  return 0;
}