#include <winsock.h>
#pragma comment(lib, "WS2_32") // ���ӵ�WS2_32.lib

struct NTP_Packet
{
	int Control_Word;
	int root_delay;
	int root_dispersion;
	int reference_identifier;
	__int64 reference_timestamp;
	__int64 originate_timestamp;
	__int64 receive_timestamp;
	int transmit_timestamp_seconds;
	int transmit_timestamp_fractions;
}; 

BOOL UpdateSysTime()
{
    WORD    wVersionRequested;
    WSADATA wsaData;
    
    // ��ʼ���汾
    wVersionRequested = MAKEWORD( 1, 1 );
    if (0!=WSAStartup(wVersionRequested, &wsaData)) 
    {
        WSACleanup();
        return FALSE;
    }
    if (LOBYTE(wsaData.wVersion)!=1 || HIBYTE(wsaData.wVersion)!=1) 
    {
        WSACleanup( );
        return FALSE; 
    }
    
    // ���IP���й���½ʱ��ͬ����������ַ���������޸�
    SOCKET soc=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    struct sockaddr_in addrSrv;
    addrSrv.sin_addr.S_un.S_addr=inet_addr("210.72.145.44");
    addrSrv.sin_family=AF_INET;
    addrSrv.sin_port=htons(123);
    
    NTP_Packet NTP_Send,NTP_Recv; 
    NTP_Send.Control_Word   =   htonl(0x0B000000);   
    NTP_Send.root_delay        =   0;   
    NTP_Send.root_dispersion   =   0;   
    NTP_Send.reference_identifier    =   0;   
    NTP_Send.reference_timestamp    =   0;   
    NTP_Send.originate_timestamp    =   0;   
    NTP_Send.receive_timestamp        =   0;   
    NTP_Send.transmit_timestamp_seconds        =   0;   
    NTP_Send.transmit_timestamp_fractions   =   0; 
    
    if(SOCKET_ERROR==sendto(soc,(const char*)&NTP_Send,sizeof(NTP_Send),
        0,(struct sockaddr*)&addrSrv,sizeof(addrSrv)))
    {
        closesocket(soc);
        return FALSE;
    }
    int sockaddr_Size =sizeof(addrSrv);
    if(SOCKET_ERROR==recvfrom(soc,(char*)&NTP_Recv,sizeof(NTP_Recv),
        0,(struct sockaddr*)&addrSrv,&sockaddr_Size))
    {
        closesocket(soc);
        return FALSE;
    }
    closesocket(soc);
    WSACleanup();
    
    SYSTEMTIME    newtime;
    float        Splitseconds;
    struct        tm    *lpLocalTime;
    time_t        ntp_time;
    
    // ��ȡʱ���������ʱ��
    ntp_time    = ntohl(NTP_Recv.transmit_timestamp_seconds)-2208988800;
    lpLocalTime = localtime(&ntp_time);
    if(lpLocalTime == NULL)
    {
        return FALSE;
    }
    
    // ��ȡ�µ�ʱ��
    newtime.wYear      =lpLocalTime->tm_year+1900;
    newtime.wMonth     =lpLocalTime->tm_mon+1;
    newtime.wDayOfWeek =lpLocalTime->tm_wday;
    newtime.wDay       =lpLocalTime->tm_mday;
    newtime.wHour      =lpLocalTime->tm_hour;
    newtime.wMinute    =lpLocalTime->tm_min;
    newtime.wSecond    =lpLocalTime->tm_sec;
    
    // ����ʱ�侫��
    Splitseconds=(float)ntohl(NTP_Recv.transmit_timestamp_fractions);
    Splitseconds=(float)0.000000000200 * Splitseconds;
    Splitseconds=(float)1000.0 * Splitseconds;
    newtime.wMilliseconds   =   (unsigned   short)Splitseconds;
    
    // �޸ı���ϵͳʱ��
    SetLocalTime(&newtime);
    return TRUE;
}
