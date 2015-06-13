#include "serverCreationScreen.h"
#include "shipSelectionScreen.h"
#include "gui/gameMasterUI.h"
#include "gameGlobalInfo.h"
#include "epsilonServer.h"
#include "main.h"

ServerCreationScreen::ServerCreationScreen()
{
    assert(game_server);
    
    (new GuiLabel(this, "SCENARIO_LABEL", "Scenario", 30))->addBox()->setPosition(-50, 50, ATopRight)->setSize(460, 50);
    (new GuiBox(this, "SCENARIO_BOX"))->setPosition(-50, 50, ATopRight)->setSize(460, 560);
    GuiListbox* scenario_list = new GuiListbox(this, "SCENARIO_LIST", [this](int index, string value) {
        selected_scenario_filename = value;
    });
    scenario_list->setPosition(-80, 100, ATopRight)->setSize(400, 500);
    
    float y = 50;
    (new GuiLabel(this, "GENERAL_LABEL", "General", 30))->addBox()->setPosition(50, y, ATopLeft)->setSize(550, 50);
    y += 50;
    (new GuiTextEntry(this, "SERVER_NAME", game_server->getServerName()))->setPosition(300, y, ATopLeft)->setSize(300, 50);
    (new GuiLabel(this, "NAME_LABEL", "Server name:", 30))->setAlignment(ACenterRight)->setPosition(50, y, ATopLeft)->setSize(250, 50);
    (new GuiBox(this, "NAME_BOX"))->setPosition(50, y, ATopLeft)->setSize(550, 50);
    y += 50;
    (new GuiLabel(this, "IP", sf::IpAddress::getLocalAddress().toString(), 30))->addBox()->setPosition(300, y, ATopLeft)->setSize(300, 50);
    (new GuiLabel(this, "IP_LABEL", "Server IP:", 30))->setAlignment(ACenterRight)->setPosition(50, y, ATopLeft)->setSize(250, 50);
    (new GuiBox(this, "IP_BOX"))->setPosition(50, y, ATopLeft)->setSize(550, 50);
    
    y += 70;
    (new GuiLabel(this, "PLAYER_SHIP_LABEL", "Player ships", 30))->addBox()->setPosition(50, y, ATopLeft)->setSize(550, 50);
    y += 50;
    (new GuiSelector(this, "WARP_JUMP_SELECT", [](int index, string value) {
        gameGlobalInfo->player_warp_jump_drive_setting = EPlayerWarpJumpDrive(index);
    }))->setOptions({"Ship default", "Warp-drive", "Jump-drive", "Both"})->setSelectionIndex((int)gameGlobalInfo->player_warp_jump_drive_setting)->setPosition(300, y, ATopLeft)->setSize(300, 50);
    (new GuiLabel(this, "WARP_JUMP_LABEL", "Warp/Jump:", 30))->setAlignment(ACenterRight)->setPosition(50, y, ATopLeft)->setSize(250, 50);
    (new GuiBox(this, "WARP_JUMP_BOX"))->setPosition(50, y, ATopLeft)->setSize(550, 50);
    y += 50;
    (new GuiSelector(this, "RADAR_SELECT", [](int index, string value) {
        gameGlobalInfo->long_range_radar_range = index * 5000 + 10000;
    }))->setOptions({"10000", "15000", "20000", "25000", "30000", "35000", "40000", "45000", "50000"})->setSelectionIndex((gameGlobalInfo->long_range_radar_range - 10000.) / 5000.0)->setPosition(300, y, ATopLeft)->setSize(300, 50);
    (new GuiLabel(this, "RADAR_LABEL", "Radar range:", 30))->setAlignment(ACenterRight)->setPosition(50, y, ATopLeft)->setSize(250, 50);
    (new GuiBox(this, "RADAR_BOX"))->setPosition(50, y, ATopLeft)->setSize(550, 50);

    y += 70;
    (new GuiLabel(this, "MAIN_SCREEN_LABEL", "Main screen", 30))->addBox()->setPosition(50, y, ATopLeft)->setSize(550, 50);
    y += 50;
    (new GuiSelector(this, "MAIN_TACTICLE_SELECT", [](int index, string value) {
        gameGlobalInfo->allow_main_screen_tactical_radar = index == 1;
    }))->setOptions({"No", "Yes"})->setSelectionIndex(gameGlobalInfo->allow_main_screen_tactical_radar ? 1 : 0)->setPosition(300, y, ATopLeft)->setSize(300, 50);
    (new GuiLabel(this, "MAIN_TACTICLE_LABEL", "Tacticle radar:", 30))->setAlignment(ACenterRight)->setPosition(50, y, ATopLeft)->setSize(250, 50);
    (new GuiBox(this, "MAIN_TACTICLE_BOX"))->setPosition(50, y, ATopLeft)->setSize(550, 50);
    y += 50;
    (new GuiSelector(this, "MAIN_LONG_RANGE_SELECT", [](int index, string value) {
        gameGlobalInfo->allow_main_screen_long_range_radar = index == 1;
    }))->setOptions({"No", "Yes"})->setSelectionIndex(gameGlobalInfo->allow_main_screen_long_range_radar ? 1 : 0)->setPosition(300, y, ATopLeft)->setSize(300, 50);
    (new GuiLabel(this, "MAIN_LONG_RANGE_LABEL", "Long range radar:", 30))->setAlignment(ACenterRight)->setPosition(50, y, ATopLeft)->setSize(250, 50);
    (new GuiBox(this, "MAIN_LONG_RANGE_BOX"))->setPosition(50, y, ATopLeft)->setSize(550, 50);

    y += 70;
    (new GuiLabel(this, "GAME_RULES_LABEL", "Game rules", 30))->addBox()->setPosition(50, y, ATopLeft)->setSize(550, 50);
    y += 50;
    (new GuiSelector(this, "GAME_FREQUENCIES_SELECT", [](int index, string value) {
        gameGlobalInfo->use_beam_shield_frequencies = index == 1;
    }))->setOptions({"No", "Yes"})->setSelectionIndex(gameGlobalInfo->use_beam_shield_frequencies ? 1 : 0)->setPosition(300, y, ATopLeft)->setSize(300, 50);
    (new GuiLabel(this, "GAME_FREQUENCIES_LABEL", "Frequencies:", 30))->setAlignment(ACenterRight)->setPosition(50, y, ATopLeft)->setSize(250, 50);
    (new GuiBox(this, "GAME_FREQUENCIES_BOX"))->setPosition(50, y, ATopLeft)->setSize(550, 50);
    y += 50;
    (new GuiSelector(this, "GAME_SYS_DAMAGE_SELECT", [](int index, string value) {
        gameGlobalInfo->use_system_damage = index == 1;
    }))->setOptions({"No", "Yes"})->setSelectionIndex(gameGlobalInfo->use_system_damage ? 1 : 0)->setPosition(300, y, ATopLeft)->setSize(300, 50);
    (new GuiLabel(this, "GAME_SYS_DAMAGE_LABEL", "System damage:", 30))->setAlignment(ACenterRight)->setPosition(50, y, ATopLeft)->setSize(250, 50);
    (new GuiBox(this, "GAME_SYS_DAMAGE_BOX"))->setPosition(50, y, ATopLeft)->setSize(550, 50);

    (new GuiButton(this, "CLOSE", "Close server", [this]() {
        destroy();
        disconnectFromServer();
        returnToMainMenu();
    }))->setPosition(150, -50, ABottomLeft)->setSize(300, 50);
    (new GuiButton(this, "START", "Start", [this]() {
        startScenario();
    }))->setPosition(-150, -50, ABottomRight)->setSize(300, 50);

    std::vector<string> scenario_filenames = findResources("scenario_*.lua");
    std::sort(scenario_filenames.begin(), scenario_filenames.end());

    for(string filename : scenario_filenames)
    {
        P<ResourceStream> stream = getResourceStream(filename);
        if (!stream) continue;

        string name = filename.substr(9, -4);

        for(int i=0; i<10; i++)
        {
            string line = stream->readLine().strip();
            if (!line.startswith("--"))
                continue;
            line = line.substr(2).strip();
            if (line.startswith("Name:"))
                name = line.substr(5).strip();
            //if (line.startswith("Description:"))
            //    info.description = line.substr(12).strip();
        }

        scenario_list->addEntry(name, filename);
    }
    scenario_list->setSelectionIndex(0);
}

void ServerCreationScreen::startScenario()
{
    P<ScriptObject> script = new ScriptObject();
    script->run(selected_scenario_filename);
    engine->registerObject("scenario", script);

    destroy();
    new ShipSelectionScreen();
}