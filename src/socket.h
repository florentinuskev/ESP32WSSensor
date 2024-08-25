#ifndef SOCKET_H
#define SOCKET_H

#include <WebsocketsClient.h>
#include <Arduino_JSON.h>
#define USE_SERIAL Serial1

extern bool wsConnStatus;

void initWSConn(WebSocketsClient &wsc, String host, int port, String url);

#endif