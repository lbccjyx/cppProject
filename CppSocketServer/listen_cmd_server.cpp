#include "fileinit.h"
#include "radixsort.h"
#include "threadForCout.h"

using namespace std;
// 删除字符串后面的换行符
static inline void removeTrailingNewline(std::string &s) {
    s.erase(s.find_last_not_of("\n\r") + 1);
}

bool executeCommand(const wchar_t* command, const wchar_t* workingDirectory) {
	// 初始化STARTUPINFO和PROCESS_INFORMATION结构
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
    si.hStdOutput = NULL;

	wchar_t* commandCopy = _wcsdup(command);

	// 创建进程
	if (CreateProcess(NULL, commandCopy, NULL, NULL, FALSE, 0, NULL,
		workingDirectory, &si, &pi)) {
		// 等待进程结束
		WaitForSingleObject(pi.hProcess, INFINITE);

		// 关闭进程和线程的句柄
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
        if(strDir.length() <= 0 || strCMD.length() <= 0)
            break;

        XXPrint("匹配命令:\tDIR:", strDir,"\tCMD:", strCMD, "\n");
        wchar_t* wcDir = new wchar_t[strDir.size()];
        swprintf(wcDir, strDir.size() + 1, L"%S", strDir.c_str());

		wchar_t* wcCMD = new wchar_t[strCMD.size()];
		swprintf(wcCMD, strCMD.size() + 1, L"%S", strCMD.c_str());

        executeCommand(wcCMD, wcDir);
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

void test01()
{
	SendaiCSBattleSignUpReportUpdate haha;
	haha.d = 1.1;
	haha.i = 2;
	std::shared_ptr<AllStruct> pAll = std::make_shared<AllStruct>();
	pAll->nType = MSGACT_SENDAI;
	pAll->data.normalP = &haha;

	XXPrint("hehehhe", 3.1456544, *pAll);
}

int main(int argc, char* argv[]) {
  init();

  threadPrint* a = new threadPrint();
  std::thread tPrint([a] { a->worker(); });

  //std::thread t(threadFunction);
  //t.join();
  test01();

  a->over();
  tPrint.join();

  //std::vector<int> arr;
  //const int numElements = 20;
  //// 使用随机设备和分布生成随机数
  //std::random_device rd;
  //std::mt19937 gen(rd());
  //int a = 2147483646;
  //std::uniform_int_distribution<int> distribution(1, a);

  //// 将随机数插入到向量中
  //for (int i = 0; i < numElements; ++i) {
	 // arr.push_back(distribution(gen));
  //}

  //std::vector<int> arrOut;
  //arrOut = RadixSort(arr);

  //std::cout << "Sorted array: ";
  //for (int num : arrOut) {
	 // std::cout << num << " ";
  //}

  system("pause");

  return 0;
}