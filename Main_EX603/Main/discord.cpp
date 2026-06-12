#include "stdafx.h"
#include "discord.h"
#include <mutex>
#include <chrono>
#include "Protect.h"

static int64_t eptime =
std::chrono::duration_cast<std::chrono::seconds>(
    std::chrono::system_clock::now().time_since_epoch()
).count();

void Discord::Initialize()
{
    DiscordEventHandlers handlers{};
    Discord_Initialize(gProtect.m_MainInfo.APPLICATION_ID, &handlers, 1, NULL);
}

void Discord::Update()
{
    DiscordRichPresence discordPresence{};
    discordPresence.state = gProtect.m_MainInfo.state;
    discordPresence.details = gProtect.m_MainInfo.details;
    discordPresence.startTimestamp = eptime;
    discordPresence.largeImageKey = gProtect.m_MainInfo.largeImageKey;
    discordPresence.largeImageText = gProtect.m_MainInfo.largeImageText;
    discordPresence.smallImageKey = gProtect.m_MainInfo.smallImageKey;
    discordPresence.smallImageText = gProtect.m_MainInfo.smallImageText;
    Discord_UpdatePresence(&discordPresence);
}
