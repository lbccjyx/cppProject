#include "fileinit.h"
#include "radixsort.h"
#include "threadForCout.h"
#include <set>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;
server print_server;
// 定义全局容器来存储连接对象
std::map<std::string, websocketpp::connection_hdl*> connectionsMap;
static std::vector<std::pair<bool, std::string>> vecLocks;
std::vector<std::string> vecLines; // 存储按行分割后的内容

std::string getIPAddress(const std::string& endpoint) {
	// 找到 '[' 和 ']' 之间的内容
	std::size_t start = endpoint.find('[');
	std::size_t end = endpoint.find(']');
	if (start != std::string::npos && end != std::string::npos && start < end) {
		return endpoint.substr(start + 1, end - start - 1);
	}

	// 如果找不到 '[', ']', 则假设没有 IPv6 括号，寻找 ':' 前的内容
	end = endpoint.find(':');
	if (end != std::string::npos) {
		return endpoint.substr(0, end);
	}

	// 如果都找不到，直接返回整个字符串
	return endpoint;
}


void sendAllStatus()
{
	for (auto it : connectionsMap)
	{
		websocketpp::connection_hdl* p = it.second;
		if (p)
		{
			std::string strTmp;
			for (int i = 0; i < vecLocks.size(); i++)
			{
				strTmp.push_back(vecLocks[i].first ? (vecLocks[i].second == getIPAddress(print_server.get_con_from_hdl(*p)->get_remote_endpoint()) ? '2' : '1') : '0');
			}

			print_server.send(*p, strTmp, websocketpp::frame::opcode::text);
		}
	}
}

void mBroadcast(std::string str)
{
	for (auto it : connectionsMap)
	{
		websocketpp::connection_hdl* p = it.second;
		if (p)
		{
			print_server.send(*p, str, websocketpp::frame::opcode::text);
		}
	}
}

void on_open(websocketpp::connection_hdl hdl) {
	// 获取客户端IP地址
	std::string client_ip = getIPAddress(print_server.get_con_from_hdl(hdl)->get_remote_endpoint());

	XXPrint("New connection from: ", "client_ip");
	//// 当新连接建立时，将连接对象存储到集合中
	websocketpp::connection_hdl* p = new websocketpp::connection_hdl(hdl);
	if (connectionsMap.find(client_ip) == connectionsMap.end())
	{
		connectionsMap[client_ip] = p;
		XXPrint("IP(", client_ip, ")\tConnection Open");
	}
	// 发送vecLines给客户端
	if (!vecLines.empty())
	{
		std::string strTmp = "HereAreYou ";
		for (auto it : vecLines)
		{
			strTmp += it + " ";
		}
		print_server.send(hdl, strTmp, websocketpp::frame::opcode::text);
	}

	// 如果当前有人锁定 则通知此客户端
	sendAllStatus();
}

void on_close(websocketpp::connection_hdl hdl) {
	// 当连接关闭时，从集合中删除对应的连接对象
	std::string client_ip = getIPAddress(print_server.get_con_from_hdl(hdl)->get_remote_endpoint());
	websocketpp::connection_hdl* p = connectionsMap[client_ip];
	if (p)
	{
		bool bFlag = false;

		for (int i = 0; i < vecLocks.size(); i++)
		{
			if (vecLocks[i].first && vecLocks[i].second == client_ip)
			{
				vecLocks[i].first = false;
				vecLocks[i].second = "";
				bFlag = true;
			}
		}

		connectionsMap.erase(client_ip);
		delete p;
		if (bFlag)
		{
			sendAllStatus();
		}
		XXPrint("IP(", client_ip, ")\tConnection closed");
	}
}

void on_message(websocketpp::connection_hdl hdl, server::message_ptr msg) {
	print_server.send(hdl, "Hello bro", websocketpp::frame::opcode::text);

	std::string strReceive = msg->get_payload();
	if (strReceive.length() > 4 && strReceive.substr(0, 4) == "lock")
	{
		std::string strTmp = getIPAddress(print_server.get_con_from_hdl(hdl)->get_remote_endpoint());
		std::string numberStr = strReceive.substr(4, strReceive.size() - 4);
		int nLockNum = std::stoi(numberStr);
		
		//未锁定则加锁 并且记录客户端IP 只有他能解锁 使其客户端颜色为不同
		if (vecLocks[nLockNum].first == false)
		{
			vecLocks[nLockNum].first = true;
			vecLocks[nLockNum].second = strTmp;
			sendAllStatus();
		}
		else
		{
			// 锁定则判断客户端IP是否为锁定者 并且解锁
			if (vecLocks[nLockNum].second == strTmp)
			{
				vecLocks[nLockNum].first = false;
				vecLocks[nLockNum].second = "";
				sendAllStatus();
			}
			else
			{
				// 只有本人能解锁 所以通知锁定方
				std::string strLockMan = vecLocks[nLockNum].second;
				websocketpp::connection_hdl* pcon = connectionsMap[strLockMan];
				if (pcon)
				{
					print_server.send(*pcon, "hurry up", websocketpp::frame::opcode::text);
				}
			}
		}
	}

}

bool LoadCfg()
{
	std::ifstream file("./config.txt"); // 打开文件用于读取

	if (!file.is_open()) { // 检查文件是否成功打开
		std::cerr << "无法打开文件: config.txt" << std::endl;
		return false;
	}

	std::ostringstream oss; // 用于存储文件内容的字符串流
	oss << file.rdbuf(); // 将文件内容读入字符串流
	file.close(); // 关闭文件

	std::string content = oss.str(); // 获取字符串流中的内容

	// 使用std::istringstream和getline按行分割内容
	std::istringstream iss(content);
	std::string line;
	while (std::getline(iss, line)) {
		vecLines.push_back(line); // 将每一行添加到vector中
		vecLocks.push_back(std::make_pair(false, ""));
	}
	return true;
}

int main() {
	if (!LoadCfg())
		return -1;
	ThreadPrintManager ctpm;
	print_server.set_open_handler(&on_open);
	print_server.set_close_handler(&on_close);
	print_server.set_message_handler(&on_message);
	/*print_server.set_access_channels(websocketpp::log::alevel::all);
	print_server.set_error_channels(websocketpp::log::elevel::all);*/
	// 关闭所有日志
	print_server.clear_access_channels(websocketpp::log::alevel::all);
	print_server.clear_error_channels(websocketpp::log::elevel::all);

	print_server.init_asio();
	print_server.listen(9002);
	print_server.start_accept();

	print_server.run();
}