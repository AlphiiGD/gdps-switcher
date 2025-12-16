#pragma once

#include "Types.hpp"
#include <km7dev.server_api/include/ServerAPIEvents.hpp>

#include <vector>
#include <string>
#include <mutex>
#include <shared_mutex>

class GDPSMain {
    friend class GSGManager;
    protected:
        geode::EventListener<EventFilter<UpdateServerEvent>> m_serverChangeListener;
        static GDPSMain *m_instance;
        std::vector<std::string> m_issues = {};
        void init();
        [[nodiscard]] geode::Result<> setServerSaveDir(GDPSTypes::Server& server, std::string_view saveDir); // Caller is responsible for managing save state.
    public:
        bool isActive() const;
        void registerIssue(const std::string& issue);
        std::vector<std::string> getIssues();
        bool isBase() const;
        geode::Result<GDPSTypes::Server> getCurrentServer();
        geode::Result<> setServerInfo(int id, std::string_view name = "", std::string_view url = "", std::string_view saveDir = "");
        geode::Result<> registerServer(GDPSTypes::Server& server);
        geode::Result<> modifyRegisteredServer(GDPSTypes::Server& server);
        geode::Result<> deleteServer(GDPSTypes::Server& server);
        geode::Result<> deleteServer(int id);
        geode::Result<> switchServer(int id);
        GDPSTypes::ServerInvalidity isValidServer(const GDPSTypes::Server& server) const; // Will check if server info can be saved to disk.
        bool serverExists(int id) const;
        bool shouldSaveGameData() const;
        static bool isBase(std::string url);

        int currentServer() const;

        void save() const;

        static GDPSMain *get();

        // One of these days I will make this shit private without breaking everything.
        std::map<int, GDPSTypes::Server> m_servers;
        int m_currentServer = -2;
        int m_serverApiId = 0;
        bool m_shouldSaveGameData = true;
        bool m_switching = false;
};