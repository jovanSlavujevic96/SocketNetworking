#pragma once

#include "iworker_socket.h"
#include "rtsp_info.h"
#include "rtsp_request.h"

class CRtspMaster;

class CRtspClientHandler : public IWorkerSocket
{
public:
	CRtspClientHandler(const CRtspClientHandler&) = delete;
	~CRtspClientHandler();

private:
	CRtspMaster* mMaster = nullptr;
	RtspInfo mRtspInfo;
	RtspRequest mRequestState;

	CRtspClientHandler(std::unique_ptr<SocketInfo> socket_info);
	
	void threadEntry() override final;

	bool onReceive(const char* message);
	
	bool parseRequestLine(const char* line);
	bool parseRequest(const char* request);
	bool parseUrl(const char* url);
	bool parseVersion(const char* version);

	bool parseHeaderLines(const char* lines);
	bool parseCSeq(const char* lines);
	bool parseAuthentication(const char* lines);
	bool parseAccept(const char* lines);
	bool parseTransport(const char* lines);
	bool parseMediaChannel(const char* lines);
	bool parseSessionId(const char* lines);
protected:
	friend class CRtspMaster;	/* only CRtspMaster can instantiate this object */
	static std::unique_ptr<CRtspClientHandler> instatiateClientHandler(CRtspMaster* master, std::unique_ptr<SocketInfo>& socket_info) noexcept;
};