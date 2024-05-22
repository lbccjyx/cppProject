#include "fileinit.h"
#include "radixsort.h"
#include "threadForCout.h"
#include <set>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;
server print_server;
// ����ȫ���������洢���Ӷ���
std::map<std::string, websocketpp::connection_hdl*> connectionsMap;
static std::vector<std::pair<bool, std::string>> vecLocks;
std::vector<std::string> vecLines; // �洢���зָ�������

std::string getIPAddress(const std::string& endpoint) {
	// �ҵ� '[' �� ']' ֮�������
	std::size_t start = endpoint.find('[');
	std::size_t end = endpoint.find(']');
	if (start != std::string::npos && end != std::string::npos && start < end) {
		return endpoint.substr(start + 1, end - start - 1);
	}

	// ����Ҳ��� '[', ']', �����û�� IPv6 ���ţ�Ѱ�� ':' ǰ������
	end = endpoint.find(':');
	if (end != std::string::npos) {
		return endpoint.substr(0, end);
	}

	// ������Ҳ�����ֱ�ӷ��������ַ���
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
	// ��ȡ�ͻ���IP��ַ
	std::string client_ip = getIPAddress(print_server.get_con_from_hdl(hdl)->get_remote_endpoint());

	XXPrint("New connection from: ", "client_ip");
	//// �������ӽ���ʱ�������Ӷ���洢��������
	websocketpp::connection_hdl* p = new websocketpp::connection_hdl(hdl);
	if (connectionsMap.find(client_ip) == connectionsMap.end())
	{
		connectionsMap[client_ip] = p;
		XXPrint("IP(", client_ip, ")\tConnection Open");
	}
	// ����vecLines���ͻ���
	if (!vecLines.empty())
	{
		std::string strTmp = "HereAreYou ";
		for (auto it : vecLines)
		{
			strTmp += it + " ";
		}
		print_server.send(hdl, strTmp, websocketpp::frame::opcode::text);
	}

	// �����ǰ�������� ��֪ͨ�˿ͻ���
	sendAllStatus();
}

void on_close(websocketpp::connection_hdl hdl) {
	// �����ӹر�ʱ���Ӽ�����ɾ����Ӧ�����Ӷ���
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
		
		//δ��������� ���Ҽ�¼�ͻ���IP ֻ�����ܽ��� ʹ��ͻ�����ɫΪ��ͬ
		if (vecLocks[nLockNum].first == false)
		{
			vecLocks[nLockNum].first = true;
			vecLocks[nLockNum].second = strTmp;
			sendAllStatus();
		}
		else
		{
			// �������жϿͻ���IP�Ƿ�Ϊ������ ���ҽ���
			if (vecLocks[nLockNum].second == strTmp)
			{
				vecLocks[nLockNum].first = false;
				vecLocks[nLockNum].second = "";
				sendAllStatus();
			}
			else
			{
				// ֻ�б����ܽ��� ����֪ͨ������
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
	std::ifstream file("./config.txt"); // ���ļ����ڶ�ȡ

	if (!file.is_open()) { // ����ļ��Ƿ�ɹ���
		std::cerr << "�޷����ļ�: config.txt" << std::endl;
		return false;
	}

	std::ostringstream oss; // ���ڴ洢�ļ����ݵ��ַ�����
	oss << file.rdbuf(); // ���ļ����ݶ����ַ�����
	file.close(); // �ر��ļ�

	std::string content = oss.str(); // ��ȡ�ַ������е�����

	// ʹ��std::istringstream��getline���зָ�����
	std::istringstream iss(content);
	std::string line;
	while (std::getline(iss, line)) {
		vecLines.push_back(line); // ��ÿһ����ӵ�vector��
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
	// �ر�������־
	print_server.clear_access_channels(websocketpp::log::alevel::all);
	print_server.clear_error_channels(websocketpp::log::elevel::all);

	print_server.init_asio();
	print_server.listen(9002);
	print_server.start_accept();

	print_server.run();
}