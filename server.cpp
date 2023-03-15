#include <WiFi.h>
#include <IPAddress.h>

#include <lwip/sockets.h>
#include <lwip/netdb.h>

#include "constants.h"
#include "prototypes.h"

WiFiClient *server_client;
IPAddress _addr;

int server_sockfd = -1;
int server_client_sockfd = -1;

client_lost_cb_t server_client_lost;

WiFiClient* server_get_client() {
  return server_client;
}

void server_initialize(int port) {
  int enable = 1;
  struct sockaddr_in server;
  server_sockfd = socket(AF_INET , SOCK_STREAM, 0);
  if (server_sockfd < 0)
    return;
  setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = _addr;
  server.sin_port = htons(port);
  if(bind(server_sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    return;
  if(listen(server_sockfd, 1) < 0)
    return;
  fcntl(server_sockfd, F_SETFL, O_NONBLOCK);
  Serial.println("Server initialize");
}

void server_close() {
  if (server_client) {
    server_client->stop();
    delete server_client;
    server_client = 0;
    server_client_sockfd = -1;
  }
  if (server_sockfd) {
#ifdef ESP_IDF_VERSION_MAJOR
    lwip_close(server_sockfd);
#else
    lwip_close_r(server_sockfd);
#endif
    server_sockfd = -1;
    Serial.println("Server close");
  }
}

void server_update() {
  if (server_sockfd < 0) return;
  if (server_client_sockfd < 0) {
    struct sockaddr_in _client;
    int cs = sizeof(struct sockaddr_in);
#ifdef ESP_IDF_VERSION_MAJOR
    server_client_sockfd = lwip_accept(server_sockfd, (struct sockaddr *)&_client, (socklen_t*)&cs);
#else
    server_client_sockfd = lwip_accept_r(server_sockfd, (struct sockaddr *)&_client, (socklen_t*)&cs);
#endif
    if(server_client_sockfd >= 0){
      int val = 1; //KEEPALIVE
      if(setsockopt(server_client_sockfd, SOL_SOCKET, SO_KEEPALIVE, (char*)&val, sizeof(int)) == ESP_OK) {
        val = false; // NODELAY
        if(setsockopt(server_client_sockfd, IPPROTO_TCP, TCP_NODELAY, (char*)&val, sizeof(int)) == ESP_OK) {
          if (server_client) {
            server_client->stop();
            delete server_client;
            server_client = 0;
          }
          server_client = new WiFiClient(server_client_sockfd);
          Serial.println("Client connected");
        }
      }
    }
  }
  if (server_client) {
    if (!server_client->connected()) {
      Serial.println("Client disconnect unexpectedly");
      server_client = 0;
      server_client_sockfd = -1;
      if (server_client_lost) {
        server_client_lost();
      }
    }
  }
}

void server_client_disconnect() {
  if (!server_client) return;
  server_client->stop();
  delete server_client;
  server_client = 0;
  server_client_sockfd = -1;
  Serial.println("Client disconnected");
  if (server_client_lost) {
    server_client_lost();
  }
}

void server_attach_client_lost(client_lost_cb_t cb) {
  server_client_lost = cb;
}
