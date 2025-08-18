#include "../utils/GDPSMain.hpp"

using namespace geode::prelude;

$on_mod(DataSaved)
{
    if (
        Mod::get()->getRequestedAction() == ModRequestedAction::Disable ||
        Mod::get()->getRequestedAction() == ModRequestedAction::Uninstall ||
        Mod::get()->getRequestedAction() == ModRequestedAction::UninstallWithSaveData ||
        GDPSMain::get()->m_switching
    ) {
        // Switched to std::filesystem::path 😊
        auto writablePath = std::filesystem::path(CCFileUtils::sharedFileUtils()->getWritablePath());
        auto musicPath = writablePath / "musiclibrary.dat";
        auto sfxPath = writablePath / "sfxlibrary.dat";

        log::debug("Deleting music library and SFX library");
        log::debug("Cache dir: {}", writablePath);

        std::error_code err;
        if (std::filesystem::exists(musicPath, err)) {
            if (err) {
                log::warn("Failed to check existence of music library at {}: {}", musicPath, err.message());
            } else {
                std::filesystem::remove(musicPath, err);
                if (err) {
                    log::warn("Failed to delete music library at {}: {}", musicPath, err.message());
                }
            }
        } else {
            if (err) {
                log::warn("Failed to check existence of music library at {}: {}", musicPath, err.message());
            } else {
                log::debug("Music library was not at {}!", musicPath);
            }
        }

        if (std::filesystem::exists(sfxPath, err)) {
            if (err) {
                log::warn("Failed to check existence of SFX library at {}: {}", sfxPath, err.message());
            } else {
                std::filesystem::remove(sfxPath, err);
                if (err) {
                    log::warn("Failed to delete SFX library at {}: {}", sfxPath, err.message());
                }
            }
        } else {
            if (err) {
                log::warn("Failed to check existence of SFX library at {}: {}", sfxPath, err.message());
            } else {
                log::debug("SFX library was not at {}!", sfxPath);
            }
        }
    }
}
