#include <Geode/Geode.hpp>
#include <Geode/modify/MusicDownloadManager.hpp>
#include <utility>
#include <utils/GDPSMain.hpp>

using namespace geode::prelude;

class $modify(GDPSMDL, MusicDownloadManager) {

    std::string pathForSFXFolder(int id) {
        auto ret = MusicDownloadManager::pathForSFXFolder(id);
        if (!GDPSMain::get()->isActive()) return ret;
        log::info("{}", getGDPSPath(ret));
        return getGDPSPath(ret);
    }

    std::string pathForSongFolder(int id) {
        auto ret = MusicDownloadManager::pathForSongFolder(id);
        if (!GDPSMain::get()->isActive()) return ret;
        log::info("{}", getGDPSPath(ret));
        return getGDPSPath(ret);
    }

    // cause gd::string
    inline std::string getGDPSPath(const gd::string& path) {
        return getGDPSPath(std::filesystem::path(path));
    }

    std::string getGDPSPath(const std::filesystem::path& orig) {
        auto server = GDPSMain::get()->m_servers[GDPSMain::get()->m_currentServer];
        return string::pathToString(orig / "gdpses" / server.saveDir / "");
    }
};
