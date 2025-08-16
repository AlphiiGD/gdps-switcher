// MUST be defined before including the header.
#define GEODE_DEFINE_EVENT_EXPORTS
#include <GDPSUtils.hpp>
#include "../ui/ServerListLayer.hpp"
#include "../utils/GDPSMain.hpp"
#include <km7dev.server_api/include/ServerAPIEvents.hpp>
#include "../utils/ServerInfoManager.hpp"
using namespace geode::prelude;

Result<int> GDPSUtils::createServer(std::string name, std::string url, std::string saveDir) {
    int id = 0;
    for (auto &[serverId, server] : GDPSMain::get()->m_servers) {
        if (serverId < 0) continue;
        if (server.url == url) {
            return Err("Server already saved as {}", name);
        }
        if (serverId == id) id++;
        else break;
    }
    auto server = GDPSTypes::Server();
    server.name = name;
    server.url = url;
    server.id = id;
    server.saveDir = saveDir.empty() ? fmt::format("{}", id) : saveDir;
    GDPSMain::get()->m_servers[id] = server;
    GDPSMain::get()->save();
    return Ok(id);
}

Result<std::map<int, GDPSTypes::Server>> GDPSUtils::getServers() {
    return Ok(GDPSMain::get()->m_servers);
}

Result<GDPSTypes::Server> GDPSUtils::getCurrentServer() {
    auto it = GDPSMain::get()->m_servers.find(GDPSMain::get()->m_currentServer);
    if (it == GDPSMain::get()->m_servers.end()) {
        return Err("Current server not found");
    }
    return Ok(it->second);
}

Result<bool> GDPSUtils::setCurrentServer(int id) {
    auto it = GDPSMain::get()->m_servers.find(id);
    if (it == GDPSMain::get()->m_servers.end()) {
        return Err("Server not found");
    }
    GDPSMain::get()->m_currentServer = id;
    return Ok(true);
}

Result<GDPSTypes::Server> GDPSUtils::findServer(std::string url, std::string saveDir) {
    for (auto &[id, server] : GDPSMain::get()->m_servers) {
        if (server.url == url && server.saveDir == saveDir) {
            return Ok(server);
        }
    }
    return Err("Server not found");
}

// This should be a Result<void> but too late to change it.
Result<bool> GDPSUtils::deleteServer(int id) {
    auto res = GDPSMain::get()->deleteServer(id);
    if (!res) {
        return Err(res.unwrapErr());
    }
    return Ok(true);
}

Result<bool> GDPSUtils::switchServer(int id) {
    auto it = GDPSMain::get()->m_servers.find(id);
    if (it == GDPSMain::get()->m_servers.end()) {
        return Err("Server not found");
    }
    GDPSMain::get()->m_currentServer = id;
    return Ok(true);
}

Result<GDPSTypes::Server> GDPSUtils::getServerInfo(int id) {
    auto it = GDPSMain::get()->m_servers.find(id);
    if (it == GDPSMain::get()->m_servers.end()) {
        return Err("Server not found");
    }
    return Ok(it->second);
}

Result<bool> GDPSUtils::setServerInfo(int id, std::string name, std::string url, std::string saveDir) {
    auto res = GDPSMain::get()->setServerInfo(id, name, url, saveDir);
    if (!res) {
        return Err(res.unwrapErr());
    }
    return Ok(true);
}