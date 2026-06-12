#include "CriticalSection.h"

#define MAX_BUFF_SIZE 8192

class JCSocket
{
public:
	JCSocket();
	virtual ~JCSocket();
	void InitProperity( );
	bool Init(void* function);
	bool Connect(char* IpAddress, WORD port);
	void Disconnect();
	bool CheckState();
	bool DataRecv();
	bool DataSend(BYTE* lpMsg, int size);
	bool DataSendEx();
	static DWORD WINAPI ClientWorkerThread(JCSocket* lpConnection);
	static DWORD WINAPI ServerQueueThread(JCSocket* lpConnection);
private:
	SOCKET m_socket;
	WSAEVENT m_event;
	BYTE m_RecvBuff[MAX_BUFF_SIZE];
	int m_RecvSize;
	BYTE m_SendBuff[MAX_BUFF_SIZE];
	int m_SendSize;
	void(*wsProtocolCore)(BYTE, BYTE*, int);
	CCriticalSection m_critical;
	HANDLE m_WorkerThread;
	bool m_active;
};
extern JCSocket JCSocketConnect;